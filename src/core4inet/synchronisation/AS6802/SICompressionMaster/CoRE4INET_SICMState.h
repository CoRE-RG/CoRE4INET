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
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */

#ifndef SICMSTATE_H_
#define SICMSTATE_H_

#include <iostream>

#include <stdio.h>
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"
#include "core4inet/scheduler/SchedulerEvent.h"
#include "core4inet/scheduler/SchedulerMessageEvents_m.h"
#include "core4inet/synchronisation/AS6802/SynchronisationEvents_m.h"
#include "core4inet/TTEScheduler.h"
#include <map>
#include <list>
#include <deque>
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"

using namespace std;

namespace CoRE4INET {

class SICM;

class SICMState {

public:
	cOutVector *outVector;

	SICM *sicm;
	FILE *fp;
	vector<int> *values;
	int counter;
	int dummy;
	int data;

	bool local_timer;
	bool flood_receive;
	bool closed_window;
	bool round_completed;

	int local_clock;
	int local_sync_membership;
	int local_async_membership;
	int local_integration_cycle;

	int clock_corr;

	int stable_cycle_counter;
	int duration;
	unsigned int max_transmision_delay;
	unsigned int local_async_membership_r;
	unsigned int local_async_membership_f;
	unsigned int ctid;

	//cm_sync_eval_pit
	SchedulerActionTimeEvent *event2;
	//cm_clock_corr_pit
	SchedulerActionTimeEvent *event3;
	//cm_inc_pit
	SchedulerActionTimeEvent *event4;
	//cm_scheduled_pit
	SchedulerActionTimeEvent *event5;

	TTEScheduler* tteScheduler;

	SchedulerTimerEvent *event;

	//compression function and clock synchronization service

	multimap<unsigned int, PCFrame *> *caCompressedFrames;
	deque<pair<unsigned int, PCFrame *> > *compressed_frames;

	//container for PCF that became permanent during the collection phase of the compression function
	//key -> integration_cycle, value=vector<membership_new, permenence_pit>
	map<unsigned int, vector<pair<unsigned int, unsigned int> > *> *compression_stack;
	map<unsigned int, vector<pair<unsigned int, unsigned int> > *>::iterator compression_stack_it;

	map<unsigned int, vector<pair<unsigned int, unsigned int> > *> *ca_compression_stack;
	map<unsigned int, vector<pair<unsigned int, unsigned int> > *>::iterator ca_compression_stack_it;

	deque<CompressedPIT *> *delay_container;
	deque<DispatchDelay *> *dispatch_delay_container;
	deque<pair<unsigned int, unsigned int> > *clock_stack;

	virtual void handleMessage(cMessage *message) {
	}
	virtual void compressionFunction(cMessage *message, SICM *sicm) {
	}
	virtual void compressionFunctionCA(cMessage *message, SICM *sicm) {
	}

	int getValue(unsigned int bitVector, int length) {

		int count = 0;

		for (int ibit = 0; ibit < length; ibit++) {
			//if (v & 1) c++;
			count += bitVector & 1;
			bitVector >>= 1;
		}

		return count;
	}

	int getBitPosition(unsigned int bitVector) {

		for (int count = 1; count <= 32; count++) {

			if ((bitVector & 1) == 1) {
				break;
				return count;
			} //if

			bitVector >>= 1;

		} //for
		return -1;
	} //method

	bool inSchedule(unsigned int permanence_pit, unsigned int sc_receive_pit,
			unsigned int precission) {

		if ((permanence_pit >= (sc_receive_pit - precission))
				&& (permanence_pit <= (sc_receive_pit + precission))) {

			return true;

		} else {

			return false;

		}
	}

	bool inSchedule2(unsigned int permanence_pit, unsigned int sc_receive_pit,
			unsigned int acceptance_window) {

		if ((permanence_pit >= (sc_receive_pit - (acceptance_window / 2)))
				&& (permanence_pit <= (sc_receive_pit + (acceptance_window / 2)))) {

			return true;

		} else {

			return false;

		}

	}

	int compress(vector<pair<unsigned int, unsigned int> > *vct
			, int faulty_sms) {

		vector<pair<unsigned int, unsigned int> >::iterator it_b;
		vector<pair<unsigned int, unsigned int> >::reverse_iterator it_e;

		int compression_correction = 0;
		int k = faulty_sms + 1;
		int numberOfInputs = vct->size();

		switch (numberOfInputs) {

		case 1:
			compression_correction = 0;
			break;
		case 2:
			compression_correction = (vct->at(1).second - vct->at(0).second)
					/ 2;
			break;
		case 3:
			compression_correction = (vct->at(1).second - vct->at(0).second);
			break;
		case 4:
			compression_correction = ((vct->at(1).second - vct->at(0).second)
					+ (vct->at(2).second - vct->at(0).second)) / 2;
			break;
		case 5:
			compression_correction = ((vct->at(1).second - vct->at(0).second)
					+ (vct->at(3).second - vct->at(0).second)) / 2;
			break;

		default:
			it_b = vct->begin() + (k - 1);
			it_e = vct->rbegin() + k;
			compression_correction = (it_e->second - it_b->second) / 2;
			break;

		}

		return compression_correction;

	}
	unsigned int setBits(vector<pair<unsigned int, unsigned int> > *vct) {

		vector<pair<unsigned int, unsigned int> >::iterator it;

		unsigned int bits = 0;

		for (it = vct->begin(); it != vct->end(); it++) {

			bits |= it->first;

		}

		return bits;
	}

};

}
#endif /* SICMSTATE_H_ */
