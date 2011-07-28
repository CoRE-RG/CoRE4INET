// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/SwPortMapping.hpp
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

#ifndef DEVICE_TARGET_MAPPING_SWPORTMAPPING_HPP
#define DEVICE_TARGET_MAPPING_SWPORTMAPPING_HPP

#include <Device_Target_Mapping_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Targets_forward.hpp>
#include <Device_Target_Mapping/PortMapping.hpp>

/*PROTECTED REGION ID(SwPortMapping_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Target_Mapping
{

    class SwPortMapping: public virtual ::Device_Target_Mapping::PortMapping
    {
    public:
        SwPortMapping();

        virtual ~SwPortMapping();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EBoolean isAddressLearningEnable() const;
        void setAddressLearningEnable(::ecore::EBoolean _addressLearningEnable);

        ::ecore::EBoolean isBroadcastForwardEnable() const;
        void setBroadcastForwardEnable(
                ::ecore::EBoolean _broadcastForwardEnable);

        // References
        ::Device_Target_Mapping::PerPortBagAccount_ptr
                getRefPerPortBroadcastBagAccount();
        void
                setRefPerPortBroadcastBagAccount(
                        ::Device_Target_Mapping::PerPortBagAccount_ptr _refPerPortBroadcastBagAccount);

        ::Device_Target_Mapping::PerPortBagAccount_ptr
                getRefPerPortUniCastBagAccount();
        void
                setRefPerPortUniCastBagAccount(
                        ::Device_Target_Mapping::PerPortBagAccount_ptr _refPerPortUniCastBagAccount);

        /*PROTECTED REGION ID(SwPortMapping) START*/
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

        /*PROTECTED REGION ID(SwPortMappingImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EBoolean m_addressLearningEnable;

        ::ecore::EBoolean m_broadcastForwardEnable;

        // References

        ::Device_Target_Mapping::PerPortBagAccount_ptr
                m_refPerPortBroadcastBagAccount;

        ::Device_Target_Mapping::PerPortBagAccount_ptr
                m_refPerPortUniCastBagAccount;

    };

} // Device_Target_Mapping

#endif // DEVICE_TARGET_MAPPING_SWPORTMAPPING_HPP
