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

#ifndef CORE4INET_DEFS_H
#define CORE4INET_DEFS_H

//OMNeT++
#include "omnetpp.h"

//INET
#include "inet/common/INETDefs.h"

#include "core4inet/base/Dependencies.h"

/**
 * Definition of CORE4INET version
 */
#define CORE4INET_VERSION 0x0100

/**
 * Delimiters for vectors
 */
#define DELIMITERS ",; \t\n\r\f"


/**
 * Ethernet 802.1Q Header
 */
#define ETHER_8021Q_TAG_BYTES 4
#define MAX_ETHER_8021Q_FRAME_BYTES (MAX_ETHERNET_FRAME_BYTES + ETHER_8021Q_TAG_BYTES)
#define MAX_VLAN_NUMBER 4095
#define MAX_Q_PRIORITY 7

/**
 * Defines for range checks
 */
#define MAX_VLAN_ID 4094
#define MAX_TICK_LENGTH DBL_MAX
#define MAX_CYCLE_TICKS UINT32_MAX

/**
 * Scheduling Priorities
 */
#define SCHEDULING_PRIORITY_OFFSET_TT 0
#define SCHEDULING_PRIORITY_OFFSET_PCF 1
#define SCHEDULING_PRIORITY_OFFSET_RC 10
#define SCHEDULING_PRIORITY_OFFSET_AVBA 11
#define SCHEDULING_PRIORITY_OFFSET_AVBB 12
#define SCHEDULING_PRIORITY_OFFSET_8021Q 20

#endif
