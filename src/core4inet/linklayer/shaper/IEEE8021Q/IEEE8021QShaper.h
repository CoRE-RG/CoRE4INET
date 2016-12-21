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

#ifndef CORE4INET_IEEE8021QShaper_H
#define CORE4INET_IEEE8021QShaper_H

#include <algorithm>    // std::sort

//CoRE4INET
#include "core4inet/utilities/classes/Timed.h"
#include "core4inet/utilities/HelperFunctions.h"
#include "core4inet/utilities/ConfigFunctions.h"
#include "core4inet/base/CoRE4INET_Defs.h"
//Auto-generated Messages
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"

namespace CoRE4INET {

/**
 * @brief A Shaper for IEEE802.1Q-tagged Messages.
 *
 * @ingroup IEEE8021Q
 *
 * @author Till Steinbach, Philipp Meyer
 */
template<class TC>
class IEEE8021QShaper : public TC, public virtual Timed
{
        using Timed::initialize;

    public:
        /**
         * @brief Constructor
         */
        IEEE8021QShaper();

        /**
         * @brief Destructor
         */
        virtual ~IEEE8021QShaper();

    private:
        /**
         * @brief Dedicated queue for each priority of Q-tagged messages
         */
        std::vector<cQueue> qQueue;
        /**
         * @brief caches queue size in bytes
         */
        std::vector<size_t> qQueueSize;

        /**
         * @brief Untagged VLAN.
         * Untagged incoming frames get tagged with this VLAN. Outgoing frames with this VLAN get untagged.
         */
        uint16_t untaggedVID;
        /**
         * @brief Tagged VLANs.
         * Only outgoing frames with one of the VLANs in this list are transmitted. Default is "0" to allow for untagged frames
         */
        std::vector<int> taggedVIDs;

        /**
         * @brief Default priority.
         * Frames without Q-tag will be treated with this priority (must be larger or equal 0 and smaller or equal 7)
         */
        uint8_t defaultPriority;
    protected:
        /**
         * @brief Signal that is emitted when the queue length of Q-tagged messages changes.
         */
        std::vector<simsignal_t> qQueueLengthSignals;
        /**
         * @brief Signal that is emitted when the queue size of rate-constrained messages changes.
         */
        std::vector<simsignal_t> qQueueSizeSignals;

    protected:
        /**
         * Initializes the module
         *
         * @param stage The stages. Module initializes when stage==0
         */
        virtual void initialize(int stage) override;

        /**
         * @brief Returns the number of initialization stages this module needs.
         *
         * @return returns 1 or more depending on inheritance
         */
        virtual int numInitStages() const override;

        /**
         * @brief Forwards the messages from the different buffers and LLC
         * according to the specification for RCMessages.
         *
         * Rate-constrained messages are send immediately, lower priority frames are queued
         * as long as there are rate-constrained messages waiting.
         * If the mac layer is idle, messages are picked from the queues according
         * to the priorities, using the template class.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Queues messages in the correct queue
         *
         * Rate-constrained messages are queued in this module, other messages are forwarded to the
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
};

template<class TC>
IEEE8021QShaper<TC>::IEEE8021QShaper()
{
    untaggedVID = 0;
}

template<class TC>
IEEE8021QShaper<TC>::~IEEE8021QShaper()
{
}

template<class TC>
void IEEE8021QShaper<TC>::initialize(int stage)
{
    TC::initialize(stage);
    if (stage == 0)
    {
        Timed::initialize();

        for (unsigned int i = 0; i < 8; i++)
        {
            char strBuf[32];
            cQueue queue;
            snprintf(strBuf, 32, "Q Priority %d Messages", i);
            queue.setName(strBuf);
            qQueue.push_back(queue);
            qQueueSize.push_back(0);

            snprintf(strBuf, 32, "q%dQueueLength", i);
            simsignal_t signal = registerSignal(strBuf);

            cProperty *statisticTemplate = getProperties()->get("statisticTemplate", "qQueueLength");
            getEnvir()->addResultRecorders(this, signal, strBuf, statisticTemplate);

            qQueueLengthSignals.push_back(signal);
            //Send initial signal to create statistic
            cComponent::emit(signal, static_cast<unsigned long>(queue.getLength()));

            snprintf(strBuf, 32, "q%dQueueSize", i);
            signal = registerSignal(strBuf);

            statisticTemplate = getProperties()->get("statisticTemplate", "qQueueSize");
            getEnvir()->addResultRecorders(this, signal, strBuf, statisticTemplate);

            qQueueSizeSignals.push_back(signal);
            //Send initial signal to create statistic
            cComponent::emit(signal, static_cast<unsigned long>(0));
        }
    }
}

template<class TC>
int IEEE8021QShaper<TC>::numInitStages() const
{
    if (TC::numInitStages() > 1)
    {
        return TC::numInitStages();
    }
    else
    {
        return 1;
    }
}

template<class TC>
void IEEE8021QShaper<TC>::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        if (EthernetIIFrameWithQTag* qframe = dynamic_cast<EthernetIIFrameWithQTag*>(msg))
        {
            //VLAN untag if requested
            if (this->untaggedVID && this->untaggedVID == qframe->getVID())
            {
                qframe->setVID(0);
            }
            //VLAN check if port is tagged with VLAN
            bool found = false;
            for (std::vector<int>::iterator vid = this->taggedVIDs.begin(); vid != this->taggedVIDs.end(); ++vid)
            {
                //Shortcut due to sorted vector
                if ((*vid) > qframe->getVID())
                {
                    break;
                }
                if ((*vid) == qframe->getVID())
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                delete qframe;
                return;
            }
        }

        if (TC::getNumPendingRequests())
        {
            TC::framesRequested--;
            cSimpleModule::send(msg, cModule::gateBaseId("out"));
        }
        else
        {
            enqueueMessage(msg);
        }
    }
    else
    {
        if (TC::getNumPendingRequests())
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
void IEEE8021QShaper<TC>::enqueueMessage(cMessage *msg)
{
    if (msg->arrivedOn("in"))
    {
        uint8_t priority = this->defaultPriority;
        if (EthernetIIFrameWithQTag* qframe = dynamic_cast<EthernetIIFrameWithQTag*>(msg))
        {
            //VLAN untag if requested
            if (this->untaggedVID && this->untaggedVID == qframe->getVID())
            {
                qframe->setVID(0);
            }
            //VLAN check if port is tagged with VLAN
            bool found = false;
            for (std::vector<int>::iterator vid = this->taggedVIDs.begin(); vid != this->taggedVIDs.end(); ++vid)
            {
                //Shortcut due to sorted vector
                if ((*vid) > qframe->getVID())
                {
                    break;
                }
                if ((*vid) == qframe->getVID())
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                delete qframe;
                return;
            }

            priority = qframe->getPcp();
        }
        if (priority >= 0 && static_cast<size_t>(priority) <= MAX_Q_PRIORITY)
        {
            qQueue[static_cast<size_t>(priority)].insert(msg);
            cComponent::emit(qQueueLengthSignals[static_cast<size_t>(priority)],
                    static_cast<unsigned long>(qQueue[static_cast<size_t>(priority)].getLength()));
            qQueueSize[static_cast<size_t>(priority)]+=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(msg)->getByteLength());
            cComponent::emit(qQueueSizeSignals[static_cast<size_t>(priority)], static_cast<unsigned long>(qQueueSize[static_cast<size_t>(priority)]));
            TC::notifyListeners();
        }
        else
        {
            qQueue[this->defaultPriority].insert(msg);
            TC::notifyListeners();
            EV_WARN << "Priority of message " << msg->getFullName()
                    << " missing or not within range, using default priority " << this->defaultPriority << "!" <<endl;
        }
    }
    else
    {
        TC::enqueueMessage(msg);
    }
}

template<class TC>
void IEEE8021QShaper<TC>::requestPacket()
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

template<class TC>
cMessage* IEEE8021QShaper<TC>::pop()
{
    Enter_Method("pop()");

    for (size_t i = 8; i > 0; i--)
    {
        if (!qQueue[i - 1].isEmpty())
        {
            inet::EtherFrame *message = static_cast<inet::EtherFrame*>(qQueue[i - 1].pop());
            cComponent::emit(qQueueLengthSignals[i - 1], static_cast<unsigned long>(qQueue[i - 1].getLength()));
            qQueueSize[i - 1]-=static_cast<size_t>(check_and_cast<inet::EtherFrame*>(message)->getByteLength());
            cComponent::emit(qQueueSizeSignals[i - 1], static_cast<unsigned long>(qQueueSize[i - 1]));
            return message;
        }
    }
    return TC::pop();
}

template<class TC>
cMessage* IEEE8021QShaper<TC>::front()
{
    Enter_Method("front()");

    for (size_t i = 8; i > 0; i--)
    {
        if (!qQueue[i - 1].isEmpty())
        {
            inet::EtherFrame *message = static_cast<inet::EtherFrame*>(qQueue[i - 1].front());
            return message;
        }
    }
    return TC::front();
}

template<class TC>
bool IEEE8021QShaper<TC>::isEmpty()
{
    bool empty = true;
    for (unsigned int i = 0; i < 8; i++)
    {
        empty &= qQueue[i].isEmpty();
    }
    empty &= TC::isEmpty();
    return empty;
}

template<class TC>
void IEEE8021QShaper<TC>::clear()
{
    TC::clear();
    for (unsigned int i = 0; i < 8; i++)
    {
        qQueue[i].clear();
    }
}

template<class TC>
void IEEE8021QShaper<TC>::handleParameterChange(const char* parname)
{
    TC::handleParameterChange(parname);

    if (!parname || !strcmp(parname, "untaggedVID"))
    {
        this->untaggedVID = static_cast<uint16_t>(parameterULongCheckRange(par("untaggedVID"), 0, MAX_VLAN_NUMBER));
    }
    if (!parname || !strcmp(parname, "taggedVIDs"))
    {
        taggedVIDs = cStringTokenizer(par("taggedVIDs"), ",").asIntVector();
        std::sort(taggedVIDs.begin(), taggedVIDs.end());
    }
    if (!parname || !strcmp(parname, "defaultPriority"))
    {
        this->defaultPriority = static_cast<uint8_t>(parameterULongCheckRange(par("defaultPriority"), 0, MAX_Q_PRIORITY));
    }
}

}

#endif

