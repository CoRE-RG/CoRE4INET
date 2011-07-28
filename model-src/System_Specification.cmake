#
# System_Specification.cmake
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

set(System_Specification_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationPackage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationPackageImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationFactoryImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/ModelElement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/ModelElementImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/NamedElement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/NamedElementImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/MetaInformation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/MetaInformationImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SystemSpecification.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SystemSpecificationImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Units.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/UnitsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Time.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/TimeImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SITime.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SITimeImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RefTime.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RefTimeImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Devices.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/DevicesImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Device.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/DeviceImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Port.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/PortImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Links.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/LinksImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Link.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/LinkImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLinks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLinksImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLinkImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/PCFVirtualLink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/PCFVirtualLinkImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/DataVirtualLink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/DataVirtualLinkImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RCVirtualLink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RCVirtualLinkImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/TTVirtualLink.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/TTVirtualLinkImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRoute.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRouteImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRouteSegment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRouteSegmentImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Periods.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/PeriodsImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Period.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/PeriodImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/AbsolutePeriod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/AbsolutePeriodImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RelativePeriod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RelativePeriodImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SubPeriod.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SubPeriodImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Alias.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/AliasImpl.cpp
   )
   
set(System_Specification_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification_forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationPackage.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationFactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/ModelElement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/NamedElement.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/MetaInformation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SystemSpecification.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Units.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Time.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SITime.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RefTime.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Devices.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Device.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Port.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Links.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Link.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLinks.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLink.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/PCFVirtualLink.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/DataVirtualLink.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RCVirtualLink.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/TTVirtualLink.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRoute.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRouteSegment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Periods.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Period.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/AbsolutePeriod.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RelativePeriod.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SubPeriod.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Alias.hpp
   )

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification_forward.hpp DESTINATION include/emf4cpp/)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationFactory.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/System_SpecificationPackage.hpp DESTINATION include/emf4cpp/System_Specification)   
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/ModelElement.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/NamedElement.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/MetaInformation.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SystemSpecification.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Units.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Time.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SITime.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RefTime.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Devices.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Device.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Port.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Links.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Link.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLinks.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/VirtualLink.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/PCFVirtualLink.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/DataVirtualLink.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RCVirtualLink.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/TTVirtualLink.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRoute.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/FrameRouteSegment.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Periods.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Period.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/AbsolutePeriod.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/RelativePeriod.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/SubPeriod.hpp DESTINATION include/emf4cpp/System_Specification)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/System_Specification/Alias.hpp DESTINATION include/emf4cpp/System_Specification)
   
include_directories(${CMAKE_CURRENT_SOURCE_DIR} /opt/emf4cpp-0.0.2/include/emf4cpp /opt/emf4cpp-0.0.2/include/emf4cpp)

add_library(emf4cpp-System_Specification SHARED ${System_Specification_HEADERS} ${System_Specification_SOURCES})
set_target_properties(emf4cpp-System_Specification PROPERTIES VERSION 0.0.1 SOVERSION 1)

install(TARGETS emf4cpp-System_Specification DESTINATION lib)

