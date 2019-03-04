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
#include "core4inet/utilities/NEDFunctions.h"

//CoRE4INET
#include "core4inet/utilities/ModuleAccess.h"

static omnetpp::cNEDValue ned_sec_to_tick(omnetpp::cComponent *context, omnetpp::cNEDValue argv[], int argc)
{
    double ticklength;
    double seconds = argv[0].doubleValueInUnit("s");
    if (argc <= 1)
    {
        cModule* module = CoRE4INET::findModuleWhereverInNode("scheduler", context->getParentModule());
        if (!module)
            throw cRuntimeError("ned_sec_to_tick(): cannot determine tick length, you should specify it!");
        ticklength = module->par("tick").doubleValue();
    }
    else
    {
        ticklength = argv[1].doubleValueInUnit("s");
    }

    long ticks = static_cast<long>(round(seconds / ticklength));
    argv[0].set(static_cast<intpar_t>(ticks), "tick");
    return argv[0];
}
Define_NED_Function2(ned_sec_to_tick, "quantity sec_to_tick(quantity seconds, quantity ticklength?)", "units",
        "Converts seconds to ticks. Uses ticklength specified in oscillator or ticklength parameter if specified");
Define_NED_Function2(ned_sec_to_tick, "quantity s2t(quantity seconds, quantity ticklength?)", "units",
        "Alias for sec_to_tick");

static omnetpp::cNEDValue ned_tick_to_sec(omnetpp::cComponent *context, omnetpp::cNEDValue argv[], int argc)
{
    double ticklength;
    long ticks = argv[0].longValue();
    if (argc <= 1)
    {
        cModule* module = CoRE4INET::findModuleWhereverInNode("scheduler", context->getParentModule());
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

static omnetpp::cNEDValue ned_find_module_wherever_in_node(omnetpp::cComponent *context, omnetpp::cNEDValue argv[],
        __attribute__((unused)) int argc)
{
    const char* name = argv[0].stringValue();
    cModule* contextModule = dynamic_cast<cModule*>(context);
    if(!contextModule)
    {
        throw cRuntimeError("find_in_node(): can only be used for parameters inside a networkNode!");
    }
    cModule* module = CoRE4INET::findModuleWhereverInNode(name, contextModule);
    if (!module)
    {
        throw cRuntimeError("find_in_node(): cannot find a module with this name!");
    }
    return module->getFullPath();
}

Define_NED_Function2(ned_find_module_wherever_in_node, "string find_in_node(string name)", "ned",
        "Tries to find a module with name name in the current node");
Define_NED_Function2(ned_find_module_wherever_in_node, "string find(string name)", "ned", "Alias for find_in_node");
