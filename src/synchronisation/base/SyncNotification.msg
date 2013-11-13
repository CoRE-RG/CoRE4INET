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
namespace CoRE4INET;

//
// Message used to notify application layer about synchronisation state
// uses SyncNotificationKind
//
// @see SyncNotificationKind
//
// @author Till Steinbach
message SyncNotification
{
}


//
// Enum for different SyncNotification messages 
//
// @see SyncNotification
//
// @author Till Steinbach
enum SyncNotificationKind {
    // TBD
    SYNC=0;
    // TBD
    ASYNC=1;
}