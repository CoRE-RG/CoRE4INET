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

#include "CoRE4INET_AVBIncoming.h"
#include "EtherFrame_m.h"
#include "CoRE4INET_BaseShaper.h"

#include "CoRE4INET_SRPTable.h"

#include "CoRE4INET_customWatch.h"

namespace CoRE4INET {

Define_Module(AVBIncoming);

AVBIncoming::AVBIncoming()
{
    hadError = false;
}

void AVBIncoming::initialize()
{
}

void AVBIncoming::handleMessage(cMessage* msg)
{
    if (msg->arrivedOn("in"))
    {
        EtherFrame *inFrame = check_and_cast<EtherFrame*>(msg);

        SRPTable *srptable = check_and_cast<SRPTable*>(getParentModule()->getSubmodule("srpTable"));
        //TODO: Minor enable VLANs
        std::list<cModule*> listeners = srptable->getListenersForTalkerAddress(inFrame->getDest(), 0);

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

} /* namespace CoRE4INET */
