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

#ifndef __CORE4INET_BASECONFIGURATIONMANAGER_H_
#define __CORE4INET_BASECONFIGURATIONMANAGER_H_

//OMNeT++
#include "csimplemodule.h"

namespace CoRE4INET {

/**
 * @brief Dummy module for a ConfigurationManager that has no configuration.
 * If you use this BaseConfigurationManager you must configure the node manually
 *
 * The module is deleted after simulation start
 *
 * @author Till Steinbach
 */
class BaseConfigurationManager : public virtual cSimpleModule
{
    protected:
        /**
         * @brief Is called in initialization phase. The module creates a message for self destruction
         */
        virtual void initialize() override;
        /**
         * @brief Destroys the module after reception of a message
         */
        virtual void handleMessage(cMessage *msg) override;
};

} //namespace

#endif
