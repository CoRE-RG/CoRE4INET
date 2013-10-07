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

#ifndef __TTETHERNETMODEL_PERIOD_H_
#define __TTETHERNETMODEL_PERIOD_H_

#include <omnetpp.h>

namespace TTEthernetModel {

class Timer;

/**
 * TODO - Generated class
 */
class Period : public cSimpleModule
{
    private:
        Timer *timer;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  public:
    /**
     * @brief Returns the current number of ticks
     *
     * @return Number of ticks since cycle start
     */
    virtual uint32_t getTicks();
    /**
     * @brief Returns the absolute number of ticks
     *
     * @return Number of ticks since simulation start
     */
    virtual uint64_t getTotalTicks();
};

} //namespace

#endif
