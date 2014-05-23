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

#include "CoRE4INET_TicApp.h"
#include "TicToc_m.h"
#include "TTFrame_m.h"
#include "RCFrame_m.h"
#include "CoRE4INET_Incoming.h"

namespace CoRE4INET {

Define_Module(TicApp);

simsignal_t TicApp::rxPkSignal = SIMSIGNAL_NULL;
simsignal_t TicApp::roundtripSignal = SIMSIGNAL_NULL;

void TicApp::initialize()
{
    ApplicationBase::initialize();
    Scheduled::initialize();

    rxPkSignal = registerSignal("rxPk");
    roundtripSignal = registerSignal("roundtrip");

    SchedulerActionTimeEvent *event = new SchedulerActionTimeEvent("API Scheduler Task Event", ACTION_TIME_EVENT);
    event->setAction_time((uint32_t) par("action_time").longValue());
    event->setDestinationGate(gate("schedulerIn"));
    period->registerEvent(event);
}

void TicApp::handleMessage(cMessage *msg)
{
    ApplicationBase::handleMessage(msg);

    if (msg->arrivedOn("schedulerIn"))
    {
        Tic *tic = new Tic();
        tic->setRoundtrip_start(simTime());
        tic->setCount((unsigned int) par("counter").longValue());
        CTFrame *frame = new TTFrame("Tic");
        frame->setCtID((uint16_t) par("ct_id").longValue());
        frame->encapsulate(tic);

        EV_DETAIL << "Sending Tic Message\n";
        std::list<CTBuffer*> buffer = ctbuffers[frame->getCtID()];
        for (std::list<CTBuffer*>::iterator buf = buffer.begin(); buf != buffer.end(); buf++)
        {
            Incoming* in = dynamic_cast<Incoming *>((*buf)->gate("in")->getPathStartGate()->getOwner());
            sendDirect(frame->dup(), in->gate("in"));
        }
        delete frame;

        SchedulerActionTimeEvent *event = (SchedulerActionTimeEvent *) msg;
        event->setNext_cycle(true);
        period->registerEvent(event);
    }
    else if (msg->arrivedOn("RCin"))
    {
        RCFrame *rcframe = dynamic_cast<RCFrame*>(msg);
        Toc *toc = dynamic_cast<Toc*>(rcframe->decapsulate());
        bubble(toc->getResponse());
        par("counter").setLongValue((long) toc->getCount());
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

}
