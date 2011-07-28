// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/Network_ConfigurationFactory.hpp
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

#ifndef _NETWORK_CONFIGURATIONFACTORY_HPP
#define _NETWORK_CONFIGURATIONFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <Network_Configuration.hpp>

namespace Network_Configuration
{

    class Network_ConfigurationFactory: public virtual ::ecore::EFactory
    {
    public:

        static Network_ConfigurationFactory_ptr _instance();

        virtual DeviceReferringElement_ptr createDeviceReferringElement();
        virtual NetworkConfig_ptr createNetworkConfig();
        virtual Synchronization_ptr createSynchronization();
        virtual SyncDomain_ptr createSyncDomain();
        virtual SyncPriority_ptr createSyncPriority();
        virtual SyncBase_ptr createSyncBase();
        virtual SyncClient_ptr createSyncClient();
        virtual ActiveSyncComponent_ptr createActiveSyncComponent();
        virtual DistributedSyncMaster_ptr createDistributedSyncMaster();
        virtual CompressionMaster_ptr createCompressionMaster();
        virtual CliqueDetection_ptr createCliqueDetection();
        virtual BusGuardian_ptr createBusGuardian();
        virtual IntegrityConfigurations_ptr createIntegrityConfigurations();
        virtual IntegrityConfigBase_ptr createIntegrityConfigBase();
        virtual SyncClientIntegrityConfig_ptr createSyncClientIntegrityConfig();
        virtual ActiveSyncComponentIntegrityConfig_ptr
                createActiveSyncComponentIntegrityConfig();
        virtual CompressionMasterIntegrityConfig_ptr
                createCompressionMasterIntegrityConfig();
        virtual SyncMasterIntegrityConfig_ptr createSyncMasterIntegrityConfig();
        virtual Periods_ptr createPeriods();
        virtual SyncMaster_ptr createSyncMaster();
        virtual StandaloneSyncMaster_ptr createStandaloneSyncMaster();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< Network_ConfigurationFactory > s_instance;

        Network_ConfigurationFactory();

    };

} // Network_Configuration


#endif // _NETWORK_CONFIGURATIONFACTORY_HPP
