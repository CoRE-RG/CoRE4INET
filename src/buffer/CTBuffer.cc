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

#include "Buffer.h"
#include "CTBuffer.h"
#include "TTE4INETDefs.h"
#include "CTFrame.h"

#include "HelperFunctions.h"

using namespace TTEthernetModel;

Define_Module( CTBuffer);

CTBuffer::~CTBuffer(){
}

 void CTBuffer::putFrame(EtherFrame* frame){
    int priority = par("priority").longValue();
    if(frame && priority>=0){
        frame->setSchedulingPriority(priority);
    }
    enqueue(frame);
}

void CTBuffer::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        CTFrame *ctframe = dynamic_cast<CTFrame *>(msg);
        //Try to correct destination mac
        if(ctframe != NULL){
            if(ctframe->getDest().isUnspecified()){
                ctframe->setCtID(ctId);
                ctframe->setCtMarker(ctMarker & ctMask);
            }
            else if(ctframe->getCtMarker()==0){
                ctframe->setCtMarker(ctMarker & ctMask);
            }
        }
        Buffer::handleMessage(msg);
    }
}

void CTBuffer::handleParameterChange(const char* parname){
    ctMask = (unsigned long)par("ct_mask").longValue();
    ctMarker = (unsigned long)par("ct_marker").longValue();
    ctId = (unsigned long)par("ct_id").longValue();

    Buffer::handleParameterChange(parname);
}
