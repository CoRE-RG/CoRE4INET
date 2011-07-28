// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TTTechIpTargetDevice.cpp
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

#include "TTTechIpTargetDevice.hpp"
#include <Device_Targets/TargetDevice.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <IP_Configuration/Implementation.hpp>
#include <Device_Targets/TargetPorts.hpp>
#include <ecore/EStringToStringMapEntry.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Targets/Device_TargetsPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Targets;

// Default constructor
TTTechIpTargetDevice::TTTechIpTargetDevice()
/*PROTECTED REGION ID(TTTechIpTargetDeviceImpl__TTTechIpTargetDeviceImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_mediaControlEnabled(false)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(TTTechIpTargetDeviceImpl__TTTechIpTargetDeviceImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTTechIpTargetDevice::~TTTechIpTargetDevice()
{
}

/*PROTECTED REGION ID(TTTechIpTargetDevice.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::Device_Target_Mapping::FrequencyType TTTechIpTargetDevice::getClockSpeed() const
{
    return m_clockSpeed;
}

void TTTechIpTargetDevice::setClockSpeed(
        ::Device_Target_Mapping::FrequencyType _clockSpeed)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::Device_Target_Mapping::FrequencyType _old_clockSpeed = m_clockSpeed;
#endif
    m_clockSpeed = _clockSpeed;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTTTechIpTargetDevice__clockSpeed(),
                _old_clockSpeed,
                m_clockSpeed
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EBoolean TTTechIpTargetDevice::isMediaControlEnabled() const
{
    return m_mediaControlEnabled;
}

void TTTechIpTargetDevice::setMediaControlEnabled(
        ::ecore::EBoolean _mediaControlEnabled)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EBoolean _old_mediaControlEnabled = m_mediaControlEnabled;
#endif
    m_mediaControlEnabled = _mediaControlEnabled;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTTTechIpTargetDevice__mediaControlEnabled(),
                _old_mediaControlEnabled,
                m_mediaControlEnabled
        );
        eNotify(&notification);
    }
#endif
}

// References

