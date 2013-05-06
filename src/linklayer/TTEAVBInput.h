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

#ifndef TTEAVBINPUT_H_
#define TTEAVBINPUT_H_

#include "TTEInput.h"
#include <SRPFrame_m.h>

namespace TTEthernetModel {

class TTEAVBInput: public TTEInput
{
    protected:
        virtual void handleMessage(cMessage *msg);
        bool isAVB(EtherFrame *frame);
    public:
        TTEAVBInput();
};

} /* namespace TTEthernetModel */
#endif /* TTEAVBINPUT_H_ */
