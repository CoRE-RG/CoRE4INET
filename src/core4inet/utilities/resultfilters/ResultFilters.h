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

#ifndef CORE4INET_RESULTFILTERS_H
#define CORE4INET_RESULTFILTERS_H

//OMNeT++
#include "omnetpp.h"

namespace CoRE4INET {

using namespace omnetpp;

/**
 * @brief Filter that expects a cPacket and outputs its encapsulated cPacket
 *
 * @ingroup ResultFilters
 *
 * @author Till Steinbach
 */
class InnerMessageFilter : public cObjectResultFilter
{
        using cObjectResultFilter::receiveSignal;
    public:
        virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *object, cObject *details);
};

class InnerMessagePacketBytesFilter : public cObjectResultFilter
{
    public:
        using cObjectResultFilter::receiveSignal;
        virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *object, cObject *details);
};

class SubtractActualFromLastFilter : public cNumericResultFilter
{
    protected:
        double difference;
    public:
        double lastValue;
        virtual bool process(simtime_t &t, double& value, cObject *details) override;
        SubtractActualFromLastFilter()
        {
            this->difference = 0;
            this->lastValue = 0;
        }
};

/**
 * @brief Experimental (use ResultRecorder instead)
 *
 * @ingroup ResultFilters
 *
 * @author Till Steinbach
 */
class FloatingIntervalFilter : public cNumericResultFilter
{
    protected:
        simtime_t interval;
        std::map<simtime_t, double> inInterval;
    protected:
        virtual bool process(simtime_t &t, double& value, cObject *details) override;
    public:
        FloatingIntervalFilter();
};

/**
 * @brief Experimental (use ResultRecorder instead)
 *
 * @ingroup ResultFilters
 *
 * @author Till Steinbach
 */
class FloatingIntervalCountFilter : public FloatingIntervalFilter
{
    protected:
        virtual bool process(simtime_t &t, double& value, cObject *details) override;
};

/**
 * @brief Experimental (use ResultRecorder instead)
 *
 * @ingroup ResultFilters
 *
 * @author Till Steinbach
 */
class FloatingIntervalSumFilter : public FloatingIntervalFilter
{
    protected:
        virtual bool process(simtime_t &t, double& value, cObject *details) override;
};

/**
 * @brief Experimental (use ResultRecorder instead)
 *
 * @ingroup ResultFilters
 *
 * @author Till Steinbach
 */
class FloatingIntervalAvgFilter : public FloatingIntervalFilter
{
    protected:
        virtual bool process(simtime_t &t, double& value, cObject *details) override;
};

}

#endif
