// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/AntiMasquerading.hpp
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

#ifndef DEVICE_TARGETS_ANTIMASQUERADING_HPP
#define DEVICE_TARGETS_ANTIMASQUERADING_HPP

#include <Device_Targets_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Target_Mapping_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(AntiMasquerading_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Targets
{

    class AntiMasquerading: public virtual ::System_Specification::ModelElement
    {
    public:
        AntiMasquerading();

        virtual ~AntiMasquerading();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::MacAddressType getMacAddress() const;
        void setMacAddress(::System_Specification::MacAddressType _macAddress);

        // References
        ::ecorecpp::mapping::EList< ::Device_Target_Mapping::SwPortMapping >
                & getRefPort();

        ::System_Specification::VirtualLink_ptr getRefVirtualLink();
        void setRefVirtualLink(
                ::System_Specification::VirtualLink_ptr _refVirtualLink);

        /*PROTECTED REGION ID(AntiMasquerading) START*/
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

        /*PROTECTED REGION ID(AntiMasqueradingImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::MacAddressType m_macAddress;

        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Device_Target_Mapping::SwPortMapping > > m_refPort;

        ::System_Specification::VirtualLink_ptr m_refVirtualLink;

    };

} // Device_Targets

#endif // DEVICE_TARGETS_ANTIMASQUERADING_HPP
