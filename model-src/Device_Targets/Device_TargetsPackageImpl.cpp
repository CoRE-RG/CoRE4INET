// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/Device_TargetsPackageImpl.cpp
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

#include <Device_Targets/Device_TargetsPackage.hpp>
#include <Device_Targets/Device_TargetsFactory.hpp>
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
#include <IP_Configuration/IP_ConfigurationPackage.hpp>
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <IP_Configuration/Implementation.hpp>
#include <ecore/EStringToStringMapEntry.hpp>
#include <Device_Target_Mapping/SwPortMapping.hpp>
#include <System_Specification/VirtualLink.hpp>

using namespace ::Device_Targets;

Device_TargetsPackage::Device_TargetsPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = Device_TargetsFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // ManagementInterface
    m_ManagementInterfaceEClass = new ::ecore::EClass();
    m_ManagementInterfaceEClass->setClassifierID(MANAGEMENTINTERFACE);
    m_ManagementInterfaceEClass->setEPackage(this);
    getEClassifiers().push_back(m_ManagementInterfaceEClass);
    m_ManagementInterface__configurationVersion = new ::ecore::EAttribute();
    m_ManagementInterface__configurationVersion->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__CONFIGURATIONVERSION);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__configurationVersion);
    m_ManagementInterface__speed = new ::ecore::EAttribute();
    m_ManagementInterface__speed->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SPEED);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__speed);
    m_ManagementInterface__unlockWrTimeout = new ::ecore::EAttribute();
    m_ManagementInterface__unlockWrTimeout->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKWRTIMEOUT);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__unlockWrTimeout);
    m_ManagementInterface__resetTimeout = new ::ecore::EAttribute();
    m_ManagementInterface__resetTimeout->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__RESETTIMEOUT);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__resetTimeout);
    m_ManagementInterface__unlockDestAddress = new ::ecore::EAttribute();
    m_ManagementInterface__unlockDestAddress->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__UNLOCKDESTADDRESS);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__unlockDestAddress);
    m_ManagementInterface__schedDiagDestAddress = new ::ecore::EAttribute();
    m_ManagementInterface__schedDiagDestAddress->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SCHEDDIAGDESTADDRESS);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__schedDiagDestAddress);
    m_ManagementInterface__sourceAddress = new ::ecore::EAttribute();
    m_ManagementInterface__sourceAddress->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__SOURCEADDRESS);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__sourceAddress);
    m_ManagementInterface__expectedUnlocks = new ::ecore::EAttribute();
    m_ManagementInterface__expectedUnlocks->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDUNLOCKS);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__expectedUnlocks);
    m_ManagementInterface__expectedResets = new ::ecore::EAttribute();
    m_ManagementInterface__expectedResets->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__EXPECTEDRESETS);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__expectedResets);
    m_ManagementInterface__diagnosisScheduleMode = new ::ecore::EAttribute();
    m_ManagementInterface__diagnosisScheduleMode->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__DIAGNOSISSCHEDULEMODE);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__diagnosisScheduleMode);
    m_ManagementInterface__apbTimeout = new ::ecore::EAttribute();
    m_ManagementInterface__apbTimeout->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__APBTIMEOUT);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__apbTimeout);
    m_ManagementInterface__macAcceptanceEntry = new ::ecore::EReference();
    m_ManagementInterface__macAcceptanceEntry->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MANAGEMENTINTERFACE__MACACCEPTANCEENTRY);
    m_ManagementInterfaceEClass->getEStructuralFeatures().push_back(
            m_ManagementInterface__macAcceptanceEntry);

    // MacAcceptanceEntry
    m_MacAcceptanceEntryEClass = new ::ecore::EClass();
    m_MacAcceptanceEntryEClass->setClassifierID(MACACCEPTANCEENTRY);
    m_MacAcceptanceEntryEClass->setEPackage(this);
    getEClassifiers().push_back(m_MacAcceptanceEntryEClass);
    m_MacAcceptanceEntry__acceptanceMacAddress = new ::ecore::EAttribute();
    m_MacAcceptanceEntry__acceptanceMacAddress->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCEPTANCEMACADDRESS);
    m_MacAcceptanceEntryEClass->getEStructuralFeatures().push_back(
            m_MacAcceptanceEntry__acceptanceMacAddress);
    m_MacAcceptanceEntry__addressType = new ::ecore::EAttribute();
    m_MacAcceptanceEntry__addressType->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ADDRESSTYPE);
    m_MacAcceptanceEntryEClass->getEStructuralFeatures().push_back(
            m_MacAcceptanceEntry__addressType);
    m_MacAcceptanceEntry__unlockEnabled = new ::ecore::EAttribute();
    m_MacAcceptanceEntry__unlockEnabled->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__UNLOCKENABLED);
    m_MacAcceptanceEntryEClass->getEStructuralFeatures().push_back(
            m_MacAcceptanceEntry__unlockEnabled);
    m_MacAcceptanceEntry__resetEnabled = new ::ecore::EAttribute();
    m_MacAcceptanceEntry__resetEnabled->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESETENABLED);
    m_MacAcceptanceEntryEClass->getEStructuralFeatures().push_back(
            m_MacAcceptanceEntry__resetEnabled);
    m_MacAcceptanceEntry__responseDestMacAddress = new ::ecore::EAttribute();
    m_MacAcceptanceEntry__responseDestMacAddress->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESPONSEDESTMACADDRESS);
    m_MacAcceptanceEntryEClass->getEStructuralFeatures().push_back(
            m_MacAcceptanceEntry__responseDestMacAddress);
    m_MacAcceptanceEntry__accessControl = new ::ecore::EReference();
    m_MacAcceptanceEntry__accessControl->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCESSCONTROL);
    m_MacAcceptanceEntryEClass->getEStructuralFeatures().push_back(
            m_MacAcceptanceEntry__accessControl);

    // AccessControl
    m_AccessControlEClass = new ::ecore::EClass();
    m_AccessControlEClass->setClassifierID(ACCESSCONTROL);
    m_AccessControlEClass->setEPackage(this);
    getEClassifiers().push_back(m_AccessControlEClass);
    m_AccessControl__page = new ::ecore::EAttribute();
    m_AccessControl__page->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::ACCESSCONTROL__PAGE);
    m_AccessControlEClass->getEStructuralFeatures().push_back(
            m_AccessControl__page);
    m_AccessControl__writeEnable = new ::ecore::EAttribute();
    m_AccessControl__writeEnable->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::ACCESSCONTROL__WRITEENABLE);
    m_AccessControlEClass->getEStructuralFeatures().push_back(
            m_AccessControl__writeEnable);

    // TargetDevices
    m_TargetDevicesEClass = new ::ecore::EClass();
    m_TargetDevicesEClass->setClassifierID(TARGETDEVICES);
    m_TargetDevicesEClass->setEPackage(this);
    getEClassifiers().push_back(m_TargetDevicesEClass);
    m_TargetDevices__targetDevice = new ::ecore::EReference();
    m_TargetDevices__targetDevice->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETDEVICES__TARGETDEVICE);
    m_TargetDevicesEClass->getEStructuralFeatures().push_back(
            m_TargetDevices__targetDevice);
    m_TargetDevices__metaInformation = new ::ecore::EReference();
    m_TargetDevices__metaInformation->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETDEVICES__METAINFORMATION);
    m_TargetDevicesEClass->getEStructuralFeatures().push_back(
            m_TargetDevices__metaInformation);

    // TargetDevice
    m_TargetDeviceEClass = new ::ecore::EClass();
    m_TargetDeviceEClass->setClassifierID(TARGETDEVICE);
    m_TargetDeviceEClass->setEPackage(this);
    getEClassifiers().push_back(m_TargetDeviceEClass);
    m_TargetDevice__description = new ::ecore::EAttribute();
    m_TargetDevice__description->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DESCRIPTION);
    m_TargetDeviceEClass->getEStructuralFeatures().push_back(
            m_TargetDevice__description);
    m_TargetDevice__metaInformation = new ::ecore::EReference();
    m_TargetDevice__metaInformation->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__METAINFORMATION);
    m_TargetDeviceEClass->getEStructuralFeatures().push_back(
            m_TargetDevice__metaInformation);
    m_TargetDevice__refImplementation = new ::ecore::EReference();
    m_TargetDevice__refImplementation->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__REFIMPLEMENTATION);
    m_TargetDeviceEClass->getEStructuralFeatures().push_back(
            m_TargetDevice__refImplementation);
    m_TargetDevice__targetPorts = new ::ecore::EReference();
    m_TargetDevice__targetPorts->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__TARGETPORTS);
    m_TargetDeviceEClass->getEStructuralFeatures().push_back(
            m_TargetDevice__targetPorts);
    m_TargetDevice__details = new ::ecore::EReference();
    m_TargetDevice__details->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DETAILS);
    m_TargetDeviceEClass->getEStructuralFeatures().push_back(
            m_TargetDevice__details);

    // TTTechIpTargetDevice
    m_TTTechIpTargetDeviceEClass = new ::ecore::EClass();
    m_TTTechIpTargetDeviceEClass->setClassifierID(TTTECHIPTARGETDEVICE);
    m_TTTechIpTargetDeviceEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTTechIpTargetDeviceEClass);
    m_TTTechIpTargetDevice__clockSpeed = new ::ecore::EAttribute();
    m_TTTechIpTargetDevice__clockSpeed->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__CLOCKSPEED);
    m_TTTechIpTargetDeviceEClass->getEStructuralFeatures().push_back(
            m_TTTechIpTargetDevice__clockSpeed);
    m_TTTechIpTargetDevice__mediaControlEnabled = new ::ecore::EAttribute();
    m_TTTechIpTargetDevice__mediaControlEnabled->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__MEDIACONTROLENABLED);
    m_TTTechIpTargetDeviceEClass->getEStructuralFeatures().push_back(
            m_TTTechIpTargetDevice__mediaControlEnabled);

    // Diagnostic
    m_DiagnosticEClass = new ::ecore::EClass();
    m_DiagnosticEClass->setClassifierID(DIAGNOSTIC);
    m_DiagnosticEClass->setEPackage(this);
    getEClassifiers().push_back(m_DiagnosticEClass);
    m_Diagnostic__diagnosisScheduleEntry = new ::ecore::EReference();
    m_Diagnostic__diagnosisScheduleEntry->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::DIAGNOSTIC__DIAGNOSISSCHEDULEENTRY);
    m_DiagnosticEClass->getEStructuralFeatures().push_back(
            m_Diagnostic__diagnosisScheduleEntry);

    // DiagnosisScheduleEntry
    m_DiagnosisScheduleEntryEClass = new ::ecore::EClass();
    m_DiagnosisScheduleEntryEClass->setClassifierID(DIAGNOSISSCHEDULEENTRY);
    m_DiagnosisScheduleEntryEClass->setEPackage(this);
    getEClassifiers().push_back(m_DiagnosisScheduleEntryEClass);
    m_DiagnosisScheduleEntry__time = new ::ecore::EAttribute();
    m_DiagnosisScheduleEntry__time->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__TIME);
    m_DiagnosisScheduleEntryEClass->getEStructuralFeatures().push_back(
            m_DiagnosisScheduleEntry__time);
    m_DiagnosisScheduleEntry__itemAddress = new ::ecore::EAttribute();
    m_DiagnosisScheduleEntry__itemAddress->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMADDRESS);
    m_DiagnosisScheduleEntryEClass->getEStructuralFeatures().push_back(
            m_DiagnosisScheduleEntry__itemAddress);
    m_DiagnosisScheduleEntry__itemsNumber = new ::ecore::EAttribute();
    m_DiagnosisScheduleEntry__itemsNumber->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMSNUMBER);
    m_DiagnosisScheduleEntryEClass->getEStructuralFeatures().push_back(
            m_DiagnosisScheduleEntry__itemsNumber);

    // TargetPorts
    m_TargetPortsEClass = new ::ecore::EClass();
    m_TargetPortsEClass->setClassifierID(TARGETPORTS);
    m_TargetPortsEClass->setEPackage(this);
    getEClassifiers().push_back(m_TargetPortsEClass);
    m_TargetPorts__targetPort = new ::ecore::EReference();
    m_TargetPorts__targetPort->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETPORTS__TARGETPORT);
    m_TargetPortsEClass->getEStructuralFeatures().push_back(
            m_TargetPorts__targetPort);

    // TargetPort
    m_TargetPortEClass = new ::ecore::EClass();
    m_TargetPortEClass->setClassifierID(TARGETPORT);
    m_TargetPortEClass->setEPackage(this);
    getEClassifiers().push_back(m_TargetPortEClass);
    m_TargetPort__rxLatency = new ::ecore::EAttribute();
    m_TargetPort__rxLatency->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETPORT__RXLATENCY);
    m_TargetPortEClass->getEStructuralFeatures().push_back(
            m_TargetPort__rxLatency);
    m_TargetPort__txLatency = new ::ecore::EAttribute();
    m_TargetPort__txLatency->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETPORT__TXLATENCY);
    m_TargetPortEClass->getEStructuralFeatures().push_back(
            m_TargetPort__txLatency);
    m_TargetPort__speed = new ::ecore::EAttribute();
    m_TargetPort__speed->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETPORT__SPEED);
    m_TargetPortEClass->getEStructuralFeatures().push_back(m_TargetPort__speed);
    m_TargetPort__portType = new ::ecore::EAttribute();
    m_TargetPort__portType->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTTYPE);
    m_TargetPortEClass->getEStructuralFeatures().push_back(
            m_TargetPort__portType);
    m_TargetPort__portSerialNumber = new ::ecore::EAttribute();
    m_TargetPort__portSerialNumber->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTSERIALNUMBER);
    m_TargetPortEClass->getEStructuralFeatures().push_back(
            m_TargetPort__portSerialNumber);

    // AntiMasquerading
    m_AntiMasqueradingEClass = new ::ecore::EClass();
    m_AntiMasqueradingEClass->setClassifierID(ANTIMASQUERADING);
    m_AntiMasqueradingEClass->setEPackage(this);
    getEClassifiers().push_back(m_AntiMasqueradingEClass);
    m_AntiMasquerading__macAddress = new ::ecore::EAttribute();
    m_AntiMasquerading__macAddress->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::ANTIMASQUERADING__MACADDRESS);
    m_AntiMasqueradingEClass->getEStructuralFeatures().push_back(
            m_AntiMasquerading__macAddress);
    m_AntiMasquerading__refPort = new ::ecore::EReference();
    m_AntiMasquerading__refPort->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::ANTIMASQUERADING__REFPORT);
    m_AntiMasqueradingEClass->getEStructuralFeatures().push_back(
            m_AntiMasquerading__refPort);
    m_AntiMasquerading__refVirtualLink = new ::ecore::EReference();
    m_AntiMasquerading__refVirtualLink->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::ANTIMASQUERADING__REFVIRTUALLINK);
    m_AntiMasqueradingEClass->getEStructuralFeatures().push_back(
            m_AntiMasquerading__refVirtualLink);

    // PortInfos
    m_PortInfosEClass = new ::ecore::EClass();
    m_PortInfosEClass->setClassifierID(PORTINFOS);
    m_PortInfosEClass->setEPackage(this);
    getEClassifiers().push_back(m_PortInfosEClass);

    // TTTechProtocolLayerDevice
    m_TTTechProtocolLayerDeviceEClass = new ::ecore::EClass();
    m_TTTechProtocolLayerDeviceEClass->setClassifierID(
            TTTECHPROTOCOLLAYERDEVICE);
    m_TTTechProtocolLayerDeviceEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTTechProtocolLayerDeviceEClass);

    // GeneralTargetDevice
    m_GeneralTargetDeviceEClass = new ::ecore::EClass();
    m_GeneralTargetDeviceEClass->setClassifierID(GENERALTARGETDEVICE);
    m_GeneralTargetDeviceEClass->setEPackage(this);
    getEClassifiers().push_back(m_GeneralTargetDeviceEClass);
    m_GeneralTargetDevice__source = new ::ecore::EAttribute();
    m_GeneralTargetDevice__source->setFeatureID(
            ::Device_Targets::Device_TargetsPackage::GENERALTARGETDEVICE__SOURCE);
    m_GeneralTargetDeviceEClass->getEStructuralFeatures().push_back(
            m_GeneralTargetDevice__source);

    // Create enums

    m_AddressTypeEnumEEnum = new ::ecore::EEnum();
    m_AddressTypeEnumEEnum->setClassifierID(ADDRESSTYPEENUM);
    m_AddressTypeEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_AddressTypeEnumEEnum);

    m_DiagnosisScheduleModeEnumEEnum = new ::ecore::EEnum();
    m_DiagnosisScheduleModeEnumEEnum->setClassifierID(DIAGNOSISSCHEDULEMODEENUM);
    m_DiagnosisScheduleModeEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_DiagnosisScheduleModeEnumEEnum);

    m_PortTypeTypeEEnum = new ::ecore::EEnum();
    m_PortTypeTypeEEnum->setClassifierID(PORTTYPETYPE);
    m_PortTypeTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_PortTypeTypeEEnum);

    // Create data types


    // Initialize package
    setName("Device_Targets");
    setNsPrefix("ttt");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/Device_Targets_V1");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_ManagementInterfaceEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_MacAcceptanceEntryEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_AccessControlEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_TargetDevicesEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_TargetDeviceEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_TTTechIpTargetDeviceEClass->getESuperTypes().push_back(
            m_TargetDeviceEClass);
    m_DiagnosticEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_DiagnosisScheduleEntryEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_TargetPortsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_TargetPortEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());
    m_AntiMasqueradingEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_PortInfosEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_TTTechProtocolLayerDeviceEClass->getESuperTypes().push_back(
            m_TargetDeviceEClass);
    m_GeneralTargetDeviceEClass->getESuperTypes().push_back(
            m_TargetDeviceEClass);

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // ManagementInterface
    m_ManagementInterfaceEClass->setName("ManagementInterface");
    m_ManagementInterfaceEClass->setAbstract(false);
    m_ManagementInterfaceEClass->setInterface(false);
    m_ManagementInterface__configurationVersion->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_ManagementInterface__configurationVersion->setName("configurationVersion");
    m_ManagementInterface__configurationVersion->setDefaultValueLiteral("10");
    m_ManagementInterface__configurationVersion->setLowerBound(0);
    m_ManagementInterface__configurationVersion->setUpperBound(1);
    m_ManagementInterface__configurationVersion->setTransient(false);
    m_ManagementInterface__configurationVersion->setVolatile(false);
    m_ManagementInterface__configurationVersion->setChangeable(true);
    m_ManagementInterface__configurationVersion->setUnsettable(false);
    m_ManagementInterface__configurationVersion->setID(false);
    m_ManagementInterface__configurationVersion->setUnique(true);
    m_ManagementInterface__configurationVersion->setDerived(false);
    m_ManagementInterface__configurationVersion->setOrdered(true);
    m_ManagementInterface__speed->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getSpeedEnum());
    m_ManagementInterface__speed->setName("speed");
    m_ManagementInterface__speed->setDefaultValueLiteral("500Mbps");
    m_ManagementInterface__speed->setLowerBound(0);
    m_ManagementInterface__speed->setUpperBound(1);
    m_ManagementInterface__speed->setTransient(false);
    m_ManagementInterface__speed->setVolatile(false);
    m_ManagementInterface__speed->setChangeable(true);
    m_ManagementInterface__speed->setUnsettable(false);
    m_ManagementInterface__speed->setID(false);
    m_ManagementInterface__speed->setUnique(true);
    m_ManagementInterface__speed->setDerived(false);
    m_ManagementInterface__speed->setOrdered(true);
    m_ManagementInterface__unlockWrTimeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_ManagementInterface__unlockWrTimeout->setName("unlockWrTimeout");
    m_ManagementInterface__unlockWrTimeout->setDefaultValueLiteral("0s");
    m_ManagementInterface__unlockWrTimeout->setLowerBound(0);
    m_ManagementInterface__unlockWrTimeout->setUpperBound(1);
    m_ManagementInterface__unlockWrTimeout->setTransient(false);
    m_ManagementInterface__unlockWrTimeout->setVolatile(false);
    m_ManagementInterface__unlockWrTimeout->setChangeable(true);
    m_ManagementInterface__unlockWrTimeout->setUnsettable(false);
    m_ManagementInterface__unlockWrTimeout->setID(false);
    m_ManagementInterface__unlockWrTimeout->setUnique(true);
    m_ManagementInterface__unlockWrTimeout->setDerived(false);
    m_ManagementInterface__unlockWrTimeout->setOrdered(true);
    m_ManagementInterface__resetTimeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_ManagementInterface__resetTimeout->setName("resetTimeout");
    m_ManagementInterface__resetTimeout->setDefaultValueLiteral("0s");
    m_ManagementInterface__resetTimeout->setLowerBound(0);
    m_ManagementInterface__resetTimeout->setUpperBound(1);
    m_ManagementInterface__resetTimeout->setTransient(false);
    m_ManagementInterface__resetTimeout->setVolatile(false);
    m_ManagementInterface__resetTimeout->setChangeable(true);
    m_ManagementInterface__resetTimeout->setUnsettable(false);
    m_ManagementInterface__resetTimeout->setID(false);
    m_ManagementInterface__resetTimeout->setUnique(true);
    m_ManagementInterface__resetTimeout->setDerived(false);
    m_ManagementInterface__resetTimeout->setOrdered(true);
    m_ManagementInterface__unlockDestAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_ManagementInterface__unlockDestAddress->setName("unlockDestAddress");
    m_ManagementInterface__unlockDestAddress->setDefaultValueLiteral(
            "00:00:00:00:00:00");
    m_ManagementInterface__unlockDestAddress->setLowerBound(0);
    m_ManagementInterface__unlockDestAddress->setUpperBound(1);
    m_ManagementInterface__unlockDestAddress->setTransient(false);
    m_ManagementInterface__unlockDestAddress->setVolatile(false);
    m_ManagementInterface__unlockDestAddress->setChangeable(true);
    m_ManagementInterface__unlockDestAddress->setUnsettable(false);
    m_ManagementInterface__unlockDestAddress->setID(false);
    m_ManagementInterface__unlockDestAddress->setUnique(true);
    m_ManagementInterface__unlockDestAddress->setDerived(false);
    m_ManagementInterface__unlockDestAddress->setOrdered(true);
    m_ManagementInterface__schedDiagDestAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_ManagementInterface__schedDiagDestAddress->setName("schedDiagDestAddress");
    m_ManagementInterface__schedDiagDestAddress->setDefaultValueLiteral(
            "00:00:00:00:00:00");
    m_ManagementInterface__schedDiagDestAddress->setLowerBound(0);
    m_ManagementInterface__schedDiagDestAddress->setUpperBound(1);
    m_ManagementInterface__schedDiagDestAddress->setTransient(false);
    m_ManagementInterface__schedDiagDestAddress->setVolatile(false);
    m_ManagementInterface__schedDiagDestAddress->setChangeable(true);
    m_ManagementInterface__schedDiagDestAddress->setUnsettable(false);
    m_ManagementInterface__schedDiagDestAddress->setID(false);
    m_ManagementInterface__schedDiagDestAddress->setUnique(true);
    m_ManagementInterface__schedDiagDestAddress->setDerived(false);
    m_ManagementInterface__schedDiagDestAddress->setOrdered(true);
    m_ManagementInterface__sourceAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_ManagementInterface__sourceAddress->setName("sourceAddress");
    m_ManagementInterface__sourceAddress->setDefaultValueLiteral(
            "00:00:00:00:00:00");
    m_ManagementInterface__sourceAddress->setLowerBound(0);
    m_ManagementInterface__sourceAddress->setUpperBound(1);
    m_ManagementInterface__sourceAddress->setTransient(false);
    m_ManagementInterface__sourceAddress->setVolatile(false);
    m_ManagementInterface__sourceAddress->setChangeable(true);
    m_ManagementInterface__sourceAddress->setUnsettable(false);
    m_ManagementInterface__sourceAddress->setID(false);
    m_ManagementInterface__sourceAddress->setUnique(true);
    m_ManagementInterface__sourceAddress->setDerived(false);
    m_ManagementInterface__sourceAddress->setOrdered(true);
    m_ManagementInterface__expectedUnlocks->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEByte());
    m_ManagementInterface__expectedUnlocks->setName("expectedUnlocks");
    m_ManagementInterface__expectedUnlocks->setDefaultValueLiteral("4");
    m_ManagementInterface__expectedUnlocks->setLowerBound(0);
    m_ManagementInterface__expectedUnlocks->setUpperBound(1);
    m_ManagementInterface__expectedUnlocks->setTransient(false);
    m_ManagementInterface__expectedUnlocks->setVolatile(false);
    m_ManagementInterface__expectedUnlocks->setChangeable(true);
    m_ManagementInterface__expectedUnlocks->setUnsettable(false);
    m_ManagementInterface__expectedUnlocks->setID(false);
    m_ManagementInterface__expectedUnlocks->setUnique(true);
    m_ManagementInterface__expectedUnlocks->setDerived(false);
    m_ManagementInterface__expectedUnlocks->setOrdered(true);
    m_ManagementInterface__expectedResets->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEByte());
    m_ManagementInterface__expectedResets->setName("expectedResets");
    m_ManagementInterface__expectedResets->setDefaultValueLiteral("4");
    m_ManagementInterface__expectedResets->setLowerBound(0);
    m_ManagementInterface__expectedResets->setUpperBound(1);
    m_ManagementInterface__expectedResets->setTransient(false);
    m_ManagementInterface__expectedResets->setVolatile(false);
    m_ManagementInterface__expectedResets->setChangeable(true);
    m_ManagementInterface__expectedResets->setUnsettable(false);
    m_ManagementInterface__expectedResets->setID(false);
    m_ManagementInterface__expectedResets->setUnique(true);
    m_ManagementInterface__expectedResets->setDerived(false);
    m_ManagementInterface__expectedResets->setOrdered(true);
    m_ManagementInterface__diagnosisScheduleMode->setEType(
            m_DiagnosisScheduleModeEnumEEnum);
    m_ManagementInterface__diagnosisScheduleMode->setName(
            "diagnosisScheduleMode");
    m_ManagementInterface__diagnosisScheduleMode->setDefaultValueLiteral(
            "disable");
    m_ManagementInterface__diagnosisScheduleMode->setLowerBound(0);
    m_ManagementInterface__diagnosisScheduleMode->setUpperBound(1);
    m_ManagementInterface__diagnosisScheduleMode->setTransient(false);
    m_ManagementInterface__diagnosisScheduleMode->setVolatile(false);
    m_ManagementInterface__diagnosisScheduleMode->setChangeable(true);
    m_ManagementInterface__diagnosisScheduleMode->setUnsettable(false);
    m_ManagementInterface__diagnosisScheduleMode->setID(false);
    m_ManagementInterface__diagnosisScheduleMode->setUnique(true);
    m_ManagementInterface__diagnosisScheduleMode->setDerived(false);
    m_ManagementInterface__diagnosisScheduleMode->setOrdered(true);
    m_ManagementInterface__apbTimeout->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_ManagementInterface__apbTimeout->setName("apbTimeout");
    m_ManagementInterface__apbTimeout->setDefaultValueLiteral("0s");
    m_ManagementInterface__apbTimeout->setLowerBound(0);
    m_ManagementInterface__apbTimeout->setUpperBound(1);
    m_ManagementInterface__apbTimeout->setTransient(false);
    m_ManagementInterface__apbTimeout->setVolatile(false);
    m_ManagementInterface__apbTimeout->setChangeable(true);
    m_ManagementInterface__apbTimeout->setUnsettable(false);
    m_ManagementInterface__apbTimeout->setID(false);
    m_ManagementInterface__apbTimeout->setUnique(true);
    m_ManagementInterface__apbTimeout->setDerived(false);
    m_ManagementInterface__apbTimeout->setOrdered(true);
    m_ManagementInterface__macAcceptanceEntry->setEType(
            m_MacAcceptanceEntryEClass);
    m_ManagementInterface__macAcceptanceEntry->setName("macAcceptanceEntry");
    m_ManagementInterface__macAcceptanceEntry->setDefaultValueLiteral("");
    m_ManagementInterface__macAcceptanceEntry->setLowerBound(0);
    m_ManagementInterface__macAcceptanceEntry->setUpperBound(-1);
    m_ManagementInterface__macAcceptanceEntry->setTransient(false);
    m_ManagementInterface__macAcceptanceEntry->setVolatile(false);
    m_ManagementInterface__macAcceptanceEntry->setChangeable(true);
    m_ManagementInterface__macAcceptanceEntry->setContainment(true);
    m_ManagementInterface__macAcceptanceEntry->setResolveProxies(true);
    m_ManagementInterface__macAcceptanceEntry->setUnique(true);
    m_ManagementInterface__macAcceptanceEntry->setDerived(false);
    m_ManagementInterface__macAcceptanceEntry->setOrdered(true);
    // MacAcceptanceEntry
    m_MacAcceptanceEntryEClass->setName("MacAcceptanceEntry");
    m_MacAcceptanceEntryEClass->setAbstract(false);
    m_MacAcceptanceEntryEClass->setInterface(false);
    m_MacAcceptanceEntry__acceptanceMacAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_MacAcceptanceEntry__acceptanceMacAddress->setName("acceptanceMacAddress");
    m_MacAcceptanceEntry__acceptanceMacAddress->setDefaultValueLiteral("");
    m_MacAcceptanceEntry__acceptanceMacAddress->setLowerBound(1);
    m_MacAcceptanceEntry__acceptanceMacAddress->setUpperBound(1);
    m_MacAcceptanceEntry__acceptanceMacAddress->setTransient(false);
    m_MacAcceptanceEntry__acceptanceMacAddress->setVolatile(false);
    m_MacAcceptanceEntry__acceptanceMacAddress->setChangeable(true);
    m_MacAcceptanceEntry__acceptanceMacAddress->setUnsettable(false);
    m_MacAcceptanceEntry__acceptanceMacAddress->setID(false);
    m_MacAcceptanceEntry__acceptanceMacAddress->setUnique(true);
    m_MacAcceptanceEntry__acceptanceMacAddress->setDerived(false);
    m_MacAcceptanceEntry__acceptanceMacAddress->setOrdered(true);
    m_MacAcceptanceEntry__addressType->setEType(m_AddressTypeEnumEEnum);
    m_MacAcceptanceEntry__addressType->setName("addressType");
    m_MacAcceptanceEntry__addressType->setDefaultValueLiteral("");
    m_MacAcceptanceEntry__addressType->setLowerBound(0);
    m_MacAcceptanceEntry__addressType->setUpperBound(1);
    m_MacAcceptanceEntry__addressType->setTransient(false);
    m_MacAcceptanceEntry__addressType->setVolatile(false);
    m_MacAcceptanceEntry__addressType->setChangeable(true);
    m_MacAcceptanceEntry__addressType->setUnsettable(false);
    m_MacAcceptanceEntry__addressType->setID(false);
    m_MacAcceptanceEntry__addressType->setUnique(true);
    m_MacAcceptanceEntry__addressType->setDerived(false);
    m_MacAcceptanceEntry__addressType->setOrdered(true);
    m_MacAcceptanceEntry__unlockEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_MacAcceptanceEntry__unlockEnabled->setName("unlockEnabled");
    m_MacAcceptanceEntry__unlockEnabled->setDefaultValueLiteral("");
    m_MacAcceptanceEntry__unlockEnabled->setLowerBound(1);
    m_MacAcceptanceEntry__unlockEnabled->setUpperBound(1);
    m_MacAcceptanceEntry__unlockEnabled->setTransient(false);
    m_MacAcceptanceEntry__unlockEnabled->setVolatile(false);
    m_MacAcceptanceEntry__unlockEnabled->setChangeable(true);
    m_MacAcceptanceEntry__unlockEnabled->setUnsettable(false);
    m_MacAcceptanceEntry__unlockEnabled->setID(false);
    m_MacAcceptanceEntry__unlockEnabled->setUnique(true);
    m_MacAcceptanceEntry__unlockEnabled->setDerived(false);
    m_MacAcceptanceEntry__unlockEnabled->setOrdered(true);
    m_MacAcceptanceEntry__resetEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_MacAcceptanceEntry__resetEnabled->setName("resetEnabled");
    m_MacAcceptanceEntry__resetEnabled->setDefaultValueLiteral("");
    m_MacAcceptanceEntry__resetEnabled->setLowerBound(1);
    m_MacAcceptanceEntry__resetEnabled->setUpperBound(1);
    m_MacAcceptanceEntry__resetEnabled->setTransient(false);
    m_MacAcceptanceEntry__resetEnabled->setVolatile(false);
    m_MacAcceptanceEntry__resetEnabled->setChangeable(true);
    m_MacAcceptanceEntry__resetEnabled->setUnsettable(false);
    m_MacAcceptanceEntry__resetEnabled->setID(false);
    m_MacAcceptanceEntry__resetEnabled->setUnique(true);
    m_MacAcceptanceEntry__resetEnabled->setDerived(false);
    m_MacAcceptanceEntry__resetEnabled->setOrdered(true);
    m_MacAcceptanceEntry__responseDestMacAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_MacAcceptanceEntry__responseDestMacAddress->setName(
            "responseDestMacAddress");
    m_MacAcceptanceEntry__responseDestMacAddress->setDefaultValueLiteral("");
    m_MacAcceptanceEntry__responseDestMacAddress->setLowerBound(1);
    m_MacAcceptanceEntry__responseDestMacAddress->setUpperBound(1);
    m_MacAcceptanceEntry__responseDestMacAddress->setTransient(false);
    m_MacAcceptanceEntry__responseDestMacAddress->setVolatile(false);
    m_MacAcceptanceEntry__responseDestMacAddress->setChangeable(true);
    m_MacAcceptanceEntry__responseDestMacAddress->setUnsettable(false);
    m_MacAcceptanceEntry__responseDestMacAddress->setID(false);
    m_MacAcceptanceEntry__responseDestMacAddress->setUnique(true);
    m_MacAcceptanceEntry__responseDestMacAddress->setDerived(false);
    m_MacAcceptanceEntry__responseDestMacAddress->setOrdered(true);
    m_MacAcceptanceEntry__accessControl->setEType(m_AccessControlEClass);
    m_MacAcceptanceEntry__accessControl->setName("accessControl");
    m_MacAcceptanceEntry__accessControl->setDefaultValueLiteral("");
    m_MacAcceptanceEntry__accessControl->setLowerBound(0);
    m_MacAcceptanceEntry__accessControl->setUpperBound(4);
    m_MacAcceptanceEntry__accessControl->setTransient(false);
    m_MacAcceptanceEntry__accessControl->setVolatile(false);
    m_MacAcceptanceEntry__accessControl->setChangeable(true);
    m_MacAcceptanceEntry__accessControl->setContainment(true);
    m_MacAcceptanceEntry__accessControl->setResolveProxies(true);
    m_MacAcceptanceEntry__accessControl->setUnique(true);
    m_MacAcceptanceEntry__accessControl->setDerived(false);
    m_MacAcceptanceEntry__accessControl->setOrdered(true);
    // AccessControl
    m_AccessControlEClass->setName("AccessControl");
    m_AccessControlEClass->setAbstract(false);
    m_AccessControlEClass->setInterface(false);
    m_AccessControl__page->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_AccessControl__page->setName("page");
    m_AccessControl__page->setDefaultValueLiteral("0");
    m_AccessControl__page->setLowerBound(1);
    m_AccessControl__page->setUpperBound(1);
    m_AccessControl__page->setTransient(false);
    m_AccessControl__page->setVolatile(false);
    m_AccessControl__page->setChangeable(true);
    m_AccessControl__page->setUnsettable(false);
    m_AccessControl__page->setID(false);
    m_AccessControl__page->setUnique(true);
    m_AccessControl__page->setDerived(false);
    m_AccessControl__page->setOrdered(true);
    m_AccessControl__writeEnable->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_AccessControl__writeEnable->setName("writeEnable");
    m_AccessControl__writeEnable->setDefaultValueLiteral("true");
    m_AccessControl__writeEnable->setLowerBound(0);
    m_AccessControl__writeEnable->setUpperBound(1);
    m_AccessControl__writeEnable->setTransient(false);
    m_AccessControl__writeEnable->setVolatile(false);
    m_AccessControl__writeEnable->setChangeable(true);
    m_AccessControl__writeEnable->setUnsettable(false);
    m_AccessControl__writeEnable->setID(false);
    m_AccessControl__writeEnable->setUnique(true);
    m_AccessControl__writeEnable->setDerived(false);
    m_AccessControl__writeEnable->setOrdered(true);
    // TargetDevices
    m_TargetDevicesEClass->setName("TargetDevices");
    m_TargetDevicesEClass->setAbstract(false);
    m_TargetDevicesEClass->setInterface(false);
    m_TargetDevices__targetDevice->setEType(m_TargetDeviceEClass);
    m_TargetDevices__targetDevice->setName("targetDevice");
    m_TargetDevices__targetDevice->setDefaultValueLiteral("");
    m_TargetDevices__targetDevice->setLowerBound(0);
    m_TargetDevices__targetDevice->setUpperBound(-1);
    m_TargetDevices__targetDevice->setTransient(false);
    m_TargetDevices__targetDevice->setVolatile(false);
    m_TargetDevices__targetDevice->setChangeable(true);
    m_TargetDevices__targetDevice->setContainment(true);
    m_TargetDevices__targetDevice->setResolveProxies(true);
    m_TargetDevices__targetDevice->setUnique(true);
    m_TargetDevices__targetDevice->setDerived(false);
    m_TargetDevices__targetDevice->setOrdered(true);
    m_TargetDevices__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_TargetDevices__metaInformation->setName("metaInformation");
    m_TargetDevices__metaInformation->setDefaultValueLiteral("");
    m_TargetDevices__metaInformation->setLowerBound(0);
    m_TargetDevices__metaInformation->setUpperBound(1);
    m_TargetDevices__metaInformation->setTransient(false);
    m_TargetDevices__metaInformation->setVolatile(false);
    m_TargetDevices__metaInformation->setChangeable(true);
    m_TargetDevices__metaInformation->setContainment(true);
    m_TargetDevices__metaInformation->setResolveProxies(true);
    m_TargetDevices__metaInformation->setUnique(true);
    m_TargetDevices__metaInformation->setDerived(false);
    m_TargetDevices__metaInformation->setOrdered(true);
    // TargetDevice
    m_TargetDeviceEClass->setName("TargetDevice");
    m_TargetDeviceEClass->setAbstract(true);
    m_TargetDeviceEClass->setInterface(false);
    m_TargetDevice__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_TargetDevice__description->setName("description");
    m_TargetDevice__description->setDefaultValueLiteral("");
    m_TargetDevice__description->setLowerBound(1);
    m_TargetDevice__description->setUpperBound(1);
    m_TargetDevice__description->setTransient(false);
    m_TargetDevice__description->setVolatile(false);
    m_TargetDevice__description->setChangeable(true);
    m_TargetDevice__description->setUnsettable(false);
    m_TargetDevice__description->setID(false);
    m_TargetDevice__description->setUnique(true);
    m_TargetDevice__description->setDerived(false);
    m_TargetDevice__description->setOrdered(true);
    m_TargetDevice__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_TargetDevice__metaInformation->setName("metaInformation");
    m_TargetDevice__metaInformation->setDefaultValueLiteral("");
    m_TargetDevice__metaInformation->setLowerBound(0);
    m_TargetDevice__metaInformation->setUpperBound(1);
    m_TargetDevice__metaInformation->setTransient(false);
    m_TargetDevice__metaInformation->setVolatile(false);
    m_TargetDevice__metaInformation->setChangeable(true);
    m_TargetDevice__metaInformation->setContainment(true);
    m_TargetDevice__metaInformation->setResolveProxies(true);
    m_TargetDevice__metaInformation->setUnique(true);
    m_TargetDevice__metaInformation->setDerived(false);
    m_TargetDevice__metaInformation->setOrdered(true);
    m_TargetDevice__refImplementation->setEType(
            dynamic_cast< ::IP_Configuration::IP_ConfigurationPackage* > (::IP_Configuration::IP_ConfigurationPackage::_instance())->getImplementation());
    m_TargetDevice__refImplementation->setName("refImplementation");
    m_TargetDevice__refImplementation->setDefaultValueLiteral("");
    m_TargetDevice__refImplementation->setLowerBound(1);
    m_TargetDevice__refImplementation->setUpperBound(1);
    m_TargetDevice__refImplementation->setTransient(false);
    m_TargetDevice__refImplementation->setVolatile(false);
    m_TargetDevice__refImplementation->setChangeable(true);
    m_TargetDevice__refImplementation->setContainment(false);
    m_TargetDevice__refImplementation->setResolveProxies(true);
    m_TargetDevice__refImplementation->setUnique(true);
    m_TargetDevice__refImplementation->setDerived(false);
    m_TargetDevice__refImplementation->setOrdered(true);
    m_TargetDevice__targetPorts->setEType(m_TargetPortsEClass);
    m_TargetDevice__targetPorts->setName("targetPorts");
    m_TargetDevice__targetPorts->setDefaultValueLiteral("");
    m_TargetDevice__targetPorts->setLowerBound(1);
    m_TargetDevice__targetPorts->setUpperBound(-1);
    m_TargetDevice__targetPorts->setTransient(false);
    m_TargetDevice__targetPorts->setVolatile(false);
    m_TargetDevice__targetPorts->setChangeable(true);
    m_TargetDevice__targetPorts->setContainment(true);
    m_TargetDevice__targetPorts->setResolveProxies(true);
    m_TargetDevice__targetPorts->setUnique(true);
    m_TargetDevice__targetPorts->setDerived(false);
    m_TargetDevice__targetPorts->setOrdered(true);
    m_TargetDevice__details->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEStringToStringMapEntry());
    m_TargetDevice__details->setName("details");
    m_TargetDevice__details->setDefaultValueLiteral("");
    m_TargetDevice__details->setLowerBound(0);
    m_TargetDevice__details->setUpperBound(-1);
    m_TargetDevice__details->setTransient(false);
    m_TargetDevice__details->setVolatile(false);
    m_TargetDevice__details->setChangeable(true);
    m_TargetDevice__details->setContainment(true);
    m_TargetDevice__details->setResolveProxies(true);
    m_TargetDevice__details->setUnique(true);
    m_TargetDevice__details->setDerived(false);
    m_TargetDevice__details->setOrdered(true);
    // TTTechIpTargetDevice
    m_TTTechIpTargetDeviceEClass->setName("TTTechIpTargetDevice");
    m_TTTechIpTargetDeviceEClass->setAbstract(false);
    m_TTTechIpTargetDeviceEClass->setInterface(false);
    m_TTTechIpTargetDevice__clockSpeed->setEType(
            dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage* > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getFrequencyType());
    m_TTTechIpTargetDevice__clockSpeed->setName("clockSpeed");
    m_TTTechIpTargetDevice__clockSpeed->setDefaultValueLiteral("");
    m_TTTechIpTargetDevice__clockSpeed->setLowerBound(1);
    m_TTTechIpTargetDevice__clockSpeed->setUpperBound(1);
    m_TTTechIpTargetDevice__clockSpeed->setTransient(false);
    m_TTTechIpTargetDevice__clockSpeed->setVolatile(false);
    m_TTTechIpTargetDevice__clockSpeed->setChangeable(true);
    m_TTTechIpTargetDevice__clockSpeed->setUnsettable(false);
    m_TTTechIpTargetDevice__clockSpeed->setID(false);
    m_TTTechIpTargetDevice__clockSpeed->setUnique(true);
    m_TTTechIpTargetDevice__clockSpeed->setDerived(false);
    m_TTTechIpTargetDevice__clockSpeed->setOrdered(true);
    m_TTTechIpTargetDevice__mediaControlEnabled->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_TTTechIpTargetDevice__mediaControlEnabled->setName("mediaControlEnabled");
    m_TTTechIpTargetDevice__mediaControlEnabled->setDefaultValueLiteral("false");
    m_TTTechIpTargetDevice__mediaControlEnabled->setLowerBound(1);
    m_TTTechIpTargetDevice__mediaControlEnabled->setUpperBound(1);
    m_TTTechIpTargetDevice__mediaControlEnabled->setTransient(false);
    m_TTTechIpTargetDevice__mediaControlEnabled->setVolatile(false);
    m_TTTechIpTargetDevice__mediaControlEnabled->setChangeable(true);
    m_TTTechIpTargetDevice__mediaControlEnabled->setUnsettable(false);
    m_TTTechIpTargetDevice__mediaControlEnabled->setID(false);
    m_TTTechIpTargetDevice__mediaControlEnabled->setUnique(true);
    m_TTTechIpTargetDevice__mediaControlEnabled->setDerived(false);
    m_TTTechIpTargetDevice__mediaControlEnabled->setOrdered(true);
    // Diagnostic
    m_DiagnosticEClass->setName("Diagnostic");
    m_DiagnosticEClass->setAbstract(false);
    m_DiagnosticEClass->setInterface(false);
    m_Diagnostic__diagnosisScheduleEntry->setEType(
            m_DiagnosisScheduleEntryEClass);
    m_Diagnostic__diagnosisScheduleEntry->setName("diagnosisScheduleEntry");
    m_Diagnostic__diagnosisScheduleEntry->setDefaultValueLiteral("");
    m_Diagnostic__diagnosisScheduleEntry->setLowerBound(0);
    m_Diagnostic__diagnosisScheduleEntry->setUpperBound(-1);
    m_Diagnostic__diagnosisScheduleEntry->setTransient(false);
    m_Diagnostic__diagnosisScheduleEntry->setVolatile(false);
    m_Diagnostic__diagnosisScheduleEntry->setChangeable(true);
    m_Diagnostic__diagnosisScheduleEntry->setContainment(true);
    m_Diagnostic__diagnosisScheduleEntry->setResolveProxies(true);
    m_Diagnostic__diagnosisScheduleEntry->setUnique(true);
    m_Diagnostic__diagnosisScheduleEntry->setDerived(false);
    m_Diagnostic__diagnosisScheduleEntry->setOrdered(true);
    // DiagnosisScheduleEntry
    m_DiagnosisScheduleEntryEClass->setName("DiagnosisScheduleEntry");
    m_DiagnosisScheduleEntryEClass->setAbstract(false);
    m_DiagnosisScheduleEntryEClass->setInterface(false);
    m_DiagnosisScheduleEntry__time->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_DiagnosisScheduleEntry__time->setName("time");
    m_DiagnosisScheduleEntry__time->setDefaultValueLiteral("");
    m_DiagnosisScheduleEntry__time->setLowerBound(1);
    m_DiagnosisScheduleEntry__time->setUpperBound(1);
    m_DiagnosisScheduleEntry__time->setTransient(false);
    m_DiagnosisScheduleEntry__time->setVolatile(false);
    m_DiagnosisScheduleEntry__time->setChangeable(true);
    m_DiagnosisScheduleEntry__time->setUnsettable(false);
    m_DiagnosisScheduleEntry__time->setID(false);
    m_DiagnosisScheduleEntry__time->setUnique(true);
    m_DiagnosisScheduleEntry__time->setDerived(false);
    m_DiagnosisScheduleEntry__time->setOrdered(true);
    m_DiagnosisScheduleEntry__itemAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getUniversalNumberType());
    m_DiagnosisScheduleEntry__itemAddress->setName("itemAddress");
    m_DiagnosisScheduleEntry__itemAddress->setDefaultValueLiteral("0x0000");
    m_DiagnosisScheduleEntry__itemAddress->setLowerBound(1);
    m_DiagnosisScheduleEntry__itemAddress->setUpperBound(1);
    m_DiagnosisScheduleEntry__itemAddress->setTransient(false);
    m_DiagnosisScheduleEntry__itemAddress->setVolatile(false);
    m_DiagnosisScheduleEntry__itemAddress->setChangeable(true);
    m_DiagnosisScheduleEntry__itemAddress->setUnsettable(false);
    m_DiagnosisScheduleEntry__itemAddress->setID(false);
    m_DiagnosisScheduleEntry__itemAddress->setUnique(true);
    m_DiagnosisScheduleEntry__itemAddress->setDerived(false);
    m_DiagnosisScheduleEntry__itemAddress->setOrdered(true);
    m_DiagnosisScheduleEntry__itemsNumber->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getUniversalNumberType());
    m_DiagnosisScheduleEntry__itemsNumber->setName("itemsNumber");
    m_DiagnosisScheduleEntry__itemsNumber->setDefaultValueLiteral("");
    m_DiagnosisScheduleEntry__itemsNumber->setLowerBound(1);
    m_DiagnosisScheduleEntry__itemsNumber->setUpperBound(1);
    m_DiagnosisScheduleEntry__itemsNumber->setTransient(false);
    m_DiagnosisScheduleEntry__itemsNumber->setVolatile(false);
    m_DiagnosisScheduleEntry__itemsNumber->setChangeable(true);
    m_DiagnosisScheduleEntry__itemsNumber->setUnsettable(false);
    m_DiagnosisScheduleEntry__itemsNumber->setID(false);
    m_DiagnosisScheduleEntry__itemsNumber->setUnique(true);
    m_DiagnosisScheduleEntry__itemsNumber->setDerived(false);
    m_DiagnosisScheduleEntry__itemsNumber->setOrdered(true);
    // TargetPorts
    m_TargetPortsEClass->setName("TargetPorts");
    m_TargetPortsEClass->setAbstract(false);
    m_TargetPortsEClass->setInterface(false);
    m_TargetPorts__targetPort->setEType(m_TargetPortEClass);
    m_TargetPorts__targetPort->setName("targetPort");
    m_TargetPorts__targetPort->setDefaultValueLiteral("");
    m_TargetPorts__targetPort->setLowerBound(0);
    m_TargetPorts__targetPort->setUpperBound(-1);
    m_TargetPorts__targetPort->setTransient(false);
    m_TargetPorts__targetPort->setVolatile(false);
    m_TargetPorts__targetPort->setChangeable(true);
    m_TargetPorts__targetPort->setContainment(true);
    m_TargetPorts__targetPort->setResolveProxies(true);
    m_TargetPorts__targetPort->setUnique(true);
    m_TargetPorts__targetPort->setDerived(false);
    m_TargetPorts__targetPort->setOrdered(true);
    // TargetPort
    m_TargetPortEClass->setName("TargetPort");
    m_TargetPortEClass->setAbstract(false);
    m_TargetPortEClass->setInterface(false);
    m_TargetPort__rxLatency->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_TargetPort__rxLatency->setName("rxLatency");
    m_TargetPort__rxLatency->setDefaultValueLiteral("0ns");
    m_TargetPort__rxLatency->setLowerBound(0);
    m_TargetPort__rxLatency->setUpperBound(1);
    m_TargetPort__rxLatency->setTransient(false);
    m_TargetPort__rxLatency->setVolatile(false);
    m_TargetPort__rxLatency->setChangeable(true);
    m_TargetPort__rxLatency->setUnsettable(false);
    m_TargetPort__rxLatency->setID(false);
    m_TargetPort__rxLatency->setUnique(true);
    m_TargetPort__rxLatency->setDerived(false);
    m_TargetPort__rxLatency->setOrdered(true);
    m_TargetPort__txLatency->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getTimeType());
    m_TargetPort__txLatency->setName("txLatency");
    m_TargetPort__txLatency->setDefaultValueLiteral("0ns");
    m_TargetPort__txLatency->setLowerBound(0);
    m_TargetPort__txLatency->setUpperBound(1);
    m_TargetPort__txLatency->setTransient(false);
    m_TargetPort__txLatency->setVolatile(false);
    m_TargetPort__txLatency->setChangeable(true);
    m_TargetPort__txLatency->setUnsettable(false);
    m_TargetPort__txLatency->setID(false);
    m_TargetPort__txLatency->setUnique(true);
    m_TargetPort__txLatency->setDerived(false);
    m_TargetPort__txLatency->setOrdered(true);
    m_TargetPort__speed->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getSpeedEnum());
    m_TargetPort__speed->setName("speed");
    m_TargetPort__speed->setDefaultValueLiteral("1000Mbps");
    m_TargetPort__speed->setLowerBound(0);
    m_TargetPort__speed->setUpperBound(1);
    m_TargetPort__speed->setTransient(false);
    m_TargetPort__speed->setVolatile(false);
    m_TargetPort__speed->setChangeable(true);
    m_TargetPort__speed->setUnsettable(false);
    m_TargetPort__speed->setID(false);
    m_TargetPort__speed->setUnique(true);
    m_TargetPort__speed->setDerived(false);
    m_TargetPort__speed->setOrdered(true);
    m_TargetPort__portType->setEType(m_PortTypeTypeEEnum);
    m_TargetPort__portType->setName("portType");
    m_TargetPort__portType->setDefaultValueLiteral("PHYS");
    m_TargetPort__portType->setLowerBound(1);
    m_TargetPort__portType->setUpperBound(1);
    m_TargetPort__portType->setTransient(false);
    m_TargetPort__portType->setVolatile(false);
    m_TargetPort__portType->setChangeable(true);
    m_TargetPort__portType->setUnsettable(false);
    m_TargetPort__portType->setID(false);
    m_TargetPort__portType->setUnique(true);
    m_TargetPort__portType->setDerived(false);
    m_TargetPort__portType->setOrdered(true);
    m_TargetPort__portSerialNumber->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_TargetPort__portSerialNumber->setName("portSerialNumber");
    m_TargetPort__portSerialNumber->setDefaultValueLiteral("0");
    m_TargetPort__portSerialNumber->setLowerBound(1);
    m_TargetPort__portSerialNumber->setUpperBound(1);
    m_TargetPort__portSerialNumber->setTransient(false);
    m_TargetPort__portSerialNumber->setVolatile(false);
    m_TargetPort__portSerialNumber->setChangeable(true);
    m_TargetPort__portSerialNumber->setUnsettable(false);
    m_TargetPort__portSerialNumber->setID(false);
    m_TargetPort__portSerialNumber->setUnique(true);
    m_TargetPort__portSerialNumber->setDerived(false);
    m_TargetPort__portSerialNumber->setOrdered(true);
    // AntiMasquerading
    m_AntiMasqueradingEClass->setName("AntiMasquerading");
    m_AntiMasqueradingEClass->setAbstract(false);
    m_AntiMasqueradingEClass->setInterface(false);
    m_AntiMasquerading__macAddress->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMacAddressType());
    m_AntiMasquerading__macAddress->setName("macAddress");
    m_AntiMasquerading__macAddress->setDefaultValueLiteral("");
    m_AntiMasquerading__macAddress->setLowerBound(1);
    m_AntiMasquerading__macAddress->setUpperBound(1);
    m_AntiMasquerading__macAddress->setTransient(false);
    m_AntiMasquerading__macAddress->setVolatile(false);
    m_AntiMasquerading__macAddress->setChangeable(true);
    m_AntiMasquerading__macAddress->setUnsettable(false);
    m_AntiMasquerading__macAddress->setID(false);
    m_AntiMasquerading__macAddress->setUnique(true);
    m_AntiMasquerading__macAddress->setDerived(false);
    m_AntiMasquerading__macAddress->setOrdered(true);
    m_AntiMasquerading__refPort->setEType(
            dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage* > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getSwPortMapping());
    m_AntiMasquerading__refPort->setName("refPort");
    m_AntiMasquerading__refPort->setDefaultValueLiteral("");
    m_AntiMasquerading__refPort->setLowerBound(0);
    m_AntiMasquerading__refPort->setUpperBound(-1);
    m_AntiMasquerading__refPort->setTransient(false);
    m_AntiMasquerading__refPort->setVolatile(false);
    m_AntiMasquerading__refPort->setChangeable(true);
    m_AntiMasquerading__refPort->setContainment(false);
    m_AntiMasquerading__refPort->setResolveProxies(true);
    m_AntiMasquerading__refPort->setUnique(true);
    m_AntiMasquerading__refPort->setDerived(false);
    m_AntiMasquerading__refPort->setOrdered(true);
    m_AntiMasquerading__refVirtualLink->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getVirtualLink());
    m_AntiMasquerading__refVirtualLink->setName("refVirtualLink");
    m_AntiMasquerading__refVirtualLink->setDefaultValueLiteral("");
    m_AntiMasquerading__refVirtualLink->setLowerBound(1);
    m_AntiMasquerading__refVirtualLink->setUpperBound(1);
    m_AntiMasquerading__refVirtualLink->setTransient(false);
    m_AntiMasquerading__refVirtualLink->setVolatile(false);
    m_AntiMasquerading__refVirtualLink->setChangeable(true);
    m_AntiMasquerading__refVirtualLink->setContainment(false);
    m_AntiMasquerading__refVirtualLink->setResolveProxies(true);
    m_AntiMasquerading__refVirtualLink->setUnique(true);
    m_AntiMasquerading__refVirtualLink->setDerived(false);
    m_AntiMasquerading__refVirtualLink->setOrdered(true);
    // PortInfos
    m_PortInfosEClass->setName("PortInfos");
    m_PortInfosEClass->setAbstract(false);
    m_PortInfosEClass->setInterface(false);
    // TTTechProtocolLayerDevice
    m_TTTechProtocolLayerDeviceEClass->setName("TTTechProtocolLayerDevice");
    m_TTTechProtocolLayerDeviceEClass->setAbstract(false);
    m_TTTechProtocolLayerDeviceEClass->setInterface(false);
    // GeneralTargetDevice
    m_GeneralTargetDeviceEClass->setName("GeneralTargetDevice");
    m_GeneralTargetDeviceEClass->setAbstract(false);
    m_GeneralTargetDeviceEClass->setInterface(false);
    m_GeneralTargetDevice__source->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_GeneralTargetDevice__source->setName("source");
    m_GeneralTargetDevice__source->setDefaultValueLiteral("");
    m_GeneralTargetDevice__source->setLowerBound(1);
    m_GeneralTargetDevice__source->setUpperBound(1);
    m_GeneralTargetDevice__source->setTransient(false);
    m_GeneralTargetDevice__source->setVolatile(false);
    m_GeneralTargetDevice__source->setChangeable(true);
    m_GeneralTargetDevice__source->setUnsettable(false);
    m_GeneralTargetDevice__source->setID(false);
    m_GeneralTargetDevice__source->setUnique(true);
    m_GeneralTargetDevice__source->setDerived(false);
    m_GeneralTargetDevice__source->setOrdered(true);

    // TODO: Initialize data types


    // addressTypeEnum
    m_AddressTypeEnumEEnum->setName("addressTypeEnum");
    m_AddressTypeEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // criticalTraffic
        _el->setName("criticalTraffic");
        _el->setValue(0);
        _el->setLiteral("criticalTraffic");
        _el->setEEnum(m_AddressTypeEnumEEnum);
        m_AddressTypeEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // nonCriticalTraffic
        _el->setName("nonCriticalTraffic");
        _el->setValue(1);
        _el->setLiteral("nonCriticalTraffic");
        _el->setEEnum(m_AddressTypeEnumEEnum);
        m_AddressTypeEnumEEnum->getELiterals().push_back(_el);
    }

    // diagnosisScheduleModeEnum
    m_DiagnosisScheduleModeEnumEEnum->setName("diagnosisScheduleModeEnum");
    m_DiagnosisScheduleModeEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // disable
        _el->setName("disable");
        _el->setValue(0);
        _el->setLiteral("disable");
        _el->setEEnum(m_DiagnosisScheduleModeEnumEEnum);
        m_DiagnosisScheduleModeEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // enable
        _el->setName("enable");
        _el->setValue(1);
        _el->setLiteral("enable");
        _el->setEEnum(m_DiagnosisScheduleModeEnumEEnum);
        m_DiagnosisScheduleModeEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // noSyncEnable
        _el->setName("noSyncEnable");
        _el->setValue(2);
        _el->setLiteral("noSyncEnable");
        _el->setEEnum(m_DiagnosisScheduleModeEnumEEnum);
        m_DiagnosisScheduleModeEnumEEnum->getELiterals().push_back(_el);
    }

    // PortTypeType
    m_PortTypeTypeEEnum->setName("PortTypeType");
    m_PortTypeTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // PHYS
        _el->setName("PHYS");
        _el->setValue(0);
        _el->setLiteral("PHYS");
        _el->setEEnum(m_PortTypeTypeEEnum);
        m_PortTypeTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // HOST
        _el->setName("HOST");
        _el->setValue(1);
        _el->setLiteral("HOST");
        _el->setEEnum(m_PortTypeTypeEEnum);
        m_PortTypeTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // MGMT
        _el->setName("MGMT");
        _el->setValue(2);
        _el->setLiteral("MGMT");
        _el->setEEnum(m_PortTypeTypeEEnum);
        m_PortTypeTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // SYNC
        _el->setName("SYNC");
        _el->setValue(3);
        _el->setLiteral("SYNC");
        _el->setEEnum(m_PortTypeTypeEEnum);
        m_PortTypeTypeEEnum->getELiterals().push_back(_el);
    }

    _initialize();
}

::ecore::EClass_ptr Device_TargetsPackage::getManagementInterface()
{
    return m_ManagementInterfaceEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getMacAcceptanceEntry()
{
    return m_MacAcceptanceEntryEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getAccessControl()
{
    return m_AccessControlEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getTargetDevices()
{
    return m_TargetDevicesEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getTargetDevice()
{
    return m_TargetDeviceEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getTTTechIpTargetDevice()
{
    return m_TTTechIpTargetDeviceEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getDiagnostic()
{
    return m_DiagnosticEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getDiagnosisScheduleEntry()
{
    return m_DiagnosisScheduleEntryEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getTargetPorts()
{
    return m_TargetPortsEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getTargetPort()
{
    return m_TargetPortEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getAntiMasquerading()
{
    return m_AntiMasqueradingEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getPortInfos()
{
    return m_PortInfosEClass;
}
::ecore::EEnum_ptr Device_TargetsPackage::getAddressTypeEnum()
{
    return m_AddressTypeEnumEEnum;
}
::ecore::EEnum_ptr Device_TargetsPackage::getDiagnosisScheduleModeEnum()
{
    return m_DiagnosisScheduleModeEnumEEnum;
}
::ecore::EEnum_ptr Device_TargetsPackage::getPortTypeType()
{
    return m_PortTypeTypeEEnum;
}
::ecore::EClass_ptr Device_TargetsPackage::getTTTechProtocolLayerDevice()
{
    return m_TTTechProtocolLayerDeviceEClass;
}
::ecore::EClass_ptr Device_TargetsPackage::getGeneralTargetDevice()
{
    return m_GeneralTargetDeviceEClass;
}

::ecore::EReference_ptr Device_TargetsPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__configurationVersion()
{
    return m_ManagementInterface__configurationVersion;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__speed()
{
    return m_ManagementInterface__speed;
}
::ecore::EReference_ptr Device_TargetsPackage::getManagementInterface__macAcceptanceEntry()
{
    return m_ManagementInterface__macAcceptanceEntry;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__unlockWrTimeout()
{
    return m_ManagementInterface__unlockWrTimeout;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__resetTimeout()
{
    return m_ManagementInterface__resetTimeout;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__unlockDestAddress()
{
    return m_ManagementInterface__unlockDestAddress;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__schedDiagDestAddress()
{
    return m_ManagementInterface__schedDiagDestAddress;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__sourceAddress()
{
    return m_ManagementInterface__sourceAddress;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__expectedUnlocks()
{
    return m_ManagementInterface__expectedUnlocks;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__expectedResets()
{
    return m_ManagementInterface__expectedResets;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__diagnosisScheduleMode()
{
    return m_ManagementInterface__diagnosisScheduleMode;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getManagementInterface__apbTimeout()
{
    return m_ManagementInterface__apbTimeout;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getMacAcceptanceEntry__acceptanceMacAddress()
{
    return m_MacAcceptanceEntry__acceptanceMacAddress;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getMacAcceptanceEntry__addressType()
{
    return m_MacAcceptanceEntry__addressType;
}
::ecore::EReference_ptr Device_TargetsPackage::getMacAcceptanceEntry__accessControl()
{
    return m_MacAcceptanceEntry__accessControl;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getMacAcceptanceEntry__unlockEnabled()
{
    return m_MacAcceptanceEntry__unlockEnabled;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getMacAcceptanceEntry__resetEnabled()
{
    return m_MacAcceptanceEntry__resetEnabled;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getMacAcceptanceEntry__responseDestMacAddress()
{
    return m_MacAcceptanceEntry__responseDestMacAddress;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getAccessControl__page()
{
    return m_AccessControl__page;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getAccessControl__writeEnable()
{
    return m_AccessControl__writeEnable;
}
::ecore::EReference_ptr Device_TargetsPackage::getTargetDevices__targetDevice()
{
    return m_TargetDevices__targetDevice;
}
::ecore::EReference_ptr Device_TargetsPackage::getTargetDevices__metaInformation()
{
    return m_TargetDevices__metaInformation;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTargetDevice__description()
{
    return m_TargetDevice__description;
}
::ecore::EReference_ptr Device_TargetsPackage::getTargetDevice__metaInformation()
{
    return m_TargetDevice__metaInformation;
}
::ecore::EReference_ptr Device_TargetsPackage::getTargetDevice__refImplementation()
{
    return m_TargetDevice__refImplementation;
}
::ecore::EReference_ptr Device_TargetsPackage::getTargetDevice__targetPorts()
{
    return m_TargetDevice__targetPorts;
}
::ecore::EReference_ptr Device_TargetsPackage::getTargetDevice__details()
{
    return m_TargetDevice__details;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTTTechIpTargetDevice__clockSpeed()
{
    return m_TTTechIpTargetDevice__clockSpeed;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTTTechIpTargetDevice__mediaControlEnabled()
{
    return m_TTTechIpTargetDevice__mediaControlEnabled;
}
::ecore::EReference_ptr Device_TargetsPackage::getDiagnostic__diagnosisScheduleEntry()
{
    return m_Diagnostic__diagnosisScheduleEntry;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getDiagnosisScheduleEntry__time()
{
    return m_DiagnosisScheduleEntry__time;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getDiagnosisScheduleEntry__itemAddress()
{
    return m_DiagnosisScheduleEntry__itemAddress;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getDiagnosisScheduleEntry__itemsNumber()
{
    return m_DiagnosisScheduleEntry__itemsNumber;
}
::ecore::EReference_ptr Device_TargetsPackage::getTargetPorts__targetPort()
{
    return m_TargetPorts__targetPort;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTargetPort__rxLatency()
{
    return m_TargetPort__rxLatency;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTargetPort__txLatency()
{
    return m_TargetPort__txLatency;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTargetPort__speed()
{
    return m_TargetPort__speed;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTargetPort__portType()
{
    return m_TargetPort__portType;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getTargetPort__portSerialNumber()
{
    return m_TargetPort__portSerialNumber;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getAntiMasquerading__macAddress()
{
    return m_AntiMasquerading__macAddress;
}
::ecore::EReference_ptr Device_TargetsPackage::getAntiMasquerading__refPort()
{
    return m_AntiMasquerading__refPort;
}
::ecore::EReference_ptr Device_TargetsPackage::getAntiMasquerading__refVirtualLink()
{
    return m_AntiMasquerading__refVirtualLink;
}
::ecore::EAttribute_ptr Device_TargetsPackage::getGeneralTargetDevice__source()
{
    return m_GeneralTargetDevice__source;
}

