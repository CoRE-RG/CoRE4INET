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
#ifndef __TTE4INET_RESULTRECORDERS_H
#define __TTE4INET_RESULTRECORDERS_H

#include <cresultrecorder.h>

namespace TTEthernetModel{

class FloatingIntervalVectorRecorder: public cNumericResultRecorder
{
    protected:
        simtime_t interval;
        std::map<simtime_t, double> inInterval;
        void *handle;        // identifies output vector for the output vector manager
        simtime_t lastTime;  // to ensure increasing timestamp order
    protected:
        virtual void collect(simtime_t_cref t, double value);
    public:
        FloatingIntervalVectorRecorder();
        virtual void subscribedTo(cResultFilter *prev);
};

class FloatingIntervalCountVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual void collect(simtime_t_cref t, double value);
};

class FloatingIntervalSumVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual void collect(simtime_t_cref t, double value);
};

class FloatingIntervalAvgVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual void collect(simtime_t_cref t, double value);
};

}

#endif
