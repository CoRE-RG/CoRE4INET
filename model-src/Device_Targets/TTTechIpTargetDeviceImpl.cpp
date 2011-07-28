// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TTTechIpTargetDeviceImpl.cpp
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

#include "TTTechIpTargetDevice.hpp"
#include <Device_Targets/Device_TargetsPackage.hpp>
#include <Device_Targets/TargetDevice.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <IP_Configuration/Implementation.hpp>
#include <Device_Targets/TargetPorts.hpp>
#include <ecore/EStringToStringMapEntry.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Targets;

/*PROTECTED REGION ID(TTTechIpTargetDeviceImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void TTTechIpTargetDevice::_initialize()
{
    // Supertypes
    ::Device_Targets::TargetDevice::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(TTTechIpTargetDeviceImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject TTTechIpTargetDevice::eGet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_description);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__REFIMPLEMENTATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_refImplementation);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__TARGETPORTS:
    {
        _any = m_targetPorts->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DETAILS:
    {
        _any = m_details->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__CLOCKSPEED:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Target_Mapping::FrequencyType >::toAny(
                _any, m_clockSpeed);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__MEDIACONTROLENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_mediaControlEnabled);
    }
        return _any;

    }
    throw "Error";
}

void TTTechIpTargetDevice::eSet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_description);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::Device_Targets::TargetDevice::setMetaInformation(_t1);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__REFIMPLEMENTATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::IP_Configuration::Implementation_ptr _t1 =
                dynamic_cast< ::IP_Configuration::Implementation_ptr > (_t0);
        ::Device_Targets::TargetDevice::setRefImplementation(_t1);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__TARGETPORTS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Targets::TargetDevice::getTargetPorts().clear();
        ::Device_Targets::TargetDevice::getTargetPorts().insert_all(*_t0);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DETAILS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Targets::TargetDevice::getDetails().clear();
        ::Device_Targets::TargetDevice::getDetails().insert_all(*_t0);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__CLOCKSPEED:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Target_Mapping::FrequencyType >::fromAny(
                _newValue, m_clockSpeed);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__MEDIACONTROLENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_mediaControlEnabled);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean TTTechIpTargetDevice::eIsSet(::ecore::EInt _featureID)
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
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DESCRIPTION:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_description);
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__METAINFORMATION:
        return m_metaInformation;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__REFIMPLEMENTATION:
        return m_refImplementation;
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__TARGETPORTS:
        return m_targetPorts && m_targetPorts->size();
    case ::Device_Targets::Device_TargetsPackage::TARGETDEVICE__DETAILS:
        return m_details && m_details->size();
    case ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__CLOCKSPEED:
        return ::ecorecpp::mapping::set_traits<
                ::Device_Target_Mapping::FrequencyType >::is_set(m_clockSpeed);
    case ::Device_Targets::Device_TargetsPackage::TTTECHIPTARGETDEVICE__MEDIACONTROLENABLED:
        /*PROTECTED REGION ID(TTTechIpTargetDeviceeIsSet__TTTechIpTargetDevicem_mediaControlEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_mediaControlEnabled != false;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void TTTechIpTargetDevice::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr TTTechIpTargetDevice::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (::Device_Targets::Device_TargetsPackage::_instance())->getTTTechIpTargetDevice();
    return _eclass;
}

