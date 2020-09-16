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
    this->initialTimestamp = 0;
    this->currentBlockSize = 0;

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
    //block_trailer* trailer = new block_trailer;
    //fread(trailer, 1, sizeof(block_trailer), file);

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
    // check for options
    if (currentBlockSize > sizeof(section_header_block)) {
        fseek(file, currentBlockSize - sizeof(section_header_block), SEEK_CUR);
    }
}

void PCAPNGReader::readInterfaceDescriptionBlock() {
    // TODO: global list? for all current IDBs, currently not used/necessary
    interface_description_block* interfaceDescription = new interface_description_block;
    fread(interfaceDescription, 1, sizeof(interface_description_block), file);
    if (!correctEndianess) {
        convertEndianess(interfaceDescription);
    }
    // check for options
    if (currentBlockSize > sizeof(interface_description_block)) {
        // TODO: check for if_tsresol option and save resolution for simtime
        fseek(file, currentBlockSize - sizeof(interface_description_block), SEEK_CUR);
    }
}

void PCAPNGReader::readPacketBlock() {
    enhanced_packet_block* header = new enhanced_packet_block;
    fread(header, 1, sizeof(enhanced_packet_block), file);

    // process packet header
    if (!correctEndianess) {
        convertEndianess(header);
    }
    currentPacketHeader = header;
    if (initialTimestamp == 0) {
        initialTimestamp = ((uint64_t)currentPacketHeader->timestamp_high << 32)
                           + (currentPacketHeader->timestamp_low);;
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
}

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

    //uint16_t firstEtherTypeByte = ((uint16_t) *(packetBlock + 12)) << 8;
    //uint16_t secondEtherTypeByte = (uint16_t) *(packetBlock + 13);
    //uint16_t etherType = firstEtherTypeByte + secondEtherTypeByte;
    uint16_t etherType = (uint16_t)((*(packetBlock + 12) << 8) + *(packetBlock + 13));

    inet::MACAddress destAddress = inet::MACAddress();
    inet::MACAddress srcAddress = inet::MACAddress();
    destAddress.setAddressBytes(&packetBlock[0]);
    srcAddress.setAddressBytes(&packetBlock[6]);

    frame->setDest(destAddress);
    frame->setSrc(srcAddress);
    frame->setEtherType(etherType);

    cPacket *payload_packet = new cPacket();
    payload_packet->setByteLength(static_cast<int64_t>(currentPacketHeader->caplen - 14)); // TODO magic numbers
    frame->setByteLength(ETHER_MAC_FRAME_BYTES);
    frame->encapsulate(payload_packet); // TODO: use actual payload (this->currentPacketBlock + 14)

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

simtime_t PCAPNGReader::getNextSimTime() {
    if (!endReached && getNextPacketBlock()) {
        uint64_t timestamp = ((uint64_t)currentPacketHeader->timestamp_high << 32)
                             + (currentPacketHeader->timestamp_low);
        // TODO: richtige Größe (ns, us...) verwenden -> aus tsresol-option vom interface description block auslesen
        return SimTime(timestamp - initialTimestamp, SIMTIME_NS);
    }
    return SimTime(0, SIMTIME_NS);
}

bool PCAPNGReader::endOfFileReached() {
    return endReached;
}

} /* namespace CoRE4INET */

