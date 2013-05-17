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
/*
 * SM.cpp
 *
 *  Created on: Feb 23, 2012
 *      Author: Lazar Todorov
 */
#include "SM.h"

namespace TTEthernetModel {


Define_Module(SM);

SM::SM(){}

int SM::numInitStages() const{
    return 2;
}

void SM::initialize(int stage){
    if(stage==1){




        //str= "/home/pcman/from_thinkpad/TTEthernetModel/examples/SICM_TEST_AS6802_sync/results/syncmaster";
        str = "syncmaster";
        ss<<this->par("bit_index").longValue();
        str+=ss.str();
        fp = NULL;
        if(this->par("read").boolValue()){
            this->par("write").setBoolValue(false);
            fp=fopen(str.c_str(),"r");

        }else if(this->par("write").boolValue()){
            fp=fopen(str.c_str(),"w+");
        }
        sm = new SMStateContex();
        s0 = new SM_INIT(this, fp);

        sm->setState(s0);
    }

}

void SM::finish(){
    fflush(fp);
    fclose(fp);

}

SM::~SM(){
	delete(sm);
}

void SM::handleMessage(cMessage *message){

	sm->parseMessage(message);


}
}
