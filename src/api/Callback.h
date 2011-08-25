/*
 * Callback.h
 *
 *  Created on: Aug 24, 2011
 *      Author: tillsteinbach
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

namespace TTEthernetModel {


class Callback
{
    public:
        void (*fn)(void *);
        void *arg;

        virtual void executeCallback(){
            fn(arg);
        }
};

}

#endif /* CALLBACK_H_ */
