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


#ifndef CORE4INET_UTILITIES_PCAPNG_PCAPNGREADER_H_
#define CORE4INET_UTILITIES_PCAPNG_PCAPNGREADER_H_

#include <stddef.h>
#include <stdio.h>
#include <string>

//CoRE4INET
#include "core4inet/utilities/pcapng/pcapng.h"

//INET
#include "inet/linklayer/ethernet/Ethernet.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/linklayer/common/MACAddress.h"

namespace CoRE4INET {

/**
 * @brief Todo
 *
 *
 * @ingroup Utilities
 *
 * @author Sandra Reider
 */
class PCAPNGReader {

private:
    FILE        *file;
    const char  *filename;
    size_t      filesize;

    bool        endReached;
    bool        correctEndianess;
    uint64_t    initialTimestamp;
    uint32_t    currentBlockSize;

    section_header_block*  currentSectionHeader;
    enhanced_packet_block* currentPacketHeader;

    std::list<inet::EthernetIIFrame*> etherFrames;


    uint32_t readNextBlock();
    void readSectionHeaderBlock();
    void readInterfaceDescriptionBlock();
    void readPacketBlock();
    bool getNextPacketBlock();
    void convertEndianess(void* blockBuffer);
    void createEthernetIIFrame(unsigned char* packetBlock);

public:
    PCAPNGReader();
    virtual ~PCAPNGReader();
    void initialize(const char *filename);

    /**
     * reads the pcapng-file until the next ethernet-frame is reached and returns its time.
     * @return the time at which the next ethernet-frame was recorded in the pcapng-file.
     */
    simtime_t getNextSimTime();

    /**
     *
     * @return whether the entire file was read.
     */
    bool endOfFileReached();

    /**
     *
     * @return the last ethernet-frame that was read.
     */
    inet::EthernetIIFrame* getNextEthernetIIFrame();
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_UTILITIES_PCAPNG_PCAPNGREADER_H_ */
