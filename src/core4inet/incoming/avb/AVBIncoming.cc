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

#include "core4inet/incoming/avb/AVBIncoming.h"

//Std
#include <string>
using namespace std;

//CoRE4INET auto-generated
#include "core4inet/linklayer/ethernet/avb/AVBFrame_m.h"

//INET
#include "inet/common/ModuleAccess.h"

namespace CoRE4INET {

Define_Module(AVBIncoming);

AVBIncoming::AVBIncoming()
{
    this->srptable = nullptr;
}

void AVBIncoming::initialize()
{
    this->srptable = inet::getModuleFromPar<SRPTable>(par("srpTable"), this, true);
    if(!srptable){
        throw cRuntimeError("Cannot find module srpTable in node. srpTable is required");
    }
}

void AVBIncoming::handleMessage(cMessage* msg)
{
    if (msg && msg->arrivedOn("in"))
    {
        if (AVBFrame *inFrame = dynamic_cast<AVBFrame*>(msg))
        {
            std::list<cModule*> listeners = srptable->getListenersForTalkerAddress(inFrame->getDest(),
                    inFrame->getVID());
            SR_CLASS srClass = srptable->getSrClassForTalkerAddress(inFrame->getDest(), inFrame->getVID());
            if (listeners.empty())
            {
                emit(droppedSignal, inFrame);
            }
            else
            {
                for (std::list<cModule*>::const_iterator listener = listeners.begin(); listener != listeners.end();
                        ++listener)
                {
                    if (strcmp((*listener)->getName(), "phy") == 0)
                    {
                        string outputStr;
                        if (srClass == SR_CLASS::A)
                            outputStr = "AVBAout";
                        else if (srClass == SR_CLASS::B)
                            outputStr = "AVBBout";
                        sendDelayed(inFrame->dup(), getHardwareDelay(),
                                gate(outputStr.c_str(), (*listener)->getIndex()));
                        emit(rxPkSignal, inFrame);
                    }
                    else
                    {
                        if ((*listener)->hasGate("AVBin"))
                        {
                            sendDirect(inFrame->dup(), (*listener)->gate("AVBin"));
                            emit(rxPkSignal, inFrame);
                        }
                    }
                }
            }
            delete inFrame;
        }
        else
        {
            throw cRuntimeError("Received non-AVBFrame frame");
        }
    }
    else
    {
        delete msg;
    }
}

} /* namespace CoRE4INET */
