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

#ifndef __CORE4INET_TTTRAFFICSOURCEAPP_H_
#define __CORE4INET_TTTRAFFICSOURCEAPP_H_

//OMNeT++
#include "clistener.h"
//CoRE4INET
#include "CoRE4INET_CTTrafficSourceAppBase.h"
#include "CoRE4INET_Scheduled.h"

namespace CoRE4INET {

/**
 * @brief Traffic-Generator for TT-Traffic.
 *
 *
 * @sa ApplicationBase
 * @ingroup Applications AS6802
 *
 * @author Till Steinbach
 */
class TTTrafficSourceApp : public virtual CTTrafficSourceAppBase, public virtual Scheduled, public virtual cListener
{
    private:
        /**
         * @brief Caches modulo parameter
         */
        unsigned int modulo;

        /**
         * @brief frame is only sent every modulo cycle
         */
        unsigned int moduloCycle;

        /**
         * @brief true when node is synchronized (Frames will be only sent when node runs synchronous)
         */
        bool synchronized;

    protected:
        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize() override;

        /**
         * @brief Handles message generation
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @ Receives signal from sync module
         *
         * @param source signal emitting  component
         * @param signalID ID of the signal
         * @param obj representation of the signal
         */
        virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;

    public:
        TTTrafficSourceApp();
};

} //namespace

#endif
