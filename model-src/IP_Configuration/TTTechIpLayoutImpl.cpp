// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/TTTechIpLayoutImpl.cpp
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

#include "TTTechIpLayout.hpp"
#include <IP_Configuration/IP_ConfigurationPackage.hpp>
#include <IP_Configuration/IpLayout.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::IP_Configuration;

/*PROTECTED REGION ID(TTTechIpLayoutImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void TTTechIpLayout::_initialize()
{
    // Supertypes
    ::IP_Configuration::IpLayout::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(TTTechIpLayoutImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject TTTechIpLayout::eGet(::ecore::EInt _featureID,
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
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_description);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__VERSION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any, m_Version);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__ID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any, m_ID);
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIPLAYOUT__PINNING:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_pinning);
    }
        return _any;

    }
    throw "Error";
}

void TTTechIpLayout::eSet(::ecore::EInt _featureID,
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
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_description);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__VERSION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_Version);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::IP_Configuration::IpLayout::setMetaInformation(_t1);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__ID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_ID);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIPLAYOUT__PINNING:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_pinning);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean TTTechIpLayout::eIsSet(::ecore::EInt _featureID)
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
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__DESCRIPTION:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_description);
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__VERSION:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(
                m_Version);
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__METAINFORMATION:
        return m_metaInformation;
    case ::IP_Configuration::IP_ConfigurationPackage::IPLAYOUT__ID:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(m_ID);
    case ::IP_Configuration::IP_ConfigurationPackage::TTTECHIPLAYOUT__PINNING:
        /*PROTECTED REGION ID(TTTechIpLayouteIsSet__TTTechIpLayoutm_pinning) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void TTTechIpLayout::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr TTTechIpLayout::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::IP_Configuration::IP_ConfigurationPackage_ptr > (::IP_Configuration::IP_ConfigurationPackage::_instance())->getTTTechIpLayout();
    return _eclass;
}

