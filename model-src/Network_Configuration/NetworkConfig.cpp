// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/NetworkConfig.cpp
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

#include "NetworkConfig.hpp"
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <Network_Configuration/Synchronization.hpp>
#include <Network_Configuration/DeviceReferringElement.hpp>
#include <System_Specification/SystemSpecification.hpp>
#include <Device_Target_Mapping/Mappings.hpp>
#include <Protocol_Definition/Protocol.hpp>
#include <Network_Configuration/Periods.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::Network_Configuration;

// Default constructor
NetworkConfig::NetworkConfig()
/*PROTECTED REGION ID(NetworkConfigImpl__NetworkConfigImplDefaults) START*/
// Please, enable the protected region if you changed it.
// To do this, add the keyword ENABLED before START.
:
    m_metaInformation(0), m_units(0), m_synchronization(0),
            m_refSystemSpecification(0), m_refMappings(0), m_refProtocol(0),
            m_refVirtualLinkMapping(0)
/*PROTECTED REGION END*/
{

    m_deviceReferringElement.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Network_Configuration::DeviceReferringElement, -1, true, false >(
            this, NULL));
    m_periods.reset(new ::ecorecpp::mapping::ReferenceEListImpl<
            ::Network_Configuration::Periods, -1, true, false >(this, NULL));

    /*PROTECTED REGION ID(NetworkConfigImpl__NetworkConfigImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

NetworkConfig::~NetworkConfig()
{
    if (m_metaInformation)
    {
        delete m_metaInformation;
    }
    if (m_units)
    {
        delete m_units;
    }
    if (m_synchronization)
    {
        delete m_synchronization;
    }
}

/*PROTECTED REGION ID(NetworkConfig.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

// References
::System_Specification::MetaInformation_ptr NetworkConfig::getMetaInformation()
{
    return m_metaInformation;
}

void NetworkConfig::setMetaInformation(
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
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__metaInformation(),
                _old_metaInformation,
                m_metaInformation
        );
        eNotify(&notification);
    }
#endif

    delete _old_metaInformation;
}

::System_Specification::Units_ptr NetworkConfig::getUnits()
{
    return m_units;
}

void NetworkConfig::setUnits(::System_Specification::Units_ptr _units)
{
    ::System_Specification::Units_ptr _old_units = m_units;

    m_units = _units;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__units(),
                _old_units,
                m_units
        );
        eNotify(&notification);
    }
#endif

    delete _old_units;
}

::Network_Configuration::Synchronization_ptr NetworkConfig::getSynchronization()
{
    return m_synchronization;
}

void NetworkConfig::setSynchronization(
        ::Network_Configuration::Synchronization_ptr _synchronization)
{
    ::Network_Configuration::Synchronization_ptr _old_synchronization =
            m_synchronization;

    m_synchronization = _synchronization;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__synchronization(),
                _old_synchronization,
                m_synchronization
        );
        eNotify(&notification);
    }
#endif

    delete _old_synchronization;
}

::ecorecpp::mapping::EList< ::Network_Configuration::DeviceReferringElement >& NetworkConfig::getDeviceReferringElement()
{
    return *m_deviceReferringElement;
}

::System_Specification::SystemSpecification_ptr NetworkConfig::getRefSystemSpecification()
{
    return m_refSystemSpecification;
}

void NetworkConfig::setRefSystemSpecification(
        ::System_Specification::SystemSpecification_ptr _refSystemSpecification)
{
    ::System_Specification::SystemSpecification_ptr
            _old_refSystemSpecification = m_refSystemSpecification;

    m_refSystemSpecification = _refSystemSpecification;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__refSystemSpecification(),
                _old_refSystemSpecification,
                m_refSystemSpecification
        );
        eNotify(&notification);
    }
#endif

}

::Device_Target_Mapping::Mappings_ptr NetworkConfig::getRefMappings()
{
    return m_refMappings;
}

void NetworkConfig::setRefMappings(
        ::Device_Target_Mapping::Mappings_ptr _refMappings)
{
    ::Device_Target_Mapping::Mappings_ptr _old_refMappings = m_refMappings;

    m_refMappings = _refMappings;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__refMappings(),
                _old_refMappings,
                m_refMappings
        );
        eNotify(&notification);
    }
#endif

}

::Protocol_Definition::Protocol_ptr NetworkConfig::getRefProtocol()
{
    return m_refProtocol;
}

void NetworkConfig::setRefProtocol(
        ::Protocol_Definition::Protocol_ptr _refProtocol)
{
    ::Protocol_Definition::Protocol_ptr _old_refProtocol = m_refProtocol;

    m_refProtocol = _refProtocol;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__refProtocol(),
                _old_refProtocol,
                m_refProtocol
        );
        eNotify(&notification);
    }
#endif

}

::ecorecpp::mapping::EList< ::Network_Configuration::Periods >& NetworkConfig::getPeriods()
{
    return *m_periods;
}

::Virtuallink_Map::VirtualLinkMapping_ptr NetworkConfig::getRefVirtualLinkMapping()
{
    return m_refVirtualLinkMapping;
}

void NetworkConfig::setRefVirtualLinkMapping(
        ::Virtuallink_Map::VirtualLinkMapping_ptr _refVirtualLinkMapping)
{
    ::Virtuallink_Map::VirtualLinkMapping_ptr _old_refVirtualLinkMapping =
            m_refVirtualLinkMapping;

    m_refVirtualLinkMapping = _refVirtualLinkMapping;

#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__refVirtualLinkMapping(),
                _old_refVirtualLinkMapping,
                m_refVirtualLinkMapping
        );
        eNotify(&notification);
    }
#endif

}

