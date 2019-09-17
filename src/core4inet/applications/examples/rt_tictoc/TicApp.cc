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

#include "core4inet/applications/examples/rt_tictoc/TicApp.h"

//CoRE4INET
#include "core4inet/incoming/base/Incoming.h"
//Auto-generated Messages
#include "core4inet/applications/examples/rt_tictoc/TicToc_m.h"
#include "core4inet/linklayer/ethernet/AS6802/TTFrame_m.h"
#include "core4inet/linklayer/ethernet/AS6802/RCFrame_m.h"


namespace CoRE4INET {

Define_Module(TicApp);

simsignal_t TicApp::rxPkSignal = registerSignal("rxPk");
simsignal_t TicApp::roundtripSignal = registerSignal("roundtrip");

void TicApp::initialize()
{
    ApplicationBase::initialize();
    Scheduled::initialize();

    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
    event->setAction_time(par("action_time"));
    event->setDestinationGate(gate("schedulerIn"));
    getPeriod()->registerEvent(event);
}

void TicApp::handleMessage(cMessage *msg)
{
    ApplicationBase::handleMessage(msg);

    if (msg->arrivedOn("schedulerIn"))
    {
        Tic *tic = new Tic();
        tic->setTimestamp();
        tic->setRoundtrip_start(simTime());
        tic->setCount(par("counter"));
        CTFrame *frame = new TTFrame("Tic");
        frame->setTimestamp();
        frame->setCtID(par("ct_id"));
        frame->encapsulate(tic);

        EV_DETAIL << "Sending Tic Message\n";
        std::list<CTBuffer*> buffer = ctbuffers[frame->getCtID()];
        for (std::list<CTBuffer*>::const_iterator buf = buffer.begin(); buf != buffer.end(); ++buf)
        {
            Incoming* in = dynamic_cast<Incoming *>((*buf)->gate("in")->getPathStartGate()->getOwner());
            sendDirect(frame->dup(), in->gate("in"));
        }
        delete frame;

        if(SchedulerActionTimeEvent *event = dynamic_cast<SchedulerActionTimeEvent *>(msg))
        {
            event->setNext_cycle(true);
            getPeriod()->registerEvent(event);
        }
        else
        {
            throw cRuntimeError("Received wrong Message on schedulerIn");
        }
    }
    else if (msg->arrivedOn("RCin"))
    {
        RCFrame *rcframe = dynamic_cast<RCFrame*>(msg);
        Toc *toc = dynamic_cast<Toc*>(rcframe->decapsulate());
        bubble(toc->getResponse());
        par("counter").setIntValue(static_cast<long>(toc->getCount()));
        emit(rxPkSignal, rcframe);
        emit(roundtripSignal, toc->getRoundtrip_start() - simTime());
        delete toc;
        delete msg;
    }
    else
    {
        delete msg;
    }
}

void TicApp::handleParameterChange(const char* parname){
    CTApplicationBase::handleParameterChange(parname);
    Scheduled::handleParameterChange(parname);
}

}
