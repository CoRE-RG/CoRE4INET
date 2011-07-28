// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping.hpp
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

#ifndef DEVICE_TARGET_MAPPING_HPP
#define DEVICE_TARGET_MAPPING_HPP

#include "Device_Target_Mapping_forward.hpp"
#include <ecorecpp/mapping.hpp>

// EPackage


// EClass
#include "Device_Target_Mapping/DeviceMapping.hpp"
#include "Device_Target_Mapping/InputBuffer.hpp"
#include "Device_Target_Mapping/Trigger.hpp"
#include "Device_Target_Mapping/PortMapping.hpp"
#include "Device_Target_Mapping/CriticalTrafficBuffer.hpp"
#include "Device_Target_Mapping/SharedBuffer.hpp"
#include "Device_Target_Mapping/DedicatedBuffer.hpp"
#include "Device_Target_Mapping/Mappings.hpp"
#include "Device_Target_Mapping/PortMappings.hpp"
#include "Device_Target_Mapping/DeviceMappings.hpp"
#include "Device_Target_Mapping/OutputBuffers.hpp"
#include "Device_Target_Mapping/InputBuffers.hpp"
#include "Device_Target_Mapping/BufferMapping.hpp"
#include "Device_Target_Mapping/MemoryBuffer.hpp"
#include "Device_Target_Mapping/Buffer.hpp"
#include "Device_Target_Mapping/COTSBuffer.hpp"
#include "Device_Target_Mapping/HostBuffer.hpp"
#include "Device_Target_Mapping/QueuedOutputBuffer.hpp"
#include "Device_Target_Mapping/SwPortMapping.hpp"
#include "Device_Target_Mapping/EsPortMapping.hpp"
#include "Device_Target_Mapping/PerPortBagAccounts.hpp"
#include "Device_Target_Mapping/PerPortBagAccount.hpp"
#include "Device_Target_Mapping/SwPortMappings.hpp"
#include "Device_Target_Mapping/EsPortMappings.hpp"

// Package & Factory
#include "Device_Target_Mapping/Device_Target_MappingPackage.hpp"
#include "Device_Target_Mapping/Device_Target_MappingFactory.hpp"

#endif // DEVICE_TARGET_MAPPING_HPP
