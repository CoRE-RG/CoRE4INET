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
 * HICM.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */

#include "CoRE4INET_HICMStates.h"
#include "CoRE4INET_HICM.h"
#include <string>
#include "omnetpp.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"
#include "SynchronisationEvents_m.h"
#include "core4inet/base/CoRE4INET_Defs.h"
#include <algorithm>
#include "core4inet/utilities/HelperFunctions.h"
#include "SchedulerMessageEvents_m.h"
#include "cmessage.h"
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"
#include "cobject.h"
class HICM;

namespace CoRE4INET {





HI_CM_INIT::HI_CM_INIT(HICM *pointer, FILE *f) {

	//for statistics purpose only
	outVector = new cOutVector("CompMaster");

	hicm = pointer;

	fp = f;

	ev << "MAX SIM TIME " << SimTime().getMaxTime() << endl;

	counter = 0;

	if (hicm->par("read").boolValue()) {

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

	} //read handle

	ctid = hicm->par("id");
	local_timer = false;
	flood_receive = false;
	closed_window = false;
	round_completed = false;

	local_clock = 0;
	local_sync_membership = 0;
	local_async_membership = 0;
	local_async_membership_r = 0;
	local_async_membership_f = 0;
	local_integration_cycle = 0;
	clock_corr = 0;
	stable_cycle_counter = 0;

	duration = hicm->par("cm_listen_timeout");
	max_transmision_delay = hicm->par("max_transmission_delay");

	tteScheduler = (TTEScheduler*) hicm->getParentModule()->getSubmodule(
			"scheduler");

	event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
	event->setSchedulingPriority(3);
	event->setTimer(duration);
	event->setDestinationGate(hicm->gate("schedulerIn"));

	clock_stack = new deque<pair<unsigned int, unsigned int> >;

	compression_stack = new map<unsigned int,
			vector<pair<unsigned int, unsigned int> > *>;

	compressed_frames = new map<long int, PCFrame * >;

	delay_container = new deque<CompressedPIT *>;

	dispatch_delay_container = new deque<DispatchDelay *>;

	//cm_sync_eval_pit
	event2 = new SchedulerActionTimeEvent("cm_sync_eval_pit",
			ACTION_TIME_EVENT);
	event2->setAction_time(hicm->par("cm_sync_eval_pit"));
	event2->setDestinationGate(hicm->gate("schedulerIn"));
	event2->setSchedulingPriority(4);
	//cm_clock_corr_pit
	event3 = new SchedulerActionTimeEvent("cm_clock_corr_pit",
			ACTION_TIME_EVENT);
	event3->setAction_time(
			(unsigned int) hicm->par("cm_clock_corr_pit"));
	event3->setDestinationGate(hicm->gate("schedulerIn"));
	event3->setSchedulingPriority(4);

	//event4 is used to update/increment/ the "local_integration_cycle" value
	event4 = new SchedulerActionTimeEvent("cm_inc_pit", ACTION_TIME_EVENT);
	event4->setAction_time(
			hicm->par("cm_scheduled_pit").intValue()
					- (hicm->par("acceptance_window").intValue() / 2));
	event4->setDestinationGate(hicm->gate("schedulerIn"));
	event4->setSchedulingPriority(1);
	//cm_scheduled_pit
	event5 = new SchedulerActionTimeEvent("cm_scheduled_pit",
			ACTION_TIME_EVENT);
	event5->setAction_time(hicm->par("cm_scheduled_pit"));
	event5->setDestinationGate(hicm->gate("schedulerIn"));
	event5->setSchedulingPriority(4);

	if (hicm->par("read").boolValue()) {

		tteScheduler->registerEvent(event3);
		tteScheduler->registerEvent(event4);

		new (this) HI_CM_PSEUDOSYNC();

		return;
	}

	new (this) HI_CM_INTEGRATE();

}

HI_CM_PSEUDOSYNC::HI_CM_PSEUDOSYNC() {
}

void HI_CM_PSEUDOSYNC::handleMessage(cMessage *message) {

	if (string(message->getName()).compare("cm_clock_corr_pit") == 0) {
		ev << "HI_CM_PSEUDOSYNC clock correction" << endl;

		tteScheduler->clockCorrection(values->at(counter++));

		tteScheduler->registerEvent(event3, true);

		return;

	}

	if (string(message->getName()).compare("cm_inc_pit") == 0) {
		ev << "local_integration_cycle" << local_integration_cycle << endl;

		local_integration_cycle = (local_integration_cycle + 1)
				% (hicm->par("max_integration_cycles").intValue());

		ev << "local_integration_cycle updated" << local_integration_cycle
				<< endl;

		tteScheduler->registerEvent(event4, true);

		return;
	}

}

HI_CM_INTEGRATE::HI_CM_INTEGRATE() {

	//after Power ON  and Initialization READY
	//duration=cm_listen_timeout;
	//Enter
	/*

	 local_timer=false;
	 TW(duration); //TO?
	 local_timer=true;
	 */
	hicm->getDisplayString().setTagArg("i", 1, "red");
	hicm->bubble("CM_INTEGRATE");
	ev << "hicm::current state :: CM_INTEGRATE" << endl;

	tteScheduler->registerEvent(event);

}
void HI_CM_INTEGRATE::handleMessage(cMessage* message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == hicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== hicm->par("syncPriority").intValue()) {

				ev << "DEBUG: HI_CM_INTEGRATE membership new value"
						<< pf->getMembership_new() << endl;
				ev << "DEBUG: HI_CM_INTEGRATE membership new number of SM"
						<< getValue(pf->getMembership_new(), 32) << endl;

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (hicm->par("max_transmission_delay").intValue())) {

					ev
							<< "WARNING: HI_CM_INTEGRATE: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->hicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

					ev << "HI_CM_INTEGRATE CS Frame Arrived:ctid "
							<< pf->getCtID() << "getTotalTicks "
							<< tteScheduler->getTotalTicks() << endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_INTEGRATE CS Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					//cs_container->insert(pair<unsigned int, PCFrame *>(member, pf));

					FrameEvent *f_event = new FrameEvent("CS_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(0);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else if (pf->getType() == CA_FRAME) {

					ev << "HI_CM_INTEGRATE CA Frame Arrived:ctid "
							<< pf->getCtID() << "getTotalTicks "
							<< tteScheduler->getTotalTicks() << endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_INTEGRATE CA Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					FrameEvent *f_event = new FrameEvent("CA_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(1);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else {

					delete pf;

					ev << "DEBUG:  HI_CM_INTEGRATE: UNKNOW FRAME TYPE   "
							<< endl;
					return;
				}

				delete pf;
				return;
			} else {

				ev << "CONFIGURATION ERROR: WRONG SYNC PRIORITY" << endl;
				delete pf;
				return;
			} //sync_priority

		} else {

			ev << "CONFIGURATION ERROR: WRONG SYNC DOMAIN" << endl;

			delete pf;
			return;
		} //sync_domain

	} //gate RCin (PCF FRAME)

	if (message->arrivedOn("schedulerIn")) {

		//cm_listen_timeout expired
		if (string(message->getName()).compare("ASYNCHRON") == 0) {

			duration = 0;

			//local_clock=0;
			tteScheduler->clockCorrection(tteScheduler->getTicks());

			local_integration_cycle = 0;
			local_sync_membership = 0;
			local_async_membership = 0;

			local_async_membership_r = 0;
			local_async_membership_f = 0;

			ev
					<< "HI_CM_INTEGRATE :: ASYNCHRON TIMER EXPIRED, NEXT STATE -> HI_CM_UNSYNC"
					<< endl;

			new (this) HI_CM_UNSYNC();

			return;

		}

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->hicm);
			return;
		}

		if (string(message->getName()).compare("CA_FRAME") == 0) {
			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CA_FRAME) {

				PCFrame *frame = new PCFrame("CA_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CA_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,blue,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}
		} //CA_FRAME

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			delete et;
			ev << "DROP CS FRAME" << endl;
			return;
		}

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			PCFrame *compressedFrame = new PCFrame("IN_FRAME");

			compressedFrame->setCtID(0);
			compressedFrame->setCtMarker(0);
			compressedFrame->setType(IN_FRAME);
			compressedFrame->setTransparent_clock(0);
			compressedFrame->setMembership_new(cp->getMembership_new());
			compressedFrame->setSync_domain(
					hicm->par("syncDomain"));
			compressedFrame->setSync_priority(
					hicm->par("syncPriority"));
			compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
			compressedFrame->setIntegration_cycle(cp->getIntegrationCycle());

			ev << "HI_CM_INTEGRATE:Compressed Frame int cycle "
					<< compressedFrame->getIntegration_cycle() << endl;
			ev << "HI_CM_INTEGRATE:Compressed Frame "
					<< compressedFrame->getMembership_new() << endl;

			//Padding
			if (compressedFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
				compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
			}

			compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

			long int key = compressedFrame->getId();

			compressed_frames->insert(
					make_pair<long int, PCFrame *>(key, compressedFrame));

			local_sync_membership = cp->getMembership_new();
			local_integration_cycle = cp->getIntegrationCycle();
			local_async_membership = 0;
			local_async_membership_r = 0;
			local_async_membership_f = 0;

			DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
			dd->setDestinationGate(hicm->gate("schedulerIn"));
			//dd->setMembership_new(cp->getMembership_new());
			dd->setTimer(hicm->par("dispatch_delay"));
			dd->setSchedulingPriority(3);
			dd->setFrameID(compressedFrame->getId());
			tteScheduler->registerEvent(dd);

			if (getValue(local_sync_membership, 32)
					>= hicm->par("cm_integrate_to_sync_thrld").intValue()) {

				int currentTime = tteScheduler->getTicks();
				//local_clock = cm_sceduled_receive_pit
				tteScheduler->clockCorrection(
						currentTime
								- hicm->par("cm_scheduled_pit").intValue());

				tteScheduler->registerEvent(event2);
				//tteScheduler->registerEvent(event3);
				tteScheduler->registerEvent(event4);
				tteScheduler->registerEvent(event5);

				unsigned int member = cp->getMembership_new();

				unsigned int compressedPit = tteScheduler->getTicks();

				clock_stack->push_front(
						pair<unsigned int, unsigned int>(member,
								compressedPit));

				tteScheduler->unregisterEvent(event);

				delete cp;

				new (this) HI_CM_SYNC();
				return;
			}

			if (getValue(local_sync_membership, 32)
					>= hicm->par("cm_integrate_to_wait_thrld").intValue()
					&& getValue(local_sync_membership, 32)
							< hicm->par("cm_integrate_to_wait_thrld").intValue()) {
				int currentTime = tteScheduler->getTicks();
				//local_clock = cm_sceduled_receive_pit
				tteScheduler->clockCorrection(
						currentTime
								- hicm->par("cm_scheduled_pit").intValue());

				tteScheduler->unregisterEvent(event);

				duration = hicm->par("int_cycle_duration").intValue()
						+ (hicm->par("acceptance_window").intValue() / 2);

				delete cp;

				new (this) HI_CM_WAIT_4_CYCLE_START();

				return;
			}

			delete cp;
			return;
		} //comressed point in time

		if (string(message->getName()).compare("DP") == 0) {

			ev << "DISPATCH DELAY size comp frames" << compressed_frames->size()
					<< endl;

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

			PCFrame *frame=compressed_frames->find(dd->getFrameID())->second;

			cMsgPar *par = &frame->addPar("created_total");

			par->setLongValue(tteScheduler->getTotalTicks());

			hicm->sendDirect(
			        frame->dup(),
					hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
							"in"));
			hicm->sendDirect(
			        frame->dup(),
					hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
							"in"));
			hicm->sendDirect(
			        frame->dup(),
					hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
							"in"));

			//delete frame;

			delete frame;
			compressed_frames->erase(dd->getId());

			delete dd;
			return;
		} //dispatch point in time

	} //schedulerIn

}

void HI_CM_INTEGRATE::compressionFunction(cMessage* message, HICM *hicm) {

	if (message->arrivedOn("RCin")) {

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//IN FRAME ?
		if (pf->getType() == IN_FRAME) {

			FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

			f_event->setMember(pf->getMembership_new());
			f_event->setPcfType(pf->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(hicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

	}

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			unsigned int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (compression_stack->find(int_cycle)
					!= compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's

				compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "HI_CM_INTEGRATE: There is a compression Function with matching integration cycle collecting PCF's "
						<< int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase
				vector<pair<unsigned int, unsigned int> > *PPT = new vector<
						pair<unsigned int, unsigned int> >();

				PPT->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, PPT));

				OWCounter *ow = new OWCounter("OW", TIMER_EVENT);

				ow->setDestinationGate(hicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(hicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "HI_CM_INTEGRATE: Compression Function:Collection Phase started"
						<< endl;
				delete evt;
				return;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:HI_CM_INTEGRATE: ERROR : OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//no new PCF IN frames became permanent during the last observation window
					//stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(hicm->par("max_observation_window")
										- owc->getNumberOfObservationWindow())
										* hicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ hicm->par("calculation_overhead").intValue()
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = hicm->par(
								"calculation_overhead").intValue()
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function HI_CM_INTEGRATE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;

					} else {
						ev
								<< "Compression Function HI_CM_INTEGRATE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function HI_CM_INTEGRATE: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

HI_CM_STABLE::HI_CM_STABLE() {

	hicm->getDisplayString().setTagArg("i", 1, "green");
	hicm->bubble("CM_STABLE");

//	if(local_clock==cm_async_eval_pit){
//		Async_Clique_Detektion();
//
//
//
//
//	if(local_clock==cm_sync_eval_pit){
//	Sync_Clique_Detektion();
//	}
//
//	if(local_clock==cm_clock_corr_pit){
//	local_clock=local_clock+clock_corr;
//	}
}

void HI_CM_STABLE::handleMessage(cMessage* message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == hicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== hicm->par("syncPriority").intValue()) {

				ev << "DEBUG: HI_CM_STABLE membership new value"
						<< pf->getMembership_new() << endl;
				ev << "DEBUG: HI_CM_STABLE membership new number of SM"
						<< getValue(pf->getMembership_new(), 32) << endl;

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (hicm->par("max_transmission_delay").intValue())) {

					ev
							<< "WARNING: HI_CM_STABLE: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->hicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

					ev << "HI_CM_STABLE CS Frame Arrived:ctid " << pf->getCtID()
							<< "getTotalTicks " << tteScheduler->getTotalTicks()
							<< endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_STABLE CS Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					FrameEvent *f_event = new FrameEvent("CS_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(0);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else if (pf->getType() == CA_FRAME) {

					ev << "HI_CM_STABLE CA Frame Arrived:ctid " << pf->getCtID()
							<< "getTotalTicks " << tteScheduler->getTotalTicks()
							<< endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_STABLE CA Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					//cs_container->insert(pair<unsigned int, PCFrame *>(member, pf));

					FrameEvent *f_event = new FrameEvent("CA_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(1);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else {

					delete pf;

					ev << " HI_CM_STABLE: UNKNOW FRAME TYPE   " << endl;
					return;
				}

				delete pf;
				return;
			} else {

				ev << " HI_CM_STABLE: CONFIGURATION ERROR: WRONG SYNC PRIORITY"
						<< endl;
				delete pf;
				return;
			} //sync_priority

		} else {

			ev << " HI_CM_STABLE: CONFIGURATION ERROR: WRONG SYNC DOMAIN"
					<< endl;

			delete pf;
			return;
		} //sync_domain

	}
	if (message->arrivedOn("schedulerIn")) {

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->hicm);
			return;
		}

		if (string(message->getName()).compare("CA_FRAME") == 0) {
			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CA_FRAME) {

				PCFrame *frame = new PCFrame("CA_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CA_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,blue,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}
		} //CA_FRAME

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			delete et;
			return;

		} //CS FRAME

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			PCFrame *compressedFrame = new PCFrame("IN_FRAME");

			compressedFrame->setCtID(0);
			compressedFrame->setCtMarker(0);
			compressedFrame->setType(IN_FRAME);
			compressedFrame->setTransparent_clock(0);
			compressedFrame->setMembership_new(cp->getMembership_new());
			compressedFrame->setSync_domain(hicm->par("syncDomain"));
			compressedFrame->setSync_priority(hicm->par("syncPriority"));
			compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
			compressedFrame->setIntegration_cycle(cp->getIntegrationCycle());

			ev << "HI_CM_STABLE:Compressed Frame int cycle "
					<< compressedFrame->getIntegration_cycle() << endl;
			ev << "HI_CM_STABLE:Compressed Frame "
					<< compressedFrame->getMembership_new() << endl;

			//Padding
			if (compressedFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
				compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
			}

			compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

			long int key = compressedFrame->getId();

			compressed_frames->insert(
					make_pair<long int, PCFrame *>(key, compressedFrame));

			DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
			dd->setDestinationGate(hicm->gate("schedulerIn"));

			dd->setTimer(hicm->par("dispatch_delay"));
			dd->setSchedulingPriority(3);
			dd->setFrameID(compressedFrame->getId());
			tteScheduler->registerEvent(dd);

			unsigned int member = cp->getMembership_new();

			unsigned int compressed_pit = tteScheduler->getTicks();

			int roundMember = getValue(cp->getMembership_new(), 32);

			delete cp;

			if (inSchedule2(compressed_pit,
					hicm->par("cm_scheduled_pit"),
					hicm->par("acceptance_window"))) {
				//in Schedule
				if (!clock_stack->empty()) {

					pair<unsigned int, unsigned int> old_pair =
							clock_stack->front();
					//
					int old_membership = getValue(old_pair.first, 32);
					unsigned int compressed_pit_old = old_pair.second;

					if (roundMember < old_membership) {

						//no replace here

						return;

					} else if (roundMember == old_membership) {
						//check permanence
						if (compressed_pit > compressed_pit_old) {

							//late permanence pit ->replace

							clock_stack->clear();

							pair<unsigned int, unsigned int> newClockPair =
									make_pair<unsigned int, unsigned int>(
											roundMember, compressed_pit);

							clock_stack->push_front(newClockPair);
							return;
						}

					} else {
						//member > member old -> replace

						clock_stack->clear();

						pair<unsigned int, unsigned int> newClockPair =
								make_pair<unsigned int, unsigned int>(
										roundMember, compressed_pit);
						clock_stack->push_front(newClockPair);
						return;
					}

				} else {

					//clock_stack is empty
					pair<unsigned int, unsigned int> newClockPair = make_pair<
							unsigned int, unsigned int>(roundMember,
							compressed_pit);
					clock_stack->push_front(newClockPair);

					return;

				}

			} else {
				//out of Schedule
				local_async_membership_r |= member;
				local_async_membership_f |= member;
				return;
			} //out of Schedule

		} //CP

		if (string(message->getName()).compare("DP") == 0) {

			ev << "DISPATCH DELAY size comp frames" << compressed_frames->size()
					<< endl;

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

            PCFrame *frame=compressed_frames->find(dd->getFrameID())->second;

            cMsgPar *par = &frame->addPar("created_total");

            par->setLongValue(tteScheduler->getTotalTicks());

            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
                            "in"));

            //delete frame;

            delete frame;
			compressed_frames->erase(dd->getId());

			delete dd;

			return;
		} //dispatch point in time

		if (string(message->getName()).compare("cm_clock_corr_pit") == 0) {

			clock_corr = ((int) clock_stack->front().second)
					- (int) (hicm->par("cm_scheduled_pit").intValue());

			tteScheduler->clockCorrection(clock_corr);

			outVector->record((double) clock_corr);
			if (hicm->par("write").boolValue()) {
				fprintf(fp, "%d ", tteScheduler->getCycles());
				fprintf(fp, "%d \n", clock_corr);
			}

			clock_stack->clear();
			return;

		}

		if (string(message->getName()).compare("cm_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (hicm->par("max_integration_cycles").intValue());

			tteScheduler->registerEvent(event4, true);
			return;
		}

		if (string(message->getName()).compare("cm_sync_eval_pit") == 0) {
			tteScheduler->registerEvent(event3);

			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}

			if (getValue(local_async_membership, 32)
					>= hicm->par("cm_stable_threshold_async").intValue()) {
				duration = hicm->par("cm_restart_timeout");

				event->setTimer(duration);
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;

				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				clock_stack->clear();

				new (this) HI_CM_INTEGRATE();
				return;
			}

			if (clock_stack->empty()) {

				ev
						<< "DEBUG:HI_CM_STABLE: NO inSchedule PCF IN FRAME WAS RECEIVED"
						<< endl;
				local_sync_membership = 0;
			} else {

				local_sync_membership |= clock_stack->front().first;
			}

			if ((getValue(local_sync_membership, 32)
					< hicm->par("cm_stable_threshold_sync").intValue())
					&& (stable_cycle_counter
							< hicm->par("num_unstable_cycles").intValue())) {

				stable_cycle_counter++;

				tteScheduler->registerEvent(event2, true);

				return;

			}

			if ((getValue(local_sync_membership, 32)
					< hicm->par("cm_stable_threshold_sync").intValue())
					&& (stable_cycle_counter
							>= hicm->par("num_unstable_cycles").intValue())) {

				duration = hicm->par("cm_restart_timeout");
				event->setTimer(duration);
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;
				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);
				//ClearForTheUnsycState();

				clock_stack->clear();

				new (this) HI_CM_INTEGRATE();
				return;

			}

			if (getValue(local_sync_membership, 32)
					>= hicm->par("cm_stable_threshold_sync").intValue()) {
				tteScheduler->registerEvent(event2, true);
				return;

			}

		}

		if (string(message->getName()).compare("cm_scheduled_pit") == 0) {

			tteScheduler->registerEvent(event5, true);

			if ((local_integration_cycle % 2) == 0) {

				local_async_membership_f = 0;

			} else {

				local_async_membership_r = 0;

			}

		}

	} //schedulerIn

}
void HI_CM_STABLE::compressionFunction(cMessage* message, HICM *hicm) {

	if (message->arrivedOn("RCin")) {

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//IN FRAME ?
		if (pf->getType() == IN_FRAME) {

			FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

			f_event->setMember(pf->getMembership_new());
			f_event->setPcfType(pf->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(hicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

	}

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			unsigned int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (compression_stack->find(int_cycle)
					!= compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's

				compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "HI_CM_STABLE: There is a compression Function with matching integration cycle collecting PCF's "
						<< int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase
				vector<pair<unsigned int, unsigned int> > *PPT = new vector<
						pair<unsigned int, unsigned int> >();

				PPT->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, PPT));

				OWCounter *ow = new OWCounter("OW", TIMER_EVENT);

				ow->setDestinationGate(hicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(hicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "HI_CM_STABLE: Compression Function:Collection Phase started"
						<< endl;
				delete evt;
				return;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:HI_CM_STABLE: ERROR : OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//no new PCF IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(hicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* hicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ hicm->par("calculation_overhead").intValue()
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function HI_CM_STABLE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;

					} else {
						ev
								<< "Compression Function HI_CM_STABLE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function HI_CM_STABLE: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

HI_CM_UNSYNC::HI_CM_UNSYNC() {
	//Enter

	//cout<<"Enter->CM_UNSYNC \n"<<endl;
	hicm->getDisplayString().setTagArg("i", 1, "black");
	hicm->bubble("CM_UNSYNC");
	ev << "ENTER HI_CM_UNSYNC " << endl;

}
void HI_CM_UNSYNC::handleMessage(cMessage* message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == hicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== hicm->par("syncPriority").intValue()) {

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (hicm->par("max_transmission_delay").intValue())) {

					ev
							<< "WARNING: HI_CM_UNSYNC: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->hicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

					ev << "HI_CM_UNSYNC CS Frame Arrived:ctid " << pf->getCtID()
							<< "getTotalTicks " << tteScheduler->getTotalTicks()
							<< endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					FrameEvent *f_event = new FrameEvent("CS_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(0);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else if (pf->getType() == CA_FRAME) {

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					FrameEvent *f_event = new FrameEvent("CA_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(1);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else {

					delete pf;

					ev << "DEBUG:  HI_CM_UNSYNC: UNKNOW FRAME TYPE   " << endl;
					return;
				}

				delete pf;
				return;
			} else {

				ev << "HI_CM_UNSYNC: CONFIGURATION ERROR: WRONG SYNC PRIORITY"
						<< endl;
				delete pf;
				return;
			} //sync_priority

		} else {

			ev << "HI_CM_UNSYNC: CONFIGURATION ERROR: WRONG SYNC DOMAIN"
					<< endl;

			delete pf;
			return;
		} //sync_domain

	} //RCin

	if (message->arrivedOn("schedulerIn")) {

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->hicm);
			return;
		}

		if (string(message->getName()).compare("CA_FRAME") == 0) {
			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CA_FRAME) {

				PCFrame *frame = new PCFrame("CA_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CA_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,blue,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}
		} //CA_FRAME

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CS_FRAME) {

				PCFrame *frame = new PCFrame("CS_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CS_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,black,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}

		} //CS FRAME

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			PCFrame *compressedFrame = new PCFrame("IN_FRAME");

			compressedFrame->setCtID(0);
			compressedFrame->setCtMarker(0);
			compressedFrame->setType(IN_FRAME);
			compressedFrame->setTransparent_clock(0);
			compressedFrame->setMembership_new(cp->getMembership_new());
			compressedFrame->setSync_domain(
					hicm->par("syncDomain"));
			compressedFrame->setSync_priority(
					hicm->par("syncPriority"));
			compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
			compressedFrame->setIntegration_cycle(cp->getIntegrationCycle());

			ev << "HI_CM_INTEGRATE:Compressed Frame int cycle "
					<< compressedFrame->getIntegration_cycle() << endl;
			ev << "HI_CM_INTEGRATE:Compressed Frame NUMBER OF SMs"
					<< getValue(compressedFrame->getMembership_new(), 32)
					<< endl;

			//Padding
			if (compressedFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
				compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
			}

			compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

			long int key = compressedFrame->getId();

			compressed_frames->insert(
					make_pair<long int, PCFrame *>(key, compressedFrame));

			DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
			dd->setDestinationGate(hicm->gate("schedulerIn"));

			dd->setTimer(hicm->par("dispatch_delay"));
			dd->setSchedulingPriority(3);
			dd->setFrameID(compressedFrame->getId());
			tteScheduler->registerEvent(dd);

			if (getValue(cp->getMembership_new(), 32)
					>= hicm->par("cm_unsync_to_sync_thrld").intValue()) {

				int currentTime = tteScheduler->getTicks();
				//local_clock = cm_sceduled_receive_pit
				tteScheduler->clockCorrection(
						currentTime
								- hicm->par("cm_scheduled_pit").intValue());

				local_sync_membership = cp->getMembership_new();
				local_integration_cycle = cp->getIntegrationCycle();
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				tteScheduler->registerEvent(event2);

				tteScheduler->registerEvent(event4);
				tteScheduler->registerEvent(event5);

				unsigned int member = cp->getMembership_new();

				unsigned int compressedPit = tteScheduler->getTicks();

				clock_stack->push_front(
						pair<unsigned int, unsigned int>(member,
								compressedPit));

				tteScheduler->unregisterEvent(event);

				delete cp;

				new (this) HI_CM_SYNC();
				return;
			}

			if (getValue(cp->getMembership_new(), 32)
					< hicm->par("cm_unsync_to_sync_thrld").intValue()
					&& getValue(cp->getMembership_new(), 32)
							>= hicm->par("cm_unsync_to_tentative_thrld").intValue()) {
				int currentTime = tteScheduler->getTicks();
				//local_clock = cm_sceduled_receive_pit
				tteScheduler->clockCorrection(
						currentTime
								- hicm->par("cm_scheduled_pit").intValue());

				local_sync_membership = cp->getMembership_new();
				local_integration_cycle = cp->getIntegrationCycle();
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				tteScheduler->registerEvent(event2);

				tteScheduler->registerEvent(event4);
				tteScheduler->registerEvent(event5);

				unsigned int member = cp->getMembership_new();

				unsigned int compressedPit = tteScheduler->getTicks();

				clock_stack->push_front(
						pair<unsigned int, unsigned int>(member,
								compressedPit));

				tteScheduler->unregisterEvent(event);

				delete cp;

				new (this) HI_CM_TENTATIVE_SYNC();

				return;
			}

			delete cp;
			return;
		} //comressed point in time

		if (string(message->getName()).compare("DP") == 0) {

			ev << "DISPATCH DELAY size comp frames" << compressed_frames->size()
					<< endl;

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);



            PCFrame *frame=compressed_frames->find(dd->getFrameID())->second;

            cMsgPar *par = &frame->addPar("created_total");

            par->setLongValue(tteScheduler->getTotalTicks());

            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
                            "in"));

            //delete frame;

            delete frame;
			compressed_frames->erase(dd->getId());

			delete dd;
			return;
		} //dispatch point in time

	} //schedulerIn

}
void HI_CM_UNSYNC::compressionFunction(cMessage* message, HICM *hicm) {

	if (message->arrivedOn("RCin")) {

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//IN FRAME ?
		if (pf->getType() == IN_FRAME) {

			FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

			f_event->setMember(pf->getMembership_new());
			f_event->setPcfType(pf->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(hicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

	}

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			unsigned int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (compression_stack->find(int_cycle)
					!= compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's

				compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "HI_CM_UNSYNC: There is a compression Function with matching integration cycle collecting PCF's "
						<< int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase
				vector<pair<unsigned int, unsigned int> > *PPT = new vector<
						pair<unsigned int, unsigned int> >();

				PPT->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, PPT));

				OWCounter *ow = new OWCounter("OW", TIMER_EVENT);

				ow->setDestinationGate(hicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(hicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "HI_CM_UNSYNC: Compression Function:Collection Phase started"
						<< endl;
				delete evt;
				return;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:HI_CM_UNSYNC: ERROR : OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//no new PCF IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(hicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* hicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = restOW
								+ hicm->par("calculation_overhead").intValue()
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function HI_CM_UNSYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;

					} else {
						ev
								<< "Compression Function HI_CM_UNSYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function HI_CM_UNSYNC: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

HI_CM_SYNC::HI_CM_SYNC() {

	//cout<<"Enter->CM_SYNC \n"<<endl;
	hicm->getDisplayString().setTagArg("i", 1, "yellow");
	hicm->bubble("CM_SYNC");
	//local_clock==cm_async_eval_pit;
	//Async_Clique_Detektion();

	//local_clock==cm_sync_eval_pit;
	//Sync_Clique_Detektion();
	//stable_cycle_counter++;

	//local_clock==cm_clock_corr_pit
	//local_clock=local_clock+clock_corr;

}
void HI_CM_SYNC::handleMessage(cMessage* message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == hicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== hicm->par("syncPriority").intValue()) {

				ev << "DEBUG: HI_CM_SYNC membership new value"
						<< pf->getMembership_new() << endl;
				ev << "DEBUG: HI_CM_SYNC membership new number of SM"
						<< getValue(pf->getMembership_new(), 32) << endl;

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (hicm->par("max_transmission_delay"))) {

					ev
							<< "WARNING: HI_CM_SYNC: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->hicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

					ev << "HI_CM_SYNC CS Frame Arrived:ctid " << pf->getCtID()
							<< "getTotalTicks " << tteScheduler->getTotalTicks()
							<< endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_SYNC CS Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					FrameEvent *f_event = new FrameEvent("CS_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(0);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else if (pf->getType() == CA_FRAME) {

					ev << "HI_CM_SYNC CA Frame Arrived:ctid " << pf->getCtID()
							<< "getTotalTicks " << tteScheduler->getTotalTicks()
							<< endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_SYNC CA Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					//cs_container->insert(pair<unsigned int, PCFrame *>(member, pf));

					FrameEvent *f_event = new FrameEvent("CA_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(1);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else {

					delete pf;

					ev << " HI_CM_SYNC: UNKNOW FRAME TYPE   " << endl;
					return;
				}

				delete pf;
				return;
			} else {

				ev << " HI_CM_SYNC: CONFIGURATION ERROR: WRONG SYNC PRIORITY"
						<< endl;
				delete pf;
				return;
			} //sync_priority

		} else {

			ev << " HI_CM_SYNC: CONFIGURATION ERROR: WRONG SYNC DOMAIN" << endl;

			delete pf;
			return;
		} //sync_domain

	} //arrived on RCin

	if (message->arrivedOn("schedulerIn")) {

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->hicm);
			return;
		}

		if (string(message->getName()).compare("CA_FRAME") == 0) {
			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CA_FRAME) {

				PCFrame *frame = new PCFrame("CA_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CA_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,blue,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}
		} //CA_FRAME

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			delete et;
			return;

		} //CS FRAME

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			PCFrame *compressedFrame = new PCFrame("IN_FRAME");

			compressedFrame->setCtID(0);
			compressedFrame->setCtMarker(0);
			compressedFrame->setType(IN_FRAME);
			compressedFrame->setTransparent_clock(0);
			compressedFrame->setMembership_new(cp->getMembership_new());
			compressedFrame->setSync_domain(
					hicm->par("syncDomain"));
			compressedFrame->setSync_priority(
					hicm->par("syncPriority"));
			compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
			compressedFrame->setIntegration_cycle(cp->getIntegrationCycle());

			ev << "HI_CM_SYNC:Compressed Frame int cycle "
					<< compressedFrame->getIntegration_cycle() << endl;
			ev << "HI_CM_SYNC:Compressed Frame "
					<< compressedFrame->getMembership_new() << endl;

			//Padding
			if (compressedFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
				compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
			}

			compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

			long int key = compressedFrame->getId();

			compressed_frames->insert(
					make_pair<long int, PCFrame *>(key, compressedFrame));

			DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
			dd->setDestinationGate(hicm->gate("schedulerIn"));

			dd->setTimer(hicm->par("dispatch_delay"));
			dd->setSchedulingPriority(3);
			dd->setFrameID(compressedFrame->getId());
			tteScheduler->registerEvent(dd);

			unsigned int member = cp->getMembership_new();

			unsigned int compressed_pit = tteScheduler->getTicks();

			int roundMember = getValue(cp->getMembership_new(), 32);

			delete cp;

			if (inSchedule2(compressed_pit,
					hicm->par("cm_scheduled_pit"),
					hicm->par("acceptance_window"))) {
				//in Schedule
				if (!clock_stack->empty()) {

					pair<unsigned int, unsigned int> old_pair =
							clock_stack->front();
					//
					int old_membership = getValue(old_pair.first, 32);
					unsigned int compressed_pit_old = old_pair.second;

					if (roundMember < old_membership) {

						//no replace here

						return;

					} else if (roundMember == old_membership) {
						//check permanence
						if (compressed_pit > compressed_pit_old) {

							//late permanence pit ->replace

							clock_stack->clear();

							pair<unsigned int, unsigned int> newClockPair =
									make_pair<unsigned int, unsigned int>(
											roundMember, compressed_pit);

							clock_stack->push_front(newClockPair);
							return;
						}

					} else {
						//member > member old -> replace

						clock_stack->clear();

						pair<unsigned int, unsigned int> newClockPair =
								make_pair<unsigned int, unsigned int>(
										roundMember, compressed_pit);
						clock_stack->push_front(newClockPair);
						return;
					}

				} else {

					//clock_stack is empty
					pair<unsigned int, unsigned int> newClockPair = make_pair<
							unsigned int, unsigned int>(roundMember,
							compressed_pit);
					clock_stack->push_front(newClockPair);

					return;

				}

			} else {
				//out of Schedule
				local_async_membership_r |= member;
				local_async_membership_f |= member;
				return;
			} //out of Schedule

		} //CP

		if (string(message->getName()).compare("DP") == 0) {

			ev << "DISPATCH DELAY size comp frames" << compressed_frames->size()
					<< endl;

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);



            PCFrame *frame=compressed_frames->find(dd->getFrameID())->second;

            cMsgPar *par = &frame->addPar("created_total");

            par->setLongValue(tteScheduler->getTotalTicks());

            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
                            "in"));

            //delete frame;

            delete frame;
			compressed_frames->erase(dd->getId());

			delete dd;

			return;
		} //dispatch point in time

		if (string(message->getName()).compare("cm_clock_corr_pit") == 0) {

			clock_corr = ((int) clock_stack->front().second)
					- (int) (hicm->par("cm_scheduled_pit"));

			tteScheduler->clockCorrection(clock_corr);

			clock_stack->clear();

		}

		if (string(message->getName()).compare("cm_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (hicm->par("max_integration_cycles").intValue());

			tteScheduler->registerEvent(event4, true);
		}

		if (string(message->getName()).compare("cm_sync_eval_pit") == 0) {
			tteScheduler->registerEvent(event3);

			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}

			if (getValue(local_async_membership, 32)
					>= hicm->par("cm_sync_threshold_async").intValue()) {
				duration = hicm->par("cm_restart_timeout");
				event->setTimer(duration);
				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;

				local_sync_membership = 0;

				local_async_membership = 0;
				local_async_membership_f = 0;
				local_async_membership_r = 0;

				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				clock_stack->clear();

				new (this) HI_CM_INTEGRATE();
				return;
			}

			if (clock_stack->empty()) {

				ev
						<< "DEBUG: HI_CM_SYNC: NO inSchedule PCF IN FRAME WAS RECEIVED"
						<< endl;
				local_sync_membership = 0;
			} else {

				local_sync_membership |= clock_stack->front().first;
			}

			tteScheduler->registerEvent(event2, true);

			if (getValue(local_sync_membership, 32)
					< hicm->par("cm_sync_threshold_sync").intValue()) {

				stable_cycle_counter = 0;
				new (this) HI_CM_TENTATIVE_SYNC();
				return;

			}

			if (((getValue(local_sync_membership, 32)
					>= hicm->par("cm_sync_threshold_sync").intValue())
					&& (stable_cycle_counter
							< hicm->par("num_stable_cycles").intValue())
					&& (hicm->par("cm_sync_to_stable_enabled").boolValue()))) {

				stable_cycle_counter++;
				return;
			}

			if (((getValue(local_sync_membership, 32)
					>= hicm->par("cm_sync_threshold_sync").intValue())
					&& (stable_cycle_counter
							>= hicm->par("num_stable_cycles").intValue())
					&& (hicm->par("cm_sync_to_stable_enabled").boolValue()))) {

				stable_cycle_counter = 0;

				new (this) HI_CM_STABLE();
				return;
			}
			if ((getValue(local_sync_membership, 32)
					>= hicm->par("cm_sync_threshold_sync").intValue())
					&& (hicm->par("cm_sync_to_stable_enabled").boolValue())) {

				stable_cycle_counter++;
				return;
			}
		}

		if (string(message->getName()).compare("cm_scheduled_pit") == 0) {

			tteScheduler->registerEvent(event5, true);

			if ((local_integration_cycle % 2) == 0) {

				local_async_membership_f = 0;

			} else {

				local_async_membership_r = 0;

			}
			return;
		}

	} //arrived on schedulerIn

}
void HI_CM_SYNC::compressionFunction(cMessage* message, HICM *hicm) {

	if (message->arrivedOn("RCin")) {

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//IN FRAME ?
		if (pf->getType() == IN_FRAME) {

			FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

			f_event->setMember(pf->getMembership_new());
			f_event->setPcfType(pf->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(hicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

	}

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			unsigned int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (compression_stack->find(int_cycle)
					!= compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's

				compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "HI_CM_SYNC: There is a compression Function with matching integration cycle collecting PCF's "
						<< int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase
				vector<pair<unsigned int, unsigned int> > *PPT = new vector<
						pair<unsigned int, unsigned int> >();

				PPT->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, PPT));

				OWCounter *ow = new OWCounter("OW", TIMER_EVENT);

				ow->setDestinationGate(hicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(hicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "HI_CM_SYNC: Compression Function:Collection Phase started"
						<< endl;
				delete evt;
				return;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:HI_CM_SYNC: ERROR : OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//no new PCF IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(hicm->par("max_observation_window")
										- owc->getNumberOfObservationWindow())
										* hicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = hicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function HI_CM_SYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window").intValue()) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = hicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;

					} else {
						ev
								<< "Compression Function HI_CM_SYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function HI_CM_SYNC: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

HI_CM_TENTATIVE_SYNC::HI_CM_TENTATIVE_SYNC() {

	ev << "ENTER: HI_CM_TENTATIVE_SYNC " << endl;
	hicm->getDisplayString().setTagArg("i", 1, "white");
	hicm->bubble("CM_TENTATIVE_SYNC");

	//local_clock==cm_async_eval_pit;
	//Async_Clique_Detektion();

	//local_clock==cm_sync_eval_pit;
	//Sync_Clique_Detektion();
	//stable_cycle_counter++;

	//local_clock==cm_clock_corr_pit;
	//local_clock=local_clock+clock_corr;

}
void HI_CM_TENTATIVE_SYNC::handleMessage(cMessage* message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == hicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== hicm->par("syncPriority").intValue()) {

				ev << "DEBUG: HI_CM_TENTATIVE_SYNC membership new value"
						<< pf->getMembership_new() << endl;
				ev << "DEBUG: HI_CM_TENTATIVE_SYNC membership new number of SM"
						<< getValue(pf->getMembership_new(), 32) << endl;

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (hicm->par("max_transmission_delay").intValue())) {

					ev
							<< "WARNING: HI_CM_TENTATIVE_SYNC: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->hicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

					ev << "HI_CM_TENTATIVE_SYNC CS Frame Arrived:ctid "
							<< pf->getCtID() << "getTotalTicks "
							<< tteScheduler->getTotalTicks() << endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_TENTATIVE_SYNC CS Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					//cs_container->insert(pair<unsigned int, PCFrame *>(member, pf));

					FrameEvent *f_event = new FrameEvent("CS_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(0);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else if (pf->getType() == CA_FRAME) {

					ev << "HI_CM_TENTATIVE_SYNC CA Frame Arrived:ctid "
							<< pf->getCtID() << "getTotalTicks "
							<< tteScheduler->getTotalTicks() << endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_TENTATIVE_SYNC CA Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					FrameEvent *f_event = new FrameEvent("CA_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(1);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else {

					delete pf;

					ev << " HI_CM_TENTATIVE_SYNC: UNKNOW FRAME TYPE   " << endl;
					return;
				}

				delete pf;
				return;
			} else {

				ev
						<< " HI_CM_TENTATIVE_SYNC: CONFIGURATION ERROR: WRONG SYNC PRIORITY"
						<< endl;
				delete pf;
				return;
			} //sync_priority

		} else {

			ev
					<< " HI_CM_TENTATIVE_SYNC: CONFIGURATION ERROR: WRONG SYNC DOMAIN"
					<< endl;

			delete pf;
			return;
		} //sync_domain

	} //arrived on RCin

	if (message->arrivedOn("schedulerIn")) {

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->hicm);
			return;
		}

		if (string(message->getName()).compare("CA_FRAME") == 0) {
			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CA_FRAME) {

				PCFrame *frame = new PCFrame("CA_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CA_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,blue,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}
		} //CA_FRAME

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CS_FRAME) {

				PCFrame *frame = new PCFrame("CS_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CS_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,black,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}

		} //CS FRAME
		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			PCFrame *compressedFrame = new PCFrame("IN_FRAME");

			compressedFrame->setCtID(0);
			compressedFrame->setCtMarker(0);
			compressedFrame->setType(IN_FRAME);
			compressedFrame->setTransparent_clock(0);
			compressedFrame->setMembership_new(cp->getMembership_new());
			compressedFrame->setSync_domain(
					hicm->par("syncDomain"));
			compressedFrame->setSync_priority(
					hicm->par("syncPriority"));
			compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
			compressedFrame->setIntegration_cycle(cp->getIntegrationCycle());

			ev << "HI_CM_TENTATIVE_SYNC:Compressed Frame int cycle "
					<< compressedFrame->getIntegration_cycle() << endl;
			ev << "HI_CM_TENTATIVE_SYNC:Compressed Frame "
					<< compressedFrame->getMembership_new() << endl;

			//Padding
			if (compressedFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
				compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
			}

			compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

			long int key = compressedFrame->getId();

			compressed_frames->insert(
					make_pair<long int, PCFrame *>(key, compressedFrame));

			DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
			dd->setDestinationGate(hicm->gate("schedulerIn"));
			//dd->setMembership_new(cp->getMembership_new());
			dd->setTimer(hicm->par("dispatch_delay"));
			dd->setSchedulingPriority(3);
			dd->setFrameID(compressedFrame->getId());
			tteScheduler->registerEvent(dd);

			unsigned int member = cp->getMembership_new();

			unsigned int compressed_pit = tteScheduler->getTicks();

			int roundMember = getValue(cp->getMembership_new(), 32);

			delete cp;

			if (inSchedule2(compressed_pit,
					hicm->par("cm_scheduled_pit"),
					hicm->par("acceptance_window"))) {
				//in Schedule
				if (!clock_stack->empty()) {

					pair<unsigned int, unsigned int> old_pair =
							clock_stack->front();
					//
					int old_membership = getValue(old_pair.first, 32);
					unsigned int compressed_pit_old = old_pair.second;

					if (roundMember < old_membership) {

						//no replace here

						return;

					} else if (roundMember == old_membership) {
						//check permanence
						if (compressed_pit > compressed_pit_old) {

							//late permanence pit ->replace

							clock_stack->clear();

							pair<unsigned int, unsigned int> newClockPair =
									make_pair<unsigned int, unsigned int>(
											roundMember, compressed_pit);

							clock_stack->push_front(newClockPair);
							return;
						}

					} else {
						//member > member old -> replace

						clock_stack->clear();

						pair<unsigned int, unsigned int> newClockPair =
								make_pair<unsigned int, unsigned int>(
										roundMember, compressed_pit);
						clock_stack->push_front(newClockPair);
						return;
					}

				} else {

					//clock_stack is empty
					pair<unsigned int, unsigned int> newClockPair = make_pair<
							unsigned int, unsigned int>(roundMember,
							compressed_pit);
					clock_stack->push_front(newClockPair);

					return;

				}

			} else {
				//out of Schedule
				local_async_membership_r |= member;
				local_async_membership_f |= member;
				return;
			} //out of Schedule

		} //CP

		if (string(message->getName()).compare("DP") == 0) {

			ev << "DISPATCH DELAY size comp frames" << compressed_frames->size()
					<< endl;

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);



            PCFrame *frame=compressed_frames->find(dd->getFrameID())->second;

            cMsgPar *par = &frame->addPar("created_total");

            par->setLongValue(tteScheduler->getTotalTicks());

            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
                            "in"));

            //delete frame;

            delete frame;
			compressed_frames->erase(dd->getId());

			delete dd;

			return;
		} //dispatch point in time

		if (string(message->getName()).compare("cm_clock_corr_pit") == 0) {

			clock_corr = ((int) clock_stack->front().second)
					- (int) (hicm->par("cm_scheduled_pit"));

			tteScheduler->clockCorrection(clock_corr);

			clock_stack->clear();

		}

		if (string(message->getName()).compare("cm_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (hicm->par("max_integration_cycles").intValue());

			tteScheduler->registerEvent(event4, true);
		}

		if (string(message->getName()).compare("cm_sync_eval_pit") == 0) {
			tteScheduler->registerEvent(event3);
			//update local_async_membership
			if ((local_integration_cycle % 2) == 0) {

				local_async_membership = local_async_membership_r;

			} else {

				local_async_membership = local_async_membership_f;

			}

			if (getValue(local_async_membership, 32)
					>= hicm->par("cm_tentative_sync_threshold_async").intValue()) {

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;

				local_sync_membership = 0;

				local_async_membership = 0;
				local_async_membership_f = 0;
				local_async_membership_r = 0;

				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);
				//ClearForTheUnsycState();

				clock_stack->clear();

				new (this) HI_CM_UNSYNC();
				return;
			}

			if (clock_stack->empty()) {

				ev << "DEBUG:SI SYNC: NO inSchedule PCF IN FRAME WAS RECEIVED"
						<< endl;
				local_sync_membership = 0;
			} else {

				local_sync_membership |= clock_stack->front().first;
			}

			if (getValue(local_sync_membership, 32)
					< hicm->par("cm_tentative_sync_threshold_sync").intValue()) {

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;

				local_async_membership = 0;
				local_async_membership_f = 0;
				local_async_membership_r = 0;

				stable_cycle_counter = 0;

				tteScheduler->unregisterEvent(event3);
				tteScheduler->unregisterEvent(event4);
				tteScheduler->unregisterEvent(event5);

				clock_stack->clear();

				new (this) HI_CM_UNSYNC();
				return;

			}

			tteScheduler->registerEvent(event2, true);

			if (((getValue(local_sync_membership, 32)
					>= hicm->par("cm_tentative_sync_threshold_sync").intValue())
					&& (getValue(local_sync_membership, 32)
							< hicm->par("cm_tentative_to_sync_thrld").intValue()))) {

				return;
			}

			if ((getValue(local_sync_membership, 32)
					>= hicm->par("cm_tentative_to_sync_thrld").intValue()))

			{

				new (this) HI_CM_SYNC();
				return;
			}

		}

		if (string(message->getName()).compare("cm_scheduled_pit") == 0) {

			tteScheduler->registerEvent(event5, true);

			if ((local_integration_cycle % 2) == 0) {

				local_async_membership_f = 0;

			} else {

				local_async_membership_r = 0;

			}

		}

	} // schedulerIn

}

void HI_CM_TENTATIVE_SYNC::compressionFunction(cMessage* message, HICM *hicm) {

	if (message->arrivedOn("RCin")) {

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//IN FRAME ?
		if (pf->getType() == IN_FRAME) {

			//in_container->insert(pair<unsigned int, PCFrame *>(membership_new, pf->dup()));

			FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

			f_event->setMember(pf->getMembership_new());
			f_event->setPcfType(pf->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(hicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

	}

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			unsigned int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (compression_stack->find(int_cycle)
					!= compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's

				compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "HI_CM_TENTATIVE_SYNC: There is a compression Function with matching integration cycle collecting PCF's "
						<< int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase
				vector<pair<unsigned int, unsigned int> > *PPT = new vector<
						pair<unsigned int, unsigned int> >();

				PPT->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, PPT));

				OWCounter *ow = new OWCounter("OW", TIMER_EVENT);

				ow->setDestinationGate(hicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(hicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "HI_CM_TENTATIVE_SYNC: Compression Function:Collection Phase started"
						<< endl;
				delete evt;
				return;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:HI_CM_TENTATIVE_SYNC: ERROR : OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//no new PCF IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window").intValue()) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(hicm->par("max_observation_window")
										- owc->getNumberOfObservationWindow())
										* hicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = hicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function HI_CM_TENTATIVE_SYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = hicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;

					} else {
						ev
								<< "Compression Function HI_CM_TENTATIVE_SYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function HI_CM_TENTATIVE_SYNC: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

HI_CM_WAIT_4_CYCLE_START::HI_CM_WAIT_4_CYCLE_START() {

	//Enter

	hicm->getDisplayString().setTagArg("i", 1, "cyan");
	hicm->bubble("CM_WAIT_4_CYCLE_START");
	tteScheduler->registerEvent(event);

	//round_completed=false;
	//TW(duration);
	//TW(int_cycle_duration+acceptance_window/2);
	//round_completed=true;

}

void HI_CM_WAIT_4_CYCLE_START::handleMessage(cMessage* message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == hicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== hicm->par("syncPriority").intValue()) {

				ev << "DEBUG: HI_CM_WAIT_4_CYCLE_START membership  value"
						<< pf->getMembership_new() << endl;
				ev << "DEBUG: HI_CM_WAIT_4_CYCLE_START membership  number of SM"
						<< getValue(pf->getMembership_new(), 32) << endl;

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (hicm->par("max_transmission_delay").intValue())) {

					ev
							<< "WARNING: HI_CM_WAIT_4_CYCLE_START: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->hicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

					ev << "HI_CM_WAIT_4_CYCLE_START CS Frame Arrived:ctid "
							<< pf->getCtID() << "getTotalTicks "
							<< tteScheduler->getTotalTicks() << endl;

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_WAIT_4_CYCLE_START CS Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					//cs_container->insert(pair<unsigned int, PCFrame *>(member, pf));

					FrameEvent *f_event = new FrameEvent("CS_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(0);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else if (pf->getType() == CA_FRAME) {

					//calculate permanence pit
					int permanence_delay =
							max_transmision_delay
									- (transparentClockToTicks(
											pf->getTransparent_clock(),
											tteScheduler->par("tick").doubleValue())
											+ (tteScheduler->getTotalTicks()
													- pf->par("received_total").intValue()));

					unsigned int member = pf->getMembership_new();

					ev << "HI_CM_WAIT_4_CYCLE_START CA Frame Arrived:ctid "
							<< "PERMANENCE DELAY" << permanence_delay << endl;

					FrameEvent *f_event = new FrameEvent("CA_FRAME",
							TIMER_EVENT);

					f_event->setIntegrationCycle(pf->getIntegration_cycle());
					f_event->setMember(member);
					f_event->setPcfType(pf->getType());
					f_event->setTimer(permanence_delay);
					f_event->setDestinationGate(hicm->gate("schedulerIn"));
					f_event->setSchedulingPriority(1);
					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else {

					delete pf;

					ev
							<< "DEBUG:  HI_CM_WAIT_4_CYCLE_START: UNKNOW FRAME TYPE   "
							<< endl;
					return;
				}

				delete pf;
				return;
			} else {

				ev
						<< "HI_CM_WAIT_4_CYCLE_START: CONFIGURATION ERROR: WRONG SYNC PRIORITY"
						<< endl;
				delete pf;
				return;
			} //sync_priority

		} else {

			ev
					<< "HI_CM_WAIT_4_CYCLE_START: CONFIGURATION ERROR: WRONG SYNC DOMAIN"
					<< endl;

			delete pf;
			return;
		} //sync_domain

	} //arrived on RCin

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("ASYNCHRON") == 0) {

			if (getValue(local_sync_membership, 32) == 0) {

				duration = 0;

				//local_clock=0;
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;

				local_async_membership_r = 0;
				local_async_membership_f = 0;

				ev
						<< "HI_CM_WAIT_4_CYCLE_START :: ASYNCHRON TIMER EXPIRED, NEXT STATE -> HI_CM_UNSYNC"
						<< endl;

				new (this) HI_CM_UNSYNC();

				return;
			} //local_sync_membership == 0

			if (getValue(local_sync_membership, 32) > 0) {

				int currentTime = tteScheduler->getTicks();

				//local_clock = cm_sceduled_receive_pit
				tteScheduler->clockCorrection(
						currentTime
								- hicm->par("cm_scheduled_pit").intValue());

				tteScheduler->registerEvent(event2);
				//tteScheduler->registerEvent(event3);
				tteScheduler->registerEvent(event4);
				tteScheduler->registerEvent(event5);

				new (this) HI_CM_TENTATIVE_SYNC();
				return;

			}
		} //ASYNC TIMEOUT

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->hicm);
			return;
		}

		if (string(message->getName()).compare("CA_FRAME") == 0) {
			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CA_FRAME) {

				PCFrame *frame = new PCFrame("CA_Frame");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CA_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,blue,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}

		} //CA_FRAME

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CS_FRAME) {

				PCFrame *frame = new PCFrame("CS_FRAME");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(hicm->par("syncDomain"));
				frame->setSync_priority(hicm->par("syncPriority"));
				frame->setIntegration_cycle(et->getIntegrationCycle());
				frame->setMembership_new(et->getMember());
				frame->setTransparent_clock(0);
				frame->setCtMarker(0);
				frame->setCtID(0);
				frame->setType(CS_FRAME);
				frame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);

				//Padding
				if (frame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
					frame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				frame->setDisplayString("b=15,15,rect,white,black,5");

				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				hicm->sendDirect(
						frame->dup(),
						hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete frame;
				delete et;
				return;
			}

		} //CS FRAME

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			PCFrame *compressedFrame = new PCFrame("IN_FRAME");

			compressedFrame->setCtID(0);
			compressedFrame->setCtMarker(0);
			compressedFrame->setType(IN_FRAME);
			compressedFrame->setTransparent_clock(0);
			compressedFrame->setMembership_new(cp->getMembership_new());
			compressedFrame->setSync_domain(
					hicm->par("syncDomain"));
			compressedFrame->setSync_priority(
					hicm->par("syncPriority"));
			compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
			compressedFrame->setIntegration_cycle(cp->getIntegrationCycle());

			ev << "HI_CM_WAIT_4_CYCLE_START: Compressed Frame int cycle "
					<< compressedFrame->getIntegration_cycle() << endl;
			ev << "HI_CM_WAIT_4_CYCLE_START: Compressed Frame membership "
					<< compressedFrame->getMembership_new() << endl;

			//Padding
			if (compressedFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
				compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
			}

			compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

			long int key = compressedFrame->getId();

			compressed_frames->insert(
					make_pair<long int, PCFrame *>(key, compressedFrame));

			DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
			dd->setDestinationGate(hicm->gate("schedulerIn"));

			dd->setTimer(hicm->par("dispatch_delay"));
			dd->setSchedulingPriority(3);
			dd->setFrameID(compressedFrame->getId());

			tteScheduler->registerEvent(dd);

			if (!((tteScheduler->getTicks()
					>= (unsigned int)(hicm->par("cm_scheduled_pit")
							- hicm->par("acceptance_window").intValue() / 2))
					&& (tteScheduler->getTicks()
							<= (unsigned int)(hicm->par("cm_scheduled_pit")
									+ hicm->par("acceptance_window").intValue()
											/ 2)))) {

				if (getValue(cp->getMembership_new(), 32)
						>= hicm->par("cm_wait_threshold_sync").intValue()) {

					int currentTime = tteScheduler->getTicks();
					//local_clock = cm_sceduled_receive_pit
					tteScheduler->clockCorrection(
							currentTime
									- hicm->par("cm_scheduled_pit").intValue());

					local_sync_membership = cp->getMembership_new();

					local_integration_cycle = cp->getIntegrationCycle();

					local_async_membership = 0;
					local_async_membership_r = 0;
					local_async_membership_f = 0;

					tteScheduler->unregisterEvent(event);

					duration = hicm->par("int_cycle_duration").intValue()
							+ (hicm->par("acceptance_window").intValue() / 2);

					delete cp;

					new (this) HI_CM_WAIT_4_CYCLE_START();
					return;
				}

			} // out of schedule -> out of acceptance_window

			if (cp->getIntegrationCycle() != local_integration_cycle) {

				if (getValue(cp->getMembership_new(), 32)
						>= hicm->par("cm_wait_threshold_sync").intValue()) {

					int currentTime = tteScheduler->getTicks();
					//local_clock = cm_sceduled_receive_pit
					tteScheduler->clockCorrection(
							currentTime
									- hicm->par("cm_scheduled_pit").intValue());

					local_sync_membership = cp->getMembership_new();

					local_integration_cycle = cp->getIntegrationCycle();

					local_async_membership = 0;
					local_async_membership_r = 0;
					local_async_membership_f = 0;

					tteScheduler->unregisterEvent(event);

					duration = hicm->par("int_cycle_duration").intValue()
							+ (hicm->par("acceptance_window").intValue() / 2);

					delete cp;

					new (this) HI_CM_WAIT_4_CYCLE_START();
					return;
				}

			} //out of schedule int_cycle

			delete cp;
			return;
		} //comressed point in time

		if (string(message->getName()).compare("DP") == 0) {

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);



            PCFrame *frame=compressed_frames->find(dd->getFrameID())->second;

            cMsgPar *par = &frame->addPar("created_total");

            par->setLongValue(tteScheduler->getTotalTicks());

            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
                            "in"));
            hicm->sendDirect(
                    frame->dup(),
                    hicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
                            "in"));

            //delete frame;

            delete frame;
			compressed_frames->erase(dd->getId());

			delete dd;
			return;
		} //dispatch point in time

	} //schedulerIn

}
void HI_CM_WAIT_4_CYCLE_START::compressionFunction(cMessage* message,
		HICM *hicm) {

	if (message->arrivedOn("RCin")) {

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//IN FRAME ?
		if (pf->getType() == IN_FRAME) {

			FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

			f_event->setMember(pf->getMembership_new());
			f_event->setPcfType(pf->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(hicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

	}

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			unsigned int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (compression_stack->find(int_cycle)
					!= compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's

				compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "HI_CM_WAIT_4_CYCLE_START: There is a compression Function with matching integration cycle collecting PCF's "
						<< int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase
				vector<pair<unsigned int, unsigned int> > *PPT = new vector<
						pair<unsigned int, unsigned int> >();

				PPT->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, PPT));

				OWCounter *ow = new OWCounter("OW", TIMER_EVENT);

				ow->setDestinationGate(hicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(hicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "HI_CM_WAIT_4_CYCLE_START: Compression Function:Collection Phase started"
						<< endl;
				delete evt;
				return;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:HI_CM_WAIT_4_CYCLE_START: ERROR : OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//no new PCF IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(hicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* hicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ hicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = hicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function HI_CM_WAIT_4_CYCLE_START: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)hicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)hicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										hicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = hicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(hicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						cpit->setIntegrationCycle(owc->getIntegrationCycle());
						tteScheduler->registerEvent(cpit);

						delete compression_stack->find(
								owc->getIntegrationCycle())->second;
						compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;

					} else {
						ev
								<< "Compression Function HI_CM_WAIT_4_CYCLE_START: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< hicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function HI_CM_WAIT_4_CYCLE_START: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

}
