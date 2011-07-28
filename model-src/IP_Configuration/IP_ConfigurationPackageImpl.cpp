// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IP_ConfigurationPackageImpl.cpp
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

#include <IP_Configuration/IP_ConfigurationPackage.hpp>
#include <IP_Configuration/IP_ConfigurationFactory.hpp>
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
#include <ecore/EAnnotation.hpp>
#include <ecore/EStringToStringMapEntry.hpp>
#include <Device_Targets/PortInfos.hpp>
#include <System_Specification/MetaInformation.hpp>

using namespace ::IP_Configuration;

IP_ConfigurationPackage::IP_ConfigurationPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = IP_ConfigurationFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // Implementation
    m_ImplementationEClass = new ::ecore::EClass();
    m_ImplementationEClass->setClassifierID(IMPLEMENTATION);
    m_ImplementationEClass->setEPackage(this);
    getEClassifiers().push_back(m_ImplementationEClass);
    m_Implementation__description = new ::ecore::EAttribute();
    m_Implementation__description->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DESCRIPTION);
    m_ImplementationEClass->getEStructuralFeatures().push_back(
            m_Implementation__description);
    m_Implementation__details = new ::ecore::EReference();
    m_Implementation__details->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IMPLEMENTATION__DETAILS);
    m_ImplementationEClass->getEStructuralFeatures().push_back(
            m_Implementation__details);

    // TTTechIp
    m_TTTechIpEClass = new ::ecore::EClass();
    m_TTTechIpEClass->setClassifierID(TTTECHIP);
    m_TTTechIpEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTTechIpEClass);
    m_TTTechIp__numDiagnosisScheduleEntries = new ::ecore::EAttribute();
    m_TTTechIp__numDiagnosisScheduleEntries->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMDIAGNOSISSCHEDULEENTRIES);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__numDiagnosisScheduleEntries);
    m_TTTechIp__vlIdBits = new ::ecore::EAttribute();
    m_TTTechIp__vlIdBits->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__VLIDBITS);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(m_TTTechIp__vlIdBits);
    m_TTTechIp__numScheduleEntries = new ::ecore::EAttribute();
    m_TTTechIp__numScheduleEntries->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSCHEDULEENTRIES);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__numScheduleEntries);
    m_TTTechIp__numPhysicalPorts = new ::ecore::EAttribute();
    m_TTTechIp__numPhysicalPorts->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMPHYSICALPORTS);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__numPhysicalPorts);
    m_TTTechIp__maxIntegrationCycles = new ::ecore::EAttribute();
    m_TTTechIp__maxIntegrationCycles->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__MAXINTEGRATIONCYCLES);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__maxIntegrationCycles);
    m_TTTechIp__numMacAcceptanceEntries = new ::ecore::EAttribute();
    m_TTTechIp__numMacAcceptanceEntries->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMMACACCEPTANCEENTRIES);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__numMacAcceptanceEntries);
    m_TTTechIp__numSubSchedules = new ::ecore::EAttribute();
    m_TTTechIp__numSubSchedules->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__NUMSUBSCHEDULES);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__numSubSchedules);
    m_TTTechIp__layer2MemByteGranularity = new ::ecore::EAttribute();
    m_TTTechIp__layer2MemByteGranularity->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTEGRANULARITY);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__layer2MemByteGranularity);
    m_TTTechIp__layer2memByteSize = new ::ecore::EAttribute();
    m_TTTechIp__layer2memByteSize->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__LAYER2MEMBYTESIZE);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__layer2memByteSize);
    m_TTTechIp__synchronizationDelayTicks = new ::ecore::EAttribute();
    m_TTTechIp__synchronizationDelayTicks->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__SYNCHRONIZATIONDELAYTICKS);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__synchronizationDelayTicks);
    m_TTTechIp__portinfo = new ::ecore::EReference();
    m_TTTechIp__portinfo->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__PORTINFO);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(m_TTTechIp__portinfo);
    m_TTTechIp__refIpLayout = new ::ecore::EReference();
    m_TTTechIp__refIpLayout->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__REFIPLAYOUT);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__refIpLayout);
    m_TTTechIp__metaInformation = new ::ecore::EReference();
    m_TTTechIp__metaInformation->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIP__METAINFORMATION);
    m_TTTechIpEClass->getEStructuralFeatures().push_back(
            m_TTTechIp__metaInformation);

    // TTTechSwIp
    m_TTTechSwIpEClass = new ::ecore::EClass();
    m_TTTechSwIpEClass->setClassifierID(TTTECHSWIP);
    m_TTTechSwIpEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTTechSwIpEClass);
    m_TTTechSwIp__numBagEntries = new ::ecore::EAttribute();
    m_TTTechSwIp__numBagEntries->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHSWIP__NUMBAGENTRIES);
    m_TTTechSwIpEClass->getEStructuralFeatures().push_back(
            m_TTTechSwIp__numBagEntries);
    m_TTTechSwIp__numDynamicCotsRoutes = new ::ecore::EAttribute();
    m_TTTechSwIp__numDynamicCotsRoutes->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHSWIP__NUMDYNAMICCOTSROUTES);
    m_TTTechSwIpEClass->getEStructuralFeatures().push_back(
            m_TTTechSwIp__numDynamicCotsRoutes);
    m_TTTechSwIp__numAntiMasqueradingEntries = new ::ecore::EAttribute();
    m_TTTechSwIp__numAntiMasqueradingEntries->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHSWIP__NUMANTIMASQUERADINGENTRIES);
    m_TTTechSwIpEClass->getEStructuralFeatures().push_back(
            m_TTTechSwIp__numAntiMasqueradingEntries);
    m_TTTechSwIp__numStaticCotsRoutes = new ::ecore::EAttribute();
    m_TTTechSwIp__numStaticCotsRoutes->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHSWIP__NUMSTATICCOTSROUTES);
    m_TTTechSwIpEClass->getEStructuralFeatures().push_back(
            m_TTTechSwIp__numStaticCotsRoutes);
    m_TTTechSwIp__synchronizationDelayTicksCM = new ::ecore::EAttribute();
    m_TTTechSwIp__synchronizationDelayTicksCM->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHSWIP__SYNCHRONIZATIONDELAYTICKSCM);
    m_TTTechSwIpEClass->getEStructuralFeatures().push_back(
            m_TTTechSwIp__synchronizationDelayTicksCM);

    // TTTechEsIp
    m_TTTechEsIpEClass = new ::ecore::EClass();
    m_TTTechEsIpEClass->setClassifierID(TTTECHESIP);
    m_TTTechEsIpEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTTechEsIpEClass);
    m_TTTechEsIp__numSharedBuffers = new ::ecore::EAttribute();
    m_TTTechEsIp__numSharedBuffers->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMSHAREDBUFFERS);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__numSharedBuffers);
    m_TTTechEsIp__numDedicatedBuffers = new ::ecore::EAttribute();
    m_TTTechEsIp__numDedicatedBuffers->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMDEDICATEDBUFFERS);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__numDedicatedBuffers);
    m_TTTechEsIp__bufferMemorySize = new ::ecore::EAttribute();
    m_TTTechEsIp__bufferMemorySize->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__BUFFERMEMORYSIZE);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__bufferMemorySize);
    m_TTTechEsIp__numQueuedCtidBuffer = new ::ecore::EAttribute();
    m_TTTechEsIp__numQueuedCtidBuffer->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__NUMQUEUEDCTIDBUFFER);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__numQueuedCtidBuffer);
    m_TTTechEsIp__hostMemByteGranularity = new ::ecore::EAttribute();
    m_TTTechEsIp__hostMemByteGranularity->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTEGRANULARITY);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__hostMemByteGranularity);
    m_TTTechEsIp__hostMemByteSize = new ::ecore::EAttribute();
    m_TTTechEsIp__hostMemByteSize->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__HOSTMEMBYTESIZE);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__hostMemByteSize);
    m_TTTechEsIp__maxStateEntries = new ::ecore::EAttribute();
    m_TTTechEsIp__maxStateEntries->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXSTATEENTRIES);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__maxStateEntries);
    m_TTTechEsIp__maxQueueEntries = new ::ecore::EAttribute();
    m_TTTechEsIp__maxQueueEntries->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHESIP__MAXQUEUEENTRIES);
    m_TTTechEsIpEClass->getEStructuralFeatures().push_back(
            m_TTTechEsIp__maxQueueEntries);

    // IpLayout
    m_IpLayoutEClass = new ::ecore::EClass();
    m_IpLayoutEClass->setClassifierID(IPLAYOUT);
    m_IpLayoutEClass->setEPackage(this);
    getEClassifiers().push_back(m_IpLayoutEClass);
    m_IpLayout__description = new ::ecore::EAttribute();
    m_IpLayout__description->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__DESCRIPTION);
    m_IpLayoutEClass->getEStructuralFeatures().push_back(
            m_IpLayout__description);
    m_IpLayout__Version = new ::ecore::EAttribute();
    m_IpLayout__Version->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__VERSION);
    m_IpLayoutEClass->getEStructuralFeatures().push_back(m_IpLayout__Version);
    m_IpLayout__ID = new ::ecore::EAttribute();
    m_IpLayout__ID->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__ID);
    m_IpLayoutEClass->getEStructuralFeatures().push_back(m_IpLayout__ID);
    m_IpLayout__metaInformation = new ::ecore::EReference();
    m_IpLayout__metaInformation->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__METAINFORMATION);
    m_IpLayoutEClass->getEStructuralFeatures().push_back(
            m_IpLayout__metaInformation);

    // TTTechIpLayout
    m_TTTechIpLayoutEClass = new ::ecore::EClass();
    m_TTTechIpLayoutEClass->setClassifierID(TTTECHIPLAYOUT);
    m_TTTechIpLayoutEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTTechIpLayoutEClass);
    m_TTTechIpLayout__pinning = new ::ecore::EAttribute();
    m_TTTechIpLayout__pinning->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::TTTECHIPLAYOUT__PINNING);
    m_TTTechIpLayoutEClass->getEStructuralFeatures().push_back(
            m_TTTechIpLayout__pinning);

    // IpConfigurations
    m_IpConfigurationsEClass = new ::ecore::EClass();
    m_IpConfigurationsEClass->setClassifierID(IPCONFIGURATIONS);
    m_IpConfigurationsEClass->setEPackage(this);
    getEClassifiers().push_back(m_IpConfigurationsEClass);
    m_IpConfigurations__implementation = new ::ecore::EReference();
    m_IpConfigurations__implementation->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IMPLEMENTATION);
    m_IpConfigurationsEClass->getEStructuralFeatures().push_back(
            m_IpConfigurations__implementation);
    m_IpConfigurations__ipLayout = new ::ecore::EReference();
    m_IpConfigurations__ipLayout->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IPLAYOUT);
    m_IpConfigurationsEClass->getEStructuralFeatures().push_back(
            m_IpConfigurations__ipLayout);
    m_IpConfigurations__metaInformation = new ::ecore::EReference();
    m_IpConfigurations__metaInformation->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__METAINFORMATION);
    m_IpConfigurationsEClass->getEStructuralFeatures().push_back(
            m_IpConfigurations__metaInformation);

    // GeneralImplementationDescription
    m_GeneralImplementationDescriptionEClass = new ::ecore::EClass();
    m_GeneralImplementationDescriptionEClass->setClassifierID(
            GENERALIMPLEMENTATIONDESCRIPTION);
    m_GeneralImplementationDescriptionEClass->setEPackage(this);
    getEClassifiers().push_back(m_GeneralImplementationDescriptionEClass);
    m_GeneralImplementationDescription__source = new ::ecore::EAttribute();
    m_GeneralImplementationDescription__source->setFeatureID(
            ::IP_Configuration::IP_ConfigurationPackage::GENERALIMPLEMENTATIONDESCRIPTION__SOURCE);
    m_GeneralImplementationDescriptionEClass->getEStructuralFeatures().push_back(
            m_GeneralImplementationDescription__source);

    // Create enums


    // Create data types


    // Initialize package
    setName("IP_Configuration");
    setNsPrefix("ip");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/IP_Configuration_V1");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_ImplementationEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_TTTechIpEClass->getESuperTypes().push_back(m_ImplementationEClass);
    m_TTTechSwIpEClass->getESuperTypes().push_back(m_TTTechIpEClass);
    m_TTTechEsIpEClass->getESuperTypes().push_back(m_TTTechIpEClass);
    m_IpLayoutEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_TTTechIpLayoutEClass->getESuperTypes().push_back(m_IpLayoutEClass);
    m_IpConfigurationsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_GeneralImplementationDescriptionEClass->getESuperTypes().push_back(
            m_ImplementationEClass);

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // Implementation
    m_ImplementationEClass->setName("Implementation");
    m_ImplementationEClass->setAbstract(true);
    m_ImplementationEClass->setInterface(false);
    m_Implementation__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Implementation__description->setName("description");
    m_Implementation__description->setDefaultValueLiteral("");
    m_Implementation__description->setLowerBound(0);
    m_Implementation__description->setUpperBound(1);
    m_Implementation__description->setTransient(false);
    m_Implementation__description->setVolatile(false);
    m_Implementation__description->setChangeable(true);
    m_Implementation__description->setUnsettable(false);
    m_Implementation__description->setID(false);
    m_Implementation__description->setUnique(true);
    m_Implementation__description->setDerived(false);
    m_Implementation__description->setOrdered(true);
    m_Implementation__details->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEStringToStringMapEntry());
    m_Implementation__details->setName("details");
    m_Implementation__details->setDefaultValueLiteral("");
    m_Implementation__details->setLowerBound(0);
    m_Implementation__details->setUpperBound(-1);
    m_Implementation__details->setTransient(false);
    m_Implementation__details->setVolatile(false);
    m_Implementation__details->setChangeable(true);
    m_Implementation__details->setContainment(true);
    m_Implementation__details->setResolveProxies(true);
    m_Implementation__details->setUnique(true);
    m_Implementation__details->setDerived(false);
    m_Implementation__details->setOrdered(true);
    // TTTechIp
    m_TTTechIpEClass->setName("TTTechIp");
    m_TTTechIpEClass->setAbstract(true);
    m_TTTechIpEClass->setInterface(false);
    m_TTTechIp__numDiagnosisScheduleEntries->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__numDiagnosisScheduleEntries->setName(
            "numDiagnosisScheduleEntries");
    m_TTTechIp__numDiagnosisScheduleEntries->setDefaultValueLiteral("256");
    m_TTTechIp__numDiagnosisScheduleEntries->setLowerBound(1);
    m_TTTechIp__numDiagnosisScheduleEntries->setUpperBound(1);
    m_TTTechIp__numDiagnosisScheduleEntries->setTransient(false);
    m_TTTechIp__numDiagnosisScheduleEntries->setVolatile(false);
    m_TTTechIp__numDiagnosisScheduleEntries->setChangeable(true);
    m_TTTechIp__numDiagnosisScheduleEntries->setUnsettable(false);
    m_TTTechIp__numDiagnosisScheduleEntries->setID(false);
    m_TTTechIp__numDiagnosisScheduleEntries->setUnique(true);
    m_TTTechIp__numDiagnosisScheduleEntries->setDerived(false);
    m_TTTechIp__numDiagnosisScheduleEntries->setOrdered(true);
    m_TTTechIp__vlIdBits->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEByte());
    m_TTTechIp__vlIdBits->setName("vlIdBits");
    m_TTTechIp__vlIdBits->setDefaultValueLiteral("12");
    m_TTTechIp__vlIdBits->setLowerBound(1);
    m_TTTechIp__vlIdBits->setUpperBound(1);
    m_TTTechIp__vlIdBits->setTransient(false);
    m_TTTechIp__vlIdBits->setVolatile(false);
    m_TTTechIp__vlIdBits->setChangeable(true);
    m_TTTechIp__vlIdBits->setUnsettable(false);
    m_TTTechIp__vlIdBits->setID(false);
    m_TTTechIp__vlIdBits->setUnique(true);
    m_TTTechIp__vlIdBits->setDerived(false);
    m_TTTechIp__vlIdBits->setOrdered(true);
    m_TTTechIp__numScheduleEntries->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__numScheduleEntries->setName("numScheduleEntries");
    m_TTTechIp__numScheduleEntries->setDefaultValueLiteral("4096");
    m_TTTechIp__numScheduleEntries->setLowerBound(1);
    m_TTTechIp__numScheduleEntries->setUpperBound(1);
    m_TTTechIp__numScheduleEntries->setTransient(false);
    m_TTTechIp__numScheduleEntries->setVolatile(false);
    m_TTTechIp__numScheduleEntries->setChangeable(true);
    m_TTTechIp__numScheduleEntries->setUnsettable(false);
    m_TTTechIp__numScheduleEntries->setID(false);
    m_TTTechIp__numScheduleEntries->setUnique(true);
    m_TTTechIp__numScheduleEntries->setDerived(false);
    m_TTTechIp__numScheduleEntries->setOrdered(true);
    m_TTTechIp__numPhysicalPorts->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__numPhysicalPorts->setName("numPhysicalPorts");
    m_TTTechIp__numPhysicalPorts->setDefaultValueLiteral("");
    m_TTTechIp__numPhysicalPorts->setLowerBound(1);
    m_TTTechIp__numPhysicalPorts->setUpperBound(1);
    m_TTTechIp__numPhysicalPorts->setTransient(false);
    m_TTTechIp__numPhysicalPorts->setVolatile(false);
    m_TTTechIp__numPhysicalPorts->setChangeable(true);
    m_TTTechIp__numPhysicalPorts->setUnsettable(false);
    m_TTTechIp__numPhysicalPorts->setID(false);
    m_TTTechIp__numPhysicalPorts->setUnique(true);
    m_TTTechIp__numPhysicalPorts->setDerived(false);
    m_TTTechIp__numPhysicalPorts->setOrdered(true);
    m_TTTechIp__maxIntegrationCycles->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__maxIntegrationCycles->setName("maxIntegrationCycles");
    m_TTTechIp__maxIntegrationCycles->setDefaultValueLiteral("256");
    m_TTTechIp__maxIntegrationCycles->setLowerBound(1);
    m_TTTechIp__maxIntegrationCycles->setUpperBound(1);
    m_TTTechIp__maxIntegrationCycles->setTransient(false);
    m_TTTechIp__maxIntegrationCycles->setVolatile(false);
    m_TTTechIp__maxIntegrationCycles->setChangeable(true);
    m_TTTechIp__maxIntegrationCycles->setUnsettable(false);
    m_TTTechIp__maxIntegrationCycles->setID(false);
    m_TTTechIp__maxIntegrationCycles->setUnique(true);
    m_TTTechIp__maxIntegrationCycles->setDerived(false);
    m_TTTechIp__maxIntegrationCycles->setOrdered(true);
    m_TTTechIp__numMacAcceptanceEntries->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__numMacAcceptanceEntries->setName("numMacAcceptanceEntries");
    m_TTTechIp__numMacAcceptanceEntries->setDefaultValueLiteral("12");
    m_TTTechIp__numMacAcceptanceEntries->setLowerBound(1);
    m_TTTechIp__numMacAcceptanceEntries->setUpperBound(1);
    m_TTTechIp__numMacAcceptanceEntries->setTransient(false);
    m_TTTechIp__numMacAcceptanceEntries->setVolatile(false);
    m_TTTechIp__numMacAcceptanceEntries->setChangeable(true);
    m_TTTechIp__numMacAcceptanceEntries->setUnsettable(false);
    m_TTTechIp__numMacAcceptanceEntries->setID(false);
    m_TTTechIp__numMacAcceptanceEntries->setUnique(true);
    m_TTTechIp__numMacAcceptanceEntries->setDerived(false);
    m_TTTechIp__numMacAcceptanceEntries->setOrdered(true);
    m_TTTechIp__numSubSchedules->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__numSubSchedules->setName("numSubSchedules");
    m_TTTechIp__numSubSchedules->setDefaultValueLiteral("");
    m_TTTechIp__numSubSchedules->setLowerBound(1);
    m_TTTechIp__numSubSchedules->setUpperBound(1);
    m_TTTechIp__numSubSchedules->setTransient(false);
    m_TTTechIp__numSubSchedules->setVolatile(false);
    m_TTTechIp__numSubSchedules->setChangeable(true);
    m_TTTechIp__numSubSchedules->setUnsettable(false);
    m_TTTechIp__numSubSchedules->setID(false);
    m_TTTechIp__numSubSchedules->setUnique(true);
    m_TTTechIp__numSubSchedules->setDerived(false);
    m_TTTechIp__numSubSchedules->setOrdered(true);
    m_TTTechIp__layer2MemByteGranularity->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__layer2MemByteGranularity->setName("layer2MemByteGranularity");
    m_TTTechIp__layer2MemByteGranularity->setDefaultValueLiteral("");
    m_TTTechIp__layer2MemByteGranularity->setLowerBound(1);
    m_TTTechIp__layer2MemByteGranularity->setUpperBound(1);
    m_TTTechIp__layer2MemByteGranularity->setTransient(false);
    m_TTTechIp__layer2MemByteGranularity->setVolatile(false);
    m_TTTechIp__layer2MemByteGranularity->setChangeable(true);
    m_TTTechIp__layer2MemByteGranularity->setUnsettable(false);
    m_TTTechIp__layer2MemByteGranularity->setID(false);
    m_TTTechIp__layer2MemByteGranularity->setUnique(true);
    m_TTTechIp__layer2MemByteGranularity->setDerived(false);
    m_TTTechIp__layer2MemByteGranularity->setOrdered(true);
    m_TTTechIp__layer2memByteSize->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__layer2memByteSize->setName("layer2memByteSize");
    m_TTTechIp__layer2memByteSize->setDefaultValueLiteral("");
    m_TTTechIp__layer2memByteSize->setLowerBound(1);
    m_TTTechIp__layer2memByteSize->setUpperBound(1);
    m_TTTechIp__layer2memByteSize->setTransient(false);
    m_TTTechIp__layer2memByteSize->setVolatile(false);
    m_TTTechIp__layer2memByteSize->setChangeable(true);
    m_TTTechIp__layer2memByteSize->setUnsettable(false);
    m_TTTechIp__layer2memByteSize->setID(false);
    m_TTTechIp__layer2memByteSize->setUnique(true);
    m_TTTechIp__layer2memByteSize->setDerived(false);
    m_TTTechIp__layer2memByteSize->setOrdered(true);
    m_TTTechIp__synchronizationDelayTicks->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechIp__synchronizationDelayTicks->setName("synchronizationDelayTicks");
    m_TTTechIp__synchronizationDelayTicks->setDefaultValueLiteral("");
    m_TTTechIp__synchronizationDelayTicks->setLowerBound(1);
    m_TTTechIp__synchronizationDelayTicks->setUpperBound(1);
    m_TTTechIp__synchronizationDelayTicks->setTransient(false);
    m_TTTechIp__synchronizationDelayTicks->setVolatile(false);
    m_TTTechIp__synchronizationDelayTicks->setChangeable(true);
    m_TTTechIp__synchronizationDelayTicks->setUnsettable(false);
    m_TTTechIp__synchronizationDelayTicks->setID(false);
    m_TTTechIp__synchronizationDelayTicks->setUnique(true);
    m_TTTechIp__synchronizationDelayTicks->setDerived(false);
    m_TTTechIp__synchronizationDelayTicks->setOrdered(true);
    m_TTTechIp__portinfo->setEType(
            dynamic_cast< ::Device_Targets::Device_TargetsPackage* > (::Device_Targets::Device_TargetsPackage::_instance())->getPortInfos());
    m_TTTechIp__portinfo->setName("portinfo");
    m_TTTechIp__portinfo->setDefaultValueLiteral("");
    m_TTTechIp__portinfo->setLowerBound(0);
    m_TTTechIp__portinfo->setUpperBound(1);
    m_TTTechIp__portinfo->setTransient(false);
    m_TTTechIp__portinfo->setVolatile(false);
    m_TTTechIp__portinfo->setChangeable(true);
    m_TTTechIp__portinfo->setContainment(true);
    m_TTTechIp__portinfo->setResolveProxies(true);
    m_TTTechIp__portinfo->setUnique(true);
    m_TTTechIp__portinfo->setDerived(false);
    m_TTTechIp__portinfo->setOrdered(true);
    m_TTTechIp__refIpLayout->setEType(m_TTTechIpLayoutEClass);
    m_TTTechIp__refIpLayout->setName("refIpLayout");
    m_TTTechIp__refIpLayout->setDefaultValueLiteral("");
    m_TTTechIp__refIpLayout->setLowerBound(0);
    m_TTTechIp__refIpLayout->setUpperBound(1);
    m_TTTechIp__refIpLayout->setTransient(false);
    m_TTTechIp__refIpLayout->setVolatile(false);
    m_TTTechIp__refIpLayout->setChangeable(true);
    m_TTTechIp__refIpLayout->setContainment(false);
    m_TTTechIp__refIpLayout->setResolveProxies(true);
    m_TTTechIp__refIpLayout->setUnique(true);
    m_TTTechIp__refIpLayout->setDerived(false);
    m_TTTechIp__refIpLayout->setOrdered(true);
    m_TTTechIp__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_TTTechIp__metaInformation->setName("metaInformation");
    m_TTTechIp__metaInformation->setDefaultValueLiteral("");
    m_TTTechIp__metaInformation->setLowerBound(0);
    m_TTTechIp__metaInformation->setUpperBound(1);
    m_TTTechIp__metaInformation->setTransient(false);
    m_TTTechIp__metaInformation->setVolatile(false);
    m_TTTechIp__metaInformation->setChangeable(true);
    m_TTTechIp__metaInformation->setContainment(true);
    m_TTTechIp__metaInformation->setResolveProxies(true);
    m_TTTechIp__metaInformation->setUnique(true);
    m_TTTechIp__metaInformation->setDerived(false);
    m_TTTechIp__metaInformation->setOrdered(true);
    // TTTechSwIp
    m_TTTechSwIpEClass->setName("TTTechSwIp");
    m_TTTechSwIpEClass->setAbstract(false);
    m_TTTechSwIpEClass->setInterface(false);
    m_TTTechSwIp__numBagEntries->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechSwIp__numBagEntries->setName("numBagEntries");
    m_TTTechSwIp__numBagEntries->setDefaultValueLiteral("256");
    m_TTTechSwIp__numBagEntries->setLowerBound(1);
    m_TTTechSwIp__numBagEntries->setUpperBound(1);
    m_TTTechSwIp__numBagEntries->setTransient(false);
    m_TTTechSwIp__numBagEntries->setVolatile(false);
    m_TTTechSwIp__numBagEntries->setChangeable(true);
    m_TTTechSwIp__numBagEntries->setUnsettable(false);
    m_TTTechSwIp__numBagEntries->setID(false);
    m_TTTechSwIp__numBagEntries->setUnique(true);
    m_TTTechSwIp__numBagEntries->setDerived(false);
    m_TTTechSwIp__numBagEntries->setOrdered(true);
    m_TTTechSwIp__numDynamicCotsRoutes->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechSwIp__numDynamicCotsRoutes->setName("numDynamicCotsRoutes");
    m_TTTechSwIp__numDynamicCotsRoutes->setDefaultValueLiteral("128");
    m_TTTechSwIp__numDynamicCotsRoutes->setLowerBound(1);
    m_TTTechSwIp__numDynamicCotsRoutes->setUpperBound(1);
    m_TTTechSwIp__numDynamicCotsRoutes->setTransient(false);
    m_TTTechSwIp__numDynamicCotsRoutes->setVolatile(false);
    m_TTTechSwIp__numDynamicCotsRoutes->setChangeable(true);
    m_TTTechSwIp__numDynamicCotsRoutes->setUnsettable(false);
    m_TTTechSwIp__numDynamicCotsRoutes->setID(false);
    m_TTTechSwIp__numDynamicCotsRoutes->setUnique(true);
    m_TTTechSwIp__numDynamicCotsRoutes->setDerived(false);
    m_TTTechSwIp__numDynamicCotsRoutes->setOrdered(true);
    m_TTTechSwIp__numAntiMasqueradingEntries->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechSwIp__numAntiMasqueradingEntries->setName(
            "numAntiMasqueradingEntries");
    m_TTTechSwIp__numAntiMasqueradingEntries->setDefaultValueLiteral("32");
    m_TTTechSwIp__numAntiMasqueradingEntries->setLowerBound(1);
    m_TTTechSwIp__numAntiMasqueradingEntries->setUpperBound(1);
    m_TTTechSwIp__numAntiMasqueradingEntries->setTransient(false);
    m_TTTechSwIp__numAntiMasqueradingEntries->setVolatile(false);
    m_TTTechSwIp__numAntiMasqueradingEntries->setChangeable(true);
    m_TTTechSwIp__numAntiMasqueradingEntries->setUnsettable(false);
    m_TTTechSwIp__numAntiMasqueradingEntries->setID(false);
    m_TTTechSwIp__numAntiMasqueradingEntries->setUnique(true);
    m_TTTechSwIp__numAntiMasqueradingEntries->setDerived(false);
    m_TTTechSwIp__numAntiMasqueradingEntries->setOrdered(true);
    m_TTTechSwIp__numStaticCotsRoutes->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechSwIp__numStaticCotsRoutes->setName("numStaticCotsRoutes");
    m_TTTechSwIp__numStaticCotsRoutes->setDefaultValueLiteral("128");
    m_TTTechSwIp__numStaticCotsRoutes->setLowerBound(1);
    m_TTTechSwIp__numStaticCotsRoutes->setUpperBound(1);
    m_TTTechSwIp__numStaticCotsRoutes->setTransient(false);
    m_TTTechSwIp__numStaticCotsRoutes->setVolatile(false);
    m_TTTechSwIp__numStaticCotsRoutes->setChangeable(true);
    m_TTTechSwIp__numStaticCotsRoutes->setUnsettable(false);
    m_TTTechSwIp__numStaticCotsRoutes->setID(false);
    m_TTTechSwIp__numStaticCotsRoutes->setUnique(true);
    m_TTTechSwIp__numStaticCotsRoutes->setDerived(false);
    m_TTTechSwIp__numStaticCotsRoutes->setOrdered(true);
    m_TTTechSwIp__synchronizationDelayTicksCM->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechSwIp__synchronizationDelayTicksCM->setName(
            "synchronizationDelayTicksCM");
    m_TTTechSwIp__synchronizationDelayTicksCM->setDefaultValueLiteral("");
    m_TTTechSwIp__synchronizationDelayTicksCM->setLowerBound(1);
    m_TTTechSwIp__synchronizationDelayTicksCM->setUpperBound(1);
    m_TTTechSwIp__synchronizationDelayTicksCM->setTransient(false);
    m_TTTechSwIp__synchronizationDelayTicksCM->setVolatile(false);
    m_TTTechSwIp__synchronizationDelayTicksCM->setChangeable(true);
    m_TTTechSwIp__synchronizationDelayTicksCM->setUnsettable(false);
    m_TTTechSwIp__synchronizationDelayTicksCM->setID(false);
    m_TTTechSwIp__synchronizationDelayTicksCM->setUnique(true);
    m_TTTechSwIp__synchronizationDelayTicksCM->setDerived(false);
    m_TTTechSwIp__synchronizationDelayTicksCM->setOrdered(true);
    // TTTechEsIp
    m_TTTechEsIpEClass->setName("TTTechEsIp");
    m_TTTechEsIpEClass->setAbstract(false);
    m_TTTechEsIpEClass->setInterface(false);
    m_TTTechEsIp__numSharedBuffers->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__numSharedBuffers->setName("numSharedBuffers");
    m_TTTechEsIp__numSharedBuffers->setDefaultValueLiteral("63");
    m_TTTechEsIp__numSharedBuffers->setLowerBound(1);
    m_TTTechEsIp__numSharedBuffers->setUpperBound(1);
    m_TTTechEsIp__numSharedBuffers->setTransient(false);
    m_TTTechEsIp__numSharedBuffers->setVolatile(false);
    m_TTTechEsIp__numSharedBuffers->setChangeable(true);
    m_TTTechEsIp__numSharedBuffers->setUnsettable(false);
    m_TTTechEsIp__numSharedBuffers->setID(false);
    m_TTTechEsIp__numSharedBuffers->setUnique(true);
    m_TTTechEsIp__numSharedBuffers->setDerived(false);
    m_TTTechEsIp__numSharedBuffers->setOrdered(true);
    m_TTTechEsIp__numDedicatedBuffers->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__numDedicatedBuffers->setName("numDedicatedBuffers");
    m_TTTechEsIp__numDedicatedBuffers->setDefaultValueLiteral("4096");
    m_TTTechEsIp__numDedicatedBuffers->setLowerBound(1);
    m_TTTechEsIp__numDedicatedBuffers->setUpperBound(1);
    m_TTTechEsIp__numDedicatedBuffers->setTransient(false);
    m_TTTechEsIp__numDedicatedBuffers->setVolatile(false);
    m_TTTechEsIp__numDedicatedBuffers->setChangeable(true);
    m_TTTechEsIp__numDedicatedBuffers->setUnsettable(false);
    m_TTTechEsIp__numDedicatedBuffers->setID(false);
    m_TTTechEsIp__numDedicatedBuffers->setUnique(true);
    m_TTTechEsIp__numDedicatedBuffers->setDerived(false);
    m_TTTechEsIp__numDedicatedBuffers->setOrdered(true);
    m_TTTechEsIp__bufferMemorySize->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__bufferMemorySize->setName("bufferMemorySize");
    m_TTTechEsIp__bufferMemorySize->setDefaultValueLiteral("128");
    m_TTTechEsIp__bufferMemorySize->setLowerBound(1);
    m_TTTechEsIp__bufferMemorySize->setUpperBound(1);
    m_TTTechEsIp__bufferMemorySize->setTransient(false);
    m_TTTechEsIp__bufferMemorySize->setVolatile(false);
    m_TTTechEsIp__bufferMemorySize->setChangeable(true);
    m_TTTechEsIp__bufferMemorySize->setUnsettable(false);
    m_TTTechEsIp__bufferMemorySize->setID(false);
    m_TTTechEsIp__bufferMemorySize->setUnique(true);
    m_TTTechEsIp__bufferMemorySize->setDerived(false);
    m_TTTechEsIp__bufferMemorySize->setOrdered(true);
    m_TTTechEsIp__numQueuedCtidBuffer->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__numQueuedCtidBuffer->setName("numQueuedCtidBuffer");
    m_TTTechEsIp__numQueuedCtidBuffer->setDefaultValueLiteral("8");
    m_TTTechEsIp__numQueuedCtidBuffer->setLowerBound(1);
    m_TTTechEsIp__numQueuedCtidBuffer->setUpperBound(1);
    m_TTTechEsIp__numQueuedCtidBuffer->setTransient(false);
    m_TTTechEsIp__numQueuedCtidBuffer->setVolatile(false);
    m_TTTechEsIp__numQueuedCtidBuffer->setChangeable(true);
    m_TTTechEsIp__numQueuedCtidBuffer->setUnsettable(false);
    m_TTTechEsIp__numQueuedCtidBuffer->setID(false);
    m_TTTechEsIp__numQueuedCtidBuffer->setUnique(true);
    m_TTTechEsIp__numQueuedCtidBuffer->setDerived(false);
    m_TTTechEsIp__numQueuedCtidBuffer->setOrdered(true);
    m_TTTechEsIp__hostMemByteGranularity->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__hostMemByteGranularity->setName("hostMemByteGranularity");
    m_TTTechEsIp__hostMemByteGranularity->setDefaultValueLiteral("");
    m_TTTechEsIp__hostMemByteGranularity->setLowerBound(1);
    m_TTTechEsIp__hostMemByteGranularity->setUpperBound(1);
    m_TTTechEsIp__hostMemByteGranularity->setTransient(false);
    m_TTTechEsIp__hostMemByteGranularity->setVolatile(false);
    m_TTTechEsIp__hostMemByteGranularity->setChangeable(true);
    m_TTTechEsIp__hostMemByteGranularity->setUnsettable(false);
    m_TTTechEsIp__hostMemByteGranularity->setID(false);
    m_TTTechEsIp__hostMemByteGranularity->setUnique(true);
    m_TTTechEsIp__hostMemByteGranularity->setDerived(false);
    m_TTTechEsIp__hostMemByteGranularity->setOrdered(true);
    m_TTTechEsIp__hostMemByteSize->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__hostMemByteSize->setName("hostMemByteSize");
    m_TTTechEsIp__hostMemByteSize->setDefaultValueLiteral("");
    m_TTTechEsIp__hostMemByteSize->setLowerBound(1);
    m_TTTechEsIp__hostMemByteSize->setUpperBound(1);
    m_TTTechEsIp__hostMemByteSize->setTransient(false);
    m_TTTechEsIp__hostMemByteSize->setVolatile(false);
    m_TTTechEsIp__hostMemByteSize->setChangeable(true);
    m_TTTechEsIp__hostMemByteSize->setUnsettable(false);
    m_TTTechEsIp__hostMemByteSize->setID(false);
    m_TTTechEsIp__hostMemByteSize->setUnique(true);
    m_TTTechEsIp__hostMemByteSize->setDerived(false);
    m_TTTechEsIp__hostMemByteSize->setOrdered(true);
    m_TTTechEsIp__maxStateEntries->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__maxStateEntries->setName("maxStateEntries");
    m_TTTechEsIp__maxStateEntries->setDefaultValueLiteral("3");
    m_TTTechEsIp__maxStateEntries->setLowerBound(1);
    m_TTTechEsIp__maxStateEntries->setUpperBound(1);
    m_TTTechEsIp__maxStateEntries->setTransient(false);
    m_TTTechEsIp__maxStateEntries->setVolatile(false);
    m_TTTechEsIp__maxStateEntries->setChangeable(true);
    m_TTTechEsIp__maxStateEntries->setUnsettable(false);
    m_TTTechEsIp__maxStateEntries->setID(false);
    m_TTTechEsIp__maxStateEntries->setUnique(true);
    m_TTTechEsIp__maxStateEntries->setDerived(false);
    m_TTTechEsIp__maxStateEntries->setOrdered(true);
    m_TTTechEsIp__maxQueueEntries->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TTTechEsIp__maxQueueEntries->setName("maxQueueEntries");
    m_TTTechEsIp__maxQueueEntries->setDefaultValueLiteral("63");
    m_TTTechEsIp__maxQueueEntries->setLowerBound(1);
    m_TTTechEsIp__maxQueueEntries->setUpperBound(1);
    m_TTTechEsIp__maxQueueEntries->setTransient(false);
    m_TTTechEsIp__maxQueueEntries->setVolatile(false);
    m_TTTechEsIp__maxQueueEntries->setChangeable(true);
    m_TTTechEsIp__maxQueueEntries->setUnsettable(false);
    m_TTTechEsIp__maxQueueEntries->setID(false);
    m_TTTechEsIp__maxQueueEntries->setUnique(true);
    m_TTTechEsIp__maxQueueEntries->setDerived(false);
    m_TTTechEsIp__maxQueueEntries->setOrdered(true);
    // IpLayout
    m_IpLayoutEClass->setName("IpLayout");
    m_IpLayoutEClass->setAbstract(true);
    m_IpLayoutEClass->setInterface(false);
    m_IpLayout__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_IpLayout__description->setName("description");
    m_IpLayout__description->setDefaultValueLiteral("");
    m_IpLayout__description->setLowerBound(0);
    m_IpLayout__description->setUpperBound(1);
    m_IpLayout__description->setTransient(false);
    m_IpLayout__description->setVolatile(false);
    m_IpLayout__description->setChangeable(true);
    m_IpLayout__description->setUnsettable(false);
    m_IpLayout__description->setID(false);
    m_IpLayout__description->setUnique(true);
    m_IpLayout__description->setDerived(false);
    m_IpLayout__description->setOrdered(true);
    m_IpLayout__Version->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_IpLayout__Version->setName("Version");
    m_IpLayout__Version->setDefaultValueLiteral("");
    m_IpLayout__Version->setLowerBound(0);
    m_IpLayout__Version->setUpperBound(1);
    m_IpLayout__Version->setTransient(false);
    m_IpLayout__Version->setVolatile(false);
    m_IpLayout__Version->setChangeable(true);
    m_IpLayout__Version->setUnsettable(false);
    m_IpLayout__Version->setID(false);
    m_IpLayout__Version->setUnique(true);
    m_IpLayout__Version->setDerived(false);
    m_IpLayout__Version->setOrdered(true);
    m_IpLayout__ID->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_IpLayout__ID->setName("ID");
    m_IpLayout__ID->setDefaultValueLiteral("");
    m_IpLayout__ID->setLowerBound(0);
    m_IpLayout__ID->setUpperBound(1);
    m_IpLayout__ID->setTransient(false);
    m_IpLayout__ID->setVolatile(false);
    m_IpLayout__ID->setChangeable(true);
    m_IpLayout__ID->setUnsettable(false);
    m_IpLayout__ID->setID(false);
    m_IpLayout__ID->setUnique(true);
    m_IpLayout__ID->setDerived(false);
    m_IpLayout__ID->setOrdered(true);
    m_IpLayout__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_IpLayout__metaInformation->setName("metaInformation");
    m_IpLayout__metaInformation->setDefaultValueLiteral("");
    m_IpLayout__metaInformation->setLowerBound(0);
    m_IpLayout__metaInformation->setUpperBound(1);
    m_IpLayout__metaInformation->setTransient(false);
    m_IpLayout__metaInformation->setVolatile(false);
    m_IpLayout__metaInformation->setChangeable(true);
    m_IpLayout__metaInformation->setContainment(true);
    m_IpLayout__metaInformation->setResolveProxies(true);
    m_IpLayout__metaInformation->setUnique(true);
    m_IpLayout__metaInformation->setDerived(false);
    m_IpLayout__metaInformation->setOrdered(true);
    // TTTechIpLayout
    m_TTTechIpLayoutEClass->setName("TTTechIpLayout");
    m_TTTechIpLayoutEClass->setAbstract(false);
    m_TTTechIpLayoutEClass->setInterface(false);
    m_TTTechIpLayout__pinning->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_TTTechIpLayout__pinning->setName("pinning");
    m_TTTechIpLayout__pinning->setDefaultValueLiteral("");
    m_TTTechIpLayout__pinning->setLowerBound(1);
    m_TTTechIpLayout__pinning->setUpperBound(1);
    m_TTTechIpLayout__pinning->setTransient(false);
    m_TTTechIpLayout__pinning->setVolatile(false);
    m_TTTechIpLayout__pinning->setChangeable(true);
    m_TTTechIpLayout__pinning->setUnsettable(false);
    m_TTTechIpLayout__pinning->setID(false);
    m_TTTechIpLayout__pinning->setUnique(true);
    m_TTTechIpLayout__pinning->setDerived(false);
    m_TTTechIpLayout__pinning->setOrdered(true);
    // IpConfigurations
    m_IpConfigurationsEClass->setName("IpConfigurations");
    m_IpConfigurationsEClass->setAbstract(false);
    m_IpConfigurationsEClass->setInterface(false);
    m_IpConfigurations__implementation->setEType(m_ImplementationEClass);
    m_IpConfigurations__implementation->setName("implementation");
    m_IpConfigurations__implementation->setDefaultValueLiteral("");
    m_IpConfigurations__implementation->setLowerBound(0);
    m_IpConfigurations__implementation->setUpperBound(-1);
    m_IpConfigurations__implementation->setTransient(false);
    m_IpConfigurations__implementation->setVolatile(false);
    m_IpConfigurations__implementation->setChangeable(true);
    m_IpConfigurations__implementation->setContainment(true);
    m_IpConfigurations__implementation->setResolveProxies(true);
    m_IpConfigurations__implementation->setUnique(true);
    m_IpConfigurations__implementation->setDerived(false);
    m_IpConfigurations__implementation->setOrdered(true);
    m_IpConfigurations__ipLayout->setEType(m_IpLayoutEClass);
    m_IpConfigurations__ipLayout->setName("ipLayout");
    m_IpConfigurations__ipLayout->setDefaultValueLiteral("");
    m_IpConfigurations__ipLayout->setLowerBound(0);
    m_IpConfigurations__ipLayout->setUpperBound(-1);
    m_IpConfigurations__ipLayout->setTransient(false);
    m_IpConfigurations__ipLayout->setVolatile(false);
    m_IpConfigurations__ipLayout->setChangeable(true);
    m_IpConfigurations__ipLayout->setContainment(true);
    m_IpConfigurations__ipLayout->setResolveProxies(true);
    m_IpConfigurations__ipLayout->setUnique(true);
    m_IpConfigurations__ipLayout->setDerived(false);
    m_IpConfigurations__ipLayout->setOrdered(true);
    m_IpConfigurations__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_IpConfigurations__metaInformation->setName("metaInformation");
    m_IpConfigurations__metaInformation->setDefaultValueLiteral("");
    m_IpConfigurations__metaInformation->setLowerBound(0);
    m_IpConfigurations__metaInformation->setUpperBound(1);
    m_IpConfigurations__metaInformation->setTransient(false);
    m_IpConfigurations__metaInformation->setVolatile(false);
    m_IpConfigurations__metaInformation->setChangeable(true);
    m_IpConfigurations__metaInformation->setContainment(true);
    m_IpConfigurations__metaInformation->setResolveProxies(true);
    m_IpConfigurations__metaInformation->setUnique(true);
    m_IpConfigurations__metaInformation->setDerived(false);
    m_IpConfigurations__metaInformation->setOrdered(true);
    // GeneralImplementationDescription
    m_GeneralImplementationDescriptionEClass->setName(
            "GeneralImplementationDescription");
    m_GeneralImplementationDescriptionEClass->setAbstract(false);
    m_GeneralImplementationDescriptionEClass->setInterface(false);
    m_GeneralImplementationDescription__source->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_GeneralImplementationDescription__source->setName("source");
    m_GeneralImplementationDescription__source->setDefaultValueLiteral("");
    m_GeneralImplementationDescription__source->setLowerBound(1);
    m_GeneralImplementationDescription__source->setUpperBound(1);
    m_GeneralImplementationDescription__source->setTransient(false);
    m_GeneralImplementationDescription__source->setVolatile(false);
    m_GeneralImplementationDescription__source->setChangeable(true);
    m_GeneralImplementationDescription__source->setUnsettable(false);
    m_GeneralImplementationDescription__source->setID(false);
    m_GeneralImplementationDescription__source->setUnique(true);
    m_GeneralImplementationDescription__source->setDerived(false);
    m_GeneralImplementationDescription__source->setOrdered(true);

    // TODO: Initialize data types


    _initialize();
}

::ecore::EClass_ptr IP_ConfigurationPackage::getImplementation()
{
    return m_ImplementationEClass;
}
::ecore::EClass_ptr IP_ConfigurationPackage::getTTTechIp()
{
    return m_TTTechIpEClass;
}
::ecore::EClass_ptr IP_ConfigurationPackage::getTTTechSwIp()
{
    return m_TTTechSwIpEClass;
}
::ecore::EClass_ptr IP_ConfigurationPackage::getTTTechEsIp()
{
    return m_TTTechEsIpEClass;
}
::ecore::EClass_ptr IP_ConfigurationPackage::getIpLayout()
{
    return m_IpLayoutEClass;
}
::ecore::EClass_ptr IP_ConfigurationPackage::getTTTechIpLayout()
{
    return m_TTTechIpLayoutEClass;
}
::ecore::EClass_ptr IP_ConfigurationPackage::getIpConfigurations()
{
    return m_IpConfigurationsEClass;
}
::ecore::EClass_ptr IP_ConfigurationPackage::getGeneralImplementationDescription()
{
    return m_GeneralImplementationDescriptionEClass;
}

::ecore::EReference_ptr IP_ConfigurationPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getImplementation__description()
{
    return m_Implementation__description;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getImplementation__details()
{
    return m_Implementation__details;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getTTTechIp__portinfo()
{
    return m_TTTechIp__portinfo;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getTTTechIp__refIpLayout()
{
    return m_TTTechIp__refIpLayout;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getTTTechIp__metaInformation()
{
    return m_TTTechIp__metaInformation;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__numDiagnosisScheduleEntries()
{
    return m_TTTechIp__numDiagnosisScheduleEntries;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__vlIdBits()
{
    return m_TTTechIp__vlIdBits;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__numScheduleEntries()
{
    return m_TTTechIp__numScheduleEntries;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__numPhysicalPorts()
{
    return m_TTTechIp__numPhysicalPorts;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__maxIntegrationCycles()
{
    return m_TTTechIp__maxIntegrationCycles;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__numMacAcceptanceEntries()
{
    return m_TTTechIp__numMacAcceptanceEntries;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__numSubSchedules()
{
    return m_TTTechIp__numSubSchedules;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__layer2MemByteGranularity()
{
    return m_TTTechIp__layer2MemByteGranularity;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__layer2memByteSize()
{
    return m_TTTechIp__layer2memByteSize;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIp__synchronizationDelayTicks()
{
    return m_TTTechIp__synchronizationDelayTicks;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechSwIp__numBagEntries()
{
    return m_TTTechSwIp__numBagEntries;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechSwIp__numDynamicCotsRoutes()
{
    return m_TTTechSwIp__numDynamicCotsRoutes;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechSwIp__numAntiMasqueradingEntries()
{
    return m_TTTechSwIp__numAntiMasqueradingEntries;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechSwIp__numStaticCotsRoutes()
{
    return m_TTTechSwIp__numStaticCotsRoutes;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechSwIp__synchronizationDelayTicksCM()
{
    return m_TTTechSwIp__synchronizationDelayTicksCM;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__numSharedBuffers()
{
    return m_TTTechEsIp__numSharedBuffers;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__numDedicatedBuffers()
{
    return m_TTTechEsIp__numDedicatedBuffers;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__bufferMemorySize()
{
    return m_TTTechEsIp__bufferMemorySize;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__numQueuedCtidBuffer()
{
    return m_TTTechEsIp__numQueuedCtidBuffer;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__hostMemByteGranularity()
{
    return m_TTTechEsIp__hostMemByteGranularity;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__hostMemByteSize()
{
    return m_TTTechEsIp__hostMemByteSize;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__maxStateEntries()
{
    return m_TTTechEsIp__maxStateEntries;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechEsIp__maxQueueEntries()
{
    return m_TTTechEsIp__maxQueueEntries;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getIpLayout__description()
{
    return m_IpLayout__description;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getIpLayout__Version()
{
    return m_IpLayout__Version;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getIpLayout__metaInformation()
{
    return m_IpLayout__metaInformation;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getIpLayout__ID()
{
    return m_IpLayout__ID;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getTTTechIpLayout__pinning()
{
    return m_TTTechIpLayout__pinning;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getIpConfigurations__implementation()
{
    return m_IpConfigurations__implementation;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getIpConfigurations__ipLayout()
{
    return m_IpConfigurations__ipLayout;
}
::ecore::EReference_ptr IP_ConfigurationPackage::getIpConfigurations__metaInformation()
{
    return m_IpConfigurations__metaInformation;
}
::ecore::EAttribute_ptr IP_ConfigurationPackage::getGeneralImplementationDescription__source()
{
    return m_GeneralImplementationDescription__source;
}

