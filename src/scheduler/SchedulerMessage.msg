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
// abstract base message for TTEScheduler.
//
// @see TTEScheduler
//
// @author Till Steinbach
message SchedulerMessage {
}

//
// Message used for events of TTEScheduler with SchedulerMessageKind = NEW_CYCLE
//
// @see SchedulerMessageKind
//
// @author Till Steinbach
message SchedulerEvent extends SchedulerMessage {
    @customize(true);
}

//
// Enum for different SchedulerEvent messages 
//
// @see SchedulerEvent
//
// @author Till Steinbach
enum SchedulerMessageKind {
    // Event that signals the beginning of a new cycle
    NEW_CYCLE=0;
    // Event with a specified action time
    ACTION_TIME_EVENT=1;
    // Event that is triggered after a specified amount of time
    TIMER_EVENT=2;
}