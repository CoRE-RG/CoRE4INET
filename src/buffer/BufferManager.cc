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

#include "BufferManager.h"

#include <buffer/Buffer.h>
#include <TTEInput.h>
#include <TTEOutput.h>
#include "TTEApplicationBase.h"

#include <configuration/ConfigurationUtils.h>

namespace TTEthernetModel {

Define_Module( BufferManager);

int BufferManager::numInitStages() const
{
    return 2;
}

void BufferManager::initialize(int stage)
{
    if (stage == 1)
    {
        ConfigurationUtils::getPreloadedMMR();
        ecorecpp::ModelRepository *mr = ecorecpp::ModelRepository::_instance();
        ConfigurationUtils::resolveCommonAliases(mr);
        ::ecore::EObject *eobj = mr->getByFilename(getParentModule()->par("network_configuration"));
        assert(eobj);
        NetworkConfig *nc = ::ecore::instanceOf<NetworkConfig>(eobj);
        assert(nc);
        DeviceSpecification *dc = ConfigurationUtils::getDeviceSpecification(getParentModule()->par("device_name"), nc);
        EList<VirtualLinkSchedule>& vlSchedulesList = dc->getVlSchedules()->getVlSchedule();
        for (unsigned int i = 0; i < vlSchedulesList.size(); i++)
        {
            VirtualLinkSchedule_ptr vls = vlSchedulesList.get(i);
            EList<CTIncoming>& incomingList = vls->getIncoming();
            for (unsigned int j = 0; j < incomingList.size(); j++)
            {
                CTIncoming_ptr incoming = incomingList.get(j);
                cModuleType *moduleType;
                cModule* newCTCModule;
                if (incoming->eClass()->getName() == "TTIncoming")
                {
                    Device_Specification::TTIncoming *ttincoming = incoming->as<Device_Specification::TTIncoming> ();
                    moduleType = cModuleType::get("ttethernet.ctc.TTIncoming");
                    std::string ctcName = vls->getRefVirtualLink()->getVlid().c_str();
                    ctcName.append("_CTC");
                    newCTCModule = moduleType->create(ctcName.c_str(), getParentModule());
                    //parameters
                    newCTCModule->par("receive_window_start") = ConfigurationUtils::time2ticks(
                            ttincoming->getReceiveWindowStart(),
                            getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                    newCTCModule->par("receive_window_end") = ConfigurationUtils::time2ticks(
                            ttincoming->getReceiveWindowEnd(),
                            getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                    newCTCModule->par("permanence_pit") = ConfigurationUtils::time2ticks(
                            ttincoming->getPermanencePit(),
                            getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                }
                else if (incoming->eClass()->getName() == "RCIncoming")
                {
                    Device_Specification::RCIncoming *rcincoming = incoming->as<Device_Specification::RCIncoming> ();
                    moduleType = cModuleType::get("ttethernet.ctc.RCIncoming");
                    std::string ctcName = vls->getRefVirtualLink()->getVlid().c_str();
                    ctcName.append("_CTC");
                    newCTCModule = moduleType->create(ctcName.c_str(), getParentModule());
                    //parameters
                    newCTCModule->par("bag") = ConfigurationUtils::time2ticks(rcincoming->getRefBagAccount()->getBag(),
                            getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                    newCTCModule->par("jitter") = ConfigurationUtils::time2ticks(
                            rcincoming->getRefBagAccount()->getJitter(),
                            getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                }
                else
                {
                    continue;
                }
                newCTCModule->finalizeParameters();
                newCTCModule->buildInside();
                newCTCModule->callInitialize();

                cModule* newModule;
                //Create Outgoing Buffers
                EList<Outgoing>& outgoingList = incoming->getOutgoing();
                for (unsigned int k = 0; k < outgoingList.size(); k++)
                {
                    Outgoing_ptr outgoing = outgoingList.get(k);
                    if (outgoing->eClass()->getName() == "TTOutgoing")
                    {
                        TTOutgoing_ptr ttoutgoing = outgoing->as<TTOutgoing> ();
                        //TODO: This may be wrong! What is the difference between incoming and outgoing buffer depth
                        if (incoming->getBufferDepth() > 0)
                        {
                            moduleType = cModuleType::get("ttethernet.buffer.TTQueueBuffer");
                        }
                        else
                        {
                            moduleType = cModuleType::get("ttethernet.buffer.TTDoubleBuffer");
                        }

                        newModule = moduleType->create(vls->getRefVirtualLink()->getVlid().c_str(), getParentModule());
                        //parameters
                        newModule->par("sendWindowStart") = ConfigurationUtils::time2ticks(
                                ttoutgoing->getSendWindowStart(),
                                getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                        newModule->par("sendWindowEnd") = ConfigurationUtils::time2ticks(
                                ttoutgoing->getSendWindowEnd(),
                                getParentModule()->getSubmodule("tteScheduler")->par("tick"));

                    }
                    else if (outgoing->eClass()->getName() == "RCOutgoing")
                    {
                        RCOutgoing_ptr rcoutgoing = outgoing->as<RCOutgoing> ();
                        //TODO: This may be wrong! What is the difference between incoming and outgoing buffer depth
                        if (incoming->getBufferDepth() > 0)
                        {
                            moduleType = cModuleType::get("ttethernet.buffer.RCQueueBuffer");
                        }
                        else
                        {
                            moduleType = cModuleType::get("ttethernet.buffer.RCDoubleBuffer");
                        }

                        newModule = moduleType->create(vls->getRefVirtualLink()->getVlid().c_str(), getParentModule());
                        //parameters
                        newModule->par("max_dispatch_delay") = ConfigurationUtils::time2ticks(
                                rcoutgoing->getMaxDispatchDelay(),
                                getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                        newModule->par("bag") = ConfigurationUtils::time2ticks(
                                rcoutgoing->getRefBagAccount()->getBag(),
                                getParentModule()->getSubmodule("tteScheduler")->par("tick"));
                        newModule->par("jitter") = ConfigurationUtils::time2ticks(
                                rcoutgoing->getRefBagAccount()->getJitter(),
                                getParentModule()->getSubmodule("tteScheduler")->par("tick"));

                    }
                    else
                    {
                        continue;
                    }
                    //Set CT ID, marker and mask
                    newModule->par("ct_id") = ConfigurationUtils::getVLid(vls->getRefVirtualLink(), nc->getRefMappings());
                    if (dc->eClass()->getName() == "Switch")
                        {
                            Switch *sw = dc->as<Switch> ();
                            if (sw->getConfig())
                            {
                                newModule->par("ct_marker") = ConfigurationUtils::mac2long(sw->getConfig()->getCtMarker());
                                newModule->par("ct_mask") = ConfigurationUtils::mac2long(sw->getConfig()->getCtMask());
                            }
                        }
                        else if (dc->eClass()->getName() == "EndSystem")
                        {
                            EndSystem *es = dc->as<EndSystem> ();
                            if (es->getConfig())
                            {
                                newModule->par("ct_marker") = ConfigurationUtils::mac2long(es->getConfig()->getCtMarker());
                                newModule->par("ct_mask") = ConfigurationUtils::mac2long(es->getConfig()->getCtMask());
                            }
                        }

                    //Register Incoming at Ports
                    //destination Ports
                    EList<Port>& incomingportList = incoming->getRefInPort();
                    for (unsigned int l = 0; l < incomingportList.size(); l++)
                    {
                        Port_ptr incomingport = incomingportList.get(l);
                        string portName = ConfigurationUtils::getPortName(incomingport, nc->getRefMappings());
                        int ctID = ConfigurationUtils::getVLid(vls->getRefVirtualLink(), nc->getRefMappings());
                        if (portName.find("PHY") != string::npos)
                        {
                            Port_ptr incomingport = incomingportList.get(l);
                            int iport = ConfigurationUtils::getPortSerialNumber(incomingport, nc->getRefMappings());
                            if (iport >= 0)
                                ((TTEInput*) getParentModule()->getSubmodule("phy", iport)->getSubmodule("tteInput"))->addIncoming(
                                        ctID, (Incoming*) newCTCModule);
                        }
                        else if (portName == "SYNC")
                        {

                        }
                        else if (portName == "HOST")
                        {
                            ((TTEApplicationBase*) getParentModule()->getSubmodule("tteApp"))->addIncoming(
                                        ctID, (Incoming*) newCTCModule);
                        }
                        else
                        {

                        }
                    }

                    //destination Ports
                    EList<Port>& outgoingportList = outgoing->getRefOutPort();
                    for (unsigned int m = 0; m < outgoingportList.size(); m++)
                    {
                        Port_ptr outgoingport = outgoingportList.get(m);
                        string portName = ConfigurationUtils::getPortName(outgoingport, nc->getRefMappings());
                        int oport = ConfigurationUtils::getPortSerialNumber(outgoingport, nc->getRefMappings());
                        cModule *destModule;
                        //TODO fix parsing of porttype attribute and use it
                        if (portName.find("PHY") != string::npos)
                        {
                            destModule = getParentModule()->getSubmodule("phy", oport);
                        }
                        else if (portName == "SYNC")
                        {
                            destModule = getParentModule()->getSubmodule("sync", oport);
                        }
                        else if (portName == "HOST")
                        {
                            destModule = getParentModule()->getSubmodule("tteApp", oport);
                        }
                        else
                        {
                            ev << portName << ":" << oport << endl << endl;
                            continue;
                        }

                        if (outgoing->eClass()->getName() == "TTOutgoing")
                        {
                            TTBuffer *ttbuffer = dynamic_cast<TTBuffer*> (newModule);
                            ttbuffer->addDestinationGate(destModule->gate("TTin"));
                            if (((TTEOutput *) destModule->getSubmodule("tteOutput")))
                            {
                                ((TTEOutput *) destModule->getSubmodule("tteOutput"))->registerTTBuffer(ttbuffer);
                            }
                        }
                        else if (outgoing->eClass()->getName() == "RCOutgoing")
                        {
                            ((TTEthernetModel::Buffer*) newModule)->addDestinationGate(destModule->gate("RCin"));
                        }
                    }

                    //generate connections
                    newCTCModule->gate("out")->connectTo(newModule->gate("in"));

                    newModule->finalizeParameters();
                    newModule->buildInside();
                    newModule->callInitialize();
                }

            }
        }
        //Generate start message to delete module
        scheduleAt(simTime(), new cMessage("Delete Module"));
    }
}

void BufferManager::handleMessage(cMessage *msg)
{
    //delete module on first message, it is not needed anymore;
    delete msg;
    deleteModule();
}

} //namespace
