// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Device_Target_MappingFactory.hpp
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

#ifndef _DEVICE_TARGET_MAPPINGFACTORY_HPP
#define _DEVICE_TARGET_MAPPINGFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <Device_Target_Mapping.hpp>

namespace Device_Target_Mapping
{

    class Device_Target_MappingFactory: public virtual ::ecore::EFactory
    {
    public:

        static Device_Target_MappingFactory_ptr _instance();

        virtual DeviceMapping_ptr createDeviceMapping();
        virtual InputBuffer_ptr createInputBuffer();
        virtual Trigger_ptr createTrigger();
        virtual PortMapping_ptr createPortMapping();
        virtual CriticalTrafficBuffer_ptr createCriticalTrafficBuffer();
        virtual SharedBuffer_ptr createSharedBuffer();
        virtual DedicatedBuffer_ptr createDedicatedBuffer();
        virtual Mappings_ptr createMappings();
        virtual PortMappings_ptr createPortMappings();
        virtual DeviceMappings_ptr createDeviceMappings();
        virtual OutputBuffers_ptr createOutputBuffers();
        virtual InputBuffers_ptr createInputBuffers();
        virtual BufferMapping_ptr createBufferMapping();
        virtual MemoryBuffer_ptr createMemoryBuffer();
        virtual Buffer_ptr createBuffer();
        virtual COTSBuffer_ptr createCOTSBuffer();
        virtual HostBuffer_ptr createHostBuffer();
        virtual QueuedOutputBuffer_ptr createQueuedOutputBuffer();
        virtual SwPortMapping_ptr createSwPortMapping();
        virtual EsPortMapping_ptr createEsPortMapping();
        virtual PerPortBagAccounts_ptr createPerPortBagAccounts();
        virtual PerPortBagAccount_ptr createPerPortBagAccount();
        virtual SwPortMappings_ptr createSwPortMappings();
        virtual EsPortMappings_ptr createEsPortMappings();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< Device_Target_MappingFactory > s_instance;

        Device_Target_MappingFactory();

    };

} // Device_Target_Mapping


#endif // _DEVICE_TARGET_MAPPINGFACTORY_HPP
