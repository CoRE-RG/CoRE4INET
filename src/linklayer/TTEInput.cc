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
#include "TTEScheduler.h"

#include "Buffer.h"

#include <iostream>

using namespace TTEthernetModel;

Define_Module( TTEInput);

simsignal_t TTEInput::ctDroppedSignal = SIMSIGNAL_NULL;

TTEInput::TTEInput(){
    hadError=false;
}

void TTEInput::initialize()
{
    ctDroppedSignal = registerSignal("ctDropped");
}

//void TTEInput::addIncoming(uint16 ctID, Incoming *incoming)
//{
//    incomings[ctID].push_back(incoming);
//}

void TTEInput::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        EtherFrame *frame = (EtherFrame*) msg;

        int i = msg->findPar("received");
        cMsgPar* par;
        if( i >=0 )
            par = &msg->par(i);
        else
            par = &msg->addPar("received");
        par->setLongValue(((TTEScheduler*)getParentModule()->getParentModule()->getSubmodule("tteScheduler"))->getTicks());

        i = msg->findPar("received_total");
        if( i >=0 )
            par = &msg->par(i);
        else
            par = &msg->addPar("received_total");
        par->setLongValue(((TTEScheduler*)getParentModule()->getParentModule()->getSubmodule("tteScheduler"))->getTotalTicks());


        i = msg->findPar("received_port");
        if( i >=0 )
            par = &msg->par(i);
        else
            par = &msg->addPar("received_port");
        par->setLongValue(getParentModule()->getIndex());

        //Auf CTCs verteilen oder BE traffic
        if (isCT(frame))
        {
            std::map<uint16_t, std::list<Incoming *> >::iterator incomingList = incomings.find(getCTID(frame));
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
                emit(ctDroppedSignal, 1);
                hadError=true;
                if(ev.isGUI()){
                    bubble("No matching buffer configured");
                    getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                    getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 0, "status/excl3");
                    getParentModule()->getParentModule()->getDisplayString().setTagArg("tt", 0, "WARNING: Input configuration problem - No matching buffer configured");
                }
                delete frame;
            }
        }
        //Sonst BE
        else
        {
            if(promiscuous || frame->getDest().isMulticast()){
                send(msg, "out");
            }
            else{
                MACAddress address;
                address.setAddress(frame->getArrivalGate()->getPathStartGate()->getOwnerModule()->par("address"));
                if(frame->getDest().equals(address)){
                    send(msg, "out");
                }
                else{
                    delete msg;
                }
            }
        }
    }
}

void TTEInput::handleParameterChange(const char* parname){
    ctMask = (uint32_t)par("ct_mask").longValue();
    ctMarker = (uint32_t)par("ct_marker").longValue();
    promiscuous = par("promiscuous").boolValue();

    incomings.clear();

    std::string incomingsString = par("incomings").stdstringValue();
    std::vector<std::string> incomingPaths;
    split(incomingsString,',',incomingPaths);
    for(std::vector<std::string>::iterator incomingPath = incomingPaths.begin();
            incomingPath!=incomingPaths.end();incomingPath++){
        cModule* module = simulation.getModuleByPath((*incomingPath).c_str());
        if(module){
            Incoming *incoming = dynamic_cast<Incoming*> (module);
            if(incoming){
                Buffer *buffer = dynamic_cast<Buffer*> (incoming->gate("out")->getPathEndGate()->getOwner());
                if(buffer && buffer->hasPar("ct_id")){
                    incomings[buffer->par("ct_id").longValue()].push_back(incoming);
                }
            }
        }
        else{
            if(ev.isGUI()){
                ev<<"Configuration problem: Module "<<(*incomingPath)<<" could not be resolved or is no Incoming CTC Module, or module is not connected to a buffer!"<<endl;
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getDisplayString().setTagArg("tt", 0, "WARNING: Configuration Problem Input Buffers!");
            }
        }
    }
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

uint16_t TTEInput::getCTID(EtherFrame *frame)
{
    unsigned char macBytes[6];
    frame->getDest().getAddressBytes(macBytes);
    return (macBytes[4] << 8) | macBytes[5];
}
