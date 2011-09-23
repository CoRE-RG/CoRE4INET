/*
 * Callback.cc
 *
 *  Created on: Sep 2, 2011
 *      Author: tillsteinbach
 */

#include <stdint.h>
#include "tte_api.h"
#include "TTBuffer.h"
#include "RCBuffer.h"
#include "Callback.h"
#include "TTEAPIApplicationBase.h"

namespace TTEthernetModel {

 void APICallback::executeCallback(){
    if(argSet){
        fn(arg);
    }
    else{
        tte_buffer_t buf;
        if(dynamic_cast<TTBuffer*>(buffer) != NULL){
            buf.traffic_type= TTE_TT_TRAFFIC;
        }
        else if(dynamic_cast<RCBuffer*>(buffer) != NULL){
            buf.traffic_type= TTE_CT_TRAFFIC;
        }
        else{
            buf.traffic_type= TTE_BG_TRAFFIC;
        }
        buf.channel=0;
        buf.ct_id=buffer->par("ct_id").longValue();
        buf.shared=0;

        TTEAPIPriv *priv = new TTEAPIPriv();
        buf.priv = priv;
        priv->buffer = buffer;
        fn((void*)&buf);
        if(buf.priv){
            delete priv;
            buf.priv=0;
        }
    }
}

}
