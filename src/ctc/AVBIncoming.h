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

/**
 * @brief Class for the critical traffic conformance check of
 * audio-video bridging traffic.
 */
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
             * @brief Initialization of the module.
             */
            virtual void initialize();

            /**
             * @brief Forwards messages arriving on in-gate to out-gate.
             *
             * @param msg the incoming message.
             */
            virtual void handleMessage(cMessage *msg);

            /**
             * @brief initializes the port bandwith and gets the TT bandwith.
             *
             * @param port number.
             *
             * @return returns the TT bandwith on the port in Mbit/s.
             */
            int calcPortUtilisation(int port);


    public:
            /**
             * @brief Constructor.
             */
            AVBIncoming();
            bool talker;

            /**
             * @brief calculates the bandwith.
             *
             * @param Size of the frame.
             * @param Sending interval of the frame.
             *
             * @return returns bandwith in Mbit/s.
             */
            int calcBandwith(int FrameSize, int IntervalFrames);

            /**
             * @brief get AVB port reservation.
             *
             * @param port number.
             *
             * @return returns the AVB bandwith on one port in Mbit/s.
             */
            int getAVBPortReservation(int port);

            /**
             * @brief set the AVB port reservation.
             *
             * @param port number.
             * @param reservation bandwith in Mbit/s.
             */
            void setAVBPortReservation(int port, int reservation);

            /**
             * @brief get port bandwith.
             *
             * @return returns the bandwith of the physical port in Mbit/s.
             */
            int getPortBandwith(int port);

            /**
             * @brief get forwarding policy.
             *
             * @return returns true if AVB forwarding is active.
             */
            bool getForwarding();
};

} /* namespace TTEthernetModel */
#endif /* AVBINCOMING_H_ */
