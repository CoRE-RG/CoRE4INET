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

#include "CoRE4INET_TTEAPITestApplication.h"

//TTE-API
#include "tte_api.h"

namespace CoRE4INET {

Define_Module(TTEAPITestApplication)

void testCallback(void* arg)
{
    std::string teststring = (const char *) arg;
    EV_INFO << "CALLBACK EXECUTED! " << teststring << endl << endl;
}

int main()
{
    //tte_init();
    tte_buffer_t testbuffer;
    if (tte_get_ct_output_buf(0, 100, &testbuffer) != ETT_SUCCESS)
    {
        EV_TRACE << "Error!" << endl << endl;
        return -1;
    }

    EV_TRACE << "tte_get_channel_cnt(): " << tte_get_controller_cnt() << endl << endl;

    uint8_t mac[6];

    tte_get_var(0, TTE_VAR_MAC_ADDRESS, sizeof(mac), mac);

    ev.printf("TTE_VAR_MAC_ADDRESS: %02x:%02x:%02x:%02x:%02x:%02x\n\n", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);

    if (tte_set_buf_var(&testbuffer, TTE_BUFVAR_TRANSMIT_CB, sizeof(void (*)(void*)), (void*)&testCallback) != ETT_SUCCESS)
    {
        EV_TRACE << "Error in tte_set_buf_var()" << endl << endl;
        return -1;
    }
    if (tte_set_buf_var(&testbuffer, TTE_BUFVAR_CB_ARG, 5, "SENT") != ETT_SUCCESS)
    {
        EV_TRACE << "Error in tte_set_buf_var()" << endl << endl;
        return -1;
    }

    tte_frame_t frame;
    frame.length = 46;

    frame.eth_hdr.src_mac[0] = 0x00;
    frame.eth_hdr.src_mac[1] = 0x00;
    frame.eth_hdr.src_mac[2] = 0x00;
    frame.eth_hdr.src_mac[3] = 0x00;
    frame.eth_hdr.src_mac[4] = 0x00;
    frame.eth_hdr.src_mac[5] = 0x00;

    frame.eth_hdr.dst_mac[0] = 0x00;
    frame.eth_hdr.dst_mac[1] = 0x00;
    frame.eth_hdr.dst_mac[2] = 0x00;
    frame.eth_hdr.dst_mac[3] = 0x00;
    frame.eth_hdr.dst_mac[4] = 0x00;
    frame.eth_hdr.dst_mac[5] = 0x00;

    if (tte_open_output_buf(&testbuffer, &frame) != ETT_SUCCESS)
    {
        EV_TRACE << "Error in tte_open_output_buf" << endl << endl;
        return -1;
    }
    if (tte_close_output_buf(&testbuffer) != ETT_SUCCESS)
    {
        EV_TRACE << "Error in tte_close_output_buf" << endl << endl;
        return -1;
    }

    tte_buffer_t testbuffer2;
    if (tte_get_ct_output_buf(0, 100, &testbuffer2) != ETT_SUCCESS)
    {
        EV_TRACE << "Error in tte_get_ct_output_buf" << endl << endl;
        return -1;
    }
    if (tte_set_buf_var(&testbuffer2, TTE_BUFVAR_RECEIVE_CB, sizeof(void (*)(void*)), (void*)&testCallback) != ETT_SUCCESS)
    {
        EV_TRACE << "Error in tte_set_buf_var" << endl << endl;
        return -1;
    }
    if (tte_set_buf_var(&testbuffer2, TTE_BUFVAR_CB_ARG, 9, "RECEIVED") != ETT_SUCCESS)
    {
        EV_TRACE << "Error in tte_set_buf_var" << endl << endl;
        return -1;
    }

    return 0;
}

void TTEAPITestApplication::startApplication()
{
    main();
}

} //namespace
