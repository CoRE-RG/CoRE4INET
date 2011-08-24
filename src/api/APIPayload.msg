cplusplus {{
#include "INETDefs.h"
}}



//
// Represents payload in an ICMP/ICMPv6 Echo Request/Reply.
//
packet APIPayload
{
    unsigned char data[];
}
