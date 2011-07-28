// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/Network_ConfigurationPackageImpl.cpp
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

#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <Network_Configuration/Network_ConfigurationFactory.hpp>
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
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <System_Specification/System_SpecificationPackage.hpp>
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <Protocol_Definition/Protocol_DefinitionPackage.hpp>
#include <Virtuallink_Map/Virtuallink_MapPackage.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/DeviceSpecification.hpp>
#include <System_Specification/Device.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <System_Specification/SystemSpecification.hpp>
#include <Device_Target_Mapping/Mappings.hpp>
#include <Protocol_Definition/Protocol.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>
#include <System_Specification/PCFVirtualLink.hpp>
#include <System_Specification/Period.hpp>

using namespace ::Network_Configuration;

Network_ConfigurationPackage::Network_ConfigurationPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = Network_ConfigurationFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // DeviceReferringElement
    m_DeviceReferringElementEClass = new ::ecore::EClass();
    m_DeviceReferringElementEClass->setClassifierID(DEVICEREFERRINGELEMENT);
    m_DeviceReferringElementEClass->setEPackage(this);
    getEClassifiers().push_back(m_DeviceReferringElementEClass);
    m_DeviceReferringElement__refDeviceSpecification
            = new ::ecore::EReference();
    m_DeviceReferringElement__refDeviceSpecification->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::DEVICEREFERRINGELEMENT__REFDEVICESPECIFICATION);
    m_DeviceReferringElementEClass->getEStructuralFeatures().push_back(
            m_DeviceReferringElement__refDeviceSpecification);
    m_DeviceReferringElement__refSyncConfiguration = new ::ecore::EReference();
    m_DeviceReferringElement__refSyncConfiguration->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::DEVICEREFERRINGELEMENT__REFSYNCCONFIGURATION);
    m_DeviceReferringElementEClass->getEStructuralFeatures().push_back(
            m_DeviceReferringElement__refSyncConfiguration);
    m_DeviceReferringElement__refDevice = new ::ecore::EReference();
    m_DeviceReferringElement__refDevice->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::DEVICEREFERRINGELEMENT__REFDEVICE);
    m_DeviceReferringElementEClass->getEStructuralFeatures().push_back(
            m_DeviceReferringElement__refDevice);

    // NetworkConfig
    m_NetworkConfigEClass = new ::ecore::EClass();
    m_NetworkConfigEClass->setClassifierID(NETWORKCONFIG);
    m_NetworkConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_NetworkConfigEClass);
    m_NetworkConfig__metaInformation = new ::ecore::EReference();
    m_NetworkConfig__metaInformation->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__METAINFORMATION);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__metaInformation);
    m_NetworkConfig__units = new ::ecore::EReference();
    m_NetworkConfig__units->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__UNITS);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__units);
    m_NetworkConfig__synchronization = new ::ecore::EReference();
    m_NetworkConfig__synchronization->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__SYNCHRONIZATION);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__synchronization);
    m_NetworkConfig__deviceReferringElement = new ::ecore::EReference();
    m_NetworkConfig__deviceReferringElement->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__DEVICEREFERRINGELEMENT);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__deviceReferringElement);
    m_NetworkConfig__refSystemSpecification = new ::ecore::EReference();
    m_NetworkConfig__refSystemSpecification->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFSYSTEMSPECIFICATION);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__refSystemSpecification);
    m_NetworkConfig__refMappings = new ::ecore::EReference();
    m_NetworkConfig__refMappings->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFMAPPINGS);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__refMappings);
    m_NetworkConfig__refProtocol = new ::ecore::EReference();
    m_NetworkConfig__refProtocol->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFPROTOCOL);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__refProtocol);
    m_NetworkConfig__periods = new ::ecore::EReference();
    m_NetworkConfig__periods->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__PERIODS);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__periods);
    m_NetworkConfig__refVirtualLinkMapping = new ::ecore::EReference();
    m_NetworkConfig__refVirtualLinkMapping->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFVIRTUALLINKMAPPING);
    m_NetworkConfigEClass->getEStructuralFeatures().push_back(
            m_NetworkConfig__refVirtualLinkMapping);

    // Synchronization
    m_SynchronizationEClass = new ::ecore::EClass();
    m_SynchronizationEClass->setClassifierID(SYNCHRONIZATION);
    m_SynchronizationEClass->setEPackage(this);
    getEClassifiers().push_back(m_SynchronizationEClass);
    m_Synchronization__syncDomain = new ::ecore::EReference();
    m_Synchronization__syncDomain->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__SYNCDOMAIN);
    m_SynchronizationEClass->getEStructuralFeatures().push_back(
            m_Synchronization__syncDomain);
    m_Synchronization__integrityConfigurations = new ::ecore::EReference();
    m_Synchronization__integrityConfigurations->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__INTEGRITYCONFIGURATIONS);
    m_SynchronizationEClass->getEStructuralFeatures().push_back(
            m_Synchronization__integrityConfigurations);

    // SyncDomain
    m_SyncDomainEClass = new ::ecore::EClass();
    m_SyncDomainEClass->setClassifierID(SYNCDOMAIN);
    m_SyncDomainEClass->setEPackage(this);
    getEClassifiers().push_back(m_SyncDomainEClass);
    m_SyncDomain__syncDomainId = new ::ecore::EAttribute();
    m_SyncDomain__syncDomainId->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCDOMAINID);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__syncDomainId);
    m_SyncDomain__clusterCycleDuration = new ::ecore::EAttribute();
    m_SyncDomain__clusterCycleDuration->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__CLUSTERCYCLEDURATION);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__clusterCycleDuration);
    m_SyncDomain__integrationCycleDuration = new ::ecore::EAttribute();
    m_SyncDomain__integrationCycleDuration->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRATIONCYCLEDURATION);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__integrationCycleDuration);
    m_SyncDomain__maxPcfTransmissionDelay = new ::ecore::EAttribute();
    m_SyncDomain__maxPcfTransmissionDelay->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__MAXPCFTRANSMISSIONDELAY);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__maxPcfTransmissionDelay);
    m_SyncDomain__faultToleranceLevel = new ::ecore::EAttribute();
    m_SyncDomain__faultToleranceLevel->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__FAULTTOLERANCELEVEL);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__faultToleranceLevel);
    m_SyncDomain__integrityLevel = new ::ecore::EAttribute();
    m_SyncDomain__integrityLevel->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRITYLEVEL);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__integrityLevel);
    m_SyncDomain__avgMode = new ::ecore::EAttribute();
    m_SyncDomain__avgMode->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__AVGMODE);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__avgMode);
    m_SyncDomain__syncPriority = new ::ecore::EReference();
    m_SyncDomain__syncPriority->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCPRIORITY);
    m_SyncDomainEClass->getEStructuralFeatures().push_back(
            m_SyncDomain__syncPriority);

    // SyncPriority
    m_SyncPriorityEClass = new ::ecore::EClass();
    m_SyncPriorityEClass->setClassifierID(SYNCPRIORITY);
    m_SyncPriorityEClass->setEPackage(this);
    getEClassifiers().push_back(m_SyncPriorityEClass);
    m_SyncPriority__value = new ::ecore::EAttribute();
    m_SyncPriority__value->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__VALUE);
    m_SyncPriorityEClass->getEStructuralFeatures().push_back(
            m_SyncPriority__value);
    m_SyncPriority__syncClient = new ::ecore::EReference();
    m_SyncPriority__syncClient->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCCLIENT);
    m_SyncPriorityEClass->getEStructuralFeatures().push_back(
            m_SyncPriority__syncClient);
    m_SyncPriority__syncMaster = new ::ecore::EReference();
    m_SyncPriority__syncMaster->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCMASTER);
    m_SyncPriorityEClass->getEStructuralFeatures().push_back(
            m_SyncPriority__syncMaster);
    m_SyncPriority__compressionMaster = new ::ecore::EReference();
    m_SyncPriority__compressionMaster->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__COMPRESSIONMASTER);
    m_SyncPriorityEClass->getEStructuralFeatures().push_back(
            m_SyncPriority__compressionMaster);

    // SyncBase
    m_SyncBaseEClass = new ::ecore::EClass();
    m_SyncBaseEClass->setClassifierID(SYNCBASE);
    m_SyncBaseEClass->setEPackage(this);
    getEClassifiers().push_back(m_SyncBaseEClass);
    m_SyncBase__scheduledReceivePit = new ::ecore::EAttribute();
    m_SyncBase__scheduledReceivePit->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SCHEDULEDRECEIVEPIT);
    m_SyncBaseEClass->getEStructuralFeatures().push_back(
            m_SyncBase__scheduledReceivePit);
    m_SyncBase__acceptanceWindow = new ::ecore::EAttribute();
    m_SyncBase__acceptanceWindow->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__ACCEPTANCEWINDOW);
    m_SyncBaseEClass->getEStructuralFeatures().push_back(
            m_SyncBase__acceptanceWindow);
    m_SyncBase__listenTimeout = new ::ecore::EAttribute();
    m_SyncBase__listenTimeout->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__LISTENTIMEOUT);
    m_SyncBaseEClass->getEStructuralFeatures().push_back(
            m_SyncBase__listenTimeout);
    m_SyncBase__priorityFallbackCycles = new ::ecore::EAttribute();
    m_SyncBase__priorityFallbackCycles->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__PRIORITYFALLBACKCYCLES);
    m_SyncBaseEClass->getEStructuralFeatures().push_back(
            m_SyncBase__priorityFallbackCycles);
    m_SyncBase__syncToStableEnabled = new ::ecore::EAttribute();
    m_SyncBase__syncToStableEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SYNCTOSTABLEENABLED);
    m_SyncBaseEClass->getEStructuralFeatures().push_back(
            m_SyncBase__syncToStableEnabled);

    // SyncClient
    m_SyncClientEClass = new ::ecore::EClass();
    m_SyncClientEClass->setClassifierID(SYNCCLIENT);
    m_SyncClientEClass->setEPackage(this);
    getEClassifiers().push_back(m_SyncClientEClass);
    m_SyncClient__refIntegrityConfig = new ::ecore::EReference();
    m_SyncClient__refIntegrityConfig->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCCLIENT__REFINTEGRITYCONFIG);
    m_SyncClientEClass->getEStructuralFeatures().push_back(
            m_SyncClient__refIntegrityConfig);

    // ActiveSyncComponent
    m_ActiveSyncComponentEClass = new ::ecore::EClass();
    m_ActiveSyncComponentEClass->setClassifierID(ACTIVESYNCCOMPONENT);
    m_ActiveSyncComponentEClass->setEPackage(this);
    getEClassifiers().push_back(m_ActiveSyncComponentEClass);
    m_ActiveSyncComponent__sourceMacAddress = new ::ecore::EAttribute();
    m_ActiveSyncComponent__sourceMacAddress->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__SOURCEMACADDRESS);
    m_ActiveSyncComponentEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponent__sourceMacAddress);
    m_ActiveSyncComponent__refPcfVlidIntegration = new ::ecore::EReference();
    m_ActiveSyncComponent__refPcfVlidIntegration->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION);
    m_ActiveSyncComponentEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponent__refPcfVlidIntegration);

    // DistributedSyncMaster
    m_DistributedSyncMasterEClass = new ::ecore::EClass();
    m_DistributedSyncMasterEClass->setClassifierID(DISTRIBUTEDSYNCMASTER);
    m_DistributedSyncMasterEClass->setEPackage(this);
    getEClassifiers().push_back(m_DistributedSyncMasterEClass);

    // CompressionMaster
    m_CompressionMasterEClass = new ::ecore::EClass();
    m_CompressionMasterEClass->setClassifierID(COMPRESSIONMASTER);
    m_CompressionMasterEClass->setEPackage(this);
    getEClassifiers().push_back(m_CompressionMasterEClass);
    m_CompressionMaster__observationWindowSize = new ::ecore::EAttribute();
    m_CompressionMaster__observationWindowSize->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__OBSERVATIONWINDOWSIZE);
    m_CompressionMasterEClass->getEStructuralFeatures().push_back(
            m_CompressionMaster__observationWindowSize);
    m_CompressionMaster__caEnableTimeout = new ::ecore::EAttribute();
    m_CompressionMaster__caEnableTimeout->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CAENABLETIMEOUT);
    m_CompressionMasterEClass->getEStructuralFeatures().push_back(
            m_CompressionMaster__caEnableTimeout);
    m_CompressionMaster__wait4in0Timeout = new ::ecore::EAttribute();
    m_CompressionMaster__wait4in0Timeout->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__WAIT4IN0TIMEOUT);
    m_CompressionMasterEClass->getEStructuralFeatures().push_back(
            m_CompressionMaster__wait4in0Timeout);
    m_CompressionMaster__busGuardian = new ::ecore::EReference();
    m_CompressionMaster__busGuardian->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__BUSGUARDIAN);
    m_CompressionMasterEClass->getEStructuralFeatures().push_back(
            m_CompressionMaster__busGuardian);
    m_CompressionMaster__cliqueDetection = new ::ecore::EReference();
    m_CompressionMaster__cliqueDetection->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CLIQUEDETECTION);
    m_CompressionMasterEClass->getEStructuralFeatures().push_back(
            m_CompressionMaster__cliqueDetection);
    m_CompressionMaster__refIntegrityConfig = new ::ecore::EReference();
    m_CompressionMaster__refIntegrityConfig->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__REFINTEGRITYCONFIG);
    m_CompressionMasterEClass->getEStructuralFeatures().push_back(
            m_CompressionMaster__refIntegrityConfig);

    // CliqueDetection
    m_CliqueDetectionEClass = new ::ecore::EClass();
    m_CliqueDetectionEClass->setClassifierID(CLIQUEDETECTION);
    m_CliqueDetectionEClass->setEPackage(this);
    getEClassifiers().push_back(m_CliqueDetectionEClass);
    m_CliqueDetection__tentativeSyncRelayEnabled = new ::ecore::EAttribute();
    m_CliqueDetection__tentativeSyncRelayEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCRELAYENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__tentativeSyncRelayEnabled);
    m_CliqueDetection__syncRelayEnabled = new ::ecore::EAttribute();
    m_CliqueDetection__syncRelayEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCRELAYENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__syncRelayEnabled);
    m_CliqueDetection__stableRelayEnabled = new ::ecore::EAttribute();
    m_CliqueDetection__stableRelayEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLERELAYENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__stableRelayEnabled);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled
            = new ::ecore::EAttribute();
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPASYNCENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__tentativeSyncMembershipAsyncEnabled);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled
            = new ::ecore::EAttribute();
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPSYNCENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__tentativeSyncMembershipSyncEnabled);
    m_CliqueDetection__syncMembershipAsyncEnabled = new ::ecore::EAttribute();
    m_CliqueDetection__syncMembershipAsyncEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPASYNCENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__syncMembershipAsyncEnabled);
    m_CliqueDetection__syncMembershipSyncEnabled = new ::ecore::EAttribute();
    m_CliqueDetection__syncMembershipSyncEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPSYNCENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__syncMembershipSyncEnabled);
    m_CliqueDetection__stableMembershipAsyncEnabled = new ::ecore::EAttribute();
    m_CliqueDetection__stableMembershipAsyncEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPASYNCENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__stableMembershipAsyncEnabled);
    m_CliqueDetection__stableMembershipSyncEnabled = new ::ecore::EAttribute();
    m_CliqueDetection__stableMembershipSyncEnabled->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPSYNCENABLED);
    m_CliqueDetectionEClass->getEStructuralFeatures().push_back(
            m_CliqueDetection__stableMembershipSyncEnabled);

    // BusGuardian
    m_BusGuardianEClass = new ::ecore::EClass();
    m_BusGuardianEClass->setClassifierID(BUSGUARDIAN);
    m_BusGuardianEClass->setEPackage(this);
    getEClassifiers().push_back(m_BusGuardianEClass);

    // IntegrityConfigurations
    m_IntegrityConfigurationsEClass = new ::ecore::EClass();
    m_IntegrityConfigurationsEClass->setClassifierID(INTEGRITYCONFIGURATIONS);
    m_IntegrityConfigurationsEClass->setEPackage(this);
    getEClassifiers().push_back(m_IntegrityConfigurationsEClass);
    m_IntegrityConfigurations__name = new ::ecore::EAttribute();
    m_IntegrityConfigurations__name->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__NAME);
    m_IntegrityConfigurationsEClass->getEStructuralFeatures().push_back(
            m_IntegrityConfigurations__name);
    m_IntegrityConfigurations__syncClientIntegrityConfig
            = new ::ecore::EReference();
    m_IntegrityConfigurations__syncClientIntegrityConfig->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCCLIENTINTEGRITYCONFIG);
    m_IntegrityConfigurationsEClass->getEStructuralFeatures().push_back(
            m_IntegrityConfigurations__syncClientIntegrityConfig);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig
            = new ::ecore::EReference();
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__COMPRESSIONMASTERINTEGRITYCONFIG);
    m_IntegrityConfigurationsEClass->getEStructuralFeatures().push_back(
            m_IntegrityConfigurations__compressionMasterIntegrityConfig);
    m_IntegrityConfigurations__syncMasterIntegrityConfig
            = new ::ecore::EReference();
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCMASTERINTEGRITYCONFIG);
    m_IntegrityConfigurationsEClass->getEStructuralFeatures().push_back(
            m_IntegrityConfigurations__syncMasterIntegrityConfig);

    // IntegrityConfigBase
    m_IntegrityConfigBaseEClass = new ::ecore::EClass();
    m_IntegrityConfigBaseEClass->setClassifierID(INTEGRITYCONFIGBASE);
    m_IntegrityConfigBaseEClass->setEPackage(this);
    getEClassifiers().push_back(m_IntegrityConfigBaseEClass);
    m_IntegrityConfigBase__integrateToSyncThreshold = new ::ecore::EAttribute();
    m_IntegrityConfigBase__integrateToSyncThreshold->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD);
    m_IntegrityConfigBaseEClass->getEStructuralFeatures().push_back(
            m_IntegrityConfigBase__integrateToSyncThreshold);
    m_IntegrityConfigBase__numUnstableCycles = new ::ecore::EAttribute();
    m_IntegrityConfigBase__numUnstableCycles->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES);
    m_IntegrityConfigBaseEClass->getEStructuralFeatures().push_back(
            m_IntegrityConfigBase__numUnstableCycles);
    m_IntegrityConfigBase__numStableCycles = new ::ecore::EAttribute();
    m_IntegrityConfigBase__numStableCycles->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMSTABLECYCLES);
    m_IntegrityConfigBaseEClass->getEStructuralFeatures().push_back(
            m_IntegrityConfigBase__numStableCycles);

    // SyncClientIntegrityConfig
    m_SyncClientIntegrityConfigEClass = new ::ecore::EClass();
    m_SyncClientIntegrityConfigEClass->setClassifierID(
            SYNCCLIENTINTEGRITYCONFIG);
    m_SyncClientIntegrityConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_SyncClientIntegrityConfigEClass);

    // ActiveSyncComponentIntegrityConfig
    m_ActiveSyncComponentIntegrityConfigEClass = new ::ecore::EClass();
    m_ActiveSyncComponentIntegrityConfigEClass->setClassifierID(
            ACTIVESYNCCOMPONENTINTEGRITYCONFIG);
    m_ActiveSyncComponentIntegrityConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_ActiveSyncComponentIntegrityConfigEClass);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__WAITTHRESHOLDASYNC);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDASYNC);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDSYNC);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__syncThresholdSync);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDASYNC);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync
            = new ::ecore::EAttribute();
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDSYNC);
    m_ActiveSyncComponentIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_ActiveSyncComponentIntegrityConfig__stableThresholdSync);

    // CompressionMasterIntegrityConfig
    m_CompressionMasterIntegrityConfigEClass = new ::ecore::EClass();
    m_CompressionMasterIntegrityConfigEClass->setClassifierID(
            COMPRESSIONMASTERINTEGRITYCONFIG);
    m_CompressionMasterIntegrityConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_CompressionMasterIntegrityConfigEClass);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold
            = new ::ecore::EAttribute();
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTERINTEGRITYCONFIG__INTEGRATETOTENTATIVETHRESHOLD);
    m_CompressionMasterIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold);

    // SyncMasterIntegrityConfig
    m_SyncMasterIntegrityConfigEClass = new ::ecore::EClass();
    m_SyncMasterIntegrityConfigEClass->setClassifierID(
            SYNCMASTERINTEGRITYCONFIG);
    m_SyncMasterIntegrityConfigEClass->setEPackage(this);
    getEClassifiers().push_back(m_SyncMasterIntegrityConfigEClass);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold
            = new ::ecore::EAttribute();
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTERINTEGRITYCONFIG__INTEGRATETOWAITTHRESHOLD);
    m_SyncMasterIntegrityConfigEClass->getEStructuralFeatures().push_back(
            m_SyncMasterIntegrityConfig__integrateToWaitThreshold);

    // Periods
    m_PeriodsEClass = new ::ecore::EClass();
    m_PeriodsEClass->setClassifierID(PERIODS);
    m_PeriodsEClass->setEPackage(this);
    getEClassifiers().push_back(m_PeriodsEClass);
    m_Periods__period = new ::ecore::EReference();
    m_Periods__period->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::PERIODS__PERIOD);
    m_PeriodsEClass->getEStructuralFeatures().push_back(m_Periods__period);

    // SyncMaster
    m_SyncMasterEClass = new ::ecore::EClass();
    m_SyncMasterEClass->setClassifierID(SYNCMASTER);
    m_SyncMasterEClass->setEPackage(this);
    getEClassifiers().push_back(m_SyncMasterEClass);
    m_SyncMaster__membershipBit = new ::ecore::EAttribute();
    m_SyncMaster__membershipBit->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__MEMBERSHIPBIT);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__membershipBit);
    m_SyncMaster__initialIntegrationCycle = new ::ecore::EAttribute();
    m_SyncMaster__initialIntegrationCycle->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__INITIALINTEGRATIONCYCLE);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__initialIntegrationCycle);
    m_SyncMaster__caOffset = new ::ecore::EAttribute();
    m_SyncMaster__caOffset->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__CAOFFSET);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__caOffset);
    m_SyncMaster__coldstartTimeout = new ::ecore::EAttribute();
    m_SyncMaster__coldstartTimeout->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__COLDSTARTTIMEOUT);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__coldstartTimeout);
    m_SyncMaster__csOffset = new ::ecore::EAttribute();
    m_SyncMaster__csOffset->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__CSOFFSET);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__csOffset);
    m_SyncMaster__restartTimeoutAsync = new ::ecore::EAttribute();
    m_SyncMaster__restartTimeoutAsync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__RESTARTTIMEOUTASYNC);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__restartTimeoutAsync);
    m_SyncMaster__restartTimeoutSync = new ::ecore::EAttribute();
    m_SyncMaster__restartTimeoutSync->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__RESTARTTIMEOUTSYNC);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__restartTimeoutSync);
    m_SyncMaster__clksyncFilterMax = new ::ecore::EAttribute();
    m_SyncMaster__clksyncFilterMax->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__CLKSYNCFILTERMAX);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__clksyncFilterMax);
    m_SyncMaster__refIntegrityConfig = new ::ecore::EReference();
    m_SyncMaster__refIntegrityConfig->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__REFINTEGRITYCONFIG);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__refIntegrityConfig);
    m_SyncMaster__refPcfVlidColdstart = new ::ecore::EReference();
    m_SyncMaster__refPcfVlidColdstart->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__REFPCFVLIDCOLDSTART);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__refPcfVlidColdstart);
    m_SyncMaster__refPcfVlidColdstartAck = new ::ecore::EReference();
    m_SyncMaster__refPcfVlidColdstartAck->setFeatureID(
            ::Network_Configuration::Network_ConfigurationPackage::SYNCMASTER__REFPCFVLIDCOLDSTARTACK);
    m_SyncMasterEClass->getEStructuralFeatures().push_back(
            m_SyncMaster__refPcfVlidColdstartAck);

    // StandaloneSyncMaster
    m_StandaloneSyncMasterEClass = new ::ecore::EClass();
    m_StandaloneSyncMasterEClass->setClassifierID(STANDALONESYNCMASTER);
    m_StandaloneSyncMasterEClass->setEPackage(this);
    getEClassifiers().push_back(m_StandaloneSyncMasterEClass);

    // Create enums

    m_AvgModeEnumEEnum = new ::ecore::EEnum();
    m_AvgModeEnumEEnum->setClassifierID(AVGMODEENUM);
    m_AvgModeEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_AvgModeEnumEEnum);

    m_FaultToleranceEnumEEnum = new ::ecore::EEnum();
    m_FaultToleranceEnumEEnum->setClassifierID(FAULTTOLERANCEENUM);
    m_FaultToleranceEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_FaultToleranceEnumEEnum);

    m_IntegrityLevelEnumEEnum = new ::ecore::EEnum();
    m_IntegrityLevelEnumEEnum->setClassifierID(INTEGRITYLEVELENUM);
    m_IntegrityLevelEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_IntegrityLevelEnumEEnum);

    // Create data types


    // Initialize package
    setName("Network_Configuration");
    setNsPrefix("nc");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/Network_Config_V1");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_DeviceReferringElementEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_NetworkConfigEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_SynchronizationEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_SyncDomainEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_SyncPriorityEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_SyncBaseEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_SyncClientEClass->getESuperTypes().push_back(m_SyncBaseEClass);
    m_ActiveSyncComponentEClass->getESuperTypes().push_back(m_SyncBaseEClass);
    m_DistributedSyncMasterEClass->getESuperTypes().push_back(
            m_SyncMasterEClass);
    m_CompressionMasterEClass->getESuperTypes().push_back(
            m_ActiveSyncComponentEClass);
    m_CliqueDetectionEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_BusGuardianEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_IntegrityConfigurationsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_IntegrityConfigBaseEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_SyncClientIntegrityConfigEClass->getESuperTypes().push_back(
            m_IntegrityConfigBaseEClass);
    m_ActiveSyncComponentIntegrityConfigEClass->getESuperTypes().push_back(
            m_IntegrityConfigBaseEClass);
    m_CompressionMasterIntegrityConfigEClass->getESuperTypes().push_back(
            m_ActiveSyncComponentIntegrityConfigEClass);
    m_SyncMasterIntegrityConfigEClass->getESuperTypes().push_back(
            m_ActiveSyncComponentIntegrityConfigEClass);
    m_PeriodsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_SyncMasterEClass->getESuperTypes().push_back(m_ActiveSyncComponentEClass);
    m_StandaloneSyncMasterEClass->getESuperTypes().push_back(m_SyncMasterEClass);

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // DeviceReferringElement
    m_DeviceReferringElementEClass->setName("DeviceReferringElement");
    m_DeviceReferringElementEClass->setAbstract(false);
    m_DeviceReferringElementEClass->setInterface(false);
    m_DeviceReferringElement__refDeviceSpecification->setEType(
            dynamic_cast< ::Device_Specification::Device_SpecificationPackage* > (::Device_Specification::Device_SpecificationPackage::_instance())->getDeviceSpecification());
    m_DeviceReferringElement__refDeviceSpecification->setName(
            "refDeviceSpecification");
    m_DeviceReferringElement__refDeviceSpecification->setDefaultValueLiteral("");
    m_DeviceReferringElement__refDeviceSpecification->setLowerBound(0);
    m_DeviceReferringElement__refDeviceSpecification->setUpperBound(1);
    m_DeviceReferringElement__refDeviceSpecification->setTransient(false);
    m_DeviceReferringElement__refDeviceSpecification->setVolatile(false);
    m_DeviceReferringElement__refDeviceSpecification->setChangeable(true);
    m_DeviceReferringElement__refDeviceSpecification->setContainment(false);
    m_DeviceReferringElement__refDeviceSpecification->setResolveProxies(true);
    m_DeviceReferringElement__refDeviceSpecification->setUnique(true);
    m_DeviceReferringElement__refDeviceSpecification->setDerived(false);
    m_DeviceReferringElement__refDeviceSpecification->setOrdered(true);
    m_DeviceReferringElement__refSyncConfiguration->setEType(m_SyncBaseEClass);
    m_DeviceReferringElement__refSyncConfiguration->setName(
            "refSyncConfiguration");
    m_DeviceReferringElement__refSyncConfiguration->setDefaultValueLiteral("");
    m_DeviceReferringElement__refSyncConfiguration->setLowerBound(0);
    m_DeviceReferringElement__refSyncConfiguration->setUpperBound(1);
    m_DeviceReferringElement__refSyncConfiguration->setTransient(false);
    m_DeviceReferringElement__refSyncConfiguration->setVolatile(false);
    m_DeviceReferringElement__refSyncConfiguration->setChangeable(true);
    m_DeviceReferringElement__refSyncConfiguration->setContainment(false);
    m_DeviceReferringElement__refSyncConfiguration->setResolveProxies(true);
    m_DeviceReferringElement__refSyncConfiguration->setUnique(true);
    m_DeviceReferringElement__refSyncConfiguration->setDerived(false);
    m_DeviceReferringElement__refSyncConfiguration->setOrdered(true);
    m_DeviceReferringElement__refDevice->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getDevice());
    m_DeviceReferringElement__refDevice->setName("refDevice");
    m_DeviceReferringElement__refDevice->setDefaultValueLiteral("");
    m_DeviceReferringElement__refDevice->setLowerBound(0);
    m_DeviceReferringElement__refDevice->setUpperBound(1);
    m_DeviceReferringElement__refDevice->setTransient(false);
    m_DeviceReferringElement__refDevice->setVolatile(false);
    m_DeviceReferringElement__refDevice->setChangeable(true);
    m_DeviceReferringElement__refDevice->setContainment(false);
    m_DeviceReferringElement__refDevice->setResolveProxies(true);
    m_DeviceReferringElement__refDevice->setUnique(true);
    m_DeviceReferringElement__refDevice->setDerived(false);
    m_DeviceReferringElement__refDevice->setOrdered(true);
    // NetworkConfig
    m_NetworkConfigEClass->setName("NetworkConfig");
    m_NetworkConfigEClass->setAbstract(false);
    m_NetworkConfigEClass->setInterface(false);
    m_NetworkConfig__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_NetworkConfig__metaInformation->setName("metaInformation");
    m_NetworkConfig__metaInformation->setDefaultValueLiteral("");
    m_NetworkConfig__metaInformation->setLowerBound(0);
    m_NetworkConfig__metaInformation->setUpperBound(1);
    m_NetworkConfig__metaInformation->setTransient(false);
    m_NetworkConfig__metaInformation->setVolatile(false);
    m_NetworkConfig__metaInformation->setChangeable(true);
    m_NetworkConfig__metaInformation->setContainment(true);
    m_NetworkConfig__metaInformation->setResolveProxies(true);
    m_NetworkConfig__metaInformation->setUnique(true);
    m_NetworkConfig__metaInformation->setDerived(false);
    m_NetworkConfig__metaInformation->setOrdered(false);
    m_NetworkConfig__units->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getUnits());
    m_NetworkConfig__units->setName("units");
    m_NetworkConfig__units->setDefaultValueLiteral("");
    m_NetworkConfig__units->setLowerBound(0);
    m_NetworkConfig__units->setUpperBound(1);
    m_NetworkConfig__units->setTransient(false);
    m_NetworkConfig__units->setVolatile(false);
    m_NetworkConfig__units->setChangeable(true);
    m_NetworkConfig__units->setContainment(true);
    m_NetworkConfig__units->setResolveProxies(true);
    m_NetworkConfig__units->setUnique(true);
    m_NetworkConfig__units->setDerived(false);
    m_NetworkConfig__units->setOrdered(false);
    m_NetworkConfig__synchronization->setEType(m_SynchronizationEClass);
    m_NetworkConfig__synchronization->setName("synchronization");
    m_NetworkConfig__synchronization->setDefaultValueLiteral("");
    m_NetworkConfig__synchronization->setLowerBound(0);
    m_NetworkConfig__synchronization->setUpperBound(1);
    m_NetworkConfig__synchronization->setTransient(false);
    m_NetworkConfig__synchronization->setVolatile(false);
    m_NetworkConfig__synchronization->setChangeable(true);
    m_NetworkConfig__synchronization->setContainment(true);
    m_NetworkConfig__synchronization->setResolveProxies(true);
    m_NetworkConfig__synchronization->setUnique(true);
    m_NetworkConfig__synchronization->setDerived(false);
    m_NetworkConfig__synchronization->setOrdered(false);
    m_NetworkConfig__deviceReferringElement->setEType(
            m_DeviceReferringElementEClass);
    m_NetworkConfig__deviceReferringElement->setName("deviceReferringElement");
    m_NetworkConfig__deviceReferringElement->setDefaultValueLiteral("");
    m_NetworkConfig__deviceReferringElement->setLowerBound(0);
    m_NetworkConfig__deviceReferringElement->setUpperBound(-1);
    m_NetworkConfig__deviceReferringElement->setTransient(false);
    m_NetworkConfig__deviceReferringElement->setVolatile(false);
    m_NetworkConfig__deviceReferringElement->setChangeable(true);
    m_NetworkConfig__deviceReferringElement->setContainment(true);
    m_NetworkConfig__deviceReferringElement->setResolveProxies(true);
    m_NetworkConfig__deviceReferringElement->setUnique(true);
    m_NetworkConfig__deviceReferringElement->setDerived(false);
    m_NetworkConfig__deviceReferringElement->setOrdered(false);
    m_NetworkConfig__refSystemSpecification->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getSystemSpecification());
    m_NetworkConfig__refSystemSpecification->setName("refSystemSpecification");
    m_NetworkConfig__refSystemSpecification->setDefaultValueLiteral("");
    m_NetworkConfig__refSystemSpecification->setLowerBound(0);
    m_NetworkConfig__refSystemSpecification->setUpperBound(1);
    m_NetworkConfig__refSystemSpecification->setTransient(false);
    m_NetworkConfig__refSystemSpecification->setVolatile(false);
    m_NetworkConfig__refSystemSpecification->setChangeable(true);
    m_NetworkConfig__refSystemSpecification->setContainment(false);
    m_NetworkConfig__refSystemSpecification->setResolveProxies(true);
    m_NetworkConfig__refSystemSpecification->setUnique(true);
    m_NetworkConfig__refSystemSpecification->setDerived(false);
    m_NetworkConfig__refSystemSpecification->setOrdered(false);
    m_NetworkConfig__refMappings->setEType(
            dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage* > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getMappings());
    m_NetworkConfig__refMappings->setName("refMappings");
    m_NetworkConfig__refMappings->setDefaultValueLiteral("");
    m_NetworkConfig__refMappings->setLowerBound(0);
    m_NetworkConfig__refMappings->setUpperBound(1);
    m_NetworkConfig__refMappings->setTransient(false);
    m_NetworkConfig__refMappings->setVolatile(false);
    m_NetworkConfig__refMappings->setChangeable(true);
    m_NetworkConfig__refMappings->setContainment(false);
    m_NetworkConfig__refMappings->setResolveProxies(true);
    m_NetworkConfig__refMappings->setUnique(true);
    m_NetworkConfig__refMappings->setDerived(false);
    m_NetworkConfig__refMappings->setOrdered(false);
    m_NetworkConfig__refProtocol->setEType(
            dynamic_cast< ::Protocol_Definition::Protocol_DefinitionPackage* > (::Protocol_Definition::Protocol_DefinitionPackage::_instance())->getProtocol());
    m_NetworkConfig__refProtocol->setName("refProtocol");
    m_NetworkConfig__refProtocol->setDefaultValueLiteral("");
    m_NetworkConfig__refProtocol->setLowerBound(0);
    m_NetworkConfig__refProtocol->setUpperBound(1);
    m_NetworkConfig__refProtocol->setTransient(false);
    m_NetworkConfig__refProtocol->setVolatile(false);
    m_NetworkConfig__refProtocol->setChangeable(true);
    m_NetworkConfig__refProtocol->setContainment(false);
    m_NetworkConfig__refProtocol->setResolveProxies(true);
    m_NetworkConfig__refProtocol->setUnique(true);
    m_NetworkConfig__refProtocol->setDerived(false);
    m_NetworkConfig__refProtocol->setOrdered(false);
    m_NetworkConfig__periods->setEType(m_PeriodsEClass);
    m_NetworkConfig__periods->setName("periods");
    m_NetworkConfig__periods->setDefaultValueLiteral("");
    m_NetworkConfig__periods->setLowerBound(0);
    m_NetworkConfig__periods->setUpperBound(-1);
    m_NetworkConfig__periods->setTransient(false);
    m_NetworkConfig__periods->setVolatile(false);
    m_NetworkConfig__periods->setChangeable(true);
    m_NetworkConfig__periods->setContainment(true);
    m_NetworkConfig__periods->setResolveProxies(true);
    m_NetworkConfig__periods->setUnique(true);
    m_NetworkConfig__periods->setDerived(false);
    m_NetworkConfig__periods->setOrdered(true);
    m_NetworkConfig__refVirtualLinkMapping->setEType(
            dynamic_cast< ::Virtuallink_Map::Virtuallink_MapPackage* > (::Virtuallink_Map::Virtuallink_MapPackage::_instance())->getVirtualLinkMapping());
    m_NetworkConfig__refVirtualLinkMapping->setName("refVirtualLinkMapping");
    m_NetworkConfig__refVirtualLinkMapping->setDefaultValueLiteral("");
    m_NetworkConfig__refVirtualLinkMapping->setLowerBound(0);
    m_NetworkConfig__refVirtualLinkMapping->setUpperBound(1);
    m_NetworkConfig__refVirtualLinkMapping->setTransient(false);
    m_NetworkConfig__refVirtualLinkMapping->setVolatile(false);
    m_NetworkConfig__refVirtualLinkMapping->setChangeable(true);
    m_NetworkConfig__refVirtualLinkMapping->setContainment(false);
    m_NetworkConfig__refVirtualLinkMapping->setResolveProxies(true);
    m_NetworkConfig__refVirtualLinkMapping->setUnique(true);
    m_NetworkConfig__refVirtualLinkMapping->setDerived(false);
    m_NetworkConfig__refVirtualLinkMapping->setOrdered(true);
    // Synchronization
    m_SynchronizationEClass->setName("Synchronization");
    m_SynchronizationEClass->setAbstract(false);
    m_SynchronizationEClass->setInterface(false);
    m_Synchronization__syncDomain->setEType(m_SyncDomainEClass);
    m_Synchronization__syncDomain->setName("syncDomain");
    m_Synchronization__syncDomain->setDefaultValueLiteral("");
    m_Synchronization__syncDomain->setLowerBound(0);
    m_Synchronization__syncDomain->setUpperBound(-1);
    m_Synchronization__syncDomain->setTransient(false);
    m_Synchronization__syncDomain->setVolatile(false);
    m_Synchronization__syncDomain->setChangeable(true);
    m_Synchronization__syncDomain->setContainment(true);
    m_Synchronization__syncDomain->setResolveProxies(true);
    m_Synchronization__syncDomain->setUnique(true);
    m_Synchronization__syncDomain->setDerived(false);
    m_Synchronization__syncDomain->setOrdered(false);
    m_Synchronization__integrityConfigurations->setEType(
            m_IntegrityConfigurationsEClass);
    m_Synchronization__integrityConfigurations->setName(
            "integrityConfigurations");
    m_Synchronization__integrityConfigurations->setDefaultValueLiteral("");
    m_Synchronization__integrityConfigurations->setLowerBound(0);
    m_Synchronization__integrityConfigurations->setUpperBound(1);
    m_Synchronization__integrityConfigurations->setTransient(false);
    m_Synchronization__integrityConfigurations->setVolatile(false);
    m_Synchronization__integrityConfigurations->setChangeable(true);
    m_Synchronization__integrityConfigurations->setContainment(true);
    m_Synchronization__integrityConfigurations->setResolveProxies(true);
    m_Synchronization__integrityConfigurations->setUnique(true);
    m_Synchronization__integrityConfigurations->setDerived(false);
    m_Synchronization__integrityConfigurations->setOrdered(false);
    // SyncDomain
    m_SyncDomainEClass->setName("SyncDomain");
    m_SyncDomainEClass->setAbstract(false);
    m_SyncDomainEClass->setInterface(false);
    m_SyncDomain__syncDomainId->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEByte());
    m_SyncDomain__syncDomainId->setName("syncDomainId");
    m_SyncDomain__syncDomainId->setDefaultValueLiteral("0");
    m_SyncDomain__syncDomainId->setLowerBound(0);
    m_SyncDomain__syncDomainId->setUpperBound(1);
    m_SyncDomain__syncDomainId->setTransient(false);
    m_SyncDomain__syncDomainId->setVolatile(false);
    m_SyncDomain__syncDomainId->setChangeable(true);
    m_SyncDomain__syncDomainId->setUnsettable(false);
    m_SyncDomain__syncDomainId->setID(false);
    m_SyncDomain__syncDomainId->setUnique(true);
    m_SyncDomain__syncDomainId->setDerived(false);
    m_SyncDomain__syncDomainId->setOrdered(true);
    m_SyncDomain__clusterCycleDuration->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncDomain__clusterCycleDuration->setName("clusterCycleDuration");
    m_SyncDomain__clusterCycleDuration->setDefaultValueLiteral("0ns");
    m_SyncDomain__clusterCycleDuration->setLowerBound(1);
    m_SyncDomain__clusterCycleDuration->setUpperBound(1);
    m_SyncDomain__clusterCycleDuration->setTransient(false);
    m_SyncDomain__clusterCycleDuration->setVolatile(false);
    m_SyncDomain__clusterCycleDuration->setChangeable(true);
    m_SyncDomain__clusterCycleDuration->setUnsettable(false);
    m_SyncDomain__clusterCycleDuration->setID(false);
    m_SyncDomain__clusterCycleDuration->setUnique(true);
    m_SyncDomain__clusterCycleDuration->setDerived(false);
    m_SyncDomain__clusterCycleDuration->setOrdered(true);
    m_SyncDomain__integrationCycleDuration->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncDomain__integrationCycleDuration->setName("integrationCycleDuration");
    m_SyncDomain__integrationCycleDuration->setDefaultValueLiteral("0ns");
    m_SyncDomain__integrationCycleDuration->setLowerBound(1);
    m_SyncDomain__integrationCycleDuration->setUpperBound(1);
    m_SyncDomain__integrationCycleDuration->setTransient(false);
    m_SyncDomain__integrationCycleDuration->setVolatile(false);
    m_SyncDomain__integrationCycleDuration->setChangeable(true);
    m_SyncDomain__integrationCycleDuration->setUnsettable(false);
    m_SyncDomain__integrationCycleDuration->setID(false);
    m_SyncDomain__integrationCycleDuration->setUnique(true);
    m_SyncDomain__integrationCycleDuration->setDerived(false);
    m_SyncDomain__integrationCycleDuration->setOrdered(true);
    m_SyncDomain__maxPcfTransmissionDelay->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncDomain__maxPcfTransmissionDelay->setName("maxPcfTransmissionDelay");
    m_SyncDomain__maxPcfTransmissionDelay->setDefaultValueLiteral("0ns");
    m_SyncDomain__maxPcfTransmissionDelay->setLowerBound(1);
    m_SyncDomain__maxPcfTransmissionDelay->setUpperBound(1);
    m_SyncDomain__maxPcfTransmissionDelay->setTransient(false);
    m_SyncDomain__maxPcfTransmissionDelay->setVolatile(false);
    m_SyncDomain__maxPcfTransmissionDelay->setChangeable(true);
    m_SyncDomain__maxPcfTransmissionDelay->setUnsettable(false);
    m_SyncDomain__maxPcfTransmissionDelay->setID(false);
    m_SyncDomain__maxPcfTransmissionDelay->setUnique(true);
    m_SyncDomain__maxPcfTransmissionDelay->setDerived(false);
    m_SyncDomain__maxPcfTransmissionDelay->setOrdered(true);
    m_SyncDomain__faultToleranceLevel->setEType(m_FaultToleranceEnumEEnum);
    m_SyncDomain__faultToleranceLevel->setName("faultToleranceLevel");
    m_SyncDomain__faultToleranceLevel->setDefaultValueLiteral(
            "singleFaultTolerant");
    m_SyncDomain__faultToleranceLevel->setLowerBound(0);
    m_SyncDomain__faultToleranceLevel->setUpperBound(1);
    m_SyncDomain__faultToleranceLevel->setTransient(false);
    m_SyncDomain__faultToleranceLevel->setVolatile(false);
    m_SyncDomain__faultToleranceLevel->setChangeable(true);
    m_SyncDomain__faultToleranceLevel->setUnsettable(false);
    m_SyncDomain__faultToleranceLevel->setID(false);
    m_SyncDomain__faultToleranceLevel->setUnique(true);
    m_SyncDomain__faultToleranceLevel->setDerived(false);
    m_SyncDomain__faultToleranceLevel->setOrdered(true);
    m_SyncDomain__integrityLevel->setEType(m_IntegrityLevelEnumEEnum);
    m_SyncDomain__integrityLevel->setName("integrityLevel");
    m_SyncDomain__integrityLevel->setDefaultValueLiteral("standard");
    m_SyncDomain__integrityLevel->setLowerBound(0);
    m_SyncDomain__integrityLevel->setUpperBound(1);
    m_SyncDomain__integrityLevel->setTransient(false);
    m_SyncDomain__integrityLevel->setVolatile(false);
    m_SyncDomain__integrityLevel->setChangeable(true);
    m_SyncDomain__integrityLevel->setUnsettable(false);
    m_SyncDomain__integrityLevel->setID(false);
    m_SyncDomain__integrityLevel->setUnique(true);
    m_SyncDomain__integrityLevel->setDerived(false);
    m_SyncDomain__integrityLevel->setOrdered(true);
    m_SyncDomain__avgMode->setEType(m_AvgModeEnumEEnum);
    m_SyncDomain__avgMode->setName("avgMode");
    m_SyncDomain__avgMode->setDefaultValueLiteral("median");
    m_SyncDomain__avgMode->setLowerBound(0);
    m_SyncDomain__avgMode->setUpperBound(1);
    m_SyncDomain__avgMode->setTransient(false);
    m_SyncDomain__avgMode->setVolatile(false);
    m_SyncDomain__avgMode->setChangeable(true);
    m_SyncDomain__avgMode->setUnsettable(false);
    m_SyncDomain__avgMode->setID(false);
    m_SyncDomain__avgMode->setUnique(true);
    m_SyncDomain__avgMode->setDerived(false);
    m_SyncDomain__avgMode->setOrdered(true);
    m_SyncDomain__syncPriority->setEType(m_SyncPriorityEClass);
    m_SyncDomain__syncPriority->setName("syncPriority");
    m_SyncDomain__syncPriority->setDefaultValueLiteral("");
    m_SyncDomain__syncPriority->setLowerBound(1);
    m_SyncDomain__syncPriority->setUpperBound(-1);
    m_SyncDomain__syncPriority->setTransient(false);
    m_SyncDomain__syncPriority->setVolatile(false);
    m_SyncDomain__syncPriority->setChangeable(true);
    m_SyncDomain__syncPriority->setContainment(true);
    m_SyncDomain__syncPriority->setResolveProxies(true);
    m_SyncDomain__syncPriority->setUnique(true);
    m_SyncDomain__syncPriority->setDerived(false);
    m_SyncDomain__syncPriority->setOrdered(true);
    // SyncPriority
    m_SyncPriorityEClass->setName("SyncPriority");
    m_SyncPriorityEClass->setAbstract(false);
    m_SyncPriorityEClass->setInterface(false);
    m_SyncPriority__value->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEByte());
    m_SyncPriority__value->setName("value");
    m_SyncPriority__value->setDefaultValueLiteral("0");
    m_SyncPriority__value->setLowerBound(1);
    m_SyncPriority__value->setUpperBound(1);
    m_SyncPriority__value->setTransient(false);
    m_SyncPriority__value->setVolatile(false);
    m_SyncPriority__value->setChangeable(true);
    m_SyncPriority__value->setUnsettable(false);
    m_SyncPriority__value->setID(false);
    m_SyncPriority__value->setUnique(true);
    m_SyncPriority__value->setDerived(false);
    m_SyncPriority__value->setOrdered(true);
    m_SyncPriority__syncClient->setEType(m_SyncClientEClass);
    m_SyncPriority__syncClient->setName("syncClient");
    m_SyncPriority__syncClient->setDefaultValueLiteral("");
    m_SyncPriority__syncClient->setLowerBound(0);
    m_SyncPriority__syncClient->setUpperBound(-1);
    m_SyncPriority__syncClient->setTransient(false);
    m_SyncPriority__syncClient->setVolatile(false);
    m_SyncPriority__syncClient->setChangeable(true);
    m_SyncPriority__syncClient->setContainment(true);
    m_SyncPriority__syncClient->setResolveProxies(true);
    m_SyncPriority__syncClient->setUnique(true);
    m_SyncPriority__syncClient->setDerived(false);
    m_SyncPriority__syncClient->setOrdered(true);
    m_SyncPriority__syncMaster->setEType(m_SyncMasterEClass);
    m_SyncPriority__syncMaster->setName("syncMaster");
    m_SyncPriority__syncMaster->setDefaultValueLiteral("");
    m_SyncPriority__syncMaster->setLowerBound(0);
    m_SyncPriority__syncMaster->setUpperBound(-1);
    m_SyncPriority__syncMaster->setTransient(false);
    m_SyncPriority__syncMaster->setVolatile(false);
    m_SyncPriority__syncMaster->setChangeable(true);
    m_SyncPriority__syncMaster->setContainment(true);
    m_SyncPriority__syncMaster->setResolveProxies(true);
    m_SyncPriority__syncMaster->setUnique(true);
    m_SyncPriority__syncMaster->setDerived(false);
    m_SyncPriority__syncMaster->setOrdered(true);
    m_SyncPriority__compressionMaster->setEType(m_CompressionMasterEClass);
    m_SyncPriority__compressionMaster->setName("compressionMaster");
    m_SyncPriority__compressionMaster->setDefaultValueLiteral("");
    m_SyncPriority__compressionMaster->setLowerBound(0);
    m_SyncPriority__compressionMaster->setUpperBound(-1);
    m_SyncPriority__compressionMaster->setTransient(false);
    m_SyncPriority__compressionMaster->setVolatile(false);
    m_SyncPriority__compressionMaster->setChangeable(true);
    m_SyncPriority__compressionMaster->setContainment(true);
    m_SyncPriority__compressionMaster->setResolveProxies(true);
    m_SyncPriority__compressionMaster->setUnique(true);
    m_SyncPriority__compressionMaster->setDerived(false);
    m_SyncPriority__compressionMaster->setOrdered(true);
    // SyncBase
    m_SyncBaseEClass->setName("SyncBase");
    m_SyncBaseEClass->setAbstract(true);
    m_SyncBaseEClass->setInterface(false);
    m_SyncBase__scheduledReceivePit->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncBase__scheduledReceivePit->setName("scheduledReceivePit");
    m_SyncBase__scheduledReceivePit->setDefaultValueLiteral("0ns");
    m_SyncBase__scheduledReceivePit->setLowerBound(1);
    m_SyncBase__scheduledReceivePit->setUpperBound(1);
    m_SyncBase__scheduledReceivePit->setTransient(false);
    m_SyncBase__scheduledReceivePit->setVolatile(false);
    m_SyncBase__scheduledReceivePit->setChangeable(true);
    m_SyncBase__scheduledReceivePit->setUnsettable(false);
    m_SyncBase__scheduledReceivePit->setID(false);
    m_SyncBase__scheduledReceivePit->setUnique(true);
    m_SyncBase__scheduledReceivePit->setDerived(false);
    m_SyncBase__scheduledReceivePit->setOrdered(true);
    m_SyncBase__acceptanceWindow->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncBase__acceptanceWindow->setName("acceptanceWindow");
    m_SyncBase__acceptanceWindow->setDefaultValueLiteral("0ns");
    m_SyncBase__acceptanceWindow->setLowerBound(1);
    m_SyncBase__acceptanceWindow->setUpperBound(1);
    m_SyncBase__acceptanceWindow->setTransient(false);
    m_SyncBase__acceptanceWindow->setVolatile(false);
    m_SyncBase__acceptanceWindow->setChangeable(true);
    m_SyncBase__acceptanceWindow->setUnsettable(false);
    m_SyncBase__acceptanceWindow->setID(false);
    m_SyncBase__acceptanceWindow->setUnique(true);
    m_SyncBase__acceptanceWindow->setDerived(false);
    m_SyncBase__acceptanceWindow->setOrdered(true);
    m_SyncBase__listenTimeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncBase__listenTimeout->setName("listenTimeout");
    m_SyncBase__listenTimeout->setDefaultValueLiteral("0ns");
    m_SyncBase__listenTimeout->setLowerBound(1);
    m_SyncBase__listenTimeout->setUpperBound(1);
    m_SyncBase__listenTimeout->setTransient(false);
    m_SyncBase__listenTimeout->setVolatile(false);
    m_SyncBase__listenTimeout->setChangeable(true);
    m_SyncBase__listenTimeout->setUnsettable(false);
    m_SyncBase__listenTimeout->setID(false);
    m_SyncBase__listenTimeout->setUnique(true);
    m_SyncBase__listenTimeout->setDerived(false);
    m_SyncBase__listenTimeout->setOrdered(true);
    m_SyncBase__priorityFallbackCycles->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SyncBase__priorityFallbackCycles->setName("priorityFallbackCycles");
    m_SyncBase__priorityFallbackCycles->setDefaultValueLiteral("0");
    m_SyncBase__priorityFallbackCycles->setLowerBound(0);
    m_SyncBase__priorityFallbackCycles->setUpperBound(1);
    m_SyncBase__priorityFallbackCycles->setTransient(false);
    m_SyncBase__priorityFallbackCycles->setVolatile(false);
    m_SyncBase__priorityFallbackCycles->setChangeable(true);
    m_SyncBase__priorityFallbackCycles->setUnsettable(false);
    m_SyncBase__priorityFallbackCycles->setID(false);
    m_SyncBase__priorityFallbackCycles->setUnique(true);
    m_SyncBase__priorityFallbackCycles->setDerived(false);
    m_SyncBase__priorityFallbackCycles->setOrdered(true);
    m_SyncBase__syncToStableEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_SyncBase__syncToStableEnabled->setName("syncToStableEnabled");
    m_SyncBase__syncToStableEnabled->setDefaultValueLiteral("false");
    m_SyncBase__syncToStableEnabled->setLowerBound(0);
    m_SyncBase__syncToStableEnabled->setUpperBound(1);
    m_SyncBase__syncToStableEnabled->setTransient(false);
    m_SyncBase__syncToStableEnabled->setVolatile(false);
    m_SyncBase__syncToStableEnabled->setChangeable(true);
    m_SyncBase__syncToStableEnabled->setUnsettable(false);
    m_SyncBase__syncToStableEnabled->setID(false);
    m_SyncBase__syncToStableEnabled->setUnique(true);
    m_SyncBase__syncToStableEnabled->setDerived(false);
    m_SyncBase__syncToStableEnabled->setOrdered(true);
    // SyncClient
    m_SyncClientEClass->setName("SyncClient");
    m_SyncClientEClass->setAbstract(false);
    m_SyncClientEClass->setInterface(false);
    m_SyncClient__refIntegrityConfig->setEType(
            m_SyncClientIntegrityConfigEClass);
    m_SyncClient__refIntegrityConfig->setName("refIntegrityConfig");
    m_SyncClient__refIntegrityConfig->setDefaultValueLiteral("");
    m_SyncClient__refIntegrityConfig->setLowerBound(1);
    m_SyncClient__refIntegrityConfig->setUpperBound(1);
    m_SyncClient__refIntegrityConfig->setTransient(false);
    m_SyncClient__refIntegrityConfig->setVolatile(false);
    m_SyncClient__refIntegrityConfig->setChangeable(true);
    m_SyncClient__refIntegrityConfig->setContainment(false);
    m_SyncClient__refIntegrityConfig->setResolveProxies(true);
    m_SyncClient__refIntegrityConfig->setUnique(true);
    m_SyncClient__refIntegrityConfig->setDerived(false);
    m_SyncClient__refIntegrityConfig->setOrdered(true);
    // ActiveSyncComponent
    m_ActiveSyncComponentEClass->setName("ActiveSyncComponent");
    m_ActiveSyncComponentEClass->setAbstract(false);
    m_ActiveSyncComponentEClass->setInterface(false);
    m_ActiveSyncComponent__sourceMacAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_ActiveSyncComponent__sourceMacAddress->setName("sourceMacAddress");
    m_ActiveSyncComponent__sourceMacAddress->setDefaultValueLiteral(
            "00:00:00:00:00:00");
    m_ActiveSyncComponent__sourceMacAddress->setLowerBound(1);
    m_ActiveSyncComponent__sourceMacAddress->setUpperBound(1);
    m_ActiveSyncComponent__sourceMacAddress->setTransient(false);
    m_ActiveSyncComponent__sourceMacAddress->setVolatile(false);
    m_ActiveSyncComponent__sourceMacAddress->setChangeable(true);
    m_ActiveSyncComponent__sourceMacAddress->setUnsettable(false);
    m_ActiveSyncComponent__sourceMacAddress->setID(false);
    m_ActiveSyncComponent__sourceMacAddress->setUnique(true);
    m_ActiveSyncComponent__sourceMacAddress->setDerived(false);
    m_ActiveSyncComponent__sourceMacAddress->setOrdered(true);
    m_ActiveSyncComponent__refPcfVlidIntegration->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPCFVirtualLink());
    m_ActiveSyncComponent__refPcfVlidIntegration->setName(
            "refPcfVlidIntegration");
    m_ActiveSyncComponent__refPcfVlidIntegration->setDefaultValueLiteral("");
    m_ActiveSyncComponent__refPcfVlidIntegration->setLowerBound(0);
    m_ActiveSyncComponent__refPcfVlidIntegration->setUpperBound(1);
    m_ActiveSyncComponent__refPcfVlidIntegration->setTransient(false);
    m_ActiveSyncComponent__refPcfVlidIntegration->setVolatile(false);
    m_ActiveSyncComponent__refPcfVlidIntegration->setChangeable(true);
    m_ActiveSyncComponent__refPcfVlidIntegration->setContainment(false);
    m_ActiveSyncComponent__refPcfVlidIntegration->setResolveProxies(true);
    m_ActiveSyncComponent__refPcfVlidIntegration->setUnique(true);
    m_ActiveSyncComponent__refPcfVlidIntegration->setDerived(false);
    m_ActiveSyncComponent__refPcfVlidIntegration->setOrdered(true);
    // DistributedSyncMaster
    m_DistributedSyncMasterEClass->setName("DistributedSyncMaster");
    m_DistributedSyncMasterEClass->setAbstract(false);
    m_DistributedSyncMasterEClass->setInterface(false);
    // CompressionMaster
    m_CompressionMasterEClass->setName("CompressionMaster");
    m_CompressionMasterEClass->setAbstract(false);
    m_CompressionMasterEClass->setInterface(false);
    m_CompressionMaster__observationWindowSize->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_CompressionMaster__observationWindowSize->setName("observationWindowSize");
    m_CompressionMaster__observationWindowSize->setDefaultValueLiteral("0ns");
    m_CompressionMaster__observationWindowSize->setLowerBound(1);
    m_CompressionMaster__observationWindowSize->setUpperBound(1);
    m_CompressionMaster__observationWindowSize->setTransient(false);
    m_CompressionMaster__observationWindowSize->setVolatile(false);
    m_CompressionMaster__observationWindowSize->setChangeable(true);
    m_CompressionMaster__observationWindowSize->setUnsettable(false);
    m_CompressionMaster__observationWindowSize->setID(false);
    m_CompressionMaster__observationWindowSize->setUnique(true);
    m_CompressionMaster__observationWindowSize->setDerived(false);
    m_CompressionMaster__observationWindowSize->setOrdered(true);
    m_CompressionMaster__caEnableTimeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_CompressionMaster__caEnableTimeout->setName("caEnableTimeout");
    m_CompressionMaster__caEnableTimeout->setDefaultValueLiteral("0ns");
    m_CompressionMaster__caEnableTimeout->setLowerBound(1);
    m_CompressionMaster__caEnableTimeout->setUpperBound(1);
    m_CompressionMaster__caEnableTimeout->setTransient(false);
    m_CompressionMaster__caEnableTimeout->setVolatile(false);
    m_CompressionMaster__caEnableTimeout->setChangeable(true);
    m_CompressionMaster__caEnableTimeout->setUnsettable(false);
    m_CompressionMaster__caEnableTimeout->setID(false);
    m_CompressionMaster__caEnableTimeout->setUnique(true);
    m_CompressionMaster__caEnableTimeout->setDerived(false);
    m_CompressionMaster__caEnableTimeout->setOrdered(true);
    m_CompressionMaster__wait4in0Timeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_CompressionMaster__wait4in0Timeout->setName("wait4in0Timeout");
    m_CompressionMaster__wait4in0Timeout->setDefaultValueLiteral("0ns");
    m_CompressionMaster__wait4in0Timeout->setLowerBound(1);
    m_CompressionMaster__wait4in0Timeout->setUpperBound(1);
    m_CompressionMaster__wait4in0Timeout->setTransient(false);
    m_CompressionMaster__wait4in0Timeout->setVolatile(false);
    m_CompressionMaster__wait4in0Timeout->setChangeable(true);
    m_CompressionMaster__wait4in0Timeout->setUnsettable(false);
    m_CompressionMaster__wait4in0Timeout->setID(false);
    m_CompressionMaster__wait4in0Timeout->setUnique(true);
    m_CompressionMaster__wait4in0Timeout->setDerived(false);
    m_CompressionMaster__wait4in0Timeout->setOrdered(true);
    m_CompressionMaster__busGuardian->setEType(m_BusGuardianEClass);
    m_CompressionMaster__busGuardian->setName("busGuardian");
    m_CompressionMaster__busGuardian->setDefaultValueLiteral("");
    m_CompressionMaster__busGuardian->setLowerBound(0);
    m_CompressionMaster__busGuardian->setUpperBound(1);
    m_CompressionMaster__busGuardian->setTransient(false);
    m_CompressionMaster__busGuardian->setVolatile(false);
    m_CompressionMaster__busGuardian->setChangeable(true);
    m_CompressionMaster__busGuardian->setContainment(true);
    m_CompressionMaster__busGuardian->setResolveProxies(true);
    m_CompressionMaster__busGuardian->setUnique(true);
    m_CompressionMaster__busGuardian->setDerived(false);
    m_CompressionMaster__busGuardian->setOrdered(true);
    m_CompressionMaster__cliqueDetection->setEType(m_CliqueDetectionEClass);
    m_CompressionMaster__cliqueDetection->setName("cliqueDetection");
    m_CompressionMaster__cliqueDetection->setDefaultValueLiteral("");
    m_CompressionMaster__cliqueDetection->setLowerBound(0);
    m_CompressionMaster__cliqueDetection->setUpperBound(1);
    m_CompressionMaster__cliqueDetection->setTransient(false);
    m_CompressionMaster__cliqueDetection->setVolatile(false);
    m_CompressionMaster__cliqueDetection->setChangeable(true);
    m_CompressionMaster__cliqueDetection->setContainment(true);
    m_CompressionMaster__cliqueDetection->setResolveProxies(true);
    m_CompressionMaster__cliqueDetection->setUnique(true);
    m_CompressionMaster__cliqueDetection->setDerived(false);
    m_CompressionMaster__cliqueDetection->setOrdered(true);
    m_CompressionMaster__refIntegrityConfig->setEType(
            m_CompressionMasterIntegrityConfigEClass);
    m_CompressionMaster__refIntegrityConfig->setName("refIntegrityConfig");
    m_CompressionMaster__refIntegrityConfig->setDefaultValueLiteral("");
    m_CompressionMaster__refIntegrityConfig->setLowerBound(1);
    m_CompressionMaster__refIntegrityConfig->setUpperBound(1);
    m_CompressionMaster__refIntegrityConfig->setTransient(false);
    m_CompressionMaster__refIntegrityConfig->setVolatile(false);
    m_CompressionMaster__refIntegrityConfig->setChangeable(true);
    m_CompressionMaster__refIntegrityConfig->setContainment(false);
    m_CompressionMaster__refIntegrityConfig->setResolveProxies(true);
    m_CompressionMaster__refIntegrityConfig->setUnique(true);
    m_CompressionMaster__refIntegrityConfig->setDerived(false);
    m_CompressionMaster__refIntegrityConfig->setOrdered(true);
    // CliqueDetection
    m_CliqueDetectionEClass->setName("CliqueDetection");
    m_CliqueDetectionEClass->setAbstract(false);
    m_CliqueDetectionEClass->setInterface(false);
    m_CliqueDetection__tentativeSyncRelayEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__tentativeSyncRelayEnabled->setName(
            "tentativeSyncRelayEnabled");
    m_CliqueDetection__tentativeSyncRelayEnabled->setDefaultValueLiteral("true");
    m_CliqueDetection__tentativeSyncRelayEnabled->setLowerBound(1);
    m_CliqueDetection__tentativeSyncRelayEnabled->setUpperBound(1);
    m_CliqueDetection__tentativeSyncRelayEnabled->setTransient(false);
    m_CliqueDetection__tentativeSyncRelayEnabled->setVolatile(false);
    m_CliqueDetection__tentativeSyncRelayEnabled->setChangeable(true);
    m_CliqueDetection__tentativeSyncRelayEnabled->setUnsettable(false);
    m_CliqueDetection__tentativeSyncRelayEnabled->setID(false);
    m_CliqueDetection__tentativeSyncRelayEnabled->setUnique(true);
    m_CliqueDetection__tentativeSyncRelayEnabled->setDerived(false);
    m_CliqueDetection__tentativeSyncRelayEnabled->setOrdered(true);
    m_CliqueDetection__syncRelayEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__syncRelayEnabled->setName("syncRelayEnabled");
    m_CliqueDetection__syncRelayEnabled->setDefaultValueLiteral("true");
    m_CliqueDetection__syncRelayEnabled->setLowerBound(1);
    m_CliqueDetection__syncRelayEnabled->setUpperBound(1);
    m_CliqueDetection__syncRelayEnabled->setTransient(false);
    m_CliqueDetection__syncRelayEnabled->setVolatile(false);
    m_CliqueDetection__syncRelayEnabled->setChangeable(true);
    m_CliqueDetection__syncRelayEnabled->setUnsettable(false);
    m_CliqueDetection__syncRelayEnabled->setID(false);
    m_CliqueDetection__syncRelayEnabled->setUnique(true);
    m_CliqueDetection__syncRelayEnabled->setDerived(false);
    m_CliqueDetection__syncRelayEnabled->setOrdered(true);
    m_CliqueDetection__stableRelayEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__stableRelayEnabled->setName("stableRelayEnabled");
    m_CliqueDetection__stableRelayEnabled->setDefaultValueLiteral("true");
    m_CliqueDetection__stableRelayEnabled->setLowerBound(1);
    m_CliqueDetection__stableRelayEnabled->setUpperBound(1);
    m_CliqueDetection__stableRelayEnabled->setTransient(false);
    m_CliqueDetection__stableRelayEnabled->setVolatile(false);
    m_CliqueDetection__stableRelayEnabled->setChangeable(true);
    m_CliqueDetection__stableRelayEnabled->setUnsettable(false);
    m_CliqueDetection__stableRelayEnabled->setID(false);
    m_CliqueDetection__stableRelayEnabled->setUnique(true);
    m_CliqueDetection__stableRelayEnabled->setDerived(false);
    m_CliqueDetection__stableRelayEnabled->setOrdered(true);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setName(
            "tentativeSyncMembershipAsyncEnabled");
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setDefaultValueLiteral(
            "true");
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setLowerBound(1);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setUpperBound(1);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setTransient(false);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setVolatile(false);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setChangeable(true);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setUnsettable(false);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setID(false);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setUnique(true);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setDerived(false);
    m_CliqueDetection__tentativeSyncMembershipAsyncEnabled->setOrdered(true);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setName(
            "tentativeSyncMembershipSyncEnabled");
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setDefaultValueLiteral(
            "true");
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setLowerBound(1);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setUpperBound(1);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setTransient(false);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setVolatile(false);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setChangeable(true);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setUnsettable(false);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setID(false);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setUnique(true);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setDerived(false);
    m_CliqueDetection__tentativeSyncMembershipSyncEnabled->setOrdered(true);
    m_CliqueDetection__syncMembershipAsyncEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__syncMembershipAsyncEnabled->setName(
            "syncMembershipAsyncEnabled");
    m_CliqueDetection__syncMembershipAsyncEnabled->setDefaultValueLiteral(
            "true");
    m_CliqueDetection__syncMembershipAsyncEnabled->setLowerBound(1);
    m_CliqueDetection__syncMembershipAsyncEnabled->setUpperBound(1);
    m_CliqueDetection__syncMembershipAsyncEnabled->setTransient(false);
    m_CliqueDetection__syncMembershipAsyncEnabled->setVolatile(false);
    m_CliqueDetection__syncMembershipAsyncEnabled->setChangeable(true);
    m_CliqueDetection__syncMembershipAsyncEnabled->setUnsettable(false);
    m_CliqueDetection__syncMembershipAsyncEnabled->setID(false);
    m_CliqueDetection__syncMembershipAsyncEnabled->setUnique(true);
    m_CliqueDetection__syncMembershipAsyncEnabled->setDerived(false);
    m_CliqueDetection__syncMembershipAsyncEnabled->setOrdered(true);
    m_CliqueDetection__syncMembershipSyncEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__syncMembershipSyncEnabled->setName(
            "syncMembershipSyncEnabled");
    m_CliqueDetection__syncMembershipSyncEnabled->setDefaultValueLiteral("true");
    m_CliqueDetection__syncMembershipSyncEnabled->setLowerBound(1);
    m_CliqueDetection__syncMembershipSyncEnabled->setUpperBound(1);
    m_CliqueDetection__syncMembershipSyncEnabled->setTransient(false);
    m_CliqueDetection__syncMembershipSyncEnabled->setVolatile(false);
    m_CliqueDetection__syncMembershipSyncEnabled->setChangeable(true);
    m_CliqueDetection__syncMembershipSyncEnabled->setUnsettable(false);
    m_CliqueDetection__syncMembershipSyncEnabled->setID(false);
    m_CliqueDetection__syncMembershipSyncEnabled->setUnique(true);
    m_CliqueDetection__syncMembershipSyncEnabled->setDerived(false);
    m_CliqueDetection__syncMembershipSyncEnabled->setOrdered(true);
    m_CliqueDetection__stableMembershipAsyncEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__stableMembershipAsyncEnabled->setName(
            "stableMembershipAsyncEnabled");
    m_CliqueDetection__stableMembershipAsyncEnabled->setDefaultValueLiteral(
            "true");
    m_CliqueDetection__stableMembershipAsyncEnabled->setLowerBound(1);
    m_CliqueDetection__stableMembershipAsyncEnabled->setUpperBound(1);
    m_CliqueDetection__stableMembershipAsyncEnabled->setTransient(false);
    m_CliqueDetection__stableMembershipAsyncEnabled->setVolatile(false);
    m_CliqueDetection__stableMembershipAsyncEnabled->setChangeable(true);
    m_CliqueDetection__stableMembershipAsyncEnabled->setUnsettable(false);
    m_CliqueDetection__stableMembershipAsyncEnabled->setID(false);
    m_CliqueDetection__stableMembershipAsyncEnabled->setUnique(true);
    m_CliqueDetection__stableMembershipAsyncEnabled->setDerived(false);
    m_CliqueDetection__stableMembershipAsyncEnabled->setOrdered(true);
    m_CliqueDetection__stableMembershipSyncEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_CliqueDetection__stableMembershipSyncEnabled->setName(
            "stableMembershipSyncEnabled");
    m_CliqueDetection__stableMembershipSyncEnabled->setDefaultValueLiteral(
            "true");
    m_CliqueDetection__stableMembershipSyncEnabled->setLowerBound(1);
    m_CliqueDetection__stableMembershipSyncEnabled->setUpperBound(1);
    m_CliqueDetection__stableMembershipSyncEnabled->setTransient(false);
    m_CliqueDetection__stableMembershipSyncEnabled->setVolatile(false);
    m_CliqueDetection__stableMembershipSyncEnabled->setChangeable(true);
    m_CliqueDetection__stableMembershipSyncEnabled->setUnsettable(false);
    m_CliqueDetection__stableMembershipSyncEnabled->setID(false);
    m_CliqueDetection__stableMembershipSyncEnabled->setUnique(true);
    m_CliqueDetection__stableMembershipSyncEnabled->setDerived(false);
    m_CliqueDetection__stableMembershipSyncEnabled->setOrdered(true);
    // BusGuardian
    m_BusGuardianEClass->setName("BusGuardian");
    m_BusGuardianEClass->setAbstract(false);
    m_BusGuardianEClass->setInterface(false);
    // IntegrityConfigurations
    m_IntegrityConfigurationsEClass->setName("IntegrityConfigurations");
    m_IntegrityConfigurationsEClass->setAbstract(false);
    m_IntegrityConfigurationsEClass->setInterface(false);
    m_IntegrityConfigurations__name->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_IntegrityConfigurations__name->setName("name");
    m_IntegrityConfigurations__name->setDefaultValueLiteral("");
    m_IntegrityConfigurations__name->setLowerBound(0);
    m_IntegrityConfigurations__name->setUpperBound(1);
    m_IntegrityConfigurations__name->setTransient(false);
    m_IntegrityConfigurations__name->setVolatile(false);
    m_IntegrityConfigurations__name->setChangeable(true);
    m_IntegrityConfigurations__name->setUnsettable(false);
    m_IntegrityConfigurations__name->setID(false);
    m_IntegrityConfigurations__name->setUnique(true);
    m_IntegrityConfigurations__name->setDerived(false);
    m_IntegrityConfigurations__name->setOrdered(true);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setEType(
            m_SyncClientIntegrityConfigEClass);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setName(
            "syncClientIntegrityConfig");
    m_IntegrityConfigurations__syncClientIntegrityConfig->setDefaultValueLiteral(
            "");
    m_IntegrityConfigurations__syncClientIntegrityConfig->setLowerBound(0);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setUpperBound(-1);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setTransient(false);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setVolatile(false);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setChangeable(true);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setContainment(true);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setResolveProxies(
            true);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setUnique(true);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setDerived(false);
    m_IntegrityConfigurations__syncClientIntegrityConfig->setOrdered(false);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setEType(
            m_CompressionMasterIntegrityConfigEClass);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setName(
            "compressionMasterIntegrityConfig");
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setDefaultValueLiteral(
            "");
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setLowerBound(
            0);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setUpperBound(
            -1);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setTransient(
            false);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setVolatile(
            false);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setChangeable(
            true);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setContainment(
            true);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setResolveProxies(
            true);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setUnique(true);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setDerived(
            false);
    m_IntegrityConfigurations__compressionMasterIntegrityConfig->setOrdered(
            false);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setEType(
            m_SyncMasterIntegrityConfigEClass);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setName(
            "syncMasterIntegrityConfig");
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setDefaultValueLiteral(
            "");
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setLowerBound(0);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setUpperBound(-1);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setTransient(false);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setVolatile(false);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setChangeable(true);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setContainment(true);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setResolveProxies(
            true);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setUnique(true);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setDerived(false);
    m_IntegrityConfigurations__syncMasterIntegrityConfig->setOrdered(false);
    // IntegrityConfigBase
    m_IntegrityConfigBaseEClass->setName("IntegrityConfigBase");
    m_IntegrityConfigBaseEClass->setAbstract(true);
    m_IntegrityConfigBaseEClass->setInterface(false);
    m_IntegrityConfigBase__integrateToSyncThreshold->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_IntegrityConfigBase__integrateToSyncThreshold->setName(
            "integrateToSyncThreshold");
    m_IntegrityConfigBase__integrateToSyncThreshold->setDefaultValueLiteral("0");
    m_IntegrityConfigBase__integrateToSyncThreshold->setLowerBound(1);
    m_IntegrityConfigBase__integrateToSyncThreshold->setUpperBound(1);
    m_IntegrityConfigBase__integrateToSyncThreshold->setTransient(false);
    m_IntegrityConfigBase__integrateToSyncThreshold->setVolatile(false);
    m_IntegrityConfigBase__integrateToSyncThreshold->setChangeable(true);
    m_IntegrityConfigBase__integrateToSyncThreshold->setUnsettable(false);
    m_IntegrityConfigBase__integrateToSyncThreshold->setID(false);
    m_IntegrityConfigBase__integrateToSyncThreshold->setUnique(true);
    m_IntegrityConfigBase__integrateToSyncThreshold->setDerived(false);
    m_IntegrityConfigBase__integrateToSyncThreshold->setOrdered(true);
    m_IntegrityConfigBase__numUnstableCycles->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_IntegrityConfigBase__numUnstableCycles->setName("numUnstableCycles");
    m_IntegrityConfigBase__numUnstableCycles->setDefaultValueLiteral("0");
    m_IntegrityConfigBase__numUnstableCycles->setLowerBound(1);
    m_IntegrityConfigBase__numUnstableCycles->setUpperBound(1);
    m_IntegrityConfigBase__numUnstableCycles->setTransient(false);
    m_IntegrityConfigBase__numUnstableCycles->setVolatile(false);
    m_IntegrityConfigBase__numUnstableCycles->setChangeable(true);
    m_IntegrityConfigBase__numUnstableCycles->setUnsettable(false);
    m_IntegrityConfigBase__numUnstableCycles->setID(false);
    m_IntegrityConfigBase__numUnstableCycles->setUnique(true);
    m_IntegrityConfigBase__numUnstableCycles->setDerived(false);
    m_IntegrityConfigBase__numUnstableCycles->setOrdered(true);
    m_IntegrityConfigBase__numStableCycles->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_IntegrityConfigBase__numStableCycles->setName("numStableCycles");
    m_IntegrityConfigBase__numStableCycles->setDefaultValueLiteral("0");
    m_IntegrityConfigBase__numStableCycles->setLowerBound(1);
    m_IntegrityConfigBase__numStableCycles->setUpperBound(1);
    m_IntegrityConfigBase__numStableCycles->setTransient(false);
    m_IntegrityConfigBase__numStableCycles->setVolatile(false);
    m_IntegrityConfigBase__numStableCycles->setChangeable(true);
    m_IntegrityConfigBase__numStableCycles->setUnsettable(false);
    m_IntegrityConfigBase__numStableCycles->setID(false);
    m_IntegrityConfigBase__numStableCycles->setUnique(true);
    m_IntegrityConfigBase__numStableCycles->setDerived(false);
    m_IntegrityConfigBase__numStableCycles->setOrdered(true);
    // SyncClientIntegrityConfig
    m_SyncClientIntegrityConfigEClass->setName("SyncClientIntegrityConfig");
    m_SyncClientIntegrityConfigEClass->setAbstract(false);
    m_SyncClientIntegrityConfigEClass->setInterface(false);
    // ActiveSyncComponentIntegrityConfig
    m_ActiveSyncComponentIntegrityConfigEClass->setName(
            "ActiveSyncComponentIntegrityConfig");
    m_ActiveSyncComponentIntegrityConfigEClass->setAbstract(true);
    m_ActiveSyncComponentIntegrityConfigEClass->setInterface(false);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setName(
            "waitThresholdAsync");
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setLowerBound(1);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setUpperBound(1);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setVolatile(false);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setID(false);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setUnique(true);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setDerived(false);
    m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync->setOrdered(true);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setName(
            "unsyncToSyncThreshold");
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setLowerBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setUpperBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setVolatile(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setID(false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setUnique(true);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setDerived(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold->setOrdered(
            true);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setName(
            "unsyncToTentativeThreshold");
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setLowerBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setUpperBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setVolatile(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setID(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setUnique(
            true);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setDerived(
            false);
    m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold->setOrdered(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setName(
            "tentativeSyncThresholdAsync");
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setLowerBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setUpperBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setVolatile(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setID(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setUnique(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setDerived(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync->setOrdered(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setName(
            "tentativeSyncThresholdSync");
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setLowerBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setUpperBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setVolatile(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setID(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setUnique(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setDerived(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync->setOrdered(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setName(
            "tentativeToSyncThreshold");
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setLowerBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setUpperBound(
            1);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setVolatile(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setID(false);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setUnique(
            true);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setDerived(
            false);
    m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold->setOrdered(
            true);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setName(
            "syncThresholdAsync");
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setLowerBound(1);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setUpperBound(1);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setVolatile(false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setID(false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setUnique(true);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setDerived(false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync->setOrdered(true);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setName(
            "syncThresholdSync");
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setLowerBound(1);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setUpperBound(1);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setTransient(false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setVolatile(false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setChangeable(true);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setID(false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setUnique(true);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setDerived(false);
    m_ActiveSyncComponentIntegrityConfig__syncThresholdSync->setOrdered(true);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setName(
            "stableThresholdAsync");
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setLowerBound(1);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setUpperBound(1);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setVolatile(
            false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setID(false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setUnique(true);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setDerived(
            false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync->setOrdered(true);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setName(
            "stableThresholdSync");
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setDefaultValueLiteral(
            "0");
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setLowerBound(1);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setUpperBound(1);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setTransient(
            false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setVolatile(
            false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setChangeable(
            true);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setUnsettable(
            false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setID(false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setUnique(true);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setDerived(false);
    m_ActiveSyncComponentIntegrityConfig__stableThresholdSync->setOrdered(true);
    // CompressionMasterIntegrityConfig
    m_CompressionMasterIntegrityConfigEClass->setName(
            "CompressionMasterIntegrityConfig");
    m_CompressionMasterIntegrityConfigEClass->setAbstract(false);
    m_CompressionMasterIntegrityConfigEClass->setInterface(false);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setName(
            "integrateToTentativeThreshold");
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setDefaultValueLiteral(
            "0");
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setLowerBound(
            1);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setUpperBound(
            1);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setTransient(
            false);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setVolatile(
            false);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setChangeable(
            true);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setUnsettable(
            false);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setID(
            false);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setUnique(
            true);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setDerived(
            false);
    m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold->setOrdered(
            true);
    // SyncMasterIntegrityConfig
    m_SyncMasterIntegrityConfigEClass->setName("SyncMasterIntegrityConfig");
    m_SyncMasterIntegrityConfigEClass->setAbstract(false);
    m_SyncMasterIntegrityConfigEClass->setInterface(false);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setName(
            "integrateToWaitThreshold");
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setDefaultValueLiteral(
            "0");
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setLowerBound(1);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setUpperBound(1);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setTransient(false);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setVolatile(false);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setChangeable(true);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setUnsettable(false);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setID(false);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setUnique(true);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setDerived(false);
    m_SyncMasterIntegrityConfig__integrateToWaitThreshold->setOrdered(true);
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
    // SyncMaster
    m_SyncMasterEClass->setName("SyncMaster");
    m_SyncMasterEClass->setAbstract(false);
    m_SyncMasterEClass->setInterface(false);
    m_SyncMaster__membershipBit->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEByte());
    m_SyncMaster__membershipBit->setName("membershipBit");
    m_SyncMaster__membershipBit->setDefaultValueLiteral("0");
    m_SyncMaster__membershipBit->setLowerBound(1);
    m_SyncMaster__membershipBit->setUpperBound(1);
    m_SyncMaster__membershipBit->setTransient(false);
    m_SyncMaster__membershipBit->setVolatile(false);
    m_SyncMaster__membershipBit->setChangeable(true);
    m_SyncMaster__membershipBit->setUnsettable(false);
    m_SyncMaster__membershipBit->setID(false);
    m_SyncMaster__membershipBit->setUnique(true);
    m_SyncMaster__membershipBit->setDerived(false);
    m_SyncMaster__membershipBit->setOrdered(true);
    m_SyncMaster__initialIntegrationCycle->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SyncMaster__initialIntegrationCycle->setName("initialIntegrationCycle");
    m_SyncMaster__initialIntegrationCycle->setDefaultValueLiteral("0");
    m_SyncMaster__initialIntegrationCycle->setLowerBound(0);
    m_SyncMaster__initialIntegrationCycle->setUpperBound(1);
    m_SyncMaster__initialIntegrationCycle->setTransient(false);
    m_SyncMaster__initialIntegrationCycle->setVolatile(false);
    m_SyncMaster__initialIntegrationCycle->setChangeable(true);
    m_SyncMaster__initialIntegrationCycle->setUnsettable(false);
    m_SyncMaster__initialIntegrationCycle->setID(false);
    m_SyncMaster__initialIntegrationCycle->setUnique(true);
    m_SyncMaster__initialIntegrationCycle->setDerived(false);
    m_SyncMaster__initialIntegrationCycle->setOrdered(true);
    m_SyncMaster__caOffset->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncMaster__caOffset->setName("caOffset");
    m_SyncMaster__caOffset->setDefaultValueLiteral("0ns");
    m_SyncMaster__caOffset->setLowerBound(0);
    m_SyncMaster__caOffset->setUpperBound(1);
    m_SyncMaster__caOffset->setTransient(false);
    m_SyncMaster__caOffset->setVolatile(false);
    m_SyncMaster__caOffset->setChangeable(true);
    m_SyncMaster__caOffset->setUnsettable(false);
    m_SyncMaster__caOffset->setID(false);
    m_SyncMaster__caOffset->setUnique(true);
    m_SyncMaster__caOffset->setDerived(false);
    m_SyncMaster__caOffset->setOrdered(true);
    m_SyncMaster__coldstartTimeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncMaster__coldstartTimeout->setName("coldstartTimeout");
    m_SyncMaster__coldstartTimeout->setDefaultValueLiteral("0ns");
    m_SyncMaster__coldstartTimeout->setLowerBound(0);
    m_SyncMaster__coldstartTimeout->setUpperBound(1);
    m_SyncMaster__coldstartTimeout->setTransient(false);
    m_SyncMaster__coldstartTimeout->setVolatile(false);
    m_SyncMaster__coldstartTimeout->setChangeable(true);
    m_SyncMaster__coldstartTimeout->setUnsettable(false);
    m_SyncMaster__coldstartTimeout->setID(false);
    m_SyncMaster__coldstartTimeout->setUnique(true);
    m_SyncMaster__coldstartTimeout->setDerived(false);
    m_SyncMaster__coldstartTimeout->setOrdered(true);
    m_SyncMaster__csOffset->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncMaster__csOffset->setName("csOffset");
    m_SyncMaster__csOffset->setDefaultValueLiteral("0ns");
    m_SyncMaster__csOffset->setLowerBound(0);
    m_SyncMaster__csOffset->setUpperBound(1);
    m_SyncMaster__csOffset->setTransient(false);
    m_SyncMaster__csOffset->setVolatile(false);
    m_SyncMaster__csOffset->setChangeable(true);
    m_SyncMaster__csOffset->setUnsettable(false);
    m_SyncMaster__csOffset->setID(false);
    m_SyncMaster__csOffset->setUnique(true);
    m_SyncMaster__csOffset->setDerived(false);
    m_SyncMaster__csOffset->setOrdered(true);
    m_SyncMaster__restartTimeoutAsync->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncMaster__restartTimeoutAsync->setName("restartTimeoutAsync");
    m_SyncMaster__restartTimeoutAsync->setDefaultValueLiteral("0ns");
    m_SyncMaster__restartTimeoutAsync->setLowerBound(0);
    m_SyncMaster__restartTimeoutAsync->setUpperBound(1);
    m_SyncMaster__restartTimeoutAsync->setTransient(false);
    m_SyncMaster__restartTimeoutAsync->setVolatile(false);
    m_SyncMaster__restartTimeoutAsync->setChangeable(true);
    m_SyncMaster__restartTimeoutAsync->setUnsettable(false);
    m_SyncMaster__restartTimeoutAsync->setID(false);
    m_SyncMaster__restartTimeoutAsync->setUnique(true);
    m_SyncMaster__restartTimeoutAsync->setDerived(false);
    m_SyncMaster__restartTimeoutAsync->setOrdered(true);
    m_SyncMaster__restartTimeoutSync->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_SyncMaster__restartTimeoutSync->setName("restartTimeoutSync");
    m_SyncMaster__restartTimeoutSync->setDefaultValueLiteral("0ns");
    m_SyncMaster__restartTimeoutSync->setLowerBound(0);
    m_SyncMaster__restartTimeoutSync->setUpperBound(1);
    m_SyncMaster__restartTimeoutSync->setTransient(false);
    m_SyncMaster__restartTimeoutSync->setVolatile(false);
    m_SyncMaster__restartTimeoutSync->setChangeable(true);
    m_SyncMaster__restartTimeoutSync->setUnsettable(false);
    m_SyncMaster__restartTimeoutSync->setID(false);
    m_SyncMaster__restartTimeoutSync->setUnique(true);
    m_SyncMaster__restartTimeoutSync->setDerived(false);
    m_SyncMaster__restartTimeoutSync->setOrdered(true);
    m_SyncMaster__clksyncFilterMax->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SyncMaster__clksyncFilterMax->setName("clksyncFilterMax");
    m_SyncMaster__clksyncFilterMax->setDefaultValueLiteral("0");
    m_SyncMaster__clksyncFilterMax->setLowerBound(0);
    m_SyncMaster__clksyncFilterMax->setUpperBound(1);
    m_SyncMaster__clksyncFilterMax->setTransient(false);
    m_SyncMaster__clksyncFilterMax->setVolatile(false);
    m_SyncMaster__clksyncFilterMax->setChangeable(true);
    m_SyncMaster__clksyncFilterMax->setUnsettable(false);
    m_SyncMaster__clksyncFilterMax->setID(false);
    m_SyncMaster__clksyncFilterMax->setUnique(true);
    m_SyncMaster__clksyncFilterMax->setDerived(false);
    m_SyncMaster__clksyncFilterMax->setOrdered(true);
    m_SyncMaster__refIntegrityConfig->setEType(
            m_SyncMasterIntegrityConfigEClass);
    m_SyncMaster__refIntegrityConfig->setName("refIntegrityConfig");
    m_SyncMaster__refIntegrityConfig->setDefaultValueLiteral("");
    m_SyncMaster__refIntegrityConfig->setLowerBound(1);
    m_SyncMaster__refIntegrityConfig->setUpperBound(1);
    m_SyncMaster__refIntegrityConfig->setTransient(false);
    m_SyncMaster__refIntegrityConfig->setVolatile(false);
    m_SyncMaster__refIntegrityConfig->setChangeable(true);
    m_SyncMaster__refIntegrityConfig->setContainment(false);
    m_SyncMaster__refIntegrityConfig->setResolveProxies(true);
    m_SyncMaster__refIntegrityConfig->setUnique(true);
    m_SyncMaster__refIntegrityConfig->setDerived(false);
    m_SyncMaster__refIntegrityConfig->setOrdered(true);
    m_SyncMaster__refPcfVlidColdstart->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPCFVirtualLink());
    m_SyncMaster__refPcfVlidColdstart->setName("refPcfVlidColdstart");
    m_SyncMaster__refPcfVlidColdstart->setDefaultValueLiteral("");
    m_SyncMaster__refPcfVlidColdstart->setLowerBound(0);
    m_SyncMaster__refPcfVlidColdstart->setUpperBound(1);
    m_SyncMaster__refPcfVlidColdstart->setTransient(false);
    m_SyncMaster__refPcfVlidColdstart->setVolatile(false);
    m_SyncMaster__refPcfVlidColdstart->setChangeable(true);
    m_SyncMaster__refPcfVlidColdstart->setContainment(false);
    m_SyncMaster__refPcfVlidColdstart->setResolveProxies(true);
    m_SyncMaster__refPcfVlidColdstart->setUnique(true);
    m_SyncMaster__refPcfVlidColdstart->setDerived(false);
    m_SyncMaster__refPcfVlidColdstart->setOrdered(true);
    m_SyncMaster__refPcfVlidColdstartAck->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getPCFVirtualLink());
    m_SyncMaster__refPcfVlidColdstartAck->setName("refPcfVlidColdstartAck");
    m_SyncMaster__refPcfVlidColdstartAck->setDefaultValueLiteral("");
    m_SyncMaster__refPcfVlidColdstartAck->setLowerBound(0);
    m_SyncMaster__refPcfVlidColdstartAck->setUpperBound(1);
    m_SyncMaster__refPcfVlidColdstartAck->setTransient(false);
    m_SyncMaster__refPcfVlidColdstartAck->setVolatile(false);
    m_SyncMaster__refPcfVlidColdstartAck->setChangeable(true);
    m_SyncMaster__refPcfVlidColdstartAck->setContainment(false);
    m_SyncMaster__refPcfVlidColdstartAck->setResolveProxies(true);
    m_SyncMaster__refPcfVlidColdstartAck->setUnique(true);
    m_SyncMaster__refPcfVlidColdstartAck->setDerived(false);
    m_SyncMaster__refPcfVlidColdstartAck->setOrdered(true);
    // StandaloneSyncMaster
    m_StandaloneSyncMasterEClass->setName("StandaloneSyncMaster");
    m_StandaloneSyncMasterEClass->setAbstract(false);
    m_StandaloneSyncMasterEClass->setInterface(false);

    // TODO: Initialize data types


    // AvgModeEnum
    m_AvgModeEnumEEnum->setName("AvgModeEnum");
    m_AvgModeEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // median
        _el->setName("median");
        _el->setValue(0);
        _el->setLiteral("median");
        _el->setEEnum(m_AvgModeEnumEEnum);
        m_AvgModeEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // average
        _el->setName("average");
        _el->setValue(1);
        _el->setLiteral("average");
        _el->setEEnum(m_AvgModeEnumEEnum);
        m_AvgModeEnumEEnum->getELiterals().push_back(_el);
    }

    // FaultToleranceEnum
    m_FaultToleranceEnumEEnum->setName("FaultToleranceEnum");
    m_FaultToleranceEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // nonFaultTolerant
        _el->setName("nonFaultTolerant");
        _el->setValue(0);
        _el->setLiteral("nonFaultTolerant");
        _el->setEEnum(m_FaultToleranceEnumEEnum);
        m_FaultToleranceEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // singleFaultTolerant
        _el->setName("singleFaultTolerant");
        _el->setValue(1);
        _el->setLiteral("singleFaultTolerant");
        _el->setEEnum(m_FaultToleranceEnumEEnum);
        m_FaultToleranceEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // doubleFaultTolerant
        _el->setName("doubleFaultTolerant");
        _el->setValue(2);
        _el->setLiteral("doubleFaultTolerant");
        _el->setEEnum(m_FaultToleranceEnumEEnum);
        m_FaultToleranceEnumEEnum->getELiterals().push_back(_el);
    }

    // IntegrityLevelEnum
    m_IntegrityLevelEnumEEnum->setName("IntegrityLevelEnum");
    m_IntegrityLevelEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // standard
        _el->setName("standard");
        _el->setValue(0);
        _el->setLiteral("standard");
        _el->setEEnum(m_IntegrityLevelEnumEEnum);
        m_IntegrityLevelEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // high
        _el->setName("high");
        _el->setValue(1);
        _el->setLiteral("high");
        _el->setEEnum(m_IntegrityLevelEnumEEnum);
        m_IntegrityLevelEnumEEnum->getELiterals().push_back(_el);
    }

    _initialize();
}

::ecore::EClass_ptr Network_ConfigurationPackage::getDeviceReferringElement()
{
    return m_DeviceReferringElementEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getNetworkConfig()
{
    return m_NetworkConfigEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSynchronization()
{
    return m_SynchronizationEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSyncDomain()
{
    return m_SyncDomainEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSyncPriority()
{
    return m_SyncPriorityEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSyncBase()
{
    return m_SyncBaseEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSyncClient()
{
    return m_SyncClientEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getActiveSyncComponent()
{
    return m_ActiveSyncComponentEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getDistributedSyncMaster()
{
    return m_DistributedSyncMasterEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getCompressionMaster()
{
    return m_CompressionMasterEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getCliqueDetection()
{
    return m_CliqueDetectionEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getBusGuardian()
{
    return m_BusGuardianEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getIntegrityConfigurations()
{
    return m_IntegrityConfigurationsEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getIntegrityConfigBase()
{
    return m_IntegrityConfigBaseEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSyncClientIntegrityConfig()
{
    return m_SyncClientIntegrityConfigEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig()
{
    return m_ActiveSyncComponentIntegrityConfigEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getCompressionMasterIntegrityConfig()
{
    return m_CompressionMasterIntegrityConfigEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSyncMasterIntegrityConfig()
{
    return m_SyncMasterIntegrityConfigEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getPeriods()
{
    return m_PeriodsEClass;
}
::ecore::EEnum_ptr Network_ConfigurationPackage::getAvgModeEnum()
{
    return m_AvgModeEnumEEnum;
}
::ecore::EEnum_ptr Network_ConfigurationPackage::getFaultToleranceEnum()
{
    return m_FaultToleranceEnumEEnum;
}
::ecore::EEnum_ptr Network_ConfigurationPackage::getIntegrityLevelEnum()
{
    return m_IntegrityLevelEnumEEnum;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getSyncMaster()
{
    return m_SyncMasterEClass;
}
::ecore::EClass_ptr Network_ConfigurationPackage::getStandaloneSyncMaster()
{
    return m_StandaloneSyncMasterEClass;
}

::ecore::EReference_ptr Network_ConfigurationPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getDeviceReferringElement__refDeviceSpecification()
{
    return m_DeviceReferringElement__refDeviceSpecification;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getDeviceReferringElement__refSyncConfiguration()
{
    return m_DeviceReferringElement__refSyncConfiguration;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getDeviceReferringElement__refDevice()
{
    return m_DeviceReferringElement__refDevice;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__metaInformation()
{
    return m_NetworkConfig__metaInformation;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__units()
{
    return m_NetworkConfig__units;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__synchronization()
{
    return m_NetworkConfig__synchronization;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__deviceReferringElement()
{
    return m_NetworkConfig__deviceReferringElement;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__refSystemSpecification()
{
    return m_NetworkConfig__refSystemSpecification;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__refMappings()
{
    return m_NetworkConfig__refMappings;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__refProtocol()
{
    return m_NetworkConfig__refProtocol;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__periods()
{
    return m_NetworkConfig__periods;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getNetworkConfig__refVirtualLinkMapping()
{
    return m_NetworkConfig__refVirtualLinkMapping;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSynchronization__syncDomain()
{
    return m_Synchronization__syncDomain;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSynchronization__integrityConfigurations()
{
    return m_Synchronization__integrityConfigurations;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncDomain__syncDomainId()
{
    return m_SyncDomain__syncDomainId;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncDomain__clusterCycleDuration()
{
    return m_SyncDomain__clusterCycleDuration;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncDomain__integrationCycleDuration()
{
    return m_SyncDomain__integrationCycleDuration;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncDomain__maxPcfTransmissionDelay()
{
    return m_SyncDomain__maxPcfTransmissionDelay;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncDomain__syncPriority()
{
    return m_SyncDomain__syncPriority;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncDomain__faultToleranceLevel()
{
    return m_SyncDomain__faultToleranceLevel;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncDomain__integrityLevel()
{
    return m_SyncDomain__integrityLevel;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncDomain__avgMode()
{
    return m_SyncDomain__avgMode;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncPriority__value()
{
    return m_SyncPriority__value;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncPriority__syncClient()
{
    return m_SyncPriority__syncClient;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncPriority__syncMaster()
{
    return m_SyncPriority__syncMaster;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncPriority__compressionMaster()
{
    return m_SyncPriority__compressionMaster;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncBase__scheduledReceivePit()
{
    return m_SyncBase__scheduledReceivePit;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncBase__acceptanceWindow()
{
    return m_SyncBase__acceptanceWindow;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncBase__listenTimeout()
{
    return m_SyncBase__listenTimeout;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncBase__priorityFallbackCycles()
{
    return m_SyncBase__priorityFallbackCycles;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncBase__syncToStableEnabled()
{
    return m_SyncBase__syncToStableEnabled;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncClient__refIntegrityConfig()
{
    return m_SyncClient__refIntegrityConfig;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponent__sourceMacAddress()
{
    return m_ActiveSyncComponent__sourceMacAddress;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getActiveSyncComponent__refPcfVlidIntegration()
{
    return m_ActiveSyncComponent__refPcfVlidIntegration;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__membershipBit()
{
    return m_SyncMaster__membershipBit;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__initialIntegrationCycle()
{
    return m_SyncMaster__initialIntegrationCycle;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncMaster__refIntegrityConfig()
{
    return m_SyncMaster__refIntegrityConfig;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__caOffset()
{
    return m_SyncMaster__caOffset;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__coldstartTimeout()
{
    return m_SyncMaster__coldstartTimeout;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__csOffset()
{
    return m_SyncMaster__csOffset;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__restartTimeoutAsync()
{
    return m_SyncMaster__restartTimeoutAsync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__restartTimeoutSync()
{
    return m_SyncMaster__restartTimeoutSync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMaster__clksyncFilterMax()
{
    return m_SyncMaster__clksyncFilterMax;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncMaster__refPcfVlidColdstart()
{
    return m_SyncMaster__refPcfVlidColdstart;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getSyncMaster__refPcfVlidColdstartAck()
{
    return m_SyncMaster__refPcfVlidColdstartAck;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getCompressionMaster__busGuardian()
{
    return m_CompressionMaster__busGuardian;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getCompressionMaster__cliqueDetection()
{
    return m_CompressionMaster__cliqueDetection;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCompressionMaster__observationWindowSize()
{
    return m_CompressionMaster__observationWindowSize;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCompressionMaster__caEnableTimeout()
{
    return m_CompressionMaster__caEnableTimeout;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCompressionMaster__wait4in0Timeout()
{
    return m_CompressionMaster__wait4in0Timeout;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getCompressionMaster__refIntegrityConfig()
{
    return m_CompressionMaster__refIntegrityConfig;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__tentativeSyncRelayEnabled()
{
    return m_CliqueDetection__tentativeSyncRelayEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__syncRelayEnabled()
{
    return m_CliqueDetection__syncRelayEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__stableRelayEnabled()
{
    return m_CliqueDetection__stableRelayEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__tentativeSyncMembershipAsyncEnabled()
{
    return m_CliqueDetection__tentativeSyncMembershipAsyncEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__tentativeSyncMembershipSyncEnabled()
{
    return m_CliqueDetection__tentativeSyncMembershipSyncEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__syncMembershipAsyncEnabled()
{
    return m_CliqueDetection__syncMembershipAsyncEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__syncMembershipSyncEnabled()
{
    return m_CliqueDetection__syncMembershipSyncEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__stableMembershipAsyncEnabled()
{
    return m_CliqueDetection__stableMembershipAsyncEnabled;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCliqueDetection__stableMembershipSyncEnabled()
{
    return m_CliqueDetection__stableMembershipSyncEnabled;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getIntegrityConfigurations__syncClientIntegrityConfig()
{
    return m_IntegrityConfigurations__syncClientIntegrityConfig;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getIntegrityConfigurations__compressionMasterIntegrityConfig()
{
    return m_IntegrityConfigurations__compressionMasterIntegrityConfig;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getIntegrityConfigurations__syncMasterIntegrityConfig()
{
    return m_IntegrityConfigurations__syncMasterIntegrityConfig;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getIntegrityConfigurations__name()
{
    return m_IntegrityConfigurations__name;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getIntegrityConfigBase__integrateToSyncThreshold()
{
    return m_IntegrityConfigBase__integrateToSyncThreshold;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getIntegrityConfigBase__numUnstableCycles()
{
    return m_IntegrityConfigBase__numUnstableCycles;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getIntegrityConfigBase__numStableCycles()
{
    return m_IntegrityConfigBase__numStableCycles;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__waitThresholdAsync()
{
    return m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold()
{
    return m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold()
{
    return m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync()
{
    return m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync()
{
    return m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold()
{
    return m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__syncThresholdAsync()
{
    return m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__syncThresholdSync()
{
    return m_ActiveSyncComponentIntegrityConfig__syncThresholdSync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__stableThresholdAsync()
{
    return m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getActiveSyncComponentIntegrityConfig__stableThresholdSync()
{
    return m_ActiveSyncComponentIntegrityConfig__stableThresholdSync;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getCompressionMasterIntegrityConfig__integrateToTentativeThreshold()
{
    return m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold;
}
::ecore::EAttribute_ptr Network_ConfigurationPackage::getSyncMasterIntegrityConfig__integrateToWaitThreshold()
{
    return m_SyncMasterIntegrityConfig__integrateToWaitThreshold;
}
::ecore::EReference_ptr Network_ConfigurationPackage::getPeriods__period()
{
    return m_Periods__period;
}

