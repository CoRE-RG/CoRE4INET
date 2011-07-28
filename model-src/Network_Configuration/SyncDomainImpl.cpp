// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncDomainImpl.cpp
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

#include "SyncDomain.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncPriority.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(SyncDomainImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void SyncDomain::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_syncPriority->size(); i++)
    {
        (*m_syncPriority)[i]->_initialize();
        (*m_syncPriority)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__syncPriority());
    }

    /*PROTECTED REGION ID(SyncDomainImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject SyncDomain::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCDOMAINID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::toAny(_any,
                m_syncDomainId);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__CLUSTERCYCLEDURATION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_clusterCycleDuration);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRATIONCYCLEDURATION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_integrationCycleDuration);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__MAXPCFTRANSMISSIONDELAY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_maxPcfTransmissionDelay);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCPRIORITY:
    {
        _any = m_syncPriority->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__FAULTTOLERANCELEVEL:
    {
        ::ecorecpp::mapping::any_traits<
                ::Network_Configuration::FaultToleranceEnum >::toAny(_any,
                m_faultToleranceLevel);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRITYLEVEL:
    {
        ::ecorecpp::mapping::any_traits<
                ::Network_Configuration::IntegrityLevelEnum >::toAny(_any,
                m_integrityLevel);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__AVGMODE:
    {
        ::ecorecpp::mapping::any_traits< ::Network_Configuration::AvgModeEnum >::toAny(
                _any, m_avgMode);
    }
        return _any;

    }
    throw "Error";
}

void SyncDomain::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCDOMAINID:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::fromAny(_newValue,
                m_syncDomainId);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__CLUSTERCYCLEDURATION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_clusterCycleDuration);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRATIONCYCLEDURATION:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_integrationCycleDuration);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__MAXPCFTRANSMISSIONDELAY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_maxPcfTransmissionDelay);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCPRIORITY:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::SyncDomain::getSyncPriority().clear();
        ::Network_Configuration::SyncDomain::getSyncPriority().insert_all(*_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__FAULTTOLERANCELEVEL:
    {
        ::ecorecpp::mapping::any_traits<
                ::Network_Configuration::FaultToleranceEnum >::fromAny(
                _newValue, m_faultToleranceLevel);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRITYLEVEL:
    {
        ::ecorecpp::mapping::any_traits<
                ::Network_Configuration::IntegrityLevelEnum >::fromAny(
                _newValue, m_integrityLevel);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__AVGMODE:
    {
        ::ecorecpp::mapping::any_traits< ::Network_Configuration::AvgModeEnum >::fromAny(
                _newValue, m_avgMode);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean SyncDomain::eIsSet(::ecore::EInt _featureID)
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
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCDOMAINID:
        /*PROTECTED REGION ID(SyncDomaineIsSet__SyncDomainm_syncDomainId) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_syncDomainId != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__CLUSTERCYCLEDURATION:
        /*PROTECTED REGION ID(SyncDomaineIsSet__SyncDomainm_clusterCycleDuration) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRATIONCYCLEDURATION:
        /*PROTECTED REGION ID(SyncDomaineIsSet__SyncDomainm_integrationCycleDuration) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__MAXPCFTRANSMISSIONDELAY:
        /*PROTECTED REGION ID(SyncDomaineIsSet__SyncDomainm_maxPcfTransmissionDelay) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__SYNCPRIORITY:
        return m_syncPriority && m_syncPriority->size();
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__FAULTTOLERANCELEVEL:
        /*PROTECTED REGION ID(SyncDomaineIsSet__SyncDomainm_faultToleranceLevel) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__INTEGRITYLEVEL:
        /*PROTECTED REGION ID(SyncDomaineIsSet__SyncDomainm_integrityLevel) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::SYNCDOMAIN__AVGMODE:
        /*PROTECTED REGION ID(SyncDomaineIsSet__SyncDomainm_avgMode) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void SyncDomain::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr SyncDomain::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getSyncDomain();
    return _eclass;
}

