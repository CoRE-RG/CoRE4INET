//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include <core4inet/utilities/pcapng/PCAPNGReader.h>

#include <cstring>

namespace CoRE4INET {

PCAPNGReader::PCAPNGReader() { // @suppress("Class members should be properly initialized")
    this->file = nullptr;
    this->filename = nullptr;
    this->filesize = 0;

    this->endReached = false;
    this->correctEndianess = false;
    this->initialTimestampNano = 0;
    this->currentBlockSize = 0;
    this->interfaceCount = 0;
    this->timeResolutions = {};

    this->currentSectionHeader = new section_header_block;
    this->currentPacketHeader = new enhanced_packet_block;

    this->etherFrames = {};
}

PCAPNGReader::~PCAPNGReader() {
    if (file) {
        fclose(file);
    }
}

void PCAPNGReader::initialize(const char *fileName) {
    this->filename = fileName;
    if (!filename) {
        throw std::invalid_argument("invalid filename.");
    }

    file = fopen(filename, "rb");
    if (file == nullptr) {
        throw std::invalid_argument("file couldn't be opened.");
    }

    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // check first block
    uint32_t blockType = readNextBlock();
    if (blockType != BT_SHB) {
        // every pcapng-file has to start with a section header
        throw std::invalid_argument("file doesn't begin with a section header.");
    }
}

void PCAPNGReader::reset() {
    fseek(file, 0, SEEK_SET);
    this->endReached = false;
    initialTimestampNano = 0;

    // check first block
    uint32_t blockType = readNextBlock();
    if (blockType != BT_SHB) {
        // every pcapng-file has to start with a section header
        throw std::invalid_argument("file doesn't begin with a section header.");
    }
}

uint32_t PCAPNGReader::readNextBlock() {
    if (ftell(file) >= filesize) {
        endReached = true;
        return 0;
    }

    // read general block header
    block_header* header = new block_header;
    fread(header, 1, sizeof(block_header), file);
    currentBlockSize = header->total_length - sizeof(block_header) - sizeof(block_trailer);

    // read specific block
    if (header->block_type == BT_SHB) {
        readSectionHeaderBlock();
    } else {
        if (!correctEndianess) {
            convertEndianess(header);
        }
        switch (header->block_type) {
            case BT_IDB:
                readInterfaceDescriptionBlock();
                break;
            case BT_EPB:
                readPacketBlock();
                break;
            default:
                // not relevant for basic functionality -> can be skipped for now
                fseek(file, currentBlockSize, SEEK_CUR);
        }
    }

    // skip general block trailer
    fseek(file, sizeof(block_trailer), SEEK_CUR);

    return header->block_type;
}

void PCAPNGReader::readSectionHeaderBlock() {
    section_header_block* sectionHeader = new section_header_block;
    fread(sectionHeader, 1, sizeof(section_header_block), file);
    if (sectionHeader->byte_order_magic == BYTE_ORDER_MAGIC) {
        correctEndianess = true;
    } else {
        correctEndianess = false;
        convertEndianess(sectionHeader);
    }
    currentSectionHeader = sectionHeader;

    // reset section specific variables
    timeResolutions.clear();
    interfaceCount = 0;

    // check for options
    if (currentBlockSize > sizeof(section_header_block)) {
        fseek(file, currentBlockSize - sizeof(section_header_block), SEEK_CUR);
    }
}

void PCAPNGReader::readInterfaceDescriptionBlock() {
    interface_description_block* interfaceDescription = new interface_description_block;
    fread(interfaceDescription, 1, sizeof(interface_description_block), file);
    if (!correctEndianess) {
        convertEndianess(interfaceDescription);
    }
    int8_t resolution = 0;

    // check for options
    uint32_t remainingOptionsSize = currentBlockSize - sizeof(interface_description_block);
    while (remainingOptionsSize > 0) {
        option_header* option = new option_header;
        fread(option, 1, sizeof(option_header), file);

        // check if time resolution is set
        if (option->option_code == IF_TSRESOL) {
            int8_t tResol;
            fread(&tResol, 1, option->option_length, file);
            resolution = tResol;
        } else {
            // other options are currently not relevant
            fseek(file, option->option_length, SEEK_CUR);
        }

        // skip padding bytes
        uint8_t numberOfUnalignedBytes = option->option_length % 4;
        uint8_t paddingBytes = (4 - numberOfUnalignedBytes) % 4;
        fseek(file, paddingBytes, SEEK_CUR);

        remainingOptionsSize -= (sizeof(option_header) + option->option_length + paddingBytes);
    }

    timeResolutions[interfaceCount] = resolution;
    interfaceCount++;
}

void PCAPNGReader::readPacketBlock() {
    enhanced_packet_block* header = new enhanced_packet_block;
    fread(header, 1, sizeof(enhanced_packet_block), file);

    // process packet header
    if (!correctEndianess) {
        convertEndianess(header);
    }
    currentPacketHeader = header;

    // set initial simulation time for the first packet of the file
    if (initialTimestampNano == 0) {
        uint64_t initialTimestamp = ((uint64_t)currentPacketHeader->timestamp_high << 32)
                           + (currentPacketHeader->timestamp_low);
        calculateSimTime(initialTimestamp, timeResolutions.at(currentPacketHeader->interface_id));
    }

    // read and process packet
    unsigned char packetBlock[currentPacketHeader->caplen];
    fread(packetBlock, 1, currentPacketHeader->caplen, file);
    createEthernetIIFrame(packetBlock);

    // skip padding bytes
    uint8_t numberOfUnalignedBytes = currentPacketHeader->caplen % 4;
    uint8_t paddingBytes = (4 - numberOfUnalignedBytes) % 4;
    fseek(file, paddingBytes, SEEK_CUR);

    // check for options
    uint32_t remainingBytes = currentBlockSize - sizeof(enhanced_packet_block)
                              - currentPacketHeader->caplen - paddingBytes;
    if (remainingBytes > 0) {
        fseek(file, remainingBytes, SEEK_CUR);
    }
}

bool PCAPNGReader::getNextPacketBlock() {
    uint32_t blockType;
    while (!endReached) {
        blockType = readNextBlock();
        if (blockType == BT_EPB) {
            return true;
        }
    }
    return false;
}

void PCAPNGReader::convertEndianess(void* blockBuffer) {
    // TODO with current pcapng-files not necessary
    throw std::invalid_argument("endianess of the section doesn't match endianess of the operating system.");
}

#define DESTADDRESS_BEGIN 0         /* begin of the destination address in an ethernet-packet-block */
#define SRCADDRESS_BEGIN 6          /* begin of the source address in an ethernet-packet-block */
#define ETHERTYPE_FIRSTBYTE_POS 12  /* position of the first ethertype-byte in an ethernet-packet-block */
#define ETHERTYPE_SECONDBYTE_POS 13 /* position of the second ethertype-byte in an ethernet-packet-block */
#define PAYLOAD_BEGIN 14            /* begin of the payload in an ethernet-packet-block */

void PCAPNGReader::createEthernetIIFrame(unsigned char* packetBlock) {
    inet::EthernetIIFrame *frame = new inet::EthernetIIFrame("Best-Effort Traffic", 7);

    /*
     * packetBlock: contains EthernetHeader and payload
     *      - destAddress:  6 Bytes
     *      - SrcAddress:   6 Bytes
     *      - type:         2 Bytes
     *      - Data:         46-15000 Bytes
     *      - CRC:          4 Bytes
     */

    uint16_t firstEtherTypeByte = ((uint16_t) *(packetBlock + ETHERTYPE_FIRSTBYTE_POS)) << 8;
    uint16_t secondEtherTypeByte = (uint16_t) *(packetBlock + ETHERTYPE_SECONDBYTE_POS);
    uint16_t etherType = firstEtherTypeByte + secondEtherTypeByte;

    inet::MACAddress destAddress = inet::MACAddress();
    inet::MACAddress srcAddress = inet::MACAddress();
    destAddress.setAddressBytes(&packetBlock[DESTADDRESS_BEGIN]);
    srcAddress.setAddressBytes(&packetBlock[SRCADDRESS_BEGIN]);

    frame->setDest(destAddress);
    frame->setSrc(srcAddress);
    frame->setEtherType(etherType);

    cPacket *payload_packet = new cPacket();
    payload_packet->setByteLength(static_cast<int64_t>(currentPacketHeader->caplen - PAYLOAD_BEGIN));
    frame->setByteLength(ETHER_MAC_FRAME_BYTES);
    frame->encapsulate(payload_packet);
    //TODO: use actual payload from file (currently not relevant for the simulation)

    //Padding
    if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES)
    {
        frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
    }

    etherFrames.push_back(frame);
}

inet::EthernetIIFrame* PCAPNGReader::getNextEthernetIIFrame() {
    if (etherFrames.empty() && !endReached) {
        if(!getNextPacketBlock()) {
            return nullptr;
        }
    } else if (endReached) {
        return nullptr;
    }

    inet::EthernetIIFrame* frame = etherFrames.front();
    etherFrames.pop_front();
    return frame;
}

simtime_t PCAPNGReader::calculateSimTime(uint64_t timestamp, int8_t timeResolution) {
    double timestampNano = 0;
    double base = 0;

    // the most significant bit decides whether the resolution is a negative power of 2 or 10
    // the remaining bits define the specific resolution
    if (timeResolution < 0) {
        // negative power of 2
        timeResolution &= 0111111;
        base = 2.0;
    }else if (timeResolution >= 0) {
        // negative power of 10
        base = 10.0;
    }

    double oldResolution = pow(base, (double)-timeResolution);
    double newResolution = pow(10, -9);
    double resolutionChangeFactor = newResolution / oldResolution;
    timestampNano = timestamp * resolutionChangeFactor;

    if (initialTimestampNano == 0) {
        initialTimestampNano = timestampNano;
    }

    simtime_t simulationTime = SimTime(timestampNano - initialTimestampNano, SIMTIME_NS);
    return simulationTime;
}

simtime_t PCAPNGReader::getNextSimTime() {
    if (!endReached && getNextPacketBlock()) {
        uint64_t timestamp = ((uint64_t)currentPacketHeader->timestamp_high << 32)
                             + (currentPacketHeader->timestamp_low);
        return calculateSimTime(timestamp, timeResolutions[currentPacketHeader->interface_id]);
    }
    return SimTime(0, SIMTIME_NS);
}

bool PCAPNGReader::endOfFileReached() {
    return endReached;
}

} /* namespace CoRE4INET */
