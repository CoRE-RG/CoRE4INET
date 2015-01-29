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

#ifndef __CORE4INET_CALLBACK_H_
#define __CORE4INET_CALLBACK_H_

//CoRE4INET
#include "CoRE4INET_Buffer.h"

namespace CoRE4INET {

typedef void (*cbFunc)(void *);

//This disables the padding warning for this class!
#pragma GCC diagnostic ignored "-Wpadded"

/**
 * @brief Class representing a Callback.
 *
 * The class stores a funtion pointer and args and executes the function on demand.
 *
 * @todo Minor: This may be merged with the Task class in a joined superclass. The
 * code seems identical.
 *
 * @sa ApplicationBase
 *
 * @author Till Steinbach
 */
class Callback : public cListener
{
    protected:
        /**
         * @brief Function pointer of the callback.
         */
        void (*fn)(void *);

        /**
         * @brief Pointer to the function args.
         */
        void *arg;
        /**
         * @brief Boolean indicating whether args were set.
         */
        bool argSet;

    public:
        /**
         * @brief Constructor
         */
        Callback(Buffer *buffer, simsignal_t signal);

        /**
         * @brief Setter for the function pointer.
         *
         * @param functionPointer the funtion pointer to be invoked in the callback
         */
        void setFunctionPointer(void (*functionPointer)(void*));

        /**
         * @brief Getter for the function pointer.
         *
         * @return the funtion pointer that is invoked in the callback
         */
        cbFunc getFunctionPointer()
        {
            return fn;
        }

        /**
         * @brief Setter for the function args.
         *
         * @param functionArg the funtion arg to be used in the callback
         */
        void setFunctionArg(void *functionArg)
        {
            arg = functionArg;
            argSet = true;
        }

        /**
         * @brief Getter for the function args.
         *
         * @return the funtion arg used in the callback
         */
        void* getFunctionArg()
        {
            return arg;
        }

        /**
         * @brief execution of the callback.
         *
         * If method is called the stored function pointer is invoked.
         */
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
};

}

#endif /* __CORE4INET_CALLBACK_H_ */
