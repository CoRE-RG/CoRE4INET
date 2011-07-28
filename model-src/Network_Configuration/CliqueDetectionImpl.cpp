// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/CliqueDetectionImpl.cpp
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

#include "CliqueDetection.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(CliqueDetectionImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void CliqueDetection::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(CliqueDetectionImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject CliqueDetection::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCRELAYENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_tentativeSyncRelayEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCRELAYENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_syncRelayEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLERELAYENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_stableRelayEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPASYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_tentativeSyncMembershipAsyncEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPSYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_tentativeSyncMembershipSyncEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPASYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_syncMembershipAsyncEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPSYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_syncMembershipSyncEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPASYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_stableMembershipAsyncEnabled);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPSYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_stableMembershipSyncEnabled);
    }
        return _any;

    }
    throw "Error";
}

void CliqueDetection::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCRELAYENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_tentativeSyncRelayEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCRELAYENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_syncRelayEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLERELAYENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_stableRelayEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPASYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_tentativeSyncMembershipAsyncEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPSYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_tentativeSyncMembershipSyncEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPASYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_syncMembershipAsyncEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPSYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_syncMembershipSyncEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPASYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_stableMembershipAsyncEnabled);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPSYNCENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_stableMembershipSyncEnabled);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean CliqueDetection::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCRELAYENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_tentativeSyncRelayEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_tentativeSyncRelayEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCRELAYENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_syncRelayEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncRelayEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLERELAYENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_stableRelayEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_stableRelayEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPASYNCENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_tentativeSyncMembershipAsyncEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_tentativeSyncMembershipAsyncEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPSYNCENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_tentativeSyncMembershipSyncEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_tentativeSyncMembershipSyncEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPASYNCENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_syncMembershipAsyncEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncMembershipAsyncEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__SYNCMEMBERSHIPSYNCENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_syncMembershipSyncEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncMembershipSyncEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPASYNCENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_stableMembershipAsyncEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_stableMembershipAsyncEnabled != true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::CLIQUEDETECTION__STABLEMEMBERSHIPSYNCENABLED:
        /*PROTECTED REGION ID(CliqueDetectioneIsSet__CliqueDetectionm_stableMembershipSyncEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_stableMembershipSyncEnabled != true;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void CliqueDetection::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr CliqueDetection::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getCliqueDetection();
    return _eclass;
}

