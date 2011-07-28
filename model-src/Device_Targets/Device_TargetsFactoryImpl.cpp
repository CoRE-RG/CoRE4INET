// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/Device_TargetsFactoryImpl.cpp
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

#include <Device_Targets/Device_TargetsFactory.hpp>
#include <Device_Targets/Device_TargetsPackage.hpp>
#include <Device_Targets/ManagementInterface.hpp>
#include <Device_Targets/MacAcceptanceEntry.hpp>
#include <Device_Targets/AccessControl.hpp>
#include <Device_Targets/TargetDevices.hpp>
#include <Device_Targets/TargetDevice.hpp>
#include <Device_Targets/TTTechIpTargetDevice.hpp>
#include <Device_Targets/Diagnostic.hpp>
#include <Device_Targets/DiagnosisScheduleEntry.hpp>
#include <Device_Targets/TargetPorts.hpp>
#include <Device_Targets/TargetPort.hpp>
#include <Device_Targets/AntiMasquerading.hpp>
#include <Device_Targets/PortInfos.hpp>
#include <Device_Targets/TTTechProtocolLayerDevice.hpp>
#include <Device_Targets/GeneralTargetDevice.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Targets;

Device_TargetsFactory::Device_TargetsFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr Device_TargetsFactory::create(::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case Device_TargetsPackage::MANAGEMENTINTERFACE:
        return createManagementInterface();
    case Device_TargetsPackage::MACACCEPTANCEENTRY:
        return createMacAcceptanceEntry();
    case Device_TargetsPackage::ACCESSCONTROL:
        return createAccessControl();
    case Device_TargetsPackage::TARGETDEVICES:
        return createTargetDevices();
    case Device_TargetsPackage::TARGETDEVICE:
        return createTargetDevice();
    case Device_TargetsPackage::TTTECHIPTARGETDEVICE:
        return createTTTechIpTargetDevice();
    case Device_TargetsPackage::DIAGNOSTIC:
        return createDiagnostic();
    case Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY:
        return createDiagnosisScheduleEntry();
    case Device_TargetsPackage::TARGETPORTS:
        return createTargetPorts();
    case Device_TargetsPackage::TARGETPORT:
        return createTargetPort();
    case Device_TargetsPackage::ANTIMASQUERADING:
        return createAntiMasquerading();
    case Device_TargetsPackage::PORTINFOS:
        return createPortInfos();
    case Device_TargetsPackage::TTTECHPROTOCOLLAYERDEVICE:
        return createTTTechProtocolLayerDevice();
    case Device_TargetsPackage::GENERALTARGETDEVICE:
        return createGeneralTargetDevice();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject Device_TargetsFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Device_TargetsPackage::ADDRESSTYPEENUM:
    {
        ::ecore::EJavaObject _any;
        Device_TargetsPackage_ptr
                _epkg =
                        dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (getEPackage());
        return _epkg->getAddressTypeEnum()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    case Device_TargetsPackage::DIAGNOSISSCHEDULEMODEENUM:
    {
        ::ecore::EJavaObject _any;
        Device_TargetsPackage_ptr
                _epkg =
                        dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (getEPackage());
        return _epkg->getDiagnosisScheduleModeEnum()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    case Device_TargetsPackage::PORTTYPETYPE:
    {
        ::ecore::EJavaObject _any;
        Device_TargetsPackage_ptr
                _epkg =
                        dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (getEPackage());
        return _epkg->getPortTypeType()->getEEnumLiteralByLiteral(_literalValue)->getValue();
    }
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString Device_TargetsFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Device_TargetsPackage::ADDRESSTYPEENUM:
    {
        Device_TargetsPackage_ptr _epkg = ::Device_Targets::instanceOf<
                ::Device_Targets::Device_TargetsPackage >(getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getAddressTypeEnum()->getEEnumLiteral(_value)->getName();
    }
    case Device_TargetsPackage::DIAGNOSISSCHEDULEMODEENUM:
    {
        Device_TargetsPackage_ptr _epkg = ::Device_Targets::instanceOf<
                ::Device_Targets::Device_TargetsPackage >(getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getDiagnosisScheduleModeEnum()->getEEnumLiteral(_value)->getName();
    }
    case Device_TargetsPackage::PORTTYPETYPE:
    {
        Device_TargetsPackage_ptr _epkg = ::Device_Targets::instanceOf<
                ::Device_Targets::Device_TargetsPackage >(getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getPortTypeType()->getEEnumLiteral(_value)->getName();
    }
    default:
        throw "IllegalArgumentException";
    }
}

ManagementInterface_ptr Device_TargetsFactory::createManagementInterface()
{
    return new ManagementInterface();
}
MacAcceptanceEntry_ptr Device_TargetsFactory::createMacAcceptanceEntry()
{
    return new MacAcceptanceEntry();
}
AccessControl_ptr Device_TargetsFactory::createAccessControl()
{
    return new AccessControl();
}
TargetDevices_ptr Device_TargetsFactory::createTargetDevices()
{
    return new TargetDevices();
}
TargetDevice_ptr Device_TargetsFactory::createTargetDevice()
{
    return new TargetDevice();
}
TTTechIpTargetDevice_ptr Device_TargetsFactory::createTTTechIpTargetDevice()
{
    return new TTTechIpTargetDevice();
}
Diagnostic_ptr Device_TargetsFactory::createDiagnostic()
{
    return new Diagnostic();
}
DiagnosisScheduleEntry_ptr Device_TargetsFactory::createDiagnosisScheduleEntry()
{
    return new DiagnosisScheduleEntry();
}
TargetPorts_ptr Device_TargetsFactory::createTargetPorts()
{
    return new TargetPorts();
}
TargetPort_ptr Device_TargetsFactory::createTargetPort()
{
    return new TargetPort();
}
AntiMasquerading_ptr Device_TargetsFactory::createAntiMasquerading()
{
    return new AntiMasquerading();
}
PortInfos_ptr Device_TargetsFactory::createPortInfos()
{
    return new PortInfos();
}
TTTechProtocolLayerDevice_ptr Device_TargetsFactory::createTTTechProtocolLayerDevice()
{
    return new TTTechProtocolLayerDevice();
}
GeneralTargetDevice_ptr Device_TargetsFactory::createGeneralTargetDevice()
{
    return new GeneralTargetDevice();
}

