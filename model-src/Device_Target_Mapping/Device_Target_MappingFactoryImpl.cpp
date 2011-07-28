// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Device_Target_MappingFactoryImpl.cpp
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

#include <Device_Target_Mapping/Device_Target_MappingFactory.hpp>
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <Device_Target_Mapping/DeviceMapping.hpp>
#include <Device_Target_Mapping/InputBuffer.hpp>
#include <Device_Target_Mapping/Trigger.hpp>
#include <Device_Target_Mapping/PortMapping.hpp>
#include <Device_Target_Mapping/CriticalTrafficBuffer.hpp>
#include <Device_Target_Mapping/SharedBuffer.hpp>
#include <Device_Target_Mapping/DedicatedBuffer.hpp>
#include <Device_Target_Mapping/Mappings.hpp>
#include <Device_Target_Mapping/PortMappings.hpp>
#include <Device_Target_Mapping/DeviceMappings.hpp>
#include <Device_Target_Mapping/OutputBuffers.hpp>
#include <Device_Target_Mapping/InputBuffers.hpp>
#include <Device_Target_Mapping/BufferMapping.hpp>
#include <Device_Target_Mapping/MemoryBuffer.hpp>
#include <Device_Target_Mapping/Buffer.hpp>
#include <Device_Target_Mapping/COTSBuffer.hpp>
#include <Device_Target_Mapping/HostBuffer.hpp>
#include <Device_Target_Mapping/QueuedOutputBuffer.hpp>
#include <Device_Target_Mapping/SwPortMapping.hpp>
#include <Device_Target_Mapping/EsPortMapping.hpp>
#include <Device_Target_Mapping/PerPortBagAccounts.hpp>
#include <Device_Target_Mapping/PerPortBagAccount.hpp>
#include <Device_Target_Mapping/SwPortMappings.hpp>
#include <Device_Target_Mapping/EsPortMappings.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Target_Mapping;

Device_Target_MappingFactory::Device_Target_MappingFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr Device_Target_MappingFactory::create(
        ::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case Device_Target_MappingPackage::DEVICEMAPPING:
        return createDeviceMapping();
    case Device_Target_MappingPackage::INPUTBUFFER:
        return createInputBuffer();
    case Device_Target_MappingPackage::TRIGGER:
        return createTrigger();
    case Device_Target_MappingPackage::PORTMAPPING:
        return createPortMapping();
    case Device_Target_MappingPackage::CRITICALTRAFFICBUFFER:
        return createCriticalTrafficBuffer();
    case Device_Target_MappingPackage::SHAREDBUFFER:
        return createSharedBuffer();
    case Device_Target_MappingPackage::DEDICATEDBUFFER:
        return createDedicatedBuffer();
    case Device_Target_MappingPackage::MAPPINGS:
        return createMappings();
    case Device_Target_MappingPackage::PORTMAPPINGS:
        return createPortMappings();
    case Device_Target_MappingPackage::DEVICEMAPPINGS:
        return createDeviceMappings();
    case Device_Target_MappingPackage::OUTPUTBUFFERS:
        return createOutputBuffers();
    case Device_Target_MappingPackage::INPUTBUFFERS:
        return createInputBuffers();
    case Device_Target_MappingPackage::BUFFERMAPPING:
        return createBufferMapping();
    case Device_Target_MappingPackage::MEMORYBUFFER:
        return createMemoryBuffer();
    case Device_Target_MappingPackage::BUFFER:
        return createBuffer();
    case Device_Target_MappingPackage::COTSBUFFER:
        return createCOTSBuffer();
    case Device_Target_MappingPackage::HOSTBUFFER:
        return createHostBuffer();
    case Device_Target_MappingPackage::QUEUEDOUTPUTBUFFER:
        return createQueuedOutputBuffer();
    case Device_Target_MappingPackage::SWPORTMAPPING:
        return createSwPortMapping();
    case Device_Target_MappingPackage::ESPORTMAPPING:
        return createEsPortMapping();
    case Device_Target_MappingPackage::PERPORTBAGACCOUNTS:
        return createPerPortBagAccounts();
    case Device_Target_MappingPackage::PERPORTBAGACCOUNT:
        return createPerPortBagAccount();
    case Device_Target_MappingPackage::SWPORTMAPPINGS:
        return createSwPortMappings();
    case Device_Target_MappingPackage::ESPORTMAPPINGS:
        return createEsPortMappings();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject Device_Target_MappingFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Device_Target_MappingPackage::BUFFERTYPEENUM:
    {
        ::ecore::EJavaObject _any;
        Device_Target_MappingPackage_ptr
                _epkg =
                        dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage_ptr > (getEPackage());
        return _epkg->getBufferTypeEnum()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    case Device_Target_MappingPackage::FREQUENCYTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::Device_Target_Mapping::FrequencyType >::fromString(
                _literalValue);
    case Device_Target_MappingPackage::MEMORYADDRESS:
        return ::ecorecpp::mapping::string_traits<
                ::Device_Target_Mapping::MemoryAddress >::fromString(
                _literalValue);
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString Device_Target_MappingFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    case Device_Target_MappingPackage::BUFFERTYPEENUM:
    {
        Device_Target_MappingPackage_ptr
                _epkg =
                        ::Device_Target_Mapping::instanceOf<
                                ::Device_Target_Mapping::Device_Target_MappingPackage >(
                                getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getBufferTypeEnum()->getEEnumLiteral(_value)->getName();
    }
    case Device_Target_MappingPackage::FREQUENCYTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::Device_Target_Mapping::FrequencyType >::toString(
                _instanceValue);
    case Device_Target_MappingPackage::MEMORYADDRESS:
        return ::ecorecpp::mapping::string_traits<
                ::Device_Target_Mapping::MemoryAddress >::toString(
                _instanceValue);
    default:
        throw "IllegalArgumentException";
    }
}

DeviceMapping_ptr Device_Target_MappingFactory::createDeviceMapping()
{
    return new DeviceMapping();
}
InputBuffer_ptr Device_Target_MappingFactory::createInputBuffer()
{
    return new InputBuffer();
}
Trigger_ptr Device_Target_MappingFactory::createTrigger()
{
    return new Trigger();
}
PortMapping_ptr Device_Target_MappingFactory::createPortMapping()
{
    return new PortMapping();
}
CriticalTrafficBuffer_ptr Device_Target_MappingFactory::createCriticalTrafficBuffer()
{
    return new CriticalTrafficBuffer();
}
SharedBuffer_ptr Device_Target_MappingFactory::createSharedBuffer()
{
    return new SharedBuffer();
}
DedicatedBuffer_ptr Device_Target_MappingFactory::createDedicatedBuffer()
{
    return new DedicatedBuffer();
}
Mappings_ptr Device_Target_MappingFactory::createMappings()
{
    return new Mappings();
}
PortMappings_ptr Device_Target_MappingFactory::createPortMappings()
{
    return new PortMappings();
}
DeviceMappings_ptr Device_Target_MappingFactory::createDeviceMappings()
{
    return new DeviceMappings();
}
OutputBuffers_ptr Device_Target_MappingFactory::createOutputBuffers()
{
    return new OutputBuffers();
}
InputBuffers_ptr Device_Target_MappingFactory::createInputBuffers()
{
    return new InputBuffers();
}
BufferMapping_ptr Device_Target_MappingFactory::createBufferMapping()
{
    return new BufferMapping();
}
MemoryBuffer_ptr Device_Target_MappingFactory::createMemoryBuffer()
{
    return new MemoryBuffer();
}
Buffer_ptr Device_Target_MappingFactory::createBuffer()
{
    return new Buffer();
}
COTSBuffer_ptr Device_Target_MappingFactory::createCOTSBuffer()
{
    return new COTSBuffer();
}
HostBuffer_ptr Device_Target_MappingFactory::createHostBuffer()
{
    return new HostBuffer();
}
QueuedOutputBuffer_ptr Device_Target_MappingFactory::createQueuedOutputBuffer()
{
    return new QueuedOutputBuffer();
}
SwPortMapping_ptr Device_Target_MappingFactory::createSwPortMapping()
{
    return new SwPortMapping();
}
EsPortMapping_ptr Device_Target_MappingFactory::createEsPortMapping()
{
    return new EsPortMapping();
}
PerPortBagAccounts_ptr Device_Target_MappingFactory::createPerPortBagAccounts()
{
    return new PerPortBagAccounts();
}
PerPortBagAccount_ptr Device_Target_MappingFactory::createPerPortBagAccount()
{
    return new PerPortBagAccount();
}
SwPortMappings_ptr Device_Target_MappingFactory::createSwPortMappings()
{
    return new SwPortMappings();
}
EsPortMappings_ptr Device_Target_MappingFactory::createEsPortMappings()
{
    return new EsPortMappings();
}

