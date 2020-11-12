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

#ifndef __CORE4INET_REORDERING_H_
#define __CORE4INET_REORDERING_H_

//std
#include <queue>
#include <deque>
//OMNeT++
#include <omnetpp.h>
//CoRE4INET
#include "core4inet/linklayer/shaper/IEEE8021Qbv/selection/IEEE8021QbvSelection.h"

using namespace omnetpp;

namespace CoRE4INET {

/**
 * TODO - Generated class
 */
class Reordering : public virtual IEEE8021QbvSelection
{
  private:
    std::queue<cMessage*> outMessages;
    std::deque<cMessage*> savedMessages;

  public:
    Reordering();
    virtual ~Reordering();

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void selectFrame() override;

  private:
    bool reorder();
};

} //namespace

#endif
