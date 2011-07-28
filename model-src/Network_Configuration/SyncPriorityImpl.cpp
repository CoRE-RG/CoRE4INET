// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncPriorityImpl.cpp
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

#include "SyncPriority.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncClient.hpp>
#include <Network_Configuration/SyncMaster.hpp>
#include <Network_Configuration/CompressionMaster.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(SyncPriorityImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void SyncPriority::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_syncClient->size(); i++)
    {
        (*m_syncClient)[i]->_initialize();
        (*m_syncClient)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncPriority__syncClient());
    }
    for (size_t i = 0; i < m_syncMaster->size(); i++)
    {
        (*m_syncMaster)[i]->_initialize();
        (*m_syncMaster)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncPriority__syncMaster());
    }
    for (size_t i = 0; i < m_compressionMaster->size(); i++)
    {
        (*m_compressionMaster)[i]->_initialize();
        (*m_compressionMaster)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncPriority__compressionMaster());
    }

    /*PROTECTED REGION ID(SyncPriorityImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject SyncPriority::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__VALUE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::toAny(_any, m_value);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCCLIENT:
    {
        _any = m_syncClient->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCMASTER:
    {
        _any = m_syncMaster->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__COMPRESSIONMASTER:
    {
        _any = m_compressionMaster->asEListOf< ::ecore::EObject > ();
    }
        return _any;

    }
    throw "Error";
}

void SyncPriority::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__VALUE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::fromAny(_newValue,
                m_value);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCCLIENT:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::SyncPriority::getSyncClient().clear();
        ::Network_Configuration::SyncPriority::getSyncClient().insert_all(*_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCMASTER:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::SyncPriority::getSyncMaster().clear();
        ::Network_Configuration::SyncPriority::getSyncMaster().insert_all(*_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__COMPRESSIONMASTER:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::SyncPriority::getCompressionMaster().clear();
        ::Network_Configuration::SyncPriority::getCompressionMaster().insert_all(
                *_t0);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean SyncPriority::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__VALUE:
        /*PROTECTED REGION ID(SyncPriorityeIsSet__SyncPrioritym_value) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_value != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCCLIENT:
        return m_syncClient && m_syncClient->size();
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__SYNCMASTER:
        return m_syncMaster && m_syncMaster->size();
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCPRIORITY__COMPRESSIONMASTER:
        return m_compressionMaster && m_compressionMaster->size();

    }
    throw "Error";
}

void SyncPriority::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr SyncPriority::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getSyncPriority();
    return _eclass;
}

