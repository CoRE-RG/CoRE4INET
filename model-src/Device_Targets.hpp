// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets.hpp
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

#ifndef DEVICE_TARGETS_HPP
#define DEVICE_TARGETS_HPP

#include "Device_Targets_forward.hpp"
#include <ecorecpp/mapping.hpp>

// EPackage


// EClass
#include "Device_Targets/ManagementInterface.hpp"
#include "Device_Targets/MacAcceptanceEntry.hpp"
#include "Device_Targets/AccessControl.hpp"
#include "Device_Targets/TargetDevices.hpp"
#include "Device_Targets/TargetDevice.hpp"
#include "Device_Targets/TTTechIpTargetDevice.hpp"
#include "Device_Targets/Diagnostic.hpp"
#include "Device_Targets/DiagnosisScheduleEntry.hpp"
#include "Device_Targets/TargetPorts.hpp"
#include "Device_Targets/TargetPort.hpp"
#include "Device_Targets/AntiMasquerading.hpp"
#include "Device_Targets/PortInfos.hpp"
#include "Device_Targets/TTTechProtocolLayerDevice.hpp"
#include "Device_Targets/GeneralTargetDevice.hpp"

// Package & Factory
#include "Device_Targets/Device_TargetsPackage.hpp"
#include "Device_Targets/Device_TargetsFactory.hpp"

#endif // DEVICE_TARGETS_HPP
