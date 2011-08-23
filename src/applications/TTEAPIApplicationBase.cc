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

namespace TTEthernetModel {

Define_Module(TTEAPIApplicationBase);

void TTEAPIApplicationBase::initialize()
{
    scheduleAt(simTime(), new cMessage("Start Application"));
}

void TTEAPIApplicationBase::handleMessage(cMessage *msg)
{
    startApplication();
}

void TTEAPIApplicationBase::startApplication(){
    ev << "TTEAPIApplicationBase::startApplication() not implemented" << endl;
    throw;
}


int32_t TTEAPIApplicationBase::tte_get_ct_output_buf(const uint8_t ctrl_id,
                                                     const uint16_t ct_id,
                                                     tte_buffer_t * const buf){
    //TODO: Find appropriate Buffer buffer and fill the structure with information obtained from there
    //TODO: Best implementation: Put map in BufferManager and ask there!
    buf->ctrl_id=0;
    buf->direction= TTE_DIR_OUTPUT;
    buf->traffic_type= TTE_CT_TRAFFIC;
    buf->channel=0;
    buf->ct_id=ct_id;
    buf->shared=0;
    //TODO: set priv structure to pointer to the buffer;
    buf->priv=NULL;
    return ETT_SUCCESS;
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
        }
        case TTE_VAR_CTRL_COUNT:{
            *((uint8_t*)value) = 1;
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
        }
        case TTE_VAR_MAC_ADDRESS:{
            uint8_t *valueArr= (uint8_t *)value;
            cModule *phy = getParentModule()->getSubmodule("phy", 0);
            if(phy){
                EtherMACFullDuplex *mac = (EtherMACFullDuplex*)phy->getSubmodule("mac");
                MACAddress macAddress = mac->getMACAddress();
                valueArr[0] = macAddress.getAddressByte(0);
                valueArr[1] = macAddress.getAddressByte(1);
                valueArr[2] = macAddress.getAddressByte(2);
                valueArr[3] = macAddress.getAddressByte(3);
                valueArr[4] = macAddress.getAddressByte(4);
                valueArr[5] = macAddress.getAddressByte(5);
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
    return ETT_NOTSUPPORTED;
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
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_read_input_buf(tte_buffer_t * const buf,
                                  tte_frame_t * const frame,
                                  tte_buf_status_t * const status){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_open_input_buf(tte_buffer_t * const buf,
                                  tte_frame_t * const frame,
                                  tte_buf_status_t * const status){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_close_input_buf(tte_buffer_t * const buf){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_open_output_buf(tte_buffer_t * const buf,
                                   tte_frame_t * const frame){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_close_output_buf(tte_buffer_t * const buf){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_get_buf_var(const tte_buffer_t * const buf,
                               const tte_buf_var_id_t var_id,
                               const uint32_t var_size,
                               void * const value){
    return ETT_NOTSUPPORTED;
}

extern "C" int32_t tte_set_buf_var(tte_buffer_t * const buf,
                               const tte_buf_var_id_t var_id,
                               const uint32_t var_size,
                               const void * const value){
    return ETT_NOTSUPPORTED;
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
