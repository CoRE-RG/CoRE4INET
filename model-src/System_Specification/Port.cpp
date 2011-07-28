// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/Port.cpp
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

#include "Port.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Device.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
Port::Port()
/*PROTECTED REGION ID(PortImpl__PortImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_device(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(PortImpl__PortImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Port::~Port()
{
}

/*PROTECTED REGION ID(Port.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::SpeedEnum Port::getTransmissionSpeed() const
{
    return m_transmissionSpeed;
}

void Port::setTransmissionSpeed(
        ::System_Specification::SpeedEnum _transmissionSpeed)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::SpeedEnum _old_transmissionSpeed = m_transmissionSpeed;
#endif
    m_transmissionSpeed = _transmissionSpeed;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getPort__transmissionSpeed(),
                _old_transmissionSpeed,
                m_transmissionSpeed
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType Port::getStaticRxDelay() const
{
    return m_staticRxDelay;
}

void Port::setStaticRxDelay(::System_Specification::TimeType _staticRxDelay)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_staticRxDelay = m_staticRxDelay;
#endif
    m_staticRxDelay = _staticRxDelay;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getPort__staticRxDelay(),
                _old_staticRxDelay,
                m_staticRxDelay
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType Port::getStaticTxDelay() const
{
    return m_staticTxDelay;
}

void Port::setStaticTxDelay(::System_Specification::TimeType _staticTxDelay)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_staticTxDelay = m_staticTxDelay;
#endif
    m_staticTxDelay = _staticTxDelay;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getPort__staticTxDelay(),
                _old_staticTxDelay,
                m_staticTxDelay
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::MediaType Port::getMediaType() const
{
    return m_mediaType;
}

void Port::setMediaType(::System_Specification::MediaType _mediaType)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::MediaType _old_mediaType = m_mediaType;
#endif
    m_mediaType = _mediaType;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getPort__mediaType(),
                _old_mediaType,
                m_mediaType
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::Device_ptr Port::getDevice()
{
    return m_device;
}

void Port::setDevice(::System_Specification::Device_ptr _device)
{
    ::System_Specification::Device_ptr _old_device = m_device;

    m_device = _device;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getPort__device(),
                _old_device,
                m_device
        );
        eNotify(&notification);
    }
#endif

}

