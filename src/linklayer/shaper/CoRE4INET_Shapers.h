//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __CoRE4INET_SHAPERS_H_
#define __CoRE4INET_SHAPERS_H_

//CoRE4INET
#include "CoRE4INET_BaseShaper.h"
#include "CoRE4INET_BEShaper.h"

#ifdef WITH_AS6802_COMMON
//CoRE4INET
#include "CoRE4INET_RCShaper.h"
#include "CoRE4INET_PCFShaper.h"
#include "CoRE4INET_TTShaper.h"
#endif

#ifdef WITH_AVB_COMMON
//CoRE4INET
#include "CoRE4INET_AVBClassAShaper.h"
#include "CoRE4INET_AVBClassBShaper.h"
#endif

namespace CoRE4INET {

/**
 * @brief Class representing the BE_Shaper module
 *
 * This shaper only handles best-effort traffic.
 *
 * @see BEShaper, BaseShaper
 *
 * @ingroup Shapers
 *
 * @author Till Steinbach
 */
class BE_Shaper : public BEShaper<BaseShaper>
{
};

#ifdef WITH_AS6802_COMMON
/**
 * @brief Class representing the PCF_RC_BE_Shaper module
 *
 * This shaper handles traffic in the following order (highest to lowest priority):
 * - PCF
 * - rate-constrained
 * - best-effort
 *
 * @see PCFShaper, RCShaper, BEShaper, BaseShaper
 *
 * @ingroup Shapers AS6802
 *
 * @author Till Steinbach
 */
class PCF_RC_BE_Shaper : public PCFShaper<RCShaper<BEShaper<BaseShaper> > >
{
};

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
 *
 * @ingroup Shapers AS6802
 *
 * @author Till Steinbach
 */
class TT_PCF_RC_BE_Shaper : public TTShaper<PCFShaper<RCShaper<BEShaper<BaseShaper> > > >
{
};
#endif


#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON)
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
 *
 * @author Philipp Meyer
 */
class TT_AVBClassA_PCF_RC_BE_Shaper : public TTShaper<AVBClassAShaper<PCFShaper<RCShaper<BEShaper<BaseShaper> > > > >
{
};

/**
 * @brief Class representing the TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper module
 *
 * This shaper handles traffic in the following order (highest to lowest priority):
 * - time-triggered
 * - AVB
 * - PCF
 * - rate-constrained
 * - best-effort
 *
 * @see TTShaper, AVBClassAShaper, AVBClassBShaper, PCFShaper, RCShaper, BEShaper, BaseShaper
 *
 * @author Philipp Meyer
 */
class TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper : public TTShaper<AVBClassAShaper<AVBClassBShaper<PCFShaper<RCShaper<BEShaper<BaseShaper> > > > > >
{
};
#endif

}

#endif
