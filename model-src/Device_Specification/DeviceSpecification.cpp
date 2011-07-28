// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/DeviceSpecification.cpp
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

#include "DeviceSpecification.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <Device_Specification/BagAccounts.hpp>
#include <Device_Specification/VirtualLinkSchedules.hpp>
#include <Device_Specification/BestEffortRouting.hpp>
#include <Device_Specification/FlowControl.hpp>
#include <Device_Specification/Periods.hpp>
#include <Device_Target_Mapping/DeviceMapping.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
DeviceSpecification::DeviceSpecification()
/*PROTECTED REGION ID(DeviceSpecificationImpl__DeviceSpecificationImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_metaInformation(0), m_units(0), m_bagAccounts(0), m_vlSchedules(0),
            m_bestEffortRouting(0), m_flowControl(0), m_periods(0),
            m_refDeviceMapping(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(DeviceSpecificationImpl__DeviceSpecificationImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

DeviceSpecification::~DeviceSpecification()
{
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
    if (m_units)
    {
        delete m_units;
    }
    if (m_bagAccounts)
    {
        delete m_bagAccounts;
    }
    if (m_vlSchedules)
    {
        delete m_vlSchedules;
    }
    if (m_bestEffortRouting)
    {
        delete m_bestEffortRouting;
    }
    if (m_flowControl)
    {
        delete m_flowControl;
    }
    if (m_periods)
    {
        delete m_periods;
    }
}

/*PROTECTED REGION ID(DeviceSpecification.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::System_Specification::MetaInformation_ptr DeviceSpecification::getMetaInformation()
{
    return m_metaInformation;
}

void DeviceSpecification::setMetaInformation(
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
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

::System_Specification::Units_ptr DeviceSpecification::getUnits()
{
    return m_units;
}

void DeviceSpecification::setUnits(::System_Specification::Units_ptr _units)
{
    ::System_Specification::Units_ptr _old_units = m_units;

    m_units = _units;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__units(),
                _old_units,
                m_units
        );
        eNotify(&notification);
    }
#endif

    delete _old_units;
}

::Device_Specification::BagAccounts_ptr DeviceSpecification::getBagAccounts()
{
    return m_bagAccounts;
}

void DeviceSpecification::setBagAccounts(
        ::Device_Specification::BagAccounts_ptr _bagAccounts)
{
    ::Device_Specification::BagAccounts_ptr _old_bagAccounts = m_bagAccounts;

    m_bagAccounts = _bagAccounts;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__bagAccounts(),
                _old_bagAccounts,
                m_bagAccounts
        );
        eNotify(&notification);
    }
#endif

    delete _old_bagAccounts;
}

::Device_Specification::VirtualLinkSchedules_ptr DeviceSpecification::getVlSchedules()
{
    return m_vlSchedules;
}

void DeviceSpecification::setVlSchedules(
        ::Device_Specification::VirtualLinkSchedules_ptr _vlSchedules)
{
    ::Device_Specification::VirtualLinkSchedules_ptr _old_vlSchedules =
            m_vlSchedules;

    m_vlSchedules = _vlSchedules;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__vlSchedules(),
                _old_vlSchedules,
                m_vlSchedules
        );
        eNotify(&notification);
    }
#endif

    delete _old_vlSchedules;
}

::Device_Specification::BestEffortRouting_ptr DeviceSpecification::getBestEffortRouting()
{
    return m_bestEffortRouting;
}

void DeviceSpecification::setBestEffortRouting(
        ::Device_Specification::BestEffortRouting_ptr _bestEffortRouting)
{
    ::Device_Specification::BestEffortRouting_ptr _old_bestEffortRouting =
            m_bestEffortRouting;

    m_bestEffortRouting = _bestEffortRouting;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__bestEffortRouting(),
                _old_bestEffortRouting,
                m_bestEffortRouting
        );
        eNotify(&notification);
    }
#endif

    delete _old_bestEffortRouting;
}

::Device_Specification::FlowControl_ptr DeviceSpecification::getFlowControl()
{
    return m_flowControl;
}

void DeviceSpecification::setFlowControl(
        ::Device_Specification::FlowControl_ptr _flowControl)
{
    ::Device_Specification::FlowControl_ptr _old_flowControl = m_flowControl;

    m_flowControl = _flowControl;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__flowControl(),
                _old_flowControl,
                m_flowControl
        );
        eNotify(&notification);
    }
#endif

    delete _old_flowControl;
}

::Device_Specification::Periods_ptr DeviceSpecification::getPeriods()
{
    return m_periods;
}

void DeviceSpecification::setPeriods(
        ::Device_Specification::Periods_ptr _periods)
{
    ::Device_Specification::Periods_ptr _old_periods = m_periods;

    m_periods = _periods;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__periods(),
                _old_periods,
                m_periods
        );
        eNotify(&notification);
    }
#endif

    delete _old_periods;
}

::Device_Target_Mapping::DeviceMapping_ptr DeviceSpecification::getRefDeviceMapping()
{
    return m_refDeviceMapping;
}

void DeviceSpecification::setRefDeviceMapping(
        ::Device_Target_Mapping::DeviceMapping_ptr _refDeviceMapping)
{
    ::Device_Target_Mapping::DeviceMapping_ptr _old_refDeviceMapping =
            m_refDeviceMapping;

    m_refDeviceMapping = _refDeviceMapping;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getDeviceSpecification__refDeviceMapping(),
                _old_refDeviceMapping,
                m_refDeviceMapping
        );
        eNotify(&notification);
    }
#endif

}

