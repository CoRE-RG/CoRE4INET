// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TargetDevice.cpp
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

#include "TargetDevice.hpp"
#include <System_Specification/NamedElement.hpp>
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
TargetDevice::TargetDevice()
/*PROTECTED REGION ID(TargetDeviceImpl__TargetDeviceImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_metaInformation(0), m_refImplementation(0)
/*PROTECTED REGION END*/
{

    m_targetPorts.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Targets::TargetPorts, -1, true, false >(this, NULL));
    m_details.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::ecore::EStringToStringMapEntry, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(TargetDeviceImpl__TargetDeviceImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TargetDevice::~TargetDevice()
{
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(TargetDevice.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& TargetDevice::getDescription() const
{
    return m_description;
}

void TargetDevice::setDescription(::ecore::EString const& _description)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_description = m_description;
#endif
    m_description = _description;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetDevice__description(),
                _old_description,
                m_description
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::MetaInformation_ptr TargetDevice::getMetaInformation()
{
    return m_metaInformation;
}

void TargetDevice::setMetaInformation(
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
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetDevice__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

::IP_Configuration::Implementation_ptr TargetDevice::getRefImplementation()
{
    return m_refImplementation;
}

void TargetDevice::setRefImplementation(
        ::IP_Configuration::Implementation_ptr _refImplementation)
{
    ::IP_Configuration::Implementation_ptr _old_refImplementation =
            m_refImplementation;

    m_refImplementation = _refImplementation;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Targets::Device_TargetsPackage::_instance()->getTargetDevice__refImplementation(),
                _old_refImplementation,
                m_refImplementation
        );
        eNotify(&notification);
    }
#endif

}

::ecorecpp::mapping::EList< ::Device_Targets::TargetPorts >& TargetDevice::getTargetPorts()
{
    return *m_targetPorts;
}

::ecorecpp::mapping::EList< ::ecore::EStringToStringMapEntry >& TargetDevice::getDetails()
{
    return *m_details;
}

