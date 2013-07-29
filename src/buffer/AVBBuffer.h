//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef AVBBUFFER_H_
#define AVBBUFFER_H_

#include <omnetpp.h>
#include "Buffer.h"
#include "TTEScheduler.h"
#include "AVBIncoming.h"

namespace TTEthernetModel {

class AVBBuffer : public virtual Buffer
{
    public:
        AVBBuffer();
        virtual ~AVBBuffer();

        void idleSlope(SimTime duration);
        void interferenceSlope(SimTime duration);
        void sendSlope(SimTime duration);
        void refresh();
        int getCredit();
        void resetCredit();
        int getMsgCount();
    protected:
        int credit;
        int maxCredit;
        int AVBReservation;
        bool inTransmission;
        bool inTerference;
        int msgCnt;
        SimTime newTime;
        SimTime oldTime;
        double Wduration;

        TTEScheduler *tteScheduler;
        AVBIncoming * avbCTC;

        virtual void initialize(int stage);
        virtual int numInitStages() const;
        virtual void handleMessage(cMessage *msg);
        virtual void handleParameterChange(const char* parname);
};

} /* namespace TTEthernetModel */
#endif /* AVBBUFFER_H_ */
