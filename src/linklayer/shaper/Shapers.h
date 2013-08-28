#ifndef __TTE4INET_SHAPERS_H_
#define __TTE4INET_SHAPERS_H_


#include <BaseShaper.h>
#include <BEShaper.h>
#include <RCShaper.h>
#include <PCFShaper.h>
#include <TTShaper.h>
#include <AVBClassAShaper.h>

namespace TTEthernetModel{

/**
* @brief Class representing the BE_Shaper module
*
* This shaper only handles best-effort traffic.
*
* @see BEShaper, BaseShaper
*/
class BE_Shaper: public BEShaper<BaseShaper>{};

/**
* @brief Class representing the PCF_RC_BE_Shaper module
*
* This shaper handles traffic in the following order (highest to lowest priority):
* - PCF
* - rate-constrained
* - best-effort
*
* @see PCFShaper, RCShaper, BEShaper, BaseShaper
*/
class PCF_RC_BE_Shaper: public PCFShaper<RCShaper<BEShaper<BaseShaper> > >{};

/**
* @brief Class representing the TT_PCF_RC_BE_Shaper module
*
* This shaper handles traffic in the following order (highest to lowest priority):
* - time-triggered
* - PCF
* - rate-constrained
* - best-effort
*
* @see TTShaper, PCFShaper, RCShaper, BEShaper, BaseShaper
*/
class TT_PCF_RC_BE_Shaper: public TTShaper<PCFShaper<RCShaper<BEShaper<BaseShaper> > > >{};

/**
* @brief Class representing the TT_AVBClassA_PCF_RC_BE_Shaper module
*
* This shaper handles traffic in the following order (highest to lowest priority):
* - time-triggered
* - AVB
* - PCF
* - rate-constrained
* - best-effort
*
* @see TTShaper, AVBClassAShaper, PCFShaper, RCShaper, BEShaper, BaseShaper
*/
class TT_AVBClassA_PCF_RC_BE_Shaper: public TTShaper<AVBClassAShaper<PCFShaper<RCShaper<BEShaper<BaseShaper> > > > >{};

}


#endif
