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

#include "core4inet/linklayer/filtering/IEEE8021Qci/IEEE8021QciInput.h"

namespace CoRE4INET {

Define_Module(IEEE8021QciInput);

void IEEE8021QciInput::initialize()
{
    int numStreamFilters = parameterULongCheckRange(getParentModule()->par("numStreamFilters"), 0, UINT32_MAX);
    streamFilters.clear();
    for (int i = 0; i < numStreamFilters; i++)
    {
        streamFilters.push_back(dynamic_cast<IEEE8021QciFilter*>(getParentModule()->getSubmodule("streamFilter", i)));
    }
}

void IEEE8021QciInput::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("upperLayerIn"))
    {
        if (inet::EtherFrame *frame = dynamic_cast<inet::EtherFrame*>(msg))
        {
            //First filtering implementation just for AVB frames
            if (AVBFrame *avbFrame = dynamic_cast<AVBFrame*>(frame))
            {
                bool filterFound = false;
                for(std::vector<IEEE8021QciFilter*>::iterator it = streamFilters.begin(); it != streamFilters.end(); ++it)
                {
                    IEEE8021QciFilter *streamFilter = *it;
                    if(!streamFilter){
                        throw cRuntimeError("StreamFilter is null");
                    }
                    if(streamFilter->getStreamID() == avbFrame->getStreamID()){
                        filterFound = true;
                        sendDirect(avbFrame, streamFilter->gate("in"));
                        break;
                    }
                }
                if(!filterFound){
                    send(avbFrame, "out");
                }
            }
            else
            {
                send(frame, "out");
            }
        }
        else
        {
            throw cRuntimeError("Received message on gate upperLayerIn that is no EtherFrame");
        }
    }
}

} //namespace
