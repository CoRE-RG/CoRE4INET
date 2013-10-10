#include "BaseInControl.h"


void BaseInControl::initialize(){
    Timed::initialize();
}

void BaseInControl::setParameters(EtherFrame *frame){
    int i = frame->findPar("received_total");
    cMsgPar* par;
    if( i >=0 )
        par = &frame->par(i);
    else
        par = &frame->addPar("received_total");
    par->setLongValue(timer->getTotalTicks());


    i = frame->findPar("received_port");
    if( i >=0 )
        par = &frame->par(i);
    else
        par = &frame->addPar("received_port");
    par->setLongValue(getParentModule()->getIndex());
}



