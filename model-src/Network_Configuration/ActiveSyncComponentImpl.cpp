// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/ActiveSyncComponentImpl.cpp
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

#include "ActiveSyncComponent.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <Network_Configuration/SyncBase.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/PCFVirtualLink.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(ActiveSyncComponentImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void ActiveSyncComponent::_initialize()
{
    // Supertypes
    ::Network_Configuration::SyncBase::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(ActiveSyncComponentImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject ActiveSyncComponent::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SCHEDULEDRECEIVEPIT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_scheduledReceivePit);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__ACCEPTANCEWINDOW:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_acceptanceWindow);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__LISTENTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_listenTimeout);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__PRIORITYFALLBACKCYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_priorityFallbackCycles);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SYNCTOSTABLEENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_syncToStableEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__SOURCEMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::toAny(
                _any, m_sourceMacAddress);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_refPcfVlidIntegration);
    }
        return _any;

    }
    throw "Error";
}

void ActiveSyncComponent::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SCHEDULEDRECEIVEPIT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_scheduledReceivePit);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__ACCEPTANCEWINDOW:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_acceptanceWindow);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__LISTENTIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_listenTimeout);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__PRIORITYFALLBACKCYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_priorityFallbackCycles);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SYNCTOSTABLEENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_syncToStableEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__SOURCEMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::fromAny(
                _newValue, m_sourceMacAddress);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::PCFVirtualLink_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::PCFVirtualLink_ptr > (_t0);
        ::Network_Configuration::ActiveSyncComponent::setRefPcfVlidIntegration(
                _t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean ActiveSyncComponent::eIsSet(::ecore::EInt _featureID)
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SCHEDULEDRECEIVEPIT:
        /*PROTECTED REGION ID(ActiveSyncComponenteIsSet__ActiveSyncComponentm_scheduledReceivePit) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__ACCEPTANCEWINDOW:
        /*PROTECTED REGION ID(ActiveSyncComponenteIsSet__ActiveSyncComponentm_acceptanceWindow) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__LISTENTIMEOUT:
        /*PROTECTED REGION ID(ActiveSyncComponenteIsSet__ActiveSyncComponentm_listenTimeout) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__PRIORITYFALLBACKCYCLES:
        /*PROTECTED REGION ID(ActiveSyncComponenteIsSet__ActiveSyncComponentm_priorityFallbackCycles) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_priorityFallbackCycles != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SYNCTOSTABLEENABLED:
        /*PROTECTED REGION ID(ActiveSyncComponenteIsSet__ActiveSyncComponentm_syncToStableEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncToStableEnabled != false;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__SOURCEMACADDRESS:
        /*PROTECTED REGION ID(ActiveSyncComponenteIsSet__ActiveSyncComponentm_sourceMacAddress) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION:
        return m_refPcfVlidIntegration;

    }
    throw "Error";
}

void ActiveSyncComponent::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr ActiveSyncComponent::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getActiveSyncComponent();
    return _eclass;
}

