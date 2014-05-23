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
 * SCSCStates.h
 *
 *  Created on: Feb 27, 2012
 *      Author: Lazar Todorov
 */

#ifndef SCSCStateS_H_
#define SCSCStateS_H_

#include "CoRE4INET_SCState.h"

#include "PCFrame_m.h"
#include "CoRE4INET_TTEScheduler.h"
#include <SchedulerMessage_m.h>
#include <SchedulerMessageEvents_m.h>

namespace CoRE4INET {

class SC;

class SC_INTEGRATE:public SCState{

public:
	SC_INTEGRATE();
	//virtual ~SC_INTEGRATE();
	//void reaction(int message);
	void handleMessage(cMessage *message);


};

class SC_INIT:public SCState{

public:
    SC_INIT(SC *sc, FILE *f);
    //virtual ~SC_INIT();
    //void reaction(int message);
    void handleMessage(cMessage *message);


};



class SC_PSEUDOSYNC:public SCState{

public:
        SC_PSEUDOSYNC();
    //void reaction(int message);
    void handleMessage(cMessage *message);
};

class SC_STABLE:public SCState{

public:
	SC_STABLE();
	//void reaction(int message);
	void handleMessage(cMessage *message);
};

class SC_SYNC:public SCState{

public:
	SC_SYNC();
	//void reaction(int message);
	void handleMessage(cMessage *message);

};

}

#endif /* SCSCStateS_H_ */
