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

#ifndef __CORE4INET_HELPERFUNCTIONS_H_
#define __CORE4INET_HELPERFUNCTIONS_H_

//Std
#include <vector>
//CoRE4INET
#include "CoRE4INET_Timer.h"

//FIXME: Can be used when opp_makedep is able to use defines
//#ifdef WITH_AS6802_COMMON
//CoRE4INET
#include "PCFrame_m.h"
//#endif

//FIXME: Can be used when opp_makedep is able to use defines
//#ifdef WITH_AVB_COMMON
//CoRE4INET
#include "CoRE4INET_AVBDefs.h"
#include "AVBDefs_m.h"
//#endif

namespace CoRE4INET {

/**
 * @brief Replaces all occurrences of a string by another string.
 *
 * @param string the input string where the substrings are replaced
 * @param toFind the substring that should be replaced
 * @param replacement the string that replaces the toFind string
 * @return reference to the the modified string
 *
 * @author Till Steinbach
 */
std::string& replaceAll(std::string &string, const std::string &toFind, const std::string &replacement);

/**
 * @brief Adds a path to a parameter that contains paths to elements.
 *
 * @param parameter the parameter object that contains the paths
 * @param pathToAdd a string with the path that should be added to the parameter
 *
 * @author Till Steinbach
 */
void addPath(cPar &parameter, const std::string &pathToAdd);

/**
 * @brief Returns the gate defined by an object path.
 *
 * @param path the path to the gate
 * @return reference to the gate defined by path or nullptr if no such gate was found
 *
 * @author Till Steinbach
 */
cGate* gateByFullPath(const std::string &path);

/**
 * @brief Returns the gate of a node defined by: modulename.gatename.
 *
 * @param nameAndGate name of the module and gatename in the format: modulename.gatename
 * @param from a module of the node in which the gate can be found
 * @return reference to the gate defined by path or nullptr if no such gate was found
 *
 * @author Till Steinbach
 */
cGate* gateByShortPath(const std::string &nameAndGate, cModule *from);

/**
 * @brief Converts value in ticks to the transparent clock unit that is ns*0x10000
 *
 * @param ticks number of ticks
 * @param tick length of one tick in seconds
 * @return transparent clock representation of ticks
 *
 * @author Till Steinbach
 */
uint64_t ticksToTransparentClock(uint64_t ticks, simtime_t tick);

/**
 * @brief Converts value in seconds to the transparent clock unit that is ns*0x10000
 *
 * @param seconds number of seconds to convert
 * @return transparent clock representation of seconds
 */
uint64_t secondsToTransparentClock(simtime_t seconds);

/**
 * @brief Converts value in the transparent clock unit that is ns*0x10000 to ticks
 *
 * @param transparentClock value in transparentClock
 * @param tick length of one tick in seconds
 * @return ticks representation of transparent clock value
 *
 * @author Till Steinbach
 */
uint64_t transparentClockToTicks(uint64_t transparentClock, simtime_t tick);

/**
 * @brief generates an auto multicast addess by using generateAutoAddress and changing the least significant bit of the
 * first byte
 *
 * @return unique multicast address
 */
MACAddress generateAutoMulticastAddress();

#ifdef WITH_AS6802_COMMON
/**
 * @brief Sets the transparent clock information in the pcf
 *
 * @param pcf Protocol control Frame to change transparent clock information
 * @param static_tx_delay A static TX-delay to be added
 * @param scheduler The scheduler of the current node
 *
 * @author Till Steinbach
 */
void setTransparentClock(PCFrame *pcf, double static_tx_delay, Timer* scheduler);

/**
 * @brief Helper function checks whether a Frame is critical traffic.
 *
 * @param frame Pointer to the frame to check.
 * @return true if frame is critical, else false
 */
bool isCT(const EtherFrame *frame, uint32_t ctMarker, uint32_t ctMask);

/**
 * @brief Returns the critical traffic id for a given frame.
 *
 * @warning does not check if it is really critical traffic.
 * If you need to be sure use isCT(EtherFrame *frame)
 *
 * @param frame Pointer to the frame to get critical traffic id from.
 * @return critical traffic id
 *
 * @sa isCT(EtherFrame *frame)
 */
uint16_t getCTID(const EtherFrame *frame);
#endif

#ifdef WITH_AVB_COMMON
/**
 * @brief Calculates required bandwidth from given interval and framesize
 *
 * @param framesize the size of the frames of the stream
 * @param intervalFrames number of frames in an interval
 * @param interval interval time (usually 125us or 250us)
 *
 * @return bandwidth in bps
 */
unsigned long bandwidthFromSizeAndInterval(size_t framesize, size_t intervalFrames, simtime_t interval);
/**
 * @brief Returns the default interval for given SR classes
 *
 * @param srClass the SR class from the enum
 *
 * @return the default SR class interval
 */
const simtime_t getIntervalForClass(SR_CLASS srClass);
#endif
}

#endif /* HELPERFUNCTIONS_H_ */
