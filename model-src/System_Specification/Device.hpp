// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/Device.hpp
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

#ifndef SYSTEM_SPECIFICATION_DEVICE_HPP
#define SYSTEM_SPECIFICATION_DEVICE_HPP

#include <System_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(Device_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace System_Specification
{

    class Device: public virtual ::System_Specification::NamedElement
    {
    public:
        Device();

        virtual ~Device();

        virtual void _initialize();

        // Operations


        // Attributes
        std::vector< ::System_Specification::CapabilitiesEnum > const
                & getCapability() const;
        void setCapability(std::vector<
                ::System_Specification::CapabilitiesEnum > _capability);

        void
                addCapability(
                        ::System_Specification::CapabilitiesEnum const& _new_element_in_capability);
        void
                setCapabilityAt(
                        size_t _position,
                        ::System_Specification::CapabilitiesEnum const& _new_element_in_capability);
        void deleteCapabilityAt(size_t _position);

        // References
        ::ecorecpp::mapping::EList< ::System_Specification::Port >& getPort();

        /*PROTECTED REGION ID(Device) START*/
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

        /*PROTECTED REGION ID(DeviceImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        std::vector< ::System_Specification::CapabilitiesEnum > m_capability;

        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::System_Specification::Port > > m_port;

    };

} // System_Specification

#endif // SYSTEM_SPECIFICATION_DEVICE_HPP
