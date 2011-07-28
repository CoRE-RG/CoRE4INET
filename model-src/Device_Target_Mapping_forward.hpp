// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping_forward.hpp
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

#ifndef _DEVICE_TARGET_MAPPING_FORWARD_HPP
#define _DEVICE_TARGET_MAPPING_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(Device_Target_Mapping_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace Device_Target_Mapping
{

    // EDataType
    /*PROTECTED REGION ID(Device_Target_Mapping_BufferTypeEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t BufferTypeEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(Device_Target_Mapping_FrequencyType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t FrequencyType;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(Device_Target_Mapping_MemoryAddress) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t MemoryAddress;
    /*PROTECTED REGION END*/

    // EClass

    // DeviceMapping
    class DeviceMapping;
    typedef DeviceMapping* DeviceMapping_ptr;

    // InputBuffer
    class InputBuffer;
    typedef InputBuffer* InputBuffer_ptr;

    // Trigger
    class Trigger;
    typedef Trigger* Trigger_ptr;

    // PortMapping
    class PortMapping;
    typedef PortMapping* PortMapping_ptr;

    // CriticalTrafficBuffer
    class CriticalTrafficBuffer;
    typedef CriticalTrafficBuffer* CriticalTrafficBuffer_ptr;

    // SharedBuffer
    class SharedBuffer;
    typedef SharedBuffer* SharedBuffer_ptr;

    // DedicatedBuffer
    class DedicatedBuffer;
    typedef DedicatedBuffer* DedicatedBuffer_ptr;

    // Mappings
    class Mappings;
    typedef Mappings* Mappings_ptr;

    // PortMappings
    class PortMappings;
    typedef PortMappings* PortMappings_ptr;

    // DeviceMappings
    class DeviceMappings;
    typedef DeviceMappings* DeviceMappings_ptr;

    // OutputBuffers
    class OutputBuffers;
    typedef OutputBuffers* OutputBuffers_ptr;

    // InputBuffers
    class InputBuffers;
    typedef InputBuffers* InputBuffers_ptr;

    // BufferMapping
    class BufferMapping;
    typedef BufferMapping* BufferMapping_ptr;

    // MemoryBuffer
    class MemoryBuffer;
    typedef MemoryBuffer* MemoryBuffer_ptr;

    // Buffer
    class Buffer;
    typedef Buffer* Buffer_ptr;

    // COTSBuffer
    class COTSBuffer;
    typedef COTSBuffer* COTSBuffer_ptr;

    // HostBuffer
    class HostBuffer;
    typedef HostBuffer* HostBuffer_ptr;

    // QueuedOutputBuffer
    class QueuedOutputBuffer;
    typedef QueuedOutputBuffer* QueuedOutputBuffer_ptr;

    // SwPortMapping
    class SwPortMapping;
    typedef SwPortMapping* SwPortMapping_ptr;

    // EsPortMapping
    class EsPortMapping;
    typedef EsPortMapping* EsPortMapping_ptr;

    // PerPortBagAccounts
    class PerPortBagAccounts;
    typedef PerPortBagAccounts* PerPortBagAccounts_ptr;

    // PerPortBagAccount
    class PerPortBagAccount;
    typedef PerPortBagAccount* PerPortBagAccount_ptr;

    // SwPortMappings
    class SwPortMappings;
    typedef SwPortMappings* SwPortMappings_ptr;

    // EsPortMappings
    class EsPortMappings;
    typedef EsPortMappings* EsPortMappings_ptr;

    // Package & Factory
    class Device_Target_MappingFactory;
    typedef Device_Target_MappingFactory * Device_Target_MappingFactory_ptr;
    class Device_Target_MappingPackage;
    typedef Device_Target_MappingPackage * Device_Target_MappingPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // Device_Target_Mapping


#endif // _DEVICE_TARGET_MAPPING_FORWARD_HPP
