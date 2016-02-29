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

#include "core4inet/synchronisation/base/SyncBase.h"

#include "core4inet/base/NotifierConsts.h"

using namespace CoRE4INET;

int SyncBase::numInitStages() const
{
    return 1;
}

void SyncBase::initialize(int stage)
{
    if(stage==0){
        Scheduled::initialize();
    }
}

void SyncBase::notify(SyncNotificationKind kind)
{
    if (mayHaveListeners(NF_SYNC_STATE_CHANGE))
    {
        SyncNotification notification("SyncNotification", kind);
        emit(NF_SYNC_STATE_CHANGE, &notification);
    }
}
