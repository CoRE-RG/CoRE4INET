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
#include <BaseShaper.h>

#include "customWatch.h"

namespace CoRE4INET {

Define_Module(AVBIncoming);

AVBIncoming::AVBIncoming()
{
    hadError = false;
}

void AVBIncoming::initialize()
{
    talker = false;

    for (unsigned int i = 0; i < (unsigned int) gateSize("AVBout"); i++)
    {
        PortReservation[i] = calcPortUtilisation(i);
        AVBPortReservation[i] = 0;
    }
    WATCH_MAP(TalkerAddresses);
    WATCH_MAP(StreamBandwith);
    WATCH_MAP(PortReservation);
    WATCH_MAP(AVBPortReservation);
    WATCH_MAP(PortBandwith);
    WATCH_LISTMAP(ListenerGates);

    EtherFrame *outFrame = new EtherFrame("MAC Register", IEEE802CTRL_DATA);
    send(outFrame, "SRPout");
}

void AVBIncoming::handleMessage(cMessage* msg)
{
    if (msg->arrivedOn("in"))
    {
        AVBFrame *inFrame = ((AVBFrame*) msg);

        //TODO Major: error when gatesize==0? is this case even relevant? better >0 and delete else?
        if (gateSize("AVBout") > 1)
        {
            for (unsigned int i = 0; i < (unsigned int) gateSize("AVBout"); i++)
            {
                for (std::list<unsigned long>::iterator sid = ListenerGates[i].begin(); sid != ListenerGates[i].end();
                        sid++)
                {
                    if (*sid == inFrame->getStreamID())
                    {
                        sendDelayed(inFrame->dup(), SimTime(getParentModule()->par("hardware_delay").doubleValue()),
                                gate("AVBout", (int) i));
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
    else
    {
        delete msg;
    }
}

unsigned int AVBIncoming::calcPortUtilisation(unsigned int port)
{
    BaseShaper *shaper = dynamic_cast<BaseShaper*>(getParentModule()->getSubmodule("phy", (int) port)->getSubmodule(
            "shaper"));
    cGate *physOutGate = getParentModule()->getSubmodule("phy", (int) port)->getSubmodule("mac")->gate("phys$o");
    cChannel *avbChannel = physOutGate->findTransmissionChannel();
    if (avbChannel)
    {
        PortBandwith[port] = (unsigned int) (avbChannel->getNominalDatarate() / 1000000);
    }
    else
    {
        PortBandwith[port] = 0;
    }
    return (unsigned int) shaper->par("TTEBandwith").longValue();
}

unsigned int AVBIncoming::getAVBPortReservation(unsigned int port)
{
    return AVBPortReservation[port];
}

void AVBIncoming::setAVBPortReservation(unsigned int port, unsigned int reservation)
{
    AVBPortReservation[port] = reservation;
}

unsigned int AVBIncoming::getPortBandwith(unsigned int port)
{
    return PortBandwith[port];
}

bool AVBIncoming::getForwarding()
{
    return ((gateSize("AVBout") > 1) || talker);
}

} /* namespace CoRE4INET */
