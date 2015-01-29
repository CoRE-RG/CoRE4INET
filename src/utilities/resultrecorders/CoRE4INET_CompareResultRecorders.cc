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

#include "CoRE4INET_CompareResultRecorders.h"

using namespace TTEthernetModel;

SubtractActualFromLastRecorder::SubtractActualFromLastRecorder()
{
    this->min = 0;
    this->max = 0;
    this->lastValue = 0;
    this->thisValue = 0;
    this->handle = nullptr;
}

void SubtractActualFromLastRecorder::initialize(){
    lastValue = 0;
    thisValue = 0;
}

void SubtractActualFromLastRecorder::subscribedTo(cResultFilter *prev)
{
    cNumericResultRecorder::subscribedTo(prev);
    opp_string_map attributes = getStatisticAttributes();
    handle = ev.registerOutputVector(getComponent()->getFullPath().c_str(), getResultName().c_str());
    ASSERT(handle != nullptr);
}

void SubtractActualFromLastRecorder::collect(simtime_t_cref t, double value)
{
    lastValue = thisValue;
    thisValue = value;
    ev.recordInOutputVector(handle, t, calculate());
}

Register_ResultRecorder("subtractActualFromLast", SubtractActualFromLastRecorder);

double SubtractActualFromLastRecorder::calculate()
{
    return thisValue - lastValue;
}

Register_ResultRecorder("subtractActualFromLastMin", SubtractActualFromLastRecorderMin);

double SubtractActualFromLastRecorderMin::calculate()
{
    return thisValue - lastValue;
}

Register_ResultRecorder("subtractActualFromLastMax", SubtractActualFromLastRecorderMax);

double SubtractActualFromLastRecorderMax::calculate()
{
    if ((thisValue - lastValue ) > max){
        return thisValue - lastValue;
    } else return 0;
}
