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

#ifndef __CORE4INET_IEEE8021QBVSELECTION_H_
#define __CORE4INET_IEEE8021QBVSELECTION_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/linklayer/shaper/base/BaseShaper.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @brief IEEE 802.1Qbv transmission selection.
 *
 * @ingroup IEEE8021Qbv
 *
 * @author Philipp Meyer
 */
class IEEE8021QbvSelection : public virtual BaseShaper
{
  private:
    /**
     * @brief Number of priorities.
     */
    unsigned int numPCP;
    /**
     * @brief Number of frames requested by MAC module.
     */
    size_t framesRequested;

  public:
    /**
     * @brief Constructor
     */
    IEEE8021QbvSelection();
    /**
     * @brief Report change to transmission selection.
     *
     * The frame selection process gets triggered.
     */
    virtual void reportChange();

  protected:
    /**
     * @brief Initializes the module.
     */
    virtual void initialize();
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname);
    /**
     * @brief Handles incoming messages and forwards them to the MAC module.
     *
     * @param msg incoming inet::EtherFrame
     */
    virtual void handleMessage(cMessage *msg);
    /**
     * @brief this method is invoked when the underlying mac is idle.
     *
     * When this method is invoked the module sends a new message when there is
     * one. Else it saves the state and sends the message immediately when it is
     * received.
     */
    virtual void requestPacket() override;

  private:
    /**
     * @brief Implements IEEE 802.1Qbv transmission frame selection.
     *
     * For each priority starting with the highest (default 7): If queue is not empty and transmission selection algorithm is open and transmission gate is open frame will be selected.
     */
    void selectFrame();
};

} //namespace

#endif
