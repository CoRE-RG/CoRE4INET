// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/ManagementInterface.cpp
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

#include "ManagementInterface.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/MacAcceptanceEntry.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
ManagementInterface::ManagementInterface()
/*PROTECTED REGION ID(ManagementInterfaceImpl__ManagementInterfaceImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_configurationVersion(10), m_expectedUnlocks(4), m_expectedResets(4)
/*PROTECTED REGION END*/
{

    m_macAcceptanceEntry.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Targets::MacAcceptanceEntry, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(ManagementInterfaceImpl__ManagementInterfaceImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

ManagementInterface::~ManagementInterface()
{
}

/*PROTECTED REGION ID(ManagementInterface.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt ManagementInterface::getConfigurationVersion() const
{
    return m_configurationVersion;
}

void ManagementInterface::setConfigurationVersion(
        ::ecore::EInt _configurationVersion)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_configurationVersion = m_configurationVersion;
#endif
    m_configurationVersion = _configurationVersion;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__configurationVersion(),
                _old_configurationVersion,
                m_configurationVersion
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::SpeedEnum ManagementInterface::getSpeed() const
{
    return m_speed;
}

void ManagementInterface::setSpeed(::System_Specification::SpeedEnum _speed)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::SpeedEnum _old_speed = m_speed;
#endif
    m_speed = _speed;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__speed(),
                _old_speed,
                m_speed
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType ManagementInterface::getUnlockWrTimeout() const
{
    return m_unlockWrTimeout;
}

void ManagementInterface::setUnlockWrTimeout(
        ::System_Specification::TimeType _unlockWrTimeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_unlockWrTimeout = m_unlockWrTimeout;
#endif
    m_unlockWrTimeout = _unlockWrTimeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__unlockWrTimeout(),
                _old_unlockWrTimeout,
                m_unlockWrTimeout
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType ManagementInterface::getResetTimeout() const
{
    return m_resetTimeout;
}

void ManagementInterface::setResetTimeout(
        ::System_Specification::TimeType _resetTimeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_resetTimeout = m_resetTimeout;
#endif
    m_resetTimeout = _resetTimeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__resetTimeout(),
                _old_resetTimeout,
                m_resetTimeout
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::MacAddressType ManagementInterface::getUnlockDestAddress() const
{
    return m_unlockDestAddress;
}

void ManagementInterface::setUnlockDestAddress(
        ::System_Specification::MacAddressType _unlockDestAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_unlockDestAddress = m_unlockDestAddress;
#endif
    m_unlockDestAddress = _unlockDestAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__unlockDestAddress(),
                _old_unlockDestAddress,
                m_unlockDestAddress
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::MacAddressType ManagementInterface::getSchedDiagDestAddress() const
{
    return m_schedDiagDestAddress;
}

void ManagementInterface::setSchedDiagDestAddress(
        ::System_Specification::MacAddressType _schedDiagDestAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_schedDiagDestAddress = m_schedDiagDestAddress;
#endif
    m_schedDiagDestAddress = _schedDiagDestAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__schedDiagDestAddress(),
                _old_schedDiagDestAddress,
                m_schedDiagDestAddress
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::MacAddressType ManagementInterface::getSourceAddress() const
{
    return m_sourceAddress;
}

void ManagementInterface::setSourceAddress(
        ::System_Specification::MacAddressType _sourceAddress)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MacAddressType _old_sourceAddress = m_sourceAddress;
#endif
    m_sourceAddress = _sourceAddress;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__sourceAddress(),
                _old_sourceAddress,
                m_sourceAddress
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EByte ManagementInterface::getExpectedUnlocks() const
{
    return m_expectedUnlocks;
}

void ManagementInterface::setExpectedUnlocks(::ecore::EByte _expectedUnlocks)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EByte _old_expectedUnlocks = m_expectedUnlocks;
#endif
    m_expectedUnlocks = _expectedUnlocks;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__expectedUnlocks(),
                _old_expectedUnlocks,
                m_expectedUnlocks
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EByte ManagementInterface::getExpectedResets() const
{
    return m_expectedResets;
}

void ManagementInterface::setExpectedResets(::ecore::EByte _expectedResets)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EByte _old_expectedResets = m_expectedResets;
#endif
    m_expectedResets = _expectedResets;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__expectedResets(),
                _old_expectedResets,
                m_expectedResets
        );
        eNotify(&notification);
    }
#endif
}

::Device_Targets::diagnosisScheduleModeEnum ManagementInterface::getDiagnosisScheduleMode() const
{
    return m_diagnosisScheduleMode;
}

void ManagementInterface::setDiagnosisScheduleMode(
        ::Device_Targets::diagnosisScheduleModeEnum _diagnosisScheduleMode)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Device_Targets::diagnosisScheduleModeEnum _old_diagnosisScheduleMode = m_diagnosisScheduleMode;
#endif
    m_diagnosisScheduleMode = _diagnosisScheduleMode;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__diagnosisScheduleMode(),
                _old_diagnosisScheduleMode,
                m_diagnosisScheduleMode
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType ManagementInterface::getApbTimeout() const
{
    return m_apbTimeout;
}

void ManagementInterface::setApbTimeout(
        ::System_Specification::TimeType _apbTimeout)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_apbTimeout = m_apbTimeout;
#endif
    m_apbTimeout = _apbTimeout;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getManagementInterface__apbTimeout(),
                _old_apbTimeout,
                m_apbTimeout
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::Device_Targets::MacAcceptanceEntry >& ManagementInterface::getMacAcceptanceEntry()
{
    return *m_macAcceptanceEntry;
}

