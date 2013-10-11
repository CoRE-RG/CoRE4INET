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

#ifndef __TTE4INET_TTE4INETDEFS_H
#define __TTE4INET_TTE4INETDEFS_H

#include <omnetpp.h>

/**
 * Check for minimal OMNeT++ Version requirements
 */
#if OMNETPP_VERSION < 0x0402
#  error At least OMNeT++/OMNEST version 4.2 required
#endif

/**
 * Definition of TTEthernetModel version
 */
#define TTE4INET_VERSION 0x0200

/**
 * Maximum number of priorities allowed for rate-constrained messages
 */
#define NUM_RC_PRIORITIES 10

/**
 * Delimiters for vectors
 */
#define DELIMITERS ",; \t\n\r\f"

#endif
