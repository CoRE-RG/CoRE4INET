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

#ifndef __TTE4INET_TTSHAPER_H
#define __TTE4INET_TTSHAPER_H

#include <ModuleAccess.h>
#include <TTBuffer.h>
#include <TTBufferEmpty_m.h>
#include <HelperFunctions.h>
#include <Timed.h>

namespace TTEthernetModel {

/**
 * @brief A Shaper for TTMessages.
 *
 * The TTShaper only allows lower priorities to transmit when their frames wont
 * collide with TTFrames
 *
 * @ingroup AS6802
 *
 * @author Till Steinbach
 */
template <class TC>
class TTShaper : public TC, public virtual Timed
{
    public:
        /**
         * @brief Constructor
         */
        TTShaper();
        /**
         * @brief Destructor
         */
        ~TTShaper();

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or NULL if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname);

    private:
        /**
         * @brief Queue for TT-Messages. Will be only filled when there is TT shuffling
         * configured or there was an error in the configuration.
         */
        cQueue ttQueue;

        /**
         * @brief Map of TTBuffers.
         *
         * The map is ordered by sendwindow
         */
        std::map <uint64_t, TTBuffer * > ttBuffers;
        bool initialize_ttBuffers;

        /**
         * @brief Current position of the next Buffer (action time) in the ttBuffers vector
         */
        size_t ttBuffersPos;

    protected:
        /**
         * @brief Signal that is emitted when the queue length of time-triggered messages changes.
         */
        static simsignal_t ttQueueLengthSignal;

    protected:
        /**
         * Initializes the module
         *
         * @param stage The stages. Module initializes when stage==0 && stage==1
         */
        virtual void initialize(int stage);

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return returns 3 or more depending on inheritance
         */
        virtual int numInitStages() const;

        /**
         * @brief Forwards the messages from the different buffers and LLC
         * according to the specification for TTMessages.
         *
         * Time-triggered messages are send immediately, lower priority frames are delayed
         * if they do not fit in the gap until the next time-triggered message.
         * If the mac layer is idle, messages are picked from the queues according
         * to the priorities, using the template class.
         * Time-triggered buffers can free the bandwidth reservation mechanism by sending
         * a TTBufferEmpty message.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg);

        /**
         * @brief Queues messages in the correct queue
         *
         * Time-triggered messages are queued in this module, other messages are forwarded to the
         * template classes enqueueMessage method
         *
         * @param msg the incoming message
         */
        virtual void enqueueMessage(cMessage *msg);

        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
         *
         * @param msg the message to be queued
         */
        virtual void requestPacket();

        /**
         * @brief Returns true when there are no pending messages.
         *
         * @return true if all queues are empty.
         */
        virtual bool isEmpty();

        /**
         * @brief Clears all queued packets and stored requests.
         */
        virtual void clear();

        /**
         * @brief Returns a frame directly from the queues, bypassing the primary,
         * send-on-request mechanism. Returns NULL if the queue is empty.
         *
         * @return the message with the highest priority from any queue. NULL if the
         * queues are empty or cannot send due to the traffic policies.
         */
        virtual cMessage *pop();

        /**
         * @brief Returns a pointer to a frame directly from the queues.
         *
         * front must return a pointer to the same message pop() would return.
         *
         * @return pointer to the message with the highest priority from any queue. NULL if the
         * queues are empty
         */
        virtual cMessage *front();

    private:
        /**
         * @brief Helper function to check whether a Messages is allowed to be transmitted.
         *
         * The function checks whether a message fits in the gap until the next TT-message
         * should be transmitted. It uses the message length to calculate the transmission
         * duration.
         *
         * @param message The message that should be transmitted
         * @returns true if transmission is allowed else false
         */
        virtual bool isTransmissionAllowed(EtherFrame *message);

        /**
         * @brief Registers a time-triggered buffer that feeds the module.
         */
        virtual void registerTTBuffer(TTBuffer *buffer);

        /**
         * @brief check whether a time-triggered buffer is registered.
         *
         * @param ttBuffer the ttBuffer to check for
         * @returns true when registered, else false
         */
        virtual bool isTTBufferRegistered(TTBuffer *ttBuffer);
};

template <class TC>
simsignal_t TTShaper<TC>::ttQueueLengthSignal = SIMSIGNAL_NULL;

template <class TC>
TTShaper<TC>::TTShaper(){
    ttBuffersPos = 0;
    ttQueue.setName("TT Messages");
    initialize_ttBuffers=false;
}

template <class TC>
TTShaper<TC>::~TTShaper(){
    ttQueue.clear();
}

template <class TC>
void TTShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if(stage==0){
        Timed::initialize();
        ttQueueLengthSignal = cComponent::registerSignal("ttQueueLength");
    }
    else if(stage==2){
        //Now the ttBuffers can be initialized as all TTBuffers should have registred their events
        initialize_ttBuffers=true;
        handleParameterChange("tt_buffers");
    }
}
template <class TC>
int TTShaper<TC>::numInitStages() const{
    if(TC::numInitStages()>3){
        return TC::numInitStages();
    }
    else{
        return 3;
    }
}

template <class TC>
void TTShaper<TC>::handleMessage(cMessage *msg)
{
    //Frames arrived on in are rate-constrained frames
    if (msg->arrivedOn("TTin"))
    {
        TTBuffer *thisttBuffer;
        TTBuffer *ttBuffer = dynamic_cast<TTBuffer*> (msg->getSenderModule());
        ASSERT(isTTBufferRegistered(ttBuffer)==true);//No shuffeling at the moment
        ASSERT2(ttBuffer, "A TTFrame was received that was not sent by a TTBuffer");

        if(ttBuffers.size()>0){
            thisttBuffer = ttBuffers.begin()->second;
        }else{
            thisttBuffer = NULL;
        }
        ASSERT(thisttBuffer==ttBuffer);
        if(thisttBuffer!=ttBuffer){
            ASSERT2(isTTBufferRegistered(ttBuffer)==false, "A TTFrame was received that was unexpected");
        }
        //Now reregister the same TTBuffer
        ttBuffers.erase(ttBuffers.begin());
        registerTTBuffer(ttBuffer);

        //If we have an empty message allow lower priority frame to be sent
        if (dynamic_cast<TTBufferEmpty *> (msg))
        {
            if (TC::getNumPendingRequests())
            {
                cMessage* lowPrioFrame = TC::pop();
                if(lowPrioFrame){
                    TC::framesRequested--;
                    cSimpleModule::send(lowPrioFrame, cModule::gateBaseId("out"));
                }
            }
            delete msg;
        }
        //Else send TT frame
        else
        {
            if (TC::getNumPendingRequests())
            {
                TC::framesRequested--;
                cSimpleModule::send(msg, cModule::gateBaseId("out"));
            }
            else
            {
                ASSERT2(isTTBufferRegistered(ttBuffer)==false, "TTFrame was delayed without permission");
                enqueueMessage(msg);
            }
        }
    }
    else{
        if(TC::getNumPendingRequests() && isTransmissionAllowed((EtherFrame*) msg)){
            TC::handleMessage(msg);
        }
        else{
            TC::enqueueMessage(msg);
        }
    }
}

template <class TC>
void TTShaper<TC>::enqueueMessage(cMessage *msg){
    if(msg->arrivedOn("TTin")){
        ttQueue.insert(msg);
        cComponent::emit(ttQueueLengthSignal, ttQueue.length());
        TC::notifyListeners();
    }
    else{
        TC::enqueueMessage(msg);
    }
}

template <class TC>
void TTShaper<TC>::requestPacket()
{
    Enter_Method("requestPacket()");
    //Feed the MAC layer with the next frame
    TC::framesRequested++;

    if (cMessage *msg = pop())
    {
        TC::framesRequested--;
        cSimpleModule::send(msg, cModule::gateBaseId("out"));
    }
}

template <class TC>
cMessage* TTShaper<TC>::pop()
{
    Enter_Method("pop()");
    //TTFrames
    if (!ttQueue.isEmpty())
    {
        cMessage *msg = (cMessage*) ttQueue.pop();
        cComponent::emit(ttQueueLengthSignal, ttQueue.length());

        //TODO Update buffers:
        if(ttBuffers.size()>0){
            ttBuffersPos = (ttBuffersPos + 1) % ttBuffers.size();
        }

        return msg;
    }
    else{
        EtherFrame *frontMsg = (EtherFrame*) front();
        if(isTransmissionAllowed(frontMsg)){
            return TC::pop();
        }
    }
    return NULL;
}

template <class TC>
cMessage* TTShaper<TC>::front()
{
    Enter_Method("front()");
    //TTFrames
    if (!ttQueue.isEmpty())
    {
        cMessage *msg = (cMessage*) ttQueue.front();
        return msg;
    }
    return TC::front();
}

template <class TC>
bool TTShaper<TC>::isEmpty()
{
        return ttQueue.isEmpty() && TC::isEmpty();
}

template <class TC>
void TTShaper<TC>::clear()
{
        TC::clear();
        ttQueue.clear();
}

template <class TC>
void TTShaper<TC>::registerTTBuffer(TTBuffer *ttBuffer)
{
    Enter_Method("registerTTBuffer(%s)", ttBuffer->getName());
    uint64_t sendWindowStart = ttBuffer->nextSendWindowStart();
    ev << "sendWindowStart:  "<< sendWindowStart << " Buffer:"<< ttBuffer->getName() <<std::endl;

    std::map<uint64_t, TTBuffer*>::iterator buf = ttBuffers.find(sendWindowStart);
    if(buf!=ttBuffers.end()){
        //TODO ERROR
        opp_error("ERROR!");
    }
    else{
        //TODO check overlapping
        ttBuffers[sendWindowStart] = ttBuffer;
    }

}

template <class TC>
bool TTShaper<TC>::isTTBufferRegistered(TTBuffer *ttBuffer){
    for (std::map<uint64_t, TTBuffer*>::iterator buffer = ttBuffers.begin(); buffer != ttBuffers.end();++buffer)
    {
        if((*buffer).second==ttBuffer){
            return true;
        }
    }
    return false;
}

template <class TC>
void TTShaper<TC>::handleParameterChange(const char* parname){
    TC::handleParameterChange(parname);
    if(initialize_ttBuffers){
        ttBuffers.clear();
        std::vector<std::string> ttBufferPaths = cStringTokenizer(cComponent::par("tt_buffers").stringValue(), DELIMITERS).asVector();
        for(std::vector<std::string>::iterator ttBufferPath = ttBufferPaths.begin();
                ttBufferPath!=ttBufferPaths.end();ttBufferPath++){
            cModule* module = simulation.getModuleByPath((*ttBufferPath).c_str());
            if(!module){
                module = findModuleWhereverInNode((*ttBufferPath).c_str(),this);
            }
            if(module){
                if(findContainingNode(module)!=findContainingNode(this)){
                    opp_error("Configuration problem of tt_buffers: Module: %s is not in node %s! Maybe a copy-paste problem?", (*ttBufferPath).c_str(),
                            findContainingNode(this)->getFullName());
                }
                else
                {
                    TTBuffer *ttBuffer = dynamic_cast<TTBuffer*> (module);
                    if(ttBuffer){
                        registerTTBuffer(ttBuffer);
                    }
                    else{
                        opp_error("Configuration problem of tt_buffers: Module: %s is no TT-Buffer!", (*ttBufferPath).c_str());
                    }
                }
            }
            else{
                opp_error("Configuration problem of tt_buffers: Module: %s could not be resolved!", (*ttBufferPath).c_str());
            }
        }
    }
}

template <class TC>
bool TTShaper<TC>::isTransmissionAllowed(EtherFrame *message)
{
    if (!message || !TC::outChannel)
    {
        return false;
    }
    //If there are no ttBuffers everything is fine
    if (ttBuffers.size() == 0)
    {
        return true;
    }
    //SimTime sendTime = (message->getBitLength()+INTERFRAME_GAP_BITS)/txRate;
    SimTime sendTime = TC::outChannel->calculateDuration(message);
    //Don't know if that is right, but it works!
    sendTime += (INTERFRAME_GAP_BITS + ((PREAMBLE_BYTES + SFD_BYTES) * 8)) / TC::outChannel->getNominalDatarate();
    unsigned long sendTicks = ceil((sendTime / oscillator->par("tick")).dbl());
    unsigned long startTicks = ttBuffers.begin()->first;

    //TODO: Perhaps more complex calculations needed?
    if ((timer->getTotalTicks() + sendTicks) >= startTicks)
    {
        ev << "transmission not allowed! Send time would be from " << timer->getTotalTicks() << " to " << timer->getTotalTicks() + sendTicks << " tt_window starts at: " << startTicks << endl;
        return false;
    }
    return true;
}

}

#endif

