// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/ActiveSyncComponentIntegrityConfigImpl.cpp
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

#include "ActiveSyncComponentIntegrityConfig.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <Network_Configuration/IntegrityConfigBase.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void ActiveSyncComponentIntegrityConfig::_initialize()
{
    // Supertypes
    ::Network_Configuration::IntegrityConfigBase::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject ActiveSyncComponentIntegrityConfig::eGet(
        ::ecore::EInt _featureID, ::ecore::EBoolean _resolve)
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_integrateToSyncThreshold);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numUnstableCycles);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numStableCycles);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__WAITTHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_waitThresholdAsync);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_unsyncToSyncThreshold);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_unsyncToTentativeThreshold);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_tentativeSyncThresholdAsync);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_tentativeSyncThresholdSync);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_tentativeToSyncThreshold);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_syncThresholdAsync);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_syncThresholdSync);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_stableThresholdAsync);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_stableThresholdSync);
    }
        return _any;

    }
    throw "Error";
}

void ActiveSyncComponentIntegrityConfig::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_integrateToSyncThreshold);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numUnstableCycles);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numStableCycles);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__WAITTHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_waitThresholdAsync);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_unsyncToSyncThreshold);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_unsyncToTentativeThreshold);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_tentativeSyncThresholdAsync);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_tentativeSyncThresholdSync);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_tentativeToSyncThreshold);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_syncThresholdAsync);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_syncThresholdSync);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDASYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_stableThresholdAsync);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_stableThresholdSync);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean ActiveSyncComponentIntegrityConfig::eIsSet(
        ::ecore::EInt _featureID)
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_integrateToSyncThreshold) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_integrateToSyncThreshold != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_numUnstableCycles) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numUnstableCycles != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMSTABLECYCLES:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_numStableCycles) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numStableCycles != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__WAITTHRESHOLDASYNC:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_waitThresholdAsync) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_waitThresholdAsync != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_unsyncToSyncThreshold) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_unsyncToSyncThreshold != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_unsyncToTentativeThreshold) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_unsyncToTentativeThreshold != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_tentativeSyncThresholdAsync) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_tentativeSyncThresholdAsync != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_tentativeSyncThresholdSync) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_tentativeSyncThresholdSync != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_tentativeToSyncThreshold) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_tentativeToSyncThreshold != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDASYNC:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_syncThresholdAsync) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncThresholdAsync != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDSYNC:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_syncThresholdSync) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncThresholdSync != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDASYNC:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_stableThresholdAsync) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_stableThresholdAsync != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDSYNC:
        /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigeIsSet__ActiveSyncComponentIntegrityConfigm_stableThresholdSync) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_stableThresholdSync != 0;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void ActiveSyncComponentIntegrityConfig::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr ActiveSyncComponentIntegrityConfig::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getActiveSyncComponentIntegrityConfig();
    return _eclass;
}

