// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/IntegrityConfigurationsImpl.cpp
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

#include "IntegrityConfigurations.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncClientIntegrityConfig.hpp>
#include <Network_Configuration/CompressionMasterIntegrityConfig.hpp>
#include <Network_Configuration/SyncMasterIntegrityConfig.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(IntegrityConfigurationsImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void IntegrityConfigurations::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_syncClientIntegrityConfig->size(); i++)
    {
        (*m_syncClientIntegrityConfig)[i]->_initialize();
        (*m_syncClientIntegrityConfig)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getIntegrityConfigurations__syncClientIntegrityConfig());
    }
    for (size_t i = 0; i < m_compressionMasterIntegrityConfig->size(); i++)
    {
        (*m_compressionMasterIntegrityConfig)[i]->_initialize();
        (*m_compressionMasterIntegrityConfig)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getIntegrityConfigurations__compressionMasterIntegrityConfig());
    }
    for (size_t i = 0; i < m_syncMasterIntegrityConfig->size(); i++)
    {
        (*m_syncMasterIntegrityConfig)[i]->_initialize();
        (*m_syncMasterIntegrityConfig)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getIntegrityConfigurations__syncMasterIntegrityConfig());
    }

    /*PROTECTED REGION ID(IntegrityConfigurationsImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject IntegrityConfigurations::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCCLIENTINTEGRITYCONFIG:
    {
        _any = m_syncClientIntegrityConfig->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__COMPRESSIONMASTERINTEGRITYCONFIG:
    {
        _any
                = m_compressionMasterIntegrityConfig->asEListOf<
                        ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCMASTERINTEGRITYCONFIG:
    {
        _any = m_syncMasterIntegrityConfig->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any, m_name);
    }
        return _any;

    }
    throw "Error";
}

void IntegrityConfigurations::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCCLIENTINTEGRITYCONFIG:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::IntegrityConfigurations::getSyncClientIntegrityConfig().clear();
        ::Network_Configuration::IntegrityConfigurations::getSyncClientIntegrityConfig().insert_all(
                *_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__COMPRESSIONMASTERINTEGRITYCONFIG:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::IntegrityConfigurations::getCompressionMasterIntegrityConfig().clear();
        ::Network_Configuration::IntegrityConfigurations::getCompressionMasterIntegrityConfig().insert_all(
                *_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCMASTERINTEGRITYCONFIG:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::IntegrityConfigurations::getSyncMasterIntegrityConfig().clear();
        ::Network_Configuration::IntegrityConfigurations::getSyncMasterIntegrityConfig().insert_all(
                *_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_name);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean IntegrityConfigurations::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCCLIENTINTEGRITYCONFIG:
        return m_syncClientIntegrityConfig
                && m_syncClientIntegrityConfig->size();
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__COMPRESSIONMASTERINTEGRITYCONFIG:
        return m_compressionMasterIntegrityConfig
                && m_compressionMasterIntegrityConfig->size();
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__SYNCMASTERINTEGRITYCONFIG:
        return m_syncMasterIntegrityConfig
                && m_syncMasterIntegrityConfig->size();
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS__NAME:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_name);

    }
    throw "Error";
}

void IntegrityConfigurations::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr IntegrityConfigurations::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getIntegrityConfigurations();
    return _eclass;
}

