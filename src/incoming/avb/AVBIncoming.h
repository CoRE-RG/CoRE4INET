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

#ifndef __CORE4INET_AVBINCOMING_H_
#define __CORE4INET_AVBINCOMING_H_

#include <omnetpp.h>
#include <map>
#include "MACAddress.h"

namespace CoRE4INET {

//This disables the padding warning for this class! please recheck when adding new members!
#pragma GCC diagnostic ignored "-Wpadded"

/**
 * @brief Class for the critical traffic conformance check of
 * audio-video bridging traffic.
 *
 * @author Philipp Meyer
 */
class AVBIncoming : public cSimpleModule
{
    protected:
            /**
             * @brief set to true if there was an error during runtime
             */
            bool hadError;

            std::map<unsigned long, MACAddress> TalkerAddresses;
            std::map<unsigned long, unsigned int> StreamBandwith;
            std::map<unsigned long, bool>StreamIsForwarding;
            std::map<unsigned int, std::list<unsigned long> > ListenerGates;
            std::map<unsigned int, unsigned int> PortReservation;
            std::map<unsigned int, unsigned int> AVBPortReservation;
            std::map<unsigned int, unsigned int> PortBandwith;

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
            unsigned int calcPortUtilisation(unsigned int port);


    public:
            /**
             * @brief Constructor.
             */
            AVBIncoming();
            bool talker;

            /**
             * @brief calculates the bandwith.
             *
             * @param FrameSize Size of the frame.
             * @param IntervalFrames Sending interval of the frame.
             *
             * @return returns bandwith in Mbit/s.
             */
            unsigned int calcBandwith(unsigned int FrameSize, unsigned int IntervalFrames);

            /**
             * @brief get AVB port reservation.
             *
             * @param port index of port.
             *
             * @return returns the AVB bandwith on one port in Mbit/s.
             */
            unsigned int getAVBPortReservation(unsigned int port);

            /**
             * @brief set the AVB port reservation.
             *
             * @param port number.
             * @param reservation bandwith in Mbit/s.
             */
            void setAVBPortReservation(unsigned int port, unsigned int reservation);

            /**
             * @brief get port bandwith.
             *
             * @return returns the bandwith of the physical port in Mbit/s.
             */
            unsigned int getPortBandwith(unsigned int port);

            /**
             * @brief get forwarding policy.
             *
             * @return returns true if AVB forwarding is active.
             */
            bool getForwarding();
};

} /* namespace CoRE4INET */
#endif /* __CORE4INET_AVBINCOMING_H_ */
