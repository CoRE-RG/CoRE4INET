#include "SchedulerEvent.h"

namespace CoRE4INET {

Register_Class(SchedulerEvent);

cGate* SchedulerEvent::getDestinationGate() const
{
    return destinationGate_var;
}

void SchedulerEvent::setDestinationGate(cGate *destinationGate_var)
{
    this->destinationGate_var = destinationGate_var;
}

}
