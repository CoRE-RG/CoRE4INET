cplusplus {{
#include "INETDefs.h"
}}



//
// Represents payload in an TTEthernet-Message sent over API
//
packet APIPayload
{
    unsigned char data[]; //The actual payload encoded in bytes
}
