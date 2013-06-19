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
