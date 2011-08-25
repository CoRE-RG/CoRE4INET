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

#ifndef __TTETHERNETMODELV2_TTEAPPLICATIONBASE_H_
#define __TTETHERNETMODELV2_TTEAPPLICATIONBASE_H_

#include <omnetpp.h>
#include "Incoming.h"
#include "Callback.h"
#include "Buffer.h"

namespace TTEthernetModel {

/**
 * TODO - Generated class
 */
class TTEApplicationBase : public cSimpleModule
{
  protected:
    std::map<uint16, std::list<Incoming*> > incomings;
    std::map<uint16, std::list<Buffer*> > buffers;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    virtual void executeCallback(Callback *cb);
    virtual void addIncoming(uint16 ctID, Incoming *incoming);
    virtual void addBuffer(uint16 ctID, Buffer *buffer);
};

} //namespace

#endif
