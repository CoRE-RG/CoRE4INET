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

#ifndef CORE4INET_IEEE8021QCIINPUT_H_
#define CORE4INET_IEEE8021QCIINPUT_H_

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/linklayer/filtering/IEEE8021Qci/filter/IEEE8021QciFilter.h"
//INET Auto-generated Messages
#include "inet/linklayer/ethernet/EtherFrame_m.h"

namespace CoRE4INET {

/**
 * @brief Class representing the IEEE 802.1Qci input module
 *
 * @author Philipp Meyer
 */
class IEEE8021QciInput : public cSimpleModule
{
  protected:
    /**
     * Signal that is emitted every time a frame is dropped.
     */
    static simsignal_t frameDroppedSignal;

  private:
    /**
     * @brief Caches pointers to stream filters contained in the IEEE 802.1Qci filter module
     */
    std::vector<IEEE8021QciFilter*> streamFilters;
    /**
     * @brief Store if all frames without filter match are dropped
     */
    bool isWhiteList;

  protected:
    /**
     * @brief Initializes the module
     */
    virtual void initialize();
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char *parname);
    /**
     * @brief Receives messages from higher layer and looks up if a stream filter is requesting it
     *
     * @param msg the incoming message
     */
    virtual void handleMessage(cMessage *msg);
};

} //namespace

#endif
