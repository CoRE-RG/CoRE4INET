#
# Device_Target_Mapping.cmake
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

set(Device_Target_Mapping_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMapping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMappingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Trigger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/TriggerImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMapping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMappingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/CriticalTrafficBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/CriticalTrafficBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SharedBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SharedBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DedicatedBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DedicatedBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Mappings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/MappingsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMappings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMappingsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMappings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMappingsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/OutputBuffers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/OutputBuffersImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBuffers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBuffersImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/BufferMapping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/BufferMappingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/MemoryBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/MemoryBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/BufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/COTSBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/COTSBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/HostBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/HostBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/QueuedOutputBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/QueuedOutputBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMapping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMappingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMapping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMappingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccounts.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccountsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccount.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccountImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMappings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMappingsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMappings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMappingsImpl.cpp
   )
   
set(Device_Target_Mapping_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMapping.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Trigger.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMapping.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/CriticalTrafficBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SharedBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DedicatedBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Mappings.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMappings.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMappings.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/OutputBuffers.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBuffers.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/BufferMapping.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/MemoryBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Buffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/COTSBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/HostBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/QueuedOutputBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMapping.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMapping.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccounts.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccount.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMappings.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMappings.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingFactory.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Device_Target_MappingPackage.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMapping.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Trigger.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMapping.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/CriticalTrafficBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SharedBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DedicatedBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Mappings.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PortMappings.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/DeviceMappings.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/OutputBuffers.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/InputBuffers.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/BufferMapping.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/MemoryBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/Buffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/COTSBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/HostBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/QueuedOutputBuffer.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMapping.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMapping.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccounts.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/PerPortBagAccount.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/SwPortMappings.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Target_Mapping/EsPortMappings.hpp DESTINATION include/emf4cpp/Device_Target_Mapping)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-Device_Target_Mapping SHARED ${Device_Target_Mapping_HEADERS} ${Device_Target_Mapping_SOURCES})
set_target_properties(emf4cpp-Device_Target_Mapping PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-Device_Target_Mapping DESTINATION lib)

