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

//CoRE4INET
#include "CoRE4INET_ConfigFunctions.h"

namespace CoRE4INET {

Define_Module(PCFIncoming);

PCFIncoming::PCFIncoming()
{
}

void PCFIncoming::initialize()
{
}

void PCFIncoming::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (PCFrame *frame = dynamic_cast<PCFrame *>(msg))
        {
            recordPacketReceived(frame);

            if (frame->getType() != static_cast<uint8_t>(pcfType))
            {
                EV_ERROR << "FRAME DROPPED, wrong type:" << static_cast<int>(frame->getType()) << " should be " << pcfType << endl;
                emit(droppedSignal, frame);
                delete frame;
            }
            else
            {
                sendDelayed(frame, getHardwareDelay(), "out");
            }
        }
        else
        {
            throw cRuntimeError("Received non-PCF frame");
        }
    }
}

void PCFIncoming::handleParameterChange(const char* parname)
{
    CTIncoming::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "pcfType"))
    {
        pcfType = static_cast<PCFType>(parameterULongCheckRange(par("pcfType"), 1, 3));
    }
}

}
