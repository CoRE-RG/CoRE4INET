//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "TTEAVBOutput.h"

#include <algorithm>

#include <Buffer.h>
#include <RCBuffer.h>
#include <PCFrame_m.h>
#include <TTEScheduler.h>
#include <TTBufferEmpty_m.h>

#include <HelperFunctions.h>

namespace TTEthernetModel {

Define_Module(TTEAVBOutput);

TTEAVBOutput::TTEAVBOutput() : TTEOutput::TTEOutput()
{
    credit = 0;

    avbQueue.setName("AVB Messages");
}

TTEAVBOutput::~TTEAVBOutput()
{
    avbQueue.clear();
}

void TTEAVBOutput::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("PCFin"))
    {
        if (framesRequested)
        {
            framesRequested--;
            send(msg, gateBaseId("out"));
        }
        else
        {
            pcfQueue.insert(msg);
            notifyListeners();
            emit(pcfQueueLengthSignal, pcfQueue.length());
        }
    }
    else if (msg->arrivedOn("TTin"))
    {
        EV << "There might be a configuration issue (TTBuffer not registered in Output module), or shuffling was enabled for a TTBuffer or a TTFrame was delayed by a PCF" << endl;
        if(ttBuffers.size()>0){
            ttBuffersPos = (++ttBuffersPos % ttBuffers.size());
        }

        //If we have an empty message allow other frame to be sent
        if (dynamic_cast<TTBufferEmpty *> (msg))
        {
            if (framesRequested)
            {
                framesRequested--;
                requestPacket();
            }
            delete msg;
        }
        //Else send frame
        else
        {
            if (framesRequested)
            {
                framesRequested--;
                send(msg, gateBaseId("out"));
            }
            else
            {
                ttQueue.insert(msg);
                notifyListeners();
                emit(ttQueueLengthSignal, ttQueue.length());
            }
        }
    }
    else if(msg->arrivedOn("AVBin"))
    {
        if(framesRequested && isTransmissionAllowed((EtherFrame*)msg))
        {
            send(msg,gateBaseId("out"));
        }
        else
        {
            avbQueue.insert(msg);
        }
    }
    else if (msg->arrivedOn("RCin"))
    {
        if (framesRequested && isTransmissionAllowed((EtherFrame*) msg))
        {
            framesRequested--;

            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*> (msg->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();
            PCFrame *pcf = dynamic_cast<PCFrame*> (msg);
            if(pcf){
                setTransparentClock(pcf);
            }
            send(msg, gateBaseId("out"));
        }
        else
        {
            int priority = msg->getSenderModule()->par("priority").longValue();
            if (priority > 0 && priority < NUM_RC_PRIORITIES)
            {
                rcQueue[priority].insert(msg);
                notifyListeners();
            }
            else
            {
                rcQueue[0].insert(msg);
                notifyListeners();
                ev << "Priority missing!" << endl;
            }
        }
    }
    //Frames arrived on in are best-effort frames
    else if (msg->arrivedOn("in"))
    {
        // If there are framesRequested the MAC layer is currently idle
        if (framesRequested && isTransmissionAllowed((EtherFrame*) msg))
        {
            framesRequested--;
            send(msg, gateBaseId("out"));
        }
        else
        {
            beQueue.insert(msg);
            notifyListeners();
            emit(beQueueLengthSignal, beQueue.length());
        }
    }
}

void TTEAVBOutput::requestPacket()
{
    Enter_Method("requestPacket()");
    //Feed the MAC layer with the next frame
    framesRequested++;

    //TTFrames
    if (!ttQueue.isEmpty())
    {
        framesRequested--;
        cMessage *msg = (cMessage*) ttQueue.pop();
        emit(ttQueueLengthSignal, ttQueue.length());

        //TODO Update buffers:
        if(ttBuffers.size()>0){
            ttBuffersPos = (ttBuffersPos + 1) % ttBuffers.size();
        }

        send(msg, gateBaseId("out"));
        return;
    }

    //AVBFrames
    if(!avbQueue.isEmpty())
    {
        framesRequested--;
        cMessage *msg = (cMessage*) avbQueue.pop();
        send(msg, gateBaseId("out"));
        return;
    }

    //RCFrames
    for (int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        if (!rcQueue[i].isEmpty() && isTransmissionAllowed((EtherFrame*) rcQueue[i].front()))
        {
            framesRequested--;
            EtherFrame *message = (EtherFrame*) rcQueue[i].pop();
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*> (message->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();

            PCFrame *pcf = dynamic_cast<PCFrame*> (message);
            if(pcf){
                setTransparentClock(pcf);
            }
            send(message, gateBaseId("out"));
            return;
        }
    }
    //BEFrames
    if (!beQueue.isEmpty() && isTransmissionAllowed((EtherFrame*) beQueue.front()))
    {
        framesRequested--;
        cMessage* message = (cMessage*) beQueue.pop();
        send(message, gateBaseId("out"));
        emit(beQueueLengthSignal, beQueue.length());
        return;
    }
}

} /* namespace TTEthernetModel */
