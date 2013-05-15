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

#include "TocApp.h"
#include "TTEScheduler.h"
#include "RCFrame_m.h"

namespace TTEthernetModel {

Define_Module(TocApp);

void TocApp::initialize()
{
    TTEApplicationBase::initialize();
}

void TocApp::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("TTin")){
        delete msg;
        CTFrame *frame = new RCFrame("Toc");
        frame->setCtID(101);

        EV << "Answering Tic Message with Toc Message\n";
        std::list<Buffer*> buffer = buffers[frame->getCtID()];
        for(std::list<Buffer*>::iterator buf = buffer.begin();
                               buf!=buffer.end();buf++){
            Incoming* in = (Incoming *)(*buf)->gate("in")->getPathStartGate()->getOwner();
            sendDirect(frame->dup(), in->gate("in"));
        }
        delete frame;
    }
    else{
        delete msg;
    }
}

}
