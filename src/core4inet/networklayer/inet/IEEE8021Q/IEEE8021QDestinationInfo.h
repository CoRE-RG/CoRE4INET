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

#ifndef CORE4INET_IEEE8021QDESTINATIONINFO_H_
#define CORE4INET_IEEE8021QDESTINATIONINFO_H_

//==============================================================================

#include "core4inet/networklayer/inet/base/DestinationInfo.h"

//==============================================================================

#include "core4inet/buffer/base/BGBuffer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

class IEEE8021QDestinationInfo : public DestinationInfo
{

    public:
        IEEE8021QDestinationInfo();
        virtual ~IEEE8021QDestinationInfo();

    public:
        inet::MACAddress* getDestMac() const { return destMAC; }

        void setDestMac(inet::MACAddress* destMac) { destMAC = destMac; }

        uint16_t getVID() const
        {
            return vid;
        }
        void setVID(uint16_t new_vid)
        {
            this->vid = new_vid;
        }
        uint8_t getPCP() const
        {
            return pcp;
        }
        void setPCP(uint8_t new_pcp)
        {
            this->pcp = new_pcp;
        }
        std::list<BGBuffer*>& getDestModules()
        {
            return destModules;
        }
        void setDestModules(std::list<BGBuffer*>& new_destModules)
        {
            this->destModules = new_destModules;
        }

    private:
        std::list<BGBuffer*> destModules;
        uint16_t vid;
        uint8_t pcp;
        inet::MACAddress  *destMAC;

};

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#endif /* CORE4INET_RCDESTINATIONINFO_H_ */

//==============================================================================
//EOF
