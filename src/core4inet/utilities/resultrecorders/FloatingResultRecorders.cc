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
#include "core4inet/utilities/resultrecorders/FloatingResultRecorders.h"

//Std
#include <limits>

using namespace CoRE4INET;

Register_PerObjectConfigOptionU(CFGID_FLOATINGINTERVALVECTORRECORDER_MEASUREINTERVAL,
        "floatingintervalvectorrecorder-measure-interval", KIND_VECTOR, "s", "1s", "Time over which the floating interval is calculated. Default is 1 second")

FloatingIntervalVectorRecorder::FloatingIntervalVectorRecorder()
{
    uninitialized = true;
    interval = SimTime(-1);
    handle = nullptr;
    lastTime = 0;
}

void FloatingIntervalVectorRecorder::initialize()
{
    handle = ev.registerOutputVector(getComponent()->getFullPath().c_str(), getResultName().c_str());

    std::string vectorfullpath = getComponent()->getFullPath() + "." + getResultName();
    this->interval = ev.getConfig()->getAsDouble(vectorfullpath.c_str(),
            CFGID_FLOATINGINTERVALVECTORRECORDER_MEASUREINTERVAL, 0);
}

void FloatingIntervalVectorRecorder::subscribedTo(cResultFilter *prev)
{
    cNumericResultRecorder::subscribedTo(prev);
}

void FloatingIntervalVectorRecorder::collect(simtime_t_cref t, double value)
{
    if (uninitialized)
    {
        initialize();
        uninitialized = false;
    }
    if (t < lastTime)
    {
        throw cRuntimeError("%s: Cannot record data with an earlier timestamp (t=%s) "
                "than the previously recorded value (t=%s)", getClassName(), SIMTIME_STR(t), SIMTIME_STR(lastTime));
    }

    for (std::map<simtime_t, double>::iterator it = inInterval.begin(); it != inInterval.lower_bound((t - interval));)
    {
        simtime_t time = SimTime(it->first);
        inInterval.erase(it++);
        ev.recordInOutputVector(handle, time + interval, calculate());
    }

    if ((t - lastTime) > (2 * interval))
    {
        ev.recordInOutputVector(handle, t - interval, 0);
    }

    //add value to interval, give hint for faster execution
    if (inInterval.empty())
    {
        inInterval[t] = value;
    }
    else
    {
        inInterval.insert(--inInterval.end(), std::pair<simtime_t, double>(t, value));
    }
    //erase old values
    //inInterval.erase(inInterval.begin(), inInterval.lower_bound((t-interval)));

    getEnvir()->recordInOutputVector(handle, t, calculate());

    lastTime = t;
}

Register_ResultRecorder("floatingIntervalCountVector", FloatingIntervalCountVectorRecorder)

double FloatingIntervalCountVectorRecorder::calculate()
{
    return static_cast<double>(inInterval.size());
}

Register_ResultRecorder("floatingIntervalSumVector", FloatingIntervalSumVectorRecorder)

double FloatingIntervalSumVectorRecorder::calculate()
{
    double sumValue = 0;
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    return sumValue;
}

Register_ResultRecorder("floatingIntervalCapacityRecorder", FloatingIntervalCapacityRecorder)
double FloatingIntervalCapacityRecorder::calculate()
{
    double sumValue = 0;
    double frameUsedSumValue = 0;
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
        frameUsedSumValue += (*it).second + 38;
    }
    return sumValue / frameUsedSumValue * 100;
}

Register_ResultRecorder("floatingIntervalSumVectorPercent", FloatingIntervalSumVectorRecorderPercent)

double FloatingIntervalSumVectorRecorderPercent::calculate()
{
    double sumValue = 0;
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    cComponent *comp = getComponent();
    //    if (comp->getParentModule()->getFullName())
    double nominalDatarate =
            comp->getParentModule()->getSubmodule("mac")->gate("phys$i")->findIncomingTransmissionChannel()->getNominalDatarate();
    return sumValue / ((interval / SimTime(1)) * nominalDatarate / 100);
}

//Register_ResultRecorder("floatingIntervalSumVectorPercent", FloatingIntervalSumVectorRecorderPercent);
//
//double FloatingIntervalSumVectorRecorderPercent::calculate(){
//    double sumValue = 0;
//    for(std::map<simtime_t, double>::const_iterator it= inInterval.begin(); it!=inInterval.end();++it){
//        sumValue += (*it).second;
//    }
//    return sumValue /((interval / SimTime(1))* 100 * 1024 * 1024 / 100);;
//}

Register_ResultRecorder("floatingIntervalAvgVector", FloatingIntervalAvgVectorRecorder)

double FloatingIntervalAvgVectorRecorder::calculate()
{
    double sumValue = 0;
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    return sumValue / static_cast<double>(inInterval.size());
}

Register_ResultRecorder("floatingIntervalMinVector", FloatingIntervalMinVectorRecorder)

double FloatingIntervalMinVectorRecorder::calculate()
{
    double minValue = std::numeric_limits<double>::max();
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        if ((*it).second < minValue)
        {
            minValue = (*it).second;
        }
    }
    return minValue;
}

Register_ResultRecorder("floatingIntervalMaxVector", FloatingIntervalMaxVectorRecorder)

double FloatingIntervalMaxVectorRecorder::calculate()
{
    double maxValue = std::numeric_limits<double>::min();
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        if ((*it).second > maxValue)
        {
            maxValue = (*it).second;
        }
    }
    return maxValue;
}

Register_ResultRecorder("floatingIntervalVarianceVectorRecorder", FloatingIntervalVarianceVectorRecorder)

double FloatingIntervalVarianceVectorRecorder::calculate()
{
    double minValue = std::numeric_limits<double>::max();
    double maxValue = std::numeric_limits<double>::min();
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
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
 * Sums the values up received for each interval
 */
Register_ResultRecorder("floatingIntervalAvailableBandwidthPercent", FloatingIntervalAvailableBandwidthPercent)

double FloatingIntervalAvailableBandwidthPercent::calculate()
{
    //  Byte / ( (20 / 1000) * 1024 * 1024)
    double sumValue = 0;
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    cComponent *comp = getComponent();
    double nominalDatarate =
            comp->getParentModule()->getSubmodule("mac")->gate("phys$i")->findIncomingTransmissionChannel()->getNominalDatarate();
    return 100 - (sumValue / ((interval / SimTime(1)) * nominalDatarate / 100));
}
