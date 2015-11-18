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

#ifndef CORE4INET_IPOREFILTER_H_
#define CORE4INET_IPOREFILTER_H_

#include "CoRE4INET_TrafficPattern.h"
#include "CoRE4INET_DestinationInfo.h"

namespace CoRE4INET {

class IPoREFilter {


public:
    IPoREFilter();
    virtual ~IPoREFilter();

    DestinationInfo* getDestInfo() const {
        return destInfo;
    }

    void setDestInfo(DestinationInfo* new_destInfo) {
        this->destInfo = new_destInfo;
    }

    TrafficPattern* getTrafficPattern() const {
        return trafficPattern;
    }

    void setTrafficPattern(TrafficPattern* new_trafficPattern) {
        this->trafficPattern = new_trafficPattern;
    }

private:
    TrafficPattern  *trafficPattern;
    DestinationInfo *destInfo;

};

} /* namespace CoRE4INET */

#endif /* CORE4INET_IPOREFILTER_H_ */
