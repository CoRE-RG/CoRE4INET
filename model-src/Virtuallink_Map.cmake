#
# Virtuallink_Map.cmake
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

set(Virtuallink_Map_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMappings.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMappingsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMapImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMapping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMappingImpl.cpp
   )
   
set(Virtuallink_Map_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMappings.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMap.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMapping.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapFactory.hpp DESTINATION include/emf4cpp/Virtuallink_Map)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/Virtuallink_MapPackage.hpp DESTINATION include/emf4cpp/Virtuallink_Map)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMappings.hpp DESTINATION include/emf4cpp/Virtuallink_Map)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMap.hpp DESTINATION include/emf4cpp/Virtuallink_Map)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Virtuallink_Map/VirtualLinkMapping.hpp DESTINATION include/emf4cpp/Virtuallink_Map)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-Virtuallink_Map SHARED ${Virtuallink_Map_HEADERS} ${Virtuallink_Map_SOURCES})
set_target_properties(emf4cpp-Virtuallink_Map PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-Virtuallink_Map DESTINATION lib)

