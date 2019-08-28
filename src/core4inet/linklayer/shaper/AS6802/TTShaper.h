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

#ifndef CORE4INET_TTSHAPER_H
#define CORE4INET_TTSHAPER_H

//Std
#include <map>
//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/buffer/AS6802/TTBuffer.h"
#include "core4inet/utilities/ModuleAccess.h"
#include "core4inet/utilities/ConfigFunctions.h"
//Auto-generated Messages
#include "core4inet/buffer/AS6802/TTBufferEmpty_m.h"

namespace CoRE4INET {

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
template<class TC>
class TTShaper : public TC, public virtual Timed
{
        using Timed::initialize;

    public:
        /**
         * @brief Constructor
         */
        TTShaper();

        /**
         * @brief Destructor
         */
        virtual ~TTShaper() override;

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
        std::map<uint64_t, TTBuffer *> ttBuffers;
        bool initialize_ttBuffers;

        /**
         * @brief Current position of the next Buffer (action time) in the ttBuffers vector
         */
        size_t ttBuffersPos;

        /**
         * Caches the safetyMargin parameter
         */
        uint32_t safetyMargin;

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
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return returns 3 or more depending on inheritance
         */
        virtual int numInitStages() const override;

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
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Queues messages in the correct queue
         *
         * Time-triggered messages are queued in this module, other messages are forwarded to the
         * template classes enqueueMessage method
         *
         * @param msg the incoming message
         */
        virtual void enqueueMessage(cMessage *msg) override;

        /**
         * @brief this method is invoked when the underlying mac is idle.
         *
         * When this method is invoked the module sends a new message when there is
         * one. Else it saves the state and sends the message immediately when it is
         * received.
         *
         */
        virtual void requestPacket() override;

        /**
         * @brief Returns true when there are no pending messages.
         *
         * @return true if all queues are empty.
         */
        virtual bool isEmpty() override;

        /**
         * @brief Clears all queued packets and stored requests.
         */
        virtual void clear() override;

        /**
         * @brief Returns a frame directly from the queues, bypassing the primary,
         * send-on-request mechanism. Returns nullptr if the queue is empty.
         *
         * @return the message with the highest priority from any queue. nullptr if the
         * queues are empty or cannot send due to the traffic policies.
         */
        virtual cMessage *pop() override;

        /**
         * @brief Returns a pointer to a frame directly from the queues.
         *
         * front must return a pointer to the same message pop() would return.
         *
         * @return pointer to the message with the highest priority from any queue. nullptr if the
         * queues are empty
         */
        virtual cMessage *front() override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

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
        virtual bool isTransmissionAllowed(inet::EtherFrame *message);

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
        virtual bool isTTBufferRegistered(const TTBuffer *ttBuffer) const;
};

template<class TC>
simsignal_t TTShaper<TC>::ttQueueLengthSignal = cComponent::registerSignal("ttQueueLength");

template<class TC>
TTShaper<TC>::TTShaper()
{
    ttBuffersPos = 0;
    ttQueue.setName("TT Messages");
    initialize_ttBuffers = false;
    safetyMargin = 0;
}

template<class TC>
TTShaper<TC>::~TTShaper()
{
    ttQueue.clear();
}

template<class TC>
void TTShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        Timed::initialize();
        //Send initial signal to create statistic
        cComponent::emit(ttQueueLengthSignal, static_cast<unsigned long>(ttQueue.getLength()));
    }
    else if (stage == 2)
    {
        //Now the ttBuffers can be initialized as all TTBuffers should have registred their events
        initialize_ttBuffers = true;
        handleParameterChange("tt_buffers");
        WATCH_MAP(ttBuffers);
    }
}
template<class TC>
int TTShaper<TC>::numInitStages() const
{
    if (TC::numInitStages() > 3)
    {
        return TC::numInitStages();
    }
    else
    {
        return 3;
    }
}

template<class TC>
void TTShaper<TC>::handleMessage(cMessage *msg)
{
    //Frames arrived on in are rate-constrained frames
    if (msg && msg->arrivedOn("TTin"))
    {
        TTBuffer *thisttBuffer;
        TTBuffer *ttBuffer = dynamic_cast<TTBuffer*>(msg->getSenderModule());
        if (!ttBuffer)
        {
            throw cRuntimeError("A TTFrame was received that was not sent by a TTBuffer! %s is not a TTBuffer",
                    msg->getSenderModule()->getFullName());
        }
        ASSERT(isTTBufferRegistered(ttBuffer) == true); //No shuffeling at the moment
        if (ttBuffers.size() > 0)
        {
            thisttBuffer = ttBuffers.begin()->second;
        }
        else
        {
            thisttBuffer = nullptr;
        }
        if (thisttBuffer != ttBuffer)
        {
            if (isTTBufferRegistered(ttBuffer) != false)
            {
                throw cRuntimeError(
                        "A TTFrame was received that was unexpected. Expected Frame from Buffer: %s, received Frame from Buffer %s",
                        thisttBuffer->getFullName(), ttBuffer->getFullName());
            }
            else
            {
                throw cRuntimeError(
                        "Warning! Frame shuffling is not yet implemented! You must register all TTBuffers in the shaper! %s was not registered",
                        ttBuffer->getFullName());
            }
        }
        //Now reregister the same TTBuffer
        ttBuffers.erase(ttBuffers.begin());
        registerTTBuffer(ttBuffer);

        //If we have an empty message allow lower priority frame to be sent
        if (dynamic_cast<TTBufferEmpty *>(msg))
        {
            if (TC::getNumPendingRequests())
            {
                EV_TRACE << "TT Buffer was empty, allow lower priority frame" << endl;
                cMessage* lowPrioFrame = pop();
                if (lowPrioFrame)
                {
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
                if (isTTBufferRegistered(ttBuffer) != false)
                {
                    EV_ERROR << "TTFrame was delayed without permission at " << getTimer()->getTotalTicks() << endl;
                    throw cRuntimeError("TTFrame was delayed without permission");
                }
                enqueueMessage(msg);
            }
        }
    }
    else
    {
        if (TC::getNumPendingRequests() && isTransmissionAllowed(dynamic_cast<inet::EtherFrame*>(msg)))
        {
            TC::handleMessage(msg);
        }
        else
        {
            TC::enqueueMessage(msg);
        }
    }
}

template<class TC>
void TTShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn("TTin"))
    {
        ttQueue.insert(msg);
        cComponent::emit(ttQueueLengthSignal, static_cast<unsigned long>(ttQueue.getLength()));
        TC::notifyListeners();
        EV_TRACE << "Interface not idle queuing TT frame" << endl;
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void TTShaper<TC>::requestPacket()
{
    Enter_Method
    ("requestPacket()");
    //Feed the MAC layer with the next frame
    TC::framesRequested++;

    if (cMessage *msg = pop())
    {
        TC::framesRequested--;
        cSimpleModule::send(msg, cModule::gateBaseId("out"));
    }
}

template<class TC>
cMessage* TTShaper<TC>::pop()
{
    Enter_Method
    ("pop()");
    //TTFrames
    if (!ttQueue.isEmpty())
    {
        cMessage *msg = static_cast<cMessage*>(ttQueue.pop());
        cComponent::emit(ttQueueLengthSignal, static_cast<unsigned long>(ttQueue.getLength()));

        if (ttBuffers.size() > 0)
        {
            ttBuffersPos = (ttBuffersPos + 1) % ttBuffers.size();
        }

        return msg;
    }
    else
    {
        inet::EtherFrame *frontMsg = static_cast<inet::EtherFrame*>(front());
        if (isTransmissionAllowed(frontMsg))
        {
            return TC::pop();
        }
    }
    return nullptr;
}

template<class TC>
cMessage* TTShaper<TC>::front()
{
    Enter_Method
    ("front()");
    //TTFrames
    if (!ttQueue.isEmpty())
    {
        cMessage *msg = static_cast<cMessage*>(ttQueue.front());
        return msg;
    }
    return TC::front();
}

template<class TC>
bool TTShaper<TC>::isEmpty()
{
    return ttQueue.isEmpty() && TC::isEmpty();
}

template<class TC>
void TTShaper<TC>::clear()
{
    TC::clear();
    ttQueue.clear();
}

template<class TC>
void TTShaper<TC>::registerTTBuffer(TTBuffer *ttBuffer)
{
    Enter_Method
    ("registerTTBuffer(%s)", ttBuffer->getName());
    uint64_t sendWindowStart = ttBuffer->nextSendWindowStart();

    std::map<uint64_t, TTBuffer*>::iterator buf = ttBuffers.find(sendWindowStart);
    if (buf != ttBuffers.end())
    {
        throw cRuntimeError(
                "ERROR! You cannot schedule two messages with the same send window (%d)! Buffers are %s and %s",
                sendWindowStart, ttBuffer->getName(), buf->second->getName());
    }
    else
    {
        //The following tests are only trivial. A complex check of the windows should be done with a suitable scheduling
        //tool. as it is takes too much computation time for a runtime check!

        //Check for overlapping windows only when new buffer has a sendWindowEnd set
        if (ttBuffer->par("sendWindowEnd").intValue())
        {
            for (std::map<uint64_t, TTBuffer*>::iterator buffer = ttBuffers.begin(); buffer != ttBuffers.end();
                    ++buffer)
            {
                //Check for overlapping windows only when other buffer has a sendWindowEnd set
                if ((*buffer).second->par("sendWindowEnd").intValue())
                {
                    uint64_t other_offset = (*buffer).second->getPeriod()->getOffsetTicks();
                    uint64_t other_sendWindowStart = (*buffer).second->getSendWindowStart() + other_offset;
                    uint64_t other_sendWindowEnd = (*buffer).second->getSendWindowEnd() + other_offset;
                    uint64_t this_offset = ttBuffer->getPeriod()->getOffsetTicks();
                    uint64_t this_sendWindowStart = ttBuffer->getSendWindowStart() + this_offset;
                    uint64_t this_sendWindowEnd = ttBuffer->getSendWindowEnd() + this_offset;
                    //For simplification one cycle is added to the WindowEnd if it is in the next cycle
                    if (other_sendWindowEnd < other_sendWindowStart)
                    {
                        other_sendWindowEnd += (*buffer).second->getPeriod()->getCycleTicks();
                    }
                    if (this_sendWindowEnd < this_sendWindowStart)
                    {
                        this_sendWindowEnd += ttBuffer->getPeriod()->getCycleTicks();
                    }
                    //Now that we have everything together do the check!
                    if (other_sendWindowStart < this_sendWindowStart && other_sendWindowEnd > this_sendWindowStart)
                    {
                        throw cRuntimeError(
                                "ERROR! You cannot schedule two messages with overlapping send windows! Window of %s starts before window of %s ends",
                                ttBuffer->getFullPath().c_str(), (*buffer).second->getFullPath().c_str());
                    }
                    if (this_sendWindowStart < other_sendWindowStart && this_sendWindowEnd > other_sendWindowStart)
                    {
                        throw cRuntimeError(
                                "ERROR! You cannot schedule two messages with overlapping send windows! Window of %s starts before window of %s ends",
                                (*buffer).second->getFullPath().c_str(), ttBuffer->getFullPath().c_str());
                    }
                }
            }
        }
        ttBuffers[sendWindowStart] = ttBuffer;
    }

}

template<class TC>
bool TTShaper<TC>::isTTBufferRegistered(const TTBuffer *ttBuffer) const
{
    for (std::map<uint64_t, TTBuffer*>::const_iterator buffer = ttBuffers.begin(); buffer != ttBuffers.end(); ++buffer)
    {
        if ((*buffer).second == ttBuffer)
        {
            return true;
        }
    }
    return false;
}

template<class TC>
void TTShaper<TC>::handleParameterChange(const char* parname)
{
    TC::handleParameterChange(parname);
    Timed::handleParameterChange(parname);

    if (initialize_ttBuffers)
    {
        ttBuffers.clear();
        std::vector<std::string> ttBufferPaths = cStringTokenizer(cComponent::par("tt_buffers").stringValue(),
        DELIMITERS).asVector();
        for (std::vector<std::string>::iterator ttBufferPath = ttBufferPaths.begin();
                ttBufferPath != ttBufferPaths.end(); ttBufferPath++)
        {
            cModule* module = getSimulation()->getModuleByPath((*ttBufferPath).c_str());
            if (!module)
            {
                module = findModuleWhereverInNode((*ttBufferPath).c_str(), this);
            }
            if (module)
            {
                if (inet::findContainingNode(module) != inet::findContainingNode(this))
                {
                    throw cRuntimeError(
                            "Configuration problem of tt_buffers: Module: %s is not in node %s! Maybe a copy-paste problem?",
                            (*ttBufferPath).c_str(), findContainingNode(this)->getFullName());
                }
                else
                {
                    TTBuffer *ttBuffer = dynamic_cast<TTBuffer*>(module);
                    if (ttBuffer)
                    {
                        if (ttBuffer->par("enabled").boolValue())
                        {
                            if (!isTTBufferRegistered(ttBuffer))
                            {
                                registerTTBuffer(ttBuffer);
                            }
                            else
                            {
                                throw cRuntimeError(
                                        "Configuration problem of tt_buffers: Module: %s is in the list more than once!",
                                        (*ttBufferPath).c_str());
                            }
                        }
                        else
                        {
                            EV_INFO << "Buffer " << ttBuffer->getName() << "is disabled and not added to shaper!"
                                    << endl;
                        }
                    }
                    else
                    {
                        throw cRuntimeError("Configuration problem of tt_buffers: Module: %s is no TT-Buffer!",
                                (*ttBufferPath).c_str());
                    }
                }
            }
            else
            {
                throw cRuntimeError("Configuration problem of tt_buffers: Module: %s could not be resolved!",
                        (*ttBufferPath).c_str());
            }
        }
    }
    if (!parname || !strcmp(parname, "safety_margin"))
    {
        this->safetyMargin = static_cast<uint32_t>(parameterULongCheckRange(par("safety_margin"), 0, UINT32_MAX));
    }
}

template<class TC>
bool TTShaper<TC>::isTransmissionAllowed(inet::EtherFrame *message)
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
    sendTime += SimTime(
            (INTERFRAME_GAP_BITS + ((PREAMBLE_BYTES + SFD_BYTES) * 8)) / TC::outChannel->getNominalDatarate());
    uint64_t sendTicks = static_cast<uint64_t>(ceil((sendTime.dbl() / getOscillator()->par("tick").doubleValue())));
    sendTicks += this->safetyMargin;
    uint64_t startTicks = ttBuffers.begin()->first;

    if ((getTimer()->getTotalTicks() + sendTicks) >= startTicks)
    {
        EV_DETAIL << "transmission not allowed! Send time would be " << sendTime.dbl() << "s from "
                << getTimer()->getTotalTicks() << "ticks to " << getTimer()->getTotalTicks() + sendTicks
                << "ticks including safety margin tt_window starts at: " << startTicks << "ticks" << endl;
        return false;
    }
    EV_TRACE << "transmission allowed! Send time is " << sendTime.dbl() << "s from " << getTimer()->getTotalTicks()
            << "ticks to " << getTimer()->getTotalTicks() + sendTicks
            << "ticks including safety margin next tt_window starts at: " << startTicks << "ticks" << endl;
    return true;
}

}

#endif

