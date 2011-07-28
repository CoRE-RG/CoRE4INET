// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TargetPortImpl.cpp
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

#include "TargetPort.hpp"
#include <Device_Targets/Device_TargetsPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Targets;

/*PROTECTED REGION ID(TargetPortImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void TargetPort::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(TargetPortImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject TargetPort::eGet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__RXLATENCY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_rxLatency);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__TXLATENCY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_txLatency);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__SPEED:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::SpeedEnum >::toAny(
                _any, m_speed);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTTYPE:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Targets::PortTypeType >::toAny(
                _any, m_portType);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTSERIALNUMBER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_portSerialNumber);
    }
        return _any;

    }
    throw "Error";
}

void TargetPort::eSet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__RXLATENCY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_rxLatency);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__TXLATENCY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_txLatency);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__SPEED:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::SpeedEnum >::fromAny(
                _newValue, m_speed);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTTYPE:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Targets::PortTypeType >::fromAny(
                _newValue, m_portType);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTSERIALNUMBER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_portSerialNumber);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean TargetPort::eIsSet(::ecore::EInt _featureID)
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
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__RXLATENCY:
        /*PROTECTED REGION ID(TargetPorteIsSet__TargetPortm_rxLatency) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__TXLATENCY:
        /*PROTECTED REGION ID(TargetPorteIsSet__TargetPortm_txLatency) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__SPEED:
        /*PROTECTED REGION ID(TargetPorteIsSet__TargetPortm_speed) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTTYPE:
        /*PROTECTED REGION ID(TargetPorteIsSet__TargetPortm_portType) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::TARGETPORT__PORTSERIALNUMBER:
        /*PROTECTED REGION ID(TargetPorteIsSet__TargetPortm_portSerialNumber) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_portSerialNumber != 0;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void TargetPort::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr TargetPort::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (::Device_Targets::Device_TargetsPackage::_instance())->getTargetPort();
    return _eclass;
}

