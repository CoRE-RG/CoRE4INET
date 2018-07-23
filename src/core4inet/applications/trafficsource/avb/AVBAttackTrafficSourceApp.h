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

#ifndef __CORE4INET_AVBATTACKTRAFFICSOURCEAPP_H_
#define __CORE4INET_AVBATTACKTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "core4inet/applications/trafficsource/avb/AVBTrafficSourceApp.h"

namespace CoRE4INET {

/**
 * @brief Class representing a AVBAttackTrafficSourceApp. Implements attack pattern stimuli. Also supports valid behavior.
 *
 * @author Philipp Meyer
 */
class AVBAttackTrafficSourceApp : public virtual AVBTrafficSourceApp
{
    private:
        /**
         * @brief Specified attack pattern
         */
        unsigned int attackPattern;
        /**
         * @brief Spam size
         */
        unsigned int spamSize;
        /**
         * @brief Spam wait interval
         */
        simtime_t spamWaitInterval;
        unsigned int counter;

    protected:
        /**
         * @brief Initialization of the module. Sends activator message
         */
        virtual void initialize() override;
        /**
         * @brief Sends an AVBFrame
         */
        virtual void sendAVBFrame() override;
        /**
         * @brief Schedule next send interval
         */
        virtual void scheduleInterval() override;
        /**
         * @brief Indicates a parameter has changed.
         *
         * @param parname Name of the changed parameter or nullptr if multiple parameter changed.
         */
        virtual void handleParameterChange(const char* parname) override;
};

} //namespace

#endif
