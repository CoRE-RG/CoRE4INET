// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/EndSystemConfig.cpp
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

#include "EndSystemConfig.hpp"
#include <Device_Specification/DeviceConfig.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/ExternalClockSynchronization.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
EndSystemConfig::EndSystemConfig()
/*PROTECTED REGION ID(EndSystemConfigImpl__EndSystemConfigImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_externalSyncAckRequired(false), m_externalClockSynchronization(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(EndSystemConfigImpl__EndSystemConfigImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

EndSystemConfig::~EndSystemConfig()
{
    if (m_externalClockSynchronization)
    {
        delete m_externalClockSynchronization;
    }
}

/*PROTECTED REGION ID(EndSystemConfig.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::Device_Specification::TimeSourceEnum EndSystemConfig::getTsSource() const
{
    return m_tsSource;
}

void EndSystemConfig::setTsSource(
        ::Device_Specification::TimeSourceEnum _tsSource)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Device_Specification::TimeSourceEnum _old_tsSource = m_tsSource;
#endif
    m_tsSource = _tsSource;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystemConfig__tsSource(),
                _old_tsSource,
                m_tsSource
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::MacAddressType EndSystemConfig::getSourceMacAddress() const
{
    return m_sourceMacAddress;
}

void EndSystemConfig::setSourceMacAddress(
        ::System_Specification::MacAddressType _sourceMacAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_sourceMacAddress = m_sourceMacAddress;
#endif
    m_sourceMacAddress = _sourceMacAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystemConfig__sourceMacAddress(),
                _old_sourceMacAddress,
                m_sourceMacAddress
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::CTMarkerType EndSystemConfig::getDestMacAddressCF() const
{
    return m_destMacAddressCF;
}

void EndSystemConfig::setDestMacAddressCF(
        ::System_Specification::CTMarkerType _destMacAddressCF)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::CTMarkerType _old_destMacAddressCF = m_destMacAddressCF;
#endif
    m_destMacAddressCF = _destMacAddressCF;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystemConfig__destMacAddressCF(),
                _old_destMacAddressCF,
                m_destMacAddressCF
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean EndSystemConfig::isExternalSyncAckRequired() const
{
    return m_externalSyncAckRequired;
}

void EndSystemConfig::setExternalSyncAckRequired(
        ::ecore::EBoolean _externalSyncAckRequired)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_externalSyncAckRequired = m_externalSyncAckRequired;
#endif
    m_externalSyncAckRequired = _externalSyncAckRequired;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystemConfig__externalSyncAckRequired(),
                _old_externalSyncAckRequired,
                m_externalSyncAckRequired
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Specification::ExternalClockSynchronization_ptr EndSystemConfig::getExternalClockSynchronization()
{
    return m_externalClockSynchronization;
}

void EndSystemConfig::setExternalClockSynchronization(
        ::Device_Specification::ExternalClockSynchronization_ptr _externalClockSynchronization)
{
    ::Device_Specification::ExternalClockSynchronization_ptr
            _old_externalClockSynchronization = m_externalClockSynchronization;

    m_externalClockSynchronization = _externalClockSynchronization;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystemConfig__externalClockSynchronization(),
                _old_externalClockSynchronization,
                m_externalClockSynchronization
        );
        eNotify(&notification);
    }
#endif

    delete _old_externalClockSynchronization;
}

