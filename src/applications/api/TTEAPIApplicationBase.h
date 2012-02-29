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

/**
 * @brief Message kinds for application control messages
 */
enum TTEAPIApplicationMessageKind{
    /**
     * @brief Message to trigger the application start.
     */
    START_APPLICATION
};

/**
 * @brief Class that contains different pointers. Internally used for TTEthernet-API
 */
class TTEAPIPriv
{
    public:
        /**
         * @brief Pointer to a Buffer for the current application request
         */
        Buffer *buffer;

        /**
         * @brief Pointer to an EtherFrame for the current application request
         */
        EtherFrame *frame;

        /**
         * @brief Pointer to the raw data
         */
        void *data;
};

/**
 * @brief Base class for a TTEthernet-Application based on the TTEthernet-API.
 *
 * The class contains the wrappers for the C to C++ Mapping.
 * @warning Please note that the TTEthernet-API functionality is not yet
 * completely implemented
 *
 * @sa TTEAPITestApplication, TTEApplicationBase
 * @ingroup Applications
 */
class TTEAPIApplicationBase : public TTEApplicationBase
{
    private:
        /**
         * @brief initializes the module.
         *
         * Registeres a START_APPLICATION self-message that triggers the application
         * start
         */
        virtual void initialize();

        /**
         * @brief Handles incoming START_APPLICATION or Scheduler messages.
         *
         * The module receives START_APPLICATION messages that trigger startApplication() or
         * messages via schedulerIn that contain Tasks to be executed.
         *
         * @param msg the incoming message
         */
        virtual void handleMessage(cMessage *msg);
    protected:
        /**
         * @brief Does nothing in this application. Must be overwritten with actual
         * application behavior.
         */
        virtual void startApplication();

    public:
        /**
         * @brief registers a task that is periodically scheduled.
         *
         * @param actionTime the time in ticks in each cycle the tasks is executed
         * @param functionPointer the function to execute
         */
        virtual void registerTask(unsigned int actionTime, void (*functionPointer)(void*), void *setFunctionArg);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_get_ct_output_buf(const uint8_t ctrl_id,
                const uint16_t ct_id,
                tte_buffer_t * const buf);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_get_bg_output_buf(const uint8_t ctrl_id,
                const uint8_t channel,
                tte_buffer_t * const buf);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_get_bg_input_buf(const uint8_t ctrl_id,
                const uint8_t channel,
                tte_buffer_t * const buf);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_get_ct_input_buf(const uint8_t ctrl_id,
                const uint16_t ct_id,
                tte_buffer_t * const buf);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_get_var(const uint8_t ctrl_id,
                const tte_var_id_t var_id,
                const uint32_t var_size,
                void * const value);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_open_output_buf(tte_buffer_t * const buf,
                tte_frame_t * const frame);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_open_input_buf(tte_buffer_t * const buf,
                tte_frame_t * const frame,
                tte_buf_status_t * const status);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_close_output_buf(tte_buffer_t * const buf);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_close_input_buf(tte_buffer_t * const buf);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_set_buf_var(tte_buffer_t * const buf,
                const tte_buf_var_id_t var_id,
                const uint32_t var_size,
                const void * const value);

        /**
         * @brief implementation of the TTEthernet-API method.
         *
         * see TTEthernet-API documentation for further information
         */
        virtual int32_t tte_get_buf_var(const tte_buffer_t * const buf,
                const tte_buf_var_id_t var_id,
                const uint32_t var_size,
                void * const value);
};


} //namespace

#endif
