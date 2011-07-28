#
# Device_Specification.cmake
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

set(Device_Specification_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceSpecification.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceSpecificationImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystemImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Switch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SwitchImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystemConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystemConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/ExternalClockSynchronization.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/ExternalClockSynchronizationImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SwitchConfig.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SwitchConfigImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccounts.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccountsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccount.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccountImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IncomingBagAccount.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IncomingBagAccountImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/OutgoingBagAccount.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/OutgoingBagAccountImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkSchedules.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkSchedulesImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkSchedule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkScheduleImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Buffers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BuffersImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FIFOQueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FIFOQueueImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SingleEntryBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SingleEntryBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DualEntryBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DualEntryBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TripleEntryBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TripleEntryBufferImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Incoming.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IncomingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTIncoming.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTIncomingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Outgoing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/OutgoingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCIncoming.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCIncomingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTIncoming.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTIncomingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEIncoming.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEIncomingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCOutgoing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCOutgoingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTOutgoing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTOutgoingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTOutgoing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTOutgoingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEOutgoing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEOutgoingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BestEffortRouting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BestEffortRoutingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteIncoming.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteIncomingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteOutgoing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteOutgoingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControlImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControlValue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControlValueImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerSchedules.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerSchedulesImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerSchedule.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerScheduleImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IntegrityCheck.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IntegrityCheckImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RedundancyManagement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RedundancyManagementImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCRedundancyManagement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCRedundancyManagementImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTRedundancyManagement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTRedundancyManagementImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Periods.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/PeriodsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FrameRelayDescriptor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FrameRelayDescriptorImpl.cpp
   )
   
set(Device_Specification_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceSpecification.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Switch.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystemConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/ExternalClockSynchronization.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SwitchConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccounts.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccount.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IncomingBagAccount.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/OutgoingBagAccount.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkSchedules.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkSchedule.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Buffers.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Buffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FIFOQueue.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SingleEntryBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DualEntryBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TripleEntryBuffer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Incoming.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTIncoming.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Outgoing.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCIncoming.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTIncoming.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEIncoming.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCOutgoing.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTOutgoing.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTOutgoing.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEOutgoing.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BestEffortRouting.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteIncoming.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteOutgoing.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControlValue.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerSchedules.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerSchedule.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IntegrityCheck.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RedundancyManagement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCRedundancyManagement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTRedundancyManagement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Periods.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FrameRelayDescriptor.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationFactory.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Device_SpecificationPackage.hpp DESTINATION include/emf4cpp/Device_Specification)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceSpecification.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystem.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Switch.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DeviceConfig.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/EndSystemConfig.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/ExternalClockSynchronization.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SwitchConfig.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccounts.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BagAccount.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IncomingBagAccount.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/OutgoingBagAccount.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkSchedules.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/VirtualLinkSchedule.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Buffers.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Buffer.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FIFOQueue.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/SingleEntryBuffer.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/DualEntryBuffer.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TripleEntryBuffer.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Incoming.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTIncoming.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Outgoing.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCIncoming.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTIncoming.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEIncoming.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCOutgoing.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/CTOutgoing.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTOutgoing.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BEOutgoing.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BestEffortRouting.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteIncoming.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/BERouteOutgoing.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControl.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FlowControlValue.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerSchedules.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TriggerSchedule.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/IntegrityCheck.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RedundancyManagement.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/RCRedundancyManagement.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/TTRedundancyManagement.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/Periods.hpp DESTINATION include/emf4cpp/Device_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Specification/FrameRelayDescriptor.hpp DESTINATION include/emf4cpp/Device_Specification)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-Device_Specification SHARED ${Device_Specification_HEADERS} ${Device_Specification_SOURCES})
set_target_properties(emf4cpp-Device_Specification PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-Device_Specification DESTINATION lib)

