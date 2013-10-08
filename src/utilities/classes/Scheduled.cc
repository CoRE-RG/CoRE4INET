#include <Scheduled.h>
#include <ModuleAccess.h>

using namespace TTEthernetModel;

void Scheduled::initialize()
{
    Timed::initialize();
    if(par("period").stdstringValue().length()==0){
        par("period").setStringValue("period[0]");
    }
    period = dynamic_cast<Period*>(findModuleWhereverInNode(par("period").stringValue(), getParentModule()));
    ASSERT2(period, "cannot find period, you should specify it!");
}

Period* Scheduled::getPeriod(){
    return period;
}
