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

#include "core4inet/linklayer/inControl/InControls.h"

using namespace CoRE4INET;


Define_Module(BE_InControl);
BE_InControl::~BE_InControl()
{
}

#ifdef WITH_IEEE8021Q_COMMON
Define_Module(IEEE8021Q_InControl);
IEEE8021Q_InControl::~IEEE8021Q_InControl()
{
}
#endif

#ifdef WITH_AS6802_COMMON
Define_Module(CT_BE_InControl);
CT_BE_InControl::~CT_BE_InControl()
{
}
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_IEEE8021Q_COMMON)
Define_Module(AVB_8021Q_InControl);
AVB_8021Q_InControl::~AVB_8021Q_InControl()
{
}
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON)
Define_Module(CT_AVB_BE_InControl);
CT_AVB_BE_InControl::~CT_AVB_BE_InControl()
{
}
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON) && defined(WITH_IEEE8021Q_COMMON)
Define_Module(CT_AVB_8021Q_InControl);
CT_AVB_8021Q_InControl::~CT_AVB_8021Q_InControl()
{
}
#endif
