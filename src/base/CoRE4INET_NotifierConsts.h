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

#ifndef __CORE4INET_NOTIFIERCONSTS_H_
#define __CORE4INET_NOTIFIERCONSTS_H_

#include "clistener.h"

namespace CoRE4INET {

#ifdef WITH_AS6802_COMMON
//Notification for changes in the synchronization state
extern simsignal_t NF_SYNC_STATE_CHANGE; //Sync
#endif

#ifdef WITH_AVB_COMMON
//Notifications for talker and listener management
extern simsignal_t NF_AVB_TALKER_REGISTERED; //emitted when a talker registers
extern simsignal_t NF_AVB_TALKER_UPDATED; //signal emitted when a talker updates
extern simsignal_t NF_AVB_LISTENER_REGISTERED; //signal emitted when a listener registers
extern simsignal_t NF_AVB_LISTENER_UPDATED; //signal emitted when a listener updates
extern simsignal_t NF_AVB_LISTENER_UNREGISTERED; //signal emitted when a listener unregisters
extern simsignal_t NF_AVB_LISTENER_REGISTRATION_TIMEOUT; //signal emitted when a listeners registration failed
#endif

}

#endif /* __CORE4INET_NOTIFIERCONSTS_H_ */
