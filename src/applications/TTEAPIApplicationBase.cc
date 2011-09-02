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

#include "TTEAPIApplicationBase.h"
#include "EtherMACFullDuplex.h"
#include "Incoming.h"
#include "TTIncoming.h"
#include "RCIncoming.h"
#include "TTBuffer.h"
#include "RCBuffer.h"
#include "APIPayload_m.h"

namespace TTEthernetModel {

Define_Module(TTEAPIApplicationBase);

void TTEAPIApplicationBase::initialize()
{
    scheduleAt(simTime(), new cMessage("Start Application", START_APPLICATION));
}

void TTEAPIApplicationBase::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage() && msg->getKind() == START_APPLICATION){
        startApplication();
        delete msg;
    }
}

void TTEAPIApplicationBase::startApplication(){
    ev << "TTEAPIApplicationBase::startApplication() not implemented" << endl;
    throw;
}

int32_t TTEAPIApplicationBase::tte_get_ct_output_buf(const uint8_t ctrl_id,
                                                     const uint16_t ct_id,
                                                     tte_buffer_t * const buf){
    std::map<uint16, std::list<Buffer *> >::iterator bufferList = buffers.find(ct_id);
    if (bufferList != buffers.end())
    {
        //Currently we use only the first entry!
        std::list<Buffer*>::iterator buffer = bufferList->second.begin();

        buf->ctrl_id=0;
        buf->direction= TTE_DIR_OUTPUT;
        if(dynamic_cast<TTBuffer*>(*buffer) != NULL){
            buf->traffic_type= TTE_TT_TRAFFIC;
        }
        else if(dynamic_cast<RCBuffer*>(*buffer) != NULL){
            buf->traffic_type= TTE_CT_TRAFFIC;
        }
        else{
            buf->traffic_type= TTE_BG_TRAFFIC;
        }
        buf->channel=0;
        buf->ct_id=ct_id;
        buf->shared=0;

        TTEAPIOutgoingPriv *priv = new TTEAPIOutgoingPriv();
        priv->buffer = (*buffer);

        buf->priv=priv;
        return ETT_SUCCESS;

    }
    else
    {
        return ETT_INVMSGID;
    }
}

int32_t TTEAPIApplicationBase::tte_get_ct_input_buf(const uint8_t ctrl_id,
                                                     const uint16_t ct_id,
                                                     tte_buffer_t * const buf){
    std::map<uint16, std::list<Buffer *> >::iterator bufferList = buffers.find(ct_id);
    if (bufferList != buffers.end())
    {
        //Currently we use only the first entry!
        std::list<Buffer*>::iterator buffer = bufferList->second.begin();

        buf->ctrl_id=0;
        buf->direction= TTE_DIR_INPUT;
        if(dynamic_cast<TTBuffer*>(*buffer) != NULL){
            buf->traffic_type= TTE_TT_TRAFFIC;
        }
        else if(dynamic_cast<RCBuffer*>(*buffer) != NULL){
            buf->traffic_type= TTE_CT_TRAFFIC;
        }
        else{
            buf->traffic_type= TTE_BG_TRAFFIC;
        }
        buf->channel=0;
        buf->ct_id=ct_id;
        buf->shared=0;

        TTEAPIPriv *priv = new TTEAPIPriv();
        priv->buffer = (*buffer);

        buf->priv=priv;
        return ETT_SUCCESS;

    }
    else
    {
        return ETT_INVMSGID;
    }
}

int32_t TTEAPIApplicationBase::tte_get_var(const uint8_t ctrl_id,
                                                            const tte_var_id_t var_id,
                                                            const uint32_t var_size,
                                                            void * const value){
    switch(var_id){
        case TTE_VAR_LINK_STATUS:{
            cModule *phy = getParentModule()->getSubmodule("phy", 0);
            if(phy){
                for(int i=0;i<phy->getVectorSize();i++){
                    EtherMACFullDuplex *mac = (EtherMACFullDuplex*)getParentModule()->getSubmodule("phy", i)->getSubmodule("mac");
                    if(mac->gate("phys")->isConnected())
                        *((uint8_t*)value) = *((uint8_t*)value)<<1 | 1;
                    else
                        *((uint8_t*)value) = *((uint8_t*)value)<<1;
                }
            }
            else{
                *((uint8_t*)value) = 0;
                return ETT_NULLPTR;
            }
            break;
        }
        case TTE_VAR_CTRL_STATUS:{
            *((uint32_t*)value) = TTE_STAT_CONFIGURED | TTE_STAT_RUNNING;
            break;
        }
        case TTE_VAR_CTRL_COUNT:{
            *((uint8_t*)value) = 1;
            break;
        }
        case TTE_VAR_CHANNEL_COUNT:{
            cModule *phy = getParentModule()->getSubmodule("phy", 0);
            if(phy){
                *((uint8_t*)value) = phy->getVectorSize();
            }
            else{
                *((uint8_t*)value) = 0;
                return ETT_NULLPTR;
            }
            break;
        }
        case TTE_VAR_TIME_RESOLUTION:{
            cModule *scheduler = getParentModule()->getSubmodule("tteScheduler", -1);
            if(scheduler){
                *((tte_time_t*)value) = scheduler->par("tick").doubleValue();
            }
            else{
                *((tte_time_t*)value) = 0;
                return ETT_NULLPTR;
            }
            break;
        }
        case TTE_VAR_API_VERSION:{
            *((uint32_t*)value) = TTE_API_VER;
        }
        case TTE_VAR_THREAD_SAFE:{
            //TODO: CHECK WHETHER IT IS POSSIBLE TO SET TO TRUE (1)
            *((uint8_t*)value) = 0;
            break;
        }
        case TTE_VAR_MAC_ADDRESS:{
            uint8_t *valueArr= (uint8_t *)value;
            cModule *phy = getParentModule()->getSubmodule("phy", 0);
            if(phy){
                EtherMACFullDuplex *mac = (EtherMACFullDuplex*)phy->getSubmodule("mac");
                MACAddress macAddress = mac->getMACAddress();
                //Change order
                valueArr[5] = macAddress.getAddressByte(0);
                valueArr[4] = macAddress.getAddressByte(1);
                valueArr[3] = macAddress.getAddressByte(2);
                valueArr[2] = macAddress.getAddressByte(3);
                valueArr[1] = macAddress.getAddressByte(4);
                valueArr[0] = macAddress.getAddressByte(5);
            }
            else{
                valueArr[0] = valueArr[1] = valueArr[2] = valueArr[3] = valueArr[4] = valueArr[5] = 0;
                return ETT_NULLPTR;
            }
            break;
        }
        default:
            return ETT_NOTSUPPORTED;
    }
    return ETT_SUCCESS;
}

int32_t TTEAPIApplicationBase::tte_open_output_buf(tte_buffer_t * const buf,
                                                   tte_frame_t * const frame){
    TTEAPIOutgoingPriv *priv = (TTEAPIOutgoingPriv*)buf->priv;

    //Now we create a frame that can be accessed later
    //TODO Divide TT and RC frames in separate types?
    std::stringstream frameNameStream;
    frameNameStream << "CT-ID: " << buf->ct_id;
    std::string frameName = frameNameStream.str();
    priv->frame = new CTFrame(frameName.c_str());
    priv->frame->setByteLength(ETHER_MAC_FRAME_BYTES);

    MACAddress dest;
    dest.setAddressByte(5, frame->eth_hdr.dst_mac[0]);
    dest.setAddressByte(4, frame->eth_hdr.dst_mac[1]);
    dest.setAddressByte(3, frame->eth_hdr.dst_mac[2]);
    dest.setAddressByte(2, frame->eth_hdr.dst_mac[3]);
    dest.setAddressByte(1, frame->eth_hdr.dst_mac[4]);
    dest.setAddressByte(0, frame->eth_hdr.dst_mac[5]);
    priv->frame->setDest(dest);
    MACAddress src;
    src.setAddressByte(5, frame->eth_hdr.src_mac[0]);
    src.setAddressByte(4, frame->eth_hdr.src_mac[1]);
    src.setAddressByte(3, frame->eth_hdr.src_mac[2]);
    src.setAddressByte(2, frame->eth_hdr.src_mac[3]);
    src.setAddressByte(1, frame->eth_hdr.src_mac[4]);
    src.setAddressByte(0, frame->eth_hdr.src_mac[5]);
    priv->frame->setSrc(src);

    APIPayload *payload = new APIPayload("TTEthernet API Payload");
    payload->setByteLength(frame->length);
    payload->setDataArraySize(frame->length);
    priv->frame->encapsulate(payload);

    frame->data = (uint8_t*)malloc(frame->length);
    priv->data = frame->data;
    return ETT_SUCCESS;
}


int32_t TTEAPIApplicationBase::tte_close_output_buf(tte_buffer_t * const buf){
    TTEAPIOutgoingPriv *priv = (TTEAPIOutgoingPriv *)buf->priv;
    //Copy frame data and free memory
    APIPayload *payload = (APIPayload*)priv->frame->getEncapsulatedPacket();
    for(unsigned int i=0;i<payload->getDataArraySize();i++){
        payload->setData(i, ((unsigned char *)priv->data)[i]);
    }
    free(priv->data);
    //Send to CTC
    if(priv->buffer)
        if(priv->buffer->gate("in"))
            if(priv->buffer->gate("in")->getPathStartGate())
                if((cModule *)priv->buffer->gate("in")->getPathStartGate()->getOwner())
                    if(((cModule *)priv->buffer->gate("in")->getPathStartGate()->getOwner())->gate("in"))
                        sendDirect(priv->frame, ((cModule *)priv->buffer->gate("in")->getPathStartGate()->getOwner())->gate("in"));
    //delete priv;
    return ETT_SUCCESS;
}

int32_t TTEAPIApplicationBase::tte_set_buf_var(tte_buffer_t * const buf,
                                   const tte_buf_var_id_t var_id,
                                   const uint32_t var_size,
                                   const void * const value){
    TTEAPIPriv *priv = (TTEAPIPriv*)buf->priv;
    switch(var_id){
        case TTE_BUFVAR_RECEIVE_CB:{
            Callback *cb = priv->buffer->getReceiveCallback(this);
            if(cb == NULL){
                cb = new APICallback(priv->buffer);
                priv->buffer->addReceiveCallback(cb, this);
            }
            cb->setFunctionPointer((void(*)(void *))value);
            break;
        }
        case TTE_BUFVAR_TRANSMIT_CB:{
            Callback *cb = priv->buffer->getTransmitCallback(this);
            if(cb == NULL){
                cb = new APICallback(priv->buffer);
                priv->buffer->addTransmitCallback(cb, this);
            }
            cb->setFunctionPointer((void(*)(void *))value);
            break;
        }
        case TTE_BUFVAR_CB_ARG:{
            Callback *cb = priv->buffer->getReceiveCallback(this);
            if(cb == NULL){
                cb = priv->buffer->getTransmitCallback(this);
                if(cb == NULL){
                    return ETT_NULLPTR;
                }
                cb->setFunctionArg((void*)value);
            }
            else{
                cb->setFunctionArg((void*)value);
            }
            break;
        }
        default:
            return ETT_NOTSUPPORTED;
    }
    return ETT_SUCCESS;
}

int32_t TTEAPIApplicationBase::tte_get_buf_var(const tte_buffer_t * const buf,
                                   const tte_buf_var_id_t var_id,
                                   const uint32_t var_size,
                                   void * const value){
    TTEAPIPriv *priv = (TTEAPIPriv*)buf->priv;
    switch(var_id){
        case TTE_BUFVAR_RECEIVE_CB:{
            Callback *cb = priv->buffer->getReceiveCallback(this);
            if(cb == NULL){
                return ETT_NULLPTR;
            }
            void (*func)(void *) = cb->getFunctionPointer();
            memcpy(value, &func, sizeof(void (*)(void *)));
            break;
        }
        case TTE_BUFVAR_TRANSMIT_CB:{
            Callback *cb = priv->buffer->getTransmitCallback(this);
            if(cb == NULL){
                return ETT_NULLPTR;
            }
            void (*func)(void *) = cb->getFunctionPointer();
            memcpy(value, &func, sizeof(void (*)(void *)));
            break;
        }
        case TTE_BUFVAR_CB_ARG:{
            Callback *cb = priv->buffer->getReceiveCallback(this);
            if(cb == NULL){
                Callback *cb = priv->buffer->getTransmitCallback(this);
                if(cb == NULL){
                    return ETT_NULLPTR;
                }
                void * arg=cb->getFunctionArg();
                memcpy(value, &arg, sizeof(void *));
            }
            else{
                void * arg=cb->getFunctionArg();
                memcpy(value, &arg, sizeof(void *));
            }
            break;
        }
        default:
            return ETT_NOTSUPPORTED;
    }
    return ETT_SUCCESS;
}

extern "C" int32_t tte_init(void){
    return ETT_NOTSUPPORTED;
}


extern "C" int32_t tte_start(const uint8_t ctrl_id){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_stop(const uint8_t ctrl_id){
    return ETT_NOTSUPPORTED;
}


extern "C" int32_t tte_exit(void){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_configure(const uint8_t ctrl_id,
                             const tte_conf_t * const conf){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_set_var(const uint8_t ctrl_id,
                           const tte_var_id_t var_id,
                           const uint32_t var_size,
                           const void * const value){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_get_var(const uint8_t ctrl_id,
                           const tte_var_id_t var_id,
                           const uint32_t var_size,
                           void * const value){
    TTEAPIApplicationBase *app = dynamic_cast<TTEAPIApplicationBase*>(cSimulation::getActiveSimulation()->getContext());
    if(app != NULL)
        return app->tte_get_var(ctrl_id, var_id, var_size, value);
    return ETT_NULLPTR;;
}

extern "C" int32_t tte_get_ct_input_buf(const uint8_t ctrl_id,
                                    const uint16_t ct_id,
                                    tte_buffer_t * const buf){
    TTEAPIApplicationBase *app = dynamic_cast<TTEAPIApplicationBase*>(cSimulation::getActiveSimulation()->getContext());
    if(app != NULL)
        return app->tte_get_ct_input_buf(ctrl_id, ct_id, buf);
    return ETT_NULLPTR;
}

extern "C" int32_t tte_get_ct_output_buf(const uint8_t ctrl_id,
                                     const uint16_t ct_id,
                                     tte_buffer_t * const buf){
    TTEAPIApplicationBase *app = dynamic_cast<TTEAPIApplicationBase*>(cSimulation::getActiveSimulation()->getContext());
    if(app != NULL)
        return app->tte_get_ct_output_buf(ctrl_id, ct_id, buf);
    return ETT_NULLPTR;
}

extern "C" int32_t tte_get_bg_input_buf(const uint8_t ctrl_id,
                                    const uint8_t channel,
                                    tte_buffer_t * const buf){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_get_bg_output_buf(const uint8_t ctrl_id,
                                     const uint8_t channel,
                                     tte_buffer_t * const buf){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_write_output_buf(tte_buffer_t * const buf,
                                    tte_frame_t * const frame){
    //TODO High prio
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_read_input_buf(tte_buffer_t * const buf,
                                  tte_frame_t * const frame,
                                  tte_buf_status_t * const status){
    //TODO High prio
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_open_input_buf(tte_buffer_t * const buf,
                                  tte_frame_t * const frame,
                                  tte_buf_status_t * const status){
    //TODO High prio
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_close_input_buf(tte_buffer_t * const buf){
    //TODO High prio
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_open_output_buf(tte_buffer_t * const buf,
                                   tte_frame_t * const frame){
    TTEAPIApplicationBase *app = dynamic_cast<TTEAPIApplicationBase*>(cSimulation::getActiveSimulation()->getContext());
    if(app != NULL)
        return app->tte_open_output_buf(buf, frame);
    return ETT_NULLPTR;
}

extern "C" int32_t tte_close_output_buf(tte_buffer_t * const buf){
    TTEAPIApplicationBase *app = dynamic_cast<TTEAPIApplicationBase*>(cSimulation::getActiveSimulation()->getContext());
    if(app != NULL)
        return app->tte_close_output_buf(buf);
    return ETT_NULLPTR;
}

extern "C" int32_t tte_get_buf_var(const tte_buffer_t * const buf,
                               const tte_buf_var_id_t var_id,
                               const uint32_t var_size,
                               void * const value){
    TTEAPIApplicationBase *app = dynamic_cast<TTEAPIApplicationBase*>(cSimulation::getActiveSimulation()->getContext());
        if(app != NULL)
            return app->tte_get_buf_var(buf, var_id, var_size, value);
        return ETT_NULLPTR;
}

extern "C" int32_t tte_set_buf_var(tte_buffer_t * const buf,
                               const tte_buf_var_id_t var_id,
                               const uint32_t var_size,
                               const void * const value){
    TTEAPIApplicationBase *app = dynamic_cast<TTEAPIApplicationBase*>(cSimulation::getActiveSimulation()->getContext());
        if(app != NULL)
            return app->tte_set_buf_var(buf, var_id, var_size, value);
        return ETT_NULLPTR;
}

extern "C" int32_t tte_flush_buffers(const uint8_t ctrl_id){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_flush_tt_buffers(const uint8_t ctrl_id){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_flush_bg_buffers(const uint8_t ctrl_id, const uint8_t channel){
    return ETT_NOTSUPPORTED;
}

} //namespace
