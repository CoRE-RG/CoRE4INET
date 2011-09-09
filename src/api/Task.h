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

#ifndef TASK_H_
#define TASK_H_

#include <cobject.h>

namespace TTEthernetModel {

typedef void(*cbFunc)(void *);

class Task
{
    protected:
        void (*fn)(void *);
        void *arg;
        bool argSet;
    public:
        Task(){
            argSet=false;
        }

        virtual void setFunctionPointer(void (*functionPointer)(void*)){
            fn=functionPointer;
        }

        virtual cbFunc getFunctionPointer(){
            return fn;
        }

        virtual void setFunctionArg(void *setFunctionArg){
            arg=setFunctionArg;
            argSet=true;
        }

        virtual void* getFunctionArg(){
            return arg;
        }

        virtual void executeTask(){
            fn(arg);
        }
};

class APITask : public Task
{
};

}

#endif /* TASK_H_ */
