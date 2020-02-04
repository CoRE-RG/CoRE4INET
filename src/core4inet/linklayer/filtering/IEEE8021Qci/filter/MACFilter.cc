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

#include <core4inet/linklayer/filtering/IEEE8021Qci/filter/MACFilter.h>

namespace CoRE4INET {

Define_Module(MACFilter);

bool MACFilter::isMatching(inet::EtherFrame* frame)
{
    bool match = false;
    if ((this->srcAddress.isUnspecified() || this->srcAddress.getInt() == frame->getSrc().getInt())
            && (this->destAddress.isUnspecified() || this->destAddress.getInt() == frame->getDest().getInt())
            && IEEE8021QciFilter::isMatching(frame))
    {
        match = true;
    }
    return match;
}

void MACFilter::handleParameterChange(const char* parname)
{
    IEEE8021QciFilter::handleParameterChange(parname);
    if (!parname || !strcmp(parname, "srcAddress"))
    {
        if (strcmp(par("srcAddress").stdstringValue().c_str(), ""))
        {
            this->srcAddress.setAddress(par("srcAddress").stringValue());
        }
    }
    if (!parname || !strcmp(parname, "destAddress"))
    {
        if (strcmp(par("destAddress").stdstringValue().c_str(), ""))
        {
            this->destAddress.setAddress(par("destAddress").stringValue());
        }
    }
}

} //namespace
