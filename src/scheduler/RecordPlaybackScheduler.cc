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

#include "RecordPlaybackScheduler.h"

namespace CoRE4INET {

Define_Module(RecordPlaybackScheduler);

int RecordPlaybackScheduler::numInitStages() const
{
    return 1;
}

void RecordPlaybackScheduler::initialize(int stage)
{
    TTEScheduler::initialize(stage);
    if (stage == 0)
    {
        std::stringstream ss;
        ss << "scheduler";
        ss << this->par("id").longValue();

        if (this->par("read").boolValue())
        {
            fp = fopen(ss.str().c_str(), "r");
            counter = 0;
            values = new std::vector<double>(1200000);

            if (NULL != fp)
            {
                while (!feof(fp))
                {
                    int dummy;
                    double data;
                    int num = fscanf(fp, "%d %lf", &dummy, &data);
                    ASSERT(num == 2);
                    values->at((size_t) (counter++)) = data;
                }
            }
            else
            {
                perror("Error opening file");
            }
            counter = 0;
        }
        else if (this->par("write").boolValue())
        {
            fp = fopen(ss.str().c_str(), "w");
        }
    }
}
RecordPlaybackScheduler::~RecordPlaybackScheduler()
{
    if (this->par("read").boolValue() || this->par("write").boolValue())
    {
        fflush(fp);
        fclose(fp);
    }
}

void RecordPlaybackScheduler::changeDrift()
{
    simtime_t newDriftChange = 0;

    if (this->par("read").boolValue())
    {
        newDriftChange = values->at((size_t) (counter++));
        counter++;
    }
    else
    {
        newDriftChange = SimTime(par("drift_change").doubleValue());
        if (this->par("write").boolValue())
        {
            fprintf(fp, "%d ", this->cycles);
            fprintf(fp, " %.40f\n", newDriftChange.dbl());
        }
    }
    simtime_t newTick = currentTick + newDriftChange;
    if ((newTick - tick) > maxDrift)
        par("current_tick").setDoubleValue((tick + maxDrift).dbl());
    else if ((newTick - tick) < -maxDrift)
        par("current_tick").setDoubleValue((tick - maxDrift).dbl());
    else
        par("current_tick").setDoubleValue(newTick.dbl());
    emit(currentDrift, par("current_tick").doubleValue() - tick);
}

} //namespace
