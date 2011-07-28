// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/ActiveSyncComponentIntegrityConfig.cpp
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
#include <Network_Configuration/IntegrityConfigBase.hpp>
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
ActiveSyncComponentIntegrityConfig::ActiveSyncComponentIntegrityConfig()
/*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigImpl__ActiveSyncComponentIntegrityConfigImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_waitThresholdAsync(0), m_unsyncToSyncThreshold(0),
            m_unsyncToTentativeThreshold(0), m_tentativeSyncThresholdAsync(0),
            m_tentativeSyncThresholdSync(0), m_tentativeToSyncThreshold(0),
            m_syncThresholdAsync(0), m_syncThresholdSync(0),
            m_stableThresholdAsync(0), m_stableThresholdSync(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfigImpl__ActiveSyncComponentIntegrityConfigImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

ActiveSyncComponentIntegrityConfig::~ActiveSyncComponentIntegrityConfig()
{
}

/*PROTECTED REGION ID(ActiveSyncComponentIntegrityConfig.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt ActiveSyncComponentIntegrityConfig::getWaitThresholdAsync() const
{
    return m_waitThresholdAsync;
}

void ActiveSyncComponentIntegrityConfig::setWaitThresholdAsync(
        ::ecore::EInt _waitThresholdAsync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_waitThresholdAsync = m_waitThresholdAsync;
#endif
    m_waitThresholdAsync = _waitThresholdAsync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__waitThresholdAsync(),
                _old_waitThresholdAsync,
                m_waitThresholdAsync
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getUnsyncToSyncThreshold() const
{
    return m_unsyncToSyncThreshold;
}

void ActiveSyncComponentIntegrityConfig::setUnsyncToSyncThreshold(
        ::ecore::EInt _unsyncToSyncThreshold)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_unsyncToSyncThreshold = m_unsyncToSyncThreshold;
#endif
    m_unsyncToSyncThreshold = _unsyncToSyncThreshold;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold(),
                _old_unsyncToSyncThreshold,
                m_unsyncToSyncThreshold
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getUnsyncToTentativeThreshold() const
{
    return m_unsyncToTentativeThreshold;
}

void ActiveSyncComponentIntegrityConfig::setUnsyncToTentativeThreshold(
        ::ecore::EInt _unsyncToTentativeThreshold)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_unsyncToTentativeThreshold = m_unsyncToTentativeThreshold;
#endif
    m_unsyncToTentativeThreshold = _unsyncToTentativeThreshold;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold(),
                _old_unsyncToTentativeThreshold,
                m_unsyncToTentativeThreshold
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getTentativeSyncThresholdAsync() const
{
    return m_tentativeSyncThresholdAsync;
}

void ActiveSyncComponentIntegrityConfig::setTentativeSyncThresholdAsync(
        ::ecore::EInt _tentativeSyncThresholdAsync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_tentativeSyncThresholdAsync = m_tentativeSyncThresholdAsync;
#endif
    m_tentativeSyncThresholdAsync = _tentativeSyncThresholdAsync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync(),
                _old_tentativeSyncThresholdAsync,
                m_tentativeSyncThresholdAsync
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getTentativeSyncThresholdSync() const
{
    return m_tentativeSyncThresholdSync;
}

void ActiveSyncComponentIntegrityConfig::setTentativeSyncThresholdSync(
        ::ecore::EInt _tentativeSyncThresholdSync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_tentativeSyncThresholdSync = m_tentativeSyncThresholdSync;
#endif
    m_tentativeSyncThresholdSync = _tentativeSyncThresholdSync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync(),
                _old_tentativeSyncThresholdSync,
                m_tentativeSyncThresholdSync
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getTentativeToSyncThreshold() const
{
    return m_tentativeToSyncThreshold;
}

void ActiveSyncComponentIntegrityConfig::setTentativeToSyncThreshold(
        ::ecore::EInt _tentativeToSyncThreshold)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_tentativeToSyncThreshold = m_tentativeToSyncThreshold;
#endif
    m_tentativeToSyncThreshold = _tentativeToSyncThreshold;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold(),
                _old_tentativeToSyncThreshold,
                m_tentativeToSyncThreshold
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getSyncThresholdAsync() const
{
    return m_syncThresholdAsync;
}

void ActiveSyncComponentIntegrityConfig::setSyncThresholdAsync(
        ::ecore::EInt _syncThresholdAsync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_syncThresholdAsync = m_syncThresholdAsync;
#endif
    m_syncThresholdAsync = _syncThresholdAsync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__syncThresholdAsync(),
                _old_syncThresholdAsync,
                m_syncThresholdAsync
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getSyncThresholdSync() const
{
    return m_syncThresholdSync;
}

void ActiveSyncComponentIntegrityConfig::setSyncThresholdSync(
        ::ecore::EInt _syncThresholdSync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_syncThresholdSync = m_syncThresholdSync;
#endif
    m_syncThresholdSync = _syncThresholdSync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__syncThresholdSync(),
                _old_syncThresholdSync,
                m_syncThresholdSync
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getStableThresholdAsync() const
{
    return m_stableThresholdAsync;
}

void ActiveSyncComponentIntegrityConfig::setStableThresholdAsync(
        ::ecore::EInt _stableThresholdAsync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_stableThresholdAsync = m_stableThresholdAsync;
#endif
    m_stableThresholdAsync = _stableThresholdAsync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__stableThresholdAsync(),
                _old_stableThresholdAsync,
                m_stableThresholdAsync
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt ActiveSyncComponentIntegrityConfig::getStableThresholdSync() const
{
    return m_stableThresholdSync;
}

void ActiveSyncComponentIntegrityConfig::setStableThresholdSync(
        ::ecore::EInt _stableThresholdSync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_stableThresholdSync = m_stableThresholdSync;
#endif
    m_stableThresholdSync = _stableThresholdSync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getActiveSyncComponentIntegrityConfig__stableThresholdSync(),
                _old_stableThresholdSync,
                m_stableThresholdSync
        );
        eNotify(&notification);
    }
#endif
}

// References

