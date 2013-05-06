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
//#include "Ieee802Ctrl_m.h"

//#define ETHERAPP_BUFFER_SAP  0xe0

namespace TTEthernetModel {

Define_Module(AVBIncoming);

AVBIncoming::AVBIncoming()
{
    hadError = false;
}

void AVBIncoming::initialize()
{
    WATCH_MAP(TalkerAddresses);
    //WATCH_MAP(ListenerGates);

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
        }
        else
        {
            if(talker)
                sendDelayed(inFrame, SimTime(getParentModule()->par("hardware_delay").doubleValue()), gate("AVBout", 0));
            else
                delete inFrame;
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
        }

        if(srpType.compare("Listener Ready") == 0)
        {
            inFrame->setDest(TalkerAddresses[inFrame->getStreamID()]);
            int portIndex = inFrame->getPortIndex();

            bool saveStreamID = true;
            for(std::list<unsigned long>::iterator sid = ListenerGates[portIndex].begin(); sid != ListenerGates[portIndex].end(); sid++)
            {
                if(*sid == inFrame->getStreamID())
                {
                    saveStreamID = false;
                }
            }
            if(saveStreamID)
            {
                ListenerGates[portIndex].push_back(inFrame->getStreamID());
            }

            send(inFrame, "SRPout");
        }
    }
    else
    {
        delete msg;
    }
}

} /* namespace TTEthernetModel */
