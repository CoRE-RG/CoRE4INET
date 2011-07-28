// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/TTVirtualLink.cpp
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

#include "TTVirtualLink.hpp"
#include <System_Specification/DataVirtualLink.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/FrameRoute.hpp>
#include <System_Specification/Device.hpp>
#include <System_Specification/Alias.hpp>
#include <System_Specification/Period.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
TTVirtualLink::TTVirtualLink()
{

    /*PROTECTED REGION ID(TTVirtualLinkImpl__TTVirtualLinkImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

TTVirtualLink::~TTVirtualLink()
{
}

/*PROTECTED REGION ID(TTVirtualLink.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::System_Specification::TimeType TTVirtualLink::getRelease() const
{
    return m_release;
}

void TTVirtualLink::setRelease(::System_Specification::TimeType _release)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_release = m_release;
#endif
    m_release = _release;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getTTVirtualLink__release(),
                _old_release,
                m_release
        );
        eNotify(&notification);
    }
#endif
}

::System_Specification::TimeType TTVirtualLink::getDeadline() const
{
    return m_deadline;
}

void TTVirtualLink::setDeadline(::System_Specification::TimeType _deadline)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::System_Specification::TimeType _old_deadline = m_deadline;
#endif
    m_deadline = _deadline;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getTTVirtualLink__deadline(),
                _old_deadline,
                m_deadline
        );
        eNotify(&notification);
    }
#endif
}

// References

