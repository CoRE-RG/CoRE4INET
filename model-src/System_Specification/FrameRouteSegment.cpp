// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/FrameRouteSegment.cpp
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

#include "FrameRouteSegment.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Link.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "System_Specification/System_SpecificationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::System_Specification;

// Default constructor
FrameRouteSegment::FrameRouteSegment()
{

    m_refOutgoingLink.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::System_Specification::Link, -1, false, false >(this, NULL));

    /*PROTECTED REGION ID(FrameRouteSegmentImpl__FrameRouteSegmentImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

FrameRouteSegment::~FrameRouteSegment()
{
}

/*PROTECTED REGION ID(FrameRouteSegment.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt FrameRouteSegment::getHop() const
{
    return m_hop;
}

void FrameRouteSegment::setHop(::ecore::EInt _hop)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_hop = m_hop;
#endif
    m_hop = _hop;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::System_Specification::System_SpecificationPackage::_instance()->getFrameRouteSegment__hop(),
                _old_hop,
                m_hop
        );
        eNotify(&notification);
    }
#endif
}

// References
::ecorecpp::mapping::EList< ::System_Specification::Link >& FrameRouteSegment::getRefOutgoingLink()
{
    return *m_refOutgoingLink;
}

