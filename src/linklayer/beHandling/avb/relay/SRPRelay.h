//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __CORE4INET_SRPRELAY_H_
#define __CORE4INET_SRPRELAY_H_

#include "Ieee8021dRelay.h"
#include "SRPFrame_m.h"

namespace CoRE4INET {

class SRPRelay : public Ieee8021dRelay
{

    protected:
        virtual void initialize(int stage);
        virtual int numInitStages() const { return 1>Ieee8021dRelay::numInitStages()?1:Ieee8021dRelay::numInitStages(); }
        virtual void handleMessage(cMessage * msg);

        void dispatchSRP(SRPFrame * srp);

        void deliverSRP(EtherFrame * frame);

};

}
#endif
