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

#include "SRPTable.h"

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
}

void AVBIncoming::handleMessage(cMessage* msg)
{
    if (msg->arrivedOn("in"))
    {
        AVBFrame *inFrame = ((AVBFrame*) msg);

        SRPTable *srptable = check_and_cast<SRPTable*>(getParentModule()->getSubmodule("srpTable"));
        std::list<cModule*> listeners = srptable->getListenersForStreamId(inFrame->getStreamID());

        for (std::list<cModule*>::iterator listener = listeners.begin(); listener != listeners.end(); listener++)
        {
            if (strcmp((*listener)->getName(), "phy") == 0)
            {
                sendDelayed(inFrame->dup(), SimTime(getParentModule()->par("hardware_delay").doubleValue()),
                        gate("AVBout", (*listener)->getIndex()));
            }
            else{
                if((*listener)->hasGate("AVBin")){
                    sendDirect(inFrame->dup(), (*listener)->gate("AVBin"));
                }
            }
        }
        delete inFrame;
    }
    else
    {
        delete msg;
    }
}

bool AVBIncoming::getForwarding()
{
    return ((gateSize("AVBout") > 1) || talker);
}

} /* namespace CoRE4INET */
