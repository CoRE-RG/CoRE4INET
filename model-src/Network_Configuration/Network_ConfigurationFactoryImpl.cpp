// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/Network_ConfigurationFactoryImpl.cpp
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

#include <Network_Configuration/Network_ConfigurationFactory.hpp>
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <Network_Configuration/DeviceReferringElement.hpp>
#include <Network_Configuration/NetworkConfig.hpp>
#include <Network_Configuration/Synchronization.hpp>
#include <Network_Configuration/SyncDomain.hpp>
#include <Network_Configuration/SyncPriority.hpp>
#include <Network_Configuration/SyncBase.hpp>
#include <Network_Configuration/SyncClient.hpp>
#include <Network_Configuration/ActiveSyncComponent.hpp>
#include <Network_Configuration/DistributedSyncMaster.hpp>
#include <Network_Configuration/CompressionMaster.hpp>
#include <Network_Configuration/CliqueDetection.hpp>
#include <Network_Configuration/BusGuardian.hpp>
#include <Network_Configuration/IntegrityConfigurations.hpp>
#include <Network_Configuration/IntegrityConfigBase.hpp>
#include <Network_Configuration/SyncClientIntegrityConfig.hpp>
#include <Network_Configuration/ActiveSyncComponentIntegrityConfig.hpp>
#include <Network_Configuration/CompressionMasterIntegrityConfig.hpp>
#include <Network_Configuration/SyncMasterIntegrityConfig.hpp>
#include <Network_Configuration/Periods.hpp>
#include <Network_Configuration/SyncMaster.hpp>
#include <Network_Configuration/StandaloneSyncMaster.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

Network_ConfigurationFactory::Network_ConfigurationFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr Network_ConfigurationFactory::create(
        ::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case Network_ConfigurationPackage::DEVICEREFERRINGELEMENT:
        return createDeviceReferringElement();
    case Network_ConfigurationPackage::NETWORKCONFIG:
        return createNetworkConfig();
    case Network_ConfigurationPackage::SYNCHRONIZATION:
        return createSynchronization();
    case Network_ConfigurationPackage::SYNCDOMAIN:
        return createSyncDomain();
    case Network_ConfigurationPackage::SYNCPRIORITY:
        return createSyncPriority();
    case Network_ConfigurationPackage::SYNCBASE:
        return createSyncBase();
    case Network_ConfigurationPackage::SYNCCLIENT:
        return createSyncClient();
    case Network_ConfigurationPackage::ACTIVESYNCCOMPONENT:
        return createActiveSyncComponent();
    case Network_ConfigurationPackage::DISTRIBUTEDSYNCMASTER:
        return createDistributedSyncMaster();
    case Network_ConfigurationPackage::COMPRESSIONMASTER:
        return createCompressionMaster();
    case Network_ConfigurationPackage::CLIQUEDETECTION:
        return createCliqueDetection();
    case Network_ConfigurationPackage::BUSGUARDIAN:
        return createBusGuardian();
    case Network_ConfigurationPackage::INTEGRITYCONFIGURATIONS:
        return createIntegrityConfigurations();
    case Network_ConfigurationPackage::INTEGRITYCONFIGBASE:
        return createIntegrityConfigBase();
    case Network_ConfigurationPackage::SYNCCLIENTINTEGRITYCONFIG:
        return createSyncClientIntegrityConfig();
    case Network_ConfigurationPackage::ACTIVESYNCCOMPONENTINTEGRITYCONFIG:
        return createActiveSyncComponentIntegrityConfig();
    case Network_ConfigurationPackage::COMPRESSIONMASTERINTEGRITYCONFIG:
        return createCompressionMasterIntegrityConfig();
    case Network_ConfigurationPackage::SYNCMASTERINTEGRITYCONFIG:
        return createSyncMasterIntegrityConfig();
    case Network_ConfigurationPackage::PERIODS:
        return createPeriods();
    case Network_ConfigurationPackage::SYNCMASTER:
        return createSyncMaster();
    case Network_ConfigurationPackage::STANDALONESYNCMASTER:
        return createStandaloneSyncMaster();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject Network_ConfigurationFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Network_ConfigurationPackage::AVGMODEENUM:
    {
        ::ecore::EJavaObject _any;
        Network_ConfigurationPackage_ptr
                _epkg =
                        dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (getEPackage());
        return _epkg->getAvgModeEnum()->getEEnumLiteralByLiteral(_literalValue)->getValue();
    }
    case Network_ConfigurationPackage::FAULTTOLERANCEENUM:
    {
        ::ecore::EJavaObject _any;
        Network_ConfigurationPackage_ptr
                _epkg =
                        dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (getEPackage());
        return _epkg->getFaultToleranceEnum()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    case Network_ConfigurationPackage::INTEGRITYLEVELENUM:
    {
        ::ecore::EJavaObject _any;
        Network_ConfigurationPackage_ptr
                _epkg =
                        dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (getEPackage());
        return _epkg->getIntegrityLevelEnum()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString Network_ConfigurationFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Network_ConfigurationPackage::AVGMODEENUM:
    {
        Network_ConfigurationPackage_ptr
                _epkg =
                        ::Network_Configuration::instanceOf<
                                ::Network_Configuration::Network_ConfigurationPackage >(
                                getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getAvgModeEnum()->getEEnumLiteral(_value)->getName();
    }
    case Network_ConfigurationPackage::FAULTTOLERANCEENUM:
    {
        Network_ConfigurationPackage_ptr
                _epkg =
                        ::Network_Configuration::instanceOf<
                                ::Network_Configuration::Network_ConfigurationPackage >(
                                getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getFaultToleranceEnum()->getEEnumLiteral(_value)->getName();
    }
    case Network_ConfigurationPackage::INTEGRITYLEVELENUM:
    {
        Network_ConfigurationPackage_ptr
                _epkg =
                        ::Network_Configuration::instanceOf<
                                ::Network_Configuration::Network_ConfigurationPackage >(
                                getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getIntegrityLevelEnum()->getEEnumLiteral(_value)->getName();
    }
    default:
        throw "IllegalArgumentException";
    }
}

DeviceReferringElement_ptr Network_ConfigurationFactory::createDeviceReferringElement()
{
    return new DeviceReferringElement();
}
NetworkConfig_ptr Network_ConfigurationFactory::createNetworkConfig()
{
    return new NetworkConfig();
}
Synchronization_ptr Network_ConfigurationFactory::createSynchronization()
{
    return new Synchronization();
}
SyncDomain_ptr Network_ConfigurationFactory::createSyncDomain()
{
    return new SyncDomain();
}
SyncPriority_ptr Network_ConfigurationFactory::createSyncPriority()
{
    return new SyncPriority();
}
SyncBase_ptr Network_ConfigurationFactory::createSyncBase()
{
    return new SyncBase();
}
SyncClient_ptr Network_ConfigurationFactory::createSyncClient()
{
    return new SyncClient();
}
ActiveSyncComponent_ptr Network_ConfigurationFactory::createActiveSyncComponent()
{
    return new ActiveSyncComponent();
}
DistributedSyncMaster_ptr Network_ConfigurationFactory::createDistributedSyncMaster()
{
    return new DistributedSyncMaster();
}
CompressionMaster_ptr Network_ConfigurationFactory::createCompressionMaster()
{
    return new CompressionMaster();
}
CliqueDetection_ptr Network_ConfigurationFactory::createCliqueDetection()
{
    return new CliqueDetection();
}
BusGuardian_ptr Network_ConfigurationFactory::createBusGuardian()
{
    return new BusGuardian();
}
IntegrityConfigurations_ptr Network_ConfigurationFactory::createIntegrityConfigurations()
{
    return new IntegrityConfigurations();
}
IntegrityConfigBase_ptr Network_ConfigurationFactory::createIntegrityConfigBase()
{
    return new IntegrityConfigBase();
}
SyncClientIntegrityConfig_ptr Network_ConfigurationFactory::createSyncClientIntegrityConfig()
{
    return new SyncClientIntegrityConfig();
}
ActiveSyncComponentIntegrityConfig_ptr Network_ConfigurationFactory::createActiveSyncComponentIntegrityConfig()
{
    return new ActiveSyncComponentIntegrityConfig();
}
CompressionMasterIntegrityConfig_ptr Network_ConfigurationFactory::createCompressionMasterIntegrityConfig()
{
    return new CompressionMasterIntegrityConfig();
}
SyncMasterIntegrityConfig_ptr Network_ConfigurationFactory::createSyncMasterIntegrityConfig()
{
    return new SyncMasterIntegrityConfig();
}
Periods_ptr Network_ConfigurationFactory::createPeriods()
{
    return new Periods();
}
SyncMaster_ptr Network_ConfigurationFactory::createSyncMaster()
{
    return new SyncMaster();
}
StandaloneSyncMaster_ptr Network_ConfigurationFactory::createStandaloneSyncMaster()
{
    return new StandaloneSyncMaster();
}

