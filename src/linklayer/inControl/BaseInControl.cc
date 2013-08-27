#include "BaseInControl.h"

void BaseInControl::setParameters(EtherFrame *frame){
    int i = frame->findPar("received");
    cMsgPar* par;
    if( i >=0 )
        par = &frame->par(i);
    else
        par = &frame->addPar("received");
    par->setLongValue(((TTEScheduler*)getParentModule()->getParentModule()->getSubmodule("tteScheduler"))->getTicks());

    i = frame->findPar("received_total");
    if( i >=0 )
        par = &frame->par(i);
    else
        par = &frame->addPar("received_total");
    par->setLongValue(((TTEScheduler*)getParentModule()->getParentModule()->getSubmodule("tteScheduler"))->getTotalTicks());


    i = frame->findPar("received_port");
    if( i >=0 )
        par = &frame->par(i);
    else
        par = &frame->addPar("received_port");
    par->setLongValue(getParentModule()->getIndex());
}



