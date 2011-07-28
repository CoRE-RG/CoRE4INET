// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Mappings.hpp
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

#ifndef DEVICE_TARGET_MAPPING_MAPPINGS_HPP
#define DEVICE_TARGET_MAPPING_MAPPINGS_HPP

#include <Device_Target_Mapping_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Virtuallink_Map_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(Mappings_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Target_Mapping
{

    class Mappings: public virtual ::System_Specification::NamedElement
    {
    public:
        Mappings();

        virtual ~Mappings();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::Device_Target_Mapping::DeviceMappings_ptr getDeviceMappings();
        void setDeviceMappings(
                ::Device_Target_Mapping::DeviceMappings_ptr _deviceMappings);

        ::Virtuallink_Map::VirtualLinkMapping_ptr
                getContainingVirtualLinkMapping();
        void
                setContainingVirtualLinkMapping(
                        ::Virtuallink_Map::VirtualLinkMapping_ptr _containingVirtualLinkMapping);

        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        ::Virtuallink_Map::VirtualLinkMapping_ptr getRefVirtualLinkMappings();
        void
                setRefVirtualLinkMappings(
                        ::Virtuallink_Map::VirtualLinkMapping_ptr _refVirtualLinkMappings);

        /*PROTECTED REGION ID(Mappings) START*/
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

        /*PROTECTED REGION ID(MappingsImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::Device_Target_Mapping::DeviceMappings_ptr m_deviceMappings;

        ::Virtuallink_Map::VirtualLinkMapping_ptr
                m_containingVirtualLinkMapping;

        ::System_Specification::MetaInformation_ptr m_metaInformation;

        ::Virtuallink_Map::VirtualLinkMapping_ptr m_refVirtualLinkMappings;

    };

} // Device_Target_Mapping

#endif // DEVICE_TARGET_MAPPING_MAPPINGS_HPP
