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

#ifndef __CORE4INET_CREDITBASEDSHAPER_H_
#define __CORE4INET_CREDITBASEDSHAPER_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/utilities/classes/Timed.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * @author Philipp Meyer
 */
class CreditBasedShaper : public virtual Timed, cListener
{
  protected:
    /**
     * Signal that is emitted every time the credit is recalculated.
     */
    static simsignal_t creditSignal;

  private:
    /**
     * @brief Current credit of the CBS
     */
    int credit;

  public:
    /**
     * @brief Constructor
     */
    CreditBasedShaper();

  protected:
    virtual void initialize();
    /**
     * @brief Indicates a parameter has changed.
     *
     * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
     */
    virtual void handleParameterChange(const char* parname);
    virtual void handleMessage(cMessage *msg);
    /**
     * @brief Receives signals from mac for CBS calculations and state.
     */
    void receiveSignal(cComponent *source, simsignal_t signalID, long l, cObject *details) override;
};

} //namespace

#endif
