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

#ifndef __TTETHERNETMODELV2_TTEINPUT_H_
#define __TTETHERNETMODELV2_TTEINPUT_H_

#include <omnetpp.h>

#include <ctc/Incoming.h>
#include <EtherFrame_m.h>

#include <map>
#include <list>

/**
 * TODO - Generated class
 */
namespace TTEthernetModel {
class TTEInput : public cSimpleModule
{
    private:
        std::map<uint16, std::list<Incoming*> > incomings;
        unsigned int ct_marker;
        unsigned int ct_mask;
    protected:
        static simsignal_t ctDroppedSignal;
    public:
        virtual void addIncoming(uint16 ctID, Incoming *incoming);
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
    private:
        virtual bool isCT(EtherFrame *frame);
        virtual uint16 getCTID(EtherFrame *frame);
};
}

#endif
