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

#ifndef AVBINCOMING_H_
#define AVBINCOMING_H_

#include <omnetpp.h>
#include <map>
#include "MACAddress.h"

using namespace std;

namespace TTEthernetModel {

class AVBIncoming : public cSimpleModule
{
    protected:
            /**
             * @brief set to true if there was an error during runtime
             */
            bool hadError;

            map<unsigned long, MACAddress> TalkerAddresses;
            map<unsigned long, int> StreamBandwith;
            map<unsigned long, bool>StreamIsForwarding;
            map<int, list<unsigned long> > ListenerGates;
            map<int, int> PortReservation;
            map<int, int> AVBPortReservation;
            map<int, int> PortBandwith;

            /**
             * @brief Initialization of the module
             */
            virtual void initialize();
            /**
             * @brief Forwards messages arriving on in-gate to out-gate
             *
             * @param msg the incoming message
             */
            virtual void handleMessage(cMessage *msg);

            int calcPortUtilisation(int port);


    public:
            /**
             * @brief Constructor.
             */
            AVBIncoming();
            bool talker;
            int calcBandwith(int FrameSize, int IntervalFrames);
            int getAVBPortReservation(int port);
            void setAVBPortReservation(int port, int reservation);
            int getPortBandwith(int port);
};

} /* namespace TTEthernetModel */
#endif /* AVBINCOMING_H_ */
