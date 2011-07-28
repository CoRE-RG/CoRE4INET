// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/VirtualLinkMap.cpp
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

#include "VirtualLinkMap.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Virtuallink_Map/Virtuallink_MapPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Virtuallink_Map;

// Default constructor
VirtualLinkMap::VirtualLinkMap()
/*PROTECTED REGION ID(VirtualLinkMapImpl__VirtualLinkMapImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_refVirtualLink(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(VirtualLinkMapImpl__VirtualLinkMapImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

VirtualLinkMap::~VirtualLinkMap()
{
}

/*PROTECTED REGION ID(VirtualLinkMap.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EInt VirtualLinkMap::getId() const
{
    return m_id;
}

void VirtualLinkMap::setId(::ecore::EInt _id)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_id = m_id;
#endif
    m_id = _id;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Virtuallink_Map::Virtuallink_MapPackage::_instance()->getVirtualLinkMap__id(),
                _old_id,
                m_id
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& VirtualLinkMap::getVL_Name() const
{
    return m_VL_Name;
}

void VirtualLinkMap::setVL_Name(::ecore::EString const& _VL_Name)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_VL_Name = m_VL_Name;
#endif
    m_VL_Name = _VL_Name;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Virtuallink_Map::Virtuallink_MapPackage::_instance()->getVirtualLinkMap__VL_Name(),
                _old_VL_Name,
                m_VL_Name
        );
        eNotify(&notification);
    }
#endif
}

// References
::System_Specification::VirtualLink_ptr VirtualLinkMap::getRefVirtualLink()
{
    return m_refVirtualLink;
}

void VirtualLinkMap::setRefVirtualLink(
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
                (::ecore::EStructuralFeature_ptr) ::Virtuallink_Map::Virtuallink_MapPackage::_instance()->getVirtualLinkMap__refVirtualLink(),
                _old_refVirtualLink,
                m_refVirtualLink
        );
        eNotify(&notification);
    }
#endif

}

