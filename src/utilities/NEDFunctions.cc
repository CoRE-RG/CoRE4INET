#include "NEDFunctions.h"

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

    long ticks = round(seconds / ticklength);
    argv[0].set(ticks, "tick");
    return argv[0];
}
Define_NED_Function2(ned_sec_to_tick, "quantity sec_to_tick(quantity seconds, quantity ticklength?)", "units",
        "Converts seconds to ticks. Uses ticklength specified in scheduler or ticklength parameter if specified");
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

    double seconds = ticks * ticklength;
    argv[0].set(seconds, "s");
    return argv[0];
}
Define_NED_Function2(ned_tick_to_sec, "quantity tick_to_sec(quantity ticks, quantity ticklength?)", "units",
        "Converts ticks to seconds. Uses ticklength specified in scheduler or ticklength parameter if specified");
Define_NED_Function2(ned_tick_to_sec, "quantity t2s(quantity ticks, quantity ticklength?)", "units",
        "Alias for tick_to_sec");

