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

#include "core4inet/networklayer/inet/AS6802/QueuedPacket.h"

namespace CoRE4INET {

QueuedPacket::QueuedPacket()
  : filter(nullptr),
    packet(nullptr)
{
}


QueuedPacket::QueuedPacket(IPoREFilter *new_filter, cPacket *new_packet)
{
    this->filter = new_filter;
    this->packet = new_packet;
}

QueuedPacket::~QueuedPacket()
{
}

} /* namespace CoRE4INET */
