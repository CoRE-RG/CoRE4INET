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

#ifndef CORE4INET_SRPETHERENCAP_H_
#define CORE4INET_SRPETHERENCAP_H_

#include "CoRE4INET_BGEtherEncap.h"

#include "SRPFrame_m.h"
#include "EtherFrame_m.h"

namespace CoRE4INET {

class SRPEtherEncap : public virtual BGEtherEncap
{

    public:
        SRPEtherEncap();
        virtual ~SRPEtherEncap();

    protected:
        virtual void handleMessage(cMessage *msg) override;
    private:
        void dispatchSRP(SRPFrame * srp);
        void deliverSRP(EtherFrame * frame);

};

} /* namespace CoRE4INET */

#endif /* CORE4INET_SRPETHERENCAP_H_ */
