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
 *  Created on: Feb 27, 2012
 *      Author: Lazar Todorov
 */

#ifndef SCSTATE_H_
#define SCSTATE_H_
#include <iostream>
#include <stdio.h>
//#include "omnetpp.h"
#include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"
#include "core4inet/scheduler/SchedulerEvent.h"
#include "core4inet/scheduler/SchedulerMessageEvents_m.h"
#include "core4inet/synchronisation/AS6802/SynchronisationEvents_m.h"
#include "core4inet/TTEScheduler.h"
#include <map>



using namespace std;

namespace CoRE4INET {

class SC;






class SCState{

	public:

    cOutVector *outVector;

    SC *sc;

    const char * CMs;

    FILE *fp;
    vector<int> *values;
    int counter;
    int dummy;
    int data;

    bool local_timer;
	bool flood_receive;
	bool closed_window;
	bool round_completed;

	bool powerUp;
	bool first_sync_cycle;
	bool timeOutExpierd;

	uint32_t MembershipAcceptanceRange;
	uint32_t syncDomainId;
	uint32_t local_current_sync_priority;

	uint32_t local_clock;
	uint32_t local_sync_membership;

	uint32_t local_async_membership;
	uint32_t local_async_membership_f;
	uint32_t local_async_membership_r;

	uint64_t local_integration_cycle;

	int32_t clock_corr;
	uint64_t stable_cycle_counter;
	uint64_t duration;
	uint64_t max_transmission_delay;

	TTEScheduler *tteScheduler;
	SchedulerTimerEvent *event;
	SchedulerActionTimeEvent *event1;
	SchedulerActionTimeEvent *event2;
	SchedulerActionTimeEvent *event3;
	SchedulerActionTimeEvent *event4;
	SchedulerActionTimeEvent *event5;
	//template< const std::pair< unsigned int , PCFrame* > >

	//clock readings stack
	//multimap<uint32_t,uint64_t> *container;
	std::map<uint32_t, pair<uint32_t,uint64_t> > *clock_stack;
	//multimap<unsigned int, PCFrame *> *f_container;
	//multimap<unsigned int, PCFrame *>  *sync_container;



	//multimap<unsigned int,PCFrame*, const Compare& = Comp() > *f_container;
	//multimap<unsigned int, PCFrame *> *f_container;

	multimap<uint64_t, FrameEvent *> *e_container;

	virtual ~SCState(){

	}

	virtual void reaction(int message){

			cout<<"default reaction \n"<<endl;


	}

	virtual void handleMessage(cMessage *message){}
	    /*dummy*/
	    void TW(int duration){}


	  int getValue( uint32_t bitVector,  uint32_t length){

	         uint32_t count = 0;

	        for (uint32_t ibit = 0; ibit < length; ibit++) {
	          //if (v & 1) c++;
	          count += bitVector & 1;
	          bitVector >>= 1;
	        }

	        return count;
	    }


	bool inSchedule(uint64_t permanence_pit, uint64_t sc_receive_pit, uint64_t precission){

	    if((permanence_pit >= (sc_receive_pit - precission))&&(permanence_pit <= (sc_receive_pit + precission))){

	        return true;

	    }else{


	     return false;

	    }
	}




};



}






#endif /* SCSTATE_H_ */
