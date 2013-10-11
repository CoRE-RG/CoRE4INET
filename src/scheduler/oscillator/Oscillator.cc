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

#include "Oscillator.h"

namespace TTEthernetModel {

Define_Module(Oscillator);

simsignal_t Oscillator::currentDrift = SIMSIGNAL_NULL;

void Oscillator::initialize(int stage)
{
    if(stage==0){
        currentDrift = registerSignal("currentDrift");
    }
}

int Oscillator::numInitStages() const{
    return 1;
}

void Oscillator::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

simtime_t Oscillator::getTick(){
    return SimTime(par("current_tick").doubleValue());
}
simtime_t Oscillator::getPreciseTick(){
    return SimTime(par("tick").doubleValue());
}

} //namespace
