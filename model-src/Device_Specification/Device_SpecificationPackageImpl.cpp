// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/Device_SpecificationPackageImpl.cpp
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

#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/Device_SpecificationFactory.hpp>
#include <ecore.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EAttribute.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EOperation.hpp>
#include <ecore/EParameter.hpp>
#include <ecore/EEnum.hpp>
#include <ecore/EEnumLiteral.hpp>
#include <ecore/EDataType.hpp>
#include <ecore/EGenericType.hpp>
#include <ecore/ETypeParameter.hpp>
#include <ecore/EcorePackage.hpp>
#include <System_Specification/System_SpecificationPackage.hpp>
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <Device_Target_Mapping/DeviceMapping.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <System_Specification/Port.hpp>
#include <System_Specification/Period.hpp>

using namespace ::Device_Specification;

Device_SpecificationPackage::Device_SpecificationPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = Device_SpecificationFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // DeviceSpecification
    m_DeviceSpecificationEClass = new ::ecore::EClass();
    m_DeviceSpecificationEClass->setClassifierID(DEVICESPECIFICATION);
    m_DeviceSpecificationEClass->setEPackage(this);
    getEClassifiers().push_back(m_DeviceSpecificationEClass);
    m_DeviceSpecification__metaInformation = new ::ecore::EReference();
    m_DeviceSpecification__metaInformation->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__METAINFORMATION);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__metaInformation);
    m_DeviceSpecification__units = new ::ecore::EReference();
    m_DeviceSpecification__units->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__UNITS);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__units);
    m_DeviceSpecification__bagAccounts = new ::ecore::EReference();
    m_DeviceSpecification__bagAccounts->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BAGACCOUNTS);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__bagAccounts);
    m_DeviceSpecification__vlSchedules = new ::ecore::EReference();
    m_DeviceSpecification__vlSchedules->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__VLSCHEDULES);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__vlSchedules);
    m_DeviceSpecification__bestEffortRouting = new ::ecore::EReference();
    m_DeviceSpecification__bestEffortRouting->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BESTEFFORTROUTING);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__bestEffortRouting);
    m_DeviceSpecification__flowControl = new ::ecore::EReference();
    m_DeviceSpecification__flowControl->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__FLOWCONTROL);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__flowControl);
    m_DeviceSpecification__periods = new ::ecore::EReference();
    m_DeviceSpecification__periods->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__PERIODS);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__periods);
    m_DeviceSpecification__refDeviceMapping = new ::ecore::EReference();
    m_DeviceSpecification__refDeviceMapping->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__REFDEVICEMAPPING);
    m_DeviceSpecificationEClass->getEStructuralFeatures().push_back(
            m_DeviceSpecification__refDeviceMapping);

    // EndSystem
    m_EndSystemEClass = new ::ecore::EClass();
    m_EndSystemEClass->setClassifierID(ENDSYSTEM);
    m_EndSystemEClass->setEPackage(this);
    getEClassifiers().push_back(m_EndSystemEClass);
    m_EndSystem__config = new ::ecore::EReference();
    m_EndSystem__config->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__CONFIG);
    m_EndSystemEClass->getEStructuralFeatures().push_back(m_EndSystem__config);
    m_EndSystem__triggerSchedules = new ::ecore::EReference();
    m_EndSystem__triggerSchedules->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__TRIGGERSCHEDULES);
    m_EndSystemEClass->getEStructuralFeatures().push_back(
            m_EndSystem__triggerSchedules);

    // Switch
    m_SwitchEClass = new ::ecore::EClass();
    m_SwitchEClass->setClassifierID(SWITCH);
    m_SwitchEClass->setEPackage(this);
    getEClassifiers().push_back(m_SwitchEClass);
    m_Switch__config = new ::ecore::EReference();
    m_Switch__config->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::SWITCH__CONFIG);
    m_SwitchEClass->getEStructuralFeatures().push_back(m_Switch__config);

    // DeviceConfig
    m_DeviceConfigEClass = new ::ecore::EClass();
    m_DeviceConfigEClass->setClassifierID(DEVICECONFIG);
    m_DeviceConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_DeviceConfigEClass);
    m_DeviceConfig__ctMarker = new ::ecore::EAttribute();
    m_DeviceConfig__ctMarker->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMARKER);
    m_DeviceConfigEClass->getEStructuralFeatures().push_back(
            m_DeviceConfig__ctMarker);
    m_DeviceConfig__ctMask = new ::ecore::EAttribute();
    m_DeviceConfig__ctMask->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMASK);
    m_DeviceConfigEClass->getEStructuralFeatures().push_back(
            m_DeviceConfig__ctMask);

    // EndSystemConfig
    m_EndSystemConfigEClass = new ::ecore::EClass();
    m_EndSystemConfigEClass->setClassifierID(ENDSYSTEMCONFIG);
    m_EndSystemConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_EndSystemConfigEClass);
    m_EndSystemConfig__tsSource = new ::ecore::EAttribute();
    m_EndSystemConfig__tsSource->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__TSSOURCE);
    m_EndSystemConfigEClass->getEStructuralFeatures().push_back(
            m_EndSystemConfig__tsSource);
    m_EndSystemConfig__sourceMacAddress = new ::ecore::EAttribute();
    m_EndSystemConfig__sourceMacAddress->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__SOURCEMACADDRESS);
    m_EndSystemConfigEClass->getEStructuralFeatures().push_back(
            m_EndSystemConfig__sourceMacAddress);
    m_EndSystemConfig__destMacAddressCF = new ::ecore::EAttribute();
    m_EndSystemConfig__destMacAddressCF->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__DESTMACADDRESSCF);
    m_EndSystemConfigEClass->getEStructuralFeatures().push_back(
            m_EndSystemConfig__destMacAddressCF);
    m_EndSystemConfig__externalSyncAckRequired = new ::ecore::EAttribute();
    m_EndSystemConfig__externalSyncAckRequired->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALSYNCACKREQUIRED);
    m_EndSystemConfigEClass->getEStructuralFeatures().push_back(
            m_EndSystemConfig__externalSyncAckRequired);
    m_EndSystemConfig__externalClockSynchronization = new ::ecore::EReference();
    m_EndSystemConfig__externalClockSynchronization->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALCLOCKSYNCHRONIZATION);
    m_EndSystemConfigEClass->getEStructuralFeatures().push_back(
            m_EndSystemConfig__externalClockSynchronization);

    // ExternalClockSynchronization
    m_ExternalClockSynchronizationEClass = new ::ecore::EClass();
    m_ExternalClockSynchronizationEClass->setClassifierID(
            EXTERNALCLOCKSYNCHRONIZATION);
    m_ExternalClockSynchronizationEClass->setEPackage(this);
    getEClassifiers().push_back(m_ExternalClockSynchronizationEClass);
    m_ExternalClockSynchronization__maxExtCorrValue = new ::ecore::EAttribute();
    m_ExternalClockSynchronization__maxExtCorrValue->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::EXTERNALCLOCKSYNCHRONIZATION__MAXEXTCORRVALUE);
    m_ExternalClockSynchronizationEClass->getEStructuralFeatures().push_back(
            m_ExternalClockSynchronization__maxExtCorrValue);

    // SwitchConfig
    m_SwitchConfigEClass = new ::ecore::EClass();
    m_SwitchConfigEClass->setClassifierID(SWITCHCONFIG);
    m_SwitchConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_SwitchConfigEClass);

    // BagAccounts
    m_BagAccountsEClass = new ::ecore::EClass();
    m_BagAccountsEClass->setClassifierID(BAGACCOUNTS);
    m_BagAccountsEClass->setEPackage(this);
    getEClassifiers().push_back(m_BagAccountsEClass);
    m_BagAccounts__incomingBagAccount = new ::ecore::EReference();
    m_BagAccounts__incomingBagAccount->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BAGACCOUNTS__INCOMINGBAGACCOUNT);
    m_BagAccountsEClass->getEStructuralFeatures().push_back(
            m_BagAccounts__incomingBagAccount);
    m_BagAccounts__outgoingBagAccount = new ::ecore::EReference();
    m_BagAccounts__outgoingBagAccount->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BAGACCOUNTS__OUTGOINGBAGACCOUNT);
    m_BagAccountsEClass->getEStructuralFeatures().push_back(
            m_BagAccounts__outgoingBagAccount);

    // BagAccount
    m_BagAccountEClass = new ::ecore::EClass();
    m_BagAccountEClass->setClassifierID(BAGACCOUNT);
    m_BagAccountEClass->setEPackage(this);
    getEClassifiers().push_back(m_BagAccountEClass);
    m_BagAccount__bag = new ::ecore::EAttribute();
    m_BagAccount__bag->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BAGACCOUNT__BAG);
    m_BagAccountEClass->getEStructuralFeatures().push_back(m_BagAccount__bag);
    m_BagAccount__jitter = new ::ecore::EAttribute();
    m_BagAccount__jitter->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BAGACCOUNT__JITTER);
    m_BagAccountEClass->getEStructuralFeatures().push_back(m_BagAccount__jitter);
    m_BagAccount__constrainType = new ::ecore::EAttribute();
    m_BagAccount__constrainType->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BAGACCOUNT__CONSTRAINTYPE);
    m_BagAccountEClass->getEStructuralFeatures().push_back(
            m_BagAccount__constrainType);

    // IncomingBagAccount
    m_IncomingBagAccountEClass = new ::ecore::EClass();
    m_IncomingBagAccountEClass->setClassifierID(INCOMINGBAGACCOUNT);
    m_IncomingBagAccountEClass->setEPackage(this);
    getEClassifiers().push_back(m_IncomingBagAccountEClass);

    // OutgoingBagAccount
    m_OutgoingBagAccountEClass = new ::ecore::EClass();
    m_OutgoingBagAccountEClass->setClassifierID(OUTGOINGBAGACCOUNT);
    m_OutgoingBagAccountEClass->setEPackage(this);
    getEClassifiers().push_back(m_OutgoingBagAccountEClass);

    // VirtualLinkSchedules
    m_VirtualLinkSchedulesEClass = new ::ecore::EClass();
    m_VirtualLinkSchedulesEClass->setClassifierID(VIRTUALLINKSCHEDULES);
    m_VirtualLinkSchedulesEClass->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinkSchedulesEClass);
    m_VirtualLinkSchedules__scheduleStartAfterSync = new ::ecore::EAttribute();
    m_VirtualLinkSchedules__scheduleStartAfterSync->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__SCHEDULESTARTAFTERSYNC);
    m_VirtualLinkSchedulesEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkSchedules__scheduleStartAfterSync);
    m_VirtualLinkSchedules__vlSchedule = new ::ecore::EReference();
    m_VirtualLinkSchedules__vlSchedule->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__VLSCHEDULE);
    m_VirtualLinkSchedulesEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkSchedules__vlSchedule);

    // VirtualLinkSchedule
    m_VirtualLinkScheduleEClass = new ::ecore::EClass();
    m_VirtualLinkScheduleEClass->setClassifierID(VIRTUALLINKSCHEDULE);
    m_VirtualLinkScheduleEClass->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinkScheduleEClass);
    m_VirtualLinkSchedule__priority = new ::ecore::EAttribute();
    m_VirtualLinkSchedule__priority->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__PRIORITY);
    m_VirtualLinkScheduleEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkSchedule__priority);
    m_VirtualLinkSchedule__refVirtualLink = new ::ecore::EReference();
    m_VirtualLinkSchedule__refVirtualLink->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__REFVIRTUALLINK);
    m_VirtualLinkScheduleEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkSchedule__refVirtualLink);
    m_VirtualLinkSchedule__incoming = new ::ecore::EReference();
    m_VirtualLinkSchedule__incoming->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__INCOMING);
    m_VirtualLinkScheduleEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkSchedule__incoming);

    // Buffers
    m_BuffersEClass = new ::ecore::EClass();
    m_BuffersEClass->setClassifierID(BUFFERS);
    m_BuffersEClass->setEPackage(this);
    getEClassifiers().push_back(m_BuffersEClass);
    m_Buffers__buffer = new ::ecore::EReference();
    m_Buffers__buffer->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BUFFERS__BUFFER);
    m_BuffersEClass->getEStructuralFeatures().push_back(m_Buffers__buffer);

    // Buffer
    m_BufferEClass = new ::ecore::EClass();
    m_BufferEClass->setClassifierID(BUFFER);
    m_BufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_BufferEClass);

    // FIFOQueue
    m_FIFOQueueEClass = new ::ecore::EClass();
    m_FIFOQueueEClass->setClassifierID(FIFOQUEUE);
    m_FIFOQueueEClass->setEPackage(this);
    getEClassifiers().push_back(m_FIFOQueueEClass);
    m_FIFOQueue__length = new ::ecore::EAttribute();
    m_FIFOQueue__length->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::FIFOQUEUE__LENGTH);
    m_FIFOQueueEClass->getEStructuralFeatures().push_back(m_FIFOQueue__length);

    // SingleEntryBuffer
    m_SingleEntryBufferEClass = new ::ecore::EClass();
    m_SingleEntryBufferEClass->setClassifierID(SINGLEENTRYBUFFER);
    m_SingleEntryBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_SingleEntryBufferEClass);

    // DualEntryBuffer
    m_DualEntryBufferEClass = new ::ecore::EClass();
    m_DualEntryBufferEClass->setClassifierID(DUALENTRYBUFFER);
    m_DualEntryBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_DualEntryBufferEClass);

    // TripleEntryBuffer
    m_TripleEntryBufferEClass = new ::ecore::EClass();
    m_TripleEntryBufferEClass->setClassifierID(TRIPLEENTRYBUFFER);
    m_TripleEntryBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_TripleEntryBufferEClass);

    // Incoming
    m_IncomingEClass = new ::ecore::EClass();
    m_IncomingEClass->setClassifierID(INCOMING);
    m_IncomingEClass->setEPackage(this);
    getEClassifiers().push_back(m_IncomingEClass);
    m_Incoming__outgoing = new ::ecore::EReference();
    m_Incoming__outgoing->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::INCOMING__OUTGOING);
    m_IncomingEClass->getEStructuralFeatures().push_back(m_Incoming__outgoing);
    m_Incoming__refInPort = new ::ecore::EReference();
    m_Incoming__refInPort->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::INCOMING__REFINPORT);
    m_IncomingEClass->getEStructuralFeatures().push_back(m_Incoming__refInPort);

    // CTIncoming
    m_CTIncomingEClass = new ::ecore::EClass();
    m_CTIncomingEClass->setClassifierID(CTINCOMING);
    m_CTIncomingEClass->setEPackage(this);
    getEClassifiers().push_back(m_CTIncomingEClass);
    m_CTIncoming__removeSequenceNumber = new ::ecore::EAttribute();
    m_CTIncoming__removeSequenceNumber->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REMOVESEQUENCENUMBER);
    m_CTIncomingEClass->getEStructuralFeatures().push_back(
            m_CTIncoming__removeSequenceNumber);
    m_CTIncoming__redundancyFunction = new ::ecore::EReference();
    m_CTIncoming__redundancyFunction->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REDUNDANCYFUNCTION);
    m_CTIncomingEClass->getEStructuralFeatures().push_back(
            m_CTIncoming__redundancyFunction);

    // Outgoing
    m_OutgoingEClass = new ::ecore::EClass();
    m_OutgoingEClass->setClassifierID(OUTGOING);
    m_OutgoingEClass->setEPackage(this);
    getEClassifiers().push_back(m_OutgoingEClass);
    m_Outgoing__appendSequenceNumber = new ::ecore::EAttribute();
    m_Outgoing__appendSequenceNumber->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::OUTGOING__APPENDSEQUENCENUMBER);
    m_OutgoingEClass->getEStructuralFeatures().push_back(
            m_Outgoing__appendSequenceNumber);
    m_Outgoing__refOutPort = new ::ecore::EReference();
    m_Outgoing__refOutPort->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::OUTGOING__REFOUTPORT);
    m_OutgoingEClass->getEStructuralFeatures().push_back(m_Outgoing__refOutPort);

    // RCIncoming
    m_RCIncomingEClass = new ::ecore::EClass();
    m_RCIncomingEClass->setClassifierID(RCINCOMING);
    m_RCIncomingEClass->setEPackage(this);
    getEClassifiers().push_back(m_RCIncomingEClass);
    m_RCIncoming__refBagAccount = new ::ecore::EReference();
    m_RCIncoming__refBagAccount->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::RCINCOMING__REFBAGACCOUNT);
    m_RCIncomingEClass->getEStructuralFeatures().push_back(
            m_RCIncoming__refBagAccount);

    // TTIncoming
    m_TTIncomingEClass = new ::ecore::EClass();
    m_TTIncomingEClass->setClassifierID(TTINCOMING);
    m_TTIncomingEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTIncomingEClass);
    m_TTIncoming__receiveWindowStart = new ::ecore::EAttribute();
    m_TTIncoming__receiveWindowStart->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWSTART);
    m_TTIncomingEClass->getEStructuralFeatures().push_back(
            m_TTIncoming__receiveWindowStart);
    m_TTIncoming__receiveWindowEnd = new ::ecore::EAttribute();
    m_TTIncoming__receiveWindowEnd->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWEND);
    m_TTIncomingEClass->getEStructuralFeatures().push_back(
            m_TTIncoming__receiveWindowEnd);
    m_TTIncoming__permanencePit = new ::ecore::EAttribute();
    m_TTIncoming__permanencePit->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TTINCOMING__PERMANENCEPIT);
    m_TTIncomingEClass->getEStructuralFeatures().push_back(
            m_TTIncoming__permanencePit);
    m_TTIncoming__refPeriod = new ::ecore::EReference();
    m_TTIncoming__refPeriod->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TTINCOMING__REFPERIOD);
    m_TTIncomingEClass->getEStructuralFeatures().push_back(
            m_TTIncoming__refPeriod);

    // BEIncoming
    m_BEIncomingEClass = new ::ecore::EClass();
    m_BEIncomingEClass->setClassifierID(BEINCOMING);
    m_BEIncomingEClass->setEPackage(this);
    getEClassifiers().push_back(m_BEIncomingEClass);

    // RCOutgoing
    m_RCOutgoingEClass = new ::ecore::EClass();
    m_RCOutgoingEClass->setClassifierID(RCOUTGOING);
    m_RCOutgoingEClass->setEPackage(this);
    getEClassifiers().push_back(m_RCOutgoingEClass);
    m_RCOutgoing__maxDispatchDelay = new ::ecore::EAttribute();
    m_RCOutgoing__maxDispatchDelay->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::RCOUTGOING__MAXDISPATCHDELAY);
    m_RCOutgoingEClass->getEStructuralFeatures().push_back(
            m_RCOutgoing__maxDispatchDelay);
    m_RCOutgoing__refBagAccount = new ::ecore::EReference();
    m_RCOutgoing__refBagAccount->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::RCOUTGOING__REFBAGACCOUNT);
    m_RCOutgoingEClass->getEStructuralFeatures().push_back(
            m_RCOutgoing__refBagAccount);

    // CTOutgoing
    m_CTOutgoingEClass = new ::ecore::EClass();
    m_CTOutgoingEClass->setClassifierID(CTOUTGOING);
    m_CTOutgoingEClass->setEPackage(this);
    getEClassifiers().push_back(m_CTOutgoingEClass);

    // TTOutgoing
    m_TTOutgoingEClass = new ::ecore::EClass();
    m_TTOutgoingEClass->setClassifierID(TTOUTGOING);
    m_TTOutgoingEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTOutgoingEClass);
    m_TTOutgoing__sendWindowStart = new ::ecore::EAttribute();
    m_TTOutgoing__sendWindowStart->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWSTART);
    m_TTOutgoingEClass->getEStructuralFeatures().push_back(
            m_TTOutgoing__sendWindowStart);
    m_TTOutgoing__sendWindowEnd = new ::ecore::EAttribute();
    m_TTOutgoing__sendWindowEnd->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWEND);
    m_TTOutgoingEClass->getEStructuralFeatures().push_back(
            m_TTOutgoing__sendWindowEnd);
    m_TTOutgoing__refPeriod = new ::ecore::EReference();
    m_TTOutgoing__refPeriod->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__REFPERIOD);
    m_TTOutgoingEClass->getEStructuralFeatures().push_back(
            m_TTOutgoing__refPeriod);

    // BEOutgoing
    m_BEOutgoingEClass = new ::ecore::EClass();
    m_BEOutgoingEClass->setClassifierID(BEOUTGOING);
    m_BEOutgoingEClass->setEPackage(this);
    getEClassifiers().push_back(m_BEOutgoingEClass);

    // BestEffortRouting
    m_BestEffortRoutingEClass = new ::ecore::EClass();
    m_BestEffortRoutingEClass->setClassifierID(BESTEFFORTROUTING);
    m_BestEffortRoutingEClass->setEPackage(this);
    getEClassifiers().push_back(m_BestEffortRoutingEClass);
    m_BestEffortRouting__enableDynamicRouting = new ::ecore::EAttribute();
    m_BestEffortRouting__enableDynamicRouting->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BESTEFFORTROUTING__ENABLEDYNAMICROUTING);
    m_BestEffortRoutingEClass->getEStructuralFeatures().push_back(
            m_BestEffortRouting__enableDynamicRouting);
    m_BestEffortRouting__beRouteIncoming = new ::ecore::EReference();
    m_BestEffortRouting__beRouteIncoming->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BESTEFFORTROUTING__BEROUTEINCOMING);
    m_BestEffortRoutingEClass->getEStructuralFeatures().push_back(
            m_BestEffortRouting__beRouteIncoming);

    // BERouteIncoming
    m_BERouteIncomingEClass = new ::ecore::EClass();
    m_BERouteIncomingEClass->setClassifierID(BEROUTEINCOMING);
    m_BERouteIncomingEClass->setEPackage(this);
    getEClassifiers().push_back(m_BERouteIncomingEClass);
    m_BERouteIncoming__destinationMacAddress = new ::ecore::EAttribute();
    m_BERouteIncoming__destinationMacAddress->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BEROUTEINCOMING__DESTINATIONMACADDRESS);
    m_BERouteIncomingEClass->getEStructuralFeatures().push_back(
            m_BERouteIncoming__destinationMacAddress);
    m_BERouteIncoming__addrMask = new ::ecore::EAttribute();
    m_BERouteIncoming__addrMask->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::BEROUTEINCOMING__ADDRMASK);
    m_BERouteIncomingEClass->getEStructuralFeatures().push_back(
            m_BERouteIncoming__addrMask);

    // BERouteOutgoing
    m_BERouteOutgoingEClass = new ::ecore::EClass();
    m_BERouteOutgoingEClass->setClassifierID(BEROUTEOUTGOING);
    m_BERouteOutgoingEClass->setEPackage(this);
    getEClassifiers().push_back(m_BERouteOutgoingEClass);

    // FlowControl
    m_FlowControlEClass = new ::ecore::EClass();
    m_FlowControlEClass->setClassifierID(FLOWCONTROL);
    m_FlowControlEClass->setEPackage(this);
    getEClassifiers().push_back(m_FlowControlEClass);
    m_FlowControl__xon = new ::ecore::EReference();
    m_FlowControl__xon->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::FLOWCONTROL__XON);
    m_FlowControlEClass->getEStructuralFeatures().push_back(m_FlowControl__xon);
    m_FlowControl__xoff = new ::ecore::EReference();
    m_FlowControl__xoff->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::FLOWCONTROL__XOFF);
    m_FlowControlEClass->getEStructuralFeatures().push_back(m_FlowControl__xoff);

    // FlowControlValue
    m_FlowControlValueEClass = new ::ecore::EClass();
    m_FlowControlValueEClass->setClassifierID(FLOWCONTROLVALUE);
    m_FlowControlValueEClass->setEPackage(this);
    getEClassifiers().push_back(m_FlowControlValueEClass);
    m_FlowControlValue__value = new ::ecore::EAttribute();
    m_FlowControlValue__value->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::FLOWCONTROLVALUE__VALUE);
    m_FlowControlValueEClass->getEStructuralFeatures().push_back(
            m_FlowControlValue__value);
    m_FlowControlValue__threshold = new ::ecore::EAttribute();
    m_FlowControlValue__threshold->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::FLOWCONTROLVALUE__THRESHOLD);
    m_FlowControlValueEClass->getEStructuralFeatures().push_back(
            m_FlowControlValue__threshold);

    // TriggerSchedules
    m_TriggerSchedulesEClass = new ::ecore::EClass();
    m_TriggerSchedulesEClass->setClassifierID(TRIGGERSCHEDULES);
    m_TriggerSchedulesEClass->setEPackage(this);
    getEClassifiers().push_back(m_TriggerSchedulesEClass);
    m_TriggerSchedules__triggerSchedule = new ::ecore::EReference();
    m_TriggerSchedules__triggerSchedule->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TRIGGERSCHEDULES__TRIGGERSCHEDULE);
    m_TriggerSchedulesEClass->getEStructuralFeatures().push_back(
            m_TriggerSchedules__triggerSchedule);

    // TriggerSchedule
    m_TriggerScheduleEClass = new ::ecore::EClass();
    m_TriggerScheduleEClass->setClassifierID(TRIGGERSCHEDULE);
    m_TriggerScheduleEClass->setEPackage(this);
    getEClassifiers().push_back(m_TriggerScheduleEClass);
    m_TriggerSchedule__refPeriod = new ::ecore::EReference();
    m_TriggerSchedule__refPeriod->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::TRIGGERSCHEDULE__REFPERIOD);
    m_TriggerScheduleEClass->getEStructuralFeatures().push_back(
            m_TriggerSchedule__refPeriod);

    // IntegrityCheck
    m_IntegrityCheckEClass = new ::ecore::EClass();
    m_IntegrityCheckEClass->setClassifierID(INTEGRITYCHECK);
    m_IntegrityCheckEClass->setEPackage(this);
    getEClassifiers().push_back(m_IntegrityCheckEClass);

    // RedundancyManagement
    m_RedundancyManagementEClass = new ::ecore::EClass();
    m_RedundancyManagementEClass->setClassifierID(REDUNDANCYMANAGEMENT);
    m_RedundancyManagementEClass->setEPackage(this);
    getEClassifiers().push_back(m_RedundancyManagementEClass);
    m_RedundancyManagement__redundancyTimeout = new ::ecore::EAttribute();
    m_RedundancyManagement__redundancyTimeout->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::REDUNDANCYMANAGEMENT__REDUNDANCYTIMEOUT);
    m_RedundancyManagementEClass->getEStructuralFeatures().push_back(
            m_RedundancyManagement__redundancyTimeout);

    // RCRedundancyManagement
    m_RCRedundancyManagementEClass = new ::ecore::EClass();
    m_RCRedundancyManagementEClass->setClassifierID(RCREDUNDANCYMANAGEMENT);
    m_RCRedundancyManagementEClass->setEPackage(this);
    getEClassifiers().push_back(m_RCRedundancyManagementEClass);
    m_RCRedundancyManagement__maxSequenceNumberRange
            = new ::ecore::EAttribute();
    m_RCRedundancyManagement__maxSequenceNumberRange->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::RCREDUNDANCYMANAGEMENT__MAXSEQUENCENUMBERRANGE);
    m_RCRedundancyManagementEClass->getEStructuralFeatures().push_back(
            m_RCRedundancyManagement__maxSequenceNumberRange);

    // TTRedundancyManagement
    m_TTRedundancyManagementEClass = new ::ecore::EClass();
    m_TTRedundancyManagementEClass->setClassifierID(TTREDUNDANCYMANAGEMENT);
    m_TTRedundancyManagementEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTRedundancyManagementEClass);

    // Periods
    m_PeriodsEClass = new ::ecore::EClass();
    m_PeriodsEClass->setClassifierID(PERIODS);
    m_PeriodsEClass->setEPackage(this);
    getEClassifiers().push_back(m_PeriodsEClass);
    m_Periods__period = new ::ecore::EReference();
    m_Periods__period->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::PERIODS__PERIOD);
    m_PeriodsEClass->getEStructuralFeatures().push_back(m_Periods__period);

    // FrameRelayDescriptor
    m_FrameRelayDescriptorEClass = new ::ecore::EClass();
    m_FrameRelayDescriptorEClass->setClassifierID(FRAMERELAYDESCRIPTOR);
    m_FrameRelayDescriptorEClass->setEPackage(this);
    getEClassifiers().push_back(m_FrameRelayDescriptorEClass);
    m_FrameRelayDescriptor__bufferDepth = new ::ecore::EAttribute();
    m_FrameRelayDescriptor__bufferDepth->setFeatureID(
            ::Device_Specification::Device_SpecificationPackage::FRAMERELAYDESCRIPTOR__BUFFERDEPTH);
    m_FrameRelayDescriptorEClass->getEStructuralFeatures().push_back(
            m_FrameRelayDescriptor__bufferDepth);

    // Create enums

    m_ConstrainTypeEEnum = new ::ecore::EEnum();
    m_ConstrainTypeEEnum->setClassifierID(CONSTRAINTYPE);
    m_ConstrainTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_ConstrainTypeEEnum);

    m_TimeSourceEnumEEnum = new ::ecore::EEnum();
    m_TimeSourceEnumEEnum->setClassifierID(TIMESOURCEENUM);
    m_TimeSourceEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_TimeSourceEnumEEnum);

    // Create data types


    // Initialize package
    setName("Device_Specification");
    setNsPrefix("ds");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/Device_Specification_V1");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_DeviceSpecificationEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_EndSystemEClass->getESuperTypes().push_back(m_DeviceSpecificationEClass);
    m_SwitchEClass->getESuperTypes().push_back(m_DeviceSpecificationEClass);
    m_DeviceConfigEClass->getESuperTypes().push_back(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getENamedElement());
    m_EndSystemConfigEClass->getESuperTypes().push_back(m_DeviceConfigEClass);
    m_ExternalClockSynchronizationEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_SwitchConfigEClass->getESuperTypes().push_back(m_DeviceConfigEClass);
    m_BagAccountsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_BagAccountEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_IncomingBagAccountEClass->getESuperTypes().push_back(m_BagAccountEClass);
    m_OutgoingBagAccountEClass->getESuperTypes().push_back(m_BagAccountEClass);
    m_VirtualLinkSchedulesEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_VirtualLinkScheduleEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_BuffersEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_BufferEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_FIFOQueueEClass->getESuperTypes().push_back(m_BufferEClass);
    m_SingleEntryBufferEClass->getESuperTypes().push_back(m_BufferEClass);
    m_DualEntryBufferEClass->getESuperTypes().push_back(m_BufferEClass);
    m_TripleEntryBufferEClass->getESuperTypes().push_back(m_BufferEClass);
    m_IncomingEClass->getESuperTypes().push_back(m_FrameRelayDescriptorEClass);
    m_CTIncomingEClass->getESuperTypes().push_back(m_IncomingEClass);
    m_OutgoingEClass->getESuperTypes().push_back(m_FrameRelayDescriptorEClass);
    m_RCIncomingEClass->getESuperTypes().push_back(m_CTIncomingEClass);
    m_TTIncomingEClass->getESuperTypes().push_back(m_CTIncomingEClass);
    m_BEIncomingEClass->getESuperTypes().push_back(m_CTIncomingEClass);
    m_RCOutgoingEClass->getESuperTypes().push_back(m_CTOutgoingEClass);
    m_CTOutgoingEClass->getESuperTypes().push_back(m_OutgoingEClass);
    m_TTOutgoingEClass->getESuperTypes().push_back(m_CTOutgoingEClass);
    m_BEOutgoingEClass->getESuperTypes().push_back(m_CTOutgoingEClass);
    m_BestEffortRoutingEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_BERouteIncomingEClass->getESuperTypes().push_back(m_IncomingEClass);
    m_BERouteOutgoingEClass->getESuperTypes().push_back(m_OutgoingEClass);
    m_FlowControlEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_FlowControlValueEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_TriggerSchedulesEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_TriggerScheduleEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_IntegrityCheckEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_RedundancyManagementEClass->getESuperTypes().push_back(
            m_IntegrityCheckEClass);
    m_RCRedundancyManagementEClass->getESuperTypes().push_back(
            m_RedundancyManagementEClass);
    m_TTRedundancyManagementEClass->getESuperTypes().push_back(
            m_RedundancyManagementEClass);
    m_PeriodsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_FrameRelayDescriptorEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // DeviceSpecification
    m_DeviceSpecificationEClass->setName("DeviceSpecification");
    m_DeviceSpecificationEClass->setAbstract(true);
    m_DeviceSpecificationEClass->setInterface(false);
    m_DeviceSpecification__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_DeviceSpecification__metaInformation->setName("metaInformation");
    m_DeviceSpecification__metaInformation->setDefaultValueLiteral("");
    m_DeviceSpecification__metaInformation->setLowerBound(0);
    m_DeviceSpecification__metaInformation->setUpperBound(1);
    m_DeviceSpecification__metaInformation->setTransient(false);
    m_DeviceSpecification__metaInformation->setVolatile(false);
    m_DeviceSpecification__metaInformation->setChangeable(true);
    m_DeviceSpecification__metaInformation->setContainment(true);
    m_DeviceSpecification__metaInformation->setResolveProxies(true);
    m_DeviceSpecification__metaInformation->setUnique(true);
    m_DeviceSpecification__metaInformation->setDerived(false);
    m_DeviceSpecification__metaInformation->setOrdered(true);
    m_DeviceSpecification__units->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getUnits());
    m_DeviceSpecification__units->setName("units");
    m_DeviceSpecification__units->setDefaultValueLiteral("");
    m_DeviceSpecification__units->setLowerBound(0);
    m_DeviceSpecification__units->setUpperBound(1);
    m_DeviceSpecification__units->setTransient(false);
    m_DeviceSpecification__units->setVolatile(false);
    m_DeviceSpecification__units->setChangeable(true);
    m_DeviceSpecification__units->setContainment(true);
    m_DeviceSpecification__units->setResolveProxies(true);
    m_DeviceSpecification__units->setUnique(true);
    m_DeviceSpecification__units->setDerived(false);
    m_DeviceSpecification__units->setOrdered(true);
    m_DeviceSpecification__bagAccounts->setEType(m_BagAccountsEClass);
    m_DeviceSpecification__bagAccounts->setName("bagAccounts");
    m_DeviceSpecification__bagAccounts->setDefaultValueLiteral("");
    m_DeviceSpecification__bagAccounts->setLowerBound(0);
    m_DeviceSpecification__bagAccounts->setUpperBound(1);
    m_DeviceSpecification__bagAccounts->setTransient(false);
    m_DeviceSpecification__bagAccounts->setVolatile(false);
    m_DeviceSpecification__bagAccounts->setChangeable(true);
    m_DeviceSpecification__bagAccounts->setContainment(true);
    m_DeviceSpecification__bagAccounts->setResolveProxies(true);
    m_DeviceSpecification__bagAccounts->setUnique(true);
    m_DeviceSpecification__bagAccounts->setDerived(false);
    m_DeviceSpecification__bagAccounts->setOrdered(true);
    m_DeviceSpecification__vlSchedules->setEType(m_VirtualLinkSchedulesEClass);
    m_DeviceSpecification__vlSchedules->setName("vlSchedules");
    m_DeviceSpecification__vlSchedules->setDefaultValueLiteral("");
    m_DeviceSpecification__vlSchedules->setLowerBound(0);
    m_DeviceSpecification__vlSchedules->setUpperBound(1);
    m_DeviceSpecification__vlSchedules->setTransient(false);
    m_DeviceSpecification__vlSchedules->setVolatile(false);
    m_DeviceSpecification__vlSchedules->setChangeable(true);
    m_DeviceSpecification__vlSchedules->setContainment(true);
    m_DeviceSpecification__vlSchedules->setResolveProxies(true);
    m_DeviceSpecification__vlSchedules->setUnique(true);
    m_DeviceSpecification__vlSchedules->setDerived(false);
    m_DeviceSpecification__vlSchedules->setOrdered(true);
    m_DeviceSpecification__bestEffortRouting->setEType(
            m_BestEffortRoutingEClass);
    m_DeviceSpecification__bestEffortRouting->setName("bestEffortRouting");
    m_DeviceSpecification__bestEffortRouting->setDefaultValueLiteral("");
    m_DeviceSpecification__bestEffortRouting->setLowerBound(0);
    m_DeviceSpecification__bestEffortRouting->setUpperBound(1);
    m_DeviceSpecification__bestEffortRouting->setTransient(false);
    m_DeviceSpecification__bestEffortRouting->setVolatile(false);
    m_DeviceSpecification__bestEffortRouting->setChangeable(true);
    m_DeviceSpecification__bestEffortRouting->setContainment(true);
    m_DeviceSpecification__bestEffortRouting->setResolveProxies(true);
    m_DeviceSpecification__bestEffortRouting->setUnique(true);
    m_DeviceSpecification__bestEffortRouting->setDerived(false);
    m_DeviceSpecification__bestEffortRouting->setOrdered(true);
    m_DeviceSpecification__flowControl->setEType(m_FlowControlEClass);
    m_DeviceSpecification__flowControl->setName("flowControl");
    m_DeviceSpecification__flowControl->setDefaultValueLiteral("");
    m_DeviceSpecification__flowControl->setLowerBound(0);
    m_DeviceSpecification__flowControl->setUpperBound(1);
    m_DeviceSpecification__flowControl->setTransient(false);
    m_DeviceSpecification__flowControl->setVolatile(false);
    m_DeviceSpecification__flowControl->setChangeable(true);
    m_DeviceSpecification__flowControl->setContainment(true);
    m_DeviceSpecification__flowControl->setResolveProxies(true);
    m_DeviceSpecification__flowControl->setUnique(true);
    m_DeviceSpecification__flowControl->setDerived(false);
    m_DeviceSpecification__flowControl->setOrdered(true);
    m_DeviceSpecification__periods->setEType(m_PeriodsEClass);
    m_DeviceSpecification__periods->setName("periods");
    m_DeviceSpecification__periods->setDefaultValueLiteral("");
    m_DeviceSpecification__periods->setLowerBound(0);
    m_DeviceSpecification__periods->setUpperBound(1);
    m_DeviceSpecification__periods->setTransient(false);
    m_DeviceSpecification__periods->setVolatile(false);
    m_DeviceSpecification__periods->setChangeable(true);
    m_DeviceSpecification__periods->setContainment(true);
    m_DeviceSpecification__periods->setResolveProxies(true);
    m_DeviceSpecification__periods->setUnique(true);
    m_DeviceSpecification__periods->setDerived(false);
    m_DeviceSpecification__periods->setOrdered(true);
    m_DeviceSpecification__refDeviceMapping->setEType(
            dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage* > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getDeviceMapping());
    m_DeviceSpecification__refDeviceMapping->setName("refDeviceMapping");
    m_DeviceSpecification__refDeviceMapping->setDefaultValueLiteral("");
    m_DeviceSpecification__refDeviceMapping->setLowerBound(0);
    m_DeviceSpecification__refDeviceMapping->setUpperBound(1);
    m_DeviceSpecification__refDeviceMapping->setTransient(false);
    m_DeviceSpecification__refDeviceMapping->setVolatile(false);
    m_DeviceSpecification__refDeviceMapping->setChangeable(true);
    m_DeviceSpecification__refDeviceMapping->setContainment(false);
    m_DeviceSpecification__refDeviceMapping->setResolveProxies(true);
    m_DeviceSpecification__refDeviceMapping->setUnique(true);
    m_DeviceSpecification__refDeviceMapping->setDerived(false);
    m_DeviceSpecification__refDeviceMapping->setOrdered(true);
    // EndSystem
    m_EndSystemEClass->setName("EndSystem");
    m_EndSystemEClass->setAbstract(false);
    m_EndSystemEClass->setInterface(false);
    m_EndSystem__config->setEType(m_EndSystemConfigEClass);
    m_EndSystem__config->setName("config");
    m_EndSystem__config->setDefaultValueLiteral("");
    m_EndSystem__config->setLowerBound(1);
    m_EndSystem__config->setUpperBound(1);
    m_EndSystem__config->setTransient(false);
    m_EndSystem__config->setVolatile(false);
    m_EndSystem__config->setChangeable(true);
    m_EndSystem__config->setContainment(true);
    m_EndSystem__config->setResolveProxies(true);
    m_EndSystem__config->setUnique(true);
    m_EndSystem__config->setDerived(false);
    m_EndSystem__config->setOrdered(true);
    m_EndSystem__triggerSchedules->setEType(m_TriggerSchedulesEClass);
    m_EndSystem__triggerSchedules->setName("triggerSchedules");
    m_EndSystem__triggerSchedules->setDefaultValueLiteral("");
    m_EndSystem__triggerSchedules->setLowerBound(0);
    m_EndSystem__triggerSchedules->setUpperBound(1);
    m_EndSystem__triggerSchedules->setTransient(false);
    m_EndSystem__triggerSchedules->setVolatile(false);
    m_EndSystem__triggerSchedules->setChangeable(true);
    m_EndSystem__triggerSchedules->setContainment(true);
    m_EndSystem__triggerSchedules->setResolveProxies(true);
    m_EndSystem__triggerSchedules->setUnique(true);
    m_EndSystem__triggerSchedules->setDerived(false);
    m_EndSystem__triggerSchedules->setOrdered(true);
    // Switch
    m_SwitchEClass->setName("Switch");
    m_SwitchEClass->setAbstract(false);
    m_SwitchEClass->setInterface(false);
    m_Switch__config->setEType(m_SwitchConfigEClass);
    m_Switch__config->setName("config");
    m_Switch__config->setDefaultValueLiteral("");
    m_Switch__config->setLowerBound(1);
    m_Switch__config->setUpperBound(1);
    m_Switch__config->setTransient(false);
    m_Switch__config->setVolatile(false);
    m_Switch__config->setChangeable(true);
    m_Switch__config->setContainment(true);
    m_Switch__config->setResolveProxies(true);
    m_Switch__config->setUnique(true);
    m_Switch__config->setDerived(false);
    m_Switch__config->setOrdered(true);
    // DeviceConfig
    m_DeviceConfigEClass->setName("DeviceConfig");
    m_DeviceConfigEClass->setAbstract(true);
    m_DeviceConfigEClass->setInterface(false);
    m_DeviceConfig__ctMarker->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getCTMarkerType());
    m_DeviceConfig__ctMarker->setName("ctMarker");
    m_DeviceConfig__ctMarker->setDefaultValueLiteral("03:00:00:00");
    m_DeviceConfig__ctMarker->setLowerBound(0);
    m_DeviceConfig__ctMarker->setUpperBound(1);
    m_DeviceConfig__ctMarker->setTransient(false);
    m_DeviceConfig__ctMarker->setVolatile(false);
    m_DeviceConfig__ctMarker->setChangeable(true);
    m_DeviceConfig__ctMarker->setUnsettable(false);
    m_DeviceConfig__ctMarker->setID(false);
    m_DeviceConfig__ctMarker->setUnique(true);
    m_DeviceConfig__ctMarker->setDerived(false);
    m_DeviceConfig__ctMarker->setOrdered(true);
    m_DeviceConfig__ctMask->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getCTMarkerType());
    m_DeviceConfig__ctMask->setName("ctMask");
    m_DeviceConfig__ctMask->setDefaultValueLiteral("ff:ff:ff:ff");
    m_DeviceConfig__ctMask->setLowerBound(0);
    m_DeviceConfig__ctMask->setUpperBound(1);
    m_DeviceConfig__ctMask->setTransient(false);
    m_DeviceConfig__ctMask->setVolatile(false);
    m_DeviceConfig__ctMask->setChangeable(true);
    m_DeviceConfig__ctMask->setUnsettable(false);
    m_DeviceConfig__ctMask->setID(false);
    m_DeviceConfig__ctMask->setUnique(true);
    m_DeviceConfig__ctMask->setDerived(false);
    m_DeviceConfig__ctMask->setOrdered(true);
    // EndSystemConfig
    m_EndSystemConfigEClass->setName("EndSystemConfig");
    m_EndSystemConfigEClass->setAbstract(false);
    m_EndSystemConfigEClass->setInterface(false);
    m_EndSystemConfig__tsSource->setEType(m_TimeSourceEnumEEnum);
    m_EndSystemConfig__tsSource->setName("tsSource");
    m_EndSystemConfig__tsSource->setDefaultValueLiteral("globalTime");
    m_EndSystemConfig__tsSource->setLowerBound(0);
    m_EndSystemConfig__tsSource->setUpperBound(1);
    m_EndSystemConfig__tsSource->setTransient(false);
    m_EndSystemConfig__tsSource->setVolatile(false);
    m_EndSystemConfig__tsSource->setChangeable(true);
    m_EndSystemConfig__tsSource->setUnsettable(false);
    m_EndSystemConfig__tsSource->setID(false);
    m_EndSystemConfig__tsSource->setUnique(true);
    m_EndSystemConfig__tsSource->setDerived(false);
    m_EndSystemConfig__tsSource->setOrdered(true);
    m_EndSystemConfig__sourceMacAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_EndSystemConfig__sourceMacAddress->setName("sourceMacAddress");
    m_EndSystemConfig__sourceMacAddress->setDefaultValueLiteral(
            "01:00:00:00:00:00");
    m_EndSystemConfig__sourceMacAddress->setLowerBound(0);
    m_EndSystemConfig__sourceMacAddress->setUpperBound(1);
    m_EndSystemConfig__sourceMacAddress->setTransient(false);
    m_EndSystemConfig__sourceMacAddress->setVolatile(false);
    m_EndSystemConfig__sourceMacAddress->setChangeable(true);
    m_EndSystemConfig__sourceMacAddress->setUnsettable(false);
    m_EndSystemConfig__sourceMacAddress->setID(false);
    m_EndSystemConfig__sourceMacAddress->setUnique(true);
    m_EndSystemConfig__sourceMacAddress->setDerived(false);
    m_EndSystemConfig__sourceMacAddress->setOrdered(true);
    m_EndSystemConfig__destMacAddressCF->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getCTMarkerType());
    m_EndSystemConfig__destMacAddressCF->setName("destMacAddressCF");
    m_EndSystemConfig__destMacAddressCF->setDefaultValueLiteral("03:00:00:00");
    m_EndSystemConfig__destMacAddressCF->setLowerBound(0);
    m_EndSystemConfig__destMacAddressCF->setUpperBound(1);
    m_EndSystemConfig__destMacAddressCF->setTransient(false);
    m_EndSystemConfig__destMacAddressCF->setVolatile(false);
    m_EndSystemConfig__destMacAddressCF->setChangeable(true);
    m_EndSystemConfig__destMacAddressCF->setUnsettable(false);
    m_EndSystemConfig__destMacAddressCF->setID(false);
    m_EndSystemConfig__destMacAddressCF->setUnique(true);
    m_EndSystemConfig__destMacAddressCF->setDerived(false);
    m_EndSystemConfig__destMacAddressCF->setOrdered(true);
    m_EndSystemConfig__externalSyncAckRequired->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_EndSystemConfig__externalSyncAckRequired->setName(
            "externalSyncAckRequired");
    m_EndSystemConfig__externalSyncAckRequired->setDefaultValueLiteral("false");
    m_EndSystemConfig__externalSyncAckRequired->setLowerBound(0);
    m_EndSystemConfig__externalSyncAckRequired->setUpperBound(1);
    m_EndSystemConfig__externalSyncAckRequired->setTransient(false);
    m_EndSystemConfig__externalSyncAckRequired->setVolatile(false);
    m_EndSystemConfig__externalSyncAckRequired->setChangeable(true);
    m_EndSystemConfig__externalSyncAckRequired->setUnsettable(false);
    m_EndSystemConfig__externalSyncAckRequired->setID(false);
    m_EndSystemConfig__externalSyncAckRequired->setUnique(true);
    m_EndSystemConfig__externalSyncAckRequired->setDerived(false);
    m_EndSystemConfig__externalSyncAckRequired->setOrdered(true);
    m_EndSystemConfig__externalClockSynchronization->setEType(
            m_ExternalClockSynchronizationEClass);
    m_EndSystemConfig__externalClockSynchronization->setName(
            "externalClockSynchronization");
    m_EndSystemConfig__externalClockSynchronization->setDefaultValueLiteral("");
    m_EndSystemConfig__externalClockSynchronization->setLowerBound(0);
    m_EndSystemConfig__externalClockSynchronization->setUpperBound(1);
    m_EndSystemConfig__externalClockSynchronization->setTransient(false);
    m_EndSystemConfig__externalClockSynchronization->setVolatile(false);
    m_EndSystemConfig__externalClockSynchronization->setChangeable(true);
    m_EndSystemConfig__externalClockSynchronization->setContainment(true);
    m_EndSystemConfig__externalClockSynchronization->setResolveProxies(true);
    m_EndSystemConfig__externalClockSynchronization->setUnique(true);
    m_EndSystemConfig__externalClockSynchronization->setDerived(false);
    m_EndSystemConfig__externalClockSynchronization->setOrdered(true);
    // ExternalClockSynchronization
    m_ExternalClockSynchronizationEClass->setName(
            "ExternalClockSynchronization");
    m_ExternalClockSynchronizationEClass->setAbstract(false);
    m_ExternalClockSynchronizationEClass->setInterface(false);
    m_ExternalClockSynchronization__maxExtCorrValue->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_ExternalClockSynchronization__maxExtCorrValue->setName("maxExtCorrValue");
    m_ExternalClockSynchronization__maxExtCorrValue->setDefaultValueLiteral("");
    m_ExternalClockSynchronization__maxExtCorrValue->setLowerBound(1);
    m_ExternalClockSynchronization__maxExtCorrValue->setUpperBound(1);
    m_ExternalClockSynchronization__maxExtCorrValue->setTransient(false);
    m_ExternalClockSynchronization__maxExtCorrValue->setVolatile(false);
    m_ExternalClockSynchronization__maxExtCorrValue->setChangeable(true);
    m_ExternalClockSynchronization__maxExtCorrValue->setUnsettable(false);
    m_ExternalClockSynchronization__maxExtCorrValue->setID(false);
    m_ExternalClockSynchronization__maxExtCorrValue->setUnique(true);
    m_ExternalClockSynchronization__maxExtCorrValue->setDerived(false);
    m_ExternalClockSynchronization__maxExtCorrValue->setOrdered(true);
    // SwitchConfig
    m_SwitchConfigEClass->setName("SwitchConfig");
    m_SwitchConfigEClass->setAbstract(false);
    m_SwitchConfigEClass->setInterface(false);
    // BagAccounts
    m_BagAccountsEClass->setName("BagAccounts");
    m_BagAccountsEClass->setAbstract(false);
    m_BagAccountsEClass->setInterface(false);
    m_BagAccounts__incomingBagAccount->setEType(m_IncomingBagAccountEClass);
    m_BagAccounts__incomingBagAccount->setName("incomingBagAccount");
    m_BagAccounts__incomingBagAccount->setDefaultValueLiteral("");
    m_BagAccounts__incomingBagAccount->setLowerBound(0);
    m_BagAccounts__incomingBagAccount->setUpperBound(-1);
    m_BagAccounts__incomingBagAccount->setTransient(false);
    m_BagAccounts__incomingBagAccount->setVolatile(false);
    m_BagAccounts__incomingBagAccount->setChangeable(true);
    m_BagAccounts__incomingBagAccount->setContainment(true);
    m_BagAccounts__incomingBagAccount->setResolveProxies(true);
    m_BagAccounts__incomingBagAccount->setUnique(true);
    m_BagAccounts__incomingBagAccount->setDerived(false);
    m_BagAccounts__incomingBagAccount->setOrdered(true);
    m_BagAccounts__outgoingBagAccount->setEType(m_OutgoingBagAccountEClass);
    m_BagAccounts__outgoingBagAccount->setName("outgoingBagAccount");
    m_BagAccounts__outgoingBagAccount->setDefaultValueLiteral("");
    m_BagAccounts__outgoingBagAccount->setLowerBound(0);
    m_BagAccounts__outgoingBagAccount->setUpperBound(-1);
    m_BagAccounts__outgoingBagAccount->setTransient(false);
    m_BagAccounts__outgoingBagAccount->setVolatile(false);
    m_BagAccounts__outgoingBagAccount->setChangeable(true);
    m_BagAccounts__outgoingBagAccount->setContainment(true);
    m_BagAccounts__outgoingBagAccount->setResolveProxies(true);
    m_BagAccounts__outgoingBagAccount->setUnique(true);
    m_BagAccounts__outgoingBagAccount->setDerived(false);
    m_BagAccounts__outgoingBagAccount->setOrdered(true);
    // BagAccount
    m_BagAccountEClass->setName("BagAccount");
    m_BagAccountEClass->setAbstract(true);
    m_BagAccountEClass->setInterface(false);
    m_BagAccount__bag->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_BagAccount__bag->setName("bag");
    m_BagAccount__bag->setDefaultValueLiteral("");
    m_BagAccount__bag->setLowerBound(1);
    m_BagAccount__bag->setUpperBound(1);
    m_BagAccount__bag->setTransient(false);
    m_BagAccount__bag->setVolatile(false);
    m_BagAccount__bag->setChangeable(true);
    m_BagAccount__bag->setUnsettable(false);
    m_BagAccount__bag->setID(false);
    m_BagAccount__bag->setUnique(true);
    m_BagAccount__bag->setDerived(false);
    m_BagAccount__bag->setOrdered(true);
    m_BagAccount__jitter->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_BagAccount__jitter->setName("jitter");
    m_BagAccount__jitter->setDefaultValueLiteral("");
    m_BagAccount__jitter->setLowerBound(1);
    m_BagAccount__jitter->setUpperBound(1);
    m_BagAccount__jitter->setTransient(false);
    m_BagAccount__jitter->setVolatile(false);
    m_BagAccount__jitter->setChangeable(true);
    m_BagAccount__jitter->setUnsettable(false);
    m_BagAccount__jitter->setID(false);
    m_BagAccount__jitter->setUnique(true);
    m_BagAccount__jitter->setDerived(false);
    m_BagAccount__jitter->setOrdered(true);
    m_BagAccount__constrainType->setEType(m_ConstrainTypeEEnum);
    m_BagAccount__constrainType->setName("constrainType");
    m_BagAccount__constrainType->setDefaultValueLiteral("frame");
    m_BagAccount__constrainType->setLowerBound(0);
    m_BagAccount__constrainType->setUpperBound(1);
    m_BagAccount__constrainType->setTransient(false);
    m_BagAccount__constrainType->setVolatile(false);
    m_BagAccount__constrainType->setChangeable(true);
    m_BagAccount__constrainType->setUnsettable(false);
    m_BagAccount__constrainType->setID(false);
    m_BagAccount__constrainType->setUnique(true);
    m_BagAccount__constrainType->setDerived(false);
    m_BagAccount__constrainType->setOrdered(true);
    // IncomingBagAccount
    m_IncomingBagAccountEClass->setName("IncomingBagAccount");
    m_IncomingBagAccountEClass->setAbstract(false);
    m_IncomingBagAccountEClass->setInterface(false);
    // OutgoingBagAccount
    m_OutgoingBagAccountEClass->setName("OutgoingBagAccount");
    m_OutgoingBagAccountEClass->setAbstract(false);
    m_OutgoingBagAccountEClass->setInterface(false);
    // VirtualLinkSchedules
    m_VirtualLinkSchedulesEClass->setName("VirtualLinkSchedules");
    m_VirtualLinkSchedulesEClass->setAbstract(false);
    m_VirtualLinkSchedulesEClass->setInterface(false);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_VirtualLinkSchedules__scheduleStartAfterSync->setName(
            "scheduleStartAfterSync");
    m_VirtualLinkSchedules__scheduleStartAfterSync->setDefaultValueLiteral("");
    m_VirtualLinkSchedules__scheduleStartAfterSync->setLowerBound(0);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setUpperBound(1);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setTransient(false);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setVolatile(false);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setChangeable(true);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setUnsettable(false);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setID(false);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setUnique(true);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setDerived(false);
    m_VirtualLinkSchedules__scheduleStartAfterSync->setOrdered(true);
    m_VirtualLinkSchedules__vlSchedule->setEType(m_VirtualLinkScheduleEClass);
    m_VirtualLinkSchedules__vlSchedule->setName("vlSchedule");
    m_VirtualLinkSchedules__vlSchedule->setDefaultValueLiteral("");
    m_VirtualLinkSchedules__vlSchedule->setLowerBound(1);
    m_VirtualLinkSchedules__vlSchedule->setUpperBound(-1);
    m_VirtualLinkSchedules__vlSchedule->setTransient(false);
    m_VirtualLinkSchedules__vlSchedule->setVolatile(false);
    m_VirtualLinkSchedules__vlSchedule->setChangeable(true);
    m_VirtualLinkSchedules__vlSchedule->setContainment(true);
    m_VirtualLinkSchedules__vlSchedule->setResolveProxies(true);
    m_VirtualLinkSchedules__vlSchedule->setUnique(true);
    m_VirtualLinkSchedules__vlSchedule->setDerived(false);
    m_VirtualLinkSchedules__vlSchedule->setOrdered(true);
    // VirtualLinkSchedule
    m_VirtualLinkScheduleEClass->setName("VirtualLinkSchedule");
    m_VirtualLinkScheduleEClass->setAbstract(false);
    m_VirtualLinkScheduleEClass->setInterface(false);
    m_VirtualLinkSchedule__priority->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEByte());
    m_VirtualLinkSchedule__priority->setName("priority");
    m_VirtualLinkSchedule__priority->setDefaultValueLiteral("6");
    m_VirtualLinkSchedule__priority->setLowerBound(0);
    m_VirtualLinkSchedule__priority->setUpperBound(1);
    m_VirtualLinkSchedule__priority->setTransient(false);
    m_VirtualLinkSchedule__priority->setVolatile(false);
    m_VirtualLinkSchedule__priority->setChangeable(true);
    m_VirtualLinkSchedule__priority->setUnsettable(false);
    m_VirtualLinkSchedule__priority->setID(false);
    m_VirtualLinkSchedule__priority->setUnique(true);
    m_VirtualLinkSchedule__priority->setDerived(false);
    m_VirtualLinkSchedule__priority->setOrdered(true);
    m_VirtualLinkSchedule__refVirtualLink->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getVirtualLink());
    m_VirtualLinkSchedule__refVirtualLink->setName("refVirtualLink");
    m_VirtualLinkSchedule__refVirtualLink->setDefaultValueLiteral("");
    m_VirtualLinkSchedule__refVirtualLink->setLowerBound(1);
    m_VirtualLinkSchedule__refVirtualLink->setUpperBound(1);
    m_VirtualLinkSchedule__refVirtualLink->setTransient(false);
    m_VirtualLinkSchedule__refVirtualLink->setVolatile(false);
    m_VirtualLinkSchedule__refVirtualLink->setChangeable(true);
    m_VirtualLinkSchedule__refVirtualLink->setContainment(false);
    m_VirtualLinkSchedule__refVirtualLink->setResolveProxies(true);
    m_VirtualLinkSchedule__refVirtualLink->setUnique(true);
    m_VirtualLinkSchedule__refVirtualLink->setDerived(false);
    m_VirtualLinkSchedule__refVirtualLink->setOrdered(true);
    m_VirtualLinkSchedule__incoming->setEType(m_CTIncomingEClass);
    m_VirtualLinkSchedule__incoming->setName("incoming");
    m_VirtualLinkSchedule__incoming->setDefaultValueLiteral("");
    m_VirtualLinkSchedule__incoming->setLowerBound(1);
    m_VirtualLinkSchedule__incoming->setUpperBound(-1);
    m_VirtualLinkSchedule__incoming->setTransient(false);
    m_VirtualLinkSchedule__incoming->setVolatile(false);
    m_VirtualLinkSchedule__incoming->setChangeable(true);
    m_VirtualLinkSchedule__incoming->setContainment(true);
    m_VirtualLinkSchedule__incoming->setResolveProxies(true);
    m_VirtualLinkSchedule__incoming->setUnique(true);
    m_VirtualLinkSchedule__incoming->setDerived(false);
    m_VirtualLinkSchedule__incoming->setOrdered(true);
    // Buffers
    m_BuffersEClass->setName("Buffers");
    m_BuffersEClass->setAbstract(false);
    m_BuffersEClass->setInterface(false);
    m_Buffers__buffer->setEType(m_BufferEClass);
    m_Buffers__buffer->setName("buffer");
    m_Buffers__buffer->setDefaultValueLiteral("");
    m_Buffers__buffer->setLowerBound(1);
    m_Buffers__buffer->setUpperBound(-1);
    m_Buffers__buffer->setTransient(false);
    m_Buffers__buffer->setVolatile(false);
    m_Buffers__buffer->setChangeable(true);
    m_Buffers__buffer->setContainment(true);
    m_Buffers__buffer->setResolveProxies(true);
    m_Buffers__buffer->setUnique(true);
    m_Buffers__buffer->setDerived(false);
    m_Buffers__buffer->setOrdered(true);
    // Buffer
    m_BufferEClass->setName("Buffer");
    m_BufferEClass->setAbstract(true);
    m_BufferEClass->setInterface(false);
    // FIFOQueue
    m_FIFOQueueEClass->setName("FIFOQueue");
    m_FIFOQueueEClass->setAbstract(false);
    m_FIFOQueueEClass->setInterface(false);
    m_FIFOQueue__length->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_FIFOQueue__length->setName("length");
    m_FIFOQueue__length->setDefaultValueLiteral("");
    m_FIFOQueue__length->setLowerBound(1);
    m_FIFOQueue__length->setUpperBound(1);
    m_FIFOQueue__length->setTransient(false);
    m_FIFOQueue__length->setVolatile(false);
    m_FIFOQueue__length->setChangeable(true);
    m_FIFOQueue__length->setUnsettable(false);
    m_FIFOQueue__length->setID(false);
    m_FIFOQueue__length->setUnique(true);
    m_FIFOQueue__length->setDerived(false);
    m_FIFOQueue__length->setOrdered(true);
    // SingleEntryBuffer
    m_SingleEntryBufferEClass->setName("SingleEntryBuffer");
    m_SingleEntryBufferEClass->setAbstract(false);
    m_SingleEntryBufferEClass->setInterface(false);
    // DualEntryBuffer
    m_DualEntryBufferEClass->setName("DualEntryBuffer");
    m_DualEntryBufferEClass->setAbstract(false);
    m_DualEntryBufferEClass->setInterface(false);
    // TripleEntryBuffer
    m_TripleEntryBufferEClass->setName("TripleEntryBuffer");
    m_TripleEntryBufferEClass->setAbstract(false);
    m_TripleEntryBufferEClass->setInterface(false);
    // Incoming
    m_IncomingEClass->setName("Incoming");
    m_IncomingEClass->setAbstract(true);
    m_IncomingEClass->setInterface(false);
    m_Incoming__outgoing->setEType(m_OutgoingEClass);
    m_Incoming__outgoing->setName("outgoing");
    m_Incoming__outgoing->setDefaultValueLiteral("");
    m_Incoming__outgoing->setLowerBound(1);
    m_Incoming__outgoing->setUpperBound(-1);
    m_Incoming__outgoing->setTransient(false);
    m_Incoming__outgoing->setVolatile(false);
    m_Incoming__outgoing->setChangeable(true);
    m_Incoming__outgoing->setContainment(true);
    m_Incoming__outgoing->setResolveProxies(true);
    m_Incoming__outgoing->setUnique(true);
    m_Incoming__outgoing->setDerived(false);
    m_Incoming__outgoing->setOrdered(true);
    m_Incoming__refInPort->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPort());
    m_Incoming__refInPort->setName("refInPort");
    m_Incoming__refInPort->setDefaultValueLiteral("");
    m_Incoming__refInPort->setLowerBound(1);
    m_Incoming__refInPort->setUpperBound(-1);
    m_Incoming__refInPort->setTransient(false);
    m_Incoming__refInPort->setVolatile(false);
    m_Incoming__refInPort->setChangeable(true);
    m_Incoming__refInPort->setContainment(false);
    m_Incoming__refInPort->setResolveProxies(true);
    m_Incoming__refInPort->setUnique(true);
    m_Incoming__refInPort->setDerived(false);
    m_Incoming__refInPort->setOrdered(false);
    // CTIncoming
    m_CTIncomingEClass->setName("CTIncoming");
    m_CTIncomingEClass->setAbstract(true);
    m_CTIncomingEClass->setInterface(false);
    m_CTIncoming__removeSequenceNumber->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CTIncoming__removeSequenceNumber->setName("removeSequenceNumber");
    m_CTIncoming__removeSequenceNumber->setDefaultValueLiteral("false");
    m_CTIncoming__removeSequenceNumber->setLowerBound(0);
    m_CTIncoming__removeSequenceNumber->setUpperBound(1);
    m_CTIncoming__removeSequenceNumber->setTransient(false);
    m_CTIncoming__removeSequenceNumber->setVolatile(false);
    m_CTIncoming__removeSequenceNumber->setChangeable(true);
    m_CTIncoming__removeSequenceNumber->setUnsettable(false);
    m_CTIncoming__removeSequenceNumber->setID(false);
    m_CTIncoming__removeSequenceNumber->setUnique(true);
    m_CTIncoming__removeSequenceNumber->setDerived(false);
    m_CTIncoming__removeSequenceNumber->setOrdered(true);
    m_CTIncoming__redundancyFunction->setEType(m_IntegrityCheckEClass);
    m_CTIncoming__redundancyFunction->setName("redundancyFunction");
    m_CTIncoming__redundancyFunction->setDefaultValueLiteral("");
    m_CTIncoming__redundancyFunction->setLowerBound(0);
    m_CTIncoming__redundancyFunction->setUpperBound(1);
    m_CTIncoming__redundancyFunction->setTransient(false);
    m_CTIncoming__redundancyFunction->setVolatile(false);
    m_CTIncoming__redundancyFunction->setChangeable(true);
    m_CTIncoming__redundancyFunction->setContainment(true);
    m_CTIncoming__redundancyFunction->setResolveProxies(true);
    m_CTIncoming__redundancyFunction->setUnique(true);
    m_CTIncoming__redundancyFunction->setDerived(false);
    m_CTIncoming__redundancyFunction->setOrdered(false);
    // Outgoing
    m_OutgoingEClass->setName("Outgoing");
    m_OutgoingEClass->setAbstract(true);
    m_OutgoingEClass->setInterface(false);
    m_Outgoing__appendSequenceNumber->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_Outgoing__appendSequenceNumber->setName("appendSequenceNumber");
    m_Outgoing__appendSequenceNumber->setDefaultValueLiteral("false");
    m_Outgoing__appendSequenceNumber->setLowerBound(0);
    m_Outgoing__appendSequenceNumber->setUpperBound(1);
    m_Outgoing__appendSequenceNumber->setTransient(false);
    m_Outgoing__appendSequenceNumber->setVolatile(false);
    m_Outgoing__appendSequenceNumber->setChangeable(true);
    m_Outgoing__appendSequenceNumber->setUnsettable(false);
    m_Outgoing__appendSequenceNumber->setID(false);
    m_Outgoing__appendSequenceNumber->setUnique(true);
    m_Outgoing__appendSequenceNumber->setDerived(false);
    m_Outgoing__appendSequenceNumber->setOrdered(true);
    m_Outgoing__refOutPort->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPort());
    m_Outgoing__refOutPort->setName("refOutPort");
    m_Outgoing__refOutPort->setDefaultValueLiteral("");
    m_Outgoing__refOutPort->setLowerBound(1);
    m_Outgoing__refOutPort->setUpperBound(-1);
    m_Outgoing__refOutPort->setTransient(false);
    m_Outgoing__refOutPort->setVolatile(false);
    m_Outgoing__refOutPort->setChangeable(true);
    m_Outgoing__refOutPort->setContainment(false);
    m_Outgoing__refOutPort->setResolveProxies(true);
    m_Outgoing__refOutPort->setUnique(true);
    m_Outgoing__refOutPort->setDerived(false);
    m_Outgoing__refOutPort->setOrdered(true);
    // RCIncoming
    m_RCIncomingEClass->setName("RCIncoming");
    m_RCIncomingEClass->setAbstract(false);
    m_RCIncomingEClass->setInterface(false);
    m_RCIncoming__refBagAccount->setEType(m_IncomingBagAccountEClass);
    m_RCIncoming__refBagAccount->setName("refBagAccount");
    m_RCIncoming__refBagAccount->setDefaultValueLiteral("");
    m_RCIncoming__refBagAccount->setLowerBound(1);
    m_RCIncoming__refBagAccount->setUpperBound(1);
    m_RCIncoming__refBagAccount->setTransient(false);
    m_RCIncoming__refBagAccount->setVolatile(false);
    m_RCIncoming__refBagAccount->setChangeable(true);
    m_RCIncoming__refBagAccount->setContainment(false);
    m_RCIncoming__refBagAccount->setResolveProxies(true);
    m_RCIncoming__refBagAccount->setUnique(true);
    m_RCIncoming__refBagAccount->setDerived(false);
    m_RCIncoming__refBagAccount->setOrdered(true);
    // TTIncoming
    m_TTIncomingEClass->setName("TTIncoming");
    m_TTIncomingEClass->setAbstract(false);
    m_TTIncomingEClass->setInterface(false);
    m_TTIncoming__receiveWindowStart->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_TTIncoming__receiveWindowStart->setName("receiveWindowStart");
    m_TTIncoming__receiveWindowStart->setDefaultValueLiteral("");
    m_TTIncoming__receiveWindowStart->setLowerBound(0);
    m_TTIncoming__receiveWindowStart->setUpperBound(1);
    m_TTIncoming__receiveWindowStart->setTransient(false);
    m_TTIncoming__receiveWindowStart->setVolatile(false);
    m_TTIncoming__receiveWindowStart->setChangeable(true);
    m_TTIncoming__receiveWindowStart->setUnsettable(false);
    m_TTIncoming__receiveWindowStart->setID(false);
    m_TTIncoming__receiveWindowStart->setUnique(true);
    m_TTIncoming__receiveWindowStart->setDerived(false);
    m_TTIncoming__receiveWindowStart->setOrdered(true);
    m_TTIncoming__receiveWindowEnd->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_TTIncoming__receiveWindowEnd->setName("receiveWindowEnd");
    m_TTIncoming__receiveWindowEnd->setDefaultValueLiteral("");
    m_TTIncoming__receiveWindowEnd->setLowerBound(0);
    m_TTIncoming__receiveWindowEnd->setUpperBound(1);
    m_TTIncoming__receiveWindowEnd->setTransient(false);
    m_TTIncoming__receiveWindowEnd->setVolatile(false);
    m_TTIncoming__receiveWindowEnd->setChangeable(true);
    m_TTIncoming__receiveWindowEnd->setUnsettable(false);
    m_TTIncoming__receiveWindowEnd->setID(false);
    m_TTIncoming__receiveWindowEnd->setUnique(true);
    m_TTIncoming__receiveWindowEnd->setDerived(false);
    m_TTIncoming__receiveWindowEnd->setOrdered(true);
    m_TTIncoming__permanencePit->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_TTIncoming__permanencePit->setName("permanencePit");
    m_TTIncoming__permanencePit->setDefaultValueLiteral("");
    m_TTIncoming__permanencePit->setLowerBound(0);
    m_TTIncoming__permanencePit->setUpperBound(1);
    m_TTIncoming__permanencePit->setTransient(false);
    m_TTIncoming__permanencePit->setVolatile(false);
    m_TTIncoming__permanencePit->setChangeable(true);
    m_TTIncoming__permanencePit->setUnsettable(false);
    m_TTIncoming__permanencePit->setID(false);
    m_TTIncoming__permanencePit->setUnique(true);
    m_TTIncoming__permanencePit->setDerived(false);
    m_TTIncoming__permanencePit->setOrdered(true);
    m_TTIncoming__refPeriod->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPeriod());
    m_TTIncoming__refPeriod->setName("refPeriod");
    m_TTIncoming__refPeriod->setDefaultValueLiteral("");
    m_TTIncoming__refPeriod->setLowerBound(1);
    m_TTIncoming__refPeriod->setUpperBound(1);
    m_TTIncoming__refPeriod->setTransient(false);
    m_TTIncoming__refPeriod->setVolatile(false);
    m_TTIncoming__refPeriod->setChangeable(true);
    m_TTIncoming__refPeriod->setContainment(false);
    m_TTIncoming__refPeriod->setResolveProxies(true);
    m_TTIncoming__refPeriod->setUnique(true);
    m_TTIncoming__refPeriod->setDerived(false);
    m_TTIncoming__refPeriod->setOrdered(true);
    // BEIncoming
    m_BEIncomingEClass->setName("BEIncoming");
    m_BEIncomingEClass->setAbstract(false);
    m_BEIncomingEClass->setInterface(false);
    // RCOutgoing
    m_RCOutgoingEClass->setName("RCOutgoing");
    m_RCOutgoingEClass->setAbstract(false);
    m_RCOutgoingEClass->setInterface(false);
    m_RCOutgoing__maxDispatchDelay->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_RCOutgoing__maxDispatchDelay->setName("maxDispatchDelay");
    m_RCOutgoing__maxDispatchDelay->setDefaultValueLiteral("");
    m_RCOutgoing__maxDispatchDelay->setLowerBound(0);
    m_RCOutgoing__maxDispatchDelay->setUpperBound(1);
    m_RCOutgoing__maxDispatchDelay->setTransient(false);
    m_RCOutgoing__maxDispatchDelay->setVolatile(false);
    m_RCOutgoing__maxDispatchDelay->setChangeable(true);
    m_RCOutgoing__maxDispatchDelay->setUnsettable(false);
    m_RCOutgoing__maxDispatchDelay->setID(false);
    m_RCOutgoing__maxDispatchDelay->setUnique(true);
    m_RCOutgoing__maxDispatchDelay->setDerived(false);
    m_RCOutgoing__maxDispatchDelay->setOrdered(true);
    m_RCOutgoing__refBagAccount->setEType(m_OutgoingBagAccountEClass);
    m_RCOutgoing__refBagAccount->setName("refBagAccount");
    m_RCOutgoing__refBagAccount->setDefaultValueLiteral("");
    m_RCOutgoing__refBagAccount->setLowerBound(1);
    m_RCOutgoing__refBagAccount->setUpperBound(1);
    m_RCOutgoing__refBagAccount->setTransient(false);
    m_RCOutgoing__refBagAccount->setVolatile(false);
    m_RCOutgoing__refBagAccount->setChangeable(true);
    m_RCOutgoing__refBagAccount->setContainment(false);
    m_RCOutgoing__refBagAccount->setResolveProxies(true);
    m_RCOutgoing__refBagAccount->setUnique(true);
    m_RCOutgoing__refBagAccount->setDerived(false);
    m_RCOutgoing__refBagAccount->setOrdered(true);
    // CTOutgoing
    m_CTOutgoingEClass->setName("CTOutgoing");
    m_CTOutgoingEClass->setAbstract(true);
    m_CTOutgoingEClass->setInterface(false);
    // TTOutgoing
    m_TTOutgoingEClass->setName("TTOutgoing");
    m_TTOutgoingEClass->setAbstract(false);
    m_TTOutgoingEClass->setInterface(false);
    m_TTOutgoing__sendWindowStart->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_TTOutgoing__sendWindowStart->setName("sendWindowStart");
    m_TTOutgoing__sendWindowStart->setDefaultValueLiteral("");
    m_TTOutgoing__sendWindowStart->setLowerBound(0);
    m_TTOutgoing__sendWindowStart->setUpperBound(1);
    m_TTOutgoing__sendWindowStart->setTransient(false);
    m_TTOutgoing__sendWindowStart->setVolatile(false);
    m_TTOutgoing__sendWindowStart->setChangeable(true);
    m_TTOutgoing__sendWindowStart->setUnsettable(false);
    m_TTOutgoing__sendWindowStart->setID(false);
    m_TTOutgoing__sendWindowStart->setUnique(true);
    m_TTOutgoing__sendWindowStart->setDerived(false);
    m_TTOutgoing__sendWindowStart->setOrdered(true);
    m_TTOutgoing__sendWindowEnd->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_TTOutgoing__sendWindowEnd->setName("sendWindowEnd");
    m_TTOutgoing__sendWindowEnd->setDefaultValueLiteral("");
    m_TTOutgoing__sendWindowEnd->setLowerBound(0);
    m_TTOutgoing__sendWindowEnd->setUpperBound(1);
    m_TTOutgoing__sendWindowEnd->setTransient(false);
    m_TTOutgoing__sendWindowEnd->setVolatile(false);
    m_TTOutgoing__sendWindowEnd->setChangeable(true);
    m_TTOutgoing__sendWindowEnd->setUnsettable(false);
    m_TTOutgoing__sendWindowEnd->setID(false);
    m_TTOutgoing__sendWindowEnd->setUnique(true);
    m_TTOutgoing__sendWindowEnd->setDerived(false);
    m_TTOutgoing__sendWindowEnd->setOrdered(true);
    m_TTOutgoing__refPeriod->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPeriod());
    m_TTOutgoing__refPeriod->setName("refPeriod");
    m_TTOutgoing__refPeriod->setDefaultValueLiteral("");
    m_TTOutgoing__refPeriod->setLowerBound(1);
    m_TTOutgoing__refPeriod->setUpperBound(1);
    m_TTOutgoing__refPeriod->setTransient(false);
    m_TTOutgoing__refPeriod->setVolatile(false);
    m_TTOutgoing__refPeriod->setChangeable(true);
    m_TTOutgoing__refPeriod->setContainment(false);
    m_TTOutgoing__refPeriod->setResolveProxies(true);
    m_TTOutgoing__refPeriod->setUnique(true);
    m_TTOutgoing__refPeriod->setDerived(false);
    m_TTOutgoing__refPeriod->setOrdered(true);
    // BEOutgoing
    m_BEOutgoingEClass->setName("BEOutgoing");
    m_BEOutgoingEClass->setAbstract(false);
    m_BEOutgoingEClass->setInterface(false);
    // BestEffortRouting
    m_BestEffortRoutingEClass->setName("BestEffortRouting");
    m_BestEffortRoutingEClass->setAbstract(false);
    m_BestEffortRoutingEClass->setInterface(false);
    m_BestEffortRouting__enableDynamicRouting->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_BestEffortRouting__enableDynamicRouting->setName("enableDynamicRouting");
    m_BestEffortRouting__enableDynamicRouting->setDefaultValueLiteral("false");
    m_BestEffortRouting__enableDynamicRouting->setLowerBound(1);
    m_BestEffortRouting__enableDynamicRouting->setUpperBound(1);
    m_BestEffortRouting__enableDynamicRouting->setTransient(false);
    m_BestEffortRouting__enableDynamicRouting->setVolatile(false);
    m_BestEffortRouting__enableDynamicRouting->setChangeable(true);
    m_BestEffortRouting__enableDynamicRouting->setUnsettable(false);
    m_BestEffortRouting__enableDynamicRouting->setID(false);
    m_BestEffortRouting__enableDynamicRouting->setUnique(true);
    m_BestEffortRouting__enableDynamicRouting->setDerived(false);
    m_BestEffortRouting__enableDynamicRouting->setOrdered(true);
    m_BestEffortRouting__beRouteIncoming->setEType(m_BERouteIncomingEClass);
    m_BestEffortRouting__beRouteIncoming->setName("beRouteIncoming");
    m_BestEffortRouting__beRouteIncoming->setDefaultValueLiteral("");
    m_BestEffortRouting__beRouteIncoming->setLowerBound(0);
    m_BestEffortRouting__beRouteIncoming->setUpperBound(-1);
    m_BestEffortRouting__beRouteIncoming->setTransient(false);
    m_BestEffortRouting__beRouteIncoming->setVolatile(false);
    m_BestEffortRouting__beRouteIncoming->setChangeable(true);
    m_BestEffortRouting__beRouteIncoming->setContainment(true);
    m_BestEffortRouting__beRouteIncoming->setResolveProxies(true);
    m_BestEffortRouting__beRouteIncoming->setUnique(true);
    m_BestEffortRouting__beRouteIncoming->setDerived(false);
    m_BestEffortRouting__beRouteIncoming->setOrdered(true);
    // BERouteIncoming
    m_BERouteIncomingEClass->setName("BERouteIncoming");
    m_BERouteIncomingEClass->setAbstract(false);
    m_BERouteIncomingEClass->setInterface(false);
    m_BERouteIncoming__destinationMacAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_BERouteIncoming__destinationMacAddress->setName("destinationMacAddress");
    m_BERouteIncoming__destinationMacAddress->setDefaultValueLiteral("");
    m_BERouteIncoming__destinationMacAddress->setLowerBound(1);
    m_BERouteIncoming__destinationMacAddress->setUpperBound(1);
    m_BERouteIncoming__destinationMacAddress->setTransient(false);
    m_BERouteIncoming__destinationMacAddress->setVolatile(false);
    m_BERouteIncoming__destinationMacAddress->setChangeable(true);
    m_BERouteIncoming__destinationMacAddress->setUnsettable(false);
    m_BERouteIncoming__destinationMacAddress->setID(false);
    m_BERouteIncoming__destinationMacAddress->setUnique(true);
    m_BERouteIncoming__destinationMacAddress->setDerived(false);
    m_BERouteIncoming__destinationMacAddress->setOrdered(true);
    m_BERouteIncoming__addrMask->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_BERouteIncoming__addrMask->setName("addrMask");
    m_BERouteIncoming__addrMask->setDefaultValueLiteral("FF:FF:FF:FF:FF:FF");
    m_BERouteIncoming__addrMask->setLowerBound(0);
    m_BERouteIncoming__addrMask->setUpperBound(1);
    m_BERouteIncoming__addrMask->setTransient(false);
    m_BERouteIncoming__addrMask->setVolatile(false);
    m_BERouteIncoming__addrMask->setChangeable(true);
    m_BERouteIncoming__addrMask->setUnsettable(false);
    m_BERouteIncoming__addrMask->setID(false);
    m_BERouteIncoming__addrMask->setUnique(true);
    m_BERouteIncoming__addrMask->setDerived(false);
    m_BERouteIncoming__addrMask->setOrdered(true);
    // BERouteOutgoing
    m_BERouteOutgoingEClass->setName("BERouteOutgoing");
    m_BERouteOutgoingEClass->setAbstract(false);
    m_BERouteOutgoingEClass->setInterface(false);
    // FlowControl
    m_FlowControlEClass->setName("FlowControl");
    m_FlowControlEClass->setAbstract(false);
    m_FlowControlEClass->setInterface(false);
    m_FlowControl__xon->setEType(m_FlowControlValueEClass);
    m_FlowControl__xon->setName("xon");
    m_FlowControl__xon->setDefaultValueLiteral("");
    m_FlowControl__xon->setLowerBound(0);
    m_FlowControl__xon->setUpperBound(1);
    m_FlowControl__xon->setTransient(false);
    m_FlowControl__xon->setVolatile(false);
    m_FlowControl__xon->setChangeable(true);
    m_FlowControl__xon->setContainment(true);
    m_FlowControl__xon->setResolveProxies(true);
    m_FlowControl__xon->setUnique(true);
    m_FlowControl__xon->setDerived(false);
    m_FlowControl__xon->setOrdered(true);
    m_FlowControl__xoff->setEType(m_FlowControlValueEClass);
    m_FlowControl__xoff->setName("xoff");
    m_FlowControl__xoff->setDefaultValueLiteral("");
    m_FlowControl__xoff->setLowerBound(0);
    m_FlowControl__xoff->setUpperBound(1);
    m_FlowControl__xoff->setTransient(false);
    m_FlowControl__xoff->setVolatile(false);
    m_FlowControl__xoff->setChangeable(true);
    m_FlowControl__xoff->setContainment(true);
    m_FlowControl__xoff->setResolveProxies(true);
    m_FlowControl__xoff->setUnique(true);
    m_FlowControl__xoff->setDerived(false);
    m_FlowControl__xoff->setOrdered(true);
    // FlowControlValue
    m_FlowControlValueEClass->setName("FlowControlValue");
    m_FlowControlValueEClass->setAbstract(false);
    m_FlowControlValueEClass->setInterface(false);
    m_FlowControlValue__value->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_FlowControlValue__value->setName("value");
    m_FlowControlValue__value->setDefaultValueLiteral("");
    m_FlowControlValue__value->setLowerBound(0);
    m_FlowControlValue__value->setUpperBound(1);
    m_FlowControlValue__value->setTransient(false);
    m_FlowControlValue__value->setVolatile(false);
    m_FlowControlValue__value->setChangeable(true);
    m_FlowControlValue__value->setUnsettable(false);
    m_FlowControlValue__value->setID(false);
    m_FlowControlValue__value->setUnique(true);
    m_FlowControlValue__value->setDerived(false);
    m_FlowControlValue__value->setOrdered(true);
    m_FlowControlValue__threshold->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_FlowControlValue__threshold->setName("threshold");
    m_FlowControlValue__threshold->setDefaultValueLiteral("");
    m_FlowControlValue__threshold->setLowerBound(0);
    m_FlowControlValue__threshold->setUpperBound(1);
    m_FlowControlValue__threshold->setTransient(false);
    m_FlowControlValue__threshold->setVolatile(false);
    m_FlowControlValue__threshold->setChangeable(true);
    m_FlowControlValue__threshold->setUnsettable(false);
    m_FlowControlValue__threshold->setID(false);
    m_FlowControlValue__threshold->setUnique(true);
    m_FlowControlValue__threshold->setDerived(false);
    m_FlowControlValue__threshold->setOrdered(true);
    // TriggerSchedules
    m_TriggerSchedulesEClass->setName("TriggerSchedules");
    m_TriggerSchedulesEClass->setAbstract(false);
    m_TriggerSchedulesEClass->setInterface(false);
    m_TriggerSchedules__triggerSchedule->setEType(m_TriggerScheduleEClass);
    m_TriggerSchedules__triggerSchedule->setName("triggerSchedule");
    m_TriggerSchedules__triggerSchedule->setDefaultValueLiteral("");
    m_TriggerSchedules__triggerSchedule->setLowerBound(1);
    m_TriggerSchedules__triggerSchedule->setUpperBound(-1);
    m_TriggerSchedules__triggerSchedule->setTransient(false);
    m_TriggerSchedules__triggerSchedule->setVolatile(false);
    m_TriggerSchedules__triggerSchedule->setChangeable(true);
    m_TriggerSchedules__triggerSchedule->setContainment(true);
    m_TriggerSchedules__triggerSchedule->setResolveProxies(true);
    m_TriggerSchedules__triggerSchedule->setUnique(true);
    m_TriggerSchedules__triggerSchedule->setDerived(false);
    m_TriggerSchedules__triggerSchedule->setOrdered(true);
    // TriggerSchedule
    m_TriggerScheduleEClass->setName("TriggerSchedule");
    m_TriggerScheduleEClass->setAbstract(false);
    m_TriggerScheduleEClass->setInterface(false);
    m_TriggerSchedule__refPeriod->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPeriod());
    m_TriggerSchedule__refPeriod->setName("refPeriod");
    m_TriggerSchedule__refPeriod->setDefaultValueLiteral("");
    m_TriggerSchedule__refPeriod->setLowerBound(1);
    m_TriggerSchedule__refPeriod->setUpperBound(1);
    m_TriggerSchedule__refPeriod->setTransient(false);
    m_TriggerSchedule__refPeriod->setVolatile(false);
    m_TriggerSchedule__refPeriod->setChangeable(true);
    m_TriggerSchedule__refPeriod->setContainment(false);
    m_TriggerSchedule__refPeriod->setResolveProxies(true);
    m_TriggerSchedule__refPeriod->setUnique(true);
    m_TriggerSchedule__refPeriod->setDerived(false);
    m_TriggerSchedule__refPeriod->setOrdered(true);
    // IntegrityCheck
    m_IntegrityCheckEClass->setName("IntegrityCheck");
    m_IntegrityCheckEClass->setAbstract(false);
    m_IntegrityCheckEClass->setInterface(false);
    // RedundancyManagement
    m_RedundancyManagementEClass->setName("RedundancyManagement");
    m_RedundancyManagementEClass->setAbstract(true);
    m_RedundancyManagementEClass->setInterface(false);
    m_RedundancyManagement__redundancyTimeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_RedundancyManagement__redundancyTimeout->setName("redundancyTimeout");
    m_RedundancyManagement__redundancyTimeout->setDefaultValueLiteral("");
    m_RedundancyManagement__redundancyTimeout->setLowerBound(0);
    m_RedundancyManagement__redundancyTimeout->setUpperBound(1);
    m_RedundancyManagement__redundancyTimeout->setTransient(false);
    m_RedundancyManagement__redundancyTimeout->setVolatile(false);
    m_RedundancyManagement__redundancyTimeout->setChangeable(true);
    m_RedundancyManagement__redundancyTimeout->setUnsettable(false);
    m_RedundancyManagement__redundancyTimeout->setID(false);
    m_RedundancyManagement__redundancyTimeout->setUnique(true);
    m_RedundancyManagement__redundancyTimeout->setDerived(false);
    m_RedundancyManagement__redundancyTimeout->setOrdered(true);
    // RCRedundancyManagement
    m_RCRedundancyManagementEClass->setName("RCRedundancyManagement");
    m_RCRedundancyManagementEClass->setAbstract(false);
    m_RCRedundancyManagementEClass->setInterface(false);
    m_RCRedundancyManagement__maxSequenceNumberRange->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_RCRedundancyManagement__maxSequenceNumberRange->setName(
            "maxSequenceNumberRange");
    m_RCRedundancyManagement__maxSequenceNumberRange->setDefaultValueLiteral("");
    m_RCRedundancyManagement__maxSequenceNumberRange->setLowerBound(0);
    m_RCRedundancyManagement__maxSequenceNumberRange->setUpperBound(1);
    m_RCRedundancyManagement__maxSequenceNumberRange->setTransient(false);
    m_RCRedundancyManagement__maxSequenceNumberRange->setVolatile(false);
    m_RCRedundancyManagement__maxSequenceNumberRange->setChangeable(true);
    m_RCRedundancyManagement__maxSequenceNumberRange->setUnsettable(false);
    m_RCRedundancyManagement__maxSequenceNumberRange->setID(false);
    m_RCRedundancyManagement__maxSequenceNumberRange->setUnique(true);
    m_RCRedundancyManagement__maxSequenceNumberRange->setDerived(false);
    m_RCRedundancyManagement__maxSequenceNumberRange->setOrdered(true);
    // TTRedundancyManagement
    m_TTRedundancyManagementEClass->setName("TTRedundancyManagement");
    m_TTRedundancyManagementEClass->setAbstract(false);
    m_TTRedundancyManagementEClass->setInterface(false);
    // Periods
    m_PeriodsEClass->setName("Periods");
    m_PeriodsEClass->setAbstract(false);
    m_PeriodsEClass->setInterface(false);
    m_Periods__period->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPeriod());
    m_Periods__period->setName("period");
    m_Periods__period->setDefaultValueLiteral("");
    m_Periods__period->setLowerBound(0);
    m_Periods__period->setUpperBound(-1);
    m_Periods__period->setTransient(false);
    m_Periods__period->setVolatile(false);
    m_Periods__period->setChangeable(true);
    m_Periods__period->setContainment(true);
    m_Periods__period->setResolveProxies(true);
    m_Periods__period->setUnique(true);
    m_Periods__period->setDerived(false);
    m_Periods__period->setOrdered(true);
    // FrameRelayDescriptor
    m_FrameRelayDescriptorEClass->setName("FrameRelayDescriptor");
    m_FrameRelayDescriptorEClass->setAbstract(true);
    m_FrameRelayDescriptorEClass->setInterface(false);
    m_FrameRelayDescriptor__bufferDepth->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_FrameRelayDescriptor__bufferDepth->setName("bufferDepth");
    m_FrameRelayDescriptor__bufferDepth->setDefaultValueLiteral("0");
    m_FrameRelayDescriptor__bufferDepth->setLowerBound(0);
    m_FrameRelayDescriptor__bufferDepth->setUpperBound(1);
    m_FrameRelayDescriptor__bufferDepth->setTransient(false);
    m_FrameRelayDescriptor__bufferDepth->setVolatile(false);
    m_FrameRelayDescriptor__bufferDepth->setChangeable(true);
    m_FrameRelayDescriptor__bufferDepth->setUnsettable(false);
    m_FrameRelayDescriptor__bufferDepth->setID(false);
    m_FrameRelayDescriptor__bufferDepth->setUnique(true);
    m_FrameRelayDescriptor__bufferDepth->setDerived(false);
    m_FrameRelayDescriptor__bufferDepth->setOrdered(true);

    // TODO: Initialize data types


    // ConstrainType
    m_ConstrainTypeEEnum->setName("ConstrainType");
    m_ConstrainTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // frame
        _el->setName("frame");
        _el->setValue(0);
        _el->setLiteral("frame");
        _el->setEEnum(m_ConstrainTypeEEnum);
        m_ConstrainTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // size
        _el->setName("size");
        _el->setValue(1);
        _el->setLiteral("size");
        _el->setEEnum(m_ConstrainTypeEEnum);
        m_ConstrainTypeEEnum->getELiterals().push_back(_el);
    }

    // TimeSourceEnum
    m_TimeSourceEnumEEnum->setName("TimeSourceEnum");
    m_TimeSourceEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // globalTime
        _el->setName("globalTime");
        _el->setValue(0);
        _el->setLiteral("globalTime");
        _el->setEEnum(m_TimeSourceEnumEEnum);
        m_TimeSourceEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // freeTime
        _el->setName("freeTime");
        _el->setValue(1);
        _el->setLiteral("freeTime");
        _el->setEEnum(m_TimeSourceEnumEEnum);
        m_TimeSourceEnumEEnum->getELiterals().push_back(_el);
    }

    _initialize();
}

::ecore::EClass_ptr Device_SpecificationPackage::getDeviceSpecification()
{
    return m_DeviceSpecificationEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getEndSystem()
{
    return m_EndSystemEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getSwitch()
{
    return m_SwitchEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getDeviceConfig()
{
    return m_DeviceConfigEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getEndSystemConfig()
{
    return m_EndSystemConfigEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getExternalClockSynchronization()
{
    return m_ExternalClockSynchronizationEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getSwitchConfig()
{
    return m_SwitchConfigEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBagAccounts()
{
    return m_BagAccountsEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBagAccount()
{
    return m_BagAccountEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getIncomingBagAccount()
{
    return m_IncomingBagAccountEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getOutgoingBagAccount()
{
    return m_OutgoingBagAccountEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getVirtualLinkSchedules()
{
    return m_VirtualLinkSchedulesEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getVirtualLinkSchedule()
{
    return m_VirtualLinkScheduleEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBuffers()
{
    return m_BuffersEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBuffer()
{
    return m_BufferEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getFIFOQueue()
{
    return m_FIFOQueueEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getSingleEntryBuffer()
{
    return m_SingleEntryBufferEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getDualEntryBuffer()
{
    return m_DualEntryBufferEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getTripleEntryBuffer()
{
    return m_TripleEntryBufferEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getIncoming()
{
    return m_IncomingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getCTIncoming()
{
    return m_CTIncomingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getOutgoing()
{
    return m_OutgoingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getRCIncoming()
{
    return m_RCIncomingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getTTIncoming()
{
    return m_TTIncomingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBEIncoming()
{
    return m_BEIncomingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getRCOutgoing()
{
    return m_RCOutgoingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getCTOutgoing()
{
    return m_CTOutgoingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getTTOutgoing()
{
    return m_TTOutgoingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBEOutgoing()
{
    return m_BEOutgoingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBestEffortRouting()
{
    return m_BestEffortRoutingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBERouteIncoming()
{
    return m_BERouteIncomingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getBERouteOutgoing()
{
    return m_BERouteOutgoingEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getFlowControl()
{
    return m_FlowControlEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getFlowControlValue()
{
    return m_FlowControlValueEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getTriggerSchedules()
{
    return m_TriggerSchedulesEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getTriggerSchedule()
{
    return m_TriggerScheduleEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getIntegrityCheck()
{
    return m_IntegrityCheckEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getRedundancyManagement()
{
    return m_RedundancyManagementEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getRCRedundancyManagement()
{
    return m_RCRedundancyManagementEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getTTRedundancyManagement()
{
    return m_TTRedundancyManagementEClass;
}
::ecore::EClass_ptr Device_SpecificationPackage::getPeriods()
{
    return m_PeriodsEClass;
}
::ecore::EEnum_ptr Device_SpecificationPackage::getConstrainType()
{
    return m_ConstrainTypeEEnum;
}
::ecore::EEnum_ptr Device_SpecificationPackage::getTimeSourceEnum()
{
    return m_TimeSourceEnumEEnum;
}
::ecore::EClass_ptr Device_SpecificationPackage::getFrameRelayDescriptor()
{
    return m_FrameRelayDescriptorEClass;
}

::ecore::EReference_ptr Device_SpecificationPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__metaInformation()
{
    return m_DeviceSpecification__metaInformation;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__units()
{
    return m_DeviceSpecification__units;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__bagAccounts()
{
    return m_DeviceSpecification__bagAccounts;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__vlSchedules()
{
    return m_DeviceSpecification__vlSchedules;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__bestEffortRouting()
{
    return m_DeviceSpecification__bestEffortRouting;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__flowControl()
{
    return m_DeviceSpecification__flowControl;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__periods()
{
    return m_DeviceSpecification__periods;
}
::ecore::EReference_ptr Device_SpecificationPackage::getDeviceSpecification__refDeviceMapping()
{
    return m_DeviceSpecification__refDeviceMapping;
}
::ecore::EReference_ptr Device_SpecificationPackage::getEndSystem__config()
{
    return m_EndSystem__config;
}
::ecore::EReference_ptr Device_SpecificationPackage::getEndSystem__triggerSchedules()
{
    return m_EndSystem__triggerSchedules;
}
::ecore::EReference_ptr Device_SpecificationPackage::getSwitch__config()
{
    return m_Switch__config;
}
::ecore::EReference_ptr Device_SpecificationPackage::getEModelElement__eAnnotations()
{
    return m_EModelElement__eAnnotations;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getENamedElement__name()
{
    return m_ENamedElement__name;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getDeviceConfig__ctMarker()
{
    return m_DeviceConfig__ctMarker;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getDeviceConfig__ctMask()
{
    return m_DeviceConfig__ctMask;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getEndSystemConfig__tsSource()
{
    return m_EndSystemConfig__tsSource;
}
::ecore::EReference_ptr Device_SpecificationPackage::getEndSystemConfig__externalClockSynchronization()
{
    return m_EndSystemConfig__externalClockSynchronization;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getEndSystemConfig__sourceMacAddress()
{
    return m_EndSystemConfig__sourceMacAddress;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getEndSystemConfig__destMacAddressCF()
{
    return m_EndSystemConfig__destMacAddressCF;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getEndSystemConfig__externalSyncAckRequired()
{
    return m_EndSystemConfig__externalSyncAckRequired;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getExternalClockSynchronization__maxExtCorrValue()
{
    return m_ExternalClockSynchronization__maxExtCorrValue;
}
::ecore::EReference_ptr Device_SpecificationPackage::getBagAccounts__incomingBagAccount()
{
    return m_BagAccounts__incomingBagAccount;
}
::ecore::EReference_ptr Device_SpecificationPackage::getBagAccounts__outgoingBagAccount()
{
    return m_BagAccounts__outgoingBagAccount;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getBagAccount__bag()
{
    return m_BagAccount__bag;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getBagAccount__jitter()
{
    return m_BagAccount__jitter;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getBagAccount__constrainType()
{
    return m_BagAccount__constrainType;
}
::ecore::EReference_ptr Device_SpecificationPackage::getVirtualLinkSchedules__vlSchedule()
{
    return m_VirtualLinkSchedules__vlSchedule;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getVirtualLinkSchedules__scheduleStartAfterSync()
{
    return m_VirtualLinkSchedules__scheduleStartAfterSync;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getVirtualLinkSchedule__priority()
{
    return m_VirtualLinkSchedule__priority;
}
::ecore::EReference_ptr Device_SpecificationPackage::getVirtualLinkSchedule__refVirtualLink()
{
    return m_VirtualLinkSchedule__refVirtualLink;
}
::ecore::EReference_ptr Device_SpecificationPackage::getVirtualLinkSchedule__incoming()
{
    return m_VirtualLinkSchedule__incoming;
}
::ecore::EReference_ptr Device_SpecificationPackage::getBuffers__buffer()
{
    return m_Buffers__buffer;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getFIFOQueue__length()
{
    return m_FIFOQueue__length;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getFrameRelayDescriptor__bufferDepth()
{
    return m_FrameRelayDescriptor__bufferDepth;
}
::ecore::EReference_ptr Device_SpecificationPackage::getIncoming__outgoing()
{
    return m_Incoming__outgoing;
}
::ecore::EReference_ptr Device_SpecificationPackage::getIncoming__refInPort()
{
    return m_Incoming__refInPort;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getCTIncoming__removeSequenceNumber()
{
    return m_CTIncoming__removeSequenceNumber;
}
::ecore::EReference_ptr Device_SpecificationPackage::getCTIncoming__redundancyFunction()
{
    return m_CTIncoming__redundancyFunction;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getOutgoing__appendSequenceNumber()
{
    return m_Outgoing__appendSequenceNumber;
}
::ecore::EReference_ptr Device_SpecificationPackage::getOutgoing__refOutPort()
{
    return m_Outgoing__refOutPort;
}
::ecore::EReference_ptr Device_SpecificationPackage::getRCIncoming__refBagAccount()
{
    return m_RCIncoming__refBagAccount;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getTTIncoming__receiveWindowStart()
{
    return m_TTIncoming__receiveWindowStart;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getTTIncoming__receiveWindowEnd()
{
    return m_TTIncoming__receiveWindowEnd;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getTTIncoming__permanencePit()
{
    return m_TTIncoming__permanencePit;
}
::ecore::EReference_ptr Device_SpecificationPackage::getTTIncoming__refPeriod()
{
    return m_TTIncoming__refPeriod;
}
::ecore::EReference_ptr Device_SpecificationPackage::getRCOutgoing__refBagAccount()
{
    return m_RCOutgoing__refBagAccount;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getRCOutgoing__maxDispatchDelay()
{
    return m_RCOutgoing__maxDispatchDelay;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getTTOutgoing__sendWindowStart()
{
    return m_TTOutgoing__sendWindowStart;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getTTOutgoing__sendWindowEnd()
{
    return m_TTOutgoing__sendWindowEnd;
}
::ecore::EReference_ptr Device_SpecificationPackage::getTTOutgoing__refPeriod()
{
    return m_TTOutgoing__refPeriod;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getBestEffortRouting__enableDynamicRouting()
{
    return m_BestEffortRouting__enableDynamicRouting;
}
::ecore::EReference_ptr Device_SpecificationPackage::getBestEffortRouting__beRouteIncoming()
{
    return m_BestEffortRouting__beRouteIncoming;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getBERouteIncoming__destinationMacAddress()
{
    return m_BERouteIncoming__destinationMacAddress;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getBERouteIncoming__addrMask()
{
    return m_BERouteIncoming__addrMask;
}
::ecore::EReference_ptr Device_SpecificationPackage::getFlowControl__xon()
{
    return m_FlowControl__xon;
}
::ecore::EReference_ptr Device_SpecificationPackage::getFlowControl__xoff()
{
    return m_FlowControl__xoff;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getFlowControlValue__value()
{
    return m_FlowControlValue__value;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getFlowControlValue__threshold()
{
    return m_FlowControlValue__threshold;
}
::ecore::EReference_ptr Device_SpecificationPackage::getTriggerSchedules__triggerSchedule()
{
    return m_TriggerSchedules__triggerSchedule;
}
::ecore::EReference_ptr Device_SpecificationPackage::getTriggerSchedule__refPeriod()
{
    return m_TriggerSchedule__refPeriod;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getRedundancyManagement__redundancyTimeout()
{
    return m_RedundancyManagement__redundancyTimeout;
}
::ecore::EAttribute_ptr Device_SpecificationPackage::getRCRedundancyManagement__maxSequenceNumberRange()
{
    return m_RCRedundancyManagement__maxSequenceNumberRange;
}
::ecore::EReference_ptr Device_SpecificationPackage::getPeriods__period()
{
    return m_Periods__period;
}

