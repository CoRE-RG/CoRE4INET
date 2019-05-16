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

#ifndef __CORE4INET_IEEE8021QBVGATECONTROLLIST_H_
#define __CORE4INET_IEEE8021QBVGATECONTROLLIST_H_

//std
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/utilities/classes/Timed.h"

using namespace omnetpp;
using namespace std;

namespace CoRE4INET {

/**
 * @author Philipp Meyer
 */
class IEEE8021QbvGateControlList : public virtual Timed
{
  private:
    unsigned int numGates;
    /**
     * @brief Length of one tick
     */
    simtime_t tick;
    vector<pair<vector<string>, double>> controlList;
    vector<pair<vector<string>, double>>::iterator controlElement;

  protected:
    virtual void initialize(int stage);
    virtual int numInitStages() const;
    virtual void handleParameterChange(const char* parname);
    virtual void handleMessage(cMessage *msg);

  private:
    void scheduleCurrentControlElementTime();
    void propagteCurrentControlElement();
    void switchToNextControlElement();
};

} //namespace

#endif
