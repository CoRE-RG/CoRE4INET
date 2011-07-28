#
# Protocol_Definition.cmake
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

set(Protocol_Definition_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocols.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/ProtocolsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/ProtocolImpl.cpp
   )
   
set(Protocol_Definition_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocols.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionFactory.hpp DESTINATION include/emf4cpp/Protocol_Definition)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol_DefinitionPackage.hpp DESTINATION include/emf4cpp/Protocol_Definition)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocols.hpp DESTINATION include/emf4cpp/Protocol_Definition)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Protocol_Definition/Protocol.hpp DESTINATION include/emf4cpp/Protocol_Definition)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-Protocol_Definition SHARED ${Protocol_Definition_HEADERS} ${Protocol_Definition_SOURCES})
set_target_properties(emf4cpp-Protocol_Definition PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-Protocol_Definition DESTINATION lib)

