// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/VirtualLinkSchedule.cpp
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

#include "VirtualLinkSchedule.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <Device_Specification/CTIncoming.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Device_Specification;

// Default constructor
VirtualLinkSchedule::VirtualLinkSchedule()
/*PROTECTED REGION ID(VirtualLinkScheduleImpl__VirtualLinkScheduleImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_priority(6), m_refVirtualLink(0)
/*PROTECTED REGION END*/
{

    m_incoming.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Device_Specification::CTIncoming, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(VirtualLinkScheduleImpl__VirtualLinkScheduleImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

VirtualLinkSchedule::~VirtualLinkSchedule()
{
}

/*PROTECTED REGION ID(VirtualLinkSchedule.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EByte VirtualLinkSchedule::getPriority() const
{
    return m_priority;
}

void VirtualLinkSchedule::setPriority(::ecore::EByte _priority)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EByte _old_priority = m_priority;
#endif
    m_priority = _priority;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getVirtualLinkSchedule__priority(),
                _old_priority,
                m_priority
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::VirtualLink_ptr VirtualLinkSchedule::getRefVirtualLink()
{
    return m_refVirtualLink;
}

void VirtualLinkSchedule::setRefVirtualLink(
        ::System_Specification::VirtualLink_ptr _refVirtualLink)
{
    ::System_Specification::VirtualLink_ptr _old_refVirtualLink =
            m_refVirtualLink;

    m_refVirtualLink = _refVirtualLink;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Specification::Device_SpecificationPackage::_instance()->getVirtualLinkSchedule__refVirtualLink(),
                _old_refVirtualLink,
                m_refVirtualLink
        );
        eNotify(&notification);
    }
#endif

}

::ecorecpp::mapping::EList< ::Device_Specification::CTIncoming >& VirtualLinkSchedule::getIncoming()
{
    return *m_incoming;
}

