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

#ifndef CORE4INET_RCDESTINATIONINFO_H_
#define CORE4INET_RCDESTINATIONINFO_H_

//==============================================================================

#include "CoRE4INET_DestinationInfo.h"

//==============================================================================

#include "CoRE4INET_CTBuffer.h"

//==============================================================================

namespace CoRE4INET {

//==============================================================================

class RCDestinationInfo : public DestinationInfo {


public:
    RCDestinationInfo();
    virtual ~RCDestinationInfo();


public:
    uint16_t getCtId() const { return ctId; }
    void setCtId(uint16_t ctId) { this->ctId = ctId; }
    std::list<CTBuffer*>& getDestModules() { return destModules; }
    void setDestModules(std::list<CTBuffer*>& destModules) { this->destModules = destModules; }


private:
    std::list<CTBuffer*> destModules;
    uint16_t             ctId;

};

//==============================================================================

} /* namespace CoRE4INET */

//==============================================================================

#endif /* CORE4INET_RCDESTINATIONINFO_H_ */

//==============================================================================
//EOF
