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

#include "CoRE4INET_CTFrame.h"

namespace CoRE4INET {

unsigned short CTFrame::getCtID() const
{
    MACAddress mac = getDest();
    uint16_t CtID = 0;
    CtID = static_cast<uint16_t>(mac.getAddressByte(4) << 8);
    CtID = static_cast<uint16_t>(CtID | static_cast<uint16_t>(mac.getAddressByte(5)));
    return CtID;
}

void CTFrame::setCtID(uint16_t ctID)
{
    MACAddress mac = getDest();
    mac.setAddressByte(4, static_cast<unsigned char>(ctID >> 8));
    mac.setAddressByte(5, static_cast<unsigned char>(ctID));
    setDest(mac);
}

unsigned int CTFrame::getCtMarker() const
{
    MACAddress mac = getDest();
    uint32_t CtMarker = 0;
    CtMarker = static_cast<uint32_t>(mac.getAddressByte(0) << 24);
    CtMarker = CtMarker | static_cast<uint32_t>(mac.getAddressByte(1) << 16);
    CtMarker = CtMarker | static_cast<uint32_t>(mac.getAddressByte(2) << 8);
    CtMarker = CtMarker | static_cast<uint32_t>(mac.getAddressByte(3));
    return CtMarker;
}

void CTFrame::setCtMarker(uint32_t ctMarker)
{
    MACAddress mac = getDest();
    mac.setAddressByte(0, static_cast<unsigned char>(ctMarker >> 24));
    mac.setAddressByte(1, static_cast<unsigned char>(ctMarker >> 16));
    mac.setAddressByte(2, static_cast<unsigned char>(ctMarker >> 8));
    mac.setAddressByte(3, static_cast<unsigned char>(ctMarker));
    setDest(mac);
}

}
