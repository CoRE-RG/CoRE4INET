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

#ifndef CORE4INET_APPLICATIONBASE_H_
#define CORE4INET_APPLICATIONBASE_H_

//Std
#include <list>

//CoRE4INET
#include "core4inet/base/CoRE4INET_Defs.h"

namespace CoRE4INET {

using namespace omnetpp;

class BGBuffer;

/**
 * @brief Base class for a Ethernet-Application.
 *
 * Containes the mapping to Buffers and the ability to execute Callbacks
 *
 * @sa Buffer, Callback
 *
 * @ingroup Applications
 *
 * @author Till Steinbach
 */
class ApplicationBase : public virtual cSimpleModule
{
    protected:
        /**
         * @brief List of Buffers for best-effor messages
         */
        std::list<BGBuffer*> bgbuffers;

    public:
        virtual ~ApplicationBase() override = 0;

    protected:
        /**
         * @brief Initialization of the module.
         */
        virtual void initialize() override;

        /**
         * @brief executes the given Callback in the context of the Application
         *
         * @param cb The Callback to execute
         */
        //virtual void executeCallback(Callback *cb);
        /**
         * @brief resets the bag on incoming RC-Frames (on RCin)
         *
         * This method should be called from subclasses unless the module
         * resets the bag on its own.
         *
         * @param msg Parameter must be forwarded from subclass
         */
        virtual void handleMessage(cMessage *msg) override;

        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         *
         * @throws cRuntimeError When buffer module and application module do not have the same parent module
         */
        virtual void handleParameterChange(const char* parname) override;
};

} //namespace

#endif
