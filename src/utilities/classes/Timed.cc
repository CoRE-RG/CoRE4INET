#include <Scheduled.h>
#include <ModuleAccess.h>

using namespace CoRE4INET;

void Timed::initialize()
{
    timer = dynamic_cast<Timer*>(findModuleWhereverInNode(par("timer").stringValue(), getParentModule()));
    ASSERT2(timer, "cannot find timer!");
    oscillator = dynamic_cast<Oscillator*>(findModuleWhereverInNode(par("oscillator").stringValue(), getParentModule()));
    ASSERT2(oscillator, "cannot find oscillator!");
}

Oscillator* Timed::getOscillator(){
    return oscillator;
}

Timer* Timed::getTimer(){
    return timer;
}
