// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SynchronizationImpl.cpp
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

#include "Synchronization.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncDomain.hpp>
#include <Network_Configuration/IntegrityConfigurations.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(SynchronizationImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void Synchronization::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_syncDomain->size(); i++)
    {
        (*m_syncDomain)[i]->_initialize();
        (*m_syncDomain)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSynchronization__syncDomain());
    }
    if (m_integrityConfigurations)
    {
        m_integrityConfigurations->_initialize();
        m_integrityConfigurations->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSynchronization__integrityConfigurations());
    }

    /*PROTECTED REGION ID(SynchronizationImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject Synchronization::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__SYNCDOMAIN:
    {
        _any = m_syncDomain->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__INTEGRITYCONFIGURATIONS:
    {
        _any = static_cast< ::ecore::EObject* > (m_integrityConfigurations);
    }
        return _any;

    }
    throw "Error";
}

void Synchronization::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__SYNCDOMAIN:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::Synchronization::getSyncDomain().clear();
        ::Network_Configuration::Synchronization::getSyncDomain().insert_all(
                *_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__INTEGRITYCONFIGURATIONS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Network_Configuration::IntegrityConfigurations_ptr
                _t1 =
                        dynamic_cast< ::Network_Configuration::IntegrityConfigurations_ptr > (_t0);
        ::Network_Configuration::Synchronization::setIntegrityConfigurations(
                _t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean Synchronization::eIsSet(::ecore::EInt _featureID)
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__SYNCDOMAIN:
        return m_syncDomain && m_syncDomain->size();
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCHRONIZATION__INTEGRITYCONFIGURATIONS:
        return m_integrityConfigurations;

    }
    throw "Error";
}

void Synchronization::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr Synchronization::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getSynchronization();
    return _eclass;
}

