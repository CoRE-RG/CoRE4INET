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

#ifndef CORE4INET_COMPARERESULTRECORDERS_H
#define CORE4INET_COMPARERESULTRECORDERS_H

#include "core4inet/base/CoRE4INET_Defs.h"


namespace CoRE4INET {

class SubtractActualFromLastRecorder : public omnetpp::cNumericResultRecorder
{
    protected:
        double min;
        double max;
        double lastValue;
        double thisValue;
        void *handle;        // identifies output vector for the output vector manager
        omnetpp::simtime_t lastTime;  // to ensure increasing timestamp order
    protected:
        virtual void collect(omnetpp::simtime_t_cref t, double value, omnetpp::cObject *details);
        virtual double calculate();
    public:
        SubtractActualFromLastRecorder();
        virtual void subscribedTo(omnetpp::cResultFilter *prev);
        virtual void initialize();
};

class SubtractActualFromLastRecorderMin : public SubtractActualFromLastRecorder
{
    protected:
        virtual double calculate();
};

class SubtractActualFromLastRecorderMax : public SubtractActualFromLastRecorder
{
    protected:
        virtual double calculate();
};

}

#endif
