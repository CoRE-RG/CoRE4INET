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

#include "CoRE4INET_SC.h"


namespace CoRE4INET {

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

        ss<<this->par("id").intValue();
        path+=ss.str();

        fp = NULL;
        if(this->par("read").boolValue()){
            this->par("write").setBoolValue(false);
            fp=fopen(path.c_str(),"r");

        }else if(this->par("write").boolValue()){
            fp=fopen(path.c_str(),"w+");
        }

        sc = new StateContex();
        s0 = new SC_INIT(this, fp);
        sc->setState(s0);

    }
}

void SC::finish(){
    if(fp){
        fflush(fp);
        fclose(fp);
    }
    if (this->par("read").boolValue()||this->par("write").boolValue()){
           sc->pState->values->clear();
           delete sc->pState->values;

       }
           delete sc->pState->outVector;


           if(sc->pState->event->getOwner()==this){
        cancelAndDelete(sc->pState->event);
           }


    if(sc->pState->event1->getOwner()==this){
               cancelAndDelete(sc->pState->event1);
                     }

    if(sc->pState->event2->getOwner()==this){
               cancelAndDelete(sc->pState->event2);
                     }

    if(sc->pState->event3->getOwner()==this){
               cancelAndDelete(sc->pState->event3);
                     }

    if(sc->pState->event4->getOwner()==this){
               cancelAndDelete(sc->pState->event4);
                     }

    if(sc->pState->event5->getOwner()==this){
               cancelAndDelete(sc->pState->event5);
                     }




           sc->pState->clock_stack->clear();
           delete(sc->pState->clock_stack);

}

SC::~SC(){
	delete(sc);
}

void SC::handleMessage(cMessage *m){

	sc->parseMessage(m);


}

}
