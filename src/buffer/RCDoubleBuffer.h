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

#ifndef __TTETHERNETMODELV2_RCDOUBLEBUFFER_H_
#define __TTETHERNETMODELV2_RCDOUBLEBUFFER_H_

#include <omnetpp.h>
#include <RCBuffer.h>
#include <DoubleBuffer.h>
#include <EtherFrame_m.h>

namespace TTEthernetModel {

/**
 * @brief Rate-constrained double buffer class.
 *
 * The Frame is stored and released immediately when the bag has expired previously.
 * If the bag has not expired yet the frame is stored. The implementation uses a
 * SchedulerTimerEvent that is registered at the TTEScheduler.
 *
 * @sa RCBuffer, RCDoubleBuffer, CTBuffer
 *
 * @ingroup Buffer
 */
class RCDoubleBuffer : public RCBuffer, DoubleBuffer
{

};
}

#endif
