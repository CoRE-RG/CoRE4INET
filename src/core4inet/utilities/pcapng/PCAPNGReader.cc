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

namespace CoRE4INET {

PCAPNGReader::PCAPNGReader(const char *filename) {
    file = nullptr;
    this->filename = filename;
}

PCAPNGReader::~PCAPNGReader() {
    if (file) {
        fclose(file);
    }
}

void PCAPNGReader::initialize() {
    // TODO: check filename
    file = fopen(filename, "rb");
    if (file == nullptr) {
        // TODO
    }

    // TODO: pacap-time -> simulation-time
}

void PCAPNGReader::readNextBlock() {
    block_header header;
    fread(header, 1, sizeof(block_header), file);

    switch (header.block_type) {
        case BT_SHB:
            readSectionHeaderBlock();
            break;
        case BT_IDB:
            readInterfaceDescriptionBlock();
            break;
        case BT_EPB:
            readPacketBlock();
            break;
        default:
            // TODO
    }
}

void PCAPNGReader::readSectionHeaderBlock() {
    // TODO: one SHB-object for current SHB
}

void PCAPNGReader::readInterfaceDescriptionBlock() {
    // TODO: global list? for all current IDBs
}

void PCAPNGReader::readPacketBlock() {
    enhanced_packet_block packet_header;
    fread(packet_header, 1, sizeof(enhanced_packet_block), file);

    byte* data_buffer;
    fread(data_buffer, 1, packet_header.len, file);
}

} /* namespace CoRE4INET */
