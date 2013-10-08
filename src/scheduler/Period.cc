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

#include "Period.h"
#include "Timer.h"

namespace TTEthernetModel {

Define_Module(Period);

void Period::initialize()
{
    ASSERT(par("cycle_ticks").longValue()>par("offset_ticks").longValue());
    timer = dynamic_cast<Timer *>(gate("out")->getPathEndGate()->getOwnerModule());
    ASSERT(timer);
}

void Period::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

bool Period::registerEvent(SchedulerEvent *event){
    return timer->registerEvent(event, this);
}

uint32_t Period::getTicks()
{
    //cycle_ticks is added to assure a positive return value
    return (par("cycle_ticks").longValue() + timer->getTotalTicks() - par("offset_ticks").longValue()) % par("cycle_ticks").longValue();
}

uint64_t Period::getTotalTicks()
{
    return timer->getTotalTicks();
}

uint32_t Period::getCycles(){
    return timer->getTotalTicks()/par("cycle_ticks").longValue();
}

} //namespace
