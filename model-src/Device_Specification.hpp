// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification.hpp
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

#ifndef DEVICE_SPECIFICATION_HPP
#define DEVICE_SPECIFICATION_HPP

#include "Device_Specification_forward.hpp"
#include <ecorecpp/mapping.hpp>

// EPackage


// EClass
#include "Device_Specification/DeviceSpecification.hpp"
#include "Device_Specification/EndSystem.hpp"
#include "Device_Specification/Switch.hpp"
#include "Device_Specification/DeviceConfig.hpp"
#include "Device_Specification/EndSystemConfig.hpp"
#include "Device_Specification/ExternalClockSynchronization.hpp"
#include "Device_Specification/SwitchConfig.hpp"
#include "Device_Specification/BagAccounts.hpp"
#include "Device_Specification/BagAccount.hpp"
#include "Device_Specification/IncomingBagAccount.hpp"
#include "Device_Specification/OutgoingBagAccount.hpp"
#include "Device_Specification/VirtualLinkSchedules.hpp"
#include "Device_Specification/VirtualLinkSchedule.hpp"
#include "Device_Specification/Buffers.hpp"
#include "Device_Specification/Buffer.hpp"
#include "Device_Specification/FIFOQueue.hpp"
#include "Device_Specification/SingleEntryBuffer.hpp"
#include "Device_Specification/DualEntryBuffer.hpp"
#include "Device_Specification/TripleEntryBuffer.hpp"
#include "Device_Specification/Incoming.hpp"
#include "Device_Specification/CTIncoming.hpp"
#include "Device_Specification/Outgoing.hpp"
#include "Device_Specification/RCIncoming.hpp"
#include "Device_Specification/TTIncoming.hpp"
#include "Device_Specification/BEIncoming.hpp"
#include "Device_Specification/RCOutgoing.hpp"
#include "Device_Specification/CTOutgoing.hpp"
#include "Device_Specification/TTOutgoing.hpp"
#include "Device_Specification/BEOutgoing.hpp"
#include "Device_Specification/BestEffortRouting.hpp"
#include "Device_Specification/BERouteIncoming.hpp"
#include "Device_Specification/BERouteOutgoing.hpp"
#include "Device_Specification/FlowControl.hpp"
#include "Device_Specification/FlowControlValue.hpp"
#include "Device_Specification/TriggerSchedules.hpp"
#include "Device_Specification/TriggerSchedule.hpp"
#include "Device_Specification/IntegrityCheck.hpp"
#include "Device_Specification/RedundancyManagement.hpp"
#include "Device_Specification/RCRedundancyManagement.hpp"
#include "Device_Specification/TTRedundancyManagement.hpp"
#include "Device_Specification/Periods.hpp"
#include "Device_Specification/FrameRelayDescriptor.hpp"

// Package & Factory
#include "Device_Specification/Device_SpecificationPackage.hpp"
#include "Device_Specification/Device_SpecificationFactory.hpp"

#endif // DEVICE_SPECIFICATION_HPP
