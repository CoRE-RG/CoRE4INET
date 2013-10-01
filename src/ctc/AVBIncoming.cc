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

#include "AVBIncoming.h"
#include <EtherFrame_m.h>
#include <SRPFrame_m.h>
#include <AVBFrame_m.h>
#include <TTEAVBOutput.h>

namespace TTEthernetModel {

Define_Module(AVBIncoming);

AVBIncoming::AVBIncoming()
{
    hadError = false;
}

void AVBIncoming::initialize()
{
    talker = false;

    for(int i=0; i<gateSize("AVBout"); i++)
    {
        PortReservation[i] = calcPortUtilisation(i);
        AVBPortReservation[i] = 0;
        WATCH_LIST(ListenerGates[i]);
    }
    WATCH_MAP(TalkerAddresses);
    WATCH_MAP(StreamBandwith);
    WATCH_MAP(PortReservation);
    WATCH_MAP(AVBPortReservation);
    WATCH_MAP(PortBandwith);

    EtherFrame *outFrame = new EtherFrame("MAC Register", IEEE802CTRL_DATA);
    send(outFrame, "SRPout");
}

void AVBIncoming::handleMessage(cMessage* msg)
{
    if(msg->arrivedOn("in"))
    {
        AVBFrame *inFrame = ((AVBFrame*)msg);

        if(gateSize("AVBout") > 1)
        {
            for(int i=0; i<gateSize("AVBout"); i++)
            {
                for(std::list<unsigned long>::iterator sid = ListenerGates[i].begin(); sid != ListenerGates[i].end(); sid++)
                {
                    if(*sid == inFrame->getStreamID())
                    {
                        sendDelayed(inFrame->dup(), SimTime(getParentModule()->par("hardware_delay").doubleValue()), gate("AVBout", i));
                    }
                }
            }
            delete inFrame;
        }
        else
        {
            sendDelayed(inFrame, SimTime(getParentModule()->par("hardware_delay").doubleValue()), gate("AVBout", 0));
        }
    }
    else if(msg->arrivedOn("SRPin"))
    {
        SRPFrame *inFrame = ((SRPFrame*)msg);
        std::string srpType = inFrame->getName();
        bubble(inFrame->getName());
        if(srpType.compare("Talker Advertise") == 0)
        {
            TalkerAddresses[inFrame->getStreamID()] = inFrame->getSrc();
            StreamBandwith[inFrame->getStreamID()] = calcBandwith(inFrame->getMaxFrameSize(), inFrame->getMaxIntervalFrames());
            delete msg;
        }
        else if(srpType.compare("Listener Ready") == 0 || srpType.compare("Listener Ready Failed") == 0)
        {
            inFrame->setDest(TalkerAddresses[inFrame->getStreamID()]);
            int portIndex = inFrame->getPortIndex();

            bool saveSIDinGate = true;
            for(std::list<unsigned long>::iterator sid = ListenerGates[portIndex].begin(); sid != ListenerGates[portIndex].end(); sid++)
            {
                if(*sid == inFrame->getStreamID())
                {
                    saveSIDinGate = false;
                }
            }
            if(saveSIDinGate)
            {
                if( ((PortBandwith[portIndex] - PortReservation[portIndex]) - (PortBandwith[portIndex] * 0.25)) >= StreamBandwith[inFrame->getStreamID()] )
                {
                    ListenerGates[portIndex].push_back(inFrame->getStreamID());
                    PortReservation[portIndex] += StreamBandwith[inFrame->getStreamID()];
                    AVBPortReservation[portIndex] += StreamBandwith[inFrame->getStreamID()];
                    StreamIsForwarding[inFrame->getStreamID()] = true;
                    send(inFrame, "SRPout");
                }
                else
                {
                    if(StreamIsForwarding[inFrame->getStreamID()])
                        inFrame->setName("Listener Ready Failed");
                    else
                        inFrame->setName("Listener Failed");
                    send(inFrame, "SRPout");
                }

            }
            else
            {
                send(inFrame, "SRPout");
            }
        }
        else if(srpType.compare("Listener Failed") == 0)
        {
            inFrame->setDest(TalkerAddresses[inFrame->getStreamID()]);

            send(inFrame, "SRPout");
        }
        else{
            delete msg;
        }
    }
    else
    {
        delete msg;
    }
}

int AVBIncoming::calcPortUtilisation(int port)
{
    TTEAVBOutput *shaper = (TTEAVBOutput*) getParentModule()->getSubmodule("phy",port)->getSubmodule("shaper");
    cGate *physOutGate = getParentModule()->getSubmodule("phy", port)->getSubmodule("mac")->gate("phys$o");
    cChannel *avbChannel = physOutGate->findTransmissionChannel();
    PortBandwith[port] = (avbChannel->getNominalDatarate() / 1000000);
    return shaper->par("TTEBandwith").longValue();
}

int AVBIncoming::calcBandwith(int FrameSize, int IntervalFrames)
{
    //interval = 125us
    double sFrameSize = ((double)IntervalFrames) * ((double)FrameSize); // in byte
    double bitFrameSize = sFrameSize * 8; //in bit
    double BitspSecond = bitFrameSize * 8 * 1000; // in per second
    return ceil((BitspSecond / 1024.00) / 1024.00 ); //in Mbit/s
}

int AVBIncoming::getAVBPortReservation(int port)
{
    return AVBPortReservation[port];
}

void AVBIncoming::setAVBPortReservation(int port, int reservation)
{
    AVBPortReservation[port] = reservation;
}

int AVBIncoming::getPortBandwith(int port)
{
    return PortBandwith[port];
}

bool AVBIncoming::getForwarding()
{
    return  ( (gateSize("AVBout") > 1) || talker);
}

} /* namespace TTEthernetModel */
