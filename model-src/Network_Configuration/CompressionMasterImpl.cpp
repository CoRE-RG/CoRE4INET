// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/CompressionMasterImpl.cpp
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

#include "CompressionMaster.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <Network_Configuration/ActiveSyncComponent.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/PCFVirtualLink.hpp>
#include <Network_Configuration/BusGuardian.hpp>
#include <Network_Configuration/CliqueDetection.hpp>
#include <Network_Configuration/CompressionMasterIntegrityConfig.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(CompressionMasterImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void CompressionMaster::_initialize()
{
    // Supertypes
    ::Network_Configuration::ActiveSyncComponent::_initialize();

    // Rerefences
    if (m_busGuardian)
    {
        m_busGuardian->_initialize();
        m_busGuardian->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__busGuardian());
    }
    if (m_cliqueDetection)
    {
        m_cliqueDetection->_initialize();
        m_cliqueDetection->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCompressionMaster__cliqueDetection());
    }

    /*PROTECTED REGION ID(CompressionMasterImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject CompressionMaster::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__BUSGUARDIAN:
    {
        _any = static_cast< ::ecore::EObject* > (m_busGuardian);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CLIQUEDETECTION:
    {
        _any = static_cast< ::ecore::EObject* > (m_cliqueDetection);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__OBSERVATIONWINDOWSIZE:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_observationWindowSize);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CAENABLETIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_caEnableTimeout);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__WAIT4IN0TIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_wait4in0Timeout);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__REFINTEGRITYCONFIG:
    {
        _any = static_cast< ::ecore::EObject* > (m_refIntegrityConfig);
    }
        return _any;

    }
    throw "Error";
}

void CompressionMaster::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__BUSGUARDIAN:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Network_Configuration::BusGuardian_ptr _t1 =
                dynamic_cast< ::Network_Configuration::BusGuardian_ptr > (_t0);
        ::Network_Configuration::CompressionMaster::setBusGuardian(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CLIQUEDETECTION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Network_Configuration::CliqueDetection_ptr
                _t1 =
                        dynamic_cast< ::Network_Configuration::CliqueDetection_ptr > (_t0);
        ::Network_Configuration::CompressionMaster::setCliqueDetection(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__OBSERVATIONWINDOWSIZE:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_observationWindowSize);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CAENABLETIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_caEnableTimeout);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__WAIT4IN0TIMEOUT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_wait4in0Timeout);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__REFINTEGRITYCONFIG:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Network_Configuration::CompressionMasterIntegrityConfig_ptr
                _t1 =
                        dynamic_cast< ::Network_Configuration::CompressionMasterIntegrityConfig_ptr > (_t0);
        ::Network_Configuration::CompressionMaster::setRefIntegrityConfig(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean CompressionMaster::eIsSet(::ecore::EInt _featureID)
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
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_scheduledReceivePit) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__ACCEPTANCEWINDOW:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_acceptanceWindow) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__LISTENTIMEOUT:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_listenTimeout) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__PRIORITYFALLBACKCYCLES:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_priorityFallbackCycles) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_priorityFallbackCycles != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCBASE__SYNCTOSTABLEENABLED:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_syncToStableEnabled) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncToStableEnabled != false;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__SOURCEMACADDRESS:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_sourceMacAddress) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
    return m_sourceMacAddress != "00:00:00:00:00:00";
    /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION:
        return m_refPcfVlidIntegration;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__BUSGUARDIAN:
        return m_busGuardian;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CLIQUEDETECTION:
        return m_cliqueDetection;
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__OBSERVATIONWINDOWSIZE:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_observationWindowSize) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__CAENABLETIMEOUT:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_caEnableTimeout) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__WAIT4IN0TIMEOUT:
        /*PROTECTED REGION ID(CompressionMastereIsSet__CompressionMasterm_wait4in0Timeout) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::COMPRESSIONMASTER__REFINTEGRITYCONFIG:
        return m_refIntegrityConfig;

    }
    throw "Error";
}

void CompressionMaster::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr CompressionMaster::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getCompressionMaster();
    return _eclass;
}

