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

#include "TTEInput.h"

#include <iostream>

using namespace TTEthernetModel;

Define_Module( TTEInput);

simsignal_t TTEInput::ctDroppedSignal = SIMSIGNAL_NULL;

void TTEInput::initialize()
{
    ctDroppedSignal = registerSignal("ctDropped");
}

void TTEInput::addIncoming(uint16 ctID, Incoming *incoming)
{
    incomings[ctID].push_back(incoming);
}

void TTEInput::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        EtherFrame *frame = (EtherFrame*) msg;
        //Auf CTCs verteilen oder BE traffic
        if (isCT(frame))
        {
            std::map<uint16, std::list<Incoming *> >::iterator incomingList = incomings.find(getCTID(frame));
            if (incomingList != incomings.end())
            {
                //Send to all CTCs for the CT-ID
                for (std::list<Incoming*>::iterator incoming = incomingList->second.begin(); incoming
                        != incomingList->second.end(); incoming++)
                {
                    sendDirect(frame->dup(), (*incoming)->gate("in"));
                }
                delete frame;
            }
            else
            {
                ev << "No incoming traffic allowed for CT ID " << getCTID(frame) << endl;
                bubble("Frame not allowed here!");
                emit(ctDroppedSignal, 1);
                delete frame;
            }
        }
        //Sonst BE
        else
        {
            send(msg, "out");
        }
    }
}

void TTEInput::handleParameterChange(const char* parname){
    ctMask = (unsigned int)par("ct_mask").longValue();
    ctMarker = (unsigned int)par("ct_marker").longValue();
}

bool TTEInput::isCT(EtherFrame *frame)
{
    unsigned char macBytes[6];
    frame->getDest().getAddressBytes(macBytes);
    //Check for ct
    if ((((macBytes[0] << 24) | (macBytes[1] << 16) | (macBytes[2] << 8) | (macBytes[3])) & ctMask) == (ctMarker
            & ctMask))
    {
        return true;
    }
    //TODO More checking ?
    return false;
}

uint16 TTEInput::getCTID(EtherFrame *frame)
{
    unsigned char macBytes[6];
    frame->getDest().getAddressBytes(macBytes);
    return (macBytes[4] << 8) | macBytes[5];
}
