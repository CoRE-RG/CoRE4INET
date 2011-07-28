// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Device_Target_MappingPackageImpl.cpp
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

#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <Device_Target_Mapping/Device_Target_MappingFactory.hpp>
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
#include <Device_Targets/Device_TargetsPackage.hpp>
#include <System_Specification/System_SpecificationPackage.hpp>
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Virtuallink_Map/Virtuallink_MapPackage.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetDevice.hpp>
#include <Device_Targets/AntiMasquerading.hpp>
#include <Device_Targets/Diagnostic.hpp>
#include <Device_Targets/ManagementInterface.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <Device_Specification/TriggerSchedule.hpp>
#include <Device_Targets/TargetPort.hpp>
#include <System_Specification/Port.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>

using namespace ::Device_Target_Mapping;

Device_Target_MappingPackage::Device_Target_MappingPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = Device_Target_MappingFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // DeviceMapping
    m_DeviceMappingEClass = new ::ecore::EClass();
    m_DeviceMappingEClass->setClassifierID(DEVICEMAPPING);
    m_DeviceMappingEClass->setEPackage(this);
    getEClassifiers().push_back(m_DeviceMappingEClass);
    m_DeviceMapping__agingTime = new ::ecore::EAttribute();
    m_DeviceMapping__agingTime->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__AGINGTIME);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__agingTime);
    m_DeviceMapping__refTargetDevice = new ::ecore::EReference();
    m_DeviceMapping__refTargetDevice->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__REFTARGETDEVICE);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__refTargetDevice);
    m_DeviceMapping__perPortBagAccounts = new ::ecore::EReference();
    m_DeviceMapping__perPortBagAccounts->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PERPORTBAGACCOUNTS);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__perPortBagAccounts);
    m_DeviceMapping__portMappings = new ::ecore::EReference();
    m_DeviceMapping__portMappings->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PORTMAPPINGS);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__portMappings);
    m_DeviceMapping__antiMasquerading = new ::ecore::EReference();
    m_DeviceMapping__antiMasquerading->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__ANTIMASQUERADING);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__antiMasquerading);
    m_DeviceMapping__diagnostic = new ::ecore::EReference();
    m_DeviceMapping__diagnostic->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__DIAGNOSTIC);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__diagnostic);
    m_DeviceMapping__trigger = new ::ecore::EReference();
    m_DeviceMapping__trigger->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__TRIGGER);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__trigger);
    m_DeviceMapping__bufferMapping = new ::ecore::EReference();
    m_DeviceMapping__bufferMapping->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__BUFFERMAPPING);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__bufferMapping);
    m_DeviceMapping__managementInterface = new ::ecore::EReference();
    m_DeviceMapping__managementInterface->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__MANAGEMENTINTERFACE);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__managementInterface);
    m_DeviceMapping__metaInformation = new ::ecore::EReference();
    m_DeviceMapping__metaInformation->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__METAINFORMATION);
    m_DeviceMappingEClass->getEStructuralFeatures().push_back(
            m_DeviceMapping__metaInformation);

    // InputBuffer
    m_InputBufferEClass = new ::ecore::EClass();
    m_InputBufferEClass->setClassifierID(INPUTBUFFER);
    m_InputBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_InputBufferEClass);

    // Trigger
    m_TriggerEClass = new ::ecore::EClass();
    m_TriggerEClass->setClassifierID(TRIGGER);
    m_TriggerEClass->setEPackage(this);
    getEClassifiers().push_back(m_TriggerEClass);
    m_Trigger__device = new ::ecore::EAttribute();
    m_Trigger__device->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::TRIGGER__DEVICE);
    m_TriggerEClass->getEStructuralFeatures().push_back(m_Trigger__device);
    m_Trigger__target = new ::ecore::EAttribute();
    m_Trigger__target->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::TRIGGER__TARGET);
    m_TriggerEClass->getEStructuralFeatures().push_back(m_Trigger__target);
    m_Trigger__refTriggerSchedule = new ::ecore::EReference();
    m_Trigger__refTriggerSchedule->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::TRIGGER__REFTRIGGERSCHEDULE);
    m_TriggerEClass->getEStructuralFeatures().push_back(
            m_Trigger__refTriggerSchedule);

    // PortMapping
    m_PortMappingEClass = new ::ecore::EClass();
    m_PortMappingEClass->setClassifierID(PORTMAPPING);
    m_PortMappingEClass->setEPackage(this);
    getEClassifiers().push_back(m_PortMappingEClass);
    m_PortMapping__rxLatencyCorrection = new ::ecore::EAttribute();
    m_PortMapping__rxLatencyCorrection->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__RXLATENCYCORRECTION);
    m_PortMappingEClass->getEStructuralFeatures().push_back(
            m_PortMapping__rxLatencyCorrection);
    m_PortMapping__txLatencyCorrection = new ::ecore::EAttribute();
    m_PortMapping__txLatencyCorrection->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__TXLATENCYCORRECTION);
    m_PortMappingEClass->getEStructuralFeatures().push_back(
            m_PortMapping__txLatencyCorrection);
    m_PortMapping__disableRxFc = new ::ecore::EAttribute();
    m_PortMapping__disableRxFc->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLERXFC);
    m_PortMappingEClass->getEStructuralFeatures().push_back(
            m_PortMapping__disableRxFc);
    m_PortMapping__disableTxFc = new ::ecore::EAttribute();
    m_PortMapping__disableTxFc->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLETXFC);
    m_PortMappingEClass->getEStructuralFeatures().push_back(
            m_PortMapping__disableTxFc);
    m_PortMapping__refTargetPort = new ::ecore::EReference();
    m_PortMapping__refTargetPort->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFTARGETPORT);
    m_PortMappingEClass->getEStructuralFeatures().push_back(
            m_PortMapping__refTargetPort);
    m_PortMapping__refPort = new ::ecore::EReference();
    m_PortMapping__refPort->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFPORT);
    m_PortMappingEClass->getEStructuralFeatures().push_back(
            m_PortMapping__refPort);

    // CriticalTrafficBuffer
    m_CriticalTrafficBufferEClass = new ::ecore::EClass();
    m_CriticalTrafficBufferEClass->setClassifierID(CRITICALTRAFFICBUFFER);
    m_CriticalTrafficBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_CriticalTrafficBufferEClass);

    // SharedBuffer
    m_SharedBufferEClass = new ::ecore::EClass();
    m_SharedBufferEClass->setClassifierID(SHAREDBUFFER);
    m_SharedBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_SharedBufferEClass);
    m_SharedBuffer__refVirtualLink = new ::ecore::EReference();
    m_SharedBuffer__refVirtualLink->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::SHAREDBUFFER__REFVIRTUALLINK);
    m_SharedBufferEClass->getEStructuralFeatures().push_back(
            m_SharedBuffer__refVirtualLink);

    // DedicatedBuffer
    m_DedicatedBufferEClass = new ::ecore::EClass();
    m_DedicatedBufferEClass->setClassifierID(DEDICATEDBUFFER);
    m_DedicatedBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_DedicatedBufferEClass);
    m_DedicatedBuffer__refVirtualLink = new ::ecore::EReference();
    m_DedicatedBuffer__refVirtualLink->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEDICATEDBUFFER__REFVIRTUALLINK);
    m_DedicatedBufferEClass->getEStructuralFeatures().push_back(
            m_DedicatedBuffer__refVirtualLink);

    // Mappings
    m_MappingsEClass = new ::ecore::EClass();
    m_MappingsEClass->setClassifierID(MAPPINGS);
    m_MappingsEClass->setEPackage(this);
    getEClassifiers().push_back(m_MappingsEClass);
    m_Mappings__deviceMappings = new ::ecore::EReference();
    m_Mappings__deviceMappings->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__DEVICEMAPPINGS);
    m_MappingsEClass->getEStructuralFeatures().push_back(
            m_Mappings__deviceMappings);
    m_Mappings__containingVirtualLinkMapping = new ::ecore::EReference();
    m_Mappings__containingVirtualLinkMapping->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__CONTAININGVIRTUALLINKMAPPING);
    m_MappingsEClass->getEStructuralFeatures().push_back(
            m_Mappings__containingVirtualLinkMapping);
    m_Mappings__metaInformation = new ::ecore::EReference();
    m_Mappings__metaInformation->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__METAINFORMATION);
    m_MappingsEClass->getEStructuralFeatures().push_back(
            m_Mappings__metaInformation);
    m_Mappings__refVirtualLinkMappings = new ::ecore::EReference();
    m_Mappings__refVirtualLinkMappings->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__REFVIRTUALLINKMAPPINGS);
    m_MappingsEClass->getEStructuralFeatures().push_back(
            m_Mappings__refVirtualLinkMappings);

    // PortMappings
    m_PortMappingsEClass = new ::ecore::EClass();
    m_PortMappingsEClass->setClassifierID(PORTMAPPINGS);
    m_PortMappingsEClass->setEPackage(this);
    getEClassifiers().push_back(m_PortMappingsEClass);
    m_PortMappings__metaInformation = new ::ecore::EReference();
    m_PortMappings__metaInformation->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPINGS__METAINFORMATION);
    m_PortMappingsEClass->getEStructuralFeatures().push_back(
            m_PortMappings__metaInformation);

    // DeviceMappings
    m_DeviceMappingsEClass = new ::ecore::EClass();
    m_DeviceMappingsEClass->setClassifierID(DEVICEMAPPINGS);
    m_DeviceMappingsEClass->setEPackage(this);
    getEClassifiers().push_back(m_DeviceMappingsEClass);
    m_DeviceMappings__deviceMapping = new ::ecore::EReference();
    m_DeviceMappings__deviceMapping->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPINGS__DEVICEMAPPING);
    m_DeviceMappingsEClass->getEStructuralFeatures().push_back(
            m_DeviceMappings__deviceMapping);
    m_DeviceMappings__metaInformation = new ::ecore::EReference();
    m_DeviceMappings__metaInformation->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPINGS__METAINFORMATION);
    m_DeviceMappingsEClass->getEStructuralFeatures().push_back(
            m_DeviceMappings__metaInformation);

    // OutputBuffers
    m_OutputBuffersEClass = new ::ecore::EClass();
    m_OutputBuffersEClass->setClassifierID(OUTPUTBUFFERS);
    m_OutputBuffersEClass->setEPackage(this);
    getEClassifiers().push_back(m_OutputBuffersEClass);
    m_OutputBuffers__dedicatedBuffer = new ::ecore::EReference();
    m_OutputBuffers__dedicatedBuffer->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__DEDICATEDBUFFER);
    m_OutputBuffersEClass->getEStructuralFeatures().push_back(
            m_OutputBuffers__dedicatedBuffer);
    m_OutputBuffers__sharedBuffer = new ::ecore::EReference();
    m_OutputBuffers__sharedBuffer->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__SHAREDBUFFER);
    m_OutputBuffersEClass->getEStructuralFeatures().push_back(
            m_OutputBuffers__sharedBuffer);
    m_OutputBuffers__cotsBuffer = new ::ecore::EReference();
    m_OutputBuffers__cotsBuffer->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__COTSBUFFER);
    m_OutputBuffersEClass->getEStructuralFeatures().push_back(
            m_OutputBuffers__cotsBuffer);

    // InputBuffers
    m_InputBuffersEClass = new ::ecore::EClass();
    m_InputBuffersEClass->setClassifierID(INPUTBUFFERS);
    m_InputBuffersEClass->setEPackage(this);
    getEClassifiers().push_back(m_InputBuffersEClass);
    m_InputBuffers__sharedBuffer = new ::ecore::EReference();
    m_InputBuffers__sharedBuffer->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::INPUTBUFFERS__SHAREDBUFFER);
    m_InputBuffersEClass->getEStructuralFeatures().push_back(
            m_InputBuffers__sharedBuffer);
    m_InputBuffers__dedicatedBuffer = new ::ecore::EReference();
    m_InputBuffers__dedicatedBuffer->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::INPUTBUFFERS__DEDICATEDBUFFER);
    m_InputBuffersEClass->getEStructuralFeatures().push_back(
            m_InputBuffers__dedicatedBuffer);
    m_InputBuffers__cotsBuffer = new ::ecore::EReference();
    m_InputBuffers__cotsBuffer->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::INPUTBUFFERS__COTSBUFFER);
    m_InputBuffersEClass->getEStructuralFeatures().push_back(
            m_InputBuffers__cotsBuffer);

    // BufferMapping
    m_BufferMappingEClass = new ::ecore::EClass();
    m_BufferMappingEClass->setClassifierID(BUFFERMAPPING);
    m_BufferMappingEClass->setEPackage(this);
    getEClassifiers().push_back(m_BufferMappingEClass);
    m_BufferMapping__outputBuffers = new ::ecore::EReference();
    m_BufferMapping__outputBuffers->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFERMAPPING__OUTPUTBUFFERS);
    m_BufferMappingEClass->getEStructuralFeatures().push_back(
            m_BufferMapping__outputBuffers);
    m_BufferMapping__inputBuffers = new ::ecore::EReference();
    m_BufferMapping__inputBuffers->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFERMAPPING__INPUTBUFFERS);
    m_BufferMappingEClass->getEStructuralFeatures().push_back(
            m_BufferMapping__inputBuffers);
    m_BufferMapping__metaInformation = new ::ecore::EReference();
    m_BufferMapping__metaInformation->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFERMAPPING__METAINFORMATION);
    m_BufferMappingEClass->getEStructuralFeatures().push_back(
            m_BufferMapping__metaInformation);

    // MemoryBuffer
    m_MemoryBufferEClass = new ::ecore::EClass();
    m_MemoryBufferEClass->setClassifierID(MEMORYBUFFER);
    m_MemoryBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_MemoryBufferEClass);
    m_MemoryBuffer__baseAddress = new ::ecore::EAttribute();
    m_MemoryBuffer__baseAddress->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::MEMORYBUFFER__BASEADDRESS);
    m_MemoryBufferEClass->getEStructuralFeatures().push_back(
            m_MemoryBuffer__baseAddress);

    // Buffer
    m_BufferEClass = new ::ecore::EClass();
    m_BufferEClass->setClassifierID(BUFFER);
    m_BufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_BufferEClass);
    m_Buffer__type = new ::ecore::EAttribute();
    m_Buffer__type->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__TYPE);
    m_BufferEClass->getEStructuralFeatures().push_back(m_Buffer__type);
    m_Buffer__depth = new ::ecore::EAttribute();
    m_Buffer__depth->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__DEPTH);
    m_BufferEClass->getEStructuralFeatures().push_back(m_Buffer__depth);
    m_Buffer__size = new ::ecore::EAttribute();
    m_Buffer__size->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__SIZE);
    m_BufferEClass->getEStructuralFeatures().push_back(m_Buffer__size);
    m_Buffer__flushOnScheduleReset = new ::ecore::EAttribute();
    m_Buffer__flushOnScheduleReset->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__FLUSHONSCHEDULERESET);
    m_BufferEClass->getEStructuralFeatures().push_back(
            m_Buffer__flushOnScheduleReset);

    // COTSBuffer
    m_COTSBufferEClass = new ::ecore::EClass();
    m_COTSBufferEClass->setClassifierID(COTSBUFFER);
    m_COTSBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_COTSBufferEClass);
    m_COTSBuffer__refTargetPort = new ::ecore::EReference();
    m_COTSBuffer__refTargetPort->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::COTSBUFFER__REFTARGETPORT);
    m_COTSBufferEClass->getEStructuralFeatures().push_back(
            m_COTSBuffer__refTargetPort);

    // HostBuffer
    m_HostBufferEClass = new ::ecore::EClass();
    m_HostBufferEClass->setClassifierID(HOSTBUFFER);
    m_HostBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_HostBufferEClass);

    // QueuedOutputBuffer
    m_QueuedOutputBufferEClass = new ::ecore::EClass();
    m_QueuedOutputBufferEClass->setClassifierID(QUEUEDOUTPUTBUFFER);
    m_QueuedOutputBufferEClass->setEPackage(this);
    getEClassifiers().push_back(m_QueuedOutputBufferEClass);
    m_QueuedOutputBuffer__refOutVirtualLink = new ::ecore::EReference();
    m_QueuedOutputBuffer__refOutVirtualLink->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::QUEUEDOUTPUTBUFFER__REFOUTVIRTUALLINK);
    m_QueuedOutputBufferEClass->getEStructuralFeatures().push_back(
            m_QueuedOutputBuffer__refOutVirtualLink);

    // SwPortMapping
    m_SwPortMappingEClass = new ::ecore::EClass();
    m_SwPortMappingEClass->setClassifierID(SWPORTMAPPING);
    m_SwPortMappingEClass->setEPackage(this);
    getEClassifiers().push_back(m_SwPortMappingEClass);
    m_SwPortMapping__addressLearningEnable = new ::ecore::EAttribute();
    m_SwPortMapping__addressLearningEnable->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPING__ADDRESSLEARNINGENABLE);
    m_SwPortMappingEClass->getEStructuralFeatures().push_back(
            m_SwPortMapping__addressLearningEnable);
    m_SwPortMapping__broadcastForwardEnable = new ::ecore::EAttribute();
    m_SwPortMapping__broadcastForwardEnable->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPING__BROADCASTFORWARDENABLE);
    m_SwPortMappingEClass->getEStructuralFeatures().push_back(
            m_SwPortMapping__broadcastForwardEnable);
    m_SwPortMapping__refPerPortBroadcastBagAccount = new ::ecore::EReference();
    m_SwPortMapping__refPerPortBroadcastBagAccount->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPING__REFPERPORTBROADCASTBAGACCOUNT);
    m_SwPortMappingEClass->getEStructuralFeatures().push_back(
            m_SwPortMapping__refPerPortBroadcastBagAccount);
    m_SwPortMapping__refPerPortUniCastBagAccount = new ::ecore::EReference();
    m_SwPortMapping__refPerPortUniCastBagAccount->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPING__REFPERPORTUNICASTBAGACCOUNT);
    m_SwPortMappingEClass->getEStructuralFeatures().push_back(
            m_SwPortMapping__refPerPortUniCastBagAccount);

    // EsPortMapping
    m_EsPortMappingEClass = new ::ecore::EClass();
    m_EsPortMappingEClass->setClassifierID(ESPORTMAPPING);
    m_EsPortMappingEClass->setEPackage(this);
    getEClassifiers().push_back(m_EsPortMappingEClass);

    // PerPortBagAccounts
    m_PerPortBagAccountsEClass = new ::ecore::EClass();
    m_PerPortBagAccountsEClass->setClassifierID(PERPORTBAGACCOUNTS);
    m_PerPortBagAccountsEClass->setEPackage(this);
    getEClassifiers().push_back(m_PerPortBagAccountsEClass);
    m_PerPortBagAccounts__perPortBagSetting = new ::ecore::EReference();
    m_PerPortBagAccounts__perPortBagSetting->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::PERPORTBAGACCOUNTS__PERPORTBAGSETTING);
    m_PerPortBagAccountsEClass->getEStructuralFeatures().push_back(
            m_PerPortBagAccounts__perPortBagSetting);

    // PerPortBagAccount
    m_PerPortBagAccountEClass = new ::ecore::EClass();
    m_PerPortBagAccountEClass->setClassifierID(PERPORTBAGACCOUNT);
    m_PerPortBagAccountEClass->setEPackage(this);
    getEClassifiers().push_back(m_PerPortBagAccountEClass);

    // SwPortMappings
    m_SwPortMappingsEClass = new ::ecore::EClass();
    m_SwPortMappingsEClass->setClassifierID(SWPORTMAPPINGS);
    m_SwPortMappingsEClass->setEPackage(this);
    getEClassifiers().push_back(m_SwPortMappingsEClass);
    m_SwPortMappings__targetPortMapping = new ::ecore::EReference();
    m_SwPortMappings__targetPortMapping->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPINGS__TARGETPORTMAPPING);
    m_SwPortMappingsEClass->getEStructuralFeatures().push_back(
            m_SwPortMappings__targetPortMapping);

    // EsPortMappings
    m_EsPortMappingsEClass = new ::ecore::EClass();
    m_EsPortMappingsEClass->setClassifierID(ESPORTMAPPINGS);
    m_EsPortMappingsEClass->setEPackage(this);
    getEClassifiers().push_back(m_EsPortMappingsEClass);
    m_EsPortMappings__targetPortMapping = new ::ecore::EReference();
    m_EsPortMappings__targetPortMapping->setFeatureID(
            ::Device_Target_Mapping::Device_Target_MappingPackage::ESPORTMAPPINGS__TARGETPORTMAPPING);
    m_EsPortMappingsEClass->getEStructuralFeatures().push_back(
            m_EsPortMappings__targetPortMapping);

    // Create enums

    m_BufferTypeEnumEEnum = new ::ecore::EEnum();
    m_BufferTypeEnumEEnum->setClassifierID(BUFFERTYPEENUM);
    m_BufferTypeEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_BufferTypeEnumEEnum);

    // Create data types

    m_FrequencyTypeEDataType = new ::ecore::EDataType();
    m_FrequencyTypeEDataType->setClassifierID(FREQUENCYTYPE);
    m_FrequencyTypeEDataType->setEPackage(this);
    getEClassifiers().push_back(m_FrequencyTypeEDataType);

    m_MemoryAddressEDataType = new ::ecore::EDataType();
    m_MemoryAddressEDataType->setClassifierID(MEMORYADDRESS);
    m_MemoryAddressEDataType->setEPackage(this);
    getEClassifiers().push_back(m_MemoryAddressEDataType);

    // Initialize package
    setName("Device_Target_Mapping");
    setNsPrefix("dm");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/Device_Target_Mapping_V1");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_DeviceMappingEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_InputBufferEClass->getESuperTypes().push_back(m_MemoryBufferEClass);
    m_TriggerEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_PortMappingEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_CriticalTrafficBufferEClass->getESuperTypes().push_back(
            m_HostBufferEClass);
    m_SharedBufferEClass->getESuperTypes().push_back(
            m_CriticalTrafficBufferEClass);
    m_DedicatedBufferEClass->getESuperTypes().push_back(
            m_CriticalTrafficBufferEClass);
    m_MappingsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_PortMappingsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_DeviceMappingsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_OutputBuffersEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_InputBuffersEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_BufferMappingEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_MemoryBufferEClass->getESuperTypes().push_back(m_BufferEClass);
    m_BufferEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_COTSBufferEClass->getESuperTypes().push_back(m_HostBufferEClass);
    m_HostBufferEClass->getESuperTypes().push_back(m_MemoryBufferEClass);
    m_QueuedOutputBufferEClass->getESuperTypes().push_back(m_HostBufferEClass);
    m_SwPortMappingEClass->getESuperTypes().push_back(m_PortMappingEClass);
    m_EsPortMappingEClass->getESuperTypes().push_back(m_PortMappingEClass);
    m_PerPortBagAccountsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_PerPortBagAccountEClass->getESuperTypes().push_back(
            dynamic_cast< ::Device_Specification::Device_SpecificationPackage* > (::Device_Specification::Device_SpecificationPackage::_instance())->getBagAccount());
    m_SwPortMappingsEClass->getESuperTypes().push_back(m_PortMappingsEClass);
    m_EsPortMappingsEClass->getESuperTypes().push_back(m_PortMappingsEClass);

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // DeviceMapping
    m_DeviceMappingEClass->setName("DeviceMapping");
    m_DeviceMappingEClass->setAbstract(false);
    m_DeviceMappingEClass->setInterface(false);
    m_DeviceMapping__agingTime->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_DeviceMapping__agingTime->setName("agingTime");
    m_DeviceMapping__agingTime->setDefaultValueLiteral("300s");
    m_DeviceMapping__agingTime->setLowerBound(0);
    m_DeviceMapping__agingTime->setUpperBound(1);
    m_DeviceMapping__agingTime->setTransient(false);
    m_DeviceMapping__agingTime->setVolatile(false);
    m_DeviceMapping__agingTime->setChangeable(true);
    m_DeviceMapping__agingTime->setUnsettable(false);
    m_DeviceMapping__agingTime->setID(false);
    m_DeviceMapping__agingTime->setUnique(true);
    m_DeviceMapping__agingTime->setDerived(false);
    m_DeviceMapping__agingTime->setOrdered(true);
    m_DeviceMapping__refTargetDevice->setEType(
            dynamic_cast< ::Device_Targets::Device_TargetsPackage* > (::Device_Targets::Device_TargetsPackage::_instance())->getTargetDevice());
    m_DeviceMapping__refTargetDevice->setName("refTargetDevice");
    m_DeviceMapping__refTargetDevice->setDefaultValueLiteral("");
    m_DeviceMapping__refTargetDevice->setLowerBound(1);
    m_DeviceMapping__refTargetDevice->setUpperBound(1);
    m_DeviceMapping__refTargetDevice->setTransient(false);
    m_DeviceMapping__refTargetDevice->setVolatile(false);
    m_DeviceMapping__refTargetDevice->setChangeable(true);
    m_DeviceMapping__refTargetDevice->setContainment(false);
    m_DeviceMapping__refTargetDevice->setResolveProxies(true);
    m_DeviceMapping__refTargetDevice->setUnique(true);
    m_DeviceMapping__refTargetDevice->setDerived(false);
    m_DeviceMapping__refTargetDevice->setOrdered(true);
    m_DeviceMapping__perPortBagAccounts->setEType(m_PerPortBagAccountsEClass);
    m_DeviceMapping__perPortBagAccounts->setName("perPortBagAccounts");
    m_DeviceMapping__perPortBagAccounts->setDefaultValueLiteral("");
    m_DeviceMapping__perPortBagAccounts->setLowerBound(0);
    m_DeviceMapping__perPortBagAccounts->setUpperBound(1);
    m_DeviceMapping__perPortBagAccounts->setTransient(false);
    m_DeviceMapping__perPortBagAccounts->setVolatile(false);
    m_DeviceMapping__perPortBagAccounts->setChangeable(true);
    m_DeviceMapping__perPortBagAccounts->setContainment(true);
    m_DeviceMapping__perPortBagAccounts->setResolveProxies(true);
    m_DeviceMapping__perPortBagAccounts->setUnique(true);
    m_DeviceMapping__perPortBagAccounts->setDerived(false);
    m_DeviceMapping__perPortBagAccounts->setOrdered(true);
    m_DeviceMapping__portMappings->setEType(m_PortMappingsEClass);
    m_DeviceMapping__portMappings->setName("portMappings");
    m_DeviceMapping__portMappings->setDefaultValueLiteral("");
    m_DeviceMapping__portMappings->setLowerBound(0);
    m_DeviceMapping__portMappings->setUpperBound(1);
    m_DeviceMapping__portMappings->setTransient(false);
    m_DeviceMapping__portMappings->setVolatile(false);
    m_DeviceMapping__portMappings->setChangeable(true);
    m_DeviceMapping__portMappings->setContainment(true);
    m_DeviceMapping__portMappings->setResolveProxies(true);
    m_DeviceMapping__portMappings->setUnique(true);
    m_DeviceMapping__portMappings->setDerived(false);
    m_DeviceMapping__portMappings->setOrdered(true);
    m_DeviceMapping__antiMasquerading->setEType(
            dynamic_cast< ::Device_Targets::Device_TargetsPackage* > (::Device_Targets::Device_TargetsPackage::_instance())->getAntiMasquerading());
    m_DeviceMapping__antiMasquerading->setName("antiMasquerading");
    m_DeviceMapping__antiMasquerading->setDefaultValueLiteral("");
    m_DeviceMapping__antiMasquerading->setLowerBound(0);
    m_DeviceMapping__antiMasquerading->setUpperBound(-1);
    m_DeviceMapping__antiMasquerading->setTransient(false);
    m_DeviceMapping__antiMasquerading->setVolatile(false);
    m_DeviceMapping__antiMasquerading->setChangeable(true);
    m_DeviceMapping__antiMasquerading->setContainment(true);
    m_DeviceMapping__antiMasquerading->setResolveProxies(true);
    m_DeviceMapping__antiMasquerading->setUnique(true);
    m_DeviceMapping__antiMasquerading->setDerived(false);
    m_DeviceMapping__antiMasquerading->setOrdered(true);
    m_DeviceMapping__diagnostic->setEType(
            dynamic_cast< ::Device_Targets::Device_TargetsPackage* > (::Device_Targets::Device_TargetsPackage::_instance())->getDiagnostic());
    m_DeviceMapping__diagnostic->setName("diagnostic");
    m_DeviceMapping__diagnostic->setDefaultValueLiteral("");
    m_DeviceMapping__diagnostic->setLowerBound(0);
    m_DeviceMapping__diagnostic->setUpperBound(1);
    m_DeviceMapping__diagnostic->setTransient(false);
    m_DeviceMapping__diagnostic->setVolatile(false);
    m_DeviceMapping__diagnostic->setChangeable(true);
    m_DeviceMapping__diagnostic->setContainment(true);
    m_DeviceMapping__diagnostic->setResolveProxies(true);
    m_DeviceMapping__diagnostic->setUnique(true);
    m_DeviceMapping__diagnostic->setDerived(false);
    m_DeviceMapping__diagnostic->setOrdered(true);
    m_DeviceMapping__trigger->setEType(m_TriggerEClass);
    m_DeviceMapping__trigger->setName("trigger");
    m_DeviceMapping__trigger->setDefaultValueLiteral("");
    m_DeviceMapping__trigger->setLowerBound(0);
    m_DeviceMapping__trigger->setUpperBound(-1);
    m_DeviceMapping__trigger->setTransient(false);
    m_DeviceMapping__trigger->setVolatile(false);
    m_DeviceMapping__trigger->setChangeable(true);
    m_DeviceMapping__trigger->setContainment(true);
    m_DeviceMapping__trigger->setResolveProxies(true);
    m_DeviceMapping__trigger->setUnique(true);
    m_DeviceMapping__trigger->setDerived(false);
    m_DeviceMapping__trigger->setOrdered(true);
    m_DeviceMapping__bufferMapping->setEType(m_BufferMappingEClass);
    m_DeviceMapping__bufferMapping->setName("bufferMapping");
    m_DeviceMapping__bufferMapping->setDefaultValueLiteral("");
    m_DeviceMapping__bufferMapping->setLowerBound(0);
    m_DeviceMapping__bufferMapping->setUpperBound(1);
    m_DeviceMapping__bufferMapping->setTransient(false);
    m_DeviceMapping__bufferMapping->setVolatile(false);
    m_DeviceMapping__bufferMapping->setChangeable(true);
    m_DeviceMapping__bufferMapping->setContainment(true);
    m_DeviceMapping__bufferMapping->setResolveProxies(true);
    m_DeviceMapping__bufferMapping->setUnique(true);
    m_DeviceMapping__bufferMapping->setDerived(false);
    m_DeviceMapping__bufferMapping->setOrdered(true);
    m_DeviceMapping__managementInterface->setEType(
            dynamic_cast< ::Device_Targets::Device_TargetsPackage* > (::Device_Targets::Device_TargetsPackage::_instance())->getManagementInterface());
    m_DeviceMapping__managementInterface->setName("managementInterface");
    m_DeviceMapping__managementInterface->setDefaultValueLiteral("");
    m_DeviceMapping__managementInterface->setLowerBound(0);
    m_DeviceMapping__managementInterface->setUpperBound(1);
    m_DeviceMapping__managementInterface->setTransient(false);
    m_DeviceMapping__managementInterface->setVolatile(false);
    m_DeviceMapping__managementInterface->setChangeable(true);
    m_DeviceMapping__managementInterface->setContainment(true);
    m_DeviceMapping__managementInterface->setResolveProxies(true);
    m_DeviceMapping__managementInterface->setUnique(true);
    m_DeviceMapping__managementInterface->setDerived(false);
    m_DeviceMapping__managementInterface->setOrdered(true);
    m_DeviceMapping__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_DeviceMapping__metaInformation->setName("metaInformation");
    m_DeviceMapping__metaInformation->setDefaultValueLiteral("");
    m_DeviceMapping__metaInformation->setLowerBound(0);
    m_DeviceMapping__metaInformation->setUpperBound(1);
    m_DeviceMapping__metaInformation->setTransient(false);
    m_DeviceMapping__metaInformation->setVolatile(false);
    m_DeviceMapping__metaInformation->setChangeable(true);
    m_DeviceMapping__metaInformation->setContainment(true);
    m_DeviceMapping__metaInformation->setResolveProxies(true);
    m_DeviceMapping__metaInformation->setUnique(true);
    m_DeviceMapping__metaInformation->setDerived(false);
    m_DeviceMapping__metaInformation->setOrdered(true);
    // InputBuffer
    m_InputBufferEClass->setName("InputBuffer");
    m_InputBufferEClass->setAbstract(true);
    m_InputBufferEClass->setInterface(false);
    // Trigger
    m_TriggerEClass->setName("Trigger");
    m_TriggerEClass->setAbstract(false);
    m_TriggerEClass->setInterface(false);
    m_Trigger__device->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Trigger__device->setName("device");
    m_Trigger__device->setDefaultValueLiteral("");
    m_Trigger__device->setLowerBound(1);
    m_Trigger__device->setUpperBound(1);
    m_Trigger__device->setTransient(false);
    m_Trigger__device->setVolatile(false);
    m_Trigger__device->setChangeable(true);
    m_Trigger__device->setUnsettable(false);
    m_Trigger__device->setID(false);
    m_Trigger__device->setUnique(true);
    m_Trigger__device->setDerived(false);
    m_Trigger__device->setOrdered(true);
    m_Trigger__target->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Trigger__target->setName("target");
    m_Trigger__target->setDefaultValueLiteral("");
    m_Trigger__target->setLowerBound(1);
    m_Trigger__target->setUpperBound(1);
    m_Trigger__target->setTransient(false);
    m_Trigger__target->setVolatile(false);
    m_Trigger__target->setChangeable(true);
    m_Trigger__target->setUnsettable(false);
    m_Trigger__target->setID(false);
    m_Trigger__target->setUnique(true);
    m_Trigger__target->setDerived(false);
    m_Trigger__target->setOrdered(true);
    m_Trigger__refTriggerSchedule->setEType(
            dynamic_cast< ::Device_Specification::Device_SpecificationPackage* > (::Device_Specification::Device_SpecificationPackage::_instance())->getTriggerSchedule());
    m_Trigger__refTriggerSchedule->setName("refTriggerSchedule");
    m_Trigger__refTriggerSchedule->setDefaultValueLiteral("");
    m_Trigger__refTriggerSchedule->setLowerBound(0);
    m_Trigger__refTriggerSchedule->setUpperBound(1);
    m_Trigger__refTriggerSchedule->setTransient(false);
    m_Trigger__refTriggerSchedule->setVolatile(false);
    m_Trigger__refTriggerSchedule->setChangeable(true);
    m_Trigger__refTriggerSchedule->setContainment(false);
    m_Trigger__refTriggerSchedule->setResolveProxies(true);
    m_Trigger__refTriggerSchedule->setUnique(true);
    m_Trigger__refTriggerSchedule->setDerived(false);
    m_Trigger__refTriggerSchedule->setOrdered(true);
    // PortMapping
    m_PortMappingEClass->setName("PortMapping");
    m_PortMappingEClass->setAbstract(true);
    m_PortMappingEClass->setInterface(false);
    m_PortMapping__rxLatencyCorrection->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_PortMapping__rxLatencyCorrection->setName("rxLatencyCorrection");
    m_PortMapping__rxLatencyCorrection->setDefaultValueLiteral("0ps");
    m_PortMapping__rxLatencyCorrection->setLowerBound(0);
    m_PortMapping__rxLatencyCorrection->setUpperBound(1);
    m_PortMapping__rxLatencyCorrection->setTransient(false);
    m_PortMapping__rxLatencyCorrection->setVolatile(false);
    m_PortMapping__rxLatencyCorrection->setChangeable(true);
    m_PortMapping__rxLatencyCorrection->setUnsettable(false);
    m_PortMapping__rxLatencyCorrection->setID(false);
    m_PortMapping__rxLatencyCorrection->setUnique(true);
    m_PortMapping__rxLatencyCorrection->setDerived(false);
    m_PortMapping__rxLatencyCorrection->setOrdered(true);
    m_PortMapping__txLatencyCorrection->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_PortMapping__txLatencyCorrection->setName("txLatencyCorrection");
    m_PortMapping__txLatencyCorrection->setDefaultValueLiteral("0ps");
    m_PortMapping__txLatencyCorrection->setLowerBound(0);
    m_PortMapping__txLatencyCorrection->setUpperBound(1);
    m_PortMapping__txLatencyCorrection->setTransient(false);
    m_PortMapping__txLatencyCorrection->setVolatile(false);
    m_PortMapping__txLatencyCorrection->setChangeable(true);
    m_PortMapping__txLatencyCorrection->setUnsettable(false);
    m_PortMapping__txLatencyCorrection->setID(false);
    m_PortMapping__txLatencyCorrection->setUnique(true);
    m_PortMapping__txLatencyCorrection->setDerived(false);
    m_PortMapping__txLatencyCorrection->setOrdered(true);
    m_PortMapping__disableRxFc->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_PortMapping__disableRxFc->setName("disableRxFc");
    m_PortMapping__disableRxFc->setDefaultValueLiteral("false");
    m_PortMapping__disableRxFc->setLowerBound(0);
    m_PortMapping__disableRxFc->setUpperBound(1);
    m_PortMapping__disableRxFc->setTransient(false);
    m_PortMapping__disableRxFc->setVolatile(false);
    m_PortMapping__disableRxFc->setChangeable(true);
    m_PortMapping__disableRxFc->setUnsettable(false);
    m_PortMapping__disableRxFc->setID(false);
    m_PortMapping__disableRxFc->setUnique(true);
    m_PortMapping__disableRxFc->setDerived(false);
    m_PortMapping__disableRxFc->setOrdered(true);
    m_PortMapping__disableTxFc->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_PortMapping__disableTxFc->setName("disableTxFc");
    m_PortMapping__disableTxFc->setDefaultValueLiteral("false");
    m_PortMapping__disableTxFc->setLowerBound(0);
    m_PortMapping__disableTxFc->setUpperBound(1);
    m_PortMapping__disableTxFc->setTransient(false);
    m_PortMapping__disableTxFc->setVolatile(false);
    m_PortMapping__disableTxFc->setChangeable(true);
    m_PortMapping__disableTxFc->setUnsettable(false);
    m_PortMapping__disableTxFc->setID(false);
    m_PortMapping__disableTxFc->setUnique(true);
    m_PortMapping__disableTxFc->setDerived(false);
    m_PortMapping__disableTxFc->setOrdered(true);
    m_PortMapping__refTargetPort->setEType(
            dynamic_cast< ::Device_Targets::Device_TargetsPackage* > (::Device_Targets::Device_TargetsPackage::_instance())->getTargetPort());
    m_PortMapping__refTargetPort->setName("refTargetPort");
    m_PortMapping__refTargetPort->setDefaultValueLiteral("");
    m_PortMapping__refTargetPort->setLowerBound(1);
    m_PortMapping__refTargetPort->setUpperBound(1);
    m_PortMapping__refTargetPort->setTransient(false);
    m_PortMapping__refTargetPort->setVolatile(false);
    m_PortMapping__refTargetPort->setChangeable(true);
    m_PortMapping__refTargetPort->setContainment(false);
    m_PortMapping__refTargetPort->setResolveProxies(true);
    m_PortMapping__refTargetPort->setUnique(true);
    m_PortMapping__refTargetPort->setDerived(false);
    m_PortMapping__refTargetPort->setOrdered(true);
    m_PortMapping__refPort->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPort());
    m_PortMapping__refPort->setName("refPort");
    m_PortMapping__refPort->setDefaultValueLiteral("");
    m_PortMapping__refPort->setLowerBound(1);
    m_PortMapping__refPort->setUpperBound(1);
    m_PortMapping__refPort->setTransient(false);
    m_PortMapping__refPort->setVolatile(false);
    m_PortMapping__refPort->setChangeable(true);
    m_PortMapping__refPort->setContainment(false);
    m_PortMapping__refPort->setResolveProxies(true);
    m_PortMapping__refPort->setUnique(true);
    m_PortMapping__refPort->setDerived(false);
    m_PortMapping__refPort->setOrdered(true);
    // CriticalTrafficBuffer
    m_CriticalTrafficBufferEClass->setName("CriticalTrafficBuffer");
    m_CriticalTrafficBufferEClass->setAbstract(true);
    m_CriticalTrafficBufferEClass->setInterface(false);
    // SharedBuffer
    m_SharedBufferEClass->setName("SharedBuffer");
    m_SharedBufferEClass->setAbstract(false);
    m_SharedBufferEClass->setInterface(false);
    m_SharedBuffer__refVirtualLink->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getVirtualLink());
    m_SharedBuffer__refVirtualLink->setName("refVirtualLink");
    m_SharedBuffer__refVirtualLink->setDefaultValueLiteral("");
    m_SharedBuffer__refVirtualLink->setLowerBound(1);
    m_SharedBuffer__refVirtualLink->setUpperBound(-1);
    m_SharedBuffer__refVirtualLink->setTransient(false);
    m_SharedBuffer__refVirtualLink->setVolatile(false);
    m_SharedBuffer__refVirtualLink->setChangeable(true);
    m_SharedBuffer__refVirtualLink->setContainment(false);
    m_SharedBuffer__refVirtualLink->setResolveProxies(true);
    m_SharedBuffer__refVirtualLink->setUnique(true);
    m_SharedBuffer__refVirtualLink->setDerived(false);
    m_SharedBuffer__refVirtualLink->setOrdered(true);
    // DedicatedBuffer
    m_DedicatedBufferEClass->setName("DedicatedBuffer");
    m_DedicatedBufferEClass->setAbstract(false);
    m_DedicatedBufferEClass->setInterface(false);
    m_DedicatedBuffer__refVirtualLink->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getVirtualLink());
    m_DedicatedBuffer__refVirtualLink->setName("refVirtualLink");
    m_DedicatedBuffer__refVirtualLink->setDefaultValueLiteral("");
    m_DedicatedBuffer__refVirtualLink->setLowerBound(1);
    m_DedicatedBuffer__refVirtualLink->setUpperBound(1);
    m_DedicatedBuffer__refVirtualLink->setTransient(false);
    m_DedicatedBuffer__refVirtualLink->setVolatile(false);
    m_DedicatedBuffer__refVirtualLink->setChangeable(true);
    m_DedicatedBuffer__refVirtualLink->setContainment(false);
    m_DedicatedBuffer__refVirtualLink->setResolveProxies(true);
    m_DedicatedBuffer__refVirtualLink->setUnique(true);
    m_DedicatedBuffer__refVirtualLink->setDerived(false);
    m_DedicatedBuffer__refVirtualLink->setOrdered(true);
    // Mappings
    m_MappingsEClass->setName("Mappings");
    m_MappingsEClass->setAbstract(false);
    m_MappingsEClass->setInterface(false);
    m_Mappings__deviceMappings->setEType(m_DeviceMappingsEClass);
    m_Mappings__deviceMappings->setName("deviceMappings");
    m_Mappings__deviceMappings->setDefaultValueLiteral("");
    m_Mappings__deviceMappings->setLowerBound(0);
    m_Mappings__deviceMappings->setUpperBound(1);
    m_Mappings__deviceMappings->setTransient(false);
    m_Mappings__deviceMappings->setVolatile(false);
    m_Mappings__deviceMappings->setChangeable(true);
    m_Mappings__deviceMappings->setContainment(true);
    m_Mappings__deviceMappings->setResolveProxies(true);
    m_Mappings__deviceMappings->setUnique(true);
    m_Mappings__deviceMappings->setDerived(false);
    m_Mappings__deviceMappings->setOrdered(true);
    m_Mappings__containingVirtualLinkMapping->setEType(
            dynamic_cast< ::Virtuallink_Map::Virtuallink_MapPackage* > (::Virtuallink_Map::Virtuallink_MapPackage::_instance())->getVirtualLinkMapping());
    m_Mappings__containingVirtualLinkMapping->setName(
            "containingVirtualLinkMapping");
    m_Mappings__containingVirtualLinkMapping->setDefaultValueLiteral("");
    m_Mappings__containingVirtualLinkMapping->setLowerBound(0);
    m_Mappings__containingVirtualLinkMapping->setUpperBound(1);
    m_Mappings__containingVirtualLinkMapping->setTransient(false);
    m_Mappings__containingVirtualLinkMapping->setVolatile(false);
    m_Mappings__containingVirtualLinkMapping->setChangeable(true);
    m_Mappings__containingVirtualLinkMapping->setContainment(true);
    m_Mappings__containingVirtualLinkMapping->setResolveProxies(true);
    m_Mappings__containingVirtualLinkMapping->setUnique(true);
    m_Mappings__containingVirtualLinkMapping->setDerived(false);
    m_Mappings__containingVirtualLinkMapping->setOrdered(true);
    m_Mappings__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_Mappings__metaInformation->setName("metaInformation");
    m_Mappings__metaInformation->setDefaultValueLiteral("");
    m_Mappings__metaInformation->setLowerBound(0);
    m_Mappings__metaInformation->setUpperBound(1);
    m_Mappings__metaInformation->setTransient(false);
    m_Mappings__metaInformation->setVolatile(false);
    m_Mappings__metaInformation->setChangeable(true);
    m_Mappings__metaInformation->setContainment(true);
    m_Mappings__metaInformation->setResolveProxies(true);
    m_Mappings__metaInformation->setUnique(true);
    m_Mappings__metaInformation->setDerived(false);
    m_Mappings__metaInformation->setOrdered(true);
    m_Mappings__refVirtualLinkMappings->setEType(
            dynamic_cast< ::Virtuallink_Map::Virtuallink_MapPackage* > (::Virtuallink_Map::Virtuallink_MapPackage::_instance())->getVirtualLinkMapping());
    m_Mappings__refVirtualLinkMappings->setName("refVirtualLinkMappings");
    m_Mappings__refVirtualLinkMappings->setDefaultValueLiteral("");
    m_Mappings__refVirtualLinkMappings->setLowerBound(0);
    m_Mappings__refVirtualLinkMappings->setUpperBound(1);
    m_Mappings__refVirtualLinkMappings->setTransient(false);
    m_Mappings__refVirtualLinkMappings->setVolatile(false);
    m_Mappings__refVirtualLinkMappings->setChangeable(true);
    m_Mappings__refVirtualLinkMappings->setContainment(false);
    m_Mappings__refVirtualLinkMappings->setResolveProxies(true);
    m_Mappings__refVirtualLinkMappings->setUnique(true);
    m_Mappings__refVirtualLinkMappings->setDerived(false);
    m_Mappings__refVirtualLinkMappings->setOrdered(true);
    // PortMappings
    m_PortMappingsEClass->setName("PortMappings");
    m_PortMappingsEClass->setAbstract(true);
    m_PortMappingsEClass->setInterface(false);
    m_PortMappings__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_PortMappings__metaInformation->setName("metaInformation");
    m_PortMappings__metaInformation->setDefaultValueLiteral("");
    m_PortMappings__metaInformation->setLowerBound(0);
    m_PortMappings__metaInformation->setUpperBound(1);
    m_PortMappings__metaInformation->setTransient(false);
    m_PortMappings__metaInformation->setVolatile(false);
    m_PortMappings__metaInformation->setChangeable(true);
    m_PortMappings__metaInformation->setContainment(true);
    m_PortMappings__metaInformation->setResolveProxies(true);
    m_PortMappings__metaInformation->setUnique(true);
    m_PortMappings__metaInformation->setDerived(false);
    m_PortMappings__metaInformation->setOrdered(true);
    // DeviceMappings
    m_DeviceMappingsEClass->setName("DeviceMappings");
    m_DeviceMappingsEClass->setAbstract(false);
    m_DeviceMappingsEClass->setInterface(false);
    m_DeviceMappings__deviceMapping->setEType(m_DeviceMappingEClass);
    m_DeviceMappings__deviceMapping->setName("deviceMapping");
    m_DeviceMappings__deviceMapping->setDefaultValueLiteral("");
    m_DeviceMappings__deviceMapping->setLowerBound(0);
    m_DeviceMappings__deviceMapping->setUpperBound(-1);
    m_DeviceMappings__deviceMapping->setTransient(false);
    m_DeviceMappings__deviceMapping->setVolatile(false);
    m_DeviceMappings__deviceMapping->setChangeable(true);
    m_DeviceMappings__deviceMapping->setContainment(true);
    m_DeviceMappings__deviceMapping->setResolveProxies(true);
    m_DeviceMappings__deviceMapping->setUnique(true);
    m_DeviceMappings__deviceMapping->setDerived(false);
    m_DeviceMappings__deviceMapping->setOrdered(true);
    m_DeviceMappings__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_DeviceMappings__metaInformation->setName("metaInformation");
    m_DeviceMappings__metaInformation->setDefaultValueLiteral("");
    m_DeviceMappings__metaInformation->setLowerBound(0);
    m_DeviceMappings__metaInformation->setUpperBound(1);
    m_DeviceMappings__metaInformation->setTransient(false);
    m_DeviceMappings__metaInformation->setVolatile(false);
    m_DeviceMappings__metaInformation->setChangeable(true);
    m_DeviceMappings__metaInformation->setContainment(true);
    m_DeviceMappings__metaInformation->setResolveProxies(true);
    m_DeviceMappings__metaInformation->setUnique(true);
    m_DeviceMappings__metaInformation->setDerived(false);
    m_DeviceMappings__metaInformation->setOrdered(true);
    // OutputBuffers
    m_OutputBuffersEClass->setName("OutputBuffers");
    m_OutputBuffersEClass->setAbstract(false);
    m_OutputBuffersEClass->setInterface(false);
    m_OutputBuffers__dedicatedBuffer->setEType(m_DedicatedBufferEClass);
    m_OutputBuffers__dedicatedBuffer->setName("dedicatedBuffer");
    m_OutputBuffers__dedicatedBuffer->setDefaultValueLiteral("");
    m_OutputBuffers__dedicatedBuffer->setLowerBound(0);
    m_OutputBuffers__dedicatedBuffer->setUpperBound(-1);
    m_OutputBuffers__dedicatedBuffer->setTransient(false);
    m_OutputBuffers__dedicatedBuffer->setVolatile(false);
    m_OutputBuffers__dedicatedBuffer->setChangeable(true);
    m_OutputBuffers__dedicatedBuffer->setContainment(true);
    m_OutputBuffers__dedicatedBuffer->setResolveProxies(true);
    m_OutputBuffers__dedicatedBuffer->setUnique(true);
    m_OutputBuffers__dedicatedBuffer->setDerived(false);
    m_OutputBuffers__dedicatedBuffer->setOrdered(true);
    m_OutputBuffers__sharedBuffer->setEType(m_SharedBufferEClass);
    m_OutputBuffers__sharedBuffer->setName("sharedBuffer");
    m_OutputBuffers__sharedBuffer->setDefaultValueLiteral("");
    m_OutputBuffers__sharedBuffer->setLowerBound(0);
    m_OutputBuffers__sharedBuffer->setUpperBound(-1);
    m_OutputBuffers__sharedBuffer->setTransient(false);
    m_OutputBuffers__sharedBuffer->setVolatile(false);
    m_OutputBuffers__sharedBuffer->setChangeable(true);
    m_OutputBuffers__sharedBuffer->setContainment(true);
    m_OutputBuffers__sharedBuffer->setResolveProxies(true);
    m_OutputBuffers__sharedBuffer->setUnique(true);
    m_OutputBuffers__sharedBuffer->setDerived(false);
    m_OutputBuffers__sharedBuffer->setOrdered(true);
    m_OutputBuffers__cotsBuffer->setEType(m_COTSBufferEClass);
    m_OutputBuffers__cotsBuffer->setName("cotsBuffer");
    m_OutputBuffers__cotsBuffer->setDefaultValueLiteral("");
    m_OutputBuffers__cotsBuffer->setLowerBound(0);
    m_OutputBuffers__cotsBuffer->setUpperBound(-1);
    m_OutputBuffers__cotsBuffer->setTransient(false);
    m_OutputBuffers__cotsBuffer->setVolatile(false);
    m_OutputBuffers__cotsBuffer->setChangeable(true);
    m_OutputBuffers__cotsBuffer->setContainment(true);
    m_OutputBuffers__cotsBuffer->setResolveProxies(true);
    m_OutputBuffers__cotsBuffer->setUnique(true);
    m_OutputBuffers__cotsBuffer->setDerived(false);
    m_OutputBuffers__cotsBuffer->setOrdered(true);
    // InputBuffers
    m_InputBuffersEClass->setName("InputBuffers");
    m_InputBuffersEClass->setAbstract(false);
    m_InputBuffersEClass->setInterface(false);
    m_InputBuffers__sharedBuffer->setEType(m_SharedBufferEClass);
    m_InputBuffers__sharedBuffer->setName("sharedBuffer");
    m_InputBuffers__sharedBuffer->setDefaultValueLiteral("");
    m_InputBuffers__sharedBuffer->setLowerBound(0);
    m_InputBuffers__sharedBuffer->setUpperBound(-1);
    m_InputBuffers__sharedBuffer->setTransient(false);
    m_InputBuffers__sharedBuffer->setVolatile(false);
    m_InputBuffers__sharedBuffer->setChangeable(true);
    m_InputBuffers__sharedBuffer->setContainment(true);
    m_InputBuffers__sharedBuffer->setResolveProxies(true);
    m_InputBuffers__sharedBuffer->setUnique(true);
    m_InputBuffers__sharedBuffer->setDerived(false);
    m_InputBuffers__sharedBuffer->setOrdered(true);
    m_InputBuffers__dedicatedBuffer->setEType(m_DedicatedBufferEClass);
    m_InputBuffers__dedicatedBuffer->setName("dedicatedBuffer");
    m_InputBuffers__dedicatedBuffer->setDefaultValueLiteral("");
    m_InputBuffers__dedicatedBuffer->setLowerBound(0);
    m_InputBuffers__dedicatedBuffer->setUpperBound(-1);
    m_InputBuffers__dedicatedBuffer->setTransient(false);
    m_InputBuffers__dedicatedBuffer->setVolatile(false);
    m_InputBuffers__dedicatedBuffer->setChangeable(true);
    m_InputBuffers__dedicatedBuffer->setContainment(true);
    m_InputBuffers__dedicatedBuffer->setResolveProxies(true);
    m_InputBuffers__dedicatedBuffer->setUnique(true);
    m_InputBuffers__dedicatedBuffer->setDerived(false);
    m_InputBuffers__dedicatedBuffer->setOrdered(true);
    m_InputBuffers__cotsBuffer->setEType(m_COTSBufferEClass);
    m_InputBuffers__cotsBuffer->setName("cotsBuffer");
    m_InputBuffers__cotsBuffer->setDefaultValueLiteral("");
    m_InputBuffers__cotsBuffer->setLowerBound(0);
    m_InputBuffers__cotsBuffer->setUpperBound(-1);
    m_InputBuffers__cotsBuffer->setTransient(false);
    m_InputBuffers__cotsBuffer->setVolatile(false);
    m_InputBuffers__cotsBuffer->setChangeable(true);
    m_InputBuffers__cotsBuffer->setContainment(true);
    m_InputBuffers__cotsBuffer->setResolveProxies(true);
    m_InputBuffers__cotsBuffer->setUnique(true);
    m_InputBuffers__cotsBuffer->setDerived(false);
    m_InputBuffers__cotsBuffer->setOrdered(true);
    // BufferMapping
    m_BufferMappingEClass->setName("BufferMapping");
    m_BufferMappingEClass->setAbstract(false);
    m_BufferMappingEClass->setInterface(false);
    m_BufferMapping__outputBuffers->setEType(m_OutputBuffersEClass);
    m_BufferMapping__outputBuffers->setName("outputBuffers");
    m_BufferMapping__outputBuffers->setDefaultValueLiteral("");
    m_BufferMapping__outputBuffers->setLowerBound(0);
    m_BufferMapping__outputBuffers->setUpperBound(1);
    m_BufferMapping__outputBuffers->setTransient(false);
    m_BufferMapping__outputBuffers->setVolatile(false);
    m_BufferMapping__outputBuffers->setChangeable(true);
    m_BufferMapping__outputBuffers->setContainment(true);
    m_BufferMapping__outputBuffers->setResolveProxies(true);
    m_BufferMapping__outputBuffers->setUnique(true);
    m_BufferMapping__outputBuffers->setDerived(false);
    m_BufferMapping__outputBuffers->setOrdered(true);
    m_BufferMapping__inputBuffers->setEType(m_InputBuffersEClass);
    m_BufferMapping__inputBuffers->setName("inputBuffers");
    m_BufferMapping__inputBuffers->setDefaultValueLiteral("");
    m_BufferMapping__inputBuffers->setLowerBound(0);
    m_BufferMapping__inputBuffers->setUpperBound(1);
    m_BufferMapping__inputBuffers->setTransient(false);
    m_BufferMapping__inputBuffers->setVolatile(false);
    m_BufferMapping__inputBuffers->setChangeable(true);
    m_BufferMapping__inputBuffers->setContainment(true);
    m_BufferMapping__inputBuffers->setResolveProxies(true);
    m_BufferMapping__inputBuffers->setUnique(true);
    m_BufferMapping__inputBuffers->setDerived(false);
    m_BufferMapping__inputBuffers->setOrdered(true);
    m_BufferMapping__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_BufferMapping__metaInformation->setName("metaInformation");
    m_BufferMapping__metaInformation->setDefaultValueLiteral("");
    m_BufferMapping__metaInformation->setLowerBound(0);
    m_BufferMapping__metaInformation->setUpperBound(1);
    m_BufferMapping__metaInformation->setTransient(false);
    m_BufferMapping__metaInformation->setVolatile(false);
    m_BufferMapping__metaInformation->setChangeable(true);
    m_BufferMapping__metaInformation->setContainment(true);
    m_BufferMapping__metaInformation->setResolveProxies(true);
    m_BufferMapping__metaInformation->setUnique(true);
    m_BufferMapping__metaInformation->setDerived(false);
    m_BufferMapping__metaInformation->setOrdered(true);
    // MemoryBuffer
    m_MemoryBufferEClass->setName("MemoryBuffer");
    m_MemoryBufferEClass->setAbstract(true);
    m_MemoryBufferEClass->setInterface(false);
    m_MemoryBuffer__baseAddress->setEType(m_MemoryAddressEDataType);
    m_MemoryBuffer__baseAddress->setName("baseAddress");
    m_MemoryBuffer__baseAddress->setDefaultValueLiteral("");
    m_MemoryBuffer__baseAddress->setLowerBound(1);
    m_MemoryBuffer__baseAddress->setUpperBound(1);
    m_MemoryBuffer__baseAddress->setTransient(false);
    m_MemoryBuffer__baseAddress->setVolatile(false);
    m_MemoryBuffer__baseAddress->setChangeable(true);
    m_MemoryBuffer__baseAddress->setUnsettable(false);
    m_MemoryBuffer__baseAddress->setID(false);
    m_MemoryBuffer__baseAddress->setUnique(true);
    m_MemoryBuffer__baseAddress->setDerived(false);
    m_MemoryBuffer__baseAddress->setOrdered(true);
    // Buffer
    m_BufferEClass->setName("Buffer");
    m_BufferEClass->setAbstract(true);
    m_BufferEClass->setInterface(false);
    m_Buffer__type->setEType(m_BufferTypeEnumEEnum);
    m_Buffer__type->setName("type");
    m_Buffer__type->setDefaultValueLiteral("STATE");
    m_Buffer__type->setLowerBound(0);
    m_Buffer__type->setUpperBound(1);
    m_Buffer__type->setTransient(false);
    m_Buffer__type->setVolatile(false);
    m_Buffer__type->setChangeable(true);
    m_Buffer__type->setUnsettable(false);
    m_Buffer__type->setID(false);
    m_Buffer__type->setUnique(true);
    m_Buffer__type->setDerived(false);
    m_Buffer__type->setOrdered(true);
    m_Buffer__depth->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Buffer__depth->setName("depth");
    m_Buffer__depth->setDefaultValueLiteral("");
    m_Buffer__depth->setLowerBound(1);
    m_Buffer__depth->setUpperBound(1);
    m_Buffer__depth->setTransient(false);
    m_Buffer__depth->setVolatile(false);
    m_Buffer__depth->setChangeable(true);
    m_Buffer__depth->setUnsettable(false);
    m_Buffer__depth->setID(false);
    m_Buffer__depth->setUnique(true);
    m_Buffer__depth->setDerived(false);
    m_Buffer__depth->setOrdered(true);
    m_Buffer__size->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Buffer__size->setName("size");
    m_Buffer__size->setDefaultValueLiteral("");
    m_Buffer__size->setLowerBound(0);
    m_Buffer__size->setUpperBound(1);
    m_Buffer__size->setTransient(false);
    m_Buffer__size->setVolatile(false);
    m_Buffer__size->setChangeable(true);
    m_Buffer__size->setUnsettable(false);
    m_Buffer__size->setID(false);
    m_Buffer__size->setUnique(true);
    m_Buffer__size->setDerived(false);
    m_Buffer__size->setOrdered(true);
    m_Buffer__flushOnScheduleReset->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_Buffer__flushOnScheduleReset->setName("flushOnScheduleReset");
    m_Buffer__flushOnScheduleReset->setDefaultValueLiteral("false");
    m_Buffer__flushOnScheduleReset->setLowerBound(0);
    m_Buffer__flushOnScheduleReset->setUpperBound(1);
    m_Buffer__flushOnScheduleReset->setTransient(false);
    m_Buffer__flushOnScheduleReset->setVolatile(false);
    m_Buffer__flushOnScheduleReset->setChangeable(true);
    m_Buffer__flushOnScheduleReset->setUnsettable(false);
    m_Buffer__flushOnScheduleReset->setID(false);
    m_Buffer__flushOnScheduleReset->setUnique(true);
    m_Buffer__flushOnScheduleReset->setDerived(false);
    m_Buffer__flushOnScheduleReset->setOrdered(true);
    // COTSBuffer
    m_COTSBufferEClass->setName("COTSBuffer");
    m_COTSBufferEClass->setAbstract(false);
    m_COTSBufferEClass->setInterface(false);
    m_COTSBuffer__refTargetPort->setEType(
            dynamic_cast< ::Device_Targets::Device_TargetsPackage* > (::Device_Targets::Device_TargetsPackage::_instance())->getTargetPort());
    m_COTSBuffer__refTargetPort->setName("refTargetPort");
    m_COTSBuffer__refTargetPort->setDefaultValueLiteral("");
    m_COTSBuffer__refTargetPort->setLowerBound(1);
    m_COTSBuffer__refTargetPort->setUpperBound(1);
    m_COTSBuffer__refTargetPort->setTransient(false);
    m_COTSBuffer__refTargetPort->setVolatile(false);
    m_COTSBuffer__refTargetPort->setChangeable(true);
    m_COTSBuffer__refTargetPort->setContainment(false);
    m_COTSBuffer__refTargetPort->setResolveProxies(true);
    m_COTSBuffer__refTargetPort->setUnique(true);
    m_COTSBuffer__refTargetPort->setDerived(false);
    m_COTSBuffer__refTargetPort->setOrdered(true);
    // HostBuffer
    m_HostBufferEClass->setName("HostBuffer");
    m_HostBufferEClass->setAbstract(true);
    m_HostBufferEClass->setInterface(false);
    // QueuedOutputBuffer
    m_QueuedOutputBufferEClass->setName("QueuedOutputBuffer");
    m_QueuedOutputBufferEClass->setAbstract(false);
    m_QueuedOutputBufferEClass->setInterface(false);
    m_QueuedOutputBuffer__refOutVirtualLink->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getVirtualLink());
    m_QueuedOutputBuffer__refOutVirtualLink->setName("refOutVirtualLink");
    m_QueuedOutputBuffer__refOutVirtualLink->setDefaultValueLiteral("");
    m_QueuedOutputBuffer__refOutVirtualLink->setLowerBound(1);
    m_QueuedOutputBuffer__refOutVirtualLink->setUpperBound(1);
    m_QueuedOutputBuffer__refOutVirtualLink->setTransient(false);
    m_QueuedOutputBuffer__refOutVirtualLink->setVolatile(false);
    m_QueuedOutputBuffer__refOutVirtualLink->setChangeable(true);
    m_QueuedOutputBuffer__refOutVirtualLink->setContainment(false);
    m_QueuedOutputBuffer__refOutVirtualLink->setResolveProxies(true);
    m_QueuedOutputBuffer__refOutVirtualLink->setUnique(true);
    m_QueuedOutputBuffer__refOutVirtualLink->setDerived(false);
    m_QueuedOutputBuffer__refOutVirtualLink->setOrdered(true);
    // SwPortMapping
    m_SwPortMappingEClass->setName("SwPortMapping");
    m_SwPortMappingEClass->setAbstract(false);
    m_SwPortMappingEClass->setInterface(false);
    m_SwPortMapping__addressLearningEnable->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_SwPortMapping__addressLearningEnable->setName("addressLearningEnable");
    m_SwPortMapping__addressLearningEnable->setDefaultValueLiteral("true");
    m_SwPortMapping__addressLearningEnable->setLowerBound(0);
    m_SwPortMapping__addressLearningEnable->setUpperBound(1);
    m_SwPortMapping__addressLearningEnable->setTransient(false);
    m_SwPortMapping__addressLearningEnable->setVolatile(false);
    m_SwPortMapping__addressLearningEnable->setChangeable(true);
    m_SwPortMapping__addressLearningEnable->setUnsettable(false);
    m_SwPortMapping__addressLearningEnable->setID(false);
    m_SwPortMapping__addressLearningEnable->setUnique(true);
    m_SwPortMapping__addressLearningEnable->setDerived(false);
    m_SwPortMapping__addressLearningEnable->setOrdered(true);
    m_SwPortMapping__broadcastForwardEnable->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_SwPortMapping__broadcastForwardEnable->setName("broadcastForwardEnable");
    m_SwPortMapping__broadcastForwardEnable->setDefaultValueLiteral("true");
    m_SwPortMapping__broadcastForwardEnable->setLowerBound(0);
    m_SwPortMapping__broadcastForwardEnable->setUpperBound(1);
    m_SwPortMapping__broadcastForwardEnable->setTransient(false);
    m_SwPortMapping__broadcastForwardEnable->setVolatile(false);
    m_SwPortMapping__broadcastForwardEnable->setChangeable(true);
    m_SwPortMapping__broadcastForwardEnable->setUnsettable(false);
    m_SwPortMapping__broadcastForwardEnable->setID(false);
    m_SwPortMapping__broadcastForwardEnable->setUnique(true);
    m_SwPortMapping__broadcastForwardEnable->setDerived(false);
    m_SwPortMapping__broadcastForwardEnable->setOrdered(true);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setEType(
            m_PerPortBagAccountEClass);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setName(
            "refPerPortBroadcastBagAccount");
    m_SwPortMapping__refPerPortBroadcastBagAccount->setDefaultValueLiteral("");
    m_SwPortMapping__refPerPortBroadcastBagAccount->setLowerBound(0);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setUpperBound(1);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setTransient(false);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setVolatile(false);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setChangeable(true);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setContainment(false);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setResolveProxies(true);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setUnique(true);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setDerived(false);
    m_SwPortMapping__refPerPortBroadcastBagAccount->setOrdered(true);
    m_SwPortMapping__refPerPortUniCastBagAccount->setEType(
            m_PerPortBagAccountEClass);
    m_SwPortMapping__refPerPortUniCastBagAccount->setName(
            "refPerPortUniCastBagAccount");
    m_SwPortMapping__refPerPortUniCastBagAccount->setDefaultValueLiteral("");
    m_SwPortMapping__refPerPortUniCastBagAccount->setLowerBound(0);
    m_SwPortMapping__refPerPortUniCastBagAccount->setUpperBound(1);
    m_SwPortMapping__refPerPortUniCastBagAccount->setTransient(false);
    m_SwPortMapping__refPerPortUniCastBagAccount->setVolatile(false);
    m_SwPortMapping__refPerPortUniCastBagAccount->setChangeable(true);
    m_SwPortMapping__refPerPortUniCastBagAccount->setContainment(false);
    m_SwPortMapping__refPerPortUniCastBagAccount->setResolveProxies(true);
    m_SwPortMapping__refPerPortUniCastBagAccount->setUnique(true);
    m_SwPortMapping__refPerPortUniCastBagAccount->setDerived(false);
    m_SwPortMapping__refPerPortUniCastBagAccount->setOrdered(true);
    // EsPortMapping
    m_EsPortMappingEClass->setName("EsPortMapping");
    m_EsPortMappingEClass->setAbstract(false);
    m_EsPortMappingEClass->setInterface(false);
    // PerPortBagAccounts
    m_PerPortBagAccountsEClass->setName("PerPortBagAccounts");
    m_PerPortBagAccountsEClass->setAbstract(false);
    m_PerPortBagAccountsEClass->setInterface(false);
    m_PerPortBagAccounts__perPortBagSetting->setEType(m_PerPortBagAccountEClass);
    m_PerPortBagAccounts__perPortBagSetting->setName("perPortBagSetting");
    m_PerPortBagAccounts__perPortBagSetting->setDefaultValueLiteral("");
    m_PerPortBagAccounts__perPortBagSetting->setLowerBound(0);
    m_PerPortBagAccounts__perPortBagSetting->setUpperBound(-1);
    m_PerPortBagAccounts__perPortBagSetting->setTransient(false);
    m_PerPortBagAccounts__perPortBagSetting->setVolatile(false);
    m_PerPortBagAccounts__perPortBagSetting->setChangeable(true);
    m_PerPortBagAccounts__perPortBagSetting->setContainment(true);
    m_PerPortBagAccounts__perPortBagSetting->setResolveProxies(true);
    m_PerPortBagAccounts__perPortBagSetting->setUnique(true);
    m_PerPortBagAccounts__perPortBagSetting->setDerived(false);
    m_PerPortBagAccounts__perPortBagSetting->setOrdered(true);
    // PerPortBagAccount
    m_PerPortBagAccountEClass->setName("PerPortBagAccount");
    m_PerPortBagAccountEClass->setAbstract(false);
    m_PerPortBagAccountEClass->setInterface(false);
    // SwPortMappings
    m_SwPortMappingsEClass->setName("SwPortMappings");
    m_SwPortMappingsEClass->setAbstract(false);
    m_SwPortMappingsEClass->setInterface(false);
    m_SwPortMappings__targetPortMapping->setEType(m_SwPortMappingEClass);
    m_SwPortMappings__targetPortMapping->setName("targetPortMapping");
    m_SwPortMappings__targetPortMapping->setDefaultValueLiteral("");
    m_SwPortMappings__targetPortMapping->setLowerBound(0);
    m_SwPortMappings__targetPortMapping->setUpperBound(-1);
    m_SwPortMappings__targetPortMapping->setTransient(false);
    m_SwPortMappings__targetPortMapping->setVolatile(false);
    m_SwPortMappings__targetPortMapping->setChangeable(true);
    m_SwPortMappings__targetPortMapping->setContainment(true);
    m_SwPortMappings__targetPortMapping->setResolveProxies(true);
    m_SwPortMappings__targetPortMapping->setUnique(true);
    m_SwPortMappings__targetPortMapping->setDerived(false);
    m_SwPortMappings__targetPortMapping->setOrdered(true);
    // EsPortMappings
    m_EsPortMappingsEClass->setName("EsPortMappings");
    m_EsPortMappingsEClass->setAbstract(false);
    m_EsPortMappingsEClass->setInterface(false);
    m_EsPortMappings__targetPortMapping->setEType(m_EsPortMappingEClass);
    m_EsPortMappings__targetPortMapping->setName("targetPortMapping");
    m_EsPortMappings__targetPortMapping->setDefaultValueLiteral("");
    m_EsPortMappings__targetPortMapping->setLowerBound(0);
    m_EsPortMappings__targetPortMapping->setUpperBound(-1);
    m_EsPortMappings__targetPortMapping->setTransient(false);
    m_EsPortMappings__targetPortMapping->setVolatile(false);
    m_EsPortMappings__targetPortMapping->setChangeable(true);
    m_EsPortMappings__targetPortMapping->setContainment(true);
    m_EsPortMappings__targetPortMapping->setResolveProxies(true);
    m_EsPortMappings__targetPortMapping->setUnique(true);
    m_EsPortMappings__targetPortMapping->setDerived(false);
    m_EsPortMappings__targetPortMapping->setOrdered(true);

    // TODO: Initialize data types

    // FrequencyType
    m_FrequencyTypeEDataType->setName("FrequencyType");
    m_FrequencyTypeEDataType->setSerializable(true);

    // MemoryAddress
    m_MemoryAddressEDataType->setName("MemoryAddress");
    m_MemoryAddressEDataType->setSerializable(true);

    // BufferTypeEnum
    m_BufferTypeEnumEEnum->setName("BufferTypeEnum");
    m_BufferTypeEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // STATE
        _el->setName("STATE");
        _el->setValue(0);
        _el->setLiteral("STATE");
        _el->setEEnum(m_BufferTypeEnumEEnum);
        m_BufferTypeEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // FIFO
        _el->setName("FIFO");
        _el->setValue(1);
        _el->setLiteral("FIFO");
        _el->setEEnum(m_BufferTypeEnumEEnum);
        m_BufferTypeEnumEEnum->getELiterals().push_back(_el);
    }

    _initialize();
}

::ecore::EClass_ptr Device_Target_MappingPackage::getDeviceMapping()
{
    return m_DeviceMappingEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getInputBuffer()
{
    return m_InputBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getTrigger()
{
    return m_TriggerEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getPortMapping()
{
    return m_PortMappingEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getCriticalTrafficBuffer()
{
    return m_CriticalTrafficBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getSharedBuffer()
{
    return m_SharedBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getDedicatedBuffer()
{
    return m_DedicatedBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getMappings()
{
    return m_MappingsEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getPortMappings()
{
    return m_PortMappingsEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getDeviceMappings()
{
    return m_DeviceMappingsEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getOutputBuffers()
{
    return m_OutputBuffersEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getInputBuffers()
{
    return m_InputBuffersEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getBufferMapping()
{
    return m_BufferMappingEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getMemoryBuffer()
{
    return m_MemoryBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getBuffer()
{
    return m_BufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getCOTSBuffer()
{
    return m_COTSBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getHostBuffer()
{
    return m_HostBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getQueuedOutputBuffer()
{
    return m_QueuedOutputBufferEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getSwPortMapping()
{
    return m_SwPortMappingEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getEsPortMapping()
{
    return m_EsPortMappingEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getPerPortBagAccounts()
{
    return m_PerPortBagAccountsEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getPerPortBagAccount()
{
    return m_PerPortBagAccountEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getSwPortMappings()
{
    return m_SwPortMappingsEClass;
}
::ecore::EClass_ptr Device_Target_MappingPackage::getEsPortMappings()
{
    return m_EsPortMappingsEClass;
}
::ecore::EEnum_ptr Device_Target_MappingPackage::getBufferTypeEnum()
{
    return m_BufferTypeEnumEEnum;
}
::ecore::EDataType_ptr Device_Target_MappingPackage::getFrequencyType()
{
    return m_FrequencyTypeEDataType;
}
::ecore::EDataType_ptr Device_Target_MappingPackage::getMemoryAddress()
{
    return m_MemoryAddressEDataType;
}

::ecore::EReference_ptr Device_Target_MappingPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__refTargetDevice()
{
    return m_DeviceMapping__refTargetDevice;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__perPortBagAccounts()
{
    return m_DeviceMapping__perPortBagAccounts;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__portMappings()
{
    return m_DeviceMapping__portMappings;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getDeviceMapping__agingTime()
{
    return m_DeviceMapping__agingTime;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__antiMasquerading()
{
    return m_DeviceMapping__antiMasquerading;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__diagnostic()
{
    return m_DeviceMapping__diagnostic;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__trigger()
{
    return m_DeviceMapping__trigger;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__bufferMapping()
{
    return m_DeviceMapping__bufferMapping;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__managementInterface()
{
    return m_DeviceMapping__managementInterface;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMapping__metaInformation()
{
    return m_DeviceMapping__metaInformation;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getBuffer__type()
{
    return m_Buffer__type;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getBuffer__depth()
{
    return m_Buffer__depth;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getBuffer__size()
{
    return m_Buffer__size;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getBuffer__flushOnScheduleReset()
{
    return m_Buffer__flushOnScheduleReset;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getMemoryBuffer__baseAddress()
{
    return m_MemoryBuffer__baseAddress;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getTrigger__device()
{
    return m_Trigger__device;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getTrigger__target()
{
    return m_Trigger__target;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getTrigger__refTriggerSchedule()
{
    return m_Trigger__refTriggerSchedule;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getPortMapping__rxLatencyCorrection()
{
    return m_PortMapping__rxLatencyCorrection;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getPortMapping__txLatencyCorrection()
{
    return m_PortMapping__txLatencyCorrection;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getPortMapping__disableRxFc()
{
    return m_PortMapping__disableRxFc;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getPortMapping__disableTxFc()
{
    return m_PortMapping__disableTxFc;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getPortMapping__refTargetPort()
{
    return m_PortMapping__refTargetPort;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getPortMapping__refPort()
{
    return m_PortMapping__refPort;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getSharedBuffer__refVirtualLink()
{
    return m_SharedBuffer__refVirtualLink;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDedicatedBuffer__refVirtualLink()
{
    return m_DedicatedBuffer__refVirtualLink;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getMappings__deviceMappings()
{
    return m_Mappings__deviceMappings;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getMappings__containingVirtualLinkMapping()
{
    return m_Mappings__containingVirtualLinkMapping;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getMappings__metaInformation()
{
    return m_Mappings__metaInformation;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getMappings__refVirtualLinkMappings()
{
    return m_Mappings__refVirtualLinkMappings;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getPortMappings__metaInformation()
{
    return m_PortMappings__metaInformation;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMappings__deviceMapping()
{
    return m_DeviceMappings__deviceMapping;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getDeviceMappings__metaInformation()
{
    return m_DeviceMappings__metaInformation;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getOutputBuffers__dedicatedBuffer()
{
    return m_OutputBuffers__dedicatedBuffer;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getOutputBuffers__sharedBuffer()
{
    return m_OutputBuffers__sharedBuffer;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getOutputBuffers__cotsBuffer()
{
    return m_OutputBuffers__cotsBuffer;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getInputBuffers__sharedBuffer()
{
    return m_InputBuffers__sharedBuffer;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getInputBuffers__dedicatedBuffer()
{
    return m_InputBuffers__dedicatedBuffer;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getInputBuffers__cotsBuffer()
{
    return m_InputBuffers__cotsBuffer;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getBufferMapping__outputBuffers()
{
    return m_BufferMapping__outputBuffers;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getBufferMapping__inputBuffers()
{
    return m_BufferMapping__inputBuffers;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getBufferMapping__metaInformation()
{
    return m_BufferMapping__metaInformation;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getCOTSBuffer__refTargetPort()
{
    return m_COTSBuffer__refTargetPort;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getQueuedOutputBuffer__refOutVirtualLink()
{
    return m_QueuedOutputBuffer__refOutVirtualLink;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getSwPortMapping__addressLearningEnable()
{
    return m_SwPortMapping__addressLearningEnable;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getSwPortMapping__broadcastForwardEnable()
{
    return m_SwPortMapping__broadcastForwardEnable;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getSwPortMapping__refPerPortBroadcastBagAccount()
{
    return m_SwPortMapping__refPerPortBroadcastBagAccount;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getSwPortMapping__refPerPortUniCastBagAccount()
{
    return m_SwPortMapping__refPerPortUniCastBagAccount;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getPerPortBagAccounts__perPortBagSetting()
{
    return m_PerPortBagAccounts__perPortBagSetting;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getBagAccount__bag()
{
    return m_BagAccount__bag;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getBagAccount__jitter()
{
    return m_BagAccount__jitter;
}
::ecore::EAttribute_ptr Device_Target_MappingPackage::getBagAccount__constrainType()
{
    return m_BagAccount__constrainType;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getSwPortMappings__targetPortMapping()
{
    return m_SwPortMappings__targetPortMapping;
}
::ecore::EReference_ptr Device_Target_MappingPackage::getEsPortMappings__targetPortMapping()
{
    return m_EsPortMappings__targetPortMapping;
}

