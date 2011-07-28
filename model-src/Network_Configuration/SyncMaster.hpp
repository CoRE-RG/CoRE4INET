// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/SyncMaster.hpp
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

#ifndef NETWORK_CONFIGURATION_SYNCMASTER_HPP
#define NETWORK_CONFIGURATION_SYNCMASTER_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Network_Configuration/ActiveSyncComponent.hpp>

/*PROTECTED REGION ID(SyncMaster_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class SyncMaster: public virtual ::Network_Configuration::ActiveSyncComponent
    {
    public:
        SyncMaster();

        virtual ~SyncMaster();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EByte getMembershipBit() const;
        void setMembershipBit(::ecore::EByte _membershipBit);

        ::ecore::EInt getInitialIntegrationCycle() const;
        void setInitialIntegrationCycle(::ecore::EInt _initialIntegrationCycle);

        ::System_Specification::TimeType getCaOffset() const;
        void setCaOffset(::System_Specification::TimeType _caOffset);

        ::System_Specification::TimeType getColdstartTimeout() const;
        void setColdstartTimeout(
                ::System_Specification::TimeType _coldstartTimeout);

        ::System_Specification::TimeType getCsOffset() const;
        void setCsOffset(::System_Specification::TimeType _csOffset);

        ::System_Specification::TimeType getRestartTimeoutAsync() const;
        void setRestartTimeoutAsync(
                ::System_Specification::TimeType _restartTimeoutAsync);

        ::System_Specification::TimeType getRestartTimeoutSync() const;
        void setRestartTimeoutSync(
                ::System_Specification::TimeType _restartTimeoutSync);

        ::ecore::EInt getClksyncFilterMax() const;
        void setClksyncFilterMax(::ecore::EInt _clksyncFilterMax);

        // References
        ::Network_Configuration::SyncMasterIntegrityConfig_ptr
                getRefIntegrityConfig();
        void
                setRefIntegrityConfig(
                        ::Network_Configuration::SyncMasterIntegrityConfig_ptr _refIntegrityConfig);

        ::System_Specification::PCFVirtualLink_ptr getRefPcfVlidColdstart();
        void
                setRefPcfVlidColdstart(
                        ::System_Specification::PCFVirtualLink_ptr _refPcfVlidColdstart);

        ::System_Specification::PCFVirtualLink_ptr getRefPcfVlidColdstartAck();
        void
                setRefPcfVlidColdstartAck(
                        ::System_Specification::PCFVirtualLink_ptr _refPcfVlidColdstartAck);

        /*PROTECTED REGION ID(SyncMaster) START*/
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

        /*PROTECTED REGION ID(SyncMasterImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EByte m_membershipBit;

        ::ecore::EInt m_initialIntegrationCycle;

        ::System_Specification::TimeType m_caOffset;

        ::System_Specification::TimeType m_coldstartTimeout;

        ::System_Specification::TimeType m_csOffset;

        ::System_Specification::TimeType m_restartTimeoutAsync;

        ::System_Specification::TimeType m_restartTimeoutSync;

        ::ecore::EInt m_clksyncFilterMax;

        // References

        ::Network_Configuration::SyncMasterIntegrityConfig_ptr
                m_refIntegrityConfig;

        ::System_Specification::PCFVirtualLink_ptr m_refPcfVlidColdstart;

        ::System_Specification::PCFVirtualLink_ptr m_refPcfVlidColdstartAck;

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_SYNCMASTER_HPP
