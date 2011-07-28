// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/Device_TargetsPackage.hpp
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

#ifndef _DEVICE_TARGETSPACKAGE_HPP
#define _DEVICE_TARGETSPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <Device_Targets_forward.hpp>

#include <System_Specification/System_SpecificationPackage.hpp>

namespace Device_Targets
{

    /*PROTECTED REGION ID(Device_Targets_SALT) ENABLED START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 3000
    /*PROTECTED REGION END*/

    class Device_TargetsPackage: public virtual ::ecore::EPackage
    {
    public:

        static Device_TargetsPackage_ptr _instance();

        // IDs for classifiers

        static const int ACCESSCONTROL = SALT + 0;

        static const int ADDRESSTYPEENUM = SALT + 1;

        static const int ANTIMASQUERADING = SALT + 2;

        static const int DIAGNOSISSCHEDULEENTRY = SALT + 3;

        static const int DIAGNOSISSCHEDULEMODEENUM = SALT + 4;

        static const int DIAGNOSTIC = SALT + 5;

        static const int GENERALTARGETDEVICE = SALT + 6;

        static const int MACACCEPTANCEENTRY = SALT + 7;

        static const int MANAGEMENTINTERFACE = SALT + 8;

        static const int PORTINFOS = SALT + 9;

        static const int PORTTYPETYPE = SALT + 10;

        static const int TARGETDEVICE = SALT + 11;

        static const int TARGETDEVICES = SALT + 12;

        static const int TARGETPORT = SALT + 13;

        static const int TARGETPORTS = SALT + 14;

        static const int TTTECHIPTARGETDEVICE = SALT + 15;

        static const int TTTECHPROTOCOLLAYERDEVICE = SALT + 16;

        static const int MANAGEMENTINTERFACE__CONFIGURATIONVERSION = SALT + 0;

        static const int MANAGEMENTINTERFACE__SPEED = SALT + 1;

        static const int MANAGEMENTINTERFACE__MACACCEPTANCEENTRY = SALT + 2;

        static const int MANAGEMENTINTERFACE__UNLOCKWRTIMEOUT = SALT + 3;

        static const int MANAGEMENTINTERFACE__RESETTIMEOUT = SALT + 4;

        static const int MANAGEMENTINTERFACE__UNLOCKDESTADDRESS = SALT + 5;

        static const int MANAGEMENTINTERFACE__SCHEDDIAGDESTADDRESS = SALT + 6;

        static const int MANAGEMENTINTERFACE__SOURCEADDRESS = SALT + 7;

        static const int MANAGEMENTINTERFACE__EXPECTEDUNLOCKS = SALT + 8;

        static const int MANAGEMENTINTERFACE__EXPECTEDRESETS = SALT + 9;

        static const int MANAGEMENTINTERFACE__DIAGNOSISSCHEDULEMODE = SALT + 10;

        static const int MANAGEMENTINTERFACE__APBTIMEOUT = SALT + 11;

        static const int MACACCEPTANCEENTRY__ACCEPTANCEMACADDRESS = SALT + 12;

        static const int MACACCEPTANCEENTRY__ADDRESSTYPE = SALT + 13;

        static const int MACACCEPTANCEENTRY__ACCESSCONTROL = SALT + 14;

        static const int MACACCEPTANCEENTRY__UNLOCKENABLED = SALT + 15;

        static const int MACACCEPTANCEENTRY__RESETENABLED = SALT + 16;

        static const int MACACCEPTANCEENTRY__RESPONSEDESTMACADDRESS = SALT + 17;

        static const int ACCESSCONTROL__PAGE = SALT + 18;

        static const int ACCESSCONTROL__WRITEENABLE = SALT + 19;

        static const int TARGETDEVICES__TARGETDEVICE = SALT + 20;

        static const int TARGETDEVICES__METAINFORMATION = SALT + 21;

        static const int TARGETDEVICE__DESCRIPTION = SALT + 22;

        static const int TARGETDEVICE__METAINFORMATION = SALT + 23;

        static const int TARGETDEVICE__REFIMPLEMENTATION = SALT + 24;

        static const int TARGETDEVICE__TARGETPORTS = SALT + 25;

        static const int TARGETDEVICE__DETAILS = SALT + 26;

        static const int TTTECHIPTARGETDEVICE__CLOCKSPEED = SALT + 27;

        static const int TTTECHIPTARGETDEVICE__MEDIACONTROLENABLED = SALT + 28;

        static const int DIAGNOSTIC__DIAGNOSISSCHEDULEENTRY = SALT + 29;

        static const int DIAGNOSISSCHEDULEENTRY__TIME = SALT + 30;

        static const int DIAGNOSISSCHEDULEENTRY__ITEMADDRESS = SALT + 31;

        static const int DIAGNOSISSCHEDULEENTRY__ITEMSNUMBER = SALT + 32;

        static const int TARGETPORTS__TARGETPORT = SALT + 33;

        static const int TARGETPORT__RXLATENCY = SALT + 34;

        static const int TARGETPORT__TXLATENCY = SALT + 35;

        static const int TARGETPORT__SPEED = SALT + 36;

        static const int TARGETPORT__PORTTYPE = SALT + 37;

        static const int TARGETPORT__PORTSERIALNUMBER = SALT + 38;

        static const int ANTIMASQUERADING__MACADDRESS = SALT + 39;

        static const int ANTIMASQUERADING__REFPORT = SALT + 40;

        static const int ANTIMASQUERADING__REFVIRTUALLINK = SALT + 41;

        static const int GENERALTARGETDEVICE__SOURCE = SALT + 42;

        // IDs for classifiers for class AccessControl 

        static const int
                ACCESSCONTROL__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                ACCESSCONTROL__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class AntiMasquerading 

        static const int
                ANTIMASQUERADING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                ANTIMASQUERADING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class DiagnosisScheduleEntry 

        static const int
                DIAGNOSISSCHEDULEENTRY__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DIAGNOSISSCHEDULEENTRY__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class Diagnostic 

        static const int
                DIAGNOSTIC__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DIAGNOSTIC__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                DIAGNOSTIC__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class GeneralTargetDevice 

        static const int
                GENERALTARGETDEVICE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                GENERALTARGETDEVICE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                GENERALTARGETDEVICE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int GENERALTARGETDEVICE__DESCRIPTION =
                TARGETDEVICE__DESCRIPTION;

        static const int GENERALTARGETDEVICE__METAINFORMATION =
                TARGETDEVICE__METAINFORMATION;

        static const int GENERALTARGETDEVICE__REFIMPLEMENTATION =
                TARGETDEVICE__REFIMPLEMENTATION;

        static const int GENERALTARGETDEVICE__TARGETPORTS =
                TARGETDEVICE__TARGETPORTS;

        static const int GENERALTARGETDEVICE__DETAILS = TARGETDEVICE__DETAILS;

        // IDs for classifiers for class MacAcceptanceEntry 

        static const int
                MACACCEPTANCEENTRY__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                MACACCEPTANCEENTRY__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class ManagementInterface 

        static const int
                MANAGEMENTINTERFACE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                MANAGEMENTINTERFACE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class PortInfos 

        static const int
                PORTINFOS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PORTINFOS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class TargetDevice 

        static const int
                TARGETDEVICE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TARGETDEVICE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TARGETDEVICE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class TargetDevices 

        static const int
                TARGETDEVICES__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TARGETDEVICES__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class TargetPort 

        static const int
                TARGETPORT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TARGETPORT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TARGETPORT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class TargetPorts 

        static const int
                TARGETPORTS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TARGETPORTS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class TTTechIpTargetDevice 

        static const int
                TTTECHIPTARGETDEVICE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTTECHIPTARGETDEVICE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TTTECHIPTARGETDEVICE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int TTTECHIPTARGETDEVICE__DESCRIPTION =
                TARGETDEVICE__DESCRIPTION;

        static const int TTTECHIPTARGETDEVICE__METAINFORMATION =
                TARGETDEVICE__METAINFORMATION;

        static const int TTTECHIPTARGETDEVICE__REFIMPLEMENTATION =
                TARGETDEVICE__REFIMPLEMENTATION;

        static const int TTTECHIPTARGETDEVICE__TARGETPORTS =
                TARGETDEVICE__TARGETPORTS;

        static const int TTTECHIPTARGETDEVICE__DETAILS = TARGETDEVICE__DETAILS;

        // IDs for classifiers for class TTTechProtocolLayerDevice 

        static const int
                TTTECHPROTOCOLLAYERDEVICE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTTECHPROTOCOLLAYERDEVICE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TTTECHPROTOCOLLAYERDEVICE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int TTTECHPROTOCOLLAYERDEVICE__DESCRIPTION =
                TARGETDEVICE__DESCRIPTION;

        static const int TTTECHPROTOCOLLAYERDEVICE__METAINFORMATION =
                TARGETDEVICE__METAINFORMATION;

        static const int TTTECHPROTOCOLLAYERDEVICE__REFIMPLEMENTATION =
                TARGETDEVICE__REFIMPLEMENTATION;

        static const int TTTECHPROTOCOLLAYERDEVICE__TARGETPORTS =
                TARGETDEVICE__TARGETPORTS;

        static const int TTTECHPROTOCOLLAYERDEVICE__DETAILS =
                TARGETDEVICE__DETAILS;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getManagementInterface();

        virtual ::ecore::EClass_ptr getMacAcceptanceEntry();

        virtual ::ecore::EClass_ptr getAccessControl();

        virtual ::ecore::EClass_ptr getTargetDevices();

        virtual ::ecore::EClass_ptr getTargetDevice();

        virtual ::ecore::EClass_ptr getTTTechIpTargetDevice();

        virtual ::ecore::EClass_ptr getDiagnostic();

        virtual ::ecore::EClass_ptr getDiagnosisScheduleEntry();

        virtual ::ecore::EClass_ptr getTargetPorts();

        virtual ::ecore::EClass_ptr getTargetPort();

        virtual ::ecore::EClass_ptr getAntiMasquerading();

        virtual ::ecore::EClass_ptr getPortInfos();

        virtual ::ecore::EEnum_ptr getAddressTypeEnum();

        virtual ::ecore::EEnum_ptr getDiagnosisScheduleModeEnum();

        virtual ::ecore::EEnum_ptr getPortTypeType();

        virtual ::ecore::EClass_ptr getTTTechProtocolLayerDevice();

        virtual ::ecore::EClass_ptr getGeneralTargetDevice();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EAttribute_ptr
                getManagementInterface__configurationVersion();

        virtual ::ecore::EAttribute_ptr getManagementInterface__speed();

        virtual ::ecore::EReference_ptr
                getManagementInterface__macAcceptanceEntry();

        virtual ::ecore::EAttribute_ptr
                getManagementInterface__unlockWrTimeout();

        virtual ::ecore::EAttribute_ptr getManagementInterface__resetTimeout();

        virtual ::ecore::EAttribute_ptr
                getManagementInterface__unlockDestAddress();

        virtual ::ecore::EAttribute_ptr
                getManagementInterface__schedDiagDestAddress();

        virtual ::ecore::EAttribute_ptr getManagementInterface__sourceAddress();

        virtual ::ecore::EAttribute_ptr
                getManagementInterface__expectedUnlocks();

        virtual ::ecore::EAttribute_ptr
                getManagementInterface__expectedResets();

        virtual ::ecore::EAttribute_ptr
                getManagementInterface__diagnosisScheduleMode();

        virtual ::ecore::EAttribute_ptr getManagementInterface__apbTimeout();

        virtual ::ecore::EAttribute_ptr
                getMacAcceptanceEntry__acceptanceMacAddress();

        virtual ::ecore::EAttribute_ptr getMacAcceptanceEntry__addressType();

        virtual ::ecore::EReference_ptr getMacAcceptanceEntry__accessControl();

        virtual ::ecore::EAttribute_ptr getMacAcceptanceEntry__unlockEnabled();

        virtual ::ecore::EAttribute_ptr getMacAcceptanceEntry__resetEnabled();

        virtual ::ecore::EAttribute_ptr
                getMacAcceptanceEntry__responseDestMacAddress();

        virtual ::ecore::EAttribute_ptr getAccessControl__page();

        virtual ::ecore::EAttribute_ptr getAccessControl__writeEnable();

        virtual ::ecore::EReference_ptr getTargetDevices__targetDevice();

        virtual ::ecore::EReference_ptr getTargetDevices__metaInformation();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EAttribute_ptr getTargetDevice__description();

        virtual ::ecore::EReference_ptr getTargetDevice__metaInformation();

        virtual ::ecore::EReference_ptr getTargetDevice__refImplementation();

        virtual ::ecore::EReference_ptr getTargetDevice__targetPorts();

        virtual ::ecore::EReference_ptr getTargetDevice__details();

        virtual ::ecore::EAttribute_ptr getTTTechIpTargetDevice__clockSpeed();

        virtual ::ecore::EAttribute_ptr
                getTTTechIpTargetDevice__mediaControlEnabled();

        virtual ::ecore::EReference_ptr getDiagnostic__diagnosisScheduleEntry();

        virtual ::ecore::EAttribute_ptr getDiagnosisScheduleEntry__time();

        virtual ::ecore::EAttribute_ptr
                getDiagnosisScheduleEntry__itemAddress();

        virtual ::ecore::EAttribute_ptr
                getDiagnosisScheduleEntry__itemsNumber();

        virtual ::ecore::EReference_ptr getTargetPorts__targetPort();

        virtual ::ecore::EAttribute_ptr getTargetPort__rxLatency();

        virtual ::ecore::EAttribute_ptr getTargetPort__txLatency();

        virtual ::ecore::EAttribute_ptr getTargetPort__speed();

        virtual ::ecore::EAttribute_ptr getTargetPort__portType();

        virtual ::ecore::EAttribute_ptr getTargetPort__portSerialNumber();

        virtual ::ecore::EAttribute_ptr getAntiMasquerading__macAddress();

        virtual ::ecore::EReference_ptr getAntiMasquerading__refPort();

        virtual ::ecore::EReference_ptr getAntiMasquerading__refVirtualLink();

        virtual ::ecore::EAttribute_ptr getGeneralTargetDevice__source();

    protected:

        static std::auto_ptr< Device_TargetsPackage > s_instance;

        Device_TargetsPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_ManagementInterfaceEClass;

        ::ecore::EClass_ptr m_MacAcceptanceEntryEClass;

        ::ecore::EClass_ptr m_AccessControlEClass;

        ::ecore::EClass_ptr m_TargetDevicesEClass;

        ::ecore::EClass_ptr m_TargetDeviceEClass;

        ::ecore::EClass_ptr m_TTTechIpTargetDeviceEClass;

        ::ecore::EClass_ptr m_DiagnosticEClass;

        ::ecore::EClass_ptr m_DiagnosisScheduleEntryEClass;

        ::ecore::EClass_ptr m_TargetPortsEClass;

        ::ecore::EClass_ptr m_TargetPortEClass;

        ::ecore::EClass_ptr m_AntiMasqueradingEClass;

        ::ecore::EClass_ptr m_PortInfosEClass;

        ::ecore::EClass_ptr m_TTTechProtocolLayerDeviceEClass;

        ::ecore::EClass_ptr m_GeneralTargetDeviceEClass;

        // EEnuminstances 

        ::ecore::EEnum_ptr m_AddressTypeEnumEEnum;

        ::ecore::EEnum_ptr m_DiagnosisScheduleModeEnumEEnum;

        ::ecore::EEnum_ptr m_PortTypeTypeEEnum;

        // EDataType instances 


        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EAttribute_ptr m_ManagementInterface__configurationVersion;

        ::ecore::EAttribute_ptr m_ManagementInterface__speed;

        ::ecore::EReference_ptr m_ManagementInterface__macAcceptanceEntry;

        ::ecore::EAttribute_ptr m_ManagementInterface__unlockWrTimeout;

        ::ecore::EAttribute_ptr m_ManagementInterface__resetTimeout;

        ::ecore::EAttribute_ptr m_ManagementInterface__unlockDestAddress;

        ::ecore::EAttribute_ptr m_ManagementInterface__schedDiagDestAddress;

        ::ecore::EAttribute_ptr m_ManagementInterface__sourceAddress;

        ::ecore::EAttribute_ptr m_ManagementInterface__expectedUnlocks;

        ::ecore::EAttribute_ptr m_ManagementInterface__expectedResets;

        ::ecore::EAttribute_ptr m_ManagementInterface__diagnosisScheduleMode;

        ::ecore::EAttribute_ptr m_ManagementInterface__apbTimeout;

        ::ecore::EAttribute_ptr m_MacAcceptanceEntry__acceptanceMacAddress;

        ::ecore::EAttribute_ptr m_MacAcceptanceEntry__addressType;

        ::ecore::EReference_ptr m_MacAcceptanceEntry__accessControl;

        ::ecore::EAttribute_ptr m_MacAcceptanceEntry__unlockEnabled;

        ::ecore::EAttribute_ptr m_MacAcceptanceEntry__resetEnabled;

        ::ecore::EAttribute_ptr m_MacAcceptanceEntry__responseDestMacAddress;

        ::ecore::EAttribute_ptr m_AccessControl__page;

        ::ecore::EAttribute_ptr m_AccessControl__writeEnable;

        ::ecore::EReference_ptr m_TargetDevices__targetDevice;

        ::ecore::EReference_ptr m_TargetDevices__metaInformation;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EAttribute_ptr m_TargetDevice__description;

        ::ecore::EReference_ptr m_TargetDevice__metaInformation;

        ::ecore::EReference_ptr m_TargetDevice__refImplementation;

        ::ecore::EReference_ptr m_TargetDevice__targetPorts;

        ::ecore::EReference_ptr m_TargetDevice__details;

        ::ecore::EAttribute_ptr m_TTTechIpTargetDevice__clockSpeed;

        ::ecore::EAttribute_ptr m_TTTechIpTargetDevice__mediaControlEnabled;

        ::ecore::EReference_ptr m_Diagnostic__diagnosisScheduleEntry;

        ::ecore::EAttribute_ptr m_DiagnosisScheduleEntry__time;

        ::ecore::EAttribute_ptr m_DiagnosisScheduleEntry__itemAddress;

        ::ecore::EAttribute_ptr m_DiagnosisScheduleEntry__itemsNumber;

        ::ecore::EReference_ptr m_TargetPorts__targetPort;

        ::ecore::EAttribute_ptr m_TargetPort__rxLatency;

        ::ecore::EAttribute_ptr m_TargetPort__txLatency;

        ::ecore::EAttribute_ptr m_TargetPort__speed;

        ::ecore::EAttribute_ptr m_TargetPort__portType;

        ::ecore::EAttribute_ptr m_TargetPort__portSerialNumber;

        ::ecore::EAttribute_ptr m_AntiMasquerading__macAddress;

        ::ecore::EReference_ptr m_AntiMasquerading__refPort;

        ::ecore::EReference_ptr m_AntiMasquerading__refVirtualLink;

        ::ecore::EAttribute_ptr m_GeneralTargetDevice__source;

    };

} // Device_Targets


#endif // _DEVICE_TARGETSPACKAGE_HPP
