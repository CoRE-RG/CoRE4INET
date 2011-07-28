// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/DeviceReferringElement.hpp
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

#ifndef NETWORK_CONFIGURATION_DEVICEREFERRINGELEMENT_HPP
#define NETWORK_CONFIGURATION_DEVICEREFERRINGELEMENT_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Device_Specification_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(DeviceReferringElement_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class DeviceReferringElement: public virtual ::System_Specification::NamedElement
    {
    public:
        DeviceReferringElement();

        virtual ~DeviceReferringElement();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::Device_Specification::DeviceSpecification_ptr
                getRefDeviceSpecification();
        void
                setRefDeviceSpecification(
                        ::Device_Specification::DeviceSpecification_ptr _refDeviceSpecification);

        ::Network_Configuration::SyncBase_ptr getRefSyncConfiguration();
        void setRefSyncConfiguration(
                ::Network_Configuration::SyncBase_ptr _refSyncConfiguration);

        ::System_Specification::Device_ptr getRefDevice();
        void setRefDevice(::System_Specification::Device_ptr _refDevice);

        /*PROTECTED REGION ID(DeviceReferringElement) START*/
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

        /*PROTECTED REGION ID(DeviceReferringElementImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::Device_Specification::DeviceSpecification_ptr
                m_refDeviceSpecification;

        ::Network_Configuration::SyncBase_ptr m_refSyncConfiguration;

        ::System_Specification::Device_ptr m_refDevice;

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_DEVICEREFERRINGELEMENT_HPP
