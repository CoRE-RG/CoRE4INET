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
 * SCStates.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: Lazar Todorov
 */

#include "CoRE4INET_SCStates.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"

#include "omnetpp.h"
#include <string>
#include "CoRE4INET_SC.h"
#include "SynchronisationEvents_m.h"
#include <algorithm>
#include "core4inet/utilities/HelperFunctions.h"
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"

namespace CoRE4INET {

SC_INIT::SC_INIT(SC *sc_ref, FILE *f) {
	sc = sc_ref;
	fp = f;
	//fp=fopen("/home/pcman/from_thinkpad/TTEthernetModel/examples/SICM_TEST_AS6802_sync/results/client.txt","w+");

	if (sc->par("read").boolValue()) {
		values = new vector<int>(1200000);

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

	} //read

	outVector = new cOutVector("client");

	syncDomainId = sc->par("syncDomain");
	local_current_sync_priority = sc->par("syncPriority");

	MembershipAcceptanceRange =
			sc->par("MembershipAcceptanceRange");

	local_timer = false;
	flood_receive = false;
	closed_window = false;
	round_completed = false;

	first_sync_cycle = false;

	local_clock = false;
	local_sync_membership = 0;
	local_async_membership = 0;
	//The monitoring intervals are longer than the integration_cycle_duration, requiring two variables  local_async_membership_f,  local_async_membership_r
	local_async_membership_f = 0;
	local_async_membership_r = 0;

	local_integration_cycle = 0;
	clock_corr = 0;
	stable_cycle_counter = 0;
	duration = 0;
	powerUp = true;
	max_transmission_delay = sc->par("max_transmission_delay");

	event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
	event->setSchedulingPriority(3);

	clock_stack = new map<uint32, pair<uint32, uint64> >;

	//NOTE: A Time-Triggered Ethernet synchronization master makes all PCFs permanent before usage.

	//container for event's used to signal the "permanence pit" per frame
	e_container = new multimap<uint64_t, FrameEvent *>;

	//container for container for PCF frames delayed for permanence pit in SYNC/STABLE state;  key = membership_new, value = PCFrame *
	//sync_container = new multimap<unsigned int, PCFrame* >;

	tteScheduler = (TTEScheduler*) sc->getParentModule()->getSubmodule("scheduler");

        event1 = new SchedulerActionTimeEvent("smc_async_eval_pit",
                ACTION_TIME_EVENT);
        //sm_dispatch_pit=smc_async_eval_pit
        // event1->setAction_time(sc->par("smc_async_eval_pit").intValue() - sc->par("smc_async_eval_pit").intValue());
        event1->setAction_time(0);
        event1->setDestinationGate(sc->gate("schedulerIn"));
        event1->setSchedulingPriority(4);

        event2 = new SchedulerActionTimeEvent("smc_sync_eval_pit",
                ACTION_TIME_EVENT);

        event2->setAction_time(
                sc->par("smc_sync_eval_pit"));
        event2->setDestinationGate(sc->gate("schedulerIn"));
        event2->setSchedulingPriority(4);

        event3 = new SchedulerActionTimeEvent("smc_clock_corr_pit",
                ACTION_TIME_EVENT);

        event3->setAction_time(sc->par("smc_clock_corr_pit"));
        event3->setDestinationGate(sc->gate("schedulerIn"));
        event3->setSchedulingPriority(4);

        //event4 is used to update/increment/ the "local_integration_cycle" value
        event4 = new SchedulerActionTimeEvent("smc_inc_pit",
                ACTION_TIME_EVENT);
        event4->setAction_time(
                sc->par("smc_scheduled_receive_pit").intValue()
                        - sc->par("precision").intValue());
        event4->setDestinationGate(sc->gate("schedulerIn"));
        event4->setSchedulingPriority(3);

        event5 = new SchedulerActionTimeEvent("smc_async_up",
                ACTION_TIME_EVENT);
        event5->setAction_time(
                (unsigned int) (sc->par("int_cycle_duration").intValue()
                        - sc->par("acceptance_window").intValue()));
        event5->setDestinationGate(sc->gate("schedulerIn"));
        event5->setSchedulingPriority(4);


	    if (sc->par("read").boolValue()) {

		event3 = new SchedulerActionTimeEvent("smc_clock_corr_pit",
				ACTION_TIME_EVENT);

		event3->setAction_time(sc->par("smc_clock_corr_pit"));
		event3->setDestinationGate(sc->gate("schedulerIn"));
		event3->setSchedulingPriority(4);

		//event4 is used to update/increment/ the "local_integration_cycle" value
		event4 = new SchedulerActionTimeEvent("smc_inc_pit", ACTION_TIME_EVENT);
		event4->setAction_time(
				sc->par("smc_scheduled_receive_pit").intValue()
						- sc->par("precision").intValue());
		event4->setDestinationGate(sc->gate("schedulerIn"));
		event4->setSchedulingPriority(3);

		tteScheduler->registerEvent(event4);
		tteScheduler->registerEvent(event3);
		new (this) SC_PSEUDOSYNC();
		return;
	}

	new (this) SC_INTEGRATE();
	return;
}

void SC_INIT::handleMessage(cMessage *message) {
}

SC_PSEUDOSYNC::SC_PSEUDOSYNC() {

	ev << "ENTER SC_PSEUDOSYNC" << endl;
}

void SC_PSEUDOSYNC::handleMessage(cMessage *message) {

	if (string(message->getName()).compare("smc_inc_pit") == 0) {

		ev << "DEBUG  SC_PSEUDOSYNC: local_integration_cycle before "
				<< local_integration_cycle << endl;

		local_integration_cycle = (local_integration_cycle + 1)
				% (sc->par("max_integration_cycles").intValue());

		ev << "DEBUG SC_PSEUDOSYNC: local_integration_cycle after "
				<< local_integration_cycle << endl;

		tteScheduler->registerEvent(event4, true);
		return;
	}

	if (string(message->getName()).compare("smc_clock_corr_pit") == 0) {

		ev << "SC_PSEUDOSYNC clock correction" << endl;

		tteScheduler->clockCorrection(values->at(counter++));

		tteScheduler->registerEvent(event3, true);

		return;
	}

}

SC_INTEGRATE::SC_INTEGRATE() {

	ev << "SC_INTEGRATE" << endl;
	sc->getDisplayString().setTagArg("i", 1, "red");
	sc->bubble("INTEGRATE");

	if (powerUp) {

		event->setTimer(sc->par("sm_listen_timeout"));
		event->setDestinationGate(sc->gate("schedulerIn"));
		event->setSchedulingPriority(3);

		powerUp = false;
	}

	timeOutExpierd = false;
	tteScheduler->registerEvent(event); //timer start

	//ev << " DEBUG: SC_INTEGRATE::event->getTimer "<< event->getTimer() << endl;
	//local_timer=false;
	//TW(sm_listen_timeout);
	//local_timer=true;

}

void SC_INTEGRATE::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {
		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//SM/SC makes all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if ((pf->getSync_domain() == syncDomainId)
				&& (pf->getSync_priority() == local_current_sync_priority)) {

			if ((transparentClockToTicks(pf->getTransparent_clock(),
					tteScheduler->par("tick").doubleValue())
					+ (tteScheduler->getTotalTicks()
							- pf->par("received_total").intValue())
					> max_transmission_delay)) {

				ev
						<< "WARNING: INTEGRATE: pkt->getTransparent_clock() > max_transmission_delay "
						<< endl;

			}

			if (pf->getType() == IN_FRAME) {

				ev << "DEBUG:SC INTEGRATE membership new value"
						<< pf->getMembership_new() << endl;
				ev << "DEBUG:SC INTEGRATE membership new number of SM"
						<< getValue(pf->getMembership_new(), 32) << endl;

				uint64_t permanence_delay =
						max_transmission_delay
								- (transparentClockToTicks(
										pf->getTransparent_clock(),
										tteScheduler->par("tick").doubleValue())
										+ (tteScheduler->getTotalTicks()
												- pf->par("received_total").intValue()));
				uint64_t permanence_pit = tteScheduler->getTotalTicks()
						+ permanence_delay;

				if (e_container->find(permanence_pit) != e_container->end()) {

					if (getValue(pf->getMembership_new(), 32)
							> (getValue(
									e_container->find(permanence_pit)->second->getMember(),
									32))) {

						ev << "DEBUG:SC INTEGRATE REPLACE membership new value"
								<< pf->getMembership_new() << endl;
						ev << "DEBUG:SC INTEGRATE membership new number of SM "
								<< getValue(pf->getMembership_new(), 32)
								<< endl;

						tteScheduler->unregisterEvent(
								e_container->find(permanence_pit)->second);
						sc->cancelAndDelete(
								e_container->find(permanence_pit)->second);
						e_container->erase(permanence_pit);

						FrameEvent *f_event = new FrameEvent("IN_FRAME",
								TIMER_EVENT);
						f_event->setReceivedPort(
								pf->par("received_port"));
						f_event->setPcfType(IN_FRAME);
						f_event->setIntegrationCycle(
								pf->getIntegration_cycle());
						f_event->setMember(pf->getMembership_new());
						f_event->setTimer(permanence_delay);

						f_event->setDestinationGate(sc->gate("schedulerIn"));
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
									<< "DEBUG:SC INTEGRATE REPLACE int_cycle new value"
									<< pf->getIntegration_cycle() << endl;

							tteScheduler->unregisterEvent(
									e_container->find(permanence_pit)->second);
							sc->cancelAndDelete(
									e_container->find(permanence_pit)->second);
							e_container->erase(permanence_pit);

							FrameEvent *f_event = new FrameEvent("IN_FRAME",
									TIMER_EVENT);
							f_event->setReceivedPort(
									pf->par("received_port"));
							f_event->setPcfType(IN_FRAME);
							f_event->setIntegrationCycle(
									pf->getIntegration_cycle());
							f_event->setMember(pf->getMembership_new());

							f_event->setTimer(permanence_delay);
							f_event->setDestinationGate(
									sc->gate("schedulerIn"));
							f_event->setSchedulingPriority(2);

							tteScheduler->registerEvent(f_event);

							//save the event /we have to cancel and delete the events later/
							e_container->insert(
									make_pair(permanence_pit, f_event));
						} //int cycle

					} else {

					}

				} else {

					FrameEvent *f_event = new FrameEvent("IN_FRAME",
							TIMER_EVENT);
					f_event->setReceivedPort(
							pf->par("received_port"));
					f_event->setPcfType(IN_FRAME);
					f_event->setMember(pf->getMembership_new());
					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					//f_event->setAction_time(permanence_pit);
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(sc->gate("schedulerIn"));
					f_event->setSchedulingPriority(2);

					tteScheduler->registerEvent(f_event);

					//save the event /we have to cancel and delete the events later/
					e_container->insert(make_pair(permanence_pit, f_event));

					//

				}

				delete pf;
				return;

			} //IN Frame
			ev << "SC DROP PCFrame " << pf->getName() << endl;
			delete pf;
			return;
		} //wrong sync domain or priority
	} //RCin

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("ASYNCHRON") == 0) {

			timeOutExpierd = true;

			return;
		}

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			if (e_container->empty()) {

				ev << "SC_INTEGRATE Container is empty" << endl;

				return;
			}

			FrameEvent *frame_ = dynamic_cast<FrameEvent *>(message);

			int64_t ppt = tteScheduler->getTotalTicks();

						//IN Frame?
			if (frame_->getPcfType() == IN_FRAME) {

				int64_t temp =
						(int64_t)(
								tteScheduler->getTicks()
										- sc->par("smc_scheduled_receive_pit").intValue());
				//local_clock=smc_scheduled_receive_pit;
				tteScheduler->clockCorrection(temp);

				local_integration_cycle = frame_->getIntegrationCycle();
				local_sync_membership = getValue(frame_->getMember(), 32);
				local_async_membership = 0;

				if (local_sync_membership
						>= (unsigned int)sc->par("sc_integrate_to_sync_thrld")) {
					//the synchronous clique detection return false and the device has synchronized to the current set of devices
					//
					if (!timeOutExpierd) {

						tteScheduler->unregisterEvent(event);

					}

					uint32_t tempKey = local_sync_membership;

					//container->insert(pair<uint32_t,uint64_t>(tempKey,tteScheduler->getTicks()));

					clock_stack->insert(
							pair<uint32, pair<uint32, uint64> >(
									frame_->getReceivedPort(),
									pair<uint32, uint64>(tempKey,
											tteScheduler->getTicks())));

					ev
							<< "DEBUG INTEGRATE: inserted value local_sync_membership"
							<< local_sync_membership << endl;


					tteScheduler->registerEvent(event1, true);

					tteScheduler->registerEvent(event2);

					tteScheduler->registerEvent(event4);

					tteScheduler->registerEvent(event5);

					delete frame_;

					if (e_container->find(ppt) != e_container->end()) {

						e_container->erase(ppt);
					}

					new (this) SC_SYNC();
					return;
				}

				delete frame_;

				if (e_container->find(ppt) != e_container->end()) {

					e_container->erase(ppt);
					return;
				}

				delete frame_;

				if (e_container->find(ppt) != e_container->end()) {

					e_container->erase(ppt);

					return;
				} //IN FRAME

			}
		} //schedulerIn

	}
}
SC_SYNC::SC_SYNC() {

	ev << "SC_SYNC" << endl;
	sc->getDisplayString().setTagArg("i", 1, "yellow");
	sc->bubble("SYNC");
}

void SC_SYNC::handleMessage(cMessage *message) {

	ev << "SC_SYNC::handleMessage" << endl;

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);
			uint32_t received_port = evt->getReceivedPort();
			uint64_t int_cycle = evt->getIntegrationCycle();
			uint32_t member = evt->getMember();
			uint64_t permanence_pit = tteScheduler->getTicks();

			if (int_cycle == local_integration_cycle) {

				if (inSchedule(permanence_pit,
						sc->par("smc_scheduled_receive_pit"),
						sc->par("precision"))) {

					if ((unsigned int)getValue(member, 32)
							>= (unsigned int)(sc->par("max_pcf_membership")
									- MembershipAcceptanceRange)
							&& (getValue(member, 32)
									<= (sc->par("max_pcf_membership").intValue()))) {

						uint32_t key_ = getValue(member, 32);

						//container->insert(pair<uint32_t, uint64_t>(key_, permanence_pit));
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

					local_async_membership_f = local_async_membership_f
							| (member);
					local_async_membership_r = local_async_membership_r
							| (member);

					sc->bubble(
							"out of Schedule -> permanence pit out of bounds");
					//write to log
					ev
							<< "DEBUG: SC SYNC: permanence point in time(out of schedule)->"
							<< permanence_pit << endl;
				} //inSchedule

			} else { //out of Schedule -> wrong integration cycle

				//update local_async_membership

				//local_async_membership = local_async_membership | (pcf->getMembership_new());
				local_async_membership_f = local_async_membership_f | (member);
				local_async_membership_r = local_async_membership_r | (member);

				sc->bubble("out of Schedule -> wrong integration cycle");

				ev
						<< "DEBUG:SC SYNC: out of Schedule -> wrong integration cycle: "
						<< int_cycle << endl;

				ev
						<< "DEBUG: SC SYNC: out of Schedule local_integration_cycle->"
						<< local_integration_cycle << endl;
				ev
						<< "DEBUG: SC SYNC: out of Schedule FRAME integration_cycle->"
						<< int_cycle << endl;

			} //local_integration_cycle

			uint64_t ppt = tteScheduler->getTotalTicks();

			delete evt;

			if (e_container->find(ppt) != e_container->end()) {

				e_container->erase(ppt);

			}

			return;

		} //IN_FRAME

		if (string(message->getName()).compare("smc_async_eval_pit") == 0) {

			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}



			if ((getValue(local_async_membership, 32)
					>= sc->par("sm_sync_threshold_async").intValue())) {

				ev << "DEBUG: SYNC: ASYNCHRONUS CLIQUE DETECTION -> TRUE"
						<< endl;
				ev << "DEBUG: SYNC: NEXT STATE INTEGRATE" << endl;

				//event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
				event->setTimer(
						sc->par("sm_restart_timeout_async"));
				event->setDestinationGate(sc->gate("schedulerIn"));
				event->setSchedulingPriority(3);
				//duration=sm_restart_timeout_async;

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				stable_cycle_counter = 0;

				//cancel  the events for the synchronous state before enter the INTEGRATE state
				//tteScheduler->cancelAndDelete(event1);

				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event2);
				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event5);
				tteScheduler->unregisterEvent(event3);



				clock_stack->clear();
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				new (this) SC_INTEGRATE();
				return;
			}

			if ((!(getValue(local_async_membership, 32)
					>= sc->par("sm_sync_threshold_async").intValue()))) {

				tteScheduler->registerEvent(event1, true);

			}
		} //smc_async_eval_pit

		if (string(message->getName()).compare("smc_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (sc->par("max_integration_cycles").intValue());

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

				ev << "DEBUG: STABLE: clock_stack is empty" << endl;

				local_sync_membership = 0;

			}

			int dummy = sc->par("sc_sync_threshold_sync");

			ev << "DEBUG SYNC  smc_sync_eval_pit local_sync_membership"
					<< local_sync_membership << endl;

			ev << "DEBUG SYNC  smc_sync_eval_pit sc_sync_threshold_sync"
					<< dummy << endl;
			ev << "DEBUG: SYNC: local_integration_cycle->"
					<< local_integration_cycle << endl;

			if (local_sync_membership
					< (unsigned int)sc->par("sc_sync_threshold_sync")) {

				event->setTimer(sc->par("sm_restart_timeout_sync"));
				event->setDestinationGate(sc->gate("schedulerIn"));
				event->setSchedulingPriority(3);
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				stable_cycle_counter = 0;

				//cancel  the events for the synchronous state before enter the INTEGRATE State

				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event2);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event5);



				clock_stack->clear();
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				new (this) SC_INTEGRATE();
				return;
			}

			if ((local_sync_membership
					>= (unsigned int)sc->par("sc_sync_threshold_sync"))
					&& (!sc->par("sc_sync_to_stable_enabled").boolValue())) {

				stable_cycle_counter++;

				tteScheduler->registerEvent(event2, true);

				return;
			}

			if ((local_sync_membership
					>= (unsigned int)sc->par("sc_sync_threshold_sync"))
					&& (sc->par("sc_sync_to_stable_enabled").boolValue())
					&& (stable_cycle_counter
							< (unsigned int)sc->par("num_stable_cycles"))) {

				stable_cycle_counter++;

				tteScheduler->registerEvent(event2, true);

				return;
			}

			if ((local_sync_membership
					>= (unsigned int)sc->par("sc_sync_threshold_sync"))
					&& (sc->par("sc_sync_to_stable_enabled").boolValue())
					&& (stable_cycle_counter
							>= (unsigned int)sc->par("num_stable_cycles"))) {

				tteScheduler->registerEvent(event2, true);

				stable_cycle_counter = 0;

				new (this) SC_STABLE();
				return;
			}

		}

		if (string(message->getName()).compare("smc_clock_corr_pit") == 0) {
			ev << "DEBUG SYNC: LOCAL_CLOCK smc_clock_corr_pit"
					<< tteScheduler->getTicks() * 80 << endl;

			if (clock_stack->empty()) {
				sc->bubble("SC_SYNC clock_stack->empty");
			} else if (clock_stack->size() == 1) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();
				clock_corr = iter->second.second
						- sc->par("smc_scheduled_receive_pit");
				tteScheduler->clockCorrection(clock_corr);
				//outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sc->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}
				//clear for the next cycle

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
											- sc->par(
													"smc_scheduled_receive_pit").intValue());

					iter++;
				}

				clock_corr = (double) (temp) / (double) (clock_stack->size());

				ev
						<< "DEBUG: SYNC:clock_corr_pit /more than one/ clock correction: "
						<< clock_corr << endl;

				tteScheduler->clockCorrection(clock_corr);

				//for the next cycle
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
			ev << "DEBUG:SYNC smc_async_up local_async_membership_r "
					<< local_async_membership_r << endl;
			ev << "DEBUG:SYNC smc_async_up local_async_membership_f "
					<< local_async_membership_f << endl;

			tteScheduler->registerEvent(event5, true);

		}

	} //message->arrivedOn("schedulerIn")

	if (message->arrivedOn("RCin")) {

		//send ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *copy_ = dynamic_cast<PCFrame *>(message);

		if ((copy_->getSync_domain() == syncDomainId)
				&& (copy_->getSync_priority() == local_current_sync_priority)) {

			if ((transparentClockToTicks(copy_->getTransparent_clock(),
					tteScheduler->par("tick").doubleValue())
					+ (tteScheduler->getTotalTicks()
							- copy_->par("received_total").intValue())
					> max_transmission_delay)) {

				ev
						<< "WARNING: SC SYNC: pkt->getTransparent_clock() > max_transmission_delay "
						<< endl;

			}

			if (copy_->getType() == IN_FRAME) {

				//calculate permanence pit
				uint64_t permanence_delay =
						max_transmission_delay
								- (transparentClockToTicks(
										copy_->getTransparent_clock(),
										tteScheduler->par("tick").doubleValue())
										+ (tteScheduler->getTotalTicks()
												- copy_->par("received_total").intValue()));
				uint64_t permanence_pit = tteScheduler->getTotalTicks()
						+ permanence_delay;

				FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);
				f_event->setReceivedPort(
						copy_->par("received_port"));
				f_event->setPcfType(IN_FRAME);
				f_event->setIntegrationCycle(copy_->getIntegration_cycle());
				f_event->setMember(copy_->getMembership_new());
				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sc->gate("schedulerIn"));
				f_event->setSchedulingPriority(2);

				tteScheduler->registerEvent(f_event);

				e_container->insert(
						pair<uint64_t, FrameEvent *>(permanence_pit, f_event));

				delete copy_;
				return;

			} else {

				ev << "ERROR::ONLY IN FRAMES ARE ACCEPTED BY SC "
						<< copy_->getType() << endl;
				ev << "ERROR::UNKNOWN PCF TYPE " << copy_->getType() << endl;

				delete copy_;
				return;

			} //IN_FRAME

		} else {

			sc->bubble("wrong sync domain or sync priority");

			delete copy_;
			return;
		} //sync_domain

		delete (copy_);

	} //RCin

}

SC_STABLE::SC_STABLE() {
	ev << "SC_STABLE" << endl;
	sc->getDisplayString().setTagArg("i", 1, "green");
	sc->bubble("STABLE");

	/*if (!sc->par("read").boolValue()) {
		fprintf(fp, "%s  ", "SC STABLE ");
		fprintf(fp, "%.15f\n", simTime().dbl());
		fprintf(fp, "%ld\n", tteScheduler->getTotalTicks());
	}*/

}

void SC_STABLE::handleMessage(cMessage *message) {
	ev << "SC_STABLE::handleMessage" << endl;

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);
			uint32_t received_port = evt->getReceivedPort();
			uint64_t int_cycle = evt->getIntegrationCycle();
			uint32_t member = evt->getMember();
			uint64_t permanence_pit = tteScheduler->getTicks();

			if (int_cycle == local_integration_cycle) {

				if (inSchedule(permanence_pit,
						sc->par("smc_scheduled_receive_pit"),
						sc->par("precision"))) {

					if ((unsigned int)getValue(member, 32)
							>= (unsigned int)(sc->par("max_pcf_membership")
									- MembershipAcceptanceRange)
							&& (getValue(member, 32)
									<= (sc->par("max_pcf_membership").intValue()))) {

						uint32_t key_ = getValue(member, 32);

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
					//local_async_membership = local_async_membership | (pcf->getMembership_new());
					local_async_membership_f = local_async_membership_f
							| (member);
					local_async_membership_r = local_async_membership_r
							| (member);

					sc->bubble(
							"out of Schedule -> permanence pit out of bounds");
					//write to log
					ev
							<< "DEBUG: SC_STABLE: permanence point in time(out of schedule)->"
							<< permanence_pit << endl;
				} //inSchedule

			} else { //out of Schedule -> wrong integration cycle

				//update local_async_membership

				//local_async_membership = local_async_membership | (pcf->getMembership_new());
				local_async_membership_f = local_async_membership_f | (member);
				local_async_membership_r = local_async_membership_r | (member);

				sc->bubble("out of Schedule -> wrong integration cycle");

				ev
						<< "DEBUG: SC_STABLE: out of Schedule -> wrong integration cycle: "
						<< int_cycle << endl;

				ev
						<< "DEBUG: SC_STABLE: out of Schedule local_integration_cycle->"
						<< local_integration_cycle << endl;
				ev
						<< "DEBUG: SC_STABLE: out of Schedule FRAME integration_cycle->"
						<< int_cycle << endl;

			} //local_integration_cycle

			uint64_t ppt = tteScheduler->getTotalTicks();

			if (e_container->find(ppt) != e_container->end()) {

				//delete e_container->find(ppt)->second;
				e_container->erase(ppt);
				ev << "CLIENT STABLE FRAME EVENT DELETED" << endl;
			}
			delete evt;

			ev << "CLIENT STABLE FRAME EVENT NOT DELETED" << endl;

			ev << "E_CONTAINER size" << e_container->size() << endl;

			return;
		} //IN_FRAME

		if (string(message->getName()).compare("smc_async_eval_pit") == 0) {

			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}

			tteScheduler->registerEvent(event1, true);

			if (getValue(local_async_membership, 32)
					>= sc->par("sc_stable_threshold_async").intValue()) {

				ev << "DEBUG STABLE  smc_async_eval_pit local_sync_membership"
						<< local_sync_membership << endl;
				ev << "DEBUG STABLE  smc_async_eval_pit local_async_membership"
						<< local_async_membership << endl;

				ev << "DEBUG STABLE: LOCAL_CLOCK smc_async_eval_pit"
						<< tteScheduler->getTicks() * 80 << endl;
				ev << "SC_STABLE:: ASYNCHRONUS CLIQUE DETECTION TRUE" << endl;

				//event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
				//duration=sm_restart_timeout_async;
				event->setTimer(
						sc->par("sm_restart_timeout_async"));
				event->setDestinationGate(sc->gate("schedulerIn"));

				//local clock=0
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;
				stable_cycle_counter = 0;

				//cancel  the events for the synchronus state before enter the INTEGRATE State

				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event2);
				tteScheduler->unregisterEvent(event5);
				tteScheduler->unregisterEvent(event3);


				clock_stack->clear();


				new (this) SC_INTEGRATE();
				return;
			} //asynchronus detection
		} //smc_async_eval_pit

		if (string(message->getName()).compare("smc_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (sc->par("max_integration_cycles").intValue());

			tteScheduler->registerEvent(event4, true);
		}

		if (string(message->getName()).compare("smc_sync_eval_pit") == 0) {
			tteScheduler->registerEvent(event3);

			/*Upon reaching the smc_sync_eval_pit or cm_sync_eval_pit, each device will update local_sync_membership. The device
			 will set local_sync_membership S(i.e., it will select the pcf_membership_new with the highest number of bits set from the
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

				ev << "DEBUG: STABLE: clock_stack is empty" << endl;

				local_sync_membership = 0;

			}

			if ((local_sync_membership
					< (unsigned int)sc->par("sc_stable_threshold_sync"))
					&& (stable_cycle_counter
							< (unsigned int)sc->par("num_unstable_cycles"))) {

				stable_cycle_counter++;

				tteScheduler->registerEvent(event2, true);

				return;
			}

			if ((local_sync_membership
					< (unsigned int)sc->par("sc_stable_threshold_sync"))
					&& (stable_cycle_counter
							>= (unsigned int)sc->par("num_unstable_cycles"))) {

				ev << "SC_STABLE:: SYNCHRONUS CLIQUE DETECTION TRUE" << endl;

				event->setSchedulingPriority(3);
				event->setTimer(sc->par("sm_restart_timeout_sync"));
				event->setDestinationGate(sc->gate("schedulerIn"));

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;

				stable_cycle_counter = 0;

				//cancel  the events for the synchronus state's before enter the INTEGRATE State

				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event1);
				tteScheduler->unregisterEvent(event2);

				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event5);


				clock_stack->clear();

				local_async_membership_r = 0;
				local_async_membership_f = 0;

				new (this) SC_INTEGRATE();
				return;
			}

			if (local_sync_membership
					>= (unsigned int)sc->par("sc_stable_threshold_sync")) {

				stable_cycle_counter = 0;

				tteScheduler->registerEvent(event2, true);

				return;
			}

		} //smc_sync_eval_pit

		if (string(message->getName()).compare("smc_clock_corr_pit") == 0) {

			ev << "DEBUG STABLE: LOCAL_CLOCK smc_clock_corr_pit"
					<< tteScheduler->getTicks() * 80 << endl;

			if (clock_stack->empty()) {
				sc->bubble("SC_STABLE clock_stack->empty");
			} else if (clock_stack->size() == 1) {

				map<uint32_t, pair<uint32_t, uint64_t> >::iterator iter =
						clock_stack->begin();
				clock_corr = iter->second.second
						- sc->par("smc_scheduled_receive_pit");
				tteScheduler->clockCorrection(clock_corr);
				// outVector->recordWithTimestamp(simTime(),(double)clock_corr);

				if (sc->par("write").boolValue()) {
					fprintf(fp, "%d ", tteScheduler->getCycles());
					fprintf(fp, " %d \n", clock_corr);
				}
				//clear for the next cycle

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
											- sc->par(
													"smc_scheduled_receive_pit").intValue());

					iter++;
				}

				clock_corr = (double) (temp) / (double) (clock_stack->size());

				if (sc->par("write").boolValue()) {
					fprintf(fp, "%d", tteScheduler->getCycles());
					fprintf(fp, "%d \n", clock_corr);
				}
				tteScheduler->clockCorrection(clock_corr);

				ev << "DEBUG: SC STABLE: clock correction " << clock_corr
						<< endl;
				ev << "DEBUG: SC STABLE: Container size more than 1" << endl;

				//for the next cycle
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
			ev << "DEBUG:STABLE smc_async_up local_async_membership_r "
					<< local_async_membership_r << endl;
			ev << "DEBUG:STABLE smc_async_up local_async_membership_f "
					<< local_async_membership_f << endl;

			tteScheduler->registerEvent(event5, true);

		}

	} //SchedulerIn

	if (message->arrivedOn("RCin")) {

		//send ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *copy_ = dynamic_cast<PCFrame *>(message);

		if ((copy_->getSync_domain() == syncDomainId)
				&& (copy_->getSync_priority() == local_current_sync_priority)) {

			if ((transparentClockToTicks(copy_->getTransparent_clock(),
					tteScheduler->par("tick").doubleValue())
					+ (tteScheduler->getTotalTicks()
							- copy_->par("received_total").intValue())
					> max_transmission_delay)) {

				ev
						<< "WARNING: SC STABLE: pkt->getTransparent_clock() > max_transmission_delay "
						<< endl;

			}

			//calculate permanence pit
			uint64_t permanence_delay =
					max_transmission_delay
							- (transparentClockToTicks(
									copy_->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
									+ (tteScheduler->getTotalTicks()
											- copy_->par("received_total").intValue()));
			uint64_t permanence_pit = tteScheduler->getTotalTicks()
					+ permanence_delay;

			if (copy_->getType() == IN_FRAME) {

				FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);
				f_event->setReceivedPort(
						copy_->par("received_port"));
				f_event->setPcfType(IN_FRAME);
				f_event->setIntegrationCycle(copy_->getIntegration_cycle());
				f_event->setMember(copy_->getMembership_new());
				f_event->setTimer(permanence_delay);

				f_event->setDestinationGate(sc->gate("schedulerIn"));
				f_event->setSchedulingPriority(2);

				tteScheduler->registerEvent(f_event);

				e_container->insert(
						pair<uint64_t, FrameEvent *>(permanence_pit, f_event));

			} else {

				ev << "ONLY IN FRAMES ARE ACCEPTED BY SYNC CLIENT "
						<< copy_->getType() << endl;

			} //IN_FRAME

		} else {

			sc->bubble("wrong sync domain or priority");

		} //sync_domain

		delete (copy_);

	} //RCin

} //method

}
