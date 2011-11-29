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

/**
 * @brief Class representing a Callback.
 *
 * The class stores a funtion pointer and args and executes the function on demand.
 *
 * @todo This may be merged with the Task class in a joined superclass. The
 * code seems identical.
 *
 * @sa TTEApplicationBase
 */
class Callback
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

        /**
         * @brief Pointer to the Buffer that issues the Callback.
         */
        Buffer *buffer;
    public:
        /**
         * @brief Constructor
         */
        Callback(Buffer *buffer){
            argSet=false;
            this->buffer=buffer;
        }

        /**
         * @brief Setter for the function pointer.
         *
         * @param functionPointer the funtion pointer to be invoked in the callback
         */
        virtual void setFunctionPointer(void (*functionPointer)(void*)){
            fn=functionPointer;
        }

        /**
         * @brief Getter for the function pointer.
         *
         * @return the funtion pointer that is invoked in the callback
         */
        virtual cbFunc getFunctionPointer(){
            return fn;
        }

        /**
         * @brief Setter for the function args.
         *
         * @param setFunctionArg the funtion arg to be used in the callback
         */
        virtual void setFunctionArg(void *setFunctionArg){
            arg=setFunctionArg;
            argSet=true;
        }


        /**
         * @brief Getter for the function args.
         *
         * @return the funtion arg used in the callback
         */
        virtual void* getFunctionArg(){
            return arg;
        }

        /**
         * @brief execution of the callback.
         *
         * If method is called the stored function pointer is invoked.
         */
        virtual void executeCallback(){
            fn(arg);
        }
};


/**
 * @brief Class representing a Callback especially for API callbacks.
 *
 * @sa Callback
 */
class APICallback: public Callback
{
    public:
        APICallback(Buffer *buffer) : Callback(buffer){
        }

        virtual void executeCallback();
};

}

#endif /* CALLBACK_H_ */
