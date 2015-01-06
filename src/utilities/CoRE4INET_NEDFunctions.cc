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
#include "CoRE4INET_NEDFunctions.h"

//INET
#include "ModuleAccess.h"

static cNEDValue ned_sec_to_tick(cComponent *context, cNEDValue argv[], int argc)
{
    double ticklength;
    double seconds = argv[0].doubleValueInUnit("s");
    if (argc <= 1)
    {
        cModule* module = findModuleWhereverInNode("scheduler", context->getParentModule());
        if (!module)
            throw cRuntimeError("ned_sec_to_tick(): cannot determine tick length, you should specify it!");
        ticklength = module->par("tick").doubleValue();
    }
    else
    {
        ticklength = argv[1].doubleValueInUnit("s");
    }

    long ticks = static_cast<long>(round(seconds / ticklength));
    argv[0].set(static_cast<double>(ticks), "tick");
    return argv[0];
}
Define_NED_Function2(ned_sec_to_tick, "quantity sec_to_tick(quantity seconds, quantity ticklength?)", "units",
        "Converts seconds to ticks. Uses ticklength specified in oscillator or ticklength parameter if specified");
Define_NED_Function2(ned_sec_to_tick, "quantity s2t(quantity seconds, quantity ticklength?)", "units",
        "Alias for sec_to_tick");

static cNEDValue ned_tick_to_sec(cComponent *context, cNEDValue argv[], int argc)
{
    double ticklength;
    long ticks = argv[0].longValue();
    if (argc <= 1)
    {
        cModule* module = findModuleWhereverInNode("scheduler", context->getParentModule());
        if (!module)
            throw cRuntimeError("ned_sec_to_tick(): cannot determine tick length, you should specify it!");
        ticklength = module->par("tick").doubleValue();
    }
    else
    {
        ticklength = argv[1].doubleValueInUnit("s");
    }

    double seconds = static_cast<double>(ticks) * ticklength;
    argv[0].set(seconds, "s");
    return argv[0];
}
Define_NED_Function2(ned_tick_to_sec, "quantity tick_to_sec(quantity ticks, quantity ticklength?)", "units",
        "Converts ticks to seconds. Uses ticklength specified in oscillator or ticklength parameter if specified");
Define_NED_Function2(ned_tick_to_sec, "quantity t2s(quantity ticks, quantity ticklength?)", "units",
        "Alias for tick_to_sec");
