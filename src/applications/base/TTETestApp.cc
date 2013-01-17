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

#include "TTETestApp.h"
#include "CTFrame.h"

namespace TTEthernetModel {

Define_Module( TTETestApp);

void TTETestApp::initialize()
{
    scheduleAt(simTime(), new cMessage("ACTIVATOR!"));
}

void TTETestApp::handleMessage(cMessage *msg)
{
    if (!msg->arrivedOn("TTin") && *new std::string(getParentModule()->getName()) != "videoclient")
    {
        CTFrame *frame = new CTFrame("CT-ID=100");
        MACAddress srcAddr;
        srcAddr.setAddress("03 04 05 06 00 64");
        frame->setDest(srcAddr);
        frame->setCtID(100);
        //ENDE TEST

        if (getParentModule()->getSubmodule("VL_TT_100_CTC"))
            sendDirect(frame, getParentModule()->getSubmodule("VL_TT_100_CTC")->gate("in"));
    }

    if (!msg->arrivedOn("TTin") && *new std::string(getParentModule()->getName()) != "videoclient")
    {
        CTFrame *frame = new CTFrame("CT-ID=101");
        MACAddress srcAddr;
        srcAddr.setAddress("03 04 05 06 00 65");
        frame->setDest(srcAddr);
        frame->setCtID(100);
        frame->setByteLength(1500);
        //ENDE TEST

        if (getParentModule()->getSubmodule("VL_TT_101_CTC"))
            sendDirect(frame, getParentModule()->getSubmodule("VL_TT_101_CTC")->gate("in"));
    }

    delete msg;
    // TODO - Generated method body
}

} //namespace
