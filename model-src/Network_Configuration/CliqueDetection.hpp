// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/CliqueDetection.hpp
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

#ifndef NETWORK_CONFIGURATION_CLIQUEDETECTION_HPP
#define NETWORK_CONFIGURATION_CLIQUEDETECTION_HPP

#include <Network_Configuration_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(CliqueDetection_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Network_Configuration
{

    class CliqueDetection: public virtual ::System_Specification::ModelElement
    {
    public:
        CliqueDetection();

        virtual ~CliqueDetection();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EBoolean isTentativeSyncRelayEnabled() const;
        void setTentativeSyncRelayEnabled(
                ::ecore::EBoolean _tentativeSyncRelayEnabled);

        ::ecore::EBoolean isSyncRelayEnabled() const;
        void setSyncRelayEnabled(::ecore::EBoolean _syncRelayEnabled);

        ::ecore::EBoolean isStableRelayEnabled() const;
        void setStableRelayEnabled(::ecore::EBoolean _stableRelayEnabled);

        ::ecore::EBoolean isTentativeSyncMembershipAsyncEnabled() const;
        void setTentativeSyncMembershipAsyncEnabled(
                ::ecore::EBoolean _tentativeSyncMembershipAsyncEnabled);

        ::ecore::EBoolean isTentativeSyncMembershipSyncEnabled() const;
        void setTentativeSyncMembershipSyncEnabled(
                ::ecore::EBoolean _tentativeSyncMembershipSyncEnabled);

        ::ecore::EBoolean isSyncMembershipAsyncEnabled() const;
        void setSyncMembershipAsyncEnabled(
                ::ecore::EBoolean _syncMembershipAsyncEnabled);

        ::ecore::EBoolean isSyncMembershipSyncEnabled() const;
        void setSyncMembershipSyncEnabled(
                ::ecore::EBoolean _syncMembershipSyncEnabled);

        ::ecore::EBoolean isStableMembershipAsyncEnabled() const;
        void setStableMembershipAsyncEnabled(
                ::ecore::EBoolean _stableMembershipAsyncEnabled);

        ::ecore::EBoolean isStableMembershipSyncEnabled() const;
        void setStableMembershipSyncEnabled(
                ::ecore::EBoolean _stableMembershipSyncEnabled);

        // References


        /*PROTECTED REGION ID(CliqueDetection) START*/
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

        /*PROTECTED REGION ID(CliqueDetectionImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EBoolean m_tentativeSyncRelayEnabled;

        ::ecore::EBoolean m_syncRelayEnabled;

        ::ecore::EBoolean m_stableRelayEnabled;

        ::ecore::EBoolean m_tentativeSyncMembershipAsyncEnabled;

        ::ecore::EBoolean m_tentativeSyncMembershipSyncEnabled;

        ::ecore::EBoolean m_syncMembershipAsyncEnabled;

        ::ecore::EBoolean m_syncMembershipSyncEnabled;

        ::ecore::EBoolean m_stableMembershipAsyncEnabled;

        ::ecore::EBoolean m_stableMembershipSyncEnabled;

        // References

    };

} // Network_Configuration

#endif // NETWORK_CONFIGURATION_CLIQUEDETECTION_HPP
