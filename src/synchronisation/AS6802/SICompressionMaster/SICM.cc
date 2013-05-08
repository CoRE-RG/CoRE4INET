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
 * SICM.cpp
 *
 *  Created on: Mar 9, 2012
 *      Author: Lazar Todorov
 */

#include "SICM.h"

namespace TTEthernetModel{

Define_Module(SICM);



SICM::SICM(){}

int SICM::numInitStages() const{
    return 2;
}

void SICM::initialize(int stage){

    if(stage==1){

        path="compmaster";
        //path="/home/pcman/from_thinkpad/TTEthernetModel/examples/SICM_TEST_AS6802_sync/results/compmaster";

        ss<<this->par("id").longValue();
        path+=ss.str();
        if(this->par("read").boolValue()){

            fp=fopen(path.c_str(),"r");

        }else{
            fp=fopen(path.c_str(),"w+");
        }

        cm = new SICMStateContex();
        c0 = new SI_CM_INIT(this, fp);
        cm->setState(c0);

    }

}

void SICM::finish(){

    fflush(fp);
    fclose(fp);
}

SICM::~SICM(){

	delete(c0);
	delete(cm);


}

void SICM::handleMessage(cMessage *message){


	cm->parseMessage(message);


}


}
