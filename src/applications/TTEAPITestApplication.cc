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

#include "TTEAPITestApplication.h"


#include "tte_api.h"

namespace TTEthernetModel {

Define_Module(TTEAPITestApplication);

unsigned int main(){
    //tte_init();
    tte_buffer_t testbuffer;
    if(tte_get_ct_output_buf(0, 100, &testbuffer) != ETT_SUCCESS){
        ev << "MIST1!" << endl << endl;
        return -1;
    }

    ev << "tte_get_channel_cnt(): " << tte_get_controller_cnt() << endl << endl;

    uint8_t mac[6];

    tte_get_var(0, TTE_VAR_MAC_ADDRESS,sizeof(mac), mac);

    ev.printf("TTE_VAR_MAC_ADDRESS: %02x:%02x:%02x:%02x:%02x:%02x\n\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

   /* tte_frame_t frame;
    if(tte_open_output_buf(&testbuffer, &frame) != ETT_SUCCESS){
        ev << "MIST2!" << endl << endl;
        return -1;
    }
    if(tte_close_input_buf(&testbuffer) != ETT_SUCCESS){
        ev << "MIST3!" << endl << endl;
        return -1;
    }*/

    return 0;
}

void TTEAPITestApplication::startApplication(){
    main();
}



} //namespace
