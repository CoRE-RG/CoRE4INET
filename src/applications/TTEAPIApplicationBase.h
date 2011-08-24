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

#ifndef __TTETHERNETMODELV2_TTEAPIAPPLICATIONBASE_H_
#define __TTETHERNETMODELV2_TTEAPIAPPLICATIONBASE_H_

#include <omnetpp.h>
#include "tte_api.h"
#include "TTEApplicationBase.h"
#include "CTFrame_m.h"


#define TTE_API_VER ( (int32_t) (0x02<<16 | 0x0000) )

namespace TTEthernetModel {

enum TTEAPIApplicationMessageKind{
    START_APPLICATION
};

/**
 * TODO - Generated class
 */
class TTEAPIApplicationBase : public TTEApplicationBase
{
  private:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  protected:
    virtual void startApplication();

  public:
    virtual int32_t tte_get_ct_output_buf(const uint8_t ctrl_id,
                                  const uint16_t ct_id,
                                  tte_buffer_t * const buf);
    virtual int32_t tte_get_var(const uint8_t ctrl_id,
                                    const tte_var_id_t var_id,
                                    const uint32_t var_size,
                                    void * const value);

    virtual int32_t tte_open_output_buf(tte_buffer_t * const buf,
                                       tte_frame_t * const frame);

    virtual int32_t tte_close_output_buf(tte_buffer_t * const buf);
};

class APIBufferPriv
{
    public:
        Incoming *ctc;
        CTFrame *frame;
        void *data;
};


} //namespace

#endif
