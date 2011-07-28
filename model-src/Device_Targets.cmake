#
# Device_Targets.cmake
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

set(Device_Targets_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/ManagementInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/ManagementInterfaceImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/MacAcceptanceEntry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/MacAcceptanceEntryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AccessControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AccessControlImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDevices.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDevicesImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDeviceImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechIpTargetDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechIpTargetDeviceImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Diagnostic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/DiagnosticImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/DiagnosisScheduleEntry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/DiagnosisScheduleEntryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPorts.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPortsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPort.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPortImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AntiMasquerading.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AntiMasqueradingImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/PortInfos.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/PortInfosImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechProtocolLayerDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechProtocolLayerDeviceImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/GeneralTargetDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/GeneralTargetDeviceImpl.cpp
   )
   
set(Device_Targets_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/ManagementInterface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/MacAcceptanceEntry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AccessControl.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDevices.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDevice.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechIpTargetDevice.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Diagnostic.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/DiagnosisScheduleEntry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPorts.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPort.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AntiMasquerading.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/PortInfos.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechProtocolLayerDevice.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/GeneralTargetDevice.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsFactory.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Device_TargetsPackage.hpp DESTINATION include/emf4cpp/Device_Targets)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/ManagementInterface.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/MacAcceptanceEntry.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AccessControl.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDevices.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetDevice.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechIpTargetDevice.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/Diagnostic.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/DiagnosisScheduleEntry.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPorts.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TargetPort.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/AntiMasquerading.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/PortInfos.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/TTTechProtocolLayerDevice.hpp DESTINATION include/emf4cpp/Device_Targets)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Device_Targets/GeneralTargetDevice.hpp DESTINATION include/emf4cpp/Device_Targets)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-Device_Targets SHARED ${Device_Targets_HEADERS} ${Device_Targets_SOURCES})
set_target_properties(emf4cpp-Device_Targets PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-Device_Targets DESTINATION lib)

