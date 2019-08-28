#include "../features.h"

#include "inet/features.h"

/**
 * Check for minimal OMNeT++ Version requirements
 */
#if OMNETPP_VERSION < 0x0504 || OMNETPP_BUILDNUM < 1020
#  error At least OMNeT++/OMNEST version 5.4.1 required
#endif

/**
 * Check for minimal INET Version requirements
 */
#if INET_VERSION < 0x0306 || (INET_VERSION == 0x0306 && INET_PATCH_LEVEL < 0x05)
#  error At least INET version 3.6.5 required
#endif

#if INET_VERSION >= 0x0363
#  error The INET 3.99 or newer versions are incompatible with this CoRE4INET version
#endif

#ifndef WITH_ETHERNET
#  error You must enable the Ethernet feature in INET framework
#endif

#ifdef WITH_AVB_COMMON
#endif

#ifdef WITH_AS6802_COMMON
#endif

#ifdef WITH_IEEE8021Q_COMMON
#endif

#ifdef WITH_IPORE
#ifndef WITH_IPv4
#  error You must enable the IPv4 feature in INET framework
#endif
#ifndef WITH_IPv6
#  error You must enable the IPv6 feature in INET framework
#endif
#ifndef WITH_TCP_COMMON
#  error You must enable the TCP_COMMON feature in INET framework
#endif
#ifndef WITH_TCP_INET
#  error You must enable the TCP_INET feature in INET framework
#endif
#ifndef WITH_UDP
#  error You must enable the UDP feature in INET framework
#endif
#ifndef WITH_SCTP
#  error You must enable the SCTP feature in INET framework
#endif
#endif

