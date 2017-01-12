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

#ifndef CORE4INET_INTERVALRESULTRECORDERS_H
#define CORE4INET_INTERVALRESULTRECORDERS_H

#include "core4inet/base/CoRE4INET_Defs.h"

namespace CoRE4INET {

extern omnetpp::cConfigOption *CFGID_INTERVALVECTORRECORDER_MEASUREINTERVAL;

class IntervalVectorRecorder : public omnetpp::cNumericResultRecorder
{
    protected:
        bool uninitialized;
        omnetpp::simtime_t interval;
        std::map<omnetpp::simtime_t, double> inInterval;
        void *handle;        // identifies output vector for the output vector manager
        omnetpp::simtime_t lastTime;  // to ensure increasing timestamp order
    protected:
        virtual void collect(omnetpp::simtime_t_cref t, double value, omnetpp::cObject *details);
        virtual void addValueToInterval(omnetpp::simtime_t_cref t, double value);
        virtual double calculate() = 0;
    public:
        IntervalVectorRecorder();
        virtual void subscribedTo(omnetpp::cResultFilter *prev);
        virtual void initialize();
};

class IntervalCountVectorRecorder : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class IntervalSumVectorRecorder : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class IntervalCapacityRecorder : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class IntervalSumVectorRecorderPercent : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};
class IntervalAvgVectorRecorder : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class IntervalMinVectorRecorder : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class IntervalMaxVectorRecorder : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class IntervalVarianceVectorRecorder : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class IntervalAvailableBandwidthPercent : public IntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

}

#endif
