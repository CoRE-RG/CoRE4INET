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
 * SICMStates.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */

#include "CoRE4INET_SICMStates.h"
#include "CoRE4INET_SICM.h"
#include <string>
#include "omnetpp.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"
#include "SynchronisationEvents_m.h"
#include "CoRE4INET_CoRE4INETDefs.h"
#include <algorithm>
#include "core4inet/utilities/HelperFunctions.h"
#include "SchedulerMessageEvents_m.h"
#include "cmessage.h"
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"

namespace CoRE4INET {

SI_CM_INIT::~SI_CM_INIT(){}

SI_CM_INIT::SI_CM_INIT(SICM *pointer, FILE *f) {
	//for statistics purpose only
	outVector = new cOutVector("CompMaster");

	sicm = pointer;
	//fp= fp=fopen("/home/pcman/from_thinkpad/TTEthernetModel/examples/SICM_TEST_AS6802_sync/results/compmaster.txt","w+");
	fp = f;

	counter = 0;

	if (sicm->par("read").boolValue()) {

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

	ctid = sicm->par("id");
	local_timer = false;
	flood_receive = false;
	closed_window = false;
	round_completed = false;

	local_clock = 0;
	local_sync_membership = 0;
	local_async_membership = 0;
	local_async_membership_f = 0;
	local_async_membership_r = 0;
	local_integration_cycle = 0;
	clock_corr = 0;
	stable_cycle_counter = 0;

	duration = sicm->par("cm_listen_timeout");
	max_transmision_delay = sicm->par("max_transmission_delay");

	tteScheduler = (TTEScheduler*) sicm->getParentModule()->getSubmodule(
			"scheduler");

	event = new SchedulerTimerEvent("ASYNCHRON", TIMER_EVENT);
	event->setSchedulingPriority(3);
	event->setTimer(duration);
	event->setDestinationGate(sicm->gate("schedulerIn"));

	clock_stack = new deque<pair<unsigned int, unsigned int> >;

	compression_stack = new map<unsigned int,
			vector<pair<unsigned int, unsigned int> > *>;

	ca_compression_stack = new map<unsigned int,
			vector<pair<unsigned int, unsigned int> > *>;

	compressed_frames = new deque<pair<unsigned int, PCFrame *> >;

	caCompressedFrames = new multimap<unsigned int, PCFrame *>;

	delay_container = new deque<CompressedPIT *>;

	dispatch_delay_container = new deque<DispatchDelay *>;

	//cm_sync_eval_pit
	event2 = new SchedulerActionTimeEvent("cm_sync_eval_pit",
			ACTION_TIME_EVENT);
	event2->setAction_time(sicm->par("cm_sync_eval_pit"));
	event2->setDestinationGate(sicm->gate("schedulerIn"));
	event2->setSchedulingPriority(4);
	//cm_clock_corr_pit
	event3 = new SchedulerActionTimeEvent("cm_clock_corr_pit",
			ACTION_TIME_EVENT);
	event3->setAction_time(
			(unsigned int) sicm->par("cm_clock_corr_pit"));
	event3->setDestinationGate(sicm->gate("schedulerIn"));
	event3->setSchedulingPriority(4);

	//event4 is used to update/increment/ the "local_integration_cycle" value
	event4 = new SchedulerActionTimeEvent("cm_inc_pit", ACTION_TIME_EVENT);
	event4->setAction_time(
			sicm->par("cm_scheduled_pit").intValue()
					- (sicm->par("acceptance_window").intValue() / 2));
	event4->setDestinationGate(sicm->gate("schedulerIn"));
	event4->setSchedulingPriority(1);
	//cm_scheduled_pit
	event5 = new SchedulerActionTimeEvent("cm_scheduled_pit",
			ACTION_TIME_EVENT);
	event5->setAction_time(sicm->par("cm_scheduled_pit"));
	event5->setDestinationGate(sicm->gate("schedulerIn"));
	event5->setSchedulingPriority(4);

	if (sicm->par("read").boolValue()) {

		tteScheduler->registerEvent(event3);
		tteScheduler->registerEvent(event4);

		new (this) SI_CM_PSEUDOSYNC();

		return;
	}

	new (this) SI_CM_INTEGRATE();

}

SI_CM_PSEUDOSYNC::SI_CM_PSEUDOSYNC() {
}

void SI_CM_PSEUDOSYNC::handleMessage(cMessage *message) {

	if (string(message->getName()).compare("cm_clock_corr_pit") == 0) {
		ev << "SI_CM_PSEUDOSYNC clock correction" << endl;

		tteScheduler->clockCorrection(values->at(counter++));

		tteScheduler->registerEvent(event3, true);

		return;

	}

	if (string(message->getName()).compare("cm_inc_pit") == 0) {
		ev << "SI_CM_PSEUDOSYNC local_integration_cycle"
				<< local_integration_cycle << endl;

		local_integration_cycle = (local_integration_cycle + 1)
				% (sicm->par("max_integration_cycles").intValue());

		ev << "local_integration_cycle updated" << local_integration_cycle
				<< endl;

		tteScheduler->registerEvent(event4, true);

		return;
	}

}

SI_CM_INTEGRATE::SI_CM_INTEGRATE() {

	//after Power ON  and Initialization READY
	//duration=cm_listen_timeout;
	//Enter

	sicm->getDisplayString().setTagArg("i", 1, "red");
	sicm->bubble("CM_INTEGRATE");

	ev << "SICM::current state :: CM_INTEGRATE" << endl;

	tteScheduler->registerEvent(event);
	//local_timer=false;
	//TW(duration); //TO?
	//local_timer=true;

}

void SI_CM_INTEGRATE::handleMessage(cMessage *message) {

	//with permanence calculation for all frames

	//SICM blocks all CA and CS Frames in INTEGRATE state

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == sicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== sicm->par("syncPriority").intValue()) {

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (sicm->par("max_transmission_delay"))) {

					ev
							<< "WARNING: SI_CM_INTEGRATE: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->sicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

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
									f_event->setDestinationGate(sicm->gate("schedulerIn"));

									if (pf->getType() == CS_FRAME) {
										f_event->setSchedulingPriority(0);
									} else {
										ev << "ERROR: expect a CS FRAME ! TYPE: "
												<< pf->getType() << endl;
									}

									tteScheduler->registerEvent(f_event);

									delete pf;

									return;

								} else if (pf->getType() == CA_FRAME) {

									compressionFunctionCA(message, this->sicm);
									return;
				} else {

					delete pf;

					ev << "DEBUG:  SI_CM_INTEGRATE: FRAME DROPPED  " << endl;
					return;
				}

				delete pf;
				return;
			} else {

			} //sync_priority

		} else {

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
					<< "SI_CM_INTEGRATE :: ASYNCHRON TIMER EXPIRED, NEXT STATE -> SI_CM_UNSYNC"
					<< endl;

			new (this) SI_CM_UNSYNC();

			return;

		}

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->sicm);
			return;
		}

		if ((string(message->getName()).compare("OW_CA") == 0)
				|| (string(message->getName()).compare("CA_FRAME") == 0)) {
			compressionFunctionCA(message, this->sicm);
			return;
		}

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			local_sync_membership = cp->getMembership_new();
			local_integration_cycle = cp->getIntegrationCycle();

			int currentTime = tteScheduler->getTicks();
			//local_clock = cm_sceduled_receive_pit
			tteScheduler->clockCorrection(
					currentTime - sicm->par("cm_scheduled_pit").intValue());

			if (getValue(local_sync_membership, 32)
					>= sicm->par("cm_integrate_to_sync_thrld").intValue()) {

				PCFrame *compressedFrame = new PCFrame("IN_FRAME");
				compressedFrame->setCtID(0);
				compressedFrame->setCtMarker(0);
				compressedFrame->setType(IN_FRAME);
				compressedFrame->setTransparent_clock(0);
				compressedFrame->setMembership_new(cp->getMembership_new());
				compressedFrame->setSync_domain(
						sicm->par("syncDomain"));
				compressedFrame->setSync_priority(
						sicm->par("syncPriority"));
				compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				compressedFrame->setIntegration_cycle(
						cp->getIntegrationCycle());

				ev << "SI_CM_INTEGRATE:Compressed Frame int cycle "
						<< compressedFrame->getIntegration_cycle() << endl;
				ev << "SI_CM_INTEGRATE:Compressed Frame NUMBER OF SMs "
						<< getValue(compressedFrame->getMembership_new(), 32)
						<< endl;

				//Padding
				if (compressedFrame->getByteLength()
						< MIN_ETHERNET_FRAME_BYTES) {
					compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

				compressed_frames->push_front(
						pair<unsigned int, PCFrame *>(cp->getMembership_new(),
								compressedFrame));

				local_sync_membership = cp->getMembership_new();
				local_integration_cycle =
						compressed_frames->front().second->getIntegration_cycle();
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
				dd->setDestinationGate(sicm->gate("schedulerIn"));
				dd->setMembership_new(cp->getMembership_new());
				dd->setTimer(sicm->par("dispatch_delay"));
				dd->setSchedulingPriority(3);

				tteScheduler->registerEvent(dd);

				dispatch_delay_container->push_front(dd);

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

				new (this) SI_CM_SYNC();
				return;
			}

			delete cp;
			return;
		} //comressed point in time

		if (string(message->getName()).compare("DP") == 0) {

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

			compressed_frames->front().second->setCtID(0);

			cMsgPar *par = &compressed_frames->front().second->addPar(
					"created_total");
			par->setLongValue(tteScheduler->getTotalTicks());
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
							"in"));

			delete compressed_frames->front().second;

			compressed_frames->clear();

			dispatch_delay_container->pop_front();

			dispatch_delay_container->clear();
			delete dd;
			return;
		} //dispatch point in time

		if (string(message->getName()).compare("DPCA") == 0) {
			DispatchDelay *dp = dynamic_cast<DispatchDelay *>(message);

			unsigned int roundMember = dp->getMembership_new();

			if (caCompressedFrames->find(roundMember)
					!= caCompressedFrames->end()) {

				delete caCompressedFrames->find(roundMember)->second;

				caCompressedFrames->erase(roundMember);

			} else {

				ev
						<< "Compression Function: Compressed Frame not found:round member:"
						<< roundMember << endl;

			}
			delete dp;
			return;
		}

		if (string(message->getName()).compare("CPCA") == 0) {

			delete 	message;
			return;
		}

		if (string(message->getName()).compare("CS_FRAME") == 0) {

					delete 	message;
					return;
				}
	} //schedulerIn

}

SI_CM_STABLE::SI_CM_STABLE() {

	sicm->getDisplayString().setTagArg("i", 1, "green");
	sicm->bubble("CM_STABLE");
	ev << "enter SI_CM_STABLE" << endl;

	/* if(!sicm->par("read").boolValue()){
	 fprintf(fp, "%s  ", "SI_CM STABLE ");
	 fprintf(fp,"%.15f\n", simTime().dbl());
	 fprintf(fp,"%ld \n", tteScheduler->getTotalTicks());
	 }*/

	//fprintf(fp, "%s", "CM STABLE");
	//fprintf(fp,"%lf\n", simTime().dbl());

//
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

void SI_CM_STABLE::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//CM make all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == sicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== sicm->par("syncPriority").intValue()) {

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (sicm->par("max_transmission_delay"))) {

					ev
							<< "WARNING: SI_CM_STABLE: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}
				ev << "SI_CM_STABLE frame received local clock"
						<< tteScheduler->getTicks() << endl;

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					compressionFunction(message, this->sicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

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
									f_event->setDestinationGate(sicm->gate("schedulerIn"));

									if (pf->getType() == CS_FRAME) {
										f_event->setSchedulingPriority(0);
									} else {
										ev << "ERROR: expect a CS FRAME ! TYPE: "
												<< pf->getType() << endl;
									}

									tteScheduler->registerEvent(f_event);

									delete pf;

									return;

								} else if (pf->getType() == CA_FRAME) {

									compressionFunctionCA(message, this->sicm);
									return;
				} else {

					delete pf;
					ev << "DEBUG:  SI_CM_STABLE FRAME DROPPED  " << endl;
					return;
				}
				delete pf;
			} else {

			} //sync_priority

		} else {

		} //sync_domain

	}

	if (message->arrivedOn("schedulerIn")) {

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->sicm);
			return;
		}

		if ((string(message->getName()).compare("OW_CA") == 0)
				|| (string(message->getName()).compare("CA_FRAME") == 0)) {
			compressionFunctionCA(message, this->sicm);
			return;
		}

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			ev << "compressed point " << tteScheduler->getTicks() << endl;

			int compressed_pit = tteScheduler->getTicks();

			if (inSchedule2(compressed_pit,
					sicm->par("cm_scheduled_pit"),
					sicm->par("acceptance_window"))) {

				int roundMember = getValue(cp->getMembership_new(), 32);

				DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
				dd->setDestinationGate(sicm->gate("schedulerIn"));
				dd->setMembership_new(roundMember);
				dd->setTimer(sicm->par("dispatch_delay"));
				dd->setSchedulingPriority(3);

				if (!clock_stack->empty()) {

					pair<unsigned int, unsigned int> old_pair =
							clock_stack->front();
					//
					int old_membership = getValue(old_pair.first, 32);
					int compressed_pit_old = old_pair.second;

					if (roundMember < old_membership) {

						//no replace here
						delete dd;
						delete cp;
						return;

					} else if (roundMember == old_membership) {

						if (compressed_pit > compressed_pit_old) {

							//late permanence pit
							delete compressed_frames->front().second;
							// sicm->cancelAndDelete(itc->second);
							compressed_frames->clear();

							clock_stack->clear();

							if (!dispatch_delay_container->empty()) {

								tteScheduler->unregisterEvent(
										dispatch_delay_container->front());

								delete dispatch_delay_container->front();

							}

							dispatch_delay_container->clear();

							clock_stack->clear();

							pair<unsigned int, unsigned int> newClockPair =
									make_pair<unsigned int, unsigned int>(
											roundMember, compressed_pit);
							clock_stack->push_front(newClockPair);

							//create the new frame
							PCFrame *compressedFrame = new PCFrame("IN_FRAME");
							compressedFrame->setCtMarker(0);
							compressedFrame->setCtID(0);
							compressedFrame->setType(IN_FRAME);
							compressedFrame->setTransparent_clock(0);
							compressedFrame->setMembership_new(
									cp->getMembership_new());
							compressedFrame->setSync_domain(
									sicm->par("syncDomain"));
							compressedFrame->setSync_priority(
									sicm->par("syncPriority"));
							compressedFrame->setByteLength(
									46 + ETHER_MAC_FRAME_BYTES);
							compressedFrame->setIntegration_cycle(
									cp->getIntegrationCycle());
							//Padding
							if (compressedFrame->getByteLength()
									< MIN_ETHERNET_FRAME_BYTES) {
								compressedFrame->setByteLength(
										MIN_ETHERNET_FRAME_BYTES);
							}
							compressedFrame->setDisplayString(
									"b=15,15,rect,white,red,5");

							//save the frame
							compressed_frames->push_front(
									pair<unsigned int, PCFrame *>(roundMember,
											compressedFrame));

							tteScheduler->registerEvent(dd);
							dispatch_delay_container->push_front(dd);
						}

					} else {
						//member > member old
						//late permanence pit
						delete compressed_frames->front().second;
						// sicm->cancelAndDelete(itc->second);
						compressed_frames->clear();

						clock_stack->clear();

						if (!dispatch_delay_container->empty()) {

							tteScheduler->unregisterEvent(
									dispatch_delay_container->front());

							delete dispatch_delay_container->front();

						}

						dispatch_delay_container->clear();

						clock_stack->clear();

						pair<unsigned int, unsigned int> newClockPair =
								make_pair<unsigned int, unsigned int>(
										roundMember, compressed_pit);
						clock_stack->push_front(newClockPair);

						//create the new frame
						PCFrame *compressedFrame = new PCFrame("IN_FRAME");
						compressedFrame->setCtID(0);
						compressedFrame->setCtMarker(0);
						compressedFrame->setType(IN_FRAME);
						compressedFrame->setTransparent_clock(0);
						compressedFrame->setMembership_new(
								cp->getMembership_new());
						compressedFrame->setSync_domain(
								sicm->par("syncDomain"));
						compressedFrame->setSync_priority(
								sicm->par("syncPriority"));
						compressedFrame->setByteLength(
								46 + ETHER_MAC_FRAME_BYTES);
						compressedFrame->setIntegration_cycle(
								cp->getIntegrationCycle());
						//Padding
						if (compressedFrame->getByteLength()
								< MIN_ETHERNET_FRAME_BYTES) {
							compressedFrame->setByteLength(
									MIN_ETHERNET_FRAME_BYTES);
						}
						compressedFrame->setDisplayString(
								"b=15,15,rect,white,red,5");

						//save the frame
						compressed_frames->push_front(
								pair<unsigned int, PCFrame *>(roundMember,
										compressedFrame));
						tteScheduler->registerEvent(dd);
						dispatch_delay_container->push_front(dd);

					}

				} else {

					//empty
					pair<unsigned int, unsigned int> newClockPair = make_pair<
							unsigned int, unsigned int>(roundMember,
							compressed_pit);
					clock_stack->push_front(newClockPair);

					//create the new frame
					PCFrame *compressedFrame = new PCFrame("IN_FRAME");
					compressedFrame->setCtID(0);
					compressedFrame->setCtMarker(0);
					compressedFrame->setType(IN_FRAME);
					compressedFrame->setTransparent_clock(0);
					compressedFrame->setMembership_new(cp->getMembership_new());
					compressedFrame->setSync_domain(
							sicm->par("syncDomain"));
					compressedFrame->setSync_priority(
							sicm->par("syncPriority"));
					compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
					compressedFrame->setIntegration_cycle(
							cp->getIntegrationCycle());
					//Padding
					if (compressedFrame->getByteLength()
							< MIN_ETHERNET_FRAME_BYTES) {
						compressedFrame->setByteLength(
								MIN_ETHERNET_FRAME_BYTES);
					}
					compressedFrame->setDisplayString(
							"b=15,15,rect,white,red,5");

					//save the frame
					compressed_frames->push_front(
							pair<unsigned int, PCFrame *>(roundMember,
									compressedFrame));
					tteScheduler->registerEvent(dd);
					dispatch_delay_container->push_front(dd);

				}

				//inSchedule
			} else {
				//out of Schedule
				local_async_membership_r |= cp->getMembership_new();
				local_async_membership_f |= cp->getMembership_new();

				ev << "Out of schedule cpt" << tteScheduler->getTicks() << endl;
			} //out of Schedule

			delete cp;
			return;
		} //CP

		if (string(message->getName()).compare("DP") == 0) {

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

			compressed_frames->front().second->setCtID(0);

			cMsgPar *par = &compressed_frames->front().second->addPar(
					"created_total");
			par->setLongValue(tteScheduler->getTotalTicks());

			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
							"in"));

			delete compressed_frames->front().second;
			compressed_frames->pop_front();
			compressed_frames->clear();

			dispatch_delay_container->pop_front();

			dispatch_delay_container->clear();
			delete dd;
			return;
		} //dispatch point in time

		if (string(message->getName()).compare("cm_clock_corr_pit") == 0) {

			clock_corr = ((int) clock_stack->front().second)
					- (int) (sicm->par("cm_scheduled_pit"));

			tteScheduler->clockCorrection(clock_corr);

			outVector->record((double) clock_corr);
			if (sicm->par("write").boolValue()) {
				fprintf(fp, "%d ", tteScheduler->getCycles());
				fprintf(fp, "%d \n", clock_corr);
			}
			clock_stack->clear();
			return;

		}

		if (string(message->getName()).compare("cm_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (sicm->par("max_integration_cycles").intValue());

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
					>= sicm->par("cm_stable_threshold_async").intValue()) {
				duration = sicm->par("cm_restart_timeout");
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

				if (dispatch_delay_container->size() != 0) {

					if (dispatch_delay_container->front() != NULL) {

						tteScheduler->unregisterEvent(
								dispatch_delay_container->front());

						delete dispatch_delay_container->front();
					}

					dispatch_delay_container->clear();
				}
				if (compressed_frames->size() != 0) {

					if (compressed_frames->front().second != NULL) {

						delete compressed_frames->front().second;
					}
					compressed_frames->clear();
				}

				new (this) SI_CM_INTEGRATE();
				return;
			}

			if (clock_stack->empty()) {

				ev
						<< "DEBUG:SI_CM_STABLE: NO inSchedule PCF IN FRAME WAS RECEIVED"
						<< endl;
				local_sync_membership = 0;
			} else {

				local_sync_membership |= clock_stack->front().first;
			}

			if ((getValue(local_sync_membership, 32)
					< sicm->par("cm_stable_threshold_sync").intValue())
					&& (stable_cycle_counter
							< sicm->par("num_unstable_cycles").intValue())) {

				stable_cycle_counter++;

				tteScheduler->registerEvent(event2, true);

				return;

			}

			if ((getValue(local_sync_membership, 32)
					< sicm->par("cm_stable_threshold_sync").intValue())
					&& (stable_cycle_counter
							>= sicm->par("num_unstable_cycles").intValue())) {

				duration = sicm->par("cm_restart_timeout");
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

				if (dispatch_delay_container->size() != 0) {

					if (dispatch_delay_container->front() != NULL) {

						tteScheduler->unregisterEvent(
								dispatch_delay_container->front());

						delete dispatch_delay_container->front();
					}

					dispatch_delay_container->clear();
				}
				if (compressed_frames->size() != 0) {

					if (compressed_frames->front().second != NULL) {

						delete compressed_frames->front().second;
					}
					compressed_frames->clear();
				}

				new (this) SI_CM_INTEGRATE();
				return;

			}

			if (getValue(local_sync_membership, 32)
					>= sicm->par("cm_stable_threshold_sync").intValue()) {
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

		if (string(message->getName()).compare("DPCA") == 0) {
			DispatchDelay *dp = dynamic_cast<DispatchDelay *>(message);

			unsigned int roundMember = dp->getMembership_new();

			if (caCompressedFrames->find(roundMember)
					!= caCompressedFrames->end()) {

				delete caCompressedFrames->find(roundMember)->second;

				caCompressedFrames->erase(roundMember);

			} else {

				ev
						<< "Compression Function: Compressed Frame not found:round member:"
						<< roundMember << endl;

			}
			delete dp;
			return;
		}

		if (string(message->getName()).compare("CPCA") == 0) {

					delete 	message;
					return;
				}

		if (string(message->getName()).compare("CS_FRAME") == 0) {

					delete 	message;
					return;
				}


	} //schedulerIn message

}

SI_CM_UNSYNC::SI_CM_UNSYNC() {
	//Enter
	sicm->getDisplayString().setTagArg("i", 1, "black");
	sicm->bubble("CM_UNSYNC");

}

void SI_CM_UNSYNC::handleMessage(cMessage *message) {

//SI CM -
//relays CS in CM_UNSYNC
//relays CA with specified pcf_membership_new value

	if (message->arrivedOn("RCin")) {
		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//CM make all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == sicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== sicm->par("syncPriority").intValue()) {

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (sicm->par("max_transmission_delay"))) {

					ev
							<< "WARNING: SI_CM_UNSYNC: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< pf->getCtID() << endl;
					ev << "WARNING: SI_CM_UNSYNC getTransparentClock:"
							<< transparentClockToTicks(
									pf->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					compressionFunction(message, this->sicm);

					return;

				} else if (pf->getType() == CS_FRAME) {

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
					f_event->setDestinationGate(sicm->gate("schedulerIn"));

					if (pf->getType() == CS_FRAME) {
						f_event->setSchedulingPriority(0);
					} else {
						ev << "ERROR: expect a CS FRAME ! TYPE: "
								<< pf->getType() << endl;
					}

					tteScheduler->registerEvent(f_event);

					delete pf;

					return;

				} else if (pf->getType() == CA_FRAME) {

					compressionFunctionCA(message, this->sicm);
					return;
				} else {
					ev << "DEBUG: Error: SI_CM_UNSYNC UNKNOWN PCF TYPE " << (int)pf->getType()
							<< endl;
					delete pf;
				}

			} else {

			} //sync_priority

		} else {

		} //sync_domain

	}

	if (message->arrivedOn("schedulerIn")) {

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->sicm);
			return;
		}

		if ((string(message->getName()).compare("OW_CA") == 0)
				|| (string(message->getName()).compare("CA_FRAME") == 0)) {
			compressionFunctionCA(message, this->sicm);
			return;
		}

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			int currentTime = tteScheduler->getTicks();

			//local_clock = cm_sceduled_receive_pit
			tteScheduler->clockCorrection(
					currentTime - sicm->par("cm_scheduled_pit").intValue());
			local_integration_cycle = cp->getIntegrationCycle();
			local_sync_membership = cp->getMembership_new();

			if (getValue(local_sync_membership, 32)
					>= sicm->par("cm_unsync_to_sync_thrld").intValue()) {

				PCFrame *compressedFrame = new PCFrame("IN_FRAME");
				compressedFrame->setCtID(0);
				compressedFrame->setCtMarker(0);
				compressedFrame->setType(IN_FRAME);
				compressedFrame->setTransparent_clock(0);
				compressedFrame->setMembership_new(cp->getMembership_new());
				compressedFrame->setSync_domain(
						sicm->par("syncDomain"));
				compressedFrame->setSync_priority(
						sicm->par("syncPriority"));
				compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				compressedFrame->setIntegration_cycle(
						cp->getIntegrationCycle());

				//Padding
				if (compressedFrame->getByteLength()
						< MIN_ETHERNET_FRAME_BYTES) {
					compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

				compressed_frames->push_front(
						pair<unsigned int, PCFrame *>(cp->getMembership_new(),
								compressedFrame->dup()));

				local_sync_membership = cp->getMembership_new();
				local_integration_cycle = cp->getIntegrationCycle();
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
				dd->setDestinationGate(sicm->gate("schedulerIn"));
				dd->setMembership_new(cp->getMembership_new());
				dd->setTimer(sicm->par("dispatch_delay"));
				dd->setSchedulingPriority(3);

				tteScheduler->registerEvent(dd);

				dispatch_delay_container->push_front(dd);

				unsigned int member = cp->getMembership_new();

				unsigned int compressedPit = tteScheduler->getTicks();

				clock_stack->push_front(
						pair<unsigned int, unsigned int>(member,
								compressedPit));

				tteScheduler->registerEvent(event2);
				tteScheduler->registerEvent(event4);
				tteScheduler->registerEvent(event5);

				delete cp;
				new (this) SI_CM_SYNC();

				return;
			}
			delete cp;
			return;
		} //compressed IN_FRAME

		if (string(message->getName()).compare("DP") == 0) {

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

			compressed_frames->front().second->setCtID(0);

			cMsgPar *par = &compressed_frames->front().second->addPar(
					"created_total");
			par->setLongValue(tteScheduler->getTotalTicks());

			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
							"in"));

			delete compressed_frames->front().second;

			delete compressed_frames->front().second;

			compressed_frames->clear();

			dispatch_delay_container->pop_front();

			dispatch_delay_container->clear();
			delete dd;
			return;
		} //dispatch point in time

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			FrameEvent *et = dynamic_cast<FrameEvent *>(message);

			if (et->getPcfType() == CS_FRAME) {

				PCFrame *frame = new PCFrame("CS_Frame");

				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				frame->setSync_domain(sicm->par("syncDomain"));
				frame->setSync_priority(sicm->par("syncPriority"));
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

				sicm->sendDirect(
						frame->dup(),
						sicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				sicm->sendDirect(
						frame->dup(),
						sicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				sicm->sendDirect(
						frame->dup(),
						sicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				duration = sicm->par("cm_ca_enabled_timeout");
				event->setTimer(duration);

				//local_clock=0
				tteScheduler->clockCorrection(tteScheduler->getTicks());

				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				delete frame;
				delete et;

				new (this) SI_CM_ENABLED();

				return;
			}
		} //CS FRAME

		if (string(message->getName()).compare("CPCA") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			if (getValue(cp->getMembership_new(), 32)
					> sicm->par("cm_sync_threshold_sync").intValue()) {

				duration = sicm->par("cm_ca_enabled_timeout");
				event->setTimer(duration);

				//local_clock=0
				tteScheduler->clockCorrection(tteScheduler->getTicks());
				local_integration_cycle = 0;
				local_sync_membership = 0;
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				//create the new frame
				PCFrame *compressedFrame = new PCFrame("CA_FRAME");
				compressedFrame->setCtID(0);
				compressedFrame->setCtMarker(0);
				compressedFrame->setType(CA_FRAME);
				compressedFrame->setTransparent_clock(0);
				compressedFrame->setMembership_new(cp->getMembership_new());
				compressedFrame->setSync_domain(
						sicm->par("syncDomain"));
				compressedFrame->setSync_priority(
						sicm->par("syncPriority"));
				compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				compressedFrame->setIntegration_cycle(local_integration_cycle);
				//Padding
				if (compressedFrame->getByteLength()
						< MIN_ETHERNET_FRAME_BYTES) {
					compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

				caCompressedFrames->insert(
						pair<unsigned int, PCFrame *>(cp->getMembership_new(),
								compressedFrame));

				DispatchDelay *dd = new DispatchDelay("DPCA", TIMER_EVENT);
				dd->setDestinationGate(sicm->gate("schedulerIn"));
				dd->setMembership_new(cp->getMembership_new());
				dd->setTimer(sicm->par("dispatch_delay"));
				dd->setSchedulingPriority(3);

				tteScheduler->registerEvent(dd);

				delete cp;
				new (this) SI_CM_ENABLED();

				return;
			}
			delete cp;
			return;

		}

		if (string(message->getName()).compare("DPCA") == 0) {
			DispatchDelay *dp = dynamic_cast<DispatchDelay *>(message);

			unsigned int roundMember = dp->getMembership_new();

			if (caCompressedFrames->find(roundMember)
					!= caCompressedFrames->end()) {

				delete caCompressedFrames->find(roundMember)->second;

				caCompressedFrames->erase(roundMember);

			} else {

				ev
						<< "Compression Function: Compressed Frame not found:round member:"
						<< roundMember << endl;

			}
			delete dp;
			return;
		}
	} //schedulerIn

}

SI_CM_SYNC::SI_CM_SYNC() {

	sicm->getDisplayString().setTagArg("i", 1, "yellow");
	sicm->bubble("CM_SYNC");

	//local_clock==cm_async_eval_pit;
	//Async_Clique_Detektion();

	//local_clock==cm_sync_eval_pit;
	//Sync_Clique_Detektion();
	//stable_cycle_counter++;

	//local_clock==cm_clock_corr_pit
	//local_clock=local_clock+clock_corr;

}

void SI_CM_SYNC::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//CM make all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == sicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== sicm->par("syncPriority").intValue()) {

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) (sicm->par("max_transmission_delay"))) {

					ev
							<< "WARNING: SI_CM_SYNC: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;

				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					compressionFunction(message, this->sicm);
					return;
				} else if (pf->getType() == CS_FRAME) {

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
									f_event->setDestinationGate(sicm->gate("schedulerIn"));

									if (pf->getType() == CS_FRAME) {
										f_event->setSchedulingPriority(0);
									} else {
										ev << "ERROR: expect a CS FRAME ! TYPE: "
												<< pf->getType() << endl;
									}

									tteScheduler->registerEvent(f_event);

									delete pf;

									return;

								} else if (pf->getType() == CA_FRAME) {

									compressionFunctionCA(message, this->sicm);
									return;
				} else {

					delete pf;
					ev << "DEBUG:  SI_CM_SYNC FRAME DROPPED  " << endl;
					return;
				}
				delete pf;
			} else {

			} //sync_priority

		} else {

		} //sync_domain

	}

	if (message->arrivedOn("schedulerIn")) {

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->sicm);
			return;
		}

		if ((string(message->getName()).compare("OW_CA") == 0)
				|| (string(message->getName()).compare("CA_FRAME") == 0)) {
			compressionFunctionCA(message, this->sicm);
			return;
		}

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			int compressed_pit = tteScheduler->getTicks();

			if (inSchedule2(compressed_pit,
					sicm->par("cm_scheduled_pit"),
					sicm->par("acceptance_window"))) {

				int roundMember = getValue(cp->getMembership_new(), 32);

				DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
				dd->setDestinationGate(sicm->gate("schedulerIn"));
				dd->setMembership_new(roundMember);
				dd->setTimer(sicm->par("dispatch_delay"));
				dd->setSchedulingPriority(3);

				if (!clock_stack->empty()) {

					pair<unsigned int, unsigned int> old_pair =
							clock_stack->front();
					//
					int old_membership = getValue(old_pair.first, 32);
					int compressed_pit_old = old_pair.second;

					if (roundMember < old_membership) {

						//no replace here
						delete dd;
						delete cp;
						return;

					} else if (roundMember == old_membership) {

						if (compressed_pit > compressed_pit_old) {
							//late permanence pit
							delete compressed_frames->front().second;

							compressed_frames->clear();

							clock_stack->clear();

							if (!dispatch_delay_container->empty()) {

								tteScheduler->unregisterEvent(
										dispatch_delay_container->front());

								delete dispatch_delay_container->front();

							}

							dispatch_delay_container->clear();

							clock_stack->clear();

							pair<unsigned int, unsigned int> newClockPair =
									make_pair<unsigned int, unsigned int>(
											roundMember, compressed_pit);
							clock_stack->push_front(newClockPair);

							//create the new frame
							PCFrame *compressedFrame = new PCFrame("IN_FRAME");
							compressedFrame->setCtID(0);
							compressedFrame->setCtMarker(0);
							compressedFrame->setType(IN_FRAME);
							compressedFrame->setTransparent_clock(0);
							compressedFrame->setMembership_new(
									cp->getMembership_new());
							compressedFrame->setSync_domain(
									sicm->par("syncDomain"));
							compressedFrame->setSync_priority(
									sicm->par("syncPriority"));
							compressedFrame->setByteLength(
									46 + ETHER_MAC_FRAME_BYTES);
							compressedFrame->setIntegration_cycle(
									cp->getIntegrationCycle());
							//Padding
							if (compressedFrame->getByteLength()
									< MIN_ETHERNET_FRAME_BYTES) {
								compressedFrame->setByteLength(
										MIN_ETHERNET_FRAME_BYTES);
							}
							compressedFrame->setDisplayString(
									"b=15,15,rect,white,red,5");

							//save the frame

							compressed_frames->push_front(
									pair<unsigned int, PCFrame *>(roundMember,
											compressedFrame));
							tteScheduler->registerEvent(dd);
							dispatch_delay_container->push_front(dd);
						}

					} else {
						//member > member old

						delete compressed_frames->front().second;

						compressed_frames->clear();

						clock_stack->clear();

						if (!dispatch_delay_container->empty()) {

							tteScheduler->unregisterEvent(
									dispatch_delay_container->front());

							delete dispatch_delay_container->front();

						}

						dispatch_delay_container->clear();

						clock_stack->clear();

						pair<unsigned int, unsigned int> newClockPair =
								make_pair<unsigned int, unsigned int>(
										roundMember, compressed_pit);
						clock_stack->push_front(newClockPair);

						//create the new frame
						PCFrame *compressedFrame = new PCFrame("IN_FRAME");
						compressedFrame->setCtID(0);
						compressedFrame->setCtMarker(0);
						compressedFrame->setType(IN_FRAME);
						compressedFrame->setTransparent_clock(0);
						compressedFrame->setMembership_new(
								cp->getMembership_new());
						compressedFrame->setSync_domain(
								sicm->par("syncDomain"));
						compressedFrame->setSync_priority(
								sicm->par("syncPriority"));
						compressedFrame->setByteLength(
								46 + ETHER_MAC_FRAME_BYTES);
						compressedFrame->setIntegration_cycle(
								cp->getIntegrationCycle());
						//Padding
						if (compressedFrame->getByteLength()
								< MIN_ETHERNET_FRAME_BYTES) {
							compressedFrame->setByteLength(
									MIN_ETHERNET_FRAME_BYTES);
						}
						compressedFrame->setDisplayString(
								"b=15,15,rect,white,red,5");

						//save the frame
						pair<unsigned int, PCFrame *> newPair = make_pair<
								unsigned int, PCFrame *>(roundMember,
								compressedFrame);
						compressed_frames->push_front(newPair);
						tteScheduler->registerEvent(dd);
						dispatch_delay_container->push_front(dd);

					}

				} else {

					//empty
					pair<unsigned int, unsigned int> newClockPair = make_pair<
							unsigned int, unsigned int>(roundMember,
							compressed_pit);
					clock_stack->push_front(newClockPair);

					//create the new frame
					PCFrame *compressedFrame = new PCFrame("IN_FRAME");
					compressedFrame->setCtID(0);
					compressedFrame->setCtMarker(0);
					compressedFrame->setType(IN_FRAME);
					compressedFrame->setTransparent_clock(0);
					compressedFrame->setMembership_new(cp->getMembership_new());
					compressedFrame->setSync_domain(
							sicm->par("syncDomain"));
					compressedFrame->setSync_priority(
							sicm->par("syncPriority"));
					compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
					compressedFrame->setIntegration_cycle(
							cp->getIntegrationCycle());
					//Padding
					if (compressedFrame->getByteLength()
							< MIN_ETHERNET_FRAME_BYTES) {
						compressedFrame->setByteLength(
								MIN_ETHERNET_FRAME_BYTES);
					}
					compressedFrame->setDisplayString(
							"b=15,15,rect,white,red,5");

					//save the frame

					compressed_frames->push_front(
							pair<unsigned int, PCFrame *>(roundMember,
									compressedFrame));
					tteScheduler->registerEvent(dd);
					dispatch_delay_container->push_front(dd);

				}

				//inSchedule
			} else {
				//out of Schedule
				local_async_membership_r |= cp->getMembership_new();
				local_async_membership_f |= cp->getMembership_new();

				ev << "Out of schedule cpt" << tteScheduler->getTicks() << endl;
			}
			delete cp;
			return;
		} //CP

		if (string(message->getName()).compare("DP") == 0) {
			ev << "SI_CM_SYNC: Scheduler->startupTime"
					<< tteScheduler->getTotalTicks() << endl;
			ev << "SI_CM_SYNC: Simtime-> startupTime" << simTime() << endl;

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

			compressed_frames->front().second->setCtID(0);

			cMsgPar *par = &compressed_frames->front().second->addPar(
					"created_total");
			par->setLongValue(tteScheduler->getTotalTicks());

			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
							"in"));

			delete compressed_frames->front().second;

			compressed_frames->clear();

			dispatch_delay_container->pop_front();

			dispatch_delay_container->clear();
			delete dd;
			return;
		} //dispatch point in time

		if (string(message->getName()).compare("cm_clock_corr_pit") == 0) {

			clock_corr = ((int) clock_stack->front().second)
					- (int) (sicm->par("cm_scheduled_pit"));

			tteScheduler->clockCorrection(clock_corr);

			clock_stack->clear();

		}

		if (string(message->getName()).compare("cm_inc_pit") == 0) {

			local_integration_cycle = (local_integration_cycle + 1)
					% (sicm->par("max_integration_cycles").intValue());

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
					>= sicm->par("cm_sync_threshold_async").intValue()) {
				duration = sicm->par("cm_restart_timeout");
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

				if (dispatch_delay_container->size() != 0) {

					if (dispatch_delay_container->front() != NULL) {

						tteScheduler->unregisterEvent(
								dispatch_delay_container->front());

						delete dispatch_delay_container->front();
					}

					dispatch_delay_container->clear();
				}
				if (compressed_frames->size() != 0) {

					if (compressed_frames->front().second != NULL) {

						delete compressed_frames->front().second;
					}
					compressed_frames->clear();
				}

				new (this) SI_CM_INTEGRATE();
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
					< sicm->par("cm_sync_threshold_sync").intValue()) {

				duration = sicm->par("cm_restart_timeout");
				;
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
				//ClearForTheUnsycState();

				clock_stack->clear();

				if (dispatch_delay_container->size() != 0) {

					if (dispatch_delay_container->front() != NULL) {

						tteScheduler->unregisterEvent(
								dispatch_delay_container->front());

						delete dispatch_delay_container->front();
					}

					dispatch_delay_container->clear();
				}
				if (compressed_frames->size() != 0) {

					if (compressed_frames->front().second != NULL) {

						delete compressed_frames->front().second;
					}
					compressed_frames->clear();
				}

				new (this) SI_CM_INTEGRATE();
				return;

			}

			tteScheduler->registerEvent(event2, true);

			if (((getValue(local_sync_membership, 32)
					>= sicm->par("cm_sync_threshold_sync").intValue())
					&& (stable_cycle_counter
							< sicm->par("num_stable_cycles").intValue())
					&& (sicm->par("cm_sync_to_stable_enabled").boolValue()))) {

				stable_cycle_counter++;
				return;
			}

			if (((getValue(local_sync_membership, 32)
					>= sicm->par("cm_sync_threshold_sync").intValue())
					&& (stable_cycle_counter
							>= sicm->par("num_stable_cycles").intValue())
					&& (sicm->par("cm_sync_to_stable_enabled").boolValue()))) {

				stable_cycle_counter = 0;

				new (this) SI_CM_STABLE();
				return;
			}
			if ((getValue(local_sync_membership, 32)
					>= sicm->par("cm_sync_threshold_sync").intValue())
					&& (sicm->par("cm_sync_to_stable_enabled").boolValue())) {

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

		}

		if (string(message->getName()).compare("DPCA") == 0) {
			DispatchDelay *dp = dynamic_cast<DispatchDelay *>(message);

			unsigned int roundMember = dp->getMembership_new();

			if (caCompressedFrames->find(roundMember)
					!= caCompressedFrames->end()) {

				delete caCompressedFrames->find(roundMember)->second;

				caCompressedFrames->erase(roundMember);

			} else {

				ev
						<< "Compression Function: Compressed Frame not found:round member:"
						<< roundMember << endl;

			}
			delete dp;
			return;
		}

		if (string(message->getName()).compare("CPCA") == 0) {

					delete 	message;
					return;
				}


		if (string(message->getName()).compare("CS_FRAME") == 0) {

					delete 	message;
					return;
				}

	} //schedulerIn message

}

SI_CM_ENABLED::SI_CM_ENABLED() {

	//Enter

	sicm->getDisplayString().setTagArg("i", 1, "white");
	sicm->bubble("CM_ENABLED");

	tteScheduler->registerEvent(event);

	//local_timer=false;
	//TW(duration);
	//local_timer=true;

}

void SI_CM_ENABLED::handleMessage(cMessage *message) {

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("ASYNCHRON") == 0) {
			duration = 0;
			duration = sicm->par("cm_wait_4_in_timeout");
			event->setTimer(duration);

			//local_clock=0;
			tteScheduler->clockCorrection(tteScheduler->getTicks());

			local_integration_cycle = 0;
			local_sync_membership = 0;
			local_async_membership = 0;

			local_async_membership_r = 0;
			local_async_membership_f = 0;

			ev
					<< "SI_CM_ENABLED :: ASYNCHRON TIMER EXPIRED, NEXT STATE -> SI_CM_WAIT_4_IN"
					<< endl;

			new (this) SI_CM_WAIT_4_IN();
			return;

		}

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->sicm);
			return;
		}

		if ((string(message->getName()).compare("OW_CA") == 0)
				|| (string(message->getName()).compare("CA_FRAME") == 0)) {
			compressionFunctionCA(message, this->sicm);
			return;
		}

		if (string(message->getName()).compare("CPCA") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			unsigned int member = cp->getMembership_new();

			ev << "SICM_ENABLED::CPCA member round " << cp->getMembership_new()
					<< endl;

			DispatchDelay *dd = new DispatchDelay("DPCA", TIMER_EVENT);
			dd->setDestinationGate(sicm->gate("schedulerIn"));
			dd->setMembership_new(member);
			dd->setTimer(sicm->par("dispatch_delay"));
			dd->setSchedulingPriority(3);

			//create the new frame
			PCFrame *compressedFrame = new PCFrame("CA_FRAME");
			compressedFrame->setCtID(0);
			compressedFrame->setCtMarker(0);
			compressedFrame->setType(CA_FRAME);
			compressedFrame->setTransparent_clock(0);
			compressedFrame->setMembership_new(member);
			compressedFrame->setSync_domain(
					sicm->par("syncDomain"));
			compressedFrame->setSync_priority(
					sicm->par("syncPriority"));
			compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
			compressedFrame->setIntegration_cycle(local_integration_cycle);
			//Padding
			if (compressedFrame->getByteLength() < MIN_ETHERNET_FRAME_BYTES) {
				compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
			}

			compressedFrame->setDisplayString("b=15,15,rect,white,blue,5");

			caCompressedFrames->insert(
					pair<unsigned int, PCFrame *>(member, compressedFrame));

			tteScheduler->registerEvent(dd);

			delete cp;
			return;
		} //CPCA

		if (string(message->getName()).compare("DPCA") == 0) {

			DispatchDelay *dp = dynamic_cast<DispatchDelay *>(message);

			unsigned int roundMember = dp->getMembership_new();

			if (caCompressedFrames->find(roundMember)
					!= caCompressedFrames->end()) {

				PCFrame *frame = caCompressedFrames->find(roundMember)->second;
				frame->setCtID(0);
				frame->setCtMarker(0);
				frame->setTransparent_clock(0);
				cMsgPar *par = &frame->addPar("created_total");
				par->setLongValue(tteScheduler->getTotalTicks());

				sicm->sendDirect(
						frame->dup(),
						sicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
								"in"));
				sicm->sendDirect(
						frame->dup(),
						sicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
								"in"));
				sicm->sendDirect(
						frame->dup(),
						sicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
								"in"));

				delete caCompressedFrames->find(roundMember)->second;

				caCompressedFrames->erase(roundMember);

			} else {

				ev
						<< "Compression Function: Compressed Frame not found:round member:"
						<< roundMember << endl;

			}
			delete dp;
			return;
		}

		if (string(message->getName()).compare("CS_FRAME") == 0) {

			delete message;
			return;
		}
		if (string(message->getName()).compare("DP") == 0) {

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

			delete compressed_frames->front().second;

			compressed_frames->clear();

			dispatch_delay_container->pop_front();

			dispatch_delay_container->clear();

			delete dd;
			return;
		} //dispatch point in time

	}

	if (message->arrivedOn("RCin")) {

		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//CM make all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == sicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== sicm->par("syncPriority").intValue()) {

				ev << "DEBUG: SI_CM_ENABLED membership new value"
						<< pf->getMembership_new() << endl;
				ev << "DEBUG: SI_CM_ENABLED membership new number of SM"
						<< getValue(pf->getMembership_new(), 32) << endl;
				ev << "DEBUG: SI_CM_ENABLED LOCAL CLOCK "
						<< tteScheduler->getTicks() << endl;

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int) sicm->par("max_transmission_delay")) {

					ev
							<< "WARNING: SI_CM_ENABLED: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< pf->getCtID() << endl;
					ev << "WARNING: SI_CM_ENABLED getTransparentClock:"
							<< transparentClockToTicks(
									pf->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
							<< endl;
					ev << "WARNING: Receive delay: "
							<< (tteScheduler->getTotalTicks()
									- pf->par("received_total").intValue())
							<< endl;
					ev << "WARNING: TYPE: " << pf->getType() << endl;
				}

			 if (pf->getType() == IN_FRAME) {

					compressionFunction(message, this->sicm);
					return;
			 } else if (pf->getType() == CS_FRAME) {

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
			 					f_event->setDestinationGate(sicm->gate("schedulerIn"));

			 					if (pf->getType() == CS_FRAME) {
			 						f_event->setSchedulingPriority(0);
			 					} else {
			 						ev << "ERROR: expect a CS FRAME ! TYPE: "
			 								<< pf->getType() << endl;
			 					}

			 					tteScheduler->registerEvent(f_event);

			 					delete pf;

			 					return;

			 				} else if (pf->getType() == CA_FRAME) {

			 					compressionFunctionCA(message, this->sicm);
			 					return;
			 } else {


					delete pf;
					return;
				}
				delete pf;
			} else {

			} //sync_priority

		} else {

		} //sync_domain

	}

}

SI_CM_WAIT_4_IN::SI_CM_WAIT_4_IN() {
	//Enter
	//cout<<"Enter->SI_CM_WAIT_4_IN \n"<<endl;
	sicm->getDisplayString().setTagArg("i", 1, "cyan");
	sicm->bubble("CM_WAIT_4_IN");

	tteScheduler->registerEvent(event);
	//local_timer=false;
	//TW(duration);
	//local_timer=true;

}

void SI_CM_WAIT_4_IN::handleMessage(cMessage *message) {

	if (message->arrivedOn("RCin")) {
		//ack to the buffer
		RCBuffer *rcBuffer = dynamic_cast<RCBuffer*>(message->getSenderModule());
		if (rcBuffer)
			rcBuffer->resetBag();

		//CM make all PCF frames permanent before usage

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		if (pf->getSync_domain() == sicm->par("syncDomain").intValue()) {

			if (pf->getSync_priority()
					== sicm->par("syncPriority").intValue()) {

				if ((transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()))
						> (unsigned int)sicm->par("max_transmission_delay")) {

					ev
							<< "WARNING: SI_CM_WAIT_4_IN: (pkt->getTransparent_clock()) > max_transmission_delay "
							<< endl;
					ev << "WARNING: SI_CM_WAIT_4_IN getTransparentClock:"
							<< transparentClockToTicks(
									pf->getTransparent_clock(),
									tteScheduler->par("tick").doubleValue())
							<< endl;
					ev << "WARNING: Receive delay: "
							<< (tteScheduler->getTotalTicks()
									- pf->par("received_total").intValue())
							<< endl;
					ev << "WARNING: TYPE: " << pf->getType() << endl;
				}

				//IN FRAME ?
				if (pf->getType() == IN_FRAME) {

					//relay to compression function
					compressionFunction(message, this->sicm);

					return;
				} else if (pf->getType() == CS_FRAME) {

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
									f_event->setDestinationGate(sicm->gate("schedulerIn"));

									if (pf->getType() == CS_FRAME) {
										f_event->setSchedulingPriority(0);
									} else {
										ev << "ERROR: expect a CS FRAME ! TYPE: "
												<< pf->getType() << endl;
									}

									tteScheduler->registerEvent(f_event);

									delete pf;

									return;

								} else if (pf->getType() == CA_FRAME) {

									compressionFunctionCA(message, this->sicm);
									return;
				} else {


					delete pf;
					return;

				}
				delete pf;
			} else {

			} //sync_priority

		} else {

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
					<< "SI_CM_WAIT_4_IN :: ASYNCHRON TIMER EXPIRED, NEXT STATE -> SI_CM_UNSYNC"
					<< endl;

			//clearForTheNextState();

			new (this) SI_CM_UNSYNC();

			return;

		}

		if ((string(message->getName()).compare("OW") == 0)
				|| (string(message->getName()).compare("IN_FRAME") == 0)) {
			compressionFunction(message, this->sicm);
			return;
		}

		if ((string(message->getName()).compare("OW_CA") == 0)
				|| (string(message->getName()).compare("CA_FRAME") == 0)) {
			compressionFunctionCA(message, this->sicm);
			return;
		}

		if (string(message->getName()).compare("CP") == 0) {

			CompressedPIT *cp = dynamic_cast<CompressedPIT *>(message);

			local_sync_membership = cp->getMembership_new();
			local_integration_cycle = cp->getIntegrationCycle();

			int currentTime = tteScheduler->getTicks();
			//local_clock = cm_sceduled_receive_pit
			tteScheduler->clockCorrection(
					currentTime - sicm->par("cm_scheduled_pit").intValue());

			if (getValue(local_sync_membership, 32)
					>= sicm->par("cm_sync_threshold_sync").intValue()) {

				//create the new frame
				PCFrame *compressedFrame = new PCFrame("IN_FRAME");
				compressedFrame->setCtID(0);
				compressedFrame->setCtMarker(0);
				compressedFrame->setType(IN_FRAME);
				compressedFrame->setTransparent_clock(0);
				compressedFrame->setMembership_new(cp->getMembership_new());
				compressedFrame->setSync_domain(
						sicm->par("syncDomain"));
				compressedFrame->setSync_priority(
						sicm->par("syncPriority"));
				compressedFrame->setByteLength(46 + ETHER_MAC_FRAME_BYTES);
				compressedFrame->setIntegration_cycle(
						cp->getIntegrationCycle());

				ev << "SI_CM_WAIT_4_IN:Compressed Frame int cycle "
						<< compressedFrame->getIntegration_cycle() << endl;
				ev << "SI_CM_WAIT_4_IN:Compressed Frame Number of SMs"
						<< getValue(compressedFrame->getMembership_new(), 32)
						<< endl;

				//Padding
				if (compressedFrame->getByteLength()
						< MIN_ETHERNET_FRAME_BYTES) {
					compressedFrame->setByteLength(MIN_ETHERNET_FRAME_BYTES);
				}

				compressedFrame->setDisplayString("b=15,15,rect,white,red,5");

				compressed_frames->push_front(
						pair<unsigned int, PCFrame *>(cp->getMembership_new(),
								compressedFrame));

				local_integration_cycle =
						compressed_frames->front().second->getIntegration_cycle();
				local_sync_membership = cp->getMembership_new();
				local_async_membership = 0;
				local_async_membership_r = 0;
				local_async_membership_f = 0;

				DispatchDelay *dd = new DispatchDelay("DP", TIMER_EVENT);
				dd->setDestinationGate(sicm->gate("schedulerIn"));
				dd->setMembership_new(cp->getMembership_new());
				dd->setTimer(sicm->par("dispatch_delay"));
				dd->setSchedulingPriority(3);

				tteScheduler->registerEvent(dd);
				dispatch_delay_container->push_front(dd);

				clock_stack->push_front(
						pair<unsigned int, unsigned int>(
								cp->getMembership_new(),
								tteScheduler->getTicks()));

				tteScheduler->unregisterEvent(event);

				tteScheduler->registerEvent(event2);
				tteScheduler->registerEvent(event4);
				tteScheduler->registerEvent(event5);

				delete cp;
				new (this) SI_CM_SYNC();

				return;
			}
			delete cp;
			return;
		} //compressed IN_FRAME

		if (string(message->getName()).compare("DP") == 0) {

			DispatchDelay *dd = dynamic_cast<DispatchDelay *>(message);

			cMsgPar *par = &compressed_frames->front().second->addPar(
					"created_total");
			par->setLongValue(tteScheduler->getTotalTicks());

			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 0)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 1)->gate(
							"in"));
			sicm->sendDirect(
					compressed_frames->front().second->dup(),
					sicm->getParentModule()->getSubmodule("pcf_out", 2)->gate(
							"in"));

			delete compressed_frames->front().second;

			compressed_frames->clear();

			dispatch_delay_container->pop_front();

			dispatch_delay_container->clear();
			delete dd;
			return;
		} //dispatch point in time

		if (string(message->getName()).compare("DPCA") == 0) {
			DispatchDelay *dp = dynamic_cast<DispatchDelay *>(message);

			unsigned int roundMember = dp->getMembership_new();

			if (caCompressedFrames->find(roundMember)
					!= caCompressedFrames->end()) {

				delete caCompressedFrames->find(roundMember)->second;

				caCompressedFrames->erase(roundMember);

			} else {

				ev
						<< "Compression Function: Compressed Frame not found:round member:"
						<< roundMember << endl;

			}
			delete dp;
			return;
		}
		if (string(message->getName()).compare("CPCA") == 0) {

					delete 	message;
					return;
				}

		if (string(message->getName()).compare("CS_FRAME") == 0) {

					delete 	message;
					return;
				}
	} //schedulerIn

}

void SI_CM_WAIT_4_IN::compressionFunction(cMessage *message, SICM *sicm) {

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
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
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
						<< "SI_CM_WAIT_4_IN: There is a compression Function with matching integration cycle collecting PCF's "
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

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size").intValue());

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_WAIT_4_IN: Compression Function:Collection Phase started"
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
						<< "Compression Function:WAIT_4_IN: ERROR : OW: no such integration cycle: "
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
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead").intValue()
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_WAIT_4_IN::compressionFunctionCA(cMessage *message, SICM *sicm) {

	if (message->arrivedOn("RCin")) {

		//CM make all PCF frames permanent before usage

		PCFrame *pf = NULL;
		pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//CA FRAME ?
		if (pf->getType() == CA_FRAME) {

			FrameEvent *f_event = new FrameEvent("CA_FRAME", TIMER_EVENT);

			f_event->setMember((pf)->getMembership_new());
			f_event->setPcfType((pf)->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());
			f_event->setTimer(permanence_delay);

			f_event->setDestinationGate(sicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;
		} //gate RCin (PCF FRAME)

		ev << "ERROR COMP FUNC CA" << endl;
		delete pf;
		return;

	}

	if ((message)->arrivedOn("schedulerIn")) {

		if (string((message)->getName()).compare("CA_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			int int_cycle = evt->getIntegrationCycle();
			uint64_t current_ppt = tteScheduler->getTicks();

			if (ca_compression_stack->find(int_cycle)
					!= ca_compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's
				ca_compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "there is a compression function with matching integration cycle collecting PCF's"
						<< endl;
				ev << "cycle_found" << int_cycle << endl;
				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase

				vector<pair<unsigned int, unsigned int> > *ppt = new vector<
						pair<unsigned int, unsigned int> >;

				ppt->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				ca_compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, ppt));

				OWCounter *ow = new OWCounter("OW_CA", TIMER_EVENT);

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_WAIT_4_IN Compression Function:Collection Phase started"
						<< endl;
				ev << "SI_CM_WAIT_4_IN Compression Fuction :(vector size)"
						<< ca_compression_stack->find(int_cycle)->second->size()
						<< endl;
				ev << "SI_CM_WAIT_4_IN Compression Function : int cycle"
						<< int_cycle << endl;

				delete evt;
				return;
			}

		} //handle FrameEvent

		if (string(message->getName()).compare("OW_CA") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (ca_compression_stack->find(owc->getIntegrationCycle())
					== ca_compression_stack->end()) {

				ev
						<< "DEBUG Compression Funktion: OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size()) {
					//no new pcf IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						ev << "Compression Function round member" << roundMember
								<< endl;

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< ca_compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_SYNC::compressionFunction(cMessage *message, SICM *sicm) {

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

			f_event->setDestinationGate(sicm->gate("schedulerIn"));
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
						<< "SI_CM_SYNC: There is a compression Function with matching integration cycle collecting PCF's "
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

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_SYNC: Compression Function:Collection Phase started"
						<< endl;

				delete evt;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:SI_CM_SYNC: ERROR : OW: no such integration cycle: "
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
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_SYNC::compressionFunctionCA(cMessage *message, SICM *sicm) {

	if (message->arrivedOn("RCin")) {

		//CM make all PCF frames permanent before usage

		PCFrame *pf = NULL;
		pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//CA FRAME ?
		if ((pf)->getType() == CA_FRAME) {

			FrameEvent *f_event = new FrameEvent("CA_FRAME", TIMER_EVENT);

			f_event->setMember((pf)->getMembership_new());
			f_event->setPcfType((pf)->getType());

			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

		ev << "ERROR COMP FUNC CA" << endl;
		delete pf;
		return;

	}

	if ((message)->arrivedOn("schedulerIn")) {

		if (string((message)->getName()).compare("CA_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			ev << "COMP FNCT SICM ENABLED MEMBER(CA EVENT)"
					<< (evt)->getMember() << endl;
			ev << "COMP FNCT SICM ENABLED INT CYCL(CA EVENT)"
					<< (evt)->getPcfType() << endl;

			int int_cycle = evt->getIntegrationCycle();
			uint64_t current_ppt = tteScheduler->getTicks();

			if (ca_compression_stack->find(int_cycle)
					!= ca_compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's
				ca_compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "there is a compression function with matching integration cycle collecting PCF's"
						<< endl;
				ev << "cycle_found" << int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase

				vector<pair<unsigned int, unsigned int> > *ppt = new vector<
						pair<unsigned int, unsigned int> >;

				ppt->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				ca_compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, ppt));

				OWCounter *ow = new OWCounter("OW_CA", TIMER_EVENT);

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev << "SI_CM_SYNC:Compression Function:Collection Phase started"
						<< endl;
				ev << "SI_CM_SYNC:Compression Fuction :(vector size)"
						<< ca_compression_stack->find(int_cycle)->second->size()
						<< endl;
				ev << "SI_CM_SYNC:Compression Function : int cycle" << int_cycle
						<< endl;
				delete evt;
				return;
			}

		} //handle FrameEvent

		if (string(message->getName()).compare("OW_CA") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (ca_compression_stack->find(owc->getIntegrationCycle())
					== ca_compression_stack->end()) {

				ev
						<< "DEBUG Compression Funktion: OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size()) {
					//no new pcf IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters").intValue());

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						ev << "Compression Function round member" << roundMember
								<< endl;

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						tteScheduler->registerEvent(cpit);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						tteScheduler->registerEvent(cpit);
						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
					} else {
						ev
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< ca_compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_INTEGRATE::compressionFunction(cMessage *message, SICM *sicm) {

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
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
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
						<< "SI_CM_INTEGRATE: There is a compression Function with matching integration cycle collecting PCF's "
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

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_INTEGRATE: Compression Function:Collection Phase started"
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
						<< "Compression Function:SI_CM_INTEGRATE: ERROR : OW: no such integration cycle: "
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
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function SI_CM_INTEGRATE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function SI_CM_INTEGRATE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function SI_CM_INTEGRATE: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_INTEGRATE::compressionFunctionCA(cMessage *message, SICM *sicm) {

	if (message->arrivedOn("RCin")) {

		//CM make all PCF frames permanent before usage

		PCFrame *pf = NULL;
		pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//CA FRAME ?
		if (pf->getType() == CA_FRAME) {
			ev << "COMP FNCT SI_CM_INTEGRATE MEMBER"
					<< (pf)->getMembership_new() << endl;
			ev << "COMP FNCT SI_CM_INTEGRATE INT CYCL"
					<< (pf)->getIntegration_cycle() << endl;

			FrameEvent *f_event = new FrameEvent("CA_FRAME", TIMER_EVENT);

			f_event->setMember((pf)->getMembership_new());
			f_event->setPcfType((pf)->getType());
			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

			//save the event
			//ca_e_container->insert(make_pair(membership_new, f_event));

			//

		} //gate RCin (PCF FRAME)

		ev << "ERROR COMP FUNC CA" << endl;
		delete pf;
		return;

	}

	if ((message)->arrivedOn("schedulerIn")) {

		if (string((message)->getName()).compare("CA_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			ev << "COMP FNCT SI_CM_INTEGRATE MEMBER(CA EVENT)"
					<< (evt)->getMember() << endl;
			ev << "COMP FNCT SI_CM_INTEGRATE INT CYCL(CA EVENT)"
					<< (evt)->getPcfType() << endl;

			int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (ca_compression_stack->find(int_cycle)
					!= ca_compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's
				ca_compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "there is a compression function with matching integration cycle collecting PCF's"
						<< endl;
				ev << "cycle_found" << int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase

				vector<pair<unsigned int, unsigned int> > *ppt = new vector<
						pair<unsigned int, unsigned int> >;

				ppt->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				ca_compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, ppt));

				OWCounter *ow = new OWCounter("OW_CA", TIMER_EVENT);

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_INTEGRATE:Compression Function SI_CM_INTEGRATE:Collection Phase started"
						<< endl;
				ev
						<< "SI_CM_INTEGRATE:Compression Fuction SI_CM_INTEGRATE:(vector size)"
						<< ca_compression_stack->find(int_cycle)->second->size()
						<< endl;
				ev
						<< "SI_CM_INTEGRATE:Compression Function SI_CM_INTEGRATE: int cycle"
						<< int_cycle << endl;

				delete evt;
				return;

				return;
			}

		} //handle FrameEvent

		if (string(message->getName()).compare("OW_CA") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (ca_compression_stack->find(owc->getIntegrationCycle())
					== ca_compression_stack->end()) {

				ev
						<< "DEBUG Compression Funktion SI_CM_INTEGRATE: OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size()) {
					//no new pcf IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						ev
								<< "Compression Function SI_CM_INTEGRATE round member"
								<< roundMember << endl;

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						tteScheduler->registerEvent(cpit);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						tteScheduler->registerEvent(cpit);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function SI_CM_INTEGRATE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< ca_compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						tteScheduler->registerEvent(cpit);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function SI_CM_INTEGRATE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function SI_CM_INTEGRATE: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_ENABLED::compressionFunction(cMessage *message, SICM *sicm) {

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
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
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
						<< "SI_CM_ENABLED: There is a compression Function with matching integration cycle collecting PCF's "
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

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_ENABLED: Compression Function:Collection Phase started"
						<< endl;
				delete evt;
			}

			return;

		} //handle FrameEvent

		if (string(message->getName()).compare("OW") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (compression_stack->find(owc->getIntegrationCycle())
					== compression_stack->end()) {

				ev
						<< "Compression Function:SI_CM_ENABLED: ERROR : OW: no such integration cycle: "
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
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function SI_CM_ENABLED: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_ENABLED::compressionFunctionCA(cMessage *message, SICM *sicm) {

	if (message->arrivedOn("RCin")) {

		//CM make all PCF frames permanent before usage

		PCFrame *pf = NULL;
		pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));
		//CA FRAME ?
		if (pf->getType() == CA_FRAME) {
			ev << "COMP FNCT SICM ENABLED MEMBER" << (pf)->getMembership_new()
					<< endl;
			ev << "COMP FNCT SICM ENABLED INT CYCL"
					<< (pf)->getIntegration_cycle() << endl;

			FrameEvent *f_event = new FrameEvent("CA_FRAME", TIMER_EVENT);

			f_event->setMember((pf)->getMembership_new());
			f_event->setPcfType((pf)->getType());
			f_event->setIntegrationCycle(pf->getIntegration_cycle());
			//f_event->setPit(permanence_pit);
			f_event->setTimer(permanence_delay);
			//f_event->setAction_time(permanence_pit);
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

		ev << "ERROR COMP FUNC CA" << endl;
		delete pf;
		return;

	}

	if ((message)->arrivedOn("schedulerIn")) {

		if (string((message)->getName()).compare("CA_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			ev << "COMP FNCT SICM ENABLED MEMBER(CA EVENT)"
					<< (evt)->getMember() << endl;
			ev << "COMP FNCT SICM ENABLED INT CYCL(CA EVENT)"
					<< (evt)->getPcfType() << endl;

			int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (ca_compression_stack->find(int_cycle)
					!= ca_compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's
				ca_compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "there is a compression function with matching integration cycle collecting PCF's"
						<< endl;
				ev << "cycle_found" << int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase

				vector<pair<unsigned int, unsigned int> > *ppt = new vector<
						pair<unsigned int, unsigned int> >;

				ppt->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				ca_compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, ppt));

				OWCounter *ow = new OWCounter("OW_CA", TIMER_EVENT);

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_ENABLED Compression Function SI_CM_ENABLED:Collection Phase started"
						<< endl;
				ev << "SI_CM_ENABLED Compression Fuction :(vector size)"
						<< ca_compression_stack->find(int_cycle)->second->size()
						<< endl;
				ev << "SI_CM_ENABLED Compression Function : int cycle"
						<< int_cycle << endl;

				delete evt;
				return;
			}

		} //handle FrameEvent

		if (string(message->getName()).compare("OW_CA") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (ca_compression_stack->find(owc->getIntegrationCycle())
					== ca_compression_stack->end()) {

				ev
						<< "DEBUG Compression Funktion SI_CM_ENABLED : OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size()) {
					//no new pcf IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						ev << "Compression Function round member" << roundMember
								<< endl;

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< ca_compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_UNSYNC::compressionFunction(cMessage *message, SICM *sicm) {

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
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);
			delete pf;
			return;

		} //gate RCin (PCF FRAME)

	}

	if (message->arrivedOn("schedulerIn")) {

		if (string(message->getName()).compare("IN_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			//PCFrame *pcf = in_container->find(evt->getMember())->second;

			unsigned int int_cycle = evt->getIntegrationCycle();

			uint64_t current_ppt = tteScheduler->getTicks();

			if (compression_stack->find(int_cycle)
					!= compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's
				compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "SI_CM_UNSYNC: There is a compression Function with matching integration cycle collecting PCF's "
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

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_UNSYNC: Compression Function:Collection Phase started"
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
						<< "Compression Function:WAIT_4_IN: ERROR : OW: no such integration cycle: "
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
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function SI_CM_UNSYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function SI_CM_UNSYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function SI_CM_UNSYNC: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_UNSYNC::compressionFunctionCA(cMessage *message, SICM *sicm) {

	if (message->arrivedOn("RCin")) {

		//CM make all PCF frames permanent before usage

		PCFrame *pf = NULL;
		pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//CA FRAME ?
		if (pf->getType() == CA_FRAME) {
			ev << "COMP FNCT SI_CM_UNSYNC MEMBER" << (pf)->getMembership_new()
					<< endl;
			ev << "COMP FNCT SI_CM_UNSYNC INT CYCL"
					<< (pf)->getIntegration_cycle() << endl;

			FrameEvent *f_event = new FrameEvent("CA_FRAME", TIMER_EVENT);

			f_event->setMember((pf)->getMembership_new());
			f_event->setPcfType((pf)->getType());
			f_event->setIntegrationCycle(pf->getIntegration_cycle());
			//f_event->setPit(permanence_pit);
			//f_event->setAction_time(permanence_pit);
			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);

			delete pf;
			return;

		} //gate RCin (PCF FRAME)

		ev << "ERROR COMP FUNC CA" << endl;
		delete pf;
		return;

	}

	if ((message)->arrivedOn("schedulerIn")) {

		if (string((message)->getName()).compare("CA_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			ev << "COMP FNCT SI_CM_UNSYNC MEMBER(CA EVENT)"
					<< (evt)->getMember() << endl;
			ev << "COMP FNCT SI_CM_UNSYNC INT CYCL(CA EVENT)"
					<< (evt)->getPcfType() << endl;

			int int_cycle = evt->getIntegrationCycle();
			uint64_t current_ppt = tteScheduler->getTicks();

			if (ca_compression_stack->find(int_cycle)
					!= ca_compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's
				ca_compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "there is a compression function with matching integration cycle collecting PCF's"
						<< endl;
				ev << "cycle_found" << int_cycle << endl;
				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase

				vector<pair<unsigned int, unsigned int> > *ppt = new vector<
						pair<unsigned int, unsigned int> >;

				ppt->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				ca_compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, ppt));

				OWCounter *ow = new OWCounter("OW_CA", TIMER_EVENT);

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_UNSYNC Compression Function SI_CM_UNSYNC:Collection Phase started"
						<< endl;
				ev << "SI_CM_UNSYNC Compression Fuction :(vector size)"
						<< ca_compression_stack->find(int_cycle)->second->size()
						<< endl;
				ev << "SI_CM_UNSYNC Compression Function : int cycle"
						<< int_cycle << endl;

				delete evt;

				return;
			}

		} //handle FrameEvent

		if (string(message->getName()).compare("OW_CA") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (ca_compression_stack->find(owc->getIntegrationCycle())
					== ca_compression_stack->end()) {

				ev
						<< "DEBUG Compression Funktion SI_CM_UNSYNC: OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size()) {
					//no new pcf IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						ev << "Compression Function SI_CM_UNSYNC round member"
								<< roundMember << endl;

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);

						delete owc;
						return;

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);
						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);

						delete owc;
						return;

					} else {
						ev
								<< "Compression Function SI_CM_UNSYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< ca_compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;

					} else {
						ev
								<< "Compression Function SI_CM_UNSYNC: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function SI_CM_UNSYNC: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_STABLE::compressionFunction(cMessage *message, SICM *sicm) {

	if (message->arrivedOn("RCin")) {

		PCFrame *pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		ev << "CF STABLE permanence_delay: " << permanence_delay << endl;
		ev << "CF STABLE CLOCK: " << tteScheduler->getTicks() << endl;
		ev << "CF STABLE CLOCK TOTAL: " << tteScheduler->getTotalTicks()
				<< endl;
		//IN FRAME ?
		if (pf->getType() == IN_FRAME) {

			FrameEvent *f_event = new FrameEvent("IN_FRAME", TIMER_EVENT);

			f_event->setMember(pf->getMembership_new());
			f_event->setPcfType(pf->getType());
			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
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
						<< "SI_CM_STABLE: There is a compression Function with matching integration cycle collecting PCF's "
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

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_STABLE: Compression Function:Collection Phase started "
						<< tteScheduler->getTicks() << endl;
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
						<< "Compression Function:SI_CM_STABLE: ERROR : OW: no such integration cycle: "
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
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						ev << "compression_correction "
								<< compression_correction << endl;

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						ev << "compression_correction "
								<< compression_correction << endl;

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function SI_CM_STABLE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CP",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
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
								<< "Compression Function SI_CM_STABLE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

void SI_CM_STABLE::compressionFunctionCA(cMessage *message, SICM *sicm) {

	if (message->arrivedOn("RCin")) {

		//CM make all PCF frames permanent before usage

		PCFrame *pf = NULL;
		pf = dynamic_cast<PCFrame *>(message);

		//calculate permanence pit
		int permanence_delay = max_transmision_delay
				- (transparentClockToTicks(pf->getTransparent_clock(),
						tteScheduler->par("tick").doubleValue())
						+ (tteScheduler->getTotalTicks()
								- pf->par("received_total").intValue()));

		//CA FRAME ?
		if (pf->getType() == CA_FRAME) {
			ev << "COMP FNCT CA SI_CM_STABLE MEMBER"
					<< (pf)->getMembership_new() << endl;
			ev << "COMP FNCT CA SI_CM_STABLE INT CYCL"
					<< (pf)->getIntegration_cycle() << endl;

			FrameEvent *f_event = new FrameEvent("CA_FRAME", TIMER_EVENT);

			f_event->setMember((pf)->getMembership_new());
			f_event->setPcfType((pf)->getType());
			f_event->setIntegrationCycle(pf->getIntegration_cycle());

			f_event->setTimer(permanence_delay);
			f_event->setDestinationGate(sicm->gate("schedulerIn"));
			f_event->setSchedulingPriority(2);

			tteScheduler->registerEvent(f_event);
			delete pf;
			return;

		} //gate RCin (PCF FRAME)

		ev << "ERROR COMP FUNC CA" << endl;
		delete pf;
		return;

	}

	if ((message)->arrivedOn("schedulerIn")) {

		if (string((message)->getName()).compare("CA_FRAME") == 0) {

			FrameEvent *evt = dynamic_cast<FrameEvent *>(message);

			ev << "COMP FNCT SI_CM_STABLE MEMBER(CA EVENT)"
					<< (evt)->getMember() << endl;
			ev << "COMP FNCT SI_CM_STABLE INT CYCL(CA EVENT)"
					<< (evt)->getPcfType() << endl;

			int int_cycle = evt->getIntegrationCycle();
			uint64_t current_ppt = tteScheduler->getTicks();
			if (ca_compression_stack->find(int_cycle)
					!= ca_compression_stack->end()) {

				//there is a compression function with matching integration cycle collecting PCF's
				ca_compression_stack->find(int_cycle)->second->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));
				ev
						<< "there is a compression function with matching integration cycle collecting PCF's"
						<< endl;
				ev << "cycle_found" << int_cycle << endl;

				delete evt;
				return;
			} else {
				//no compression function with matching integration cycle collecting PCF's
				//start collecting phase

				vector<pair<unsigned int, unsigned int> > *ppt = new vector<
						pair<unsigned int, unsigned int> >;

				ppt->push_back(
						pair<unsigned int, unsigned int>(evt->getMember(),
								current_ppt));

				ca_compression_stack->insert(
						pair<unsigned int,
								vector<pair<unsigned int, unsigned int> > *>(
								int_cycle, ppt));

				OWCounter *ow = new OWCounter("OW_CA", TIMER_EVENT);

				ow->setDestinationGate(sicm->gate("schedulerIn"));
				ow->setSchedulingPriority(3);
				ow->setTimer(sicm->par("observation_window_size"));

				ow->setNumberOfObservationWindow(1);
				ow->setLastNumberOfFrames(1);
				ow->setIntegrationCycle(int_cycle);

				tteScheduler->registerEvent(ow);

				ev
						<< "SI_CM_STABLE Compression Function:Collection Phase started"
						<< endl;
				ev << "SI_CM_STABLE Compression Fuction :(vector size)"
						<< ca_compression_stack->find(int_cycle)->second->size()
						<< endl;
				ev << "SI_CM_STABLE Compression Function : int cycle"
						<< int_cycle << endl;

				delete evt;
				return;
			}

		} //handle FrameEvent

		if (string(message->getName()).compare("OW_CA") == 0) {

			OWCounter *owc = dynamic_cast<OWCounter *>(message);

			if (ca_compression_stack->find(owc->getIntegrationCycle())
					== ca_compression_stack->end()) {

				ev
						<< "DEBUG Compression Funktion SI_CM_STABLE: OW: no such integration cycle: "
						<< owc->getIntegrationCycle() << endl;

			} else {
				//compression function is active
				//check for frames received during the last observation window
				if (owc->getLastNumberOfFrames()
						== ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size()) {
					//no new pcf IN frames became permanent during the last observation window
					// stop collecting
					//check reaching max_observation_window
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int restOW =
								(sicm->par("max_observation_window").intValue()
										- owc->getNumberOfObservationWindow())
										* sicm->par("observation_window_size").intValue();

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = restOW
								+ sicm->par("calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						ev << "Compression Function SI_CM_STABLE round member"
								<< roundMember << endl;

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {

						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function SI_CM_STABLE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;
					}

				} else if (owc->getLastNumberOfFrames()
						< ca_compression_stack->find(owc->getIntegrationCycle())->second->size()) {
					//pcf became permanent during the last observation window, check max ow reached
					if (owc->getNumberOfObservationWindow()
							< (unsigned int)sicm->par("max_observation_window")) {
						//open another ow
						int new_ow = (owc->getNumberOfObservationWindow()) + 1;
						int new_number_frames = ca_compression_stack->find(
								owc->getIntegrationCycle())->second->size();

						owc->setNumberOfObservationWindow(new_ow);
						owc->setLastNumberOfFrames(new_number_frames);

						tteScheduler->registerEvent(owc);

					} else if (owc->getNumberOfObservationWindow()
							== (unsigned int)sicm->par("max_observation_window")) {
						//max_ow_reached
						//stop collecting
						//calculate the compression_funktion_delay and register the event for compressed pit

						int compression_correction =
								compress(
										ca_compression_stack->find(
												owc->getIntegrationCycle())->second,
										sicm->par(
												"faulty_synchronisatzation_masters"));

						int compression_funktion_delay = sicm->par(
								"calculation_overhead")
								+ compression_correction;

						unsigned int roundMember = setBits(
								ca_compression_stack->find(
										owc->getIntegrationCycle())->second);

						CompressedPIT *cpit = new CompressedPIT("CPCA",
								TIMER_EVENT);
						cpit->setDestinationGate(sicm->gate("schedulerIn"));
						cpit->setTimer(compression_funktion_delay);
						cpit->setSchedulingPriority(3);
						cpit->setMembership_new(roundMember);

						delete ca_compression_stack->find(
								owc->getIntegrationCycle())->second;
						ca_compression_stack->erase(owc->getIntegrationCycle());

						tteScheduler->registerEvent(cpit);
						delete owc;
						return;
					} else {
						ev
								<< "Compression Function SI_CM_STABLE: Error END OBSERVATION WINDOW:"
								<< owc->getNumberOfObservationWindow() << endl;
						ev << "MAX Observation Window: "
								<< sicm->par("max_observation_window").intValue()
								<< endl;

					}
					//pcf became permanent during the last observation window, check max ow reached
				} else {
					ev
							<< "Compression Function SI_CM_STABLE: Error owc->getLastNumberOfFrames() > compression_stack->find(owc->getIntegrationCycle())->second->size()"
							<< owc->getNumberOfObservationWindow() << endl;
				}

			} //compression Function witch matching integration cycle found

		} //OW

	} //schedulerIn

}

} //namespace

