#include "../features.h"

#include "inet/features.h"

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

