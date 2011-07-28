// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/DeviceMapping.cpp
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

#include "DeviceMapping.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/TargetDevice.hpp>
#include <Device_Target_Mapping/PerPortBagAccounts.hpp>
#include <Device_Target_Mapping/PortMappings.hpp>
#include <Device_Targets/AntiMasquerading.hpp>
#include <Device_Targets/Diagnostic.hpp>
#include <Device_Target_Mapping/Trigger.hpp>
#include <Device_Target_Mapping/BufferMapping.hpp>
#include <Device_Targets/ManagementInterface.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Target_Mapping;

// Default constructor
DeviceMapping::DeviceMapping()
/*PROTECTED REGION ID(DeviceMappingImpl__DeviceMappingImplDefaults) ENABLED START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refTargetDevice(0), m_perPortBagAccounts(0), m_portMappings(0),
            m_diagnostic(0), m_bufferMapping(0), m_managementInterface(0),
            m_metaInformation(0)
/*PROTECTED REGION END*/
{

    m_antiMasquerading.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Targets::AntiMasquerading, -1, true, false >(this, NULL));
    m_trigger.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Target_Mapping::Trigger, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(DeviceMappingImpl__DeviceMappingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

DeviceMapping::~DeviceMapping()
{
    if (m_perPortBagAccounts)
    {
        delete m_perPortBagAccounts;
    }
    if (m_portMappings)
    {
        delete m_portMappings;
    }
    if (m_diagnostic)
    {
        delete m_diagnostic;
    }
    if (m_bufferMapping)
    {
        delete m_bufferMapping;
    }
    if (m_managementInterface)
    {
        delete m_managementInterface;
    }
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(DeviceMapping.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType DeviceMapping::getAgingTime() const
{
    return m_agingTime;
}

void DeviceMapping::setAgingTime(::System_Specification::TimeType _agingTime)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_agingTime = m_agingTime;
#endif
    m_agingTime = _agingTime;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__agingTime(),
                _old_agingTime,
                m_agingTime
        );
        eNotify(&notification);
    }
#endif
}

// References
::Device_Targets::TargetDevice_ptr DeviceMapping::getRefTargetDevice()
{
    return m_refTargetDevice;
}

void DeviceMapping::setRefTargetDevice(
        ::Device_Targets::TargetDevice_ptr _refTargetDevice)
{
    ::Device_Targets::TargetDevice_ptr _old_refTargetDevice = m_refTargetDevice;

    m_refTargetDevice = _refTargetDevice;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__refTargetDevice(),
                _old_refTargetDevice,
                m_refTargetDevice
        );
        eNotify(&notification);
    }
#endif

}

::Device_Target_Mapping::PerPortBagAccounts_ptr DeviceMapping::getPerPortBagAccounts()
{
    return m_perPortBagAccounts;
}

void DeviceMapping::setPerPortBagAccounts(
        ::Device_Target_Mapping::PerPortBagAccounts_ptr _perPortBagAccounts)
{
    ::Device_Target_Mapping::PerPortBagAccounts_ptr _old_perPortBagAccounts =
            m_perPortBagAccounts;

    m_perPortBagAccounts = _perPortBagAccounts;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__perPortBagAccounts(),
                _old_perPortBagAccounts,
                m_perPortBagAccounts
        );
        eNotify(&notification);
    }
#endif

    delete _old_perPortBagAccounts;
}

::Device_Target_Mapping::PortMappings_ptr DeviceMapping::getPortMappings()
{
    return m_portMappings;
}

void DeviceMapping::setPortMappings(
        ::Device_Target_Mapping::PortMappings_ptr _portMappings)
{
    ::Device_Target_Mapping::PortMappings_ptr _old_portMappings =
            m_portMappings;

    m_portMappings = _portMappings;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__portMappings(),
                _old_portMappings,
                m_portMappings
        );
        eNotify(&notification);
    }
#endif

    delete _old_portMappings;
}

::ecorecpp::mapping::EList< ::Device_Targets::AntiMasquerading >& DeviceMapping::getAntiMasquerading()
{
    return *m_antiMasquerading;
}

::Device_Targets::Diagnostic_ptr DeviceMapping::getDiagnostic()
{
    return m_diagnostic;
}

void DeviceMapping::setDiagnostic(::Device_Targets::Diagnostic_ptr _diagnostic)
{
    ::Device_Targets::Diagnostic_ptr _old_diagnostic = m_diagnostic;

    m_diagnostic = _diagnostic;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__diagnostic(),
                _old_diagnostic,
                m_diagnostic
        );
        eNotify(&notification);
    }
#endif

    delete _old_diagnostic;
}

::ecorecpp::mapping::EList< ::Device_Target_Mapping::Trigger >& DeviceMapping::getTrigger()
{
    return *m_trigger;
}

::Device_Target_Mapping::BufferMapping_ptr DeviceMapping::getBufferMapping()
{
    return m_bufferMapping;
}

void DeviceMapping::setBufferMapping(
        ::Device_Target_Mapping::BufferMapping_ptr _bufferMapping)
{
    ::Device_Target_Mapping::BufferMapping_ptr _old_bufferMapping =
            m_bufferMapping;

    m_bufferMapping = _bufferMapping;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__bufferMapping(),
                _old_bufferMapping,
                m_bufferMapping
        );
        eNotify(&notification);
    }
#endif

    delete _old_bufferMapping;
}

::Device_Targets::ManagementInterface_ptr DeviceMapping::getManagementInterface()
{
    return m_managementInterface;
}

void DeviceMapping::setManagementInterface(
        ::Device_Targets::ManagementInterface_ptr _managementInterface)
{
    ::Device_Targets::ManagementInterface_ptr _old_managementInterface =
            m_managementInterface;

    m_managementInterface = _managementInterface;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__managementInterface(),
                _old_managementInterface,
                m_managementInterface
        );
        eNotify(&notification);
    }
#endif

    delete _old_managementInterface;
}

::System_Specification::MetaInformation_ptr DeviceMapping::getMetaInformation()
{
    return m_metaInformation;
}

void DeviceMapping::setMetaInformation(
        ::System_Specification::MetaInformation_ptr _metaInformation)
{
    ::System_Specification::MetaInformation_ptr _old_metaInformation =
            m_metaInformation;

    m_metaInformation = _metaInformation;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getDeviceMapping__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

