// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration.hpp
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

#ifndef NETWORK_CONFIGURATION_HPP
#define NETWORK_CONFIGURATION_HPP

#include "Network_Configuration_forward.hpp"
#include <ecorecpp/mapping.hpp>

// EPackage


// EClass
#include "Network_Configuration/DeviceReferringElement.hpp"
#include "Network_Configuration/NetworkConfig.hpp"
#include "Network_Configuration/Synchronization.hpp"
#include "Network_Configuration/SyncDomain.hpp"
#include "Network_Configuration/SyncPriority.hpp"
#include "Network_Configuration/SyncBase.hpp"
#include "Network_Configuration/SyncClient.hpp"
#include "Network_Configuration/ActiveSyncComponent.hpp"
#include "Network_Configuration/DistributedSyncMaster.hpp"
#include "Network_Configuration/CompressionMaster.hpp"
#include "Network_Configuration/CliqueDetection.hpp"
#include "Network_Configuration/BusGuardian.hpp"
#include "Network_Configuration/IntegrityConfigurations.hpp"
#include "Network_Configuration/IntegrityConfigBase.hpp"
#include "Network_Configuration/SyncClientIntegrityConfig.hpp"
#include "Network_Configuration/ActiveSyncComponentIntegrityConfig.hpp"
#include "Network_Configuration/CompressionMasterIntegrityConfig.hpp"
#include "Network_Configuration/SyncMasterIntegrityConfig.hpp"
#include "Network_Configuration/Periods.hpp"
#include "Network_Configuration/SyncMaster.hpp"
#include "Network_Configuration/StandaloneSyncMaster.hpp"

// Package & Factory
#include "Network_Configuration/Network_ConfigurationPackage.hpp"
#include "Network_Configuration/Network_ConfigurationFactory.hpp"

#endif // NETWORK_CONFIGURATION_HPP
