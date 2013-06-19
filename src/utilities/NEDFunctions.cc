#include "NEDFunctions.h"

#include "ModuleAccess.h"

static cNEDValue ned_sec_to_tick(cComponent *context, cNEDValue argv[], int argc)
{
    double ticklength;
    double seconds = argv[0].doubleValueInUnit("s");
    if (argc <= 1)
    {
        cModule* module = findModuleWhereverInNode("tteScheduler", context->getParentModule());
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
        "Converts seconds to ticks. Uses ticklength specified in tteScheduler or ticklength parameter if specified")
;
