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

#ifndef CORE4INET_SHAPERS_H_
#define CORE4INET_SHAPERS_H_

//CoRE4INET
#include "core4inet/linklayer/shaper/base/BaseShaper.h"
#include "core4inet/linklayer/shaper/base/BEShaper.h"
#include "core4inet/linklayer/shaper/base/BackdoorShaper.h"

#ifdef WITH_IEEE8021Q_COMMON
#include "core4inet/linklayer/shaper/IEEE8021Q/IEEE8021QShaper.h"
#endif

#ifdef WITH_AS6802_COMMON
//CoRE4INET
#include "core4inet/linklayer/shaper/AS6802/RCShaper.h"
#include "core4inet/linklayer/shaper/AS6802/PCFShaper.h"
#include "core4inet/linklayer/shaper/AS6802/TTShaper.h"
#endif

#ifdef WITH_AVB_COMMON
//CoRE4INET
#include "core4inet/linklayer/shaper/avb/AVBShaper.h"
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
    public:
        virtual ~BE_Shaper();
};

#ifdef WITH_IEEE8021Q_COMMON
/**
* @brief Class representing the IEEE8021Q_Shaper module
 *
 * This shaper handles Q-tagged and best-effort traffic.
 *
 * @see IEEE8021QShaper, BaseShaper
 *
 * @ingroup Shapers
 *
 * @author Philipp Meyer
 */
class IEEE8021Q_Shaper : public IEEE8021QShaper<BaseShaper>
{
    public:
        virtual ~IEEE8021Q_Shaper();
};
#endif

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
    public:
        virtual ~PCF_RC_BE_Shaper();
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
    public:
        virtual ~TT_PCF_RC_BE_Shaper();
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
class TT_AVBClassA_PCF_RC_BE_Shaper : public TTShaper<AVBShaper<SR_CLASS::A, PCFShaper<RCShaper<BEShaper<BaseShaper> > > > >
{
    public:
        virtual ~TT_AVBClassA_PCF_RC_BE_Shaper();
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
class TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper : public TTShaper<AVBShaper<SR_CLASS::A, AVBShaper<SR_CLASS::B, PCFShaper<RCShaper<BEShaper<BaseShaper> > > > > >
{
    public:
        virtual ~TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper();
};
#endif


#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON) && defined(WITH_IEEE8021Q_COMMON)

/**
 * @brief Class representing the TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper module
 *
 * This shaper handles traffic in the following order (highest to lowest priority):
 * - time-triggered
 * - AVB
 * - PCF
 * - rate-constrained
 * - IEEE 802.1Q
 *
 * @see TTShaper, AVBClassAShaper, AVBClassBShaper, PCFShaper, RCShaper, IEEE8021QShaper, BaseShaper
 *
 * @author Till Steinbach
 */
class TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper : public TTShaper<AVBShaper<SR_CLASS::A, AVBShaper<SR_CLASS::B, PCFShaper<RCShaper<IEEE8021QShaper<BaseShaper> > > > > >
{
    public:
        virtual ~TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper();
};

/**
 * @brief Class representing the Backdoor_TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper module
 *
 * This shaper handles traffic in the following order (highest to lowest priority):
 * - Backdoor
 * - time-triggered
 * - AVB
 * - PCF
 * - rate-constrained
 * - IEEE 802.1Q
 *
 * @see TTShaper, AVBClassAShaper, AVBClassBShaper, PCFShaper, RCShaper, IEEE8021QShaper, BaseShaper
 *
 * @author Philipp Meyer
 */
class Backdoor_TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper : public BackdoorShaper<TTShaper<AVBShaper<SR_CLASS::A, AVBShaper<SR_CLASS::B, PCFShaper<RCShaper<IEEE8021QShaper<BaseShaper> > > > > > >
{
    public:
        virtual ~Backdoor_TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper();
};
#endif

}

#endif
