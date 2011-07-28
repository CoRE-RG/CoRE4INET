// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/SystemSpecification.cpp
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

#include "SystemSpecification.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <System_Specification/VirtualLinks.hpp>
#include <System_Specification/Devices.hpp>
#include <System_Specification/Links.hpp>
#include <System_Specification/Periods.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
SystemSpecification::SystemSpecification()
/*PROTECTED REGION ID(SystemSpecificationImpl__SystemSpecificationImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_metaInformation(0), m_units(0), m_virtualLinks(0), m_devices(0), m_links(
            0), m_periods(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(SystemSpecificationImpl__SystemSpecificationImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

SystemSpecification::~SystemSpecification()
{
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
    if (m_units)
    {
        delete m_units;
    }
    if (m_virtualLinks)
    {
        delete m_virtualLinks;
    }
    if (m_devices)
    {
        delete m_devices;
    }
    if (m_links)
    {
        delete m_links;
    }
    if (m_periods)
    {
        delete m_periods;
    }
}

/*PROTECTED REGION ID(SystemSpecification.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::System_Specification::MetaInformation_ptr SystemSpecification::getMetaInformation()
{
    return m_metaInformation;
}

void SystemSpecification::setMetaInformation(
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
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

::System_Specification::Units_ptr SystemSpecification::getUnits()
{
    return m_units;
}

void SystemSpecification::setUnits(::System_Specification::Units_ptr _units)
{
    ::System_Specification::Units_ptr _old_units = m_units;

    m_units = _units;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__units(),
                _old_units,
                m_units
        );
        eNotify(&notification);
    }
#endif

    delete _old_units;
}

::System_Specification::VirtualLinks_ptr SystemSpecification::getVirtualLinks()
{
    return m_virtualLinks;
}

void SystemSpecification::setVirtualLinks(
        ::System_Specification::VirtualLinks_ptr _virtualLinks)
{
    ::System_Specification::VirtualLinks_ptr _old_virtualLinks = m_virtualLinks;

    m_virtualLinks = _virtualLinks;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__virtualLinks(),
                _old_virtualLinks,
                m_virtualLinks
        );
        eNotify(&notification);
    }
#endif

    delete _old_virtualLinks;
}

::System_Specification::Devices_ptr SystemSpecification::getDevices()
{
    return m_devices;
}

void SystemSpecification::setDevices(
        ::System_Specification::Devices_ptr _devices)
{
    ::System_Specification::Devices_ptr _old_devices = m_devices;

    m_devices = _devices;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__devices(),
                _old_devices,
                m_devices
        );
        eNotify(&notification);
    }
#endif

    delete _old_devices;
}

::System_Specification::Links_ptr SystemSpecification::getLinks()
{
    return m_links;
}

void SystemSpecification::setLinks(::System_Specification::Links_ptr _links)
{
    ::System_Specification::Links_ptr _old_links = m_links;

    m_links = _links;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__links(),
                _old_links,
                m_links
        );
        eNotify(&notification);
    }
#endif

    delete _old_links;
}

::System_Specification::Periods_ptr SystemSpecification::getPeriods()
{
    return m_periods;
}

void SystemSpecification::setPeriods(
        ::System_Specification::Periods_ptr _periods)
{
    ::System_Specification::Periods_ptr _old_periods = m_periods;

    m_periods = _periods;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__periods(),
                _old_periods,
                m_periods
        );
        eNotify(&notification);
    }
#endif

    delete _old_periods;
}

