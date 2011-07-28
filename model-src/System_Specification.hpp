// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification.hpp
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

#ifndef SYSTEM_SPECIFICATION_HPP
#define SYSTEM_SPECIFICATION_HPP

#include "System_Specification_forward.hpp"
#include <ecorecpp/mapping.hpp>

// EPackage


// EClass
#include "System_Specification/ModelElement.hpp"
#include "System_Specification/NamedElement.hpp"
#include "System_Specification/MetaInformation.hpp"
#include "System_Specification/SystemSpecification.hpp"
#include "System_Specification/Units.hpp"
#include "System_Specification/Time.hpp"
#include "System_Specification/SITime.hpp"
#include "System_Specification/RefTime.hpp"
#include "System_Specification/Devices.hpp"
#include "System_Specification/Device.hpp"
#include "System_Specification/Port.hpp"
#include "System_Specification/Links.hpp"
#include "System_Specification/Link.hpp"
#include "System_Specification/VirtualLinks.hpp"
#include "System_Specification/VirtualLink.hpp"
#include "System_Specification/PCFVirtualLink.hpp"
#include "System_Specification/DataVirtualLink.hpp"
#include "System_Specification/RCVirtualLink.hpp"
#include "System_Specification/TTVirtualLink.hpp"
#include "System_Specification/FrameRoute.hpp"
#include "System_Specification/FrameRouteSegment.hpp"
#include "System_Specification/Periods.hpp"
#include "System_Specification/Period.hpp"
#include "System_Specification/AbsolutePeriod.hpp"
#include "System_Specification/RelativePeriod.hpp"
#include "System_Specification/SubPeriod.hpp"
#include "System_Specification/Alias.hpp"

// Package & Factory
#include "System_Specification/System_SpecificationPackage.hpp"
#include "System_Specification/System_SpecificationFactory.hpp"

#endif // SYSTEM_SPECIFICATION_HPP
