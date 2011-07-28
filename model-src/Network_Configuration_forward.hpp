// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration_forward.hpp
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

#ifndef _NETWORK_CONFIGURATION_FORWARD_HPP
#define _NETWORK_CONFIGURATION_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(Network_Configuration_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace Network_Configuration
{

    // EDataType
    /*PROTECTED REGION ID(Network_Configuration_AvgModeEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t AvgModeEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(Network_Configuration_FaultToleranceEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t FaultToleranceEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(Network_Configuration_IntegrityLevelEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t IntegrityLevelEnum;
    /*PROTECTED REGION END*/

    // EClass

    // DeviceReferringElement
    class DeviceReferringElement;
    typedef DeviceReferringElement* DeviceReferringElement_ptr;

    // NetworkConfig
    class NetworkConfig;
    typedef NetworkConfig* NetworkConfig_ptr;

    // Synchronization
    class Synchronization;
    typedef Synchronization* Synchronization_ptr;

    // SyncDomain
    class SyncDomain;
    typedef SyncDomain* SyncDomain_ptr;

    // SyncPriority
    class SyncPriority;
    typedef SyncPriority* SyncPriority_ptr;

    // SyncBase
    class SyncBase;
    typedef SyncBase* SyncBase_ptr;

    // SyncClient
    class SyncClient;
    typedef SyncClient* SyncClient_ptr;

    // ActiveSyncComponent
    class ActiveSyncComponent;
    typedef ActiveSyncComponent* ActiveSyncComponent_ptr;

    // DistributedSyncMaster
    class DistributedSyncMaster;
    typedef DistributedSyncMaster* DistributedSyncMaster_ptr;

    // CompressionMaster
    class CompressionMaster;
    typedef CompressionMaster* CompressionMaster_ptr;

    // CliqueDetection
    class CliqueDetection;
    typedef CliqueDetection* CliqueDetection_ptr;

    // BusGuardian
    class BusGuardian;
    typedef BusGuardian* BusGuardian_ptr;

    // IntegrityConfigurations
    class IntegrityConfigurations;
    typedef IntegrityConfigurations* IntegrityConfigurations_ptr;

    // IntegrityConfigBase
    class IntegrityConfigBase;
    typedef IntegrityConfigBase* IntegrityConfigBase_ptr;

    // SyncClientIntegrityConfig
    class SyncClientIntegrityConfig;
    typedef SyncClientIntegrityConfig* SyncClientIntegrityConfig_ptr;

    // ActiveSyncComponentIntegrityConfig
    class ActiveSyncComponentIntegrityConfig;
    typedef ActiveSyncComponentIntegrityConfig
            * ActiveSyncComponentIntegrityConfig_ptr;

    // CompressionMasterIntegrityConfig
    class CompressionMasterIntegrityConfig;
    typedef CompressionMasterIntegrityConfig
            * CompressionMasterIntegrityConfig_ptr;

    // SyncMasterIntegrityConfig
    class SyncMasterIntegrityConfig;
    typedef SyncMasterIntegrityConfig* SyncMasterIntegrityConfig_ptr;

    // Periods
    class Periods;
    typedef Periods* Periods_ptr;

    // SyncMaster
    class SyncMaster;
    typedef SyncMaster* SyncMaster_ptr;

    // StandaloneSyncMaster
    class StandaloneSyncMaster;
    typedef StandaloneSyncMaster* StandaloneSyncMaster_ptr;

    // Package & Factory
    class Network_ConfigurationFactory;
    typedef Network_ConfigurationFactory * Network_ConfigurationFactory_ptr;
    class Network_ConfigurationPackage;
    typedef Network_ConfigurationPackage * Network_ConfigurationPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // Network_Configuration


#endif // _NETWORK_CONFIGURATION_FORWARD_HPP
