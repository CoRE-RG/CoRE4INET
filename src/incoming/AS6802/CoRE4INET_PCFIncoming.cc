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
#include "CoRE4INET_PCFIncoming.h"
#include "PCFrame_m.h"

namespace CoRE4INET {

Define_Module(PCFIncoming);

PCFIncoming::PCFIncoming()
{
}

void PCFIncoming::initialize()
{
    pcfType = (PCFType) par("pcfType").longValue();
}

void PCFIncoming::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        PCFrame *frame = dynamic_cast<PCFrame *>(msg);
        recordPacketReceived(frame);

        if (frame->getType() != (uint8_t) pcfType)
        {
            EV_ERROR << "FRAME DROPPED, wrong type:" << (int) frame->getType() << " should be " << pcfType << endl;
            emit(droppedSignal, frame);
            delete frame;
        }
        else
        {
            sendDelayed(frame, SimTime(getParentModule()->par("hardware_delay").doubleValue()), "out");
        }
    }
}

void PCFIncoming::handleParameterChange(__attribute((unused)) const char* parname)
{
    pcfType = (PCFType) par("pcfType").longValue();
}

}
