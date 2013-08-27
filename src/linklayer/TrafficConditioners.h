#ifndef __TTE4INET_TRAFFICCONDITIONERS_H_
#define __TTE4INET_TRAFFICCONDITIONERS_H_


#include <BaseTrafficConditioner.h>
#include <BETrafficConditioner.h>
#include <RCTrafficConditioner.h>
#include <PCFTrafficConditioner.h>
#include <TTTrafficConditioner.h>

namespace TTEthernetModel{

/**
* @brief Class representing the BE_TrafficConditioner module
*
* This traffic conditioner only handles best-effort traffic.
*
* @see BETrafficConditioner, BaseTrafficConditioner
*/
class BE_TrafficConditioner: public BETrafficConditioner<BaseTrafficConditioner>{};

/**
* @brief Class representing the PCF_RC_BE_TrafficConditioner module
*
* This traffic conditioner handles traffic in the following order (highest to lowest priority):
* - PCF
* - rate-constrained
* - best-effort
*
* @see PCFTrafficConditioner, RCTrafficConditioner, BETrafficConditioner, BaseTrafficConditioner
*/
class PCF_RC_BE_TrafficConditioner: public PCFTrafficConditioner<RCTrafficConditioner<BETrafficConditioner<BaseTrafficConditioner> > >{};

/**
* @brief Class representing the TT_PCF_RC_BE_TrafficConditioner module
*
* This traffic conditioner handles traffic in the following order (highest to lowest priority):
* - time-triggered
* - PCF
* - rate-constrained
* - best-effort
*
* @see TTTrafficConditioner, PCFTrafficConditioner, RCTrafficConditioner, BETrafficConditioner, BaseTrafficConditioner
*/
class TT_PCF_RC_BE_TrafficConditioner: public TTTrafficConditioner<PCFTrafficConditioner<RCTrafficConditioner<BETrafficConditioner<BaseTrafficConditioner> > > >{};

}


#endif
