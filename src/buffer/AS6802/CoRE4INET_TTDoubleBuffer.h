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

#ifndef __CORE4INET_TTDOUBLEBUFFER_H_
#define __CORE4INET_TTDOUBLEBUFFER_H_

//CoRE4INET
#include "CoRE4INET_TTBuffer.h"
#include "CoRE4INET_DoubleBuffer.h"

namespace CoRE4INET {

/**
 * @brief Time-triggered double buffer class.
 *
 * The Frame is stored and released time-triggered using a previously
 * registered SchedulerActionTimeEvent. The Buffer interacts with the TTEScheduler.
 *
 * @sa TTBuffer, TTDoubleBuffer, CTBuffer
 *
 * @ingroup Buffer AS6802
 *
 * @author Till Steinbach
 */
class TTDoubleBuffer : public virtual TTBuffer, public virtual DoubleBuffer
{
};
}
#endif
