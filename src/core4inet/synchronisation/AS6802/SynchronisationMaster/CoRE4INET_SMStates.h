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
 * SMStates.h
 *
 *  Created on: Feb 13, 2012
 *      Author: Lazar Todorov
 */

#ifndef SMSTATES_H_
#define SMSTATES_H_

#include "CoRE4INET_SMState.h"

#include "PCFrame_m.h"
#include "CoRE4INET_TTEScheduler.h"
#include <SchedulerMessage_m.h>
#include <SchedulerMessageEvents_m.h>
#include <SchedulerEvent.h>
class SM;

namespace CoRE4INET {



class SM_INIT:public SMState{

    public:

    SM_INIT(SM *sm, FILE *fp);
    //virtual ~SM_INIT();
	void reaction(int message);

};



class SM_PSEUDOSYNC:public SMState{

public:

    SM_PSEUDOSYNC();
    //void reaction(int message);
    void handleMessage(cMessage *message);
};


class SM_INTEGRATE:public SMState{

public:

	SM_INTEGRATE();
	//void reaction(int message);
	void handleMessage(cMessage *message);
};

class SM_STABLE:public SMState{

public:

	SM_STABLE();
	//virtual ~SM_STABLE();
	//void reaction(int message);
	void handleMessage(cMessage *message);


};

class SM_UNSYNC:public SMState{

public:
	SM_UNSYNC();
	//void reaction(int message);
	void handleMessage(cMessage *message);

};


class SM_SYNC:public SMState{

public:
	SM_SYNC();
	//void reaction(int message);
	void handleMessage(cMessage *message);
};

class SM_FLOOD:public SMState{



	public:


	SM_FLOOD();
	//void reaction(int message);
	void handleMessage(cMessage *message);
};

class SM_WAIT_4_CYCLE_START_CS:public SMState{

public:

	SM_WAIT_4_CYCLE_START_CS();
	//void reaction(int message);
	void handleMessage(cMessage *message);
};

class SM_TENTATIVE_SYNC:public SMState{

	public:
	SM_TENTATIVE_SYNC();
	//void reaction(int message);
	void handleMessage(cMessage *message);

};

class SM_WAIT_4_CYCLE_START:public SMState{

public:

	SM_WAIT_4_CYCLE_START();
	//void reaction(int message);
	void handleMessage(cMessage *message);


};

}

#endif /* SMSTATES_H_ */
