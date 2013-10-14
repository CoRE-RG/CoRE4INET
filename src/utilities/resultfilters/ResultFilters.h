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
#ifndef __TTE4INET_RESULTFILTERS_H
#define __TTE4INET_RESULTFILTERS_H

#include <cresultfilter.h>

namespace TTEthernetModel{

/**
 * Filter that expects a cPacket and outputs its encapsulated cPacket
 */
class InnerMessageFilter : public cObjectResultFilter
{
    public:
        virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *object);
};

class FloatingIntervalFilter : public cNumericResultFilter{
    protected:
        simtime_t interval;
        std::map<simtime_t, double> inInterval;
    protected:
        virtual bool process(simtime_t &t, double& value);
    public:
        FloatingIntervalFilter();
};

class FloatingIntervalCountFilter : public FloatingIntervalFilter
{
    protected:
        virtual bool process(simtime_t &t, double& value);
};

class FloatingIntervalSumFilter : public FloatingIntervalFilter
{
    protected:
        virtual bool process(simtime_t &t, double& value);
};

class FloatingIntervalAvgFilter : public FloatingIntervalFilter
{
    protected:
        virtual bool process(simtime_t &t, double& value);
};

}

#endif
