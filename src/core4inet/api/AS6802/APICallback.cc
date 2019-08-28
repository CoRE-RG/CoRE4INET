/*
 * Callback.cc
 *
 *  Created on: Sep 2, 2011
 *      Author: tillsteinbach
 */

//#include <stdint.h>

#include "core4inet/api/AS6802/APICallback.h"

//TTE-API
#include "tte_api.h"
//CoRE4INET
#include "core4inet/buffer/AS6802/TTBuffer.h"
#include "core4inet/buffer/AS6802/RCBuffer.h"
#include "core4inet/applications/api/AS6802/TTEAPIApplicationBase.h"

namespace CoRE4INET {

void APICallback::receiveSignal(cComponent *src, __attribute__((unused)) simsignal_t id,
        __attribute__((unused)) cObject *obj, __attribute__((unused)) cObject *details)
{
    if (argSet)
    {
        fn(arg);
    }
    else
    {
        tte_buffer_t buf;
        if (dynamic_cast<TTBuffer*>(src) != nullptr)
        {
            buf.traffic_type = TTE_TT_TRAFFIC;
        }
        else if (dynamic_cast<RCBuffer*>(src) != nullptr)
        {
            buf.traffic_type = TTE_CT_TRAFFIC;
        }
        else
        {
            buf.traffic_type = TTE_BG_TRAFFIC;
        }
        buf.channel = 0;
        buf.ct_id = src->par("ct_id");
        buf.shared = 0;

        TTEAPIPriv *priv = new TTEAPIPriv();
        buf.priv = priv;
        priv->buffer = dynamic_cast<Buffer*>(src);
        fn(static_cast<void*>(&buf));
        if (buf.priv)
        {
            delete priv;
            buf.priv = 0;
        }
    }
}

}
