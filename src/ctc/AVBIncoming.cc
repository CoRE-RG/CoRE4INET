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
//    EtherFrame *outFrame = new EtherFrame("MAC Register", IEEE802CTRL_DATA);
//    outFrame->setSrc( *(new MACAddress("FFFFFFFFFFFF")) );
//    send(outFrame, "SRPout");

//    Ieee802Ctrl *etherctrl = new Ieee802Ctrl();
//    etherctrl->setDsap(ETHERAPP_BUFFER_SAP);
//    etherctrl->setSrc(*(new MACAddress("FFFFFFFFFFFF")));
//    cMessage *msg = new cMessage("register_DSAP", IEEE802CTRL_REGISTER_DSAP);
//    msg->setControlInfo(etherctrl);
//
//    send(msg, "SRPout");
}

void AVBIncoming::handleMessage(cMessage* msg)
{
    if(msg->arrivedOn("in"))
    {
        sendDelayed(msg,SimTime(getParentModule()->par("hardware_delay").doubleValue()),"out"); //temp
    }
    else if(msg->arrivedOn("SRPin"))
    {
        //SRPFrame *inFrame = ((SRPFrame*)((EtherFrameWithLLC*)msg)->decapsulate());

        std::string msgClass = msg->getClassName();
        if(msgClass.compare("TTEthernetModel::SRPFrame") == 0)
        {
            SRPFrame *inFrame = ((SRPFrame*)msg);
            std::string srpType = inFrame->getName();
            bubble(inFrame->getName());
            if(srpType.compare("Talker Advertise") == 0)
            {
                SRPFrame *outFrame = new SRPFrame("SRP Test Frame", IEEE802CTRL_DATA);
                outFrame->setDest(inFrame->getSrc());
                send(outFrame, this->gate("SRPout"));
            }
        }
        else
        {
            delete msg;
        }
    }
}

} /* namespace TTEthernetModel */
