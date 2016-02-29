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

#ifndef CORE4INET_APICALLBACK_H_
#define CORE4INET_APICALLBACK_H_

//CoRE4INET
#include "core4inet/api/base/Callback.h"
#include "core4inet/buffer/base/Buffer.h"

namespace CoRE4INET {

typedef void(*cbFunc)(void *);

//This disables the padding warning for this class!
#pragma GCC diagnostic ignored "-Wpadded"

/**
 * @brief Class representing a Callback especially for API callbacks.
 *
 * @sa Callback
 */
class APICallback: public Callback
{
    public:
        /**
         * @brief Constructor
         */
        APICallback(Buffer *buffer, simsignal_t signal) : Callback(buffer, signal){
        }

        /**
         * @brief execution of the callback.
         *
         * If method is called the stored function pointer is invoked.
         */
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
};

}

#endif /* CORE4INET_CALLBACK_H_ */
