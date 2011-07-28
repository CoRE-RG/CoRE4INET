// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncDomain.cpp
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
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Network_Configuration/SyncPriority.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
SyncDomain::SyncDomain()
/*PROTECTED REGION ID(SyncDomainImpl__SyncDomainImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_syncDomainId(0)
/*PROTECTED REGION END*/
{

    m_syncPriority.reset(
            new ::ecorecpp::mapping::ReferenceEListImpl<
                    ::Network_Configuration::SyncPriority, -1, true, false >(
                    this, NULL));

    /*PROTECTED REGION ID(SyncDomainImpl__SyncDomainImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

SyncDomain::~SyncDomain()
{
}

/*PROTECTED REGION ID(SyncDomain.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EByte SyncDomain::getSyncDomainId() const
{
    return m_syncDomainId;
}

void SyncDomain::setSyncDomainId(::ecore::EByte _syncDomainId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EByte _old_syncDomainId = m_syncDomainId;
#endif
    m_syncDomainId = _syncDomainId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__syncDomainId(),
                _old_syncDomainId,
                m_syncDomainId
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncDomain::getClusterCycleDuration() const
{
    return m_clusterCycleDuration;
}

void SyncDomain::setClusterCycleDuration(
        ::System_Specification::TimeType _clusterCycleDuration)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_clusterCycleDuration = m_clusterCycleDuration;
#endif
    m_clusterCycleDuration = _clusterCycleDuration;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__clusterCycleDuration(),
                _old_clusterCycleDuration,
                m_clusterCycleDuration
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncDomain::getIntegrationCycleDuration() const
{
    return m_integrationCycleDuration;
}

void SyncDomain::setIntegrationCycleDuration(
        ::System_Specification::TimeType _integrationCycleDuration)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_integrationCycleDuration = m_integrationCycleDuration;
#endif
    m_integrationCycleDuration = _integrationCycleDuration;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__integrationCycleDuration(),
                _old_integrationCycleDuration,
                m_integrationCycleDuration
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncDomain::getMaxPcfTransmissionDelay() const
{
    return m_maxPcfTransmissionDelay;
}

void SyncDomain::setMaxPcfTransmissionDelay(
        ::System_Specification::TimeType _maxPcfTransmissionDelay)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_maxPcfTransmissionDelay = m_maxPcfTransmissionDelay;
#endif
    m_maxPcfTransmissionDelay = _maxPcfTransmissionDelay;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__maxPcfTransmissionDelay(),
                _old_maxPcfTransmissionDelay,
                m_maxPcfTransmissionDelay
        );
        eNotify(&notification);
    }
#endif
}

::Network_Configuration::FaultToleranceEnum SyncDomain::getFaultToleranceLevel() const
{
    return m_faultToleranceLevel;
}

void SyncDomain::setFaultToleranceLevel(
        ::Network_Configuration::FaultToleranceEnum _faultToleranceLevel)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Network_Configuration::FaultToleranceEnum _old_faultToleranceLevel = m_faultToleranceLevel;
#endif
    m_faultToleranceLevel = _faultToleranceLevel;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__faultToleranceLevel(),
                _old_faultToleranceLevel,
                m_faultToleranceLevel
        );
        eNotify(&notification);
    }
#endif
}

::Network_Configuration::IntegrityLevelEnum SyncDomain::getIntegrityLevel() const
{
    return m_integrityLevel;
}

void SyncDomain::setIntegrityLevel(
        ::Network_Configuration::IntegrityLevelEnum _integrityLevel)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Network_Configuration::IntegrityLevelEnum _old_integrityLevel = m_integrityLevel;
#endif
    m_integrityLevel = _integrityLevel;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__integrityLevel(),
                _old_integrityLevel,
                m_integrityLevel
        );
        eNotify(&notification);
    }
#endif
}

::Network_Configuration::AvgModeEnum SyncDomain::getAvgMode() const
{
    return m_avgMode;
}

void SyncDomain::setAvgMode(::Network_Configuration::AvgModeEnum _avgMode)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Network_Configuration::AvgModeEnum _old_avgMode = m_avgMode;
#endif
    m_avgMode = _avgMode;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncDomain__avgMode(),
                _old_avgMode,
                m_avgMode
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Network_Configuration::SyncPriority >& SyncDomain::getSyncPriority()
{
    return *m_syncPriority;
}

