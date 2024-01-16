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
using namespace inet;

namespace CoRE4INET {

/**
 * @brief Class that reads ethernetIIframes from pcapng files.
 *
 * @ingroup Utilities
 * @author Sandra Reider, Philipp Meyer
 */
class PCAPNGReader {

private:
    /**
     * the pcapng file.
     */
    FILE *file;
    /**
     * the name of the pcapng file.
     */
    const char *filename;
    /**
     * the size of the pcapng file.
     */
    size_t filesize;

    /**
     * whether the end of file was reached.
     */
    bool endReached;
    /**
     * whether the endianess of the file matches the endianess of the operating system.
     */
    bool correctEndianess;

    /**
     * the timestamp in nanoseconds of the first packet block in the file.
     */
    uint64_t initialTimestampNano;
    /**
     * the size of the block that is currently read.
     */
    uint32_t currentBlockSize;
    /**
     * the number of interface blocks in the current section.
     */
    uint32_t interfaceCount;
    /**
     * the number of the current packet block.
     */
    uint64_t currentPackeBlockNo;
    /**
     * the time resolution of the interfaces in the current section.
     */
    std::map<uint32_t, int8_t> timeResolutions;

    /**
     * the header of the currently read section.
     */
    section_header_block* currentSectionHeader;
    /**
     * the header of the currently read packet.
     */
    enhanced_packet_block* currentPacketHeader;

    /**
     * all ethernet frames that were read but not (yet) returned.
     */
    std::list<inet::EthernetIIFrame*> etherFrames;

    /**
     * processes the next block in the file.
     * @return the id of the block.
     */
    uint32_t readNextBlock();

    /**
     * processes the section header block.
     */
    void readSectionHeaderBlock();

    /**
     * processes the interface description block.
     */
    void readInterfaceDescriptionBlock();

    /**
     * processes the packet block.
     */
    void readPacketBlock();

    /**
     * processes all blocks until the next packet block or the end of file is reached.
     * @return whether a packet block was found.
     */
    bool getNextPacketBlock();

    /**
     * converts the endianess of the block to match the operationg system.
     * @param blockBuffer the block.
     */
    void convertEndianess(void* blockBuffer);

    /**
     * creates an ethernet-frame from the packet block.
     * @param packetBlockNo the number of the packet block.
     * @param packetBlock the block that contains an ethernet frame.
     */
    void createEthernetIIFrame(uint64_t packetBlockNo, unsigned char* packetBlock);

    /**
     * calculates the simulation time for a timestamp and resolution.
     * @param timestamp the timestamp.
     * @param timeResolution the resolution of the timestamp.
     * @return the simulation time that is defined by the timestamp and resolution.
     */
    simtime_t calculateSimTime(uint64_t timestamp, int8_t timeResolution);

public:
    PCAPNGReader();
    virtual ~PCAPNGReader();
    void initialize(const char *filename);

    /**
     * resets the Reader to the beginning of the pcapng-file.
     */
    void reset();

    /**
     * reads the pcapng-file until the next ethernet-frame is reached and returns its time.
     * @return the time at which the next ethernet-frame was recorded in the pcapng-file.
     */
    simtime_t getNextSimTime();

    /**
     * determines if all blocks from the file were read.
     * @return whether the entire file was read.
     */
    bool endOfFileReached();

    /**
     * gets the next ethernet frame.
     * @return the next ethernet-frame.
     */
    inet::EthernetIIFrame* getNextEthernetIIFrame();
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_UTILITIES_PCAPNG_PCAPNGREADER_H_ */
