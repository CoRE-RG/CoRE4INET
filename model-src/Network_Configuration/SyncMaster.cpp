// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncMaster.cpp
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

#include "SyncMaster.hpp"
#include <Network_Configuration/ActiveSyncComponent.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/PCFVirtualLink.hpp>
#include <Network_Configuration/SyncMasterIntegrityConfig.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
SyncMaster::SyncMaster()
/*PROTECTED REGION ID(SyncMasterImpl__SyncMasterImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_membershipBit(0), m_initialIntegrationCycle(0), m_clksyncFilterMax(0),
            m_refIntegrityConfig(0), m_refPcfVlidColdstart(0),
            m_refPcfVlidColdstartAck(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(SyncMasterImpl__SyncMasterImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

SyncMaster::~SyncMaster()
{
}

/*PROTECTED REGION ID(SyncMaster.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EByte SyncMaster::getMembershipBit() const
{
    return m_membershipBit;
}

void SyncMaster::setMembershipBit(::ecore::EByte _membershipBit)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EByte _old_membershipBit = m_membershipBit;
#endif
    m_membershipBit = _membershipBit;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__membershipBit(),
                _old_membershipBit,
                m_membershipBit
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt SyncMaster::getInitialIntegrationCycle() const
{
    return m_initialIntegrationCycle;
}

void SyncMaster::setInitialIntegrationCycle(
        ::ecore::EInt _initialIntegrationCycle)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_initialIntegrationCycle = m_initialIntegrationCycle;
#endif
    m_initialIntegrationCycle = _initialIntegrationCycle;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__initialIntegrationCycle(),
                _old_initialIntegrationCycle,
                m_initialIntegrationCycle
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncMaster::getCaOffset() const
{
    return m_caOffset;
}

void SyncMaster::setCaOffset(::System_Specification::TimeType _caOffset)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_caOffset = m_caOffset;
#endif
    m_caOffset = _caOffset;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__caOffset(),
                _old_caOffset,
                m_caOffset
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncMaster::getColdstartTimeout() const
{
    return m_coldstartTimeout;
}

void SyncMaster::setColdstartTimeout(
        ::System_Specification::TimeType _coldstartTimeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_coldstartTimeout = m_coldstartTimeout;
#endif
    m_coldstartTimeout = _coldstartTimeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__coldstartTimeout(),
                _old_coldstartTimeout,
                m_coldstartTimeout
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncMaster::getCsOffset() const
{
    return m_csOffset;
}

void SyncMaster::setCsOffset(::System_Specification::TimeType _csOffset)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_csOffset = m_csOffset;
#endif
    m_csOffset = _csOffset;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__csOffset(),
                _old_csOffset,
                m_csOffset
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncMaster::getRestartTimeoutAsync() const
{
    return m_restartTimeoutAsync;
}

void SyncMaster::setRestartTimeoutAsync(
        ::System_Specification::TimeType _restartTimeoutAsync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_restartTimeoutAsync = m_restartTimeoutAsync;
#endif
    m_restartTimeoutAsync = _restartTimeoutAsync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__restartTimeoutAsync(),
                _old_restartTimeoutAsync,
                m_restartTimeoutAsync
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncMaster::getRestartTimeoutSync() const
{
    return m_restartTimeoutSync;
}

void SyncMaster::setRestartTimeoutSync(
        ::System_Specification::TimeType _restartTimeoutSync)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_restartTimeoutSync = m_restartTimeoutSync;
#endif
    m_restartTimeoutSync = _restartTimeoutSync;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__restartTimeoutSync(),
                _old_restartTimeoutSync,
                m_restartTimeoutSync
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt SyncMaster::getClksyncFilterMax() const
{
    return m_clksyncFilterMax;
}

void SyncMaster::setClksyncFilterMax(::ecore::EInt _clksyncFilterMax)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_clksyncFilterMax = m_clksyncFilterMax;
#endif
    m_clksyncFilterMax = _clksyncFilterMax;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__clksyncFilterMax(),
                _old_clksyncFilterMax,
                m_clksyncFilterMax
        );
        eNotify(&notification);
    }
#endif
}

// References
::Network_Configuration::SyncMasterIntegrityConfig_ptr SyncMaster::getRefIntegrityConfig()
{
    return m_refIntegrityConfig;
}

void SyncMaster::setRefIntegrityConfig(
        ::Network_Configuration::SyncMasterIntegrityConfig_ptr _refIntegrityConfig)
{
    ::Network_Configuration::SyncMasterIntegrityConfig_ptr
            _old_refIntegrityConfig = m_refIntegrityConfig;

    m_refIntegrityConfig = _refIntegrityConfig;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__refIntegrityConfig(),
                _old_refIntegrityConfig,
                m_refIntegrityConfig
        );
        eNotify(&notification);
    }
#endif

}

::System_Specification::PCFVirtualLink_ptr SyncMaster::getRefPcfVlidColdstart()
{
    return m_refPcfVlidColdstart;
}

void SyncMaster::setRefPcfVlidColdstart(
        ::System_Specification::PCFVirtualLink_ptr _refPcfVlidColdstart)
{
    ::System_Specification::PCFVirtualLink_ptr _old_refPcfVlidColdstart =
            m_refPcfVlidColdstart;

    m_refPcfVlidColdstart = _refPcfVlidColdstart;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__refPcfVlidColdstart(),
                _old_refPcfVlidColdstart,
                m_refPcfVlidColdstart
        );
        eNotify(&notification);
    }
#endif

}

::System_Specification::PCFVirtualLink_ptr SyncMaster::getRefPcfVlidColdstartAck()
{
    return m_refPcfVlidColdstartAck;
}

void SyncMaster::setRefPcfVlidColdstartAck(
        ::System_Specification::PCFVirtualLink_ptr _refPcfVlidColdstartAck)
{
    ::System_Specification::PCFVirtualLink_ptr _old_refPcfVlidColdstartAck =
            m_refPcfVlidColdstartAck;

    m_refPcfVlidColdstartAck = _refPcfVlidColdstartAck;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncMaster__refPcfVlidColdstartAck(),
                _old_refPcfVlidColdstartAck,
                m_refPcfVlidColdstartAck
        );
        eNotify(&notification);
    }
#endif

}

