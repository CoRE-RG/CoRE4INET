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

#ifndef TTEAVBOUTPUT_H_
#define TTEAVBOUTPUT_H_

#include "TTEOutput.h"
#include "AVBIncoming.h"
#include "AVBBuffer.h"

namespace TTEthernetModel {

class TTEAVBOutput : public TTEOutput
{
    protected:
        int portIndex;

        cQueue avbQueue;
        AVBBuffer *avbBuffer;

        SimTime newTime;
        SimTime oldTime;
        SimTime durationDebug;

        static simsignal_t avbQueueLengthSignal;

        virtual void initialize();

        virtual void handleMessage(cMessage *msg);
        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
         */
        virtual void requestPacket();
    public:
        /**
         * @brief Constructor
         */
        TTEAVBOutput();
        /**
         * @brief Destructor
         */
        ~TTEAVBOutput();
};

} /* namespace TTEthernetModel */
#endif /* TTEAVBOUTPUT_H_ */
