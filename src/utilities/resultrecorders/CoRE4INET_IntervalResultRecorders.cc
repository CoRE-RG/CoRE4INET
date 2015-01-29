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

#include "CoRE4INET_IntervalResultRecorders.h"

//Std
#include <limits>
//OMNeT++
#include "cmodule.h"
#include "cchannel.h"

using namespace TTEthernetModel;

IntervalVectorRecorder::IntervalVectorRecorder()
{
    uninitialized = true;
    interval = SimTime(-1);
    handle = nullptr;
    lastTime = 0;

}

void IntervalVectorRecorder::initialize(){
    bool notSet=true;
    cComponent *comp = getComponent();
    do
    {
        if (comp->hasPar("measure_interval") && notSet)
        {
            interval = SimTime(comp->par("measure_interval").doubleValue());
            notSet = false;
        }
    } while ((comp = comp->getParentModule()));
}

void IntervalVectorRecorder::subscribedTo(cResultFilter *prev)
{
    cNumericResultRecorder::subscribedTo(prev);
    // we can register the vector here, because base class ensures we are subscribed only at once place
           opp_string_map attributes = getStatisticAttributes();
           handle = ev.registerOutputVector(getComponent()->getFullPath().c_str(), getResultName().c_str());
           ASSERT(handle != nullptr);
           //Attributes are title->interpolationmode ...
           for (opp_string_map::const_iterator it = attributes.begin(); it != attributes.end(); ++it)
           {
//               EV<<it->first.c_str()  <<"\n";
               ev.setVectorAttribute(handle, it->first.c_str(), it->second.c_str());
               if(opp_strcmp(it->first.c_str(), "measure_interval")==0)
               {
                   interval = SimTime::parse(it->second.c_str());
//                   EV << "Interval: " <<interval << "\n";
               }
           }
           if (interval < SimTime(0))
           {
               bool notSet=true;
               cComponent *comp = getComponent();
               do
               {
                   if (comp->hasPar("measure_interval") && notSet)
                   {
                       interval = SimTime(comp->par("measure_interval").doubleValue());
                       notSet = false;
//                       EV << "Interval: " <<interval << comp->getFullName()<<"\n";
                   }
               } while ((comp = comp->getParentModule()));
           }
           if (interval < SimTime(0))
           {
               interval = SimTime(1);
           }
}

void IntervalVectorRecorder::collect(simtime_t_cref t, double value)
{
    if (uninitialized){
        initialize();
        uninitialized = false;
    }
    if (t < lastTime)
    {
        throw cRuntimeError("%s: Cannot record data with an earlier timestamp (t=%s) "
                "than the previously recorded value (t=%s)", getClassName(), SIMTIME_STR(t), SIMTIME_STR(lastTime));
    }


    if (lastTime + interval == t)
    {
        addValueToInterval(t, value);
        ev.recordInOutputVector(handle, lastTime+interval, calculate());
        inInterval.clear();
        lastTime = lastTime+interval;
    }
    else if (lastTime + interval < t)
    {
        ev.recordInOutputVector(handle, lastTime+interval, calculate());
        inInterval.clear();
        addValueToInterval(t,value);

        //Calculate every point between
        int i = 1;
        for (i = 1; i < ((t-lastTime)/interval)-1;i++)
        {
            ev.recordInOutputVector(handle, lastTime+interval*(i+1), 0);
        }
        lastTime = lastTime+interval*i;
    }
    else
    {
        addValueToInterval(t, value);
    }
}

void IntervalVectorRecorder::addValueToInterval(simtime_t_cref t, double value)
{
    if (inInterval.empty())
    {
        inInterval[t] = value;
    }
    else
    {
        inInterval.insert(--inInterval.end(), std::pair<simtime_t, double>(t, value));
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
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
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
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
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
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
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
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
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
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
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
 */
Register_ResultRecorder("IntervalSumVectorPercent", IntervalSumVectorRecorderPercent)

double IntervalSumVectorRecorderPercent::calculate()
{
    //  Byte / ( (20 / 1000) * 1024 * 1024)
    double sumValue = 0;
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    cComponent *comp = getComponent();
    double nominalDatarate = comp->getParentModule()->getSubmodule("mac")->gate("phys$i")->findIncomingTransmissionChannel()->getNominalDatarate();
    return sumValue /((interval / SimTime(1))* nominalDatarate / 100);
}


/*
 * Sums the values up received for each interval
 */
Register_ResultRecorder("IntervalAvailableBandwidthPercent", IntervalAvailableBandwidthPercent)

double IntervalAvailableBandwidthPercent::calculate()
{
    //  Byte / ( (20 / 1000) * 1024 * 1024)
    double sumValue = 0;
    for (std::map<simtime_t, double>::const_iterator it = inInterval.begin(); it != inInterval.end(); ++it)
    {
        sumValue += (*it).second;
    }
    cComponent *comp = getComponent();
    double nominalDatarate = comp->getParentModule()->getSubmodule("mac")->gate("phys$i")->findIncomingTransmissionChannel()->getNominalDatarate();
    return 100 - (sumValue /((interval / SimTime(1)) * nominalDatarate / 100)); // TODO Linkgeschwindigkeit
}
