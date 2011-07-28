#
# Network_Configuration.cmake
# Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
#
# EMF4CPP is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# EMF4CPP is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -funroll-loops")

set(Network_Configuration_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DeviceReferringElement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DeviceReferringElementImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/NetworkConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/NetworkConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Synchronization.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SynchronizationImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncDomain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncDomainImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncPriority.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncPriorityImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncBaseImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClientImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponentImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DistributedSyncMaster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DistributedSyncMasterImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMaster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMasterImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CliqueDetection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CliqueDetectionImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/BusGuardian.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/BusGuardianImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigurations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigurationsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigBaseImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClientIntegrityConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClientIntegrityConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponentIntegrityConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponentIntegrityConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMasterIntegrityConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMasterIntegrityConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMasterIntegrityConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMasterIntegrityConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Periods.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/PeriodsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMaster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMasterImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/StandaloneSyncMaster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/StandaloneSyncMasterImpl.cpp
   )
   
set(Network_Configuration_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DeviceReferringElement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/NetworkConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Synchronization.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncDomain.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncPriority.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncBase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClient.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponent.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DistributedSyncMaster.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMaster.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CliqueDetection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/BusGuardian.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigurations.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigBase.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClientIntegrityConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponentIntegrityConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMasterIntegrityConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMasterIntegrityConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Periods.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMaster.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/StandaloneSyncMaster.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationFactory.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Network_ConfigurationPackage.hpp DESTINATION include/emf4cpp/Network_Configuration)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DeviceReferringElement.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/NetworkConfig.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Synchronization.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncDomain.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncPriority.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncBase.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClient.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponent.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/DistributedSyncMaster.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMaster.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CliqueDetection.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/BusGuardian.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigurations.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/IntegrityConfigBase.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncClientIntegrityConfig.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/ActiveSyncComponentIntegrityConfig.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/CompressionMasterIntegrityConfig.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMasterIntegrityConfig.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/Periods.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/SyncMaster.hpp DESTINATION include/emf4cpp/Network_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Network_Configuration/StandaloneSyncMaster.hpp DESTINATION include/emf4cpp/Network_Configuration)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-Network_Configuration SHARED ${Network_Configuration_HEADERS} ${Network_Configuration_SOURCES})
set_target_properties(emf4cpp-Network_Configuration PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-Network_Configuration DESTINATION lib)

