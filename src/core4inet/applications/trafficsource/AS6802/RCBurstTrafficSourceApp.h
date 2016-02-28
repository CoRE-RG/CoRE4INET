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

#ifndef RCBURSTTRAFFICSOURCEAPP_H_
#define RCBURSTTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "./CTTrafficSourceAppBase.h"
#include "core4inet/utilities/classes/Timed.h"

namespace CoRE4INET {

/**
 * @brief Traffic-Generator for RC-Traffic with burst behavior.
 *
 *
 * @sa ApplicationBase
 * @ingroup Applications AS6802
 *
 * @author Philipp Meyer
 */
class RCBurstTrafficSourceApp : public virtual CoRE4INET::CTTrafficSourceAppBase, public virtual CoRE4INET::Timed
{
    private:
        /**
         * @brief Caches interval parameter
         */
        double interval;
        /**
         * @brief Caches burstInterval parameter
         */
        double burstInterval;
        /**
         * @brief Counts the number of frames that are sent until now
         */
        unsigned int framesBurstedCnt;

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
         * @brief constructor for RCBurstTrafficSourceApp
         */
        RCBurstTrafficSourceApp();
};

} //namespace

#endif /* RCBURSTTRAFFICSOURCEAPP_H_ */
