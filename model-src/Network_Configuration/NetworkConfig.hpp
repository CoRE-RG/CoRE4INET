// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/NetworkConfig.hpp
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

#ifndef NETWORK_CONFIGURATION_NETWORKCONFIG_HPP
#define NETWORK_CONFIGURATION_NETWORKCONFIG_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Target_Mapping_forward.hpp>
#include <Protocol_Definition_forward.hpp>
#include <Virtuallink_Map_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(NetworkConfig_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class NetworkConfig: public virtual ::System_Specification::ModelElement
    {
    public:
        NetworkConfig();

        virtual ~NetworkConfig();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        ::System_Specification::Units_ptr getUnits();
        void setUnits(::System_Specification::Units_ptr _units);

        ::Network_Configuration::Synchronization_ptr getSynchronization();
        void setSynchronization(
                ::Network_Configuration::Synchronization_ptr _synchronization);

        ::ecorecpp::mapping::EList<
                ::Network_Configuration::DeviceReferringElement >
                & getDeviceReferringElement();

        ::System_Specification::SystemSpecification_ptr
                getRefSystemSpecification();
        void
                setRefSystemSpecification(
                        ::System_Specification::SystemSpecification_ptr _refSystemSpecification);

        ::Device_Target_Mapping::Mappings_ptr getRefMappings();
        void setRefMappings(::Device_Target_Mapping::Mappings_ptr _refMappings);

        ::Protocol_Definition::Protocol_ptr getRefProtocol();
        void setRefProtocol(::Protocol_Definition::Protocol_ptr _refProtocol);

        ::ecorecpp::mapping::EList< ::Network_Configuration::Periods >
                & getPeriods();

        ::Virtuallink_Map::VirtualLinkMapping_ptr getRefVirtualLinkMapping();
        void
                setRefVirtualLinkMapping(
                        ::Virtuallink_Map::VirtualLinkMapping_ptr _refVirtualLinkMapping);

        /*PROTECTED REGION ID(NetworkConfig) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(NetworkConfigImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::System_Specification::MetaInformation_ptr m_metaInformation;

        ::System_Specification::Units_ptr m_units;

        ::Network_Configuration::Synchronization_ptr m_synchronization;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Network_Configuration::DeviceReferringElement > >
                m_deviceReferringElement;

        ::System_Specification::SystemSpecification_ptr
                m_refSystemSpecification;

        ::Device_Target_Mapping::Mappings_ptr m_refMappings;

        ::Protocol_Definition::Protocol_ptr m_refProtocol;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Network_Configuration::Periods > > m_periods;

        ::Virtuallink_Map::VirtualLinkMapping_ptr m_refVirtualLinkMapping;

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_NETWORKCONFIG_HPP
