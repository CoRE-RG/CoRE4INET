#include "BaseTrafficConditioner.h"

#include <algorithm>

#include <ModuleAccess.h>


#include <HelperFunctions.h>

using namespace TTEthernetModel;


void BaseTrafficConditioner::initialize()
{
    cGate *physOutGate = getParentModule()->getSubmodule("mac")->gate("phys$o");
    outChannel = physOutGate->findTransmissionChannel();

    WATCH(framesRequested);
}

void BaseTrafficConditioner::addListener(IPassiveQueueListener *listener){
    std::list<IPassiveQueueListener*>::iterator it = find(listeners.begin(), listeners.end(), listener);
    if (it == listeners.end())
        listeners.push_back(listener);
}
void BaseTrafficConditioner::removeListener(IPassiveQueueListener *listener){
    std::list<IPassiveQueueListener*>::iterator it = find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
        listeners.erase(it);
}

void BaseTrafficConditioner::notifyListeners()
{
    for (std::list<IPassiveQueueListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
        (*it)->packetEnqueued(this);
}

void BaseTrafficConditioner::handleMessage(cMessage *msg)
{
    delete msg;
}
