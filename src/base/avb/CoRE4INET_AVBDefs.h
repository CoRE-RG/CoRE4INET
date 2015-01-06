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

#ifndef __CORE4INET_AVBDEFS_H_
#define __CORE4INET_AVBDEFS_H_

#include "simtime.h"

namespace CoRE4INET {

//Ethertype for MSRP Protocol
#define MSRP_ETHERTYPE 0x22EA

//Destination Multicast MAC for SRP Protocol (01:80:C2:00:00:0E)
const MACAddress SRP_ADDRESS = MACAddress("01:80:C2:00:00:0E");

//Service class A interval is 125us
const_simtime_t SR_CLASS_A_INTERVAL = 0.000125;
//Service class B interval is 250us
const_simtime_t SR_CLASS_B_INTERVAL = 0.000250;

const unsigned short VLAN_ID_DEFAULT = 2;

const unsigned char PRIOANDRANK_SRCLASSA = 0xD0; //0b11010000; //For more details see SRPFrame.msg
const unsigned char PRIOANDRANK_SRCLASSB = 0xB0; //0b10110000;

/**
 * Defines for range checks
 */
#define MAX_STREAM_ID UINT64_MAX
#define MAX_INTERVAL_FRAMES UINT32_MAX

}
#endif /* AVBDEFS_H_ */
