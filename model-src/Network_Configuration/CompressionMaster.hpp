// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/CompressionMaster.hpp
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

#ifndef NETWORK_CONFIGURATION_COMPRESSIONMASTER_HPP
#define NETWORK_CONFIGURATION_COMPRESSIONMASTER_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Network_Configuration/ActiveSyncComponent.hpp>

/*PROTECTED REGION ID(CompressionMaster_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class CompressionMaster: public virtual ::Network_Configuration::ActiveSyncComponent
    {
    public:
        CompressionMaster();

        virtual ~CompressionMaster();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::TimeType getObservationWindowSize() const;
        void setObservationWindowSize(
                ::System_Specification::TimeType _observationWindowSize);

        ::System_Specification::TimeType getCaEnableTimeout() const;
        void setCaEnableTimeout(
                ::System_Specification::TimeType _caEnableTimeout);

        ::System_Specification::TimeType getWait4in0Timeout() const;
        void setWait4in0Timeout(
                ::System_Specification::TimeType _wait4in0Timeout);

        // References
        ::Network_Configuration::BusGuardian_ptr getBusGuardian();
        void setBusGuardian(
                ::Network_Configuration::BusGuardian_ptr _busGuardian);

        ::Network_Configuration::CliqueDetection_ptr getCliqueDetection();
        void setCliqueDetection(
                ::Network_Configuration::CliqueDetection_ptr _cliqueDetection);

        ::Network_Configuration::CompressionMasterIntegrityConfig_ptr
                getRefIntegrityConfig();
        void
                setRefIntegrityConfig(
                        ::Network_Configuration::CompressionMasterIntegrityConfig_ptr _refIntegrityConfig);

        /*PROTECTED REGION ID(CompressionMaster) START*/
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

        /*PROTECTED REGION ID(CompressionMasterImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::TimeType m_observationWindowSize;

        ::System_Specification::TimeType m_caEnableTimeout;

        ::System_Specification::TimeType m_wait4in0Timeout;

        // References

        ::Network_Configuration::BusGuardian_ptr m_busGuardian;

        ::Network_Configuration::CliqueDetection_ptr m_cliqueDetection;

        ::Network_Configuration::CompressionMasterIntegrityConfig_ptr
                m_refIntegrityConfig;

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_COMPRESSIONMASTER_HPP
