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

#include "CoRE4INET_BaseInControl.h"

namespace CoRE4INET {

simsignal_t BaseInControl::rxPkSignal = registerSignal("rxPk");

void BaseInControl::initialize()
{
    Timed::initialize();
}

void BaseInControl::setParameters(EtherFrame *frame)
{
    if (frame)
    {
        int i = frame->findPar("received_total");
        cMsgPar* parameter;
        if (i >= 0)
            parameter = &frame->par(i);
        else
            parameter = &frame->addPar("received_total");
        parameter->setLongValue(static_cast<long>(getTimer()->getTotalTicks()));

        i = frame->findPar("received_port");
        if (i >= 0)
            parameter = &frame->par(i);
        else
            parameter = &frame->addPar("received_port");
        parameter->setLongValue(getParentModule()->getIndex());
    }
}

void BaseInControl::recordPacketReceived(EtherFrame *frame)
{
    emit(rxPkSignal, frame);
}

}
