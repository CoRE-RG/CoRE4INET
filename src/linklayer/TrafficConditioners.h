#ifndef __TTE4INET_TRAFFICCONDITIONERS_H_
#define __TTE4INET_TRAFFICCONDITIONERS_H_


#include <BaseTrafficConditioner.h>
#include <BETrafficConditioner.h>
#include <RCTrafficConditioner.h>
#include <PCFTrafficConditioner.h>
#include <TTTrafficConditioner.h>

namespace TTEthernetModel{

class BE_TrafficConditioner: public BETrafficConditioner<BaseTrafficConditioner>{};

class PCF_RC_BE_TrafficConditioner: public PCFTrafficConditioner<RCTrafficConditioner<BETrafficConditioner<BaseTrafficConditioner> > >{};

class TT_PCF_RC_BE_TrafficConditioner: public TTTrafficConditioner<PCFTrafficConditioner<RCTrafficConditioner<BETrafficConditioner<BaseTrafficConditioner> > > >{};

}


#endif
