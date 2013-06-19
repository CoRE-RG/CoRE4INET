#include "NEDFunctions.h"

#include "ModuleAccess.h"

static cNEDValue ned_sec2tick(cComponent *context, cNEDValue argv[], int argc)
{
    cModule* module = findModuleWhereverInNode("tteScheduler",context->getParentModule());
    if(!module)
        throw cRuntimeError("ned_sec2tick(): cannot determine tick length");
    long ticks = round(argv[0].doubleValueInUnit("s")/module->par("tick").doubleValue());
    argv[0].set(ticks, "tick");
    return argv[0];
}
Define_NED_Function(ned_sec2tick, "quantity sec2tick(quantity seconds)");
