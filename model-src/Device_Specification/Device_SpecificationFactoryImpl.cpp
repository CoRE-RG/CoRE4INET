// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/Device_SpecificationFactoryImpl.cpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Device_Specification/Device_SpecificationFactory.hpp>
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/DeviceSpecification.hpp>
#include <Device_Specification/EndSystem.hpp>
#include <Device_Specification/Switch.hpp>
#include <Device_Specification/DeviceConfig.hpp>
#include <Device_Specification/EndSystemConfig.hpp>
#include <Device_Specification/ExternalClockSynchronization.hpp>
#include <Device_Specification/SwitchConfig.hpp>
#include <Device_Specification/BagAccounts.hpp>
#include <Device_Specification/BagAccount.hpp>
#include <Device_Specification/IncomingBagAccount.hpp>
#include <Device_Specification/OutgoingBagAccount.hpp>
#include <Device_Specification/VirtualLinkSchedules.hpp>
#include <Device_Specification/VirtualLinkSchedule.hpp>
#include <Device_Specification/Buffers.hpp>
#include <Device_Specification/Buffer.hpp>
#include <Device_Specification/FIFOQueue.hpp>
#include <Device_Specification/SingleEntryBuffer.hpp>
#include <Device_Specification/DualEntryBuffer.hpp>
#include <Device_Specification/TripleEntryBuffer.hpp>
#include <Device_Specification/Incoming.hpp>
#include <Device_Specification/CTIncoming.hpp>
#include <Device_Specification/Outgoing.hpp>
#include <Device_Specification/RCIncoming.hpp>
#include <Device_Specification/TTIncoming.hpp>
#include <Device_Specification/BEIncoming.hpp>
#include <Device_Specification/RCOutgoing.hpp>
#include <Device_Specification/CTOutgoing.hpp>
#include <Device_Specification/TTOutgoing.hpp>
#include <Device_Specification/BEOutgoing.hpp>
#include <Device_Specification/BestEffortRouting.hpp>
#include <Device_Specification/BERouteIncoming.hpp>
#include <Device_Specification/BERouteOutgoing.hpp>
#include <Device_Specification/FlowControl.hpp>
#include <Device_Specification/FlowControlValue.hpp>
#include <Device_Specification/TriggerSchedules.hpp>
#include <Device_Specification/TriggerSchedule.hpp>
#include <Device_Specification/IntegrityCheck.hpp>
#include <Device_Specification/RedundancyManagement.hpp>
#include <Device_Specification/RCRedundancyManagement.hpp>
#include <Device_Specification/TTRedundancyManagement.hpp>
#include <Device_Specification/Periods.hpp>
#include <Device_Specification/FrameRelayDescriptor.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

Device_SpecificationFactory::Device_SpecificationFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr Device_SpecificationFactory::create(
        ::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case Device_SpecificationPackage::DEVICESPECIFICATION:
        return createDeviceSpecification();
    case Device_SpecificationPackage::ENDSYSTEM:
        return createEndSystem();
    case Device_SpecificationPackage::SWITCH:
        return createSwitch();
    case Device_SpecificationPackage::DEVICECONFIG:
        return createDeviceConfig();
    case Device_SpecificationPackage::ENDSYSTEMCONFIG:
        return createEndSystemConfig();
    case Device_SpecificationPackage::EXTERNALCLOCKSYNCHRONIZATION:
        return createExternalClockSynchronization();
    case Device_SpecificationPackage::SWITCHCONFIG:
        return createSwitchConfig();
    case Device_SpecificationPackage::BAGACCOUNTS:
        return createBagAccounts();
    case Device_SpecificationPackage::BAGACCOUNT:
        return createBagAccount();
    case Device_SpecificationPackage::INCOMINGBAGACCOUNT:
        return createIncomingBagAccount();
    case Device_SpecificationPackage::OUTGOINGBAGACCOUNT:
        return createOutgoingBagAccount();
    case Device_SpecificationPackage::VIRTUALLINKSCHEDULES:
        return createVirtualLinkSchedules();
    case Device_SpecificationPackage::VIRTUALLINKSCHEDULE:
        return createVirtualLinkSchedule();
    case Device_SpecificationPackage::BUFFERS:
        return createBuffers();
    case Device_SpecificationPackage::BUFFER:
        return createBuffer();
    case Device_SpecificationPackage::FIFOQUEUE:
        return createFIFOQueue();
    case Device_SpecificationPackage::SINGLEENTRYBUFFER:
        return createSingleEntryBuffer();
    case Device_SpecificationPackage::DUALENTRYBUFFER:
        return createDualEntryBuffer();
    case Device_SpecificationPackage::TRIPLEENTRYBUFFER:
        return createTripleEntryBuffer();
    case Device_SpecificationPackage::INCOMING:
        return createIncoming();
    case Device_SpecificationPackage::CTINCOMING:
        return createCTIncoming();
    case Device_SpecificationPackage::OUTGOING:
        return createOutgoing();
    case Device_SpecificationPackage::RCINCOMING:
        return createRCIncoming();
    case Device_SpecificationPackage::TTINCOMING:
        return createTTIncoming();
    case Device_SpecificationPackage::BEINCOMING:
        return createBEIncoming();
    case Device_SpecificationPackage::RCOUTGOING:
        return createRCOutgoing();
    case Device_SpecificationPackage::CTOUTGOING:
        return createCTOutgoing();
    case Device_SpecificationPackage::TTOUTGOING:
        return createTTOutgoing();
    case Device_SpecificationPackage::BEOUTGOING:
        return createBEOutgoing();
    case Device_SpecificationPackage::BESTEFFORTROUTING:
        return createBestEffortRouting();
    case Device_SpecificationPackage::BEROUTEINCOMING:
        return createBERouteIncoming();
    case Device_SpecificationPackage::BEROUTEOUTGOING:
        return createBERouteOutgoing();
    case Device_SpecificationPackage::FLOWCONTROL:
        return createFlowControl();
    case Device_SpecificationPackage::FLOWCONTROLVALUE:
        return createFlowControlValue();
    case Device_SpecificationPackage::TRIGGERSCHEDULES:
        return createTriggerSchedules();
    case Device_SpecificationPackage::TRIGGERSCHEDULE:
        return createTriggerSchedule();
    case Device_SpecificationPackage::INTEGRITYCHECK:
        return createIntegrityCheck();
    case Device_SpecificationPackage::REDUNDANCYMANAGEMENT:
        return createRedundancyManagement();
    case Device_SpecificationPackage::RCREDUNDANCYMANAGEMENT:
        return createRCRedundancyManagement();
    case Device_SpecificationPackage::TTREDUNDANCYMANAGEMENT:
        return createTTRedundancyManagement();
    case Device_SpecificationPackage::PERIODS:
        return createPeriods();
    case Device_SpecificationPackage::FRAMERELAYDESCRIPTOR:
        return createFrameRelayDescriptor();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject Device_SpecificationFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Device_SpecificationPackage::CONSTRAINTYPE:
    {
        ::ecore::EJavaObject _any;
        Device_SpecificationPackage_ptr
                _epkg =
                        dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (getEPackage());
        return _epkg->getConstrainType()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    case Device_SpecificationPackage::TIMESOURCEENUM:
    {
        ::ecore::EJavaObject _any;
        Device_SpecificationPackage_ptr
                _epkg =
                        dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (getEPackage());
        return _epkg->getTimeSourceEnum()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString Device_SpecificationFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Device_SpecificationPackage::CONSTRAINTYPE:
    {
        Device_SpecificationPackage_ptr _epkg =
                ::Device_Specification::instanceOf<
                        ::Device_Specification::Device_SpecificationPackage >(
                        getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getConstrainType()->getEEnumLiteral(_value)->getName();
    }
    case Device_SpecificationPackage::TIMESOURCEENUM:
    {
        Device_SpecificationPackage_ptr _epkg =
                ::Device_Specification::instanceOf<
                        ::Device_Specification::Device_SpecificationPackage >(
                        getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getTimeSourceEnum()->getEEnumLiteral(_value)->getName();
    }
    default:
        throw "IllegalArgumentException";
    }
}

DeviceSpecification_ptr Device_SpecificationFactory::createDeviceSpecification()
{
    return new DeviceSpecification();
}
EndSystem_ptr Device_SpecificationFactory::createEndSystem()
{
    return new EndSystem();
}
Switch_ptr Device_SpecificationFactory::createSwitch()
{
    return new Switch();
}
DeviceConfig_ptr Device_SpecificationFactory::createDeviceConfig()
{
    return new DeviceConfig();
}
EndSystemConfig_ptr Device_SpecificationFactory::createEndSystemConfig()
{
    return new EndSystemConfig();
}
ExternalClockSynchronization_ptr Device_SpecificationFactory::createExternalClockSynchronization()
{
    return new ExternalClockSynchronization();
}
SwitchConfig_ptr Device_SpecificationFactory::createSwitchConfig()
{
    return new SwitchConfig();
}
BagAccounts_ptr Device_SpecificationFactory::createBagAccounts()
{
    return new BagAccounts();
}
BagAccount_ptr Device_SpecificationFactory::createBagAccount()
{
    return new BagAccount();
}
IncomingBagAccount_ptr Device_SpecificationFactory::createIncomingBagAccount()
{
    return new IncomingBagAccount();
}
OutgoingBagAccount_ptr Device_SpecificationFactory::createOutgoingBagAccount()
{
    return new OutgoingBagAccount();
}
VirtualLinkSchedules_ptr Device_SpecificationFactory::createVirtualLinkSchedules()
{
    return new VirtualLinkSchedules();
}
VirtualLinkSchedule_ptr Device_SpecificationFactory::createVirtualLinkSchedule()
{
    return new VirtualLinkSchedule();
}
Buffers_ptr Device_SpecificationFactory::createBuffers()
{
    return new Buffers();
}
Buffer_ptr Device_SpecificationFactory::createBuffer()
{
    return new Buffer();
}
FIFOQueue_ptr Device_SpecificationFactory::createFIFOQueue()
{
    return new FIFOQueue();
}
SingleEntryBuffer_ptr Device_SpecificationFactory::createSingleEntryBuffer()
{
    return new SingleEntryBuffer();
}
DualEntryBuffer_ptr Device_SpecificationFactory::createDualEntryBuffer()
{
    return new DualEntryBuffer();
}
TripleEntryBuffer_ptr Device_SpecificationFactory::createTripleEntryBuffer()
{
    return new TripleEntryBuffer();
}
Incoming_ptr Device_SpecificationFactory::createIncoming()
{
    return new Incoming();
}
CTIncoming_ptr Device_SpecificationFactory::createCTIncoming()
{
    return new CTIncoming();
}
Outgoing_ptr Device_SpecificationFactory::createOutgoing()
{
    return new Outgoing();
}
RCIncoming_ptr Device_SpecificationFactory::createRCIncoming()
{
    return new RCIncoming();
}
TTIncoming_ptr Device_SpecificationFactory::createTTIncoming()
{
    return new TTIncoming();
}
BEIncoming_ptr Device_SpecificationFactory::createBEIncoming()
{
    return new BEIncoming();
}
RCOutgoing_ptr Device_SpecificationFactory::createRCOutgoing()
{
    return new RCOutgoing();
}
CTOutgoing_ptr Device_SpecificationFactory::createCTOutgoing()
{
    return new CTOutgoing();
}
TTOutgoing_ptr Device_SpecificationFactory::createTTOutgoing()
{
    return new TTOutgoing();
}
BEOutgoing_ptr Device_SpecificationFactory::createBEOutgoing()
{
    return new BEOutgoing();
}
BestEffortRouting_ptr Device_SpecificationFactory::createBestEffortRouting()
{
    return new BestEffortRouting();
}
BERouteIncoming_ptr Device_SpecificationFactory::createBERouteIncoming()
{
    return new BERouteIncoming();
}
BERouteOutgoing_ptr Device_SpecificationFactory::createBERouteOutgoing()
{
    return new BERouteOutgoing();
}
FlowControl_ptr Device_SpecificationFactory::createFlowControl()
{
    return new FlowControl();
}
FlowControlValue_ptr Device_SpecificationFactory::createFlowControlValue()
{
    return new FlowControlValue();
}
TriggerSchedules_ptr Device_SpecificationFactory::createTriggerSchedules()
{
    return new TriggerSchedules();
}
TriggerSchedule_ptr Device_SpecificationFactory::createTriggerSchedule()
{
    return new TriggerSchedule();
}
IntegrityCheck_ptr Device_SpecificationFactory::createIntegrityCheck()
{
    return new IntegrityCheck();
}
RedundancyManagement_ptr Device_SpecificationFactory::createRedundancyManagement()
{
    return new RedundancyManagement();
}
RCRedundancyManagement_ptr Device_SpecificationFactory::createRCRedundancyManagement()
{
    return new RCRedundancyManagement();
}
TTRedundancyManagement_ptr Device_SpecificationFactory::createTTRedundancyManagement()
{
    return new TTRedundancyManagement();
}
Periods_ptr Device_SpecificationFactory::createPeriods()
{
    return new Periods();
}
FrameRelayDescriptor_ptr Device_SpecificationFactory::createFrameRelayDescriptor()
{
    return new FrameRelayDescriptor();
}

