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

#ifndef __CORE4INET_TTEAPITESTAPPLICATION_H_
#define __CORE4INET_TTEAPITESTAPPLICATION_H_

//CoRE4INET
#include "CoRE4INET_TTEAPIApplicationBase.h"

namespace CoRE4INET {

/**
 * @brief Simple Test-Application based on the TTEthernet-API.
 *
 * Contains main() and callback
 *
 * @sa TTEAPITestApplication, ApplicationBase
 * @ingroup Applications AS6802
 *
 * @author Till Steinbach
 */
class TTEAPITestApplication : public TTEAPIApplicationBase
{
    protected:
        /**
         * @brief Implementation of startApplication() that starts the main()
         */
        virtual void startApplication();
};

} //namespace

#endif
