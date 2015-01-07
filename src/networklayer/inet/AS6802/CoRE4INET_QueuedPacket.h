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

#ifndef CORE4INET_QUEUEDPACKET_H_
#define CORE4INET_QUEUEDPACKET_H_

#include "CoRE4INET_IPoREFilter.h"
#include "InterfaceEntry.h"

namespace CoRE4INET {

class QueuedPacket {
public:
    QueuedPacket();
    QueuedPacket(IPoREFilter *filter, cPacket *packet);
    virtual ~QueuedPacket();

    IPoREFilter* getFilter() { return filter; }
    void setFilter(IPoREFilter* new_filter) { this->filter = new_filter; }
    cPacket* getPacket() { return packet; }
    void setPacket(cPacket* new_packet) { this->packet = new_packet; }

protected:
    IPoREFilter    *filter;
    cPacket        *packet;
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_QUEUEDPACKET_H_ */
