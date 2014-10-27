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

#ifndef CORE4INET_IPORE_H_
#define CORE4INET_IPORE_H_

#include "CoRE4INET_IPv4oAVB.h"
#include "CoRE4INET_IPv4oRC.h"
#include "CoRE4INET_IPv4oTT.h"

namespace CoRE4INET {

class AVB_IPv4 : public IPv4oAVB<IPv4oREBase>
{
};

class RC_AVB_IPv4 : public IPv4oRC<AVB_IPv4>
{
};

/*!
this parameter defines which traffic is sent via TT, RC or AVB
The config consists of "filter" elements and "subscribe" elements

Each filter consists of several attributes.
Each attribute either is used to define the pattern to check if outgoing packets are matching them or is used to define how to send the matching packets:
The pattern attributes are always the same, no matter what kind of outgoing packet should be sent.
The other attributes, which are defining how to send the packet, vary, depending on which kind of packet should be sent (i.e. TT or RC or AVB)

Pattern attributes:
- srcAddress       (optional)
- srcPrefixLength  (optional)
- destAddress      (optional)
- destPrefixLength (optional)
- protocol         (optional)
- tos              (optional)
- tosMask          (optional)
- srcPort          (optional)
- srcPortMin       (optional)
- srcPortMax       (optional)
- destPort         (optional)
- destPortMin      (optional)
- destPortMax      (optional)

Destination Type (value of the "destType" attribute, which defines the Layer2)
- destType="DestinationType_TT"
- destType="DestinationType_RC"
- destType="DestinationType_AVB"

TT send attributes:
- destModule (mandatory)
- ctId       (mandatory)
- actionTime (mandatory)
- period     (optional, defaults to "period[0]")
- oscillator (optional, defaults to "oscillator")

RC send attributes:
- destModules (mandatory)
- ctId        (mandatory)

AVB send attributes:
- destModule      (mandatory)
- destMAC         (mandatory)
- streamId        (mandatory)
- trafficClass    (mandatory)
- frameSize       (mandatory)
- intervallFrames (mandatory)
- vlanId          (mandatory)

 Each subscribe element has one single "streamId" attribute which defines the stream Id to subscribe to.
 */
class TT_RC_AVB_IPv4 : public IPv4oTT<RC_AVB_IPv4>
{
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_IPORE_H_ */
