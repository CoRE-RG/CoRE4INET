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

#include <omnetpp.h>

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @author Philipp Meyer
 */
class IEEE8021QbvSelection : public cSimpleModule
{
  private:
    unsigned int numPCP;
    size_t framesRequested;

  public:
    /**
     * @brief Constructor
     */
    IEEE8021QbvSelection();

  protected:
    virtual void initialize();
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname);
    virtual void handleMessage(cMessage *msg);

    virtual void reportPacket();
    /**
     * @brief this method is invoked when the underlying mac is idle.
     *
     * When this method is invoked the module sends a new message when there is
     * one. Else it saves the state and sends the message immediately when it is
     * received.
     *
     */
    virtual void requestPacket();

  private:
    cMessage* selectFrame();
};

} //namespace

#endif
