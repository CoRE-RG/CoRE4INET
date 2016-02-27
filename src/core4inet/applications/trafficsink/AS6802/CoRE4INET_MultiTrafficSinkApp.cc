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

#include "CoRE4INET_MultiTrafficSinkApp.h"

//CoRE4INET
#include "CoRE4INET_CTFrame.h"

namespace CoRE4INET {

Define_Module(MultiTrafficSinkApp);

std::unordered_map<uint16_t, simsignal_t> MultiTrafficSinkApp::rxPkSignal;

void MultiTrafficSinkApp::handleMessage(cMessage *msg)
{
    ApplicationBase::handleMessage(msg);

    if (msg->arrivedOn("RCin") || msg->arrivedOn("TTin"))
    {
        CTFrame *ctframe = dynamic_cast<CTFrame*>(msg);
        if (ctframe)
        {
            uint16_t ctID = ctframe->getCtID();
            std::unordered_map<uint16_t, simsignal_t>::const_iterator entry = rxPkSignal.find(ctID);
            simsignal_t signal;
            if (entry != rxPkSignal.end())
            {
                signal = entry->second;
            }
            else
            {
                char strBuf[16];
                snprintf(strBuf, sizeof(strBuf), "rxPk:%d", ctID);
                signal = registerSignal(strBuf);
                cProperty *statisticTemplate = getProperties()->get("statisticTemplate", "rxPk");
                ev.addResultRecorders(this, signal, strBuf, statisticTemplate);
                //statisticTemplate = getProperties()->get("statisticTemplate", "latency");
                //cResultFilter *messageAgeFilter = cResultFilterDescriptor::get("messageAge")->create();
                //subscribe(signal, messageAgeFilter);
                //ev.addResultRecorders(this, messageAgeFilter, strBuf, statisticTemplate);

                rxPkSignal[ctID] = signal;
            }
            emit(signal, ctframe);
        }
        else
        {
            EV_ERROR << "only ct frames will collect statistics" << std::endl;
        }
    }
    delete msg;
}

} //namespace
