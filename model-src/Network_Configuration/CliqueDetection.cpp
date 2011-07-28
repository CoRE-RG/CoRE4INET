// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/CliqueDetection.cpp
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
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
CliqueDetection::CliqueDetection()
/*PROTECTED REGION ID(CliqueDetectionImpl__CliqueDetectionImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_tentativeSyncRelayEnabled(true), m_syncRelayEnabled(true),
            m_stableRelayEnabled(true), m_tentativeSyncMembershipAsyncEnabled(
                    true), m_tentativeSyncMembershipSyncEnabled(true),
            m_syncMembershipAsyncEnabled(true), m_syncMembershipSyncEnabled(
                    true), m_stableMembershipAsyncEnabled(true),
            m_stableMembershipSyncEnabled(true)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(CliqueDetectionImpl__CliqueDetectionImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

CliqueDetection::~CliqueDetection()
{
}

/*PROTECTED REGION ID(CliqueDetection.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EBoolean CliqueDetection::isTentativeSyncRelayEnabled() const
{
    return m_tentativeSyncRelayEnabled;
}

void CliqueDetection::setTentativeSyncRelayEnabled(
        ::ecore::EBoolean _tentativeSyncRelayEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_tentativeSyncRelayEnabled = m_tentativeSyncRelayEnabled;
#endif
    m_tentativeSyncRelayEnabled = _tentativeSyncRelayEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__tentativeSyncRelayEnabled(),
                _old_tentativeSyncRelayEnabled,
                m_tentativeSyncRelayEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isSyncRelayEnabled() const
{
    return m_syncRelayEnabled;
}

void CliqueDetection::setSyncRelayEnabled(::ecore::EBoolean _syncRelayEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_syncRelayEnabled = m_syncRelayEnabled;
#endif
    m_syncRelayEnabled = _syncRelayEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__syncRelayEnabled(),
                _old_syncRelayEnabled,
                m_syncRelayEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isStableRelayEnabled() const
{
    return m_stableRelayEnabled;
}

void CliqueDetection::setStableRelayEnabled(
        ::ecore::EBoolean _stableRelayEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_stableRelayEnabled = m_stableRelayEnabled;
#endif
    m_stableRelayEnabled = _stableRelayEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__stableRelayEnabled(),
                _old_stableRelayEnabled,
                m_stableRelayEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isTentativeSyncMembershipAsyncEnabled() const
{
    return m_tentativeSyncMembershipAsyncEnabled;
}

void CliqueDetection::setTentativeSyncMembershipAsyncEnabled(
        ::ecore::EBoolean _tentativeSyncMembershipAsyncEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_tentativeSyncMembershipAsyncEnabled = m_tentativeSyncMembershipAsyncEnabled;
#endif
    m_tentativeSyncMembershipAsyncEnabled
            = _tentativeSyncMembershipAsyncEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__tentativeSyncMembershipAsyncEnabled(),
                _old_tentativeSyncMembershipAsyncEnabled,
                m_tentativeSyncMembershipAsyncEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isTentativeSyncMembershipSyncEnabled() const
{
    return m_tentativeSyncMembershipSyncEnabled;
}

void CliqueDetection::setTentativeSyncMembershipSyncEnabled(
        ::ecore::EBoolean _tentativeSyncMembershipSyncEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_tentativeSyncMembershipSyncEnabled = m_tentativeSyncMembershipSyncEnabled;
#endif
    m_tentativeSyncMembershipSyncEnabled = _tentativeSyncMembershipSyncEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__tentativeSyncMembershipSyncEnabled(),
                _old_tentativeSyncMembershipSyncEnabled,
                m_tentativeSyncMembershipSyncEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isSyncMembershipAsyncEnabled() const
{
    return m_syncMembershipAsyncEnabled;
}

void CliqueDetection::setSyncMembershipAsyncEnabled(
        ::ecore::EBoolean _syncMembershipAsyncEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_syncMembershipAsyncEnabled = m_syncMembershipAsyncEnabled;
#endif
    m_syncMembershipAsyncEnabled = _syncMembershipAsyncEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__syncMembershipAsyncEnabled(),
                _old_syncMembershipAsyncEnabled,
                m_syncMembershipAsyncEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isSyncMembershipSyncEnabled() const
{
    return m_syncMembershipSyncEnabled;
}

void CliqueDetection::setSyncMembershipSyncEnabled(
        ::ecore::EBoolean _syncMembershipSyncEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_syncMembershipSyncEnabled = m_syncMembershipSyncEnabled;
#endif
    m_syncMembershipSyncEnabled = _syncMembershipSyncEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__syncMembershipSyncEnabled(),
                _old_syncMembershipSyncEnabled,
                m_syncMembershipSyncEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isStableMembershipAsyncEnabled() const
{
    return m_stableMembershipAsyncEnabled;
}

void CliqueDetection::setStableMembershipAsyncEnabled(
        ::ecore::EBoolean _stableMembershipAsyncEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_stableMembershipAsyncEnabled = m_stableMembershipAsyncEnabled;
#endif
    m_stableMembershipAsyncEnabled = _stableMembershipAsyncEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__stableMembershipAsyncEnabled(),
                _old_stableMembershipAsyncEnabled,
                m_stableMembershipAsyncEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean CliqueDetection::isStableMembershipSyncEnabled() const
{
    return m_stableMembershipSyncEnabled;
}

void CliqueDetection::setStableMembershipSyncEnabled(
        ::ecore::EBoolean _stableMembershipSyncEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_stableMembershipSyncEnabled = m_stableMembershipSyncEnabled;
#endif
    m_stableMembershipSyncEnabled = _stableMembershipSyncEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getCliqueDetection__stableMembershipSyncEnabled(),
                _old_stableMembershipSyncEnabled,
                m_stableMembershipSyncEnabled
        );
        eNotify(&notification);
    }
#endif
}

// References

