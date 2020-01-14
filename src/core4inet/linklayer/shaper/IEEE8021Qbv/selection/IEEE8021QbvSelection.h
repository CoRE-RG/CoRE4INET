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

#ifndef CORE4INET_IEEE8021QBVSELECTION_H_
#define CORE4INET_IEEE8021QBVSELECTION_H_

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
  protected:
    /**
     * @brief Signals that are emitted when a frame is chosen for forwarding.
     */
    std::vector<simsignal_t> qPcpPkSignals;
    /**
     * @brief Signals that are emitted when a frame is chosen for forwarding.
     */
    std::vector<simsignal_t> qPcpPkAgeSignals;

  private:
    /**
     * @brief Number of priorities.
     */
    unsigned int numPCP;
    /**
     * @brief Counts number of frames per pcp.
     */
    std::vector<unsigned long> numFrames;
    /**
     * @brief Counts number of bytes per pcp.
     */
    std::vector<unsigned long> numBytes;

  public:
    /**
     * @brief Constructor
     */
    IEEE8021QbvSelection();

  protected:
    /**
     * @brief Initializes the module
     *
     * @param stage The stages. Module initializes when stage==0
     */
    virtual void initialize(int stage) override;
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname) override;
    /**
     * @brief Handles incoming messages and forwards them to the MAC module.
     *
     * @param msg incoming inet::EtherFrame
     */
    virtual void handleMessage(cMessage *msg) override;
    /**
     * @brief handles signals containing qbv state changes
     *
     * @param src src module
     * @param id signal id
     * @param l the related state
     */
    virtual void receiveSignal(cComponent *src, simsignal_t id, long l, cObject *details) override;
    /**
     * @brief this method is invoked when the underlying mac is idle.
     *
     * When this method is invoked the module sends a new message when there is
     * one. Else it saves the state and sends the message immediately when it is
     * received.
     */
    virtual void requestPacket() override;
    /**
     * @brief Called at the end of simulation. Records frames + bytes per second results.
     */
    virtual void finish() override;

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
