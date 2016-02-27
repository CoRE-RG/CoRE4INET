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
 * SICMStates.h
 *
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */

#ifndef SICMSTATES_H_
#define SICMSTATES_H_

#include "CoRE4INET_SICMState.h"

#include "PCFrame_m.h"
#include "CoRE4INET_TTEScheduler.h"
#include <SchedulerMessage_m.h>
#include <SchedulerMessageEvents_m.h>
#include <SchedulerEvent.h>
class SICM;




namespace CoRE4INET{

class SI_CM_INIT:public SICMState{

    public:
        //virtual ~SI_CM_INIT();
        SI_CM_INIT(SICM *sicm, FILE *f);
        virtual ~SI_CM_INIT();
};

class SI_CM_PSEUDOSYNC:public SICMState{

public:
    //virtual ~SI_CM_INTEGRATE();
        SI_CM_PSEUDOSYNC();

    void handleMessage(cMessage *message);

};

class SI_CM_INTEGRATE:public SICMState{

public:
    //virtual ~SI_CM_INTEGRATE();
	SI_CM_INTEGRATE();

	void handleMessage(cMessage *message);
	void compressionFunction(cMessage *message, SICM *sicm);
	void compressionFunctionCA(cMessage *message, SICM *sicm);
};

class SI_CM_STABLE:public SICMState{

public:
       //virtual ~SI_CM_STABLE();
	SI_CM_STABLE();

	void handleMessage(cMessage *message);
	void compressionFunction(cMessage *message, SICM *sicm);
	void compressionFunctionCA(cMessage *message, SICM *sicm);

};

class SI_CM_UNSYNC:public SICMState{

public:
        //virtual ~SI_CM_UNSYNC();
        SI_CM_UNSYNC();

	void handleMessage(cMessage *message);
	void compressionFunction(cMessage *message, SICM *sicm);
	 void compressionFunctionCA(cMessage *message, SICM *sicm);
};


class SI_CM_SYNC:public SICMState{

public:
        //virtual ~SI_CM_SYNC();
        SI_CM_SYNC();

	void handleMessage(cMessage *message);
	void compressionFunction(cMessage *message, SICM *sicm);
	void compressionFunctionCA(cMessage *message, SICM *sicm);
};



class SI_CM_ENABLED:public SICMState{

	public:
       //virtual ~SI_CM_ENABLED();
        SI_CM_ENABLED();

	void handleMessage(cMessage *message);
	void compressionFunction(cMessage *message, SICM *sicm);
	void compressionFunctionCA(cMessage *message, SICM *sicm);

};

class SI_CM_WAIT_4_IN:public SICMState{

public:
        //virtual ~SI_CM_WAIT_4_IN();
	SI_CM_WAIT_4_IN();

	void handleMessage(cMessage *message);
	void compressionFunction(cMessage *message, SICM *sicm);
	void compressionFunctionCA(cMessage *message, SICM *sicm);

};




}





#endif /* SICMSTATES_H_ */
