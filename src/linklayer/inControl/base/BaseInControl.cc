#include "BaseInControl.h"

namespace CoRE4INET {

simsignal_t BaseInControl::rxPkSignal = SIMSIGNAL_NULL;

void BaseInControl::initialize()
{
    Timed::initialize();
    rxPkSignal = registerSignal("rxPk");
}

void BaseInControl::setParameters(EtherFrame *frame)
{
    int i = frame->findPar("received_total");
    cMsgPar* par;
    if (i >= 0)
        par = &frame->par(i);
    else
        par = &frame->addPar("received_total");
    par->setLongValue((long) timer->getTotalTicks());

    i = frame->findPar("received_port");
    if (i >= 0)
        par = &frame->par(i);
    else
        par = &frame->addPar("received_port");
    par->setLongValue(getParentModule()->getIndex());
}

void BaseInControl::recordPacketReceived(EtherFrame *frame)
{
    emit(rxPkSignal, frame);
}

}
