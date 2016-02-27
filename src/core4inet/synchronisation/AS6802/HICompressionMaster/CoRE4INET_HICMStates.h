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
 *
 *
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */

#ifndef HICMSTATES_H_
#define HICMSTATES_H_

#include "CoRE4INET_HICMState.h"

#include "PCFrame_m.h"
#include "CoRE4INET_TTEScheduler.h"
#include "SchedulerMessage_m.h"
#include "SchedulerMessageEvents_m.h"
#include "CoRE4INET_SchedulerEvent.h"

class HICM;

namespace CoRE4INET {

class HI_CM_INIT : public HICMState
{
    public:
        HI_CM_INIT(HICM *hicm, FILE *f);
        //virtual ~HI_CM_INIT();

};

class HI_CM_PSEUDOSYNC : public HICMState
{
    public:
        HI_CM_PSEUDOSYNC();
        //virtual ~HI_CM_PSEUDOSYNC();
        void handleMessage(cMessage *message);

};

class HI_CM_INTEGRATE : public HICMState
{
    public:
        HI_CM_INTEGRATE();
        //virtual ~HI_CM_INTEGRATE();
        void compressionFunction(cMessage* message, HICM *hicm);
        void handleMessage(cMessage *message);

};

class HI_CM_STABLE : public HICMState
{
    public:
        HI_CM_STABLE();
        //virtual ~HI_CM_STABLE();
        void compressionFunction(cMessage* message, HICM *hicm);
        void handleMessage(cMessage *message);


};

class HI_CM_UNSYNC : public HICMState
{
    public:
        HI_CM_UNSYNC();
        //virtual ~HI_CM_UNSYNC();
        void compressionFunction(cMessage* message, HICM *hicm);
        void handleMessage(cMessage *message);


};

class HI_CM_SYNC : public HICMState
{
    public:
        HI_CM_SYNC();
        //virtual ~HI_CM_SYNC();
        void compressionFunction(cMessage* message, HICM *hicm);
        void handleMessage(cMessage *message);

};

class HI_CM_TENTATIVE_SYNC : public HICMState
{
    public:
        HI_CM_TENTATIVE_SYNC();
        //virtual ~HI_CM_TENTATIVE_SYNC();
        void compressionFunction(cMessage* message, HICM *hicm);
        void handleMessage(cMessage *message);

};

class HI_CM_WAIT_4_CYCLE_START : public HICMState
{
    public:
        HI_CM_WAIT_4_CYCLE_START();
        //virtual ~HI_CM_WAIT_4_CYCLE_START();
        void compressionFunction(cMessage* message, HICM *hicm);
        void handleMessage(cMessage *message);

};

}

#endif /* HICMSTATES_H_ */
