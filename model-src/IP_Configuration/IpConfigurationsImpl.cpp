// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IpConfigurationsImpl.cpp
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

#include "IpConfigurations.hpp"
#include <IP_Configuration/IP_ConfigurationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <IP_Configuration/Implementation.hpp>
#include <IP_Configuration/IpLayout.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::IP_Configuration;

/*PROTECTED REGION ID(IpConfigurationsImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void IpConfigurations::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_implementation->size(); i++)
    {
        (*m_implementation)[i]->_initialize();
        (*m_implementation)[i]->_setEContainer(
                this,
                ::IP_Configuration::IP_ConfigurationPackage::_instance()->getIpConfigurations__implementation());
    }
    for (size_t i = 0; i < m_ipLayout->size(); i++)
    {
        (*m_ipLayout)[i]->_initialize();
        (*m_ipLayout)[i]->_setEContainer(
                this,
                ::IP_Configuration::IP_ConfigurationPackage::_instance()->getIpConfigurations__ipLayout());
    }
    if (m_metaInformation)
    {
        m_metaInformation->_initialize();
        m_metaInformation->_setEContainer(
                this,
                ::IP_Configuration::IP_ConfigurationPackage::_instance()->getIpConfigurations__metaInformation());
    }

    /*PROTECTED REGION ID(IpConfigurationsImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject IpConfigurations::eGet(::ecore::EInt _featureID,
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
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IMPLEMENTATION:
    {
        _any = m_implementation->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IPLAYOUT:
    {
        _any = m_ipLayout->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;

    }
    throw "Error";
}

void IpConfigurations::eSet(::ecore::EInt _featureID,
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
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IMPLEMENTATION:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::IP_Configuration::IpConfigurations::getImplementation().clear();
        ::IP_Configuration::IpConfigurations::getImplementation().insert_all(
                *_t0);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IPLAYOUT:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::IP_Configuration::IpConfigurations::getIpLayout().clear();
        ::IP_Configuration::IpConfigurations::getIpLayout().insert_all(*_t0);
    }
        return;
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::IP_Configuration::IpConfigurations::setMetaInformation(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean IpConfigurations::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IMPLEMENTATION:
        return m_implementation && m_implementation->size();
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__IPLAYOUT:
        return m_ipLayout && m_ipLayout->size();
    case ::IP_Configuration::IP_ConfigurationPackage::IPCONFIGURATIONS__METAINFORMATION:
        return m_metaInformation;

    }
    throw "Error";
}

void IpConfigurations::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr IpConfigurations::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::IP_Configuration::IP_ConfigurationPackage_ptr > (::IP_Configuration::IP_ConfigurationPackage::_instance())->getIpConfigurations();
    return _eclass;
}

