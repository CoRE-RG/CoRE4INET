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

#include "QTagFilter.h"

namespace CoRE4INET {

Define_Module(QTagFilter);

bool QTagFilter::isMatching(inet::EtherFrame* frame)
{
    bool match = false;
    if (EthernetIIFrameWithQTag* qframe = dynamic_cast<EthernetIIFrameWithQTag*>(frame))
    {
        if ((this->vid == -1 || this->vid == qframe->getVID())
                && (this->pcp == -1 || this->pcp == qframe->getPcp())
                && MACFilter::isMatching(frame))
        {
            match = true;
        }
    }
    return match;
}

void QTagFilter::handleParameterChange(const char* parname)
{
    MACFilter::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "vID"))
    {
        this->vid = static_cast<uint16_t>(parameterLongCheckRange(par("vID"), -1, MAX_VLAN_ID));
    }
    if (!parname || !strcmp(parname, "pcp"))
    {
        this->pcp = static_cast<uint8_t>(parameterLongCheckRange(par("pcp"), -1, 7));
    }
}

} //namespace


