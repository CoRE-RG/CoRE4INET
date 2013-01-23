#include "TTEOutput.h"

#include <algorithm>

#include <Buffer.h>
#include <RCBuffer.h>
#include <PCFrame_m.h>
#include <TTEScheduler.h>
#include <TTBufferEmpty_m.h>

#include <HelperFunctions.h>

using namespace TTEthernetModel;

Define_Module( TTEOutput);

simsignal_t TTEOutput::ttQueueLengthSignal = SIMSIGNAL_NULL;
simsignal_t TTEOutput::beQueueLengthSignal = SIMSIGNAL_NULL;
simsignal_t TTEOutput::pcfQueueLengthSignal = SIMSIGNAL_NULL;

TTEOutput::TTEOutput()
{
    framesRequested = 0;
    ttBuffersPos = 0;

    ttQueue.setName("TT Messages");
    for (int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        char strBuf[64];
        snprintf(strBuf,64,"RC Priority %d Messages", i);
        rcQueue[i].setName(strBuf);
    }
    beQueue.setName("BE Messages");
    pcfQueue.setName("PCF Messages");
}

TTEOutput::~TTEOutput()
{
    ttQueue.clear();
    for (int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        rcQueue[i].clear();
    }
    beQueue.clear();
    pcfQueue.clear();
}

void TTEOutput::initialize()
{
    cGate *physOutGate = getParentModule()->getSubmodule("mac")->gate("phys$o");
    outChannel = physOutGate->findTransmissionChannel();

    ttQueueLengthSignal = registerSignal("ttQueueLength");
    beQueueLengthSignal = registerSignal("beQueueLength");
    pcfQueueLengthSignal = registerSignal("pcfQueueLength");
}

void TTEOutput::addListener(IPassiveQueueListener *listener){
    std::list<IPassiveQueueListener*>::iterator it = find(listeners.begin(), listeners.end(), listener);
    if (it == listeners.end())
        listeners.push_back(listener);
}
void TTEOutput::removeListener(IPassiveQueueListener *listener){
    std::list<IPassiveQueueListener*>::iterator it = find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
        listeners.erase(it);
}

void TTEOutput::notifyListeners()
{
    for (std::list<IPassiveQueueListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it)
        (*it)->packetEnqueued(this);
}

void TTEOutput::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("PCFin"))
    {
        if (framesRequested)
        {
            framesRequested--;
            PCFrame *pcf = dynamic_cast<PCFrame*>(msg);
            if(pcf){
                setTransparentClock(pcf);
            }
            send(msg, gateBaseId("out"));

        }
        else
        {
            pcfQueue.insert(msg);
            notifyListeners();
            emit(pcfQueueLengthSignal, pcfQueue.length());
        }
    }
    else if (msg->arrivedOn("TTin"))
    {
        if(ttBuffers.size()>0){
            ttBuffersPos = (++ttBuffersPos % ttBuffers.size());
        }

        //If we have an empty message allow other frame to be sent
        if (dynamic_cast<TTBufferEmpty *> (msg))
        {
            if (framesRequested)
            {
                framesRequested--;
                requestPacket();
            }
            delete msg;
        }
        //Else send frame
        else
        {
            if (framesRequested)
            {
                framesRequested--;
                send(msg, gateBaseId("out"));
            }
            else
            {
                EV << "There might be a configuration issue (TTBuffer not registered in Output module), or shuffling was enabled for a TTBuffer or a TTFrame was delayed by a PCF" << endl;
                ttQueue.insert(msg);
                notifyListeners();
                emit(ttQueueLengthSignal, ttQueue.length());
            }
        }
    }
    else if (msg->arrivedOn("RCin"))
    {
        if (framesRequested && isTransmissionAllowed((EtherFrame*) msg))
        {
            framesRequested--;

            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*> (msg->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();
            PCFrame *pcf = dynamic_cast<PCFrame*> (msg);
            if(pcf){
                setTransparentClock(pcf);
            }
            send(msg, gateBaseId("out"));
        }
        else
        {
            int priority = msg->getSenderModule()->par("priority").longValue();
            if (priority > 0 && priority < NUM_RC_PRIORITIES)
            {
                rcQueue[priority].insert(msg);
                notifyListeners();
            }
            else
            {
                rcQueue[0].insert(msg);
                notifyListeners();
                ev << "Priority missing!" << endl;
            }
        }
    }
    //Frames arrived on in are best-effort frames
    else if (msg->arrivedOn("in"))
    {
        // If there are framesRequested the MAC layer is currently idle
        if (framesRequested && isTransmissionAllowed((EtherFrame*) msg))
        {
            framesRequested--;
            send(msg, gateBaseId("out"));
        }
        else
        {
            beQueue.insert(msg);
            notifyListeners();
            emit(beQueueLengthSignal, beQueue.length());
        }
    }
}

void TTEOutput::registerTTBuffer(TTBuffer *ttBuffer)
{
    Enter_Method("registerTTBuffer(%s)", ttBuffer->getName());
    int sendWindowStart = ttBuffer->par("sendWindowStart");
    for (std::vector<TTBuffer*>::iterator buffer = ttBuffers.begin(); buffer != ttBuffers.end();)
    {
        if (buffer == ttBuffers.end() || (*buffer)->par("sendWindowStart").longValue() > sendWindowStart)
        {
            ttBuffers.insert(buffer, ttBuffer);
            //Now doublecheck that the schedule is not overlapping for this port
            for (std::vector<TTBuffer*>::iterator buffer2 = ttBuffers.begin(); buffer2 != ttBuffers.end();)
            {
                Buffer *tmpBuffer = *buffer2;
                ++buffer2;
                if (buffer2 != ttBuffers.end() && (tmpBuffer->par("sendWindowEnd").longValue() > (*buffer2)->par(
                        "sendWindowStart").longValue()))
                {
                    opp_error("Port cannot be scheduled due to overlapping schedules: %s (End: %d) and %s (Start: %d)", tmpBuffer->getName(),
                            tmpBuffer->par("sendWindowEnd").longValue(),
                            (*buffer2)->getName(),
                            (*buffer2)->par("sendWindowStart").longValue());
                }
            }
            return;
        }
        ++buffer;
    }
    //This should only happen if buffer was empty
    ttBuffers.push_back(ttBuffer);
}

void TTEOutput::handleParameterChange(const char* parname){
    ttBuffers.clear();
    if(ev.isGUI()){
        //TODO check why this does not work
        //getDisplayString().setTagArg("i2", 0, "");
        //getDisplayString().setTagArg("tt", 0, "");
    }
    std::string ttBuffersString = par("tt_buffers").stdstringValue();
    std::vector<std::string> ttBufferPaths;
    split(ttBuffersString,',',ttBufferPaths);
    for(std::vector<std::string>::iterator ttBufferPath = ttBufferPaths.begin();
            ttBufferPath!=ttBufferPaths.end();ttBufferPath++){
        cModule* module = simulation.getModuleByPath((*ttBufferPath).c_str());
        if(module){
            TTBuffer *ttBuffer = dynamic_cast<TTBuffer*> (module);
            if(ttBuffer){
                registerTTBuffer(ttBuffer);
            }
        }
        else{
            if(ev.isGUI()){
                ev<<"Configuration problem: Module "<<(*ttBufferPath)<<" could not be resolved or is no TT-Buffer!"<<endl;
                getDisplayString().setTagArg("i2", 0, "status/excl3");
                getDisplayString().setTagArg("tt", 0, "WARNING: Configuration Problem outgoing TT-Buffer!");
            }
        }
    }
}

void TTEOutput::requestPacket()
{
    Enter_Method("requestPacket()");
    //Feed the MAC layer with the next frame
    framesRequested++;

    //TTFrames
    if (!ttQueue.isEmpty())
    {
        framesRequested--;
        cMessage *msg = (cMessage*) ttQueue.pop();
        emit(ttQueueLengthSignal, ttQueue.length());

        //TODO Update buffers:
        if(ttBuffers.size()>0){
            ttBuffersPos = (ttBuffersPos + 1) % ttBuffers.size();
        }

        send(msg, gateBaseId("out"));
        return;
    }
    //RCFrames
    for (int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        if (!rcQueue[i].isEmpty() && isTransmissionAllowed((EtherFrame*) rcQueue[i].front()))
        {
            framesRequested--;
            EtherFrame *message = (EtherFrame*) rcQueue[i].pop();
            //Reset Bag
            RCBuffer *rcBuffer = dynamic_cast<RCBuffer*> (message->getSenderModule());
            if (rcBuffer)
                rcBuffer->resetBag();

            PCFrame *pcf = dynamic_cast<PCFrame*> (message);
            if(pcf){
                setTransparentClock(pcf);
            }
            send(message, gateBaseId("out"));
            return;
        }
    }
    //BEFrames
    if (!beQueue.isEmpty() && isTransmissionAllowed((EtherFrame*) beQueue.front()))
    {
        framesRequested--;
        cMessage* message = (cMessage*) beQueue.pop();
        send(message, gateBaseId("out"));
        emit(beQueueLengthSignal, beQueue.length());
        return;
    }
}

bool TTEOutput::isTransmissionAllowed(EtherFrame *message)
{
    if (!outChannel)
    {
        return false;
    }
    //If there are no ttBuffers everything is fine
    if (ttBuffers.size() == 0)
    {
        return true;
    }
    TTEScheduler *scheduler = (TTEScheduler*) getParentModule()->getParentModule()->getSubmodule("tteScheduler");
    //SimTime sendTime = (message->getBitLength()+INTERFRAME_GAP_BITS)/txRate;
    SimTime sendTime = outChannel->calculateDuration(message);
    //Don't know if that is right, but it works!
    sendTime += (INTERFRAME_GAP_BITS + ((PREAMBLE_BYTES + SFD_BYTES) * 8)) / outChannel->getNominalDatarate();
    unsigned long sendTicks = ceil((sendTime / scheduler->par("tick")).dbl());
    unsigned long startTicks = ttBuffers[ttBuffersPos]->par("sendWindowStart").longValue();
    unsigned long endTicks = ttBuffers[ttBuffersPos]->par("sendWindowEnd").longValue();

    //Send Window Start is in next cycle
    if (scheduler->getTicks() > startTicks)
    {
        long cycleTicks = scheduler->par("cycle_ticks").longValue();
        startTicks += cycleTicks;
        endTicks += cycleTicks;
    }
    //Send Window End is in next cycle
    else if (scheduler->getTicks() > endTicks)
    {
        endTicks += scheduler->par("cycle_ticks").longValue();
    }

    //TODO: Perhaps more complex calculations needed?
    if ((scheduler->getTicks() + sendTicks) >= startTicks)
    {
        ev << "transmission not allowed!" << endl;
        return false;
    }
    return true;
}

void TTEOutput::setTransparentClock(PCFrame *pcf){
    unsigned long transparentClock = pcf->getTransparent_clock();

    //Add static delay for this port
    transparentClock+=secondsToTransparentClock(getParentModule()->par("static_tx_delay").doubleValue());

    //Add dynamic delay for the device
    cArray parlist = pcf->getParList();
    unsigned long start = -1;
    for(int i=0;i<parlist.size();i++){
        cMsgPar *parameter = dynamic_cast<cMsgPar*>(parlist.get(i));
        if(parameter){
            if(strncmp(parameter->getName(),"received_total",15)==0 || strncmp(parameter->getName(),"created_total",15)==0){
                start = parameter->longValue();
            }
        }
    }
    if(start >= 0){
        TTEScheduler* scheduler = ((TTEScheduler*)getParentModule()->getParentModule()->getSubmodule("tteScheduler"));
        transparentClock+=ticksToTransparentClock((scheduler->getTotalTicks()-start),scheduler->par("tick").doubleValue());
    }

    //Set new transparent clock
    pcf->setTransparent_clock(transparentClock);
}

int TTEOutput::getNumPendingRequests()
{
    return framesRequested;
}

bool TTEOutput::isEmpty()
{
    bool empty = true;
    empty &= ttQueue.isEmpty();
    for (int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        empty &= rcQueue[i].isEmpty();
    }
    empty &= beQueue.isEmpty();
    return empty;
}
void TTEOutput::clear()
{
    beQueue.clear();
    for (int i = 0; i < NUM_RC_PRIORITIES; i++)
    {
        rcQueue[i].clear();
    }
    ttQueue.clear();
    framesRequested = 0;
}

