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
#ifndef CORE4INET_INCONTROLS_H_
#define CORE4INET_INCONTROLS_H_

//CoRE4INET
#include "core4inet/linklayer/inControl/base/BaseInControl.h"
#include "core4inet/linklayer/inControl/base/BEInControl.h"

#ifdef WITH_AS6802_COMMON
//CoRE4INET
#include "core4inet/linklayer/inControl/AS6802/CTInControl.h"
#endif

#ifdef WITH_AVB_COMMON
//CoRE4INET
#include "core4inet/linklayer/inControl/avb/AVBInControl.h"
#endif

#ifdef WITH_IEEE8021Q_COMMON
//CoRE4INET
#include "core4inet/linklayer/inControl/IEEE8021Q/IEEE8021QInControl.h"
#endif

namespace CoRE4INET {

/**
 * @brief Class representing the BE_InControl module
 *
 * This module only handles incoming best-effort traffic.
 *
 * @see BaseInControl
 *
 * @author Till Steinbach
 */
class BE_InControl : public BEInControl<BaseInControl>
{
    public:
        virtual ~BE_InControl();
};

#ifdef WITH_IEEE8021Q_COMMON
/**
 * @brief Class representing the BE_InControl module
 *
 * This module only handles incoming best-effort traffic.
 *
 * @see BaseInControl
 *
 * @author Till Steinbach
 */
class IEEE8021Q_InControl : public IEEE8021QInControl<BaseInControl>
{
    public:
        virtual ~IEEE8021Q_InControl();
};
#endif

#ifdef WITH_AS6802_COMMON
/**
 * @brief Class representing the CT_BE_InControl module
 *
 * This module handles incoming critical (TT, RC and PCF) and best-effort traffic.
 *
 * @see BaseInControl, BEInControl
 *
 * @ingroup AS6802
 *
 * @author Till Steinbach
 */
class CT_BE_InControl : public CTInControl<BEInControl<BaseInControl> >
{
    public:
        virtual ~CT_BE_InControl();
};
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_IEEE8021Q_COMMON)
/**
 * @brief Class representing the AVB_8021Q_InControl
 *
 * This module handles incoming AVB and IEEE 802.1Q traffic
 *
 * @see BaseInControl, IEEE8021Q_InControl
 *
 * @author Philipp Meyer
 */
class AVB_8021Q_InControl : public AVBInControl<IEEE8021QInControl<BaseInControl> >
{
    public:
        virtual ~AVB_8021Q_InControl();
};
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON)
/**
 * @brief Class representing the CT_AVB_BE_InControl module
 *
 * This module handles incoming critical (TT, RC and PCF), AVB and best-effort traffic.
 *
 * @see BaseInControl, BEInControl, CT_BE_InControl
 *
 * @author Philipp Meyer
 */
class CT_AVB_BE_InControl : public CTInControl<AVBInControl<BEInControl<BaseInControl> > >
{
    public:
        virtual ~CT_AVB_BE_InControl();
};
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON) && defined(WITH_IEEE8021Q_COMMON)
/**
 * @brief Class representing the CT_AVB_8021Q_InControl module
 *
 * This module handles incoming critical (TT, RC and PCF), AVB and best-effort traffic using IEEE 802.1Q.
 *
 * @see BaseInControl, BEInControl, CT_BE_InControl, IEEE8021Q_InControl
 *
 * @author Philipp Meyer
 */
class CT_AVB_8021Q_InControl : public CTInControl<AVBInControl<IEEE8021QInControl<BaseInControl> > >
{
    public:
        virtual ~CT_AVB_8021Q_InControl();
};
#endif

}

#endif
