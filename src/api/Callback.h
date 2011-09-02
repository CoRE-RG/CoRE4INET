/*
 * Callback.h
 *
 *  Created on: Aug 24, 2011
 *      Author: tillsteinbach
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

#include "tte_api.h"
#include "Buffer.h"
#include "TTBuffer.h"
#include "RCBuffer.h"

namespace TTEthernetModel {

typedef void(*cbFunc)(void *);

class Callback
{
    protected:
        void (*fn)(void *);
        void *arg;
        bool argSet;
        Buffer *buffer;
    public:
        Callback(Buffer *buffer){
            argSet=false;
            this->buffer=buffer;
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

        virtual void executeCallback(){
            fn(arg);
        }
};

class APICallback: public Callback
{
    public:
        APICallback(Buffer *buffer) : Callback(buffer){
        }

        virtual void executeCallback();
};

}

#endif /* CALLBACK_H_ */
