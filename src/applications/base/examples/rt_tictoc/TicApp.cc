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

#include "TicApp.h"
#include "TicToc_m.h"
#include "TTEScheduler.h"
#include "TTFrame_m.h"
#include "RCFrame_m.h"

namespace TTEthernetModel {

Define_Module(TicApp);

simsignal_t TicApp::rxPkSignal = SIMSIGNAL_NULL;
simsignal_t TicApp::roundtripSignal = SIMSIGNAL_NULL;

void TicApp::initialize()
{
    TTEApplicationBase::initialize();

    rxPkSignal = registerSignal("rxPk");
    roundtripSignal = registerSignal("roundtrip");

    TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("scheduler");
    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
    event->setAction_time(par("action_time").longValue());
    event->setDestinationGate(gate("schedulerIn"));
    tteScheduler->registerEvent(event);
}

void TicApp::handleMessage(cMessage *msg)
{
    TTEApplicationBase::handleMessage(msg);

    if(msg->arrivedOn("schedulerIn")){
        Tic *tic = new Tic();
        tic->setRoundtrip_start(simTime());
        tic->setCount(par("counter").longValue());
        CTFrame *frame = new TTFrame("Tic");
        frame->setCtID(par("ct_id").longValue());
        frame->encapsulate(tic);

        EV << "Sending Tic Message\n";
        std::list<Buffer*> buffer = buffers[frame->getCtID()];
        for(std::list<Buffer*>::iterator buf = buffer.begin();
                               buf!=buffer.end();buf++){
            Incoming* in = (Incoming *)(*buf)->gate("in")->getPathStartGate()->getOwner();
            sendDirect(frame->dup(), in->gate("in"));
        }
        delete frame;

        TTEScheduler *tteScheduler = (TTEScheduler*) getParentModule()->getSubmodule("scheduler");
        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *)msg;
        tteScheduler->registerEvent(event, true);
    }
    else if(msg->arrivedOn("RCin")){
        RCFrame *rcframe = dynamic_cast<RCFrame*>(msg);
        Toc *toc=dynamic_cast<Toc*>(rcframe->decapsulate());
        delete msg;
        bubble(toc->getResponse());
        par("counter").setLongValue(toc->getCount());
        emit(rxPkSignal, 1L);
        emit(roundtripSignal, toc->getRoundtrip_start()-simTime());
        delete toc;
    }
    else{
        delete msg;
    }
}

}
