// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/EndSystemConfig.hpp
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

#ifndef DEVICE_SPECIFICATION_ENDSYSTEMCONFIG_HPP
#define DEVICE_SPECIFICATION_ENDSYSTEMCONFIG_HPP

#include <Device_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Specification/DeviceConfig.hpp>

/*PROTECTED REGION ID(EndSystemConfig_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Specification
{

    class EndSystemConfig: public virtual ::Device_Specification::DeviceConfig
    {
    public:
        EndSystemConfig();

        virtual ~EndSystemConfig();

        virtual void _initialize();

        // Operations


        // Attributes
        ::Device_Specification::TimeSourceEnum getTsSource() const;
        void setTsSource(::Device_Specification::TimeSourceEnum _tsSource);

        ::System_Specification::MacAddressType getSourceMacAddress() const;
        void setSourceMacAddress(
                ::System_Specification::MacAddressType _sourceMacAddress);

        ::System_Specification::CTMarkerType getDestMacAddressCF() const;
        void setDestMacAddressCF(
                ::System_Specification::CTMarkerType _destMacAddressCF);

        ::ecore::EBoolean isExternalSyncAckRequired() const;
        void setExternalSyncAckRequired(
                ::ecore::EBoolean _externalSyncAckRequired);

        // References
        ::Device_Specification::ExternalClockSynchronization_ptr
                getExternalClockSynchronization();
        void
                setExternalClockSynchronization(
                        ::Device_Specification::ExternalClockSynchronization_ptr _externalClockSynchronization);

        /*PROTECTED REGION ID(EndSystemConfig) START*/
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

        /*PROTECTED REGION ID(EndSystemConfigImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::Device_Specification::TimeSourceEnum m_tsSource;

        ::System_Specification::MacAddressType m_sourceMacAddress;

        ::System_Specification::CTMarkerType m_destMacAddressCF;

        ::ecore::EBoolean m_externalSyncAckRequired;

        // References

        ::Device_Specification::ExternalClockSynchronization_ptr
                m_externalClockSynchronization;

    };

} // Device_Specification

#endif // DEVICE_SPECIFICATION_ENDSYSTEMCONFIG_HPP
