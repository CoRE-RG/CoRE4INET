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

#include "core4inet/base/NotifierConsts.h"

namespace CoRE4INET {

simsignal_t NF_SYNC_STATE_CHANGE = cComponent::registerSignal("NF_SYNC_STATE_CHANGE");


#ifdef WITH_AVB_COMMON
simsignal_t NF_AVB_TALKER_REGISTERED = cComponent::registerSignal("NF_AVB_TALKER_REGISTERED");
simsignal_t NF_AVB_TALKER_UPDATED = cComponent::registerSignal("NF_AVB_TALKER_UPDATED");
simsignal_t NF_AVB_LISTENER_REGISTERED = cComponent::registerSignal("NF_AVB_LISTENER_REGISTERED");
simsignal_t NF_AVB_LISTENER_UPDATED = cComponent::registerSignal("NF_AVB_LISTENER_UPDATED");
simsignal_t NF_AVB_LISTENER_UNREGISTERED = cComponent::registerSignal("NF_AVB_LISTENER_UNREGISTERED");
simsignal_t NF_AVB_LISTENER_REGISTRATION_TIMEOUT = cComponent::registerSignal("NF_AVB_LISTENER_REGISTRATION_TIMEOUT");
#endif


#ifdef WITH_IEEE8021QBV_COMMON
simsignal_t NF_QBV_STATE_CHANGED = cComponent::registerSignal("NF_QBV_STATE_CHANGED");
#endif
}
