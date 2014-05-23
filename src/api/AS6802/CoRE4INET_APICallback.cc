/*
 * Callback.cc
 *
 *  Created on: Sep 2, 2011
 *      Author: tillsteinbach
 */

#include <stdint.h>

#include "CoRE4INET_APICallback.h"

#include "tte_api.h"
#include "CoRE4INET_TTBuffer.h"
#include "CoRE4INET_RCBuffer.h"
#include "CoRE4INET_TTEAPIApplicationBase.h"

namespace CoRE4INET {

 void APICallback::receiveSignal(cComponent *src, simsignal_t id, cObject *obj){
    if(argSet){
        fn(arg);
    }
    else{
        tte_buffer_t buf;
        if(dynamic_cast<TTBuffer*>(src) != NULL){
            buf.traffic_type= TTE_TT_TRAFFIC;
        }
        else if(dynamic_cast<RCBuffer*>(src) != NULL){
            buf.traffic_type= TTE_CT_TRAFFIC;
        }
        else{
            buf.traffic_type= TTE_BG_TRAFFIC;
        }
        buf.channel=0;
        buf.ct_id=(uint16_t)src->par("ct_id").longValue();
        buf.shared=0;

        TTEAPIPriv *priv = new TTEAPIPriv();
        buf.priv = priv;
        priv->buffer = dynamic_cast<Buffer*>(src);
        fn((void*)&buf);
        if(buf.priv){
            delete priv;
            buf.priv=0;
        }
    }
}

}
