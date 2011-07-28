// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Mappings.cpp
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

#include "Mappings.hpp"
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Target_Mapping/DeviceMappings.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>
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
Mappings::Mappings()
/*PROTECTED REGION ID(MappingsImpl__MappingsImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_deviceMappings(0), m_containingVirtualLinkMapping(0),
            m_metaInformation(0), m_refVirtualLinkMappings(0)
/*PROTECTED REGION END*/
{

    /*PROTECTED REGION ID(MappingsImpl__MappingsImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Mappings::~Mappings()
{
    if (m_deviceMappings)
    {
        delete m_deviceMappings;
    }
    if (m_containingVirtualLinkMapping)
    {
        delete m_containingVirtualLinkMapping;
    }
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
}

/*PROTECTED REGION ID(Mappings.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::Device_Target_Mapping::DeviceMappings_ptr Mappings::getDeviceMappings()
{
    return m_deviceMappings;
}

void Mappings::setDeviceMappings(
        ::Device_Target_Mapping::DeviceMappings_ptr _deviceMappings)
{
    ::Device_Target_Mapping::DeviceMappings_ptr _old_deviceMappings =
            m_deviceMappings;

    m_deviceMappings = _deviceMappings;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getMappings__deviceMappings(),
                _old_deviceMappings,
                m_deviceMappings
        );
        eNotify(&notification);
    }
#endif

    delete _old_deviceMappings;
}

::Virtuallink_Map::VirtualLinkMapping_ptr Mappings::getContainingVirtualLinkMapping()
{
    return m_containingVirtualLinkMapping;
}

void Mappings::setContainingVirtualLinkMapping(
        ::Virtuallink_Map::VirtualLinkMapping_ptr _containingVirtualLinkMapping)
{
    ::Virtuallink_Map::VirtualLinkMapping_ptr
            _old_containingVirtualLinkMapping = m_containingVirtualLinkMapping;

    m_containingVirtualLinkMapping = _containingVirtualLinkMapping;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getMappings__containingVirtualLinkMapping(),
                _old_containingVirtualLinkMapping,
                m_containingVirtualLinkMapping
        );
        eNotify(&notification);
    }
#endif

    delete _old_containingVirtualLinkMapping;
}

::System_Specification::MetaInformation_ptr Mappings::getMetaInformation()
{
    return m_metaInformation;
}

void Mappings::setMetaInformation(
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
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getMappings__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

::Virtuallink_Map::VirtualLinkMapping_ptr Mappings::getRefVirtualLinkMappings()
{
    return m_refVirtualLinkMappings;
}

void Mappings::setRefVirtualLinkMappings(
        ::Virtuallink_Map::VirtualLinkMapping_ptr _refVirtualLinkMappings)
{
    ::Virtuallink_Map::VirtualLinkMapping_ptr _old_refVirtualLinkMappings =
            m_refVirtualLinkMappings;

    m_refVirtualLinkMappings = _refVirtualLinkMappings;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getMappings__refVirtualLinkMappings(),
                _old_refVirtualLinkMappings,
                m_refVirtualLinkMappings
        );
        eNotify(&notification);
    }
#endif

}

