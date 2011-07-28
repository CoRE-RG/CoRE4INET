// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/DeviceMappingImpl.cpp
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

#include "DeviceMapping.hpp"
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetDevice.hpp>
#include <Device_Target_Mapping/PerPortBagAccounts.hpp>
#include <Device_Target_Mapping/PortMappings.hpp>
#include <Device_Targets/AntiMasquerading.hpp>
#include <Device_Targets/Diagnostic.hpp>
#include <Device_Target_Mapping/Trigger.hpp>
#include <Device_Target_Mapping/BufferMapping.hpp>
#include <Device_Targets/ManagementInterface.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Target_Mapping;

/*PROTECTED REGION ID(DeviceMappingImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void DeviceMapping::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences
    if (m_perPortBagAccounts)
    {
        m_perPortBagAccounts->_initialize();
        m_perPortBagAccounts->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__perPortBagAccounts());
    }
    if (m_portMappings)
    {
        m_portMappings->_initialize();
        m_portMappings->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__portMappings());
    }
    for (size_t i = 0; i < m_antiMasquerading->size(); i++)
    {
        (*m_antiMasquerading)[i]->_initialize();
        (*m_antiMasquerading)[i]->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__antiMasquerading());
    }
    if (m_diagnostic)
    {
        m_diagnostic->_initialize();
        m_diagnostic->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__diagnostic());
    }
    for (size_t i = 0; i < m_trigger->size(); i++)
    {
        (*m_trigger)[i]->_initialize();
        (*m_trigger)[i]->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__trigger());
    }
    if (m_bufferMapping)
    {
        m_bufferMapping->_initialize();
        m_bufferMapping->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__bufferMapping());
    }
    if (m_managementInterface)
    {
        m_managementInterface->_initialize();
        m_managementInterface->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__managementInterface());
    }
    if (m_metaInformation)
    {
        m_metaInformation->_initialize();
        m_metaInformation->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__metaInformation());
    }

    /*PROTECTED REGION ID(DeviceMappingImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject DeviceMapping::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean _resolve)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
    {
        _any = m_eAnnotations->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_signature);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any, m_name);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__REFTARGETDEVICE:
    {
        _any = static_cast< ::ecore::EObject* > (m_refTargetDevice);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PERPORTBAGACCOUNTS:
    {
        _any = static_cast< ::ecore::EObject* > (m_perPortBagAccounts);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PORTMAPPINGS:
    {
        _any = static_cast< ::ecore::EObject* > (m_portMappings);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__AGINGTIME:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_agingTime);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__ANTIMASQUERADING:
    {
        _any = m_antiMasquerading->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__DIAGNOSTIC:
    {
        _any = static_cast< ::ecore::EObject* > (m_diagnostic);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__TRIGGER:
    {
        _any = m_trigger->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__BUFFERMAPPING:
    {
        _any = static_cast< ::ecore::EObject* > (m_bufferMapping);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__MANAGEMENTINTERFACE:
    {
        _any = static_cast< ::ecore::EObject* > (m_managementInterface);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;

    }
    throw "Error";
}

void DeviceMapping::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::System_Specification::ModelElement::getEAnnotations().clear();
        ::System_Specification::ModelElement::getEAnnotations().insert_all(*_t0);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_signature);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_name);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__REFTARGETDEVICE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Targets::TargetDevice_ptr _t1 =
                dynamic_cast< ::Device_Targets::TargetDevice_ptr > (_t0);
        ::Device_Target_Mapping::DeviceMapping::setRefTargetDevice(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PERPORTBAGACCOUNTS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Target_Mapping::PerPortBagAccounts_ptr
                _t1 =
                        dynamic_cast< ::Device_Target_Mapping::PerPortBagAccounts_ptr > (_t0);
        ::Device_Target_Mapping::DeviceMapping::setPerPortBagAccounts(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PORTMAPPINGS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Target_Mapping::PortMappings_ptr _t1 =
                dynamic_cast< ::Device_Target_Mapping::PortMappings_ptr > (_t0);
        ::Device_Target_Mapping::DeviceMapping::setPortMappings(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__AGINGTIME:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_agingTime);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__ANTIMASQUERADING:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Target_Mapping::DeviceMapping::getAntiMasquerading().clear();
        ::Device_Target_Mapping::DeviceMapping::getAntiMasquerading().insert_all(
                *_t0);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__DIAGNOSTIC:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Targets::Diagnostic_ptr _t1 =
                dynamic_cast< ::Device_Targets::Diagnostic_ptr > (_t0);
        ::Device_Target_Mapping::DeviceMapping::setDiagnostic(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__TRIGGER:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Target_Mapping::DeviceMapping::getTrigger().clear();
        ::Device_Target_Mapping::DeviceMapping::getTrigger().insert_all(*_t0);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__BUFFERMAPPING:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Target_Mapping::BufferMapping_ptr
                _t1 =
                        dynamic_cast< ::Device_Target_Mapping::BufferMapping_ptr > (_t0);
        ::Device_Target_Mapping::DeviceMapping::setBufferMapping(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__MANAGEMENTINTERFACE:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Targets::ManagementInterface_ptr _t1 =
                dynamic_cast< ::Device_Targets::ManagementInterface_ptr > (_t0);
        ::Device_Target_Mapping::DeviceMapping::setManagementInterface(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::Device_Target_Mapping::DeviceMapping::setMetaInformation(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean DeviceMapping::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_name);
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__REFTARGETDEVICE:
        return m_refTargetDevice;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PERPORTBAGACCOUNTS:
        return m_perPortBagAccounts;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__PORTMAPPINGS:
        return m_portMappings;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__AGINGTIME:
        /*PROTECTED REGION ID(DeviceMappingeIsSet__DeviceMappingm_agingTime) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__ANTIMASQUERADING:
        return m_antiMasquerading && m_antiMasquerading->size();
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__DIAGNOSTIC:
        return m_diagnostic;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__TRIGGER:
        return m_trigger && m_trigger->size();
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__BUFFERMAPPING:
        return m_bufferMapping;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__MANAGEMENTINTERFACE:
        return m_managementInterface;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEVICEMAPPING__METAINFORMATION:
        return m_metaInformation;

    }
    throw "Error";
}

void DeviceMapping::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr DeviceMapping::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage_ptr > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getDeviceMapping();
    return _eclass;
}

