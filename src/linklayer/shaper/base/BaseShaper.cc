#include "BaseShaper.h"

#include <algorithm>

#include <ModuleAccess.h>


#include <HelperFunctions.h>

using namespace CoRE4INET;


void BaseShaper::initialize(int stage)
{
    if(stage == 0){
        cGate *physOutGate = getParentModule()->getSubmodule("mac")->gate("phys$o");
        outChannel = physOutGate->findTransmissionChannel();

        WATCH(framesRequested);
    }
}

int BaseShaper::numInitStages() const{
    return 1;
}

void BaseShaper::addListener(IPassiveQueueListener *listener){
    std::list<IPassiveQueueListener*>::iterator it = find(listeners.begin(), listeners.end(), listener);
    if (it == listeners.end())
        listeners.push_back(listener);
}
void BaseShaper::removeListener(IPassiveQueueListener *listener){
    std::list<IPassiveQueueListener*>::iterator it = find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
        listeners.erase(it);
}

void BaseShaper::notifyListeners()
{
    for (std::list<IPassiveQueueListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
        (*it)->packetEnqueued(this);
}

void BaseShaper::handleMessage(cMessage *msg)
{
    delete msg;
}

void BaseShaper::enqueueMessage(cMessage *msg)
{
    delete msg;
}
