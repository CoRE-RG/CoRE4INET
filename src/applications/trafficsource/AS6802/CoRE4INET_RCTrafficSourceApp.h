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

#ifndef __CORE4INET_RCTRAFFICSOURCEAPP_H_
#define __CORE4INET_RCTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "CoRE4INET_CTTrafficSourceAppBase.h"
#include "CoRE4INET_Timed.h"

namespace CoRE4INET {

/**
 * @brief Traffic-Generator for RC-Traffic.
 *
 *
 * @sa ApplicationBase
 * @ingroup Applications AS6802
 *
 * @author Till Steinbach
 */
class RCTrafficSourceApp : public virtual CTTrafficSourceAppBase, public virtual Timed
{
        /**
         * @brief Caches interval parameter
         */
        double interval;

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
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
    public:
        /**
         * @brief constructor for RCTrafficSourceApp
         */
        RCTrafficSourceApp();

};

} //namespace

#endif
