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
 * SC.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: Lazar Todorov
 */

#include "SC.h"


namespace TTEthernetModel {

Define_Module(SC);

SC::SC(){
}

int SC::numInitStages() const{
    return 2;
}

void SC::initialize(int stage){
    if(stage==1){

        path="client";
        //path = "/home/pcman/from_thinkpad/TTEthernetModel/examples/SICM_TEST_AS6802_sync/results/client";

        ss<<this->par("id").longValue();
        path+=ss.str();

        if(this->par("read").boolValue()){

            fp=fopen(path.c_str(),"r");

        }else{

            fp=fopen(path.c_str(),"w+");


        }

        sc = new StateContex();
        s0 = new SC_INIT(this, fp);
        sc->setState(s0);

    }
}

void SC::finish(){
    fflush(fp);
    fclose(fp);



}

SC::~SC(){

	delete(s0);
	delete(sc);


}

void SC::handleMessage(cMessage *m){

	sc->parseMessage(m);


}

}
