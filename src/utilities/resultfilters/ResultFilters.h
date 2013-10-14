#ifndef __TTE4INET_RESULTFILTERS_H
#define __TTE4INET_RESULTFILTERS_H

#include <cresultfilter.h>

namespace TTEthernetModel{

/**
 * Filter that expects a cMessage and outputs its age in seconds
 * (t - msg->getCreationTime()).
 */
class InnerMessageFilter : public cObjectResultFilter
{
    public:
        virtual void receiveSignal(cResultFilter *prev, simtime_t_cref t, cObject *object);
};

}

#endif
