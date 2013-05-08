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
 * HICM.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */
#include "HICM.h"

namespace TTEthernetModel{

Define_Module(HICM);



HICM::HICM(){}

int HICM::numInitStages() const{
    return 2;
}

void HICM::initialize(int stage){

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

        cm = new HICMStateContex();
        c0 = new HI_CM_INIT(this, fp);
        cm->setState(c0);

    }

}

void HICM::finish(){

    fflush(fp);
    fclose(fp);
}

HICM::~HICM(){

	delete(c0);
	delete(cm);


}

void HICM::handleMessage(cMessage *message){


	cm->parseMessage(message);


}


}
