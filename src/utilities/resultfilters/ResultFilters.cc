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
#include "ResultFilters.h"

#include <cmessage.h>

using namespace CoRE4INET;

Register_ResultFilter("innerMessage", InnerMessageFilter);

void InnerMessageFilter::receiveSignal(__attribute((unused))  cResultFilter *prev, simtime_t_cref t, cObject *object)
{
    if (dynamic_cast<cPacket *>(object))
    {
        cPacket *innerPacket = (cPacket *) object;
        cPacket *tmpPacket;
        while ((tmpPacket = innerPacket->decapsulate()) != NULL)
        {
            innerPacket = tmpPacket;
        }
        fire(this, t, innerPacket);
        delete (innerPacket);
    }
}

FloatingIntervalFilter::FloatingIntervalFilter()
{
    interval = SimTime(1);
}

bool FloatingIntervalFilter::process(simtime_t &t, double &value)
{
    //first add new value to interval, give hint for faster execution
    if (inInterval.size() > 0)
    {
        inInterval.insert(--inInterval.end(), std::pair<simtime_t, double>(t, value));
    }
    else
    {
        inInterval[t] = value;
    }
    //erase old values
    inInterval.erase(inInterval.begin(), inInterval.lower_bound((t - interval)));
    return true;
}

Register_ResultFilter("floatingIntervalCount", FloatingIntervalCountFilter);

bool FloatingIntervalCountFilter::process(simtime_t &t, double &value)
{
    FloatingIntervalFilter::process(t, value);
    //return size
    value = inInterval.size();
    return true;
}

Register_ResultFilter("floatingIntervalSum", FloatingIntervalSumFilter);

bool FloatingIntervalSumFilter::process(simtime_t &t, double &value)
{
    FloatingIntervalFilter::process(t, value);
    //build sum
    double newValue = 0;
    for (std::map<simtime_t, double>::iterator it2 = inInterval.begin(); it2 != inInterval.end(); ++it2)
    {
        newValue += (*it2).second;
    }
    value = newValue;
    return true;
}

Register_ResultFilter("floatingIntervalAvg", FloatingIntervalAvgFilter);

bool FloatingIntervalAvgFilter::process(simtime_t &t, double &value)
{
    FloatingIntervalFilter::process(t, value);
    //build average
    double newValue = 0;
    for (std::map<simtime_t, double>::iterator it2 = inInterval.begin(); it2 != inInterval.end(); ++it2)
    {
        newValue += (*it2).second;
    }
    value = (newValue / inInterval.size());
    return true;
}
