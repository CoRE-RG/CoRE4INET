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

#ifndef __TTETHERNETMODELV2_BUFFER_H_
#define __TTETHERNETMODELV2_BUFFER_H_

#include <omnetpp.h>
#include <EtherFrame_m.h>
#include <list>

/**
 * TODO - Generated class
 */
namespace TTEthernetModel {

class TTEApplicationBase;
class TTEAPIPriv;
class Callback;

class Buffer : public cSimpleModule
{
    protected:
        std::list<cGate*> destinationGates;
        std::map<TTEApplicationBase*, Callback*> receiveCallbacks;
        std::map<TTEApplicationBase*, Callback*> transmitCallbacks;

    private:
        virtual void initializeStatistics();
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void enqueue(EtherFrame *newFrame);
        virtual EtherFrame* dequeue();
        virtual void recordPacketSent();
        virtual void setIsEmpty(bool empty);

    public:
    public:
        Buffer();
        virtual EtherFrame* getFrame();
        virtual ~Buffer();
        virtual void addDestinationGate(cGate *destinationGate);
        virtual void removeDestinationGate(cGate *destinationGate);
        virtual void addReceiveCallback(Callback *cb, TTEApplicationBase *application);
        virtual Callback* getReceiveCallback(TTEApplicationBase *application);
        virtual void addTransmitCallback(Callback *cb, TTEApplicationBase *application);
        virtual Callback* getTransmitCallback(TTEApplicationBase *application);

    protected:
        static simsignal_t txPkSignal;
        static simsignal_t latencySignal;

};
}

#endif
