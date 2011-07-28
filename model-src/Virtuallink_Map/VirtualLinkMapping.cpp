// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/VirtualLinkMapping.cpp
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

#include "VirtualLinkMapping.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Virtuallink_Map/VirtualLinkMap.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Virtuallink_Map/Virtuallink_MapPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Virtuallink_Map;

// Default constructor
VirtualLinkMapping::VirtualLinkMapping()
/*PROTECTED REGION ID(VirtualLinkMappingImpl__VirtualLinkMappingImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_metaInformation(0)
/*PROTECTED REGION END*/
{

    m_virtualLinkMap.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Virtuallink_Map::VirtualLinkMap, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(VirtualLinkMappingImpl__VirtualLinkMappingImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

VirtualLinkMapping::~VirtualLinkMapping()
{
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(VirtualLinkMapping.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::ecorecpp::mapping::EList< ::Virtuallink_Map::VirtualLinkMap >& VirtualLinkMapping::getVirtualLinkMap()
{
    return *m_virtualLinkMap;
}

::System_Specification::MetaInformation_ptr VirtualLinkMapping::getMetaInformation()
{
    return m_metaInformation;
}

void VirtualLinkMapping::setMetaInformation(
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
                (::ecore::EStructuralFeature_ptr) ::Virtuallink_Map::Virtuallink_MapPackage::_instance()->getVirtualLinkMapping__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

