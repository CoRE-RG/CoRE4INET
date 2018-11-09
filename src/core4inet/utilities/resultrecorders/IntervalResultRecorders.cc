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

#include "core4inet/utilities/resultrecorders/IntervalResultRecorders.h"

//Std
#include <limits>

using namespace CoRE4INET;

Register_PerObjectConfigOptionU(CoRE4INET::CFGID_INTERVALVECTORRECORDER_MEASUREINTERVAL,
        "intervalvectorrecorder-measure-interval", KIND_VECTOR, "s", "1s",
        "interval in which the value is calculated. Default is 1 second")

IntervalVectorRecorder::IntervalVectorRecorder()
{
    uninitialized = true;
    interval = omnetpp::SimTime(-1);
    handle = nullptr;
    lastTime = 0;

}

void IntervalVectorRecorder::initialize()
{
    handle = omnetpp::getEnvir()->registerOutputVector(getComponent()->getFullPath().c_str(), getResultName().c_str());

    std::string vectorfullpath = getComponent()->getFullPath() + "." + getResultName();
    this->interval = omnetpp::getEnvir()->getConfig()->getAsDouble(vectorfullpath.c_str(),
            CFGID_INTERVALVECTORRECORDER_MEASUREINTERVAL, 0);
}

void IntervalVectorRecorder::subscribedTo(omnetpp::cResultFilter *prev)
{
    cNumericResultRecorder::subscribedTo(prev);
}

void IntervalVectorRecorder::collect(omnetpp::simtime_t_cref t, double value, __attribute__((unused)) omnetpp::cObject *details)
{
    if (uninitialized)
    {
        initialize();
        uninitialized = false;
    }
    if (t < lastTime)
    {
        throw omnetpp::cRuntimeError("%s: Cannot record data with an earlier timestamp (t=%s) "
                "than the previously recorded value (t=%s)", getClassName(), SIMTIME_STR(t), SIMTIME_STR(lastTime));
    }

    if (lastTime + interval == t)
    {
        addValueToInterval(t, value);
        omnetpp::getEnvir()->recordInOutputVector(handle, lastTime + interval, calculate());
        inInterval.clear();
        lastTime = lastTime + interval;
    }
    else if (lastTime + interval < t)
    {
        omnetpp::getEnvir()->recordInOutputVector(handle, lastTime + interval, calculate());
        inInterval.clear();
        addValueToInterval(t, value);

        //Calculate every point between
        int i = 1;
        for (i = 1; i < ((t - lastTime) / interval) - 1; i++)
        {
            omnetpp::getEnvir()->recordInOutputVector(handle, lastTime + interval * (i + 1), 0);
        }
        lastTime = lastTime + interval * i;
    }
    else
    {
        addValueToInterval(t, value);
    }
}

void IntervalVectorRecorder::addValueToInterval(omnetpp::simtime_t_cref t, double value)
{
    if (inInterval.empty())
    {
        inInterval[t] = value;
    }
    else
    {
        inInterval.insert(--inInterval.end(), std::pair<omnetpp::simtime_t, double>(t, value));
    }
}

/*
 * Counts the values received for each interval
 */
Register_ResultRecorder("IntervalCountVector", IntervalCountVectorRecorder)

double IntervalCountVectorRecorder::calculate()
{
    return static_cast<double>(inInterval.size());
}

/*
 * Sums the values up received for each interval
 */
Register_ResultRecorder("IntervalSumVector", IntervalSumVectorRecorder)

double IntervalSumVectorRecorder::calculate()
{
    double sumValue = 0;
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    return sumValue;
}

/*
 * Sums the values up received for each interval
 */
Register_ResultRecorder("IntervalCapacityRecorder", IntervalCapacityRecorder)

double IntervalCapacityRecorder::calculate()
{
    static int ETHERNETHEADERSIZE = 38;
    double sumValue = 0;
    double frameUsedSumValue = 0;
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
        frameUsedSumValue += (*it).second + ETHERNETHEADERSIZE;
    }
    return sumValue / frameUsedSumValue * 100;
}

/*
 * Gives the average value for each interval
 */
Register_ResultRecorder("IntervalAvgVector", IntervalAvgVectorRecorder)

double IntervalAvgVectorRecorder::calculate()
{
    double sumValue = 0;
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    return sumValue / static_cast<double>(inInterval.size());
}

/*
 * Gives the minimal value for each interval
 */
Register_ResultRecorder("IntervalMinVector", IntervalMinVectorRecorder)

double IntervalMinVectorRecorder::calculate()
{
    double minValue = std::numeric_limits<double>::max();
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        if ((*it).second < minValue)
        {
            minValue = (*it).second;
        }
    }
    return minValue;
}

/*
 * Gives the maximal value for each interval
 */
Register_ResultRecorder("IntervalMaxVector", IntervalMaxVectorRecorder)

double IntervalMaxVectorRecorder::calculate()
{
    double maxValue = std::numeric_limits<double>::min();
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        if ((*it).second > maxValue)
        {
            maxValue = (*it).second;
        }
    }
    return maxValue;
}

/*
 * Gives the variance for each interval
 */
Register_ResultRecorder("IntervalVarianceVector", IntervalVarianceVectorRecorder)

double IntervalVarianceVectorRecorder::calculate()
{
    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::min();
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        if ((*it).second < minValue)
        {
            minValue = (*it).second;
        }
        if ((*it).second > maxValue)
        {
            maxValue = (*it).second;
        }
    }
    return (maxValue - minValue);
}

/*
 */
Register_ResultRecorder("IntervalSumVectorPercent", IntervalSumVectorRecorderPercent)

double IntervalSumVectorRecorderPercent::calculate()
{
    //  Byte / ( (20 / 1000) * 1024 * 1024)
    double sumValue = 0;
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    omnetpp::cComponent *comp = getComponent();
    double nominalDatarate =
            comp->getParentModule()->getSubmodule("mac")->gate("phys$i")->findIncomingTransmissionChannel()->getNominalDatarate();
    return sumValue / ((interval / omnetpp::SimTime(1)) * nominalDatarate / 100);
}

/*
 * Sums the values up received for each interval
 */
Register_ResultRecorder("IntervalAvailableBandwidthPercent", IntervalAvailableBandwidthPercent)

double IntervalAvailableBandwidthPercent::calculate()
{
    //  Byte / ( (20 / 1000) * 1024 * 1024)
    double sumValue = 0;
    for (std::map<omnetpp::simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    omnetpp::cComponent *comp = getComponent();
    double nominalDatarate =
            comp->getParentModule()->getSubmodule("mac")->gate("phys$i")->findIncomingTransmissionChannel()->getNominalDatarate();
    return 100 - (sumValue / ((interval / omnetpp::SimTime(1)) * nominalDatarate / 100));
}
