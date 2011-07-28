// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/PortMappingImpl.cpp
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

#include "PortMapping.hpp"
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetPort.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Target_Mapping;

/*PROTECTED REGION ID(PortMappingImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void PortMapping::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(PortMappingImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject PortMapping::eGet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__RXLATENCYCORRECTION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_rxLatencyCorrection);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__TXLATENCYCORRECTION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_txLatencyCorrection);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLERXFC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_disableRxFc);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLETXFC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_disableTxFc);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFTARGETPORT:
    {
        _any = static_cast< ::ecore::EObject* > (m_refTargetPort);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFPORT:
    {
        _any = static_cast< ::ecore::EObject* > (m_refPort);
    }
        return _any;

    }
    throw "Error";
}

void PortMapping::eSet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__RXLATENCYCORRECTION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_rxLatencyCorrection);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__TXLATENCYCORRECTION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_txLatencyCorrection);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLERXFC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_disableRxFc);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLETXFC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_disableTxFc);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFTARGETPORT:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Targets::TargetPort_ptr _t1 =
                dynamic_cast< ::Device_Targets::TargetPort_ptr > (_t0);
        ::Device_Target_Mapping::PortMapping::setRefTargetPort(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFPORT:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Port_ptr _t1 =
                dynamic_cast< ::System_Specification::Port_ptr > (_t0);
        ::Device_Target_Mapping::PortMapping::setRefPort(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean PortMapping::eIsSet(::ecore::EInt _featureID)
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__RXLATENCYCORRECTION:
        /*PROTECTED REGION ID(PortMappingeIsSet__PortMappingm_rxLatencyCorrection) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__TXLATENCYCORRECTION:
        /*PROTECTED REGION ID(PortMappingeIsSet__PortMappingm_txLatencyCorrection) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLERXFC:
        /*PROTECTED REGION ID(PortMappingeIsSet__PortMappingm_disableRxFc) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_disableRxFc != false;
        /*PROTECTED REGION END*/
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__DISABLETXFC:
        /*PROTECTED REGION ID(PortMappingeIsSet__PortMappingm_disableTxFc) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_disableTxFc != false;
        /*PROTECTED REGION END*/
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFTARGETPORT:
        return m_refTargetPort;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPING__REFPORT:
        return m_refPort;

    }
    throw "Error";
}

void PortMapping::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr PortMapping::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage_ptr > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getPortMapping();
    return _eclass;
}

