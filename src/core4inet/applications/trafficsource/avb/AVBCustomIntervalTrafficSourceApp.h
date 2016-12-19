//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CORE4INET_AVBCZSTOMINTERVALTRAFFICSOURCEAPP_H_
#define CORE4INET_AVBCZSTOMINTERVALTRAFFICSOURCEAPP_H_

//CoRE4INET
#include "core4inet/applications/trafficsource/avb/AVBTrafficSourceApp.h"

namespace CoRE4INET {

/**
 * @brief Simple AVB Traffic Source-Application.
 *
 *
 * @sa TTEApplicationBase
 * @ingroup Applications
 *
 * @author Philipp Meyer, Till Steinbach
 *
 */

class AVBCustomIntervalTrafficSourceApp : public virtual AVBTrafficSourceApp
{
    private:
        simtime_t interval;
    public:
        AVBCustomIntervalTrafficSourceApp();
    protected:
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

} /* namespace CoRE4INET */
#endif /* CORE4INET_AVBTRAFFICSOURCEAPP_H_ */
