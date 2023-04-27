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

#ifndef CORE4INET_IEEE8021QCIGATECONTROLLIST_H_
#define CORE4INET_IEEE8021QCIGATECONTROLLIST_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/linklayer/shaper/IEEE8021Qbv/gate/IEEE8021QbvGateControlList.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @brief IEEE 802.1Qci gate control list implementation.
 *
 * Stores control list and propagates its states over time.
 *
 * @ingroup IEEE8021Qci
 *
 * @author Philipp Meyer
 */
class IEEE8021QciGateControlList : public virtual IEEE8021QbvGateControlList
{
  protected:
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname);
    /**
     * @brief Propagate the gate states of the current control element.
     */
    virtual void propagateGateControlElement(vector<string> gateStates);
};

} //namespace

#endif
