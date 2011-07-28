// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/MacAcceptanceEntry.cpp
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

#include "MacAcceptanceEntry.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/AccessControl.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
MacAcceptanceEntry::MacAcceptanceEntry()
{

    m_accessControl.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Targets::AccessControl, 4, true, false >(this, NULL));

    /*PROTECTED REGION ID(MacAcceptanceEntryImpl__MacAcceptanceEntryImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

MacAcceptanceEntry::~MacAcceptanceEntry()
{
}

/*PROTECTED REGION ID(MacAcceptanceEntry.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::MacAddressType MacAcceptanceEntry::getAcceptanceMacAddress() const
{
    return m_acceptanceMacAddress;
}

void MacAcceptanceEntry::setAcceptanceMacAddress(
        ::System_Specification::MacAddressType _acceptanceMacAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_acceptanceMacAddress = m_acceptanceMacAddress;
#endif
    m_acceptanceMacAddress = _acceptanceMacAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getMacAcceptanceEntry__acceptanceMacAddress(),
                _old_acceptanceMacAddress,
                m_acceptanceMacAddress
        );
        eNotify(&notification);
    }
#endif
}

::Device_Targets::addressTypeEnum MacAcceptanceEntry::getAddressType() const
{
    return m_addressType;
}

void MacAcceptanceEntry::setAddressType(
        ::Device_Targets::addressTypeEnum _addressType)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Device_Targets::addressTypeEnum _old_addressType = m_addressType;
#endif
    m_addressType = _addressType;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getMacAcceptanceEntry__addressType(),
                _old_addressType,
                m_addressType
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean MacAcceptanceEntry::isUnlockEnabled() const
{
    return m_unlockEnabled;
}

void MacAcceptanceEntry::setUnlockEnabled(::ecore::EBoolean _unlockEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_unlockEnabled = m_unlockEnabled;
#endif
    m_unlockEnabled = _unlockEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getMacAcceptanceEntry__unlockEnabled(),
                _old_unlockEnabled,
                m_unlockEnabled
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean MacAcceptanceEntry::isResetEnabled() const
{
    return m_resetEnabled;
}

void MacAcceptanceEntry::setResetEnabled(::ecore::EBoolean _resetEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_resetEnabled = m_resetEnabled;
#endif
    m_resetEnabled = _resetEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getMacAcceptanceEntry__resetEnabled(),
                _old_resetEnabled,
                m_resetEnabled
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::MacAddressType MacAcceptanceEntry::getResponseDestMacAddress() const
{
    return m_responseDestMacAddress;
}

void MacAcceptanceEntry::setResponseDestMacAddress(
        ::System_Specification::MacAddressType _responseDestMacAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_responseDestMacAddress = m_responseDestMacAddress;
#endif
    m_responseDestMacAddress = _responseDestMacAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getMacAcceptanceEntry__responseDestMacAddress(),
                _old_responseDestMacAddress,
                m_responseDestMacAddress
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Device_Targets::AccessControl >& MacAcceptanceEntry::getAccessControl()
{
    return *m_accessControl;
}

