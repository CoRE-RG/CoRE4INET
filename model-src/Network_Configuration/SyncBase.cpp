// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncBase.cpp
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

#include "SyncBase.hpp"
#include <System_Specification/NamedElement.hpp>
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
SyncBase::SyncBase()
/*PROTECTED REGION ID(SyncBaseImpl__SyncBaseImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:

    m_priorityFallbackCycles(0), m_syncToStableEnabled(false)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(SyncBaseImpl__SyncBaseImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

SyncBase::~SyncBase()
{
}

/*PROTECTED REGION ID(SyncBase.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType SyncBase::getScheduledReceivePit() const
{
    return m_scheduledReceivePit;
}

void SyncBase::setScheduledReceivePit(
        ::System_Specification::TimeType _scheduledReceivePit)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_scheduledReceivePit = m_scheduledReceivePit;
#endif
    m_scheduledReceivePit = _scheduledReceivePit;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncBase__scheduledReceivePit(),
                _old_scheduledReceivePit,
                m_scheduledReceivePit
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncBase::getAcceptanceWindow() const
{
    return m_acceptanceWindow;
}

void SyncBase::setAcceptanceWindow(
        ::System_Specification::TimeType _acceptanceWindow)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_acceptanceWindow = m_acceptanceWindow;
#endif
    m_acceptanceWindow = _acceptanceWindow;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncBase__acceptanceWindow(),
                _old_acceptanceWindow,
                m_acceptanceWindow
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType SyncBase::getListenTimeout() const
{
    return m_listenTimeout;
}

void SyncBase::setListenTimeout(::System_Specification::TimeType _listenTimeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_listenTimeout = m_listenTimeout;
#endif
    m_listenTimeout = _listenTimeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncBase__listenTimeout(),
                _old_listenTimeout,
                m_listenTimeout
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt SyncBase::getPriorityFallbackCycles() const
{
    return m_priorityFallbackCycles;
}

void SyncBase::setPriorityFallbackCycles(::ecore::EInt _priorityFallbackCycles)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_priorityFallbackCycles = m_priorityFallbackCycles;
#endif
    m_priorityFallbackCycles = _priorityFallbackCycles;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncBase__priorityFallbackCycles(),
                _old_priorityFallbackCycles,
                m_priorityFallbackCycles
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean SyncBase::isSyncToStableEnabled() const
{
    return m_syncToStableEnabled;
}

void SyncBase::setSyncToStableEnabled(::ecore::EBoolean _syncToStableEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_syncToStableEnabled = m_syncToStableEnabled;
#endif
    m_syncToStableEnabled = _syncToStableEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getSyncBase__syncToStableEnabled(),
                _old_syncToStableEnabled,
                m_syncToStableEnabled
        );
        eNotify(&notification);
    }
#endif
}

// References

