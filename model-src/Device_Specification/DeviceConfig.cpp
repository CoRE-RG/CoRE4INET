// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/DeviceConfig.cpp
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

#include "DeviceConfig.hpp"
#include <ecore/ENamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
DeviceConfig::DeviceConfig()
/*PROTECTED REGION ID(DeviceConfigImpl__DeviceConfigImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.

/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(DeviceConfigImpl__DeviceConfigImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

DeviceConfig::~DeviceConfig()
{
}

/*PROTECTED REGION ID(DeviceConfig.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::CTMarkerType DeviceConfig::getCtMarker() const
{
    return m_ctMarker;
}

void DeviceConfig::setCtMarker(::System_Specification::CTMarkerType _ctMarker)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::CTMarkerType _old_ctMarker = m_ctMarker;
#endif
    m_ctMarker = _ctMarker;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceConfig__ctMarker(),
                _old_ctMarker,
                m_ctMarker
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::CTMarkerType DeviceConfig::getCtMask() const
{
    return m_ctMask;
}

void DeviceConfig::setCtMask(::System_Specification::CTMarkerType _ctMask)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::CTMarkerType _old_ctMask = m_ctMask;
#endif
    m_ctMask = _ctMask;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceConfig__ctMask(),
                _old_ctMask,
                m_ctMask
        );
        eNotify(&notification);
    }
#endif
}

// References

