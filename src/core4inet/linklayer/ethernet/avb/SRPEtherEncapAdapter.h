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

#ifndef CORE4INET_SRPETHERENCAPADAPTER_H_
#define CORE4INET_SRPETHERENCAPADAPTER_H_

#include <omnetpp.h>
//Auto-generated Messages
#include "core4inet/linklayer/contract/ExtendedIeee802Ctrl_m.h"
#include "core4inet/linklayer/ethernet/avb/SRPFrame_m.h"

namespace CoRE4INET {

using namespace omnetpp;

class SRPEtherEncapAdapter : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    size_t portCount;
};

} //namespace

#endif
