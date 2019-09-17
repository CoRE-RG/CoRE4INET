cplusplus {{
        #include "core4inet/scheduler/SchedulerMessageEvents_m.h"
        #include "core4inet/linklayer/ethernet/AS6802/PCFrame_m.h"
}}

namespace CoRE4INET;

class SchedulerActionTimeEvent;
class SchedulerTimerEvent;

enum PCFType;

//
// Documentation TBD
//
// @see SchedulerTimerEvent
//
// @author Lazar Todorov
message FrameEvent extends SchedulerTimerEvent
{
        unsigned long integrationCycle;
		unsigned int member;
		unsigned char pcfType @enum(PCFType);
		unsigned int receivedPort;
}

//
// Documentation TBD
//
// @see SchedulerTimerEvent
//
// @author Lazar Todorov
message OWCounter extends SchedulerTimerEvent
{
		unsigned int lastNumberOfFrames;
		unsigned int numberOfObservationWindow;
		unsigned long integrationCycle;
}

//
// Documentation TBD
//
// @see SchedulerTimerEvent
//
// @author Lazar Todorov
message CompressedPIT extends SchedulerTimerEvent
{
	unsigned int membership_new;
	unsigned long integrationCycle;
}

//
// Documentation TBD
//
// @see SchedulerTimerEvent
//
// @author Lazar Todorov
message DispatchDelay extends SchedulerTimerEvent
{
	long frameID;
	unsigned int membership_new;

}
