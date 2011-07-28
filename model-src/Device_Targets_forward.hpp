// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets_forward.hpp
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

#ifndef _DEVICE_TARGETS_FORWARD_HPP
#define _DEVICE_TARGETS_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(Device_Targets_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace Device_Targets
{

    // EDataType
    /*PROTECTED REGION ID(Device_Targets_addressTypeEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t addressTypeEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(Device_Targets_diagnosisScheduleModeEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t
            diagnosisScheduleModeEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(Device_Targets_PortTypeType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t PortTypeType;
    /*PROTECTED REGION END*/

    // EClass

    // ManagementInterface
    class ManagementInterface;
    typedef ManagementInterface* ManagementInterface_ptr;

    // MacAcceptanceEntry
    class MacAcceptanceEntry;
    typedef MacAcceptanceEntry* MacAcceptanceEntry_ptr;

    // AccessControl
    class AccessControl;
    typedef AccessControl* AccessControl_ptr;

    // TargetDevices
    class TargetDevices;
    typedef TargetDevices* TargetDevices_ptr;

    // TargetDevice
    class TargetDevice;
    typedef TargetDevice* TargetDevice_ptr;

    // TTTechIpTargetDevice
    class TTTechIpTargetDevice;
    typedef TTTechIpTargetDevice* TTTechIpTargetDevice_ptr;

    // Diagnostic
    class Diagnostic;
    typedef Diagnostic* Diagnostic_ptr;

    // DiagnosisScheduleEntry
    class DiagnosisScheduleEntry;
    typedef DiagnosisScheduleEntry* DiagnosisScheduleEntry_ptr;

    // TargetPorts
    class TargetPorts;
    typedef TargetPorts* TargetPorts_ptr;

    // TargetPort
    class TargetPort;
    typedef TargetPort* TargetPort_ptr;

    // AntiMasquerading
    class AntiMasquerading;
    typedef AntiMasquerading* AntiMasquerading_ptr;

    // PortInfos
    class PortInfos;
    typedef PortInfos* PortInfos_ptr;

    // TTTechProtocolLayerDevice
    class TTTechProtocolLayerDevice;
    typedef TTTechProtocolLayerDevice* TTTechProtocolLayerDevice_ptr;

    // GeneralTargetDevice
    class GeneralTargetDevice;
    typedef GeneralTargetDevice* GeneralTargetDevice_ptr;

    // Package & Factory
    class Device_TargetsFactory;
    typedef Device_TargetsFactory * Device_TargetsFactory_ptr;
    class Device_TargetsPackage;
    typedef Device_TargetsPackage * Device_TargetsPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // Device_Targets


#endif // _DEVICE_TARGETS_FORWARD_HPP
