#
# IP_Configuration.cmake
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

set(IP_Configuration_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/Implementation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/ImplementationImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIpImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechSwIp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechSwIpImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechEsIp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechEsIpImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpLayoutImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIpLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIpLayoutImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpConfigurations.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpConfigurationsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/GeneralImplementationDescription.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/GeneralImplementationDescriptionImpl.cpp
   )
   
set(IP_Configuration_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/Implementation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIp.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechSwIp.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechEsIp.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpLayout.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIpLayout.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpConfigurations.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/GeneralImplementationDescription.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationFactory.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IP_ConfigurationPackage.hpp DESTINATION include/emf4cpp/IP_Configuration)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/Implementation.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIp.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechSwIp.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechEsIp.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpLayout.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/TTTechIpLayout.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/IpConfigurations.hpp DESTINATION include/emf4cpp/IP_Configuration)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/IP_Configuration/GeneralImplementationDescription.hpp DESTINATION include/emf4cpp/IP_Configuration)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-IP_Configuration SHARED ${IP_Configuration_HEADERS} ${IP_Configuration_SOURCES})
set_target_properties(emf4cpp-IP_Configuration PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-IP_Configuration DESTINATION lib)

