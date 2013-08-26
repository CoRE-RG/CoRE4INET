
#include <BaseTrafficConditioner.h>
#include "BETrafficConditioner.h"
#include "RCTrafficConditioner.h"
#include "TTTrafficConditioner.h"

namespace TTEthernetModel{

class BE_TrafficConditioner: public BETrafficConditioner<BaseTrafficConditioner>{};
Define_Module(BE_TrafficConditioner);

class RC_BE_TrafficConditioner: public RCTrafficConditioner<BETrafficConditioner<BaseTrafficConditioner> >{};
Define_Module(RC_BE_TrafficConditioner);

class TT_RC_BE_TrafficConditioner: public TTTrafficConditioner<RCTrafficConditioner<BETrafficConditioner<BaseTrafficConditioner> > >{};
Define_Module(TT_RC_BE_TrafficConditioner);

}
