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

#include "CoRE4INET_NoSync.h"

//CoRE4INET
#include "CoRE4INET_NotifierConsts.h"

//Auto-generated Messages
#include "scheduler/SchedulerMessageEvents_m.h"
#include "SyncNotification_m.h"

//INET
#include "Compat.h"

using namespace CoRE4INET;

Define_Module(NoSync);

int NoSync::numInitStages() const
{
        return 1;
}

void NoSync::initialize(int stage)
{
    if (stage == 0)
    {
        if (mayHaveListeners(NF_SYNC_STATE_CHANGE))
            {
                SyncNotification notification("SyncNotification", ASYNC);
                emit(NF_SYNC_STATE_CHANGE, &notification);
            }
        if (ev.isGUI())
        {
            getDisplayString().setTagArg("i", 1, "red");
        }
    }
}

void NoSync::handleMessage(cMessage *msg)
{
    delete msg;
}
