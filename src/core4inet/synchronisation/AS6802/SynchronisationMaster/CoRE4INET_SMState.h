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
 * State.h
 *
 *  Created on: Feb 13, 2012
 *      Author: Lazar Todorov
 */

#ifndef SMSTATE_H_
#define SMSTATE_H_

#include <iostream>

#include <stdio.h>
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"
#include "core4inet/scheduler/SchedulerEvent.h"
#include "core4inet/scheduler/SchedulerMessageEvents_m.h"
#include "core4inet/synchronisation/AS6802/SynchronisationEvents_m.h"
//#include "core4inet/TTEScheduler.h"
#include <map>
#include <list>
#include <stdint.h>

using namespace std;

namespace CoRE4INET {

class SM;

class SMState {

public:

	cOutVector *outVector;

	SM *sm;
	FILE *fp;
	vector<int> *values;

	vector<int> *knownCMs;
	const char *CMs;
	cStringTokenizer *tokenizer;
	string temp;

	int counter;
	int dummy;
	int data;

	bool local_timer;
	bool flood_receive;
	bool closed_window;
	bool round_completed;

	int32_t ctid;

	uint64_t local_clock;

	uint32_t local_sync_membership;
	uint32_t local_async_membership;

	//The monitoring intervals are longer than the integration_cycle_duration,
	//requiring two variables  local_async_membership_f,  local_async_membership_r
	uint32_t local_async_membership_f;
	uint32_t local_async_membership_r;

	uint64_t local_integration_cycle;
	int32_t clock_corr;
	uint64_t stable_cycle_counter;
	uint64_t duration;
	uint32_t ownBit;
	uint64_t max_transmission_delay;
	uint32_t syncDomain;
	uint32_t syncPriority;

	TTEScheduler *tteScheduler;
	SchedulerTimerEvent *event;
	SchedulerActionTimeEvent *event1;
	SchedulerActionTimeEvent *event2;
	SchedulerActionTimeEvent *event3;
	SchedulerActionTimeEvent *event4;
	SchedulerActionTimeEvent *event5;

	uint32_t MembershipAcceptanceRange;

	std::map<uint32_t, pair<uint32_t, uint64_t> > *clock_stack;

	multimap<uint64_t, FrameEvent *> *e_container;

	virtual ~SMState(){


	}

	virtual void handleMessage(cMessage *message) {
	}

	uint32_t getValue(uint32_t bitVector, uint32_t length) {

		uint32_t count = 0;

		for (uint32_t ibit = 0; ibit < length; ibit++) {
			//if (v & 1) c++;
			count += bitVector & 1;
			bitVector >>= 1;
		}

		return count;
	}

	bool inSchedule(uint64_t permanence_pit, uint64_t sc_receive_pit,
			uint64_t acceptance_window) {

		if ((permanence_pit >= (sc_receive_pit - (acceptance_window / 2)))
				&& (permanence_pit <= (sc_receive_pit + (acceptance_window / 2)))) {

			return true;

		} else {

			return false;

		}

	}
};

}

#endif /* SMSTATE_H_ */
