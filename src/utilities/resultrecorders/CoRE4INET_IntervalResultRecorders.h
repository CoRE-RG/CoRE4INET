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
#ifndef __TTE4INET_INTERVALRESULTRECORDERS_H
#define __TTE4INET_INTERVALRESULTRECORDERS_H

//OMNeT++
#include "cresultrecorder.h"

namespace TTEthernetModel {

class IntervalVectorRecorder : public cNumericResultRecorder
{
    protected:
        bool uninitialized;
        simtime_t interval;
        std::map<simtime_t, double> inInterval;
        void *handle;        // identifies output vector for the output vector manager
        simtime_t lastTime;  // to ensure increasing timestamp order
    protected:
        virtual void collect(simtime_t_cref t, double value);
        virtual void addValueToInterval(simtime_t_cref t, double value);
        virtual double calculate() = 0;
    public:
        IntervalVectorRecorder();
        virtual void subscribedTo(cResultFilter *prev);
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
