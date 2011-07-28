// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncDomain.hpp
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

#ifndef NETWORK_CONFIGURATION_SYNCDOMAIN_HPP
#define NETWORK_CONFIGURATION_SYNCDOMAIN_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(SyncDomain_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class SyncDomain: public virtual ::System_Specification::NamedElement
    {
    public:
        SyncDomain();

        virtual ~SyncDomain();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EByte getSyncDomainId() const;
        void setSyncDomainId(::ecore::EByte _syncDomainId);

        ::System_Specification::TimeType getClusterCycleDuration() const;
        void setClusterCycleDuration(
                ::System_Specification::TimeType _clusterCycleDuration);

        ::System_Specification::TimeType getIntegrationCycleDuration() const;
        void setIntegrationCycleDuration(
                ::System_Specification::TimeType _integrationCycleDuration);

        ::System_Specification::TimeType getMaxPcfTransmissionDelay() const;
        void setMaxPcfTransmissionDelay(
                ::System_Specification::TimeType _maxPcfTransmissionDelay);

        ::Network_Configuration::FaultToleranceEnum
                getFaultToleranceLevel() const;
        void
                setFaultToleranceLevel(
                        ::Network_Configuration::FaultToleranceEnum _faultToleranceLevel);

        ::Network_Configuration::IntegrityLevelEnum getIntegrityLevel() const;
        void setIntegrityLevel(
                ::Network_Configuration::IntegrityLevelEnum _integrityLevel);

        ::Network_Configuration::AvgModeEnum getAvgMode() const;
        void setAvgMode(::Network_Configuration::AvgModeEnum _avgMode);

        // References
        ::ecorecpp::mapping::EList< ::Network_Configuration::SyncPriority >
                & getSyncPriority();

        /*PROTECTED REGION ID(SyncDomain) START*/
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

        /*PROTECTED REGION ID(SyncDomainImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EByte m_syncDomainId;

        ::System_Specification::TimeType m_clusterCycleDuration;

        ::System_Specification::TimeType m_integrationCycleDuration;

        ::System_Specification::TimeType m_maxPcfTransmissionDelay;

        ::Network_Configuration::FaultToleranceEnum m_faultToleranceLevel;

        ::Network_Configuration::IntegrityLevelEnum m_integrityLevel;

        ::Network_Configuration::AvgModeEnum m_avgMode;

        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Network_Configuration::SyncPriority > > m_syncPriority;

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_SYNCDOMAIN_HPP
