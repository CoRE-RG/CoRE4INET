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

#ifndef __CORE4INET_TASK_H_
#define __CORE4INET_TASK_H_

#include <stddef.h>

namespace CoRE4INET {

typedef void(*cbFunc)(void *);

//This disables the padding warning for this class!
#pragma GCC diagnostic ignored "-Wpadded"

/**
 * @brief Class representing a Task.
 *
 * The class stores a function pointer and args and invokes the function periodically.
 *
 * @todo Minor: This may be merged with the Callback class in a joined superclass. The
 * code seems identical.
 *
 * @sa ApplicationBase
 *
 *  @author Till Steinbach
 */
class Task
{
    protected:
        /**
         * @brief Function pointer of the task.
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
        Task();

        /**
         * @brief Setter for the function pointer.
         *
         * @param functionPointer the funtion pointer to be invoked in the task
         */
        void setFunctionPointer(void (*functionPointer)(void*)){
            fn=functionPointer;
        }

        /**
         * @brief Getter for the function pointer.
         *
         * @return the funtion pointer that is invoked in the task
         */
        cbFunc getFunctionPointer(){
            return fn;
        }

        /**
         * @brief Setter for the function args.
         *
         * @param functionArg the funtion arg to be used in the task
         */
        void setFunctionArg(void *functionArg){
            arg=functionArg;
            argSet=true;
        }

        /**
         * @brief Getter for the function args.
         *
         * @return the funtion arg used in the task
         */
        void* getFunctionArg(){
            return arg;
        }

        /**
         * @brief execution of the task.
         *
         * If method is called the stored function pointer is invoked.
         */
        void executeTask(){
            fn(arg);
        }
};

/**
 * @brief Class representing a Task especially for API.
 *
 * @sa Task
 */
class APITask : public Task
{
};

}

#endif /* __CORE4INET_TASK_H_ */
