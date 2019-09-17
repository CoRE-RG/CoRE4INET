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
#include "CoRE4INET_HICM.h"

namespace CoRE4INET{

Define_Module(HICM);



HICM::HICM(){}

int HICM::numInitStages() const{
    return 2;
}

void HICM::initialize(int stage){

    if(stage==1){

        path="compmaster";
        //path="/home/pcman/from_thinkpad/TTEthernetModel/examples/SICM_TEST_AS6802_sync/results/compmaster";

        ss<<this->par("id").intValue();
        path+=ss.str();
        fp = NULL;
        if(this->par("read").boolValue()){
            this->par("write").setBoolValue(false);
            fp=fopen(path.c_str(),"r");

        }else if(this->par("write").boolValue()){
            fp=fopen(path.c_str(),"w+");
        }

        cm = new HICMStateContex();
        c0 = new HI_CM_INIT(this, fp);
        cm->setState(c0);

    }

}

void HICM::finish(){
    if(fp){
        fflush(fp);
        fclose(fp);
    }

    delete(cm->pState->outVector);

    if (this->par("read").boolValue() || this->par("write").boolValue() ) {
        cm->pState->values->clear();
    delete(cm->pState->values);
    }

    if(cm->pState->event->getOwner()==this){
        cancelAndDelete(cm->pState->event);
    }
    if(cm->pState->event2->getOwner()==this){
           cancelAndDelete(cm->pState->event2);
       }
    if(cm->pState->event3->getOwner()==this){
           cancelAndDelete(cm->pState->event3);
       }
    if(cm->pState->event4->getOwner()==this){
              cancelAndDelete(cm->pState->event4);
          }
    if(cm->pState->event5->getOwner()==this){
                  cancelAndDelete(cm->pState->event5);
              }





    /*for(std::map<long int, PCFrame *>::iterator itCompFrames=cm->pState->compressed_frames->begin(); itCompFrames != cm->pState->compressed_frames->end(); itCompFrames++){


            cancelAndDelete(itCompFrames->second);



        }*/

    cm->pState->compressed_frames->clear();

    delete(cm->pState->compressed_frames);

    for(cm->pState->compression_stack_it=cm->pState->compression_stack->begin();cm->pState->compression_stack_it != cm->pState->compression_stack->end(); cm->pState->compression_stack_it++){

        (*cm->pState->compression_stack_it).second->clear();

        delete (*cm->pState->compression_stack_it).second;
    }

    cm->pState->compression_stack->clear();

    delete(cm->pState->compression_stack);

    for(std::deque<CompressedPIT *>::iterator event=cm->pState->delay_container->begin();event != cm->pState->delay_container->end(); event++){

        if((*event)->getOwner()==this)

            cancelAndDelete(*event);
    }

    cm->pState->delay_container->clear();

    delete(cm->pState->delay_container);

    for(std::deque<DispatchDelay *>::iterator event=cm->pState->dispatch_delay_container->begin(); event != cm->pState->dispatch_delay_container->end(); event++){

        if((*event)->getOwner()==this)

           cancelAndDelete(*event);

    }

    cm->pState->dispatch_delay_container->clear();

    delete(cm->pState->dispatch_delay_container);

    cm->pState->clock_stack->clear();
    delete(cm->pState->clock_stack);



}

HICM::~HICM(){

    delete(cm);
}

void HICM::handleMessage(cMessage *message){


	cm->parseMessage(message);


}


}
