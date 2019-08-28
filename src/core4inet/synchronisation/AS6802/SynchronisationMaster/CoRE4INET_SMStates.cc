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
/*
 * SMStates.cpp
 *
 *  Created on: Feb 13, 2012
 *      Author: Lazar Todorov
 */
#include "CoRE4INET_SMStates.h"
#include "CoRE4INET_SM.h"
#include <string>
#include "omnetpp.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"
#include "SynchronisationEvents_m.h"

#include "CoRE4INET_CoRE4INETDefs.h"
#include "algorithm"
#include "core4inet/utilities/HelperFunctions.h"
#include "CoRE4INET_TTEScheduler.h"
#include "SchedulerMessageEvents_m.h"
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"

namespace CoRE4INET {
using namespace std;

SM_INIT::SM_INIT(SM *s, FILE *f) {

	outVector = new cOutVector("Name");
	sm = s;
	fp = f;
	counter = 0;

	if (sm->par("read").boolValue()) {

		values = new std::vector<int>(1200000);

		if (NULL != fp) {

			while (!feof(fp)) {

				int num = fscanf(fp, "%d %d", &dummy, &data);
				ASSERT(num==2);
				values->at(counter++) = data;

			} //while

		} else {
			perror("Error opening file");
		}

		counter = 0;

	}

	clock_stack = new map<uint32, pair<uint32, uint64> >;


	//after Power ON  and Initialization READY
	//duration=sm_listen_timeout;
	max_transmission_delay = sm->par("max_transmission_delay");
	duration = sm->par("sm_listen_timeout");
	ownBit = sm->par("bit_index");
	syncDomain = sm->par("syncDomain");
	MembershipAcceptanceRange =
			sm->par("MembershipAcceptanceRange");
	syncPriority = sm->par("syncPriority");

	local_timer = false;
	flood_receive = false;
	closed_window = false;
	round_completed = false;

	local_clock = 0;
	local_sync_membership = 0;
	local_async_membership = 0;
	local_integration_cycle = 0;
	clock_corr = 0;
	stable_cycle_counter = 0;

	//The monitoring intervals are longer than the integration_cycle_duration, requiring two variables
	//local_async_membership_f,  local_async_membership_r
	local_async_membership_f = 0;
	local_async_membership_r = 0;

	event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
	event->setSchedulingPriority(3);
	event->setTimer(duration);
	event->setDestinationGate(sm->gate("schedulerIn"));

	//container for event's representing the permanence pit per frame
	e_container = new multimap<uint64_t, FrameEvent *>;

	tteScheduler = (TTEScheduler*) sm->getParentModule()->getSubmodule(
			"scheduler");

	event1 = new SchedulerActionTimeEvent("smc_async_eval_pit",
			ACTION_TIME_EVENT);

	event1->setAction_time(0);
	event1->setDestinationGate(sm->gate("schedulerIn"));
	event1->setSchedulingPriority(4);

	event2 = new SchedulerActionTimeEvent("smc_sync_eval_pit",
			ACTION_TIME_EVENT);

	event2->setAction_time(sm->par("smc_sync_eval_pit"));
	event2->setDestinationGate(sm->gate("schedulerIn"));
	event2->setSchedulingPriority(4);

	event3 = new SchedulerActionTimeEvent("smc_clock_corr_pit",
			ACTION_TIME_EVENT);

	event3->setAction_time(sm->par("smc_clock_corr_pit"));
	event3->setDestinationGate(sm->gate("schedulerIn"));
	event3->setSchedulingPriority(4);

	//event4 is used to update/increment/ the "local_integration_cycle" value
	event4 = new SchedulerActionTimeEvent("smc_inc_pit", ACTION_TIME_EVENT);
	event4->setAction_time(
			sm->par("smc_scheduled_receive_pit").intValue()
					- sm->par("precision").intValue());
	event4->setDestinationGate(sm->gate("schedulerIn"));
	event4->setSchedulingPriority(3);

	event5 = new SchedulerActionTimeEvent("smc_async_up", ACTION_TIME_EVENT);
	event5->setAction_time(
			(sm->par("int_cycle_duration").intValue()
					- sm->par("acceptance_window").intValue()));
	event5->setDestinationGate(sm->gate("schedulerIn"));
	event5->setSchedulingPriority(4);

	if (sm->par("read").boolValue()) {

		tteScheduler->registerEvent(event3);
		tteScheduler->registerEvent(event4);

		new (this) SM_PSEUDOSYNC();

		return;
	}

	new (this) SM_INTEGRATE();
	return;
}

//nothing to do here
void SM_INIT::reaction(int message) {
}

SM_PSEUDOSYNC::SM_PSEUDOSYNC() {
	ev << "Enter PSEUDOSYNC" << endl;
}

void SM_PSEUDOSYNC::handleMessage(cMessage * message) {

	if (string(message->getName()).compare("smc_clock_corr_pit") == 0) {

		ev << "SM_PSEUDOSYNC clock correction" << endl;

		tteScheduler->clockCorrection(values->at(counter++));

		tteScheduler->registerEvent(event3, true);

		return;

	}

	if (string(message->getName()).compare("smc_inc_pit") == 0) {

		local_integration_cycle = (local_integration_cycle + 1)
				% (sm->par("max_integration_cycles").intValue());

		tteScheduler->registerEvent(event4, true);

		return;
	}

}

SM_INTEGRATE::SM_INTEGRATE() {

	sm->getDisplayString().setTagArg("i", 1, "red");
	sm->bubble("SM_INTEGRATE");
	ev << "current state :: SM_INTEGRATE" << endl;
	//cout<<"Enter->SM_INTEGRATE \n"<<endl;

	//local_timer=false;
	//timer start
	tteScheduler->registerEvent(event);
	//TW(duration); //TO?
	//local_timer=true;

}

void SM_INTEGRATE::handleMessage(cMessage *message) {
//with permanence calculation for all frames



	if (message->arrivedOn("RCin")) {
		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//SM/SC makes all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		ev << "DEBUG: INTEGRATE membership new value" << pf->getMembership_new()
				<< ownBit << endl;
		ev << "DEBUG: INTEGRATE membership new number of SM"
				<< getValue(pf->getMembership_new(), 32) << ownBit << endl;

		if ((pf->getSync_domain() == syncDomain)
				&& (pf->getSync_priority() == syncPriority)) {

			if ((transparentClockToTicks(pf->getTransparent_clock(),
					tteScheduler->par("tick").doubleValue())
					+ (tteScheduler->getTotalTicks()
							- pf->par("received_total").intValue())
					> max_transmission_delay)) {

				ev
						<< "WARNING: INTEGRATE: pkt->getTransparent_clock() > max_transmission_delay "
						<< ownBit << endl;

			}

			//calculate permanence pit

			uint64_t permanence_delay = max_transmission_delay
					- (transparentClockToTicks(pf->getTransparent_clock(),
							tteScheduler->par("tick").doubleValue())
							+ (tteScheduler->getTotalTicks()
									- pf->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			if (pf->getType() == IN_FRAME) {

				if (e_container->find(permanence_pit) != e_container->end()) {

					if (getValue(pf->getMembership_new(), 32)
							> (getValue(
									e_container->find(permanence_pit)->second->getMember(),
									32))) {

						ev << "DEBUG: INTEGRATE REPLACE membership new value"
								<< pf->getMembership_new() << endl;
						ev << "DEBUG: INTEGRATE membership new number of SM "
								<< getValue(pf->getMembership_new(), 32)
								<< endl;

						tteScheduler->unregisterEvent(
								e_container->find(permanence_pit)->second);
						sm->cancelAndDelete(
								e_container->find(permanence_pit)->second);
						e_container->erase(permanence_pit);

						FrameEvent *f_event = new FrameEvent("IN_FRAME",
								TIMER_EVENT);
						f_event->setReceivedPort(
								pf->par("received_port"));
						f_event->setMember(pf->getMembership_new());
						f_event->setPcfType(pf->getType());

						f_event->setTimer(permanence_delay);
						f_event->setDestinationGate(sm->gate("schedulerIn"));
						f_event->setIntegrationCycle(
								pf->getIntegration_cycle());
						f_event->setSchedulingPriority(2);

						tteScheduler->registerEvent(f_event);

						//save the event /we have to cancel and delete the events later/
						e_container->insert(make_pair(permanence_pit, f_event));

					} else if (getValue(pf->getMembership_new(), 32)
							== (getValue(
									e_container->find(permanence_pit)->second->getMember(),
									32))) {

						if (pf->getIntegration_cycle()
								> e_container->find(permanence_pit)->second->getIntegrationCycle()) {

							ev
									<< "DEBUG: INTEGRATE REPLACE membership new value"
									<< pf->getMembership_new() << endl;
							ev
									<< "DEBUG: INTEGRATE membership new number of SM "
									<< getValue(pf->getMembership_new(), 32)
									<< endl;

							tteScheduler->unregisterEvent(
									e_container->find(permanence_pit)->second);
							sm->cancelAndDelete(
									e_container->find(permanence_pit)->second);
							e_container->erase(permanence_pit);

							FrameEvent *f_event = new FrameEvent("IN_FRAME",
									TIMER_EVENT);
							f_event->setReceivedPort(
									pf->par("received_port"));
							f_event->setMember(pf->getMembership_new());
							f_event->setPcfType(pf->getType());

							f_event->setTimer(permanence_delay);
							f_event->setDestinationGate(
									sm->gate("schedulerIn"));
							f_event->setIntegrationCycle(
									pf->getIntegration_cycle());
							f_event->setSchedulingPriority(2);

							tteScheduler->registerEvent(f_event);

							//save the event /we have to cancel and delete the events later/
							e_container->insert(
									make_pair(permanence_pit, f_event));

						} //int_cycle

					} else {
						ev << "DEBUG: INTEGRATE NO REPLACE" << endl;
					}

				} else {

					FrameEvent *f_event = new FrameEvent("IN_FRAME",
							TIMER_EVENT);
					f_event->setReceivedPort(
							pf->par("received_port"));
					f_event->setMember(pf->getMembership_new());
					f_event->setPcfType(pf->getType());

					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(sm->gate("schedulerIn"));
					f_event->setIntegrationCycle(pf->getIntegration_cycle());

					f_event->setSchedulingPriority(2);

					tteScheduler->registerEvent(f_event);

					//save the event /we have to cancel and delete the events later/
					e_container->insert(make_pair(permanence_pit, f_event));

				} //frame not found

			} //IN

			if (pf->getType() == CA_FRAME) {

				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);
				f_event->setMember(pf->getMembership_new());
				f_event->setPcfType(pf->getType());
				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sm->gate("schedulerIn"));
				f_event->setSchedulingPriority(1);

				tteScheduler->registerEvent(f_event);

			} //CA

			delete pf;
		} //syncDomain && syncDomain

	} //gate RCin (PCF FRAME)

	if (message->arrivedOn("schedulerIn")) {

		//sm_listen_timeout expired
		if (string(message->getName()).compare("ASYNCHRON") == 0) {

			duration = sm->par("sm_coldstart_timeout");

			event->setSchedulingPriority(3);
			event->setTimer(duration);
			event->setDestinationGate(sm->gate("schedulerIn"));

			//local_clock=0;
			tteScheduler->clockCorrection(tteScheduler->getTicks());

			local_integration_cycle = 0;
			local_sync_membership = 0;
			local_async_membership = 0;

			local_async_membership_r = 0;
			local_async_membership_f = 0;

			ev
					<< "SM_INTEGRATE :: ASYNCHRON TIMER EXPIRED, NEXT STATE -> SM_UNSYNC"
					<< endl;

			new (this) SM_UNSYNC();

			return;

		}

		if (string(message->getName()).compare("FRAME") == 0) {
			//PCF Frame becomes permanent

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CA_FRAME) {

				tteScheduler->unregisterEvent(event);

				duration = sm->par("ca_offset");

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;

				//for safety
				local_sync_membership = 0;

				//local_sync_membership=1; set the own bit
				local_sync_membership |= (1 << ownBit);

				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				delete et;

				new (this) SM_WAIT_4_CYCLE_START_CS();
				return;
			} //CA_FRAME
			delete et;

			return;
		}
		if (string(message->getName()).compare("IN_FRAME") == 0) {
			//PCF Frame becomes permanent

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			//receive(IN_FRAME)
			if (et->getPcfType() == IN_FRAME) {

				uint64_t ppt = tteScheduler->getTotalTicks();

				int64_t temp =
						(int64_t)(
								tteScheduler->getTicks()
										- sm->par("smc_scheduled_receive_pit").intValue());
				//local_clock=smc_scheduled_receive_pit;
				tteScheduler->clockCorrection(temp);

				local_integration_cycle = et->getIntegrationCycle();
				local_sync_membership = getValue(et->getMember(), 32);
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				if ((local_sync_membership
						>= (uint32_t) sm->par("sm_integrate_to_wait_thrld"))
						&& (local_sync_membership
								< (uint32_t) sm->par(
										"sm_integrate_to_sync_thrld"))) {

					tteScheduler->unregisterEvent(event);

					//duration=integration_cycle_duration;????
					duration = sm->par("int_cycle_duration").intValue()
							+ (sm->par("acceptance_window").intValue() / 2);
					//event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
					event->setSchedulingPriority(3);
					event->setTimer(duration);
					event->setDestinationGate(sm->gate("schedulerIn"));

					delete et;

					if (e_container->find(ppt) != e_container->end()) {

						e_container->erase(ppt);
					}

					new (this) SM_WAIT_4_CYCLE_START();

					return;
				}

				if (local_sync_membership
						>= (uint32_t) sm->par("sm_integrate_to_sync_thrld")) {

					tteScheduler->unregisterEvent(event);

					tteScheduler->registerEvent(event1, true);
					tteScheduler->registerEvent(event2);
					tteScheduler->registerEvent(event4);
					tteScheduler->registerEvent(event5);

					//tteScheduler->registerEvent(event3);
					uint32_t tempKey = local_sync_membership;

					clock_stack->insert(
							pair<uint32, pair<uint32, uint64> >(
									et->getReceivedPort(),
									pair<uint32, uint64>(tempKey,
											tteScheduler->getTicks())));

					delete et;
					if (e_container->find(ppt) != e_container->end()) {

						e_container->erase(ppt);
					}



					new (this) SM_SYNC();

					return;
				}

				delete et;

				if (e_container->find(ppt) != e_container->end()) {

					e_container->erase(ppt);
				}

				return;

			} //IN_FRAME

		} //PCF IN Frames

	} //schedulerIn

}

SM_STABLE::SM_STABLE() {

	sm->getDisplayString().setTagArg("i", 1, "green");
	sm->bubble("SM_STABLE");

	/*   if(!sm->par("read").boolValue()){
	 fprintf(fp, "%s %d ", "SM STABLE ", ownBit);
	 fprintf(fp,"%.15f\n", simTime().dbl());
	 fprintf(fp,"%d\n", tteScheduler->getTotalTicks());
	 }
	 */

	//if(local_clock==0){
	//send(IN_FRAME);

	//if(local_clock==smc_async_eval_pit){
//		Async_Clique_Detektion();
//		Relative_Clique_Detection();
//
//		if(local_async_membership >= sm_stable_threshold_async ||
//				local_async_membership >= local_sync_membership)
//			new (this) SM_INTEGRATE();
//
//		}
//
//	if(local_clock==smc_sync_eval_pit){
//	Sync_Clique_Detektion();
//	}
//
//	if(local_clock==smc_clock_corr_pit){
//	local_clock=local_clock+clock_corr;
//	}
}

void SM_STABLE::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *frame = dynamic_cast<PCFrame *>(message);

		if ((frame->getSync_domain() == syncDomain)
				&& (frame->getSync_priority() == syncPriority)) {

			//calculate permanence pit
			uint64_t permanence_delay =
					max_transmission_delay
							- (transparentClockToTicks(
									frame->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
									+ (tteScheduler->getTotalTicks()
											- frame->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;



			//save the event
			if (frame->getType() == CA_FRAME) {

				//create and register the event for the permanence pit
				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);

				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());

				f_event->setTimer(permanence_delay);
				f_event->setDestinationGate(sm->gate("schedulerIn"));

				if (frame->getType() == CS_FRAME) {
					f_event->setSchedulingPriority(0);
				} else if (frame->getType() == CA_FRAME) {
					f_event->setSchedulingPriority(1);
				} else if (frame->getType() == IN_FRAME) {
					f_event->setSchedulingPriority(2);
				} else {
					ev << "UNKNOWN PCF FRAME->TYPE: " << frame->getType()
							<< endl;
				}
				tteScheduler->registerEvent(f_event);

			} //CA_FRAME

			if (frame->getType() == IN_FRAME) {

				FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

				f_event->setReceivedPort(
						frame->par("received_port"));
				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());

				f_event->setTimer(permanence_delay);
				f_event->setDestinationGate(sm->gate("schedulerIn"));
				f_event->setIntegrationCycle(frame->getIntegration_cycle());
				f_event->setSchedulingPriority(2);

				tteScheduler->registerEvent(f_event);

				e_container->insert(
						pair<uint64_t, FrameEvent *>(permanence_pit, f_event));
			} //IN_FRAME

			delete frame;

		} else {

			ev << "DEBUG: STABLE: FRAME ERROR" << "wrong domain or priority"
					<< endl;

		} //sync_priority, sync_domain

	} //gate RCin (PCF FRAME)

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("FRAME") == 0) {

			FrameEvent *e = dynamic_cast<FrameEvent *>(message);

			if (e->getPcfType() == CA_FRAME) {

				if ((e->getPcfType() == CA_FRAME)
						&& (sm->par("stable_ca_enabled").boolValue())) {

					duration = sm->par("ca_offset");
					//local_clock=0;
					event->setSchedulingPriority(3);
					event->setTimer(duration);
					event->setDestinationGate(sm->gate("schedulerIn"));

					tteScheduler->clockCorrection(tteScheduler->getTicks());
					local_integration_cycle = 0;
					local_sync_membership |= (1 << ownBit);
					local_async_membership = 0;
					local_async_membership_f = 0;
					local_async_membership_r = 0;

					stable_cycle_counter = 0;

					clock_stack->clear();

					tteScheduler->unregisterEvent(event1);
					tteScheduler->unregisterEvent(event2);
					tteScheduler->unregisterEvent(event3);
					tteScheduler->unregisterEvent(event4);
					tteScheduler->unregisterEvent(event5);

					delete e;

					new (this) SM_WAIT_4_CYCLE_START_CS();

					return;

				}
				delete e;

				return;
			} //CA_FRAME

			delete e;
			return;
		} //FRAME

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *e = dynamic_cast<FrameEvent *>(message);

			if (e->getPcfType() == IN_FRAME) {
				uint32_t received_port = e->getReceivedPort();
				uint64_t int_cycle = e->getIntegrationCycle();
				uint64_t permanence_pit = tteScheduler->getTicks();
				uint32_t membership = e->getMember();

				if (int_cycle == local_integration_cycle) {



					if (inSchedule(permanence_pit,
							sm->par("smc_scheduled_receive_pit"),
							sm->par("acceptance_window"))) {

						if ((unsigned int)getValue(membership, 32)
								>= (unsigned int)(sm->par("max_pcf_membership")
										- MembershipAcceptanceRange)
								&& (getValue(membership, 32)
										<= (unsigned int)sm->par("max_pcf_membership"))) {

							uint32_t key_ = getValue(membership, 32);

							map<uint32_t, pair<uint32_t, uint64_t> >::iterator itr =
									clock_stack->find(received_port);

							if (itr == clock_stack->end()) {

								clock_stack->insert(
										pair<uint32_t, pair<uint32_t, uint64_t> >(
												received_port,
												pair<uint32_t, uint64_t>(key_,
														permanence_pit)));

							} else {

								if (key_ > itr->second.first) {

									itr->second.first = key_;
									itr->second.second = permanence_pit;

								} else if (key_ == itr->second.first) {

									if (permanence_pit > itr->second.second) {
										itr->second.second = permanence_pit;
									}

								} //membership equal

							} //found

						} //faulty sync master to be tolerated

					} else { //out of Schedule -> permanence pit out of bounds

						//update local_async_membership
						local_async_membership_r = local_async_membership_r
								| (membership);
						local_async_membership_f = local_async_membership_f
								| (membership);
						//
						sm->bubble(
								"out of Schedule -> permanence pit out of bounds");
						//write to log
						ev
								<< "DEBUG: SM_STABLE: permanence point in time(out of schedule)->"
								<< permanence_pit << ownBit << endl;
					} //inSchedule

				} else { //out of Schedule -> wrong integration cycle

					//update local_async_membership

					local_async_membership_r = local_async_membership_r
							| (membership);
					local_async_membership_f = local_async_membership_f
							| (membership);

					sm->bubble("out of Schedule -> wrong integration cycle");
					ev
							<< "DEBUG: SM_STABLE: permanence point in time( wrong integration cycle)->"
							<< permanence_pit << ownBit << endl;

					ev << "DEBUG: SM_STABLE: local_integration_cycle->"
							<< local_integration_cycle << ownBit << endl;
					ev << "DEBUG: SM_STABLE: FRAME integration_cycle->"
							<< int_cycle << ownBit << endl;

				} //local_integration_cycle
				uint64_t ppt = tteScheduler->getTotalTicks();

				if (e_container->find(ppt) != e_container->end()) {

					e_container->erase(ppt);

				}

				delete e;
				return;
			} //IN

		} //IN FRAME

		if (string(message->getName()).compare("smc_async_eval_pit") == 0) {

			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}

			//Relative_Clique_Detection(); Async_Clique_Detektion();
			if ((getValue(local_async_membership, 32)
					>= (unsigned int)sm->par("sm_stable_threshold_async"))
					|| ((unsigned int)getValue(local_async_membership, 32)
							>= local_sync_membership)) {

				duration = sm->par("sm_restart_timeout");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;
				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event2);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				new (this) SM_INTEGRATE();
				return;
			}

			if (!((getValue(local_async_membership, 32)
					>= (unsigned int)sm->par("sm_stable_threshold_async"))
					|| ((unsigned int)getValue(local_async_membership, 32)
							>= local_sync_membership))) {

				//send(IN_FRAME);
				tteScheduler->registerEvent(event1, true);

				PCFrame *p = new PCFrame("IN_FRAME");

				cMsgPar *par = &p->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				p->setType(IN_FRAME);
				p->setTransparent_clock(0);
				p->setMembership_new((1 << ownBit));
				p->setSync_domain(2);
				p->setSync_priority(4);
				p->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				p->setIntegration_cycle((local_integration_cycle + 1));

				if (p->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					p->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}
				p->setDisplayString("b=15,15,rect,white,red,5");

				sm->sendDirect(
						p,
						sm->getParentModule()->getSubmodule("vl_pcf_out_IN")->gate(
								"in"));


				return;
			}
		}

		if (string(message->getName()).compare("smc_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (sm->par("max_integration_cycles").intValue());

			tteScheduler->registerEvent(event4, true);
			return;
		}

		//Sync_Clique_Detektion();
		if (string(message->getName()).compare("smc_sync_eval_pit") == 0) {

			tteScheduler->registerEvent(event2, true);

			tteScheduler->registerEvent(event3);



			/*Upon reaching the smc_sync_eval_pit or cm_sync_eval_pit, each device will update local_sync_membership. The device
			 will set local_sync_membership (i.e., it will select the pcf_membership_new with the highest number of bits set from the
			 set of in-schedule PCFs received during the acceptance window).*/

			if (!clock_stack->empty()) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();

				if (clock_stack->size() == 1) {

					local_sync_membership = iter->second.first;

				} else {
					local_sync_membership = iter->second.first;

					while (iter != clock_stack->end()) {

						if (iter->second.first > local_sync_membership) {
							local_sync_membership = iter->second.first;
						}
						iter++;
					} //while

				}

				ev
						<< "DEBUG STABLE clock_stack not empty: local_sync_membership"
						<< local_sync_membership << endl;

			} else {

				//no "in Schedule" frame has been received during the acceptance window



				local_sync_membership = 0;

			}

			if ((local_sync_membership
					< (unsigned int)sm->par("sm_stable_threshold_sync"))
					&& (stable_cycle_counter
							< (unsigned int)sm->par("num_unstable_cycles"))) {

				stable_cycle_counter++;

				new (this) SM_STABLE();
			}

			if ((local_sync_membership
					< (unsigned int)sm->par("sm_stable_threshold_sync"))
					&& (stable_cycle_counter
							>= (unsigned int)sm->par("num_unstable_cycles"))) {

				duration = sm->par("sm_restart_timeout");
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;
				stable_cycle_counter = 0;

				//clearForTheNextState();

				//container->clear();
				clock_stack->clear();

				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event2);
				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				new (this) SM_INTEGRATE();
				return;
			}

			if (local_sync_membership
					>= (unsigned int)sm->par("sm_stable_threshold_sync")) {

				stable_cycle_counter = 0;

				//new (this) SM_STABLE();
				return;
			}

		}

		if (string(message->getName()).compare("smc_clock_corr_pit") == 0) {



			if (clock_stack->empty()) {
				sm->bubble("SM_STABLE clock_stack->empty");
			} else if (clock_stack->size() == 1) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();
				clock_corr = iter->second.second
						- sm->par("smc_scheduled_receive_pit").intValue();
				tteScheduler->clockCorrection(clock_corr);
				// outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sm->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}

				clock_stack->clear();

				return;
			} else {
				//average method
				int64_t temp = 0;
				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();

				while (iter != clock_stack->end()) {

					temp =
							temp
									+ (iter->second.second
											- sm->par(
													"smc_scheduled_receive_pit").intValue());

					iter++;
				}

				clock_corr = (double) (temp) / (double) (clock_stack->size());

				ev
						<< "DEBUG: SM_STABLE:clock_corr_pit /more than one/ clock correction: "
						<< clock_corr << endl;

				tteScheduler->clockCorrection(clock_corr);

				//outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sm->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}

				clock_stack->clear();

				return;

			}

		}
		if (string(message->getName()).compare("smc_async_up") == 0) {

			if ((local_integration_cycle % 2) == 0) {

				local_async_membership_f = 0;

			} else {

				local_async_membership_r = 0;

			}


			tteScheduler->registerEvent(event5, true);

		}

	} //schedulerIn
}

SM_UNSYNC::SM_UNSYNC() {
	//Enter

	sm->getDisplayString().setTagArg("i", 1, "black");
	sm->bubble("SM_UNSYNC");
	ev << "current state: SM_UNSYNC" << endl;

	PCFrame *p = new PCFrame("CS_FRAME");



	cMsgPar *par = &p->addPar("created_total");
	par->setLongValue(tteScheduler->getTotalTicks());

	p->setType(CS_FRAME);
	p->setTransparent_clock(0);
	p->setMembership_new((1 << ownBit));
	p->setSync_domain(2);
	p->setSync_priority(4);
	p->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
	p->setIntegration_cycle(local_integration_cycle);
	//Padding
	if (p->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
		p->setByteLength(MIN_ETHERNET_FRAME_BYTES);
	}
	p->setDisplayString("b=15,15,rect,white,black,5");

	sm->sendDirect(p,
			sm->getParentModule()->getSubmodule("vl_pcf_out_CS")->gate("in"));

	ev << "SM_UNSYNC send CS Bit Number" << ownBit << endl;


	//timer start
	tteScheduler->registerEvent(event);

}

void SM_UNSYNC::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {
		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();


		//SM/SC makes all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);



		if ((pf->getSync_domain() == syncDomain)
				&& (pf->getSync_priority() == syncPriority)) {

			if ((transparentClockToTicks(pf->getTransparent_clock(),
					tteScheduler->par("tick").doubleValue())
					+ (tteScheduler->getTotalTicks()
							- pf->par("received_total").intValue())
					> max_transmission_delay)) {

				ev
						<< "WARNING: SM_UNSYNC: pkt->getTransparent_clock() > max_transmission_delay "
						<< endl;
				ev << "WARNING: pkt->getTransparent_clock()"
						<< transparentClockToTicks(pf->getTransparent_clock(),
								tteScheduler->par("tick").doubleValue())
						<< endl;
			}

			//calculate permanence pit
			uint64_t permanence_delay = max_transmission_delay
					- (transparentClockToTicks(pf->getTransparent_clock(),
							tteScheduler->par("tick").doubleValue())
							+ (tteScheduler->getTotalTicks()
									- pf->par("received_total").intValue()));

			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			if (pf->getType() == IN_FRAME) {

				if (e_container->find(permanence_pit) != e_container->end()) {

					if (getValue(pf->getMembership_new(), 32)
							> (getValue(
									e_container->find(permanence_pit)->second->getMember(),
									32))) {

						ev << "DEBUG: SM_UNSYNC REPLACE membership new value"
								<< pf->getMembership_new() << endl;
						ev << "DEBUG: SM_UNSYNC membership new number of SM "
								<< getValue(pf->getMembership_new(), 32)
								<< endl;

						tteScheduler->unregisterEvent(
								e_container->find(permanence_pit)->second);
						sm->cancelAndDelete(
								e_container->find(permanence_pit)->second);
						e_container->erase(permanence_pit);

						FrameEvent *f_event = new FrameEvent("IN_FRAME",
								TIMER_EVENT);
						f_event->setReceivedPort(
								pf->par("received_port").intValue());
						f_event->setMember(pf->getMembership_new());
						f_event->setPcfType(pf->getType());

						f_event->setTimer(permanence_delay);
						f_event->setDestinationGate(sm->gate("schedulerIn"));
						f_event->setIntegrationCycle(
								pf->getIntegration_cycle());
						f_event->setSchedulingPriority(2);

						tteScheduler->registerEvent(f_event);

						//save the event /we have to cancel and delete the events later/
						e_container->insert(make_pair(permanence_pit, f_event));

					} else if (getValue(pf->getMembership_new(), 32)
							== (getValue(
									e_container->find(permanence_pit)->second->getMember(),
									32))) {

						if (pf->getIntegration_cycle()
								> e_container->find(permanence_pit)->second->getIntegrationCycle()) {

							ev
									<< "DEBUG: SM_UNSYNC REPLACE membership new value"
									<< pf->getMembership_new() << endl;
							ev
									<< "DEBUG: SM_UNSYNC membership new number of SM "
									<< getValue(pf->getMembership_new(), 32)
									<< endl;

							tteScheduler->unregisterEvent(
									e_container->find(permanence_pit)->second);
							sm->cancelAndDelete(
									e_container->find(permanence_pit)->second);
							e_container->erase(permanence_pit);

							FrameEvent *f_event = new FrameEvent("IN_FRAME",
									TIMER_EVENT);
							f_event->setReceivedPort(
									pf->par("received_port").intValue());
							f_event->setMember(pf->getMembership_new());
							f_event->setPcfType(pf->getType());
							//f_event->setAction_time(permanence_pit);
							f_event->setTimer(permanence_delay);
							f_event->setDestinationGate(
									sm->gate("schedulerIn"));
							f_event->setIntegrationCycle(
									pf->getIntegration_cycle());
							f_event->setSchedulingPriority(2);

							tteScheduler->registerEvent(f_event);

							//save the event /we have to cancel and delete the events later/
							e_container->insert(
									make_pair(permanence_pit, f_event));

						} //int_cycle

					} else {
						ev << "DEBUG: SM_UNSYNC NO REPLACE" << endl;
					}

				} else {

					FrameEvent *f_event = new FrameEvent("IN_FRAME",
							TIMER_EVENT);
					f_event->setReceivedPort(
							pf->par("received_port").intValue());
					f_event->setMember(pf->getMembership_new());
					f_event->setPcfType(pf->getType());

					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(sm->gate("schedulerIn"));
					f_event->setIntegrationCycle(pf->getIntegration_cycle());

					f_event->setSchedulingPriority(2);

					tteScheduler->registerEvent(f_event);

					//save the event /we have to cancel and delete the events later/
					e_container->insert(make_pair(permanence_pit, f_event));

				} //frame not found

				delete pf;

			} else {

				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);
				f_event->setReceivedPort(pf->par("received_port").intValue());
				f_event->setMember(pf->getMembership_new());
				f_event->setPcfType(pf->getType());
				f_event->setIntegrationCycle(pf->getIntegration_cycle());

				f_event->setTimer(permanence_delay);
				f_event->setDestinationGate(sm->gate("schedulerIn"));

				if (pf->getType() == CS_FRAME) {
					f_event->setSchedulingPriority(0);
				} else if (pf->getType() == CA_FRAME) {
					f_event->setSchedulingPriority(1);
				} else if (pf->getType() == IN_FRAME) {
					f_event->setSchedulingPriority(2);
				} else {
					ev << "UNKNOWN PCF FRAME->TYPE: " << pf->getType() << endl;
				}

				tteScheduler->registerEvent(f_event);

				delete pf;

			} //FRAME

		} //syncDomain && syncPriority

	} //RCin

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("ASYNCHRON") == 0) {
			//local_timer expired

			duration = sm->par("sm_coldstart_timeout").intValue();
			int64_t clk = tteScheduler->getTicks();
			//local_clock=0;

			tteScheduler->clockCorrection(clk);

			local_integration_cycle = 0;
			local_sync_membership = 0;
			local_async_membership = 0;
			local_async_membership_r = 0;
			local_async_membership_f = 0;

			new (this) SM_UNSYNC();
			return;

		}

		if (string(message->getName()).compare("FRAME") == 0) {
			//PCF Frame becomes permanent

			FrameEvent *e = dynamic_cast<FrameEvent *>(message);

			if (e->getPcfType() == CS_FRAME) {

				//receive CS_FRAME, Master config ->Standart_Integrity_Synchronisation
				if (sm->par("Standart_Integrity_Synchronisation").boolValue()) {

					duration = sm->par("cs_offset").intValue();

					tteScheduler->unregisterEvent(event);

					event->setSchedulingPriority(3);
					event->setTimer(duration);
					event->setDestinationGate(sm->gate("schedulerIn"));

					//local_clock=0;
					tteScheduler->clockCorrection(tteScheduler->getTicks());

					local_integration_cycle = 0;
					local_sync_membership = 0;
					local_async_membership = 0;
					local_async_membership_r = 0;
					local_async_membership_f = 0;

					//clearForTheNextState();
					flood_receive = false;
					closed_window = false;

					delete e;

					new (this) SM_FLOOD();
					return;
				}
				//Master config -> High_Integrity_Synchronisation
				//the received CS frame stems from a other synchronization master
				if ((sm->par("High_Integrity_Synchronisation").boolValue())
						&& (((unsigned int)1 << ownBit) != e->getMember())) {

					duration = sm->par("cs_offset").intValue();

					tteScheduler->unregisterEvent(event);

					event->setSchedulingPriority(3);
					event->setTimer(duration);
					event->setDestinationGate(sm->gate("schedulerIn"));

					//local_clock=0;
					tteScheduler->clockCorrection(tteScheduler->getTicks());

					local_integration_cycle = 0;
					local_sync_membership = 0;
					local_async_membership = 0;
					local_async_membership_r = 0;
					local_async_membership_f = 0;

					flood_receive = false;
					closed_window = false;

					delete e;
					ev << "NEXT STATE: SM_FLOOD: INDEX" << ownBit << "BIT SET"
							<< (1 << ownBit) << endl;
					new (this) SM_FLOOD();
					return;
				}
				delete e;
				return;
			}

			//receive CA_FRAME
			if (e->getPcfType() == CA_FRAME) {

				tteScheduler->unregisterEvent(event);

				duration = sm->par("ca_offset").intValue();

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				//local_sync_membership=1; set own bit
				local_sync_membership = 0;
				local_sync_membership |= (1 << ownBit);

				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				delete e;

				new (this) SM_WAIT_4_CYCLE_START_CS();
				return;
			}
		} //FRAME
		  //receive IN_FRAME
		if (string(message->getName()).compare("IN_FRAME") == 0) {
			//PCF Frame becomes permanent

			FrameEvent *e = dynamic_cast<FrameEvent *>(message);

			if (e->getPcfType() == IN_FRAME) {

				//duration=0;
				tteScheduler->unregisterEvent(event);

				int64_t temp =
						(int64_t)(
								tteScheduler->getTicks()
										- sm->par("smc_scheduled_receive_pit").intValue());
				//local_clock=smc_scheduled_receive_pit;
				tteScheduler->clockCorrection(temp);

				local_integration_cycle = e->getIntegrationCycle();
				local_sync_membership = getValue(e->getMember(), 32);
				local_async_membership = 0;

				if (local_sync_membership
						>= (unsigned int)sm->par("sm_unsync_to_sync_thrld")) {

					uint32_t tempKey = local_sync_membership;

					uint32_t received_port = e->getReceivedPort();
					clock_stack->insert(
							pair<uint32_t, pair<uint32_t, uint64_t> >(
									received_port,
									pair<uint32_t, uint64_t>(tempKey,
											tteScheduler->getTicks())));

					tteScheduler->registerEvent(event1, true);
					tteScheduler->registerEvent(event2);
					tteScheduler->registerEvent(event4);

					tteScheduler->registerEvent(event5);

					uint64_t ppt = tteScheduler->getTotalTicks();

					if (e_container->find(ppt) != e_container->end()) {

						e_container->erase(ppt);
					}

					delete e;
					new (this) SM_SYNC();
					return;
				}
				if ((local_sync_membership
						< (unsigned int)sm->par("sm_unsync_to_sync_thrld"))
						&& (local_sync_membership
								>= (unsigned int)sm->par("sm_unsync_to_tentative_thrld"))) {

					uint32_t tempKey = local_sync_membership;

					uint32_t received_port = e->getReceivedPort();
					clock_stack->insert(
							pair<uint32_t, pair<uint32_t, uint64_t> >(
									received_port,
									pair<uint32_t, uint64_t>(tempKey,
											tteScheduler->getTicks())));

					tteScheduler->registerEvent(event1, true);
					tteScheduler->registerEvent(event2);
					tteScheduler->registerEvent(event4);
					tteScheduler->registerEvent(event5);

					uint64_t ppt = tteScheduler->getTotalTicks();

					if (e_container->find(ppt) != e_container->end()) {

						e_container->erase(ppt);
					}

					delete e;

					new (this) SM_TENTATIVE_SYNC();
					return;
				}

				delete e;
				return;
			} //IN-FRAME

		} //pcf frame IN

	} //schedulerIn
}

SM_SYNC::SM_SYNC() {

	sm->getDisplayString().setTagArg("i", 1, "yellow");
	sm->bubble("SM_SYNC");

	//local_clock==smc_async_eval_pit;
	//Async_Clique_Detektion();
	//Relative_Clique_Detection();

	//if(local_clock==0)
	//send(IN_FRAME);

	//local_clock==smc_sync_eval_pit;
	//Sync_Clique_Detektion();
	//stable_cycle_counter++;

	//local_clock==smc_clock_corr_pit
	//local_clock=local_clock+clock_corr;

}
void SM_SYNC::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *frame = dynamic_cast<PCFrame *>(message);

		if ((frame->getSync_domain() == syncDomain)
				&& (frame->getSync_priority() == syncPriority)) {

			//calculate permanence pit
			uint64_t permanence_delay =
					max_transmission_delay
							- (transparentClockToTicks(
									frame->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
									+ (tteScheduler->getTotalTicks()
											- frame->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			//save the event
			if (frame->getType() == CA_FRAME) {

				//create and register the event for the permanence pit
				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);

				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());
				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sm->gate("schedulerIn"));
				f_event->setIntegrationCycle(frame->getIntegration_cycle());

				if (frame->getType() == CS_FRAME) {
					f_event->setSchedulingPriority(0);
				} else if (frame->getType() == CA_FRAME) {
					f_event->setSchedulingPriority(1);
				} else if (frame->getType() == IN_FRAME) {
					f_event->setSchedulingPriority(2);
				} else {
					ev << "UNKNOWN PCF FRAME->TYPE: " << frame->getType()
							<< endl;
				}
				tteScheduler->registerEvent(f_event);

			} //CA_FRAME

			if (frame->getType() == IN_FRAME) {

				FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

				f_event->setReceivedPort(
						frame->par("received_port"));
				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());

				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sm->gate("schedulerIn"));
				f_event->setIntegrationCycle(frame->getIntegration_cycle());
				f_event->setSchedulingPriority(2);

				tteScheduler->registerEvent(f_event);
				e_container->insert(
						pair<uint64_t, FrameEvent *>(permanence_pit, f_event));
			} //IN_FRAME

			delete frame;

		} else {

			ev << "DEBUG: SYNC: FRAME ERROR" << "wrong domain or priority"
					<< endl;

		} //sync_priority, sync_domain

	} //gate RCin (PCF FRAME)

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			if (evt->getPcfType() == CA_FRAME) {

				duration = sm->par("ca_offset");

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;

				local_sync_membership = local_sync_membership | (1 << ownBit);

				local_async_membership = 0;

				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event1);

				tteScheduler->unregisterEvent(event2);

				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				clock_stack->clear();

				delete evt;

				new (this) SM_WAIT_4_CYCLE_START_CS();
				return;

			}

			delete evt;
			return;

		} //Frame
		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			if (evt->getPcfType() == IN_FRAME) {

				uint32_t received_port = evt->getReceivedPort();
				uint64_t int_cycle = evt->getIntegrationCycle();
				uint64_t permanence_pit = tteScheduler->getTicks();
				uint32_t membership = evt->getMember();

				if (int_cycle == local_integration_cycle) {

					if (inSchedule(permanence_pit,
							sm->par("smc_scheduled_receive_pit"),
							sm->par("acceptance_window"))) {

						if ((unsigned int)getValue(membership, 32)
								>= (unsigned int)(sm->par("max_pcf_membership")
										- MembershipAcceptanceRange)
								&& (getValue(membership, 32)
										<= (unsigned int)sm->par("max_pcf_membership"))) {

							uint32_t key_ = getValue(membership, 32);

							map<uint32_t, pair<uint32_t, uint64_t> >::iterator itr =
									clock_stack->find(received_port);

							if (itr == clock_stack->end()) {

								clock_stack->insert(
										pair<uint32_t, pair<uint32_t, uint64_t> >(
												received_port,
												pair<uint32_t, uint64_t>(key_,
														permanence_pit)));

							} else {

								if (key_ > itr->second.first) {

									itr->second.first = key_;
									itr->second.second = permanence_pit;

								} else if (key_ == itr->second.first) {

									if (permanence_pit > itr->second.second) {
										itr->second.second = permanence_pit;
									}

								} //membership equal

							} //found

						} //faulty sync master to be tolerated

					} else { //out of Schedule -> permanence pit out of bounds

						//update local_async_membership
						local_async_membership_r = local_async_membership_r
								| (membership);
						local_async_membership_f = local_async_membership_f
								| (membership);
						//
						sm->bubble(
								"out of Schedule -> permanence pit out of bounds");
						//write to log
						ev
								<< "DEBUG: SM_SYNC: permanence point in time(out of schedule)->"
								<< permanence_pit << ownBit << endl;
					} //inSchedule

				} else { //out of Schedule -> wrong integration cycle

					//update local_async_membership

					local_async_membership_r = local_async_membership_r
							| (membership);
					local_async_membership_f = local_async_membership_f
							| (membership);

					sm->bubble("out of Schedule -> wrong integration cycle");

					ev << "DEBUG: SM_SYNC: permanence point in time:member:->"
							<< ownBit << permanence_pit << endl;

					ev << "DEBUG: SM_SYNC: local_integration_cycle:member:->"
							<< ownBit << local_integration_cycle << ownBit
							<< endl;
					ev << "DEBUG: SM_SYNC: FRAME integration_cycle->"
							<< int_cycle << endl;

				} //local_integration_cycle

				uint64_t ppt = tteScheduler->getTotalTicks();

				if (e_container->find(ppt) != e_container->end()) {

					e_container->erase(ppt);
				}

				delete evt;
				return;

			}
		} //IN FRAME

		//local_clock==smc_async_eval_pit;
		//Async_Clique_Detektion();
		//Relative_Clique_Detection();
		if (string(message->getName()).compare("smc_async_eval_pit") == 0) {

			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}

			if ((getValue(local_async_membership, 32)
					>= (unsigned int)sm->par("sm_sync_threshold_async"))
					|| (getValue(local_async_membership, 32)
							>= local_sync_membership)) {

				duration = sm->par("sm_restart_timeout_async");

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event2);

				clock_stack->clear();

				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event2);
				tteScheduler->unregisterEvent(event5);

				new (this) SM_UNSYNC();
				return;
			}

			if (!((getValue(local_async_membership, 32)
					>= (unsigned int)sm->par("sm_sync_threshold_async"))
					|| (getValue(local_async_membership, 32)
							>= local_sync_membership))) {

				tteScheduler->registerEvent(event1, true);

				//send(IN_FRAME);
				PCFrame *p = new PCFrame("IN_FRAME");
				cMsgPar *par = &p->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				p->setType(IN_FRAME);
				p->setTransparent_clock(0);
				p->setMembership_new(1 << ownBit);
				p->setSync_domain(2);
				p->setSync_priority(4);
				p->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				p->setIntegration_cycle(local_integration_cycle + 1);


				ev << "Send IN FRAME INT CYCLE int cycle" << p->getIntegration_cycle()
						<< endl;

				//Padding
				if (p->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					p->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}
				p->setDisplayString("b=15,15,rect,white,red,5");

				sm->sendDirect(
						p,
						sm->getParentModule()->getSubmodule("vl_pcf_out_IN")->gate(
								"in"));

				return;
			}
		}

		if (string(message->getName()).compare("smc_inc_pit") == 0) {



			local_integration_cycle = (local_integration_cycle + 1)
					% (sm->par("max_integration_cycles").intValue());


			tteScheduler->registerEvent(event4, true);
		}

		if (string(message->getName()).compare("smc_sync_eval_pit") == 0) {

			tteScheduler->registerEvent(event3);


			/*Upon reaching the smc_sync_eval_pit or cm_sync_eval_pit, each device will update local_sync_membership. The device
			 will set local_sync_membership (i.e., it will select the pcf_membership_new with the highest number of bits set from the
			 set of in-schedule PCFs received during the acceptance window).*/

			if (!clock_stack->empty()) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();

				if (clock_stack->size() == 1) {

					local_sync_membership = iter->second.first;

				} else {
					local_sync_membership = iter->second.first;

					while (iter != clock_stack->end()) {

						if (iter->second.first > local_sync_membership) {
							local_sync_membership = iter->second.first;
						}
						iter++;
					} //while

				}

				ev
						<< "DEBUG STABLE clock_stack not empty: local_sync_membership"
						<< local_sync_membership << endl;

			} else {

				//no "in Schedule" frame has been received during the acceptance window



				local_sync_membership = 0;

			}

			if ((local_sync_membership
					< (unsigned int)sm->par("sm_sync_threshold_sync"))
					&& (local_sync_membership > 0)) {

				duration = sm->par("sm_restart_timeout_sync");

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event5);


				clock_stack->clear();

				new (this) SM_UNSYNC();

				return;
			}

			if ((local_sync_membership
					< (unsigned int)sm->par("sm_sync_threshold_sync"))
					&& (local_sync_membership == 0)) {

				duration = sm->par("sm_restart_timeout_sync");

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);
				tteScheduler->unregisterEvent(event3);

				clock_stack->clear();

				new (this) SM_INTEGRATE();
				return;
			}

			if ((local_sync_membership
					>= (unsigned int)sm->par("sm_sync_threshold_sync"))
					&& (stable_cycle_counter
							< (unsigned int)sm->par("num_stable_cycles"))
					&& (sm->par("sm_sync_to_stable_enabled").boolValue())) {

				stable_cycle_counter++;
				tteScheduler->registerEvent(event2, true);
				return;
				//new (this) SM_SYNC();

			}

			if ((local_sync_membership
					>= (unsigned int)sm->par("sm_sync_threshold_sync"))
					&& (stable_cycle_counter
							>= (unsigned int)sm->par("num_stable_cycles"))
					&& (sm->par("sm_sync_to_stable_enabled").boolValue())) {

				stable_cycle_counter = 0;
				tteScheduler->registerEvent(event2, true);
				new (this) SM_STABLE();
				return;
			}
			if (local_sync_membership
					>= (unsigned int)sm->par("sm_sync_threshold_sync")) {
				tteScheduler->registerEvent(event2, true);
				stable_cycle_counter++;

				//new (this) SM_SYNC();
				return;
			}

		} //sm_sync_eval

		if (string(message->getName()).compare("smc_clock_corr_pit") == 0) {


			if (clock_stack->empty()) {
				sm->bubble("SM_SYNC clock_stack->empty");
			} else if (clock_stack->size() == 1) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();
				clock_corr = iter->second.second
						- sm->par("smc_scheduled_receive_pit");
				tteScheduler->clockCorrection(clock_corr);
				//outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sm->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}

				clock_stack->clear();
				//
				//new (this) SC_SYNC();
				return;
			} else {
				//average method
				int64_t temp = 0;
				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();

				while (iter != clock_stack->end()) {

					temp =
							temp
									+ (iter->second.second
											- sm->par(
													"smc_scheduled_receive_pit").intValue());

					iter++;
				}

				clock_corr = (double) (temp) / (double) (clock_stack->size());

				ev
						<< "DEBUG: SM_SYNC:clock_corr_pit /more than one/ clock correction: "
						<< clock_corr << endl;

				tteScheduler->clockCorrection(clock_corr);

				//outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sm->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}

				//for the next cycle
				//container->clear();
				clock_stack->clear();
				//
				//new (this) SM_STABLE();
				return;

			}

		}

		if (string(message->getName()).compare("smc_async_up") == 0) {

			if ((local_integration_cycle % 2) == 0) {

				local_async_membership_f = 0;

			} else {

				local_async_membership_r = 0;

			}


			tteScheduler->registerEvent(event5, true);

		}

	} //scheduler In
}
SM_FLOOD::SM_FLOOD() {

	sm->getDisplayString().setTagArg("i", 1, "white");
	sm->bubble("SM_FLOOD");

	tteScheduler->registerEvent(event);

}

void SM_FLOOD::handleMessage(cMessage *message) {

	//receive CS_FRAME

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//makes all PCF frames permanent

		PCFrame *f = dynamic_cast<PCFrame *>(message);

		if ((f->getSync_domain() == syncDomain)
				&& (f->getSync_priority() == syncPriority)) {

			//calculate permanence pit
			uint64_t permanence_delay = max_transmission_delay
					- (transparentClockToTicks(f->getTransparent_clock(),
							tteScheduler->par("tick").doubleValue())
							+ (tteScheduler->getTotalTicks()
									- f->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			if (f->getType() == CS_FRAME) {
				//create and register the event for the permanence pit

				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);

				f_event->setPcfType(f->getType());
				f_event->setMember(f->getMembership_new());
				f_event->setIntegrationCycle(f->getIntegration_cycle());
				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sm->gate("schedulerIn"));

				f_event->setSchedulingPriority(0);
				tteScheduler->registerEvent(f_event);

			} else if (f->getType() == CA_FRAME) {
				//create and register the event for the permanence pit

				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);

				f_event->setPcfType(f->getType());
				f_event->setMember(f->getMembership_new());
				f_event->setIntegrationCycle(f->getIntegration_cycle());
				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sm->gate("schedulerIn"));

				f_event->setSchedulingPriority(1);
				tteScheduler->registerEvent(f_event);

			} else if (f->getType() == IN_FRAME) {

                if (e_container->find(permanence_pit) != e_container->end()) {

                    if (getValue(f->getMembership_new(), 32)
                            > (getValue(
                                    e_container->find(permanence_pit)->second->getMember(),
                                    32))) {

                        ev << "DEBUG: SM_FLOOD REPLACE membership new value"
                                << f->getMembership_new() << endl;
                        ev << "DEBUG: SM_FLOOD membership new number of SM "
                                << getValue(f->getMembership_new(), 32)
                                << endl;

                        tteScheduler->unregisterEvent(
                                e_container->find(permanence_pit)->second);
                        sm->cancelAndDelete(
                                e_container->find(permanence_pit)->second);
                        e_container->erase(permanence_pit);

                        FrameEvent *f_event = new FrameEvent("IN_FRAME",
                                TIMER_EVENT);
                        f_event->setReceivedPort(
                                f->par("received_port"));
                        f_event->setMember(f->getMembership_new());
                        f_event->setPcfType(f->getType());

                        f_event->setTimer(permanence_delay);
                        f_event->setDestinationGate(sm->gate("schedulerIn"));
                        f_event->setIntegrationCycle(
                                f->getIntegration_cycle());
                        f_event->setSchedulingPriority(2);

                        tteScheduler->registerEvent(f_event);

                        //save the event /we have to cancel and delete the events later/
                        e_container->insert(make_pair(permanence_pit, f_event));

                    } else if (getValue(f->getMembership_new(), 32)
                            == (getValue(
                                    e_container->find(permanence_pit)->second->getMember(),
                                    32))) {

                        if (f->getIntegration_cycle()
                                > e_container->find(permanence_pit)->second->getIntegrationCycle()) {

                            ev
                                    << "DEBUG: SM_FLOOD REPLACE membership new value"
                                    << f->getMembership_new() << endl;
                            ev
                                    << "DEBUG: SM_FLOOD membership new number of SM "
                                    << getValue(f->getMembership_new(), 32)
                                    << endl;

                            tteScheduler->unregisterEvent(
                                    e_container->find(permanence_pit)->second);
                            sm->cancelAndDelete(
                                    e_container->find(permanence_pit)->second);
                            e_container->erase(permanence_pit);

                            FrameEvent *f_event = new FrameEvent("IN_FRAME",
                                    TIMER_EVENT);
                            f_event->setReceivedPort(
                                    f->par("received_port"));
                            f_event->setMember(f->getMembership_new());
                            f_event->setPcfType(f->getType());
                            //f_event->setAction_time(permanence_pit);
                            f_event->setTimer(permanence_delay);
                            f_event->setDestinationGate(
                                    sm->gate("schedulerIn"));
                            f_event->setIntegrationCycle(
                                    f->getIntegration_cycle());
                            f_event->setSchedulingPriority(2);

                            tteScheduler->registerEvent(f_event);

                            //save the event /we have to cancel and delete the events later/
                            e_container->insert(
                                    make_pair(permanence_pit, f_event));

                        } //int_cycle

                    } else {
                        ev << "DEBUG: SM_FLOOD NO REPLACE" << endl;
                    }

                } else {

                    FrameEvent *f_event = new FrameEvent("IN_FRAME",
                            TIMER_EVENT);
                    f_event->setReceivedPort(
                            f->par("received_port"));
                    f_event->setMember(f->getMembership_new());
                    f_event->setPcfType(f->getType());

                    f_event->setTimer(permanence_delay);
                    f_event->setDestinationGate(sm->gate("schedulerIn"));
                    f_event->setIntegrationCycle(f->getIntegration_cycle());

                    f_event->setSchedulingPriority(2);

                    tteScheduler->registerEvent(f_event);

                    //save the event /we have to cancel and delete the events later/
                    e_container->insert(make_pair(permanence_pit, f_event));

                } //frame not found

                delete f;

            } else {
				ev << "UNKNOWN PCF FRAME->TYPE: " << f->getType() << endl;
			}

			delete f;

		} //syncDomain && syncPriority

	} //RCin

	if (message->arrivedOn("schedulerIn")) {


		//local timer expired

		if (string(message->getName()).compare("ASYNCHRON") == 0) {

			ev << "SyncMaster:" << ownBit << "FLOOD-> TIMER EXPIRED "
					<< tteScheduler->getTotalTicks() << endl;

			if ((!flood_receive) && (!closed_window)) {

				//send(CA_FRAME);
				PCFrame *p = new PCFrame("CA_FRAME");
				cMsgPar *par = &p->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());
				p->setType(CA_FRAME);
				p->setTransparent_clock(0);
				p->setMembership_new(1 << ownBit);
				p->setSync_domain(2);
				p->setSync_priority(4);
				p->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				p->setIntegration_cycle(64);
				//Padding
				if (p->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					p->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				p->setDisplayString("b=15,15,rect,white,blue,5");

				sm->sendDirect(
						p,
						sm->getParentModule()->getSubmodule("vl_pcf_out_CA")->gate(
								"in"));
				ev << "SEND CAFRAME getTotalTicks: "
						<< tteScheduler->getTotalTicks() << endl;

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				tteScheduler->unregisterEvent(event);

				//
				//As6802 spec ->  duration=sm->par("ca_round_trip") - (sm->par("ca_acceptance_window")/2);
				//should be
				duration = (sm->par("ca_round_trip"));

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				flood_receive = true;

				new (this) SM_FLOOD();

				return;
			}

			if ((flood_receive) && (!closed_window)) {

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				tteScheduler->unregisterEvent(event);

				duration = sm->par("ca_acceptance_window");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				closed_window = true;

				new (this) SM_FLOOD();

				return;
			}

			if ((flood_receive) && (closed_window)) {

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				tteScheduler->unregisterEvent(event);

				duration = sm->par("sm_coldstart_timeout");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				flood_receive = false;
				closed_window = false;

				new (this) SM_UNSYNC();
				return;

			}

		}

		if (string(message->getName()).compare("FRAME") == 0) {
			//PCF Frame becomes permanent

			FrameEvent *e = dynamic_cast<FrameEvent*>(message);
			//ev << "TYPE" << e->getPcfType() << endl;

			if (e->getPcfType() == CS_FRAME) {

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				tteScheduler->unregisterEvent(event);

				duration = sm->par("cs_offset");

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				flood_receive = false;
				closed_window = false;

				delete e;

				new (this) SM_FLOOD();
				return;
			} //CS_FRAME

			if ((e->getPcfType() == CA_FRAME)
					&& (flood_receive && (!closed_window))) {
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				tteScheduler->unregisterEvent(event);

				duration = sm->par("ca_offset");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				flood_receive = false;
				closed_window = false;

				delete e;

				new (this) SM_WAIT_4_CYCLE_START_CS();
				return;
			} //CA_FRAME

			delete e;
			return;
		} //CA, CS frames becomes permanent

		if (string(message->getName()).compare("IN_FRAME") == 0) {



		    FrameEvent *e = dynamic_cast<FrameEvent*>(message);
		    delete e;

		    uint64_t ppt=tteScheduler->getTotalTicks();

		    if (e_container->find(ppt) != e_container->end()) {

		                            e_container->erase(ppt);
		                        }

		    return;
		}


	} //scheduler in

}

SM_WAIT_4_CYCLE_START_CS::SM_WAIT_4_CYCLE_START_CS() {

	sm->getDisplayString().setTagArg("i", 1, "cyan");
	sm->bubble("SM_WAIT_4_CYCLE_START_CS");
	ev << "SM_WAIT_4_CYCLE_START_CS MEMBER" << ownBit << endl;

	tteScheduler->registerEvent(event);

}

void SM_WAIT_4_CYCLE_START_CS::handleMessage(cMessage* message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//makes all PCF frames permanent

		PCFrame *frame = dynamic_cast<PCFrame *>(message);

		if ((frame->getSync_domain() == syncDomain)
				&& (frame->getSync_priority() == syncPriority)) {

			//calculate permanence pit
			uint64_t permanence_delay =
					max_transmission_delay
							- (transparentClockToTicks(
									frame->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
									+ (tteScheduler->getTotalTicks()
											- frame->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			//create and register the event for the permanence pit

			if (frame->getType() == CS_FRAME) {

				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);

				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());
				f_event->setIntegrationCycle(frame->getIntegration_cycle());

				f_event->setTimer(permanence_delay);
				f_event->setDestinationGate(sm->gate("schedulerIn"));

				f_event->setSchedulingPriority(0);
				tteScheduler->registerEvent(f_event);

			} else if (frame->getType() == CA_FRAME) {

				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);

				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());
				f_event->setIntegrationCycle(frame->getIntegration_cycle());

				f_event->setTimer(permanence_delay);
				f_event->setDestinationGate(sm->gate("schedulerIn"));

				f_event->setSchedulingPriority(1);
				tteScheduler->registerEvent(f_event);

			} else if (frame->getType() == IN_FRAME) {

                if (e_container->find(permanence_pit) != e_container->end()) {

                    if (getValue(frame->getMembership_new(), 32)
                            > (getValue(
                                    e_container->find(permanence_pit)->second->getMember(),
                                    32))) {

                        ev << "DEBUG: SM_WAIT_4_CYCLE_START_CS REPLACE membership new value"
                                << frame->getMembership_new() << endl;
                        ev << "DEBUG: SM_WAIT_4_CYCLE_START_CS membership new number of SM "
                                << getValue(frame->getMembership_new(), 32)
                                << endl;

                        tteScheduler->unregisterEvent(
                                e_container->find(permanence_pit)->second);
                        sm->cancelAndDelete(
                                e_container->find(permanence_pit)->second);
                        e_container->erase(permanence_pit);

                        FrameEvent *f_event = new FrameEvent("IN_FRAME",
                                TIMER_EVENT);
                        f_event->setReceivedPort(
                                frame->par("received_port"));
                        f_event->setMember(frame->getMembership_new());
                        f_event->setPcfType(frame->getType());

                        f_event->setTimer(permanence_delay);
                        f_event->setDestinationGate(sm->gate("schedulerIn"));
                        f_event->setIntegrationCycle(
                                frame->getIntegration_cycle());
                        f_event->setSchedulingPriority(2);

                        tteScheduler->registerEvent(f_event);

                        //save the event /we have to cancel and delete the events later/
                        e_container->insert(make_pair(permanence_pit, f_event));

                    } else if (getValue(frame->getMembership_new(), 32)
                            == (getValue(
                                    e_container->find(permanence_pit)->second->getMember(),
                                    32))) {

                        if (frame->getIntegration_cycle()
                                > e_container->find(permanence_pit)->second->getIntegrationCycle()) {

                            ev
                                    << "DEBUG: SM_WAIT_4_CYCLE_START_CS REPLACE membership new value"
                                    << frame->getMembership_new() << endl;
                            ev
                                    << "DEBUG: SM_WAIT_4_CYCLE_START_CS membership new number of SM "
                                    << getValue(frame->getMembership_new(), 32)
                                    << endl;

                            tteScheduler->unregisterEvent(
                                    e_container->find(permanence_pit)->second);
                            sm->cancelAndDelete(
                                    e_container->find(permanence_pit)->second);
                            e_container->erase(permanence_pit);

                            FrameEvent *f_event = new FrameEvent("IN_FRAME",
                                    TIMER_EVENT);
                            f_event->setReceivedPort(
                                    frame->par("received_port"));
                            f_event->setMember(frame->getMembership_new());
                            f_event->setPcfType(frame->getType());
                            //f_event->setAction_time(permanence_pit);
                            f_event->setTimer(permanence_delay);
                            f_event->setDestinationGate(
                                    sm->gate("schedulerIn"));
                            f_event->setIntegrationCycle(
                                    frame->getIntegration_cycle());
                            f_event->setSchedulingPriority(2);

                            tteScheduler->registerEvent(f_event);

                            //save the event /we have to cancel and delete the events later/
                            e_container->insert(
                                    make_pair(permanence_pit, f_event));

                        } //int_cycle

                    } else {
                        ev << "DEBUG: SM_WAIT_4_CYCLE_START_CS NO REPLACE" << endl;
                    }

                } else {

                    FrameEvent *f_event = new FrameEvent("IN_FRAME",
                            TIMER_EVENT);
                    f_event->setReceivedPort(
                            frame->par("received_port"));
                    f_event->setMember(frame->getMembership_new());
                    f_event->setPcfType(frame->getType());

                    f_event->setTimer(permanence_delay);
                    f_event->setDestinationGate(sm->gate("schedulerIn"));
                    f_event->setIntegrationCycle(frame->getIntegration_cycle());

                    f_event->setSchedulingPriority(2);

                    tteScheduler->registerEvent(f_event);

                    //save the event /we have to cancel and delete the events later/
                    e_container->insert(make_pair(permanence_pit, f_event));

                } //frame not found

                delete frame;

            } else {
				ev << "UNKNOWN PCF FRAME->TYPE: " << frame->getType() << endl;
			}

			delete frame;

		} //syncDomain && syncPriority

	} //RCin

	if (message->arrivedOn("schedulerIn")) {
		//local timer expired
		//if(local_timer==true){
		if (string(message->getName()).compare("ASYNCHRON") == 0) {

			//local_clock=0;

			local_integration_cycle =
					sm->par("cv_local_integration_cycle");
			//local_sync_membership=1; set the own bit
			local_sync_membership = 0;
			local_sync_membership |= (1 << ownBit);

			local_async_membership = 0;
			local_async_membership_r = 0;
			local_async_membership_f = 0;

			tteScheduler->registerEvent(event1);
			tteScheduler->registerEvent(event4);
			tteScheduler->registerEvent(event2);
			tteScheduler->registerEvent(event5);



			tteScheduler->clockCorrection(tteScheduler->getTicks());

			new (this) SM_TENTATIVE_SYNC();
			return;

		}

		if (string(message->getName()).compare("FRAME") == 0) {
			//pcf frame becomes permanent

			//get the PCF Frame
			FrameEvent *e = dynamic_cast<FrameEvent*>(message);

			if (e->getPcfType() == CS_FRAME) {

				tteScheduler->unregisterEvent(event);

				//event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
				duration = sm->par("cs_offset");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());
				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				delete e;

				new (this) SM_FLOOD();
				return;
			} //CS_FRAME

			if (e->getPcfType() == CA_FRAME) {

				tteScheduler->unregisterEvent(event);

				//event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
				duration = sm->par("ca_offset");

				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				//local_sync_membership=1; set the own bit
				local_sync_membership = 0;
				local_sync_membership |= (1 << ownBit);

				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				delete e;

				new (this) SM_WAIT_4_CYCLE_START_CS();
				return;
			}

			delete e;

		} //pcf frame becomes permanent

		if (string(message->getName()).compare("IN_FRAME") == 0) {


		    FrameEvent *e = dynamic_cast<FrameEvent*>(message);
		            delete e;

		   uint64_t ppt=tteScheduler->getTotalTicks();

           if (e_container->find(ppt) != e_container->end()) {

                                   e_container->erase(ppt);
                               }


		            return;
		        }
	} //schedulerIn

}

SM_TENTATIVE_SYNC::SM_TENTATIVE_SYNC() {

	//cout<<"Enter->SM_TENTATIVE_SYNC \n"<<endl;
	sm->getDisplayString().setTagArg("i", 1, "blue");
	sm->bubble("SM_TENTATIVE_SYNC");

	ev << "SM_TENTATIVE_SYNC MEMBER " << ownBit << endl;
	//local_clock==smc_async_eval_pit;
	//Async_Clique_Detektion();
	//Relative_Clique_Detection();

	//if(local_clock==0)
	//send(IN_FRAME);

	//local_clock==smc_sync_eval_pit;
	//Sync_Clique_Detektion();
	//stable_cycle_counter++;

	//local_clock==smc_clock_corr_pit;
	//local_clock=local_clock+clock_corr;

}
void SM_TENTATIVE_SYNC::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *frame = dynamic_cast<PCFrame *>(message);

		if ((frame->getSync_domain() == syncDomain)
				&& (frame->getSync_priority() == syncPriority)) {

			if ((transparentClockToTicks(frame->getTransparent_clock(),
					tteScheduler->par("tick").doubleValue())
					+ (tteScheduler->getTotalTicks()
							- frame->par("received_total").intValue())
					> max_transmission_delay)) {

				ev
						<< "WARNING: SM_TENTATIVE_SYNC : max_transmission_delay < frame->getTransparent_clock() :"
						<< endl;
			}



			//calculate permanence pit
			uint64_t permanence_delay =
					max_transmission_delay
							- (transparentClockToTicks(
									frame->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
									+ (tteScheduler->getTotalTicks()
											- frame->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			//save the event
			if (frame->getType() == CA_FRAME) {

				//create and register the event for the permanence pit
				FrameEvent *f_event = new FrameEvent("FRAME", TIMER_EVENT);

				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());
				f_event->setIntegrationCycle(frame->getIntegration_cycle());
				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sm->gate("schedulerIn"));

				f_event->setSchedulingPriority(1);

				tteScheduler->registerEvent(f_event);

			} //CA_FRAME

			if (frame->getType() == IN_FRAME) {

				FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

				f_event->setReceivedPort(
						frame->par("received_port"));
				f_event->setPcfType(frame->getType());
				f_event->setMember(frame->getMembership_new());

				f_event->setTimer(permanence_delay);
				f_event->setDestinationGate(sm->gate("schedulerIn"));
				f_event->setIntegrationCycle(frame->getIntegration_cycle());
				f_event->setSchedulingPriority(2);

				tteScheduler->registerEvent(f_event);

				e_container->insert(
						pair<uint64_t, FrameEvent *>(permanence_pit, f_event));

			} //IN_FRAME

			delete frame;

		} else {

			ev << "DEBUG: TENTATIVE_SYNC: FRAME ERROR"
					<< "wrong domain or priority" << endl;

		} //sync_priority, sync_domain

	} //gate RCin (PCF FRAME)

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			if (evt->getPcfType() == CA_FRAME) {

				//get the PCF Frame

				//event=new SchedulerTimerEvent("ASYNCHRON",TIMER_EVENT);
				duration = sm->par("ca_offset");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_sync_membership = local_sync_membership | (1 << ownBit);
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;
				stable_cycle_counter = 0;

				clock_stack->clear();

				if (event1->isScheduled()) {
					tteScheduler->unregisterEvent(event1);
				}
				if (event2->isScheduled()) {
					tteScheduler->unregisterEvent(event2);
				}
				if (event3->isScheduled()) {
					tteScheduler->unregisterEvent(event3);
				}
				if (event4->isScheduled()) {
					tteScheduler->unregisterEvent(event4);
				}
				if (event5->isScheduled()) {
					tteScheduler->unregisterEvent(event5);
				}

				delete evt;

				new (this) SM_WAIT_4_CYCLE_START_CS();
				return;
			}

		delete evt;
		return;

		} //FRAME

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			if (evt->getPcfType() == IN_FRAME) {

				uint32_t received_port = evt->getReceivedPort();
				uint64_t int_cycle = evt->getIntegrationCycle();
				uint64_t permanence_pit = tteScheduler->getTicks();
				uint32_t membership = evt->getMember();

				if (int_cycle == local_integration_cycle) {

					if (inSchedule(permanence_pit,
							sm->par("smc_scheduled_receive_pit"),
							sm->par("acceptance_window"))) {

						if (getValue(membership, 32)
								>= (sm->par("max_pcf_membership").intValue()
										- MembershipAcceptanceRange)
								&& (getValue(membership, 32)
										<= (unsigned int)sm->par("max_pcf_membership"))) {

							uint32_t key_ = getValue(membership, 32);

							map<uint32_t, pair<uint32_t, uint64_t> >::iterator itr =
									clock_stack->find(received_port);

							if (itr == clock_stack->end()) {

								clock_stack->insert(
										pair<uint32_t, pair<uint32_t, uint64_t> >(
												received_port,
												pair<uint32_t, uint64_t>(key_,
														permanence_pit)));

							} else {

								if (key_ > itr->second.first) {

									itr->second.first = key_;
									itr->second.second = permanence_pit;

								} else if (key_ == itr->second.first) {

									if (permanence_pit > itr->second.second) {
										itr->second.second = permanence_pit;
									}

								} //membership equal

							} //found

						} //faulty sync master to be tolerated

					} else { //out of Schedule -> permanence pit out of bounds

						//update local_async_membership
						local_async_membership_r = local_async_membership_r
								| (membership);
						local_async_membership_f = local_async_membership_f
								| (membership);
						//
						sm->bubble(
								"out of Schedule -> permanence pit out of bounds");
						//write to log
						ev
								<< "DEBUG: TENTATIVE_SYNC: permanence point in time(out of schedule)->"
								<< permanence_pit << ownBit << endl;
					} //inSchedule

				} else { //out of Schedule -> wrong integration cycle

					//update local_async_membership

					local_async_membership_r = local_async_membership_r
							| (membership);
					local_async_membership_f = local_async_membership_f
							| (membership);

					sm->bubble("out of Schedule -> wrong integration cycle");

					ev << "DEBUG: SM_TENTATIVE_SYNC:" << ownBit << endl;
					ev
							<< "DEBUG: SM_TENTATIVE_SYNC: permanence point in time( wrong integration cycle)->"
							<< permanence_pit << endl;
					ev << "DEBUG: SM_TENTATIVE_SYNC: local_integration_cycle->"
							<< local_integration_cycle << endl;
					ev << "DEBUG: SM_TENTATIVE_SYNC: FRAME integration_cycle->"
							<< int_cycle << endl;

				} //local_integration_cycle

				uint64_t ppt = tteScheduler->getTotalTicks();

				if (e_container->find(ppt) != e_container->end()) {

					e_container->erase(ppt);

				}

				delete evt;
				return;
			}
		} //IN FRAME Event

		if (string(message->getName()).compare("smc_async_eval_pit") == 0) {

			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}

			if ((getValue(local_async_membership, 32)
					>= (unsigned int)sm->par("sm_tentative_sync_threshold_async"))
					|| (getValue(local_async_membership, 32)
							>= local_sync_membership)) {

				//event=new SchedulerTimerEvent("ASYNCHRON",TIMER_EVENT);
				duration = sm->par("sm_restart_timeout_async");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;
				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event2);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				clock_stack->clear();

				new (this) SM_UNSYNC();

				return;
			} //smc_async_eval_pit

			if (!((getValue(local_async_membership, 32)
					>= (unsigned int)sm->par("sm_tentative_sync_threshold_async"))
					|| (getValue(local_async_membership, 32)
							>= local_sync_membership))) {

				//send(IN_FRAME);

				PCFrame *p = new PCFrame("IN_FRAME");

				cMsgPar *par = &p->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				p->setType(IN_FRAME);
				p->setTransparent_clock(0);
				p->setMembership_new(1 << ownBit);
				p->setSync_domain(2);
				p->setSync_priority(4);
				p->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				p->setIntegration_cycle(local_integration_cycle + 1);
				//Padding
				if (p->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					p->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}
				p->setDisplayString("b=15,15,rect,white,red,5");

				sm->sendDirect(
						p,
						sm->getParentModule()->getSubmodule("vl_pcf_out_IN")->gate(
								"in"));



				tteScheduler->registerEvent(event1, true);

			}
		} //sm_dispatch_pit

		if (string(message->getName()).compare("smc_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (sm->par("max_integration_cycles").intValue());

			tteScheduler->registerEvent(event4, true);
		}

		if (string(message->getName()).compare("smc_sync_eval_pit") == 0) {

			if (!clock_stack->empty()) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();

				if (clock_stack->size() == 1) {

					local_sync_membership = iter->second.first;

				} else {
					local_sync_membership = iter->second.first;

					while (iter != clock_stack->end()) {

						if (iter->second.first > local_sync_membership) {
							local_sync_membership = iter->second.first;
						}
						iter++;
					} //while

				}


			} else {

				//no "in Schedule" frame has been received during the acceptance window

				local_sync_membership = 0;

			}

			if (local_sync_membership
					< (unsigned int)sm->par("sm_tentative_sync_threshold_sync")) {

				duration = sm->par("sm_restart_timeout_async");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;
				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				clock_stack->clear();

				new (this) SM_UNSYNC();

				return;
			}

			tteScheduler->registerEvent(event2, true);
			tteScheduler->registerEvent(event3);

			if (((local_sync_membership
					>= (unsigned int)sm->par("sm_tentative_sync_threshold_sync"))
					&& (local_sync_membership
							< (unsigned int)sm->par("sm_tentative_to_sync_thrld")))) {

				stable_cycle_counter++;
				//stable_cycle_counter+1 ??

				new (this) SM_TENTATIVE_SYNC();
				return;
			}

			if ((local_sync_membership
					>= (unsigned int)sm->par("sm_tentative_sync_threshold_sync"))) {

				stable_cycle_counter = 0;

				new (this) SM_SYNC();
				return;
			}

			if (((local_sync_membership
					>= (unsigned int)sm->par("sm_tentative_sync_threshold_sync"))
					&& (local_sync_membership
							< (unsigned int)sm->par("sm_tentative_to_sync_thrld")))
					&& ((stable_cycle_counter
							>= (unsigned int)sm->par("num_stable_cycles"))
							&& (sm->par("sm_tent_to_stable_enabled").boolValue()))) {

				stable_cycle_counter = 0;

				new (this) SM_STABLE();
				return;
			}

		} //smc_sync_eval

		if (string(message->getName()).compare("smc_clock_corr_pit") == 0) {



			if (clock_stack->empty()) {

				sm->bubble("TEN_SYNC clock_stack->empty");

			} else if (clock_stack->size() == 1) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();
				clock_corr = iter->second.second
						- sm->par("smc_scheduled_receive_pit").intValue();
				tteScheduler->clockCorrection(clock_corr);
				//outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sm->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}
				//clear for the next cycle
				// container->clear();
				clock_stack->clear();
				//
				//new (this) SC_SYNC();
				return;
			} else {
				//average method
				int64_t temp = 0;
				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();

				while (iter != clock_stack->end()) {

					temp =
							temp
									+ (iter->second.second
											- sm->par(
													"smc_scheduled_receive_pit").intValue());

					iter++;
				}

				clock_corr = (double) (temp) / (double) (clock_stack->size());

				tteScheduler->clockCorrection(clock_corr);

				//outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sm->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}

				clock_stack->clear();

				return;

			}

		}

		if (string(message->getName()).compare("smc_async_up") == 0) {

			if ((local_integration_cycle % 2) == 0) {

				local_async_membership_f = 0;

			} else {

				local_async_membership_r = 0;

			}

			if (!event5->isScheduled()) {

				tteScheduler->registerEvent(event5, true);

			}
		}

	}
}
SM_WAIT_4_CYCLE_START::SM_WAIT_4_CYCLE_START() {

	sm->getDisplayString().setTagArg("i", 1, "magenta");
	sm->bubble("SM_WAIT_4_CYCLE_START");

	//Enter

	tteScheduler->registerEvent(event);

}

void SM_WAIT_4_CYCLE_START::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//SM/SC makes all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);





		if ((pf->getSync_domain() == syncDomain)
				&& (pf->getSync_priority() == syncPriority)) {

			if ((transparentClockToTicks(pf->getTransparent_clock(),
					tteScheduler->par("tick").doubleValue())
					+ (tteScheduler->getTotalTicks()
							- pf->par("received_total").intValue())
					> max_transmission_delay)) {

				ev
						<< "WARNING: SM_WAIT_4_CYCLE_START: pkt->getTransparent_clock() > max_transmission_delay "
						<< endl;

			}

			//calculate permanence pit
			uint64_t permanence_delay = max_transmission_delay
					- (transparentClockToTicks(pf->getTransparent_clock(),
							tteScheduler->par("tick").doubleValue())
							+ (tteScheduler->getTotalTicks()
									- pf->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			if (pf->getType() == IN_FRAME) {

				if (e_container->find(permanence_pit) != e_container->end()) {

					if (getValue(pf->getMembership_new(), 32)
							> (getValue(
									e_container->find(permanence_pit)->second->getMember(),
									32))) {

						ev
								<< "DEBUG: SM_WAIT_4_CYCLE_START REPLACE membership new value"
								<< pf->getMembership_new() << endl;
						ev
								<< "DEBUG: SM_WAIT_4_CYCLE_START membership new number of SM "
								<< getValue(pf->getMembership_new(), 32)
								<< endl;

						tteScheduler->unregisterEvent(
								e_container->find(permanence_pit)->second);
						sm->cancelAndDelete(
								e_container->find(permanence_pit)->second);
						e_container->erase(permanence_pit);

						FrameEvent *f_event = new FrameEvent("IN_FRAME",
								TIMER_EVENT);

						f_event->setReceivedPort(
								pf->par("received_port"));
						f_event->setMember(pf->getMembership_new());
						f_event->setPcfType(pf->getType());
						//f_event->setAction_time(permanence_pit);
						f_event->setTimer(permanence_delay);
						f_event->setDestinationGate(sm->gate("schedulerIn"));
						f_event->setIntegrationCycle(
								pf->getIntegration_cycle());
						f_event->setSchedulingPriority(2);

						tteScheduler->registerEvent(f_event);

						//save the event /we have to cancel and delete the events later/
						e_container->insert(make_pair(permanence_pit, f_event));

					} else if (getValue(pf->getMembership_new(), 32)
							== (getValue(
									e_container->find(permanence_pit)->second->getMember(),
									32))) {

						if (pf->getIntegration_cycle()
								> e_container->find(permanence_pit)->second->getIntegrationCycle()) {

							ev
									<< "DEBUG: SM_WAIT_4_CYCLE_START REPLACE membership new value"
									<< pf->getMembership_new() << endl;
							ev
									<< "DEBUG: SM_WAIT_4_CYCLE_START membership new number of SM "
									<< getValue(pf->getMembership_new(), 32)
									<< endl;

							tteScheduler->unregisterEvent(
									e_container->find(permanence_pit)->second);
							sm->cancelAndDelete(
									e_container->find(permanence_pit)->second);
							e_container->erase(permanence_pit);

							FrameEvent *f_event = new FrameEvent("IN_FRAME",
									TIMER_EVENT);
							f_event->setReceivedPort(
									pf->par("received_port"));
							f_event->setMember(pf->getMembership_new());
							f_event->setPcfType(pf->getType());
							//f_event->setAction_time(permanence_pit);
							f_event->setTimer(permanence_delay);
							f_event->setDestinationGate(
									sm->gate("schedulerIn"));
							f_event->setIntegrationCycle(
									pf->getIntegration_cycle());
							f_event->setSchedulingPriority(2);

							tteScheduler->registerEvent(f_event);

							//save the event /we have to cancel and delete the events later/
							e_container->insert(
									make_pair(permanence_pit, f_event));

						} //int_cycle

					} else {
						ev << "DEBUG: SM_WAIT_4_CYCLE_START NO REPLACE" << endl;
					}

				} else {

					FrameEvent *f_event = new FrameEvent("IN_FRAME",
							TIMER_EVENT);

					f_event->setReceivedPort(
							pf->par("received_port"));
					f_event->setMember(pf->getMembership_new());
					f_event->setPcfType(pf->getType());
					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					//f_event->setAction_time(permanence_delay);
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(sm->gate("schedulerIn"));
					f_event->setIntegrationCycle(pf->getIntegration_cycle());

					f_event->setSchedulingPriority(2);

					tteScheduler->registerEvent(f_event);

					//save the event /we have to cancel and delete the events later/
					e_container->insert(make_pair(permanence_pit, f_event));

					//

				} //frame not found

				delete pf;

			} //IN_FRAME

		} //syncPriority && syncDomain

	} //RCin

	//
	if (message->arrivedOn("schedulerIn")) {
		//local timer expired
		if (string(message->getName()).compare("ASYNCHRON")) {
			//Actually we don't need this variable
			round_completed = true;

			if ((local_sync_membership == 0) && (round_completed)) {

				tteScheduler->unregisterEvent(event);

				duration = sm->par("sm_restart_timeout_sync");
				event->setSchedulingPriority(3);
				event->setTimer(duration);
				event->setDestinationGate(sm->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;

				new (this) SM_UNSYNC();
				return;
			}

			if ((local_sync_membership > 0) && (round_completed)) {

				int64_t temp =
						(int64_t)(
								tteScheduler->getTicks()
										- sm->par("smc_scheduled_receive_pit").intValue());
				//local_clock=smc_scheduled_receive_pit;
				tteScheduler->clockCorrection(temp);

				local_integration_cycle++;

				tteScheduler->registerEvent(event1, true);

				tteScheduler->registerEvent(event2);

				tteScheduler->registerEvent(event4);

				tteScheduler->registerEvent(event5);
				//tteScheduler->registerEvent(event3);

				//clearForTheNextState();

				new (this) SM_TENTATIVE_SYNC();
				return;
			}

		}

		if (string(message->getName()).compare("IN_FRAME") == 0) {
			//pcf frame becomes permanent

			FrameEvent *e = dynamic_cast<FrameEvent*>(message);
			//get the PCF Frame

			if (e->getPcfType() == IN_FRAME) {

				if ((e->getIntegrationCycle() != local_integration_cycle)
						&& (!(inSchedule(
								tteScheduler->getTicks(),
								sm->par("smc_scheduled_receive_pit"),
								sm->par("acceptance_window"))))) {

					if (getValue(e->getMember(), 32)
							>= (unsigned int)sm->par("sm_wait_threshold_async")) {

						tteScheduler->unregisterEvent(event);

						duration = sm->par("int_cycle_duration").intValue()
								+ sm->par("acceptance_window").intValue() / 2;
						//event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
						event->setSchedulingPriority(3);
						event->setTimer(duration);
						event->setDestinationGate(sm->gate("schedulerIn"));

						int64_t temp =
								(int64_t)(
										tteScheduler->getTicks()
												- sm->par(
														"smc_scheduled_receive_pit").intValue());
						//local_clock=smc_scheduled_receive_pit;
						tteScheduler->clockCorrection(temp);

						local_integration_cycle = e->getIntegrationCycle();
						local_sync_membership = getValue(e->getMember(), 32);
						local_async_membership = 0;
						round_completed = false;

						uint64_t ppt = tteScheduler->getTotalTicks();

						if (e_container->find(ppt) != e_container->end()) {

							e_container->erase(ppt);
						}
						delete e;

						new (this) SM_WAIT_4_CYCLE_START();
						return;
					} //threshold

					delete e;
					return;

				} //in schedule

				delete e;
				return;
			} //IN Frame

			delete e;
			return;
		} //pcf becomes permanent
		if (string(message->getName()).compare("FRAME") == 0){

		    FrameEvent *e = dynamic_cast<FrameEvent*>(message);
		    delete e;
		}
	} //schedulerIn
}

} //namespace
