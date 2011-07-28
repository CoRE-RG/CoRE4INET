// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/DeviceReferringElement.cpp
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

#include "DeviceReferringElement.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/DeviceSpecification.hpp>
#include <Network_Configuration/SyncBase.hpp>
#include <System_Specification/Device.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
DeviceReferringElement::DeviceReferringElement()
/*PROTECTED REGION ID(DeviceReferringElementImpl__DeviceReferringElementImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refDeviceSpecification(0), m_refSyncConfiguration(0), m_refDevice(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(DeviceReferringElementImpl__DeviceReferringElementImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

DeviceReferringElement::~DeviceReferringElement()
{
}

/*PROTECTED REGION ID(DeviceReferringElement.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Specification::DeviceSpecification_ptr DeviceReferringElement::getRefDeviceSpecification()
{
    return m_refDeviceSpecification;
}

void DeviceReferringElement::setRefDeviceSpecification(
        ::Device_Specification::DeviceSpecification_ptr _refDeviceSpecification)
{
    ::Device_Specification::DeviceSpecification_ptr
            _old_refDeviceSpecification = m_refDeviceSpecification;

    m_refDeviceSpecification = _refDeviceSpecification;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getDeviceReferringElement__refDeviceSpecification(),
                _old_refDeviceSpecification,
                m_refDeviceSpecification
        );
        eNotify(&notification);
    }
#endif

}

::Network_Configuration::SyncBase_ptr DeviceReferringElement::getRefSyncConfiguration()
{
    return m_refSyncConfiguration;
}

void DeviceReferringElement::setRefSyncConfiguration(
        ::Network_Configuration::SyncBase_ptr _refSyncConfiguration)
{
    ::Network_Configuration::SyncBase_ptr _old_refSyncConfiguration =
            m_refSyncConfiguration;

    m_refSyncConfiguration = _refSyncConfiguration;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getDeviceReferringElement__refSyncConfiguration(),
                _old_refSyncConfiguration,
                m_refSyncConfiguration
        );
        eNotify(&notification);
    }
#endif

}

::System_Specification::Device_ptr DeviceReferringElement::getRefDevice()
{
    return m_refDevice;
}

void DeviceReferringElement::setRefDevice(
        ::System_Specification::Device_ptr _refDevice)
{
    ::System_Specification::Device_ptr _old_refDevice = m_refDevice;

    m_refDevice = _refDevice;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getDeviceReferringElement__refDevice(),
                _old_refDevice,
                m_refDevice
        );
        eNotify(&notification);
    }
#endif

}

