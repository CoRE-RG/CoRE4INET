#include "NEDFunctions.h"

#include "ModuleAccess.h"

static cNEDValue ned_sec2tick(cComponent *context, cNEDValue argv[], int argc)
{
    double ticklength;
    double seconds = argv[0].doubleValueInUnit("s");
    if(argc<=1){
        cModule* module = findModuleWhereverInNode("tteScheduler",context->getParentModule());
        if(!module)
            throw cRuntimeError("ned_sec2tick(): cannot determine tick length, you should specify it!");
        ticklength = module->par("tick").doubleValue();
    }
    else{
        ticklength = argv[1].doubleValueInUnit("s");
    }

    long ticks = round(seconds/ticklength);
    argv[0].set(ticks, "tick");
    return argv[0];
}
Define_NED_Function(ned_sec2tick, "quantity sec2tick(quantity seconds, quantity ticklength?)");
