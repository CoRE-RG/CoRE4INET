// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Device_Target_MappingPackage.hpp
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

#ifndef _DEVICE_TARGET_MAPPINGPACKAGE_HPP
#define _DEVICE_TARGET_MAPPINGPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <Device_Target_Mapping_forward.hpp>

#include <System_Specification/System_SpecificationPackage.hpp>
#include <Device_Specification/Device_SpecificationPackage.hpp>

namespace Device_Target_Mapping
{

    /*PROTECTED REGION ID(Device_Target_Mapping_SALT) ENABLED START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 2000
    /*PROTECTED REGION END*/

    class Device_Target_MappingPackage: public virtual ::ecore::EPackage
    {
    public:

        static Device_Target_MappingPackage_ptr _instance();

        // IDs for classifiers

        static const int BUFFER = SALT + 0;

        static const int BUFFERMAPPING = SALT + 1;

        static const int BUFFERTYPEENUM = SALT + 2;

        static const int COTSBUFFER = SALT + 3;

        static const int CRITICALTRAFFICBUFFER = SALT + 4;

        static const int DEDICATEDBUFFER = SALT + 5;

        static const int DEVICEMAPPING = SALT + 6;

        static const int DEVICEMAPPINGS = SALT + 7;

        static const int ESPORTMAPPING = SALT + 8;

        static const int ESPORTMAPPINGS = SALT + 9;

        static const int FREQUENCYTYPE = SALT + 10;

        static const int HOSTBUFFER = SALT + 11;

        static const int INPUTBUFFER = SALT + 12;

        static const int INPUTBUFFERS = SALT + 13;

        static const int MAPPINGS = SALT + 14;

        static const int MEMORYADDRESS = SALT + 15;

        static const int MEMORYBUFFER = SALT + 16;

        static const int OUTPUTBUFFERS = SALT + 17;

        static const int PERPORTBAGACCOUNT = SALT + 18;

        static const int PERPORTBAGACCOUNTS = SALT + 19;

        static const int PORTMAPPING = SALT + 20;

        static const int PORTMAPPINGS = SALT + 21;

        static const int QUEUEDOUTPUTBUFFER = SALT + 22;

        static const int SHAREDBUFFER = SALT + 23;

        static const int SWPORTMAPPING = SALT + 24;

        static const int SWPORTMAPPINGS = SALT + 25;

        static const int TRIGGER = SALT + 26;

        static const int DEVICEMAPPING__REFTARGETDEVICE = SALT + 0;

        static const int DEVICEMAPPING__PERPORTBAGACCOUNTS = SALT + 1;

        static const int DEVICEMAPPING__PORTMAPPINGS = SALT + 2;

        static const int DEVICEMAPPING__AGINGTIME = SALT + 3;

        static const int DEVICEMAPPING__ANTIMASQUERADING = SALT + 4;

        static const int DEVICEMAPPING__DIAGNOSTIC = SALT + 5;

        static const int DEVICEMAPPING__TRIGGER = SALT + 6;

        static const int DEVICEMAPPING__BUFFERMAPPING = SALT + 7;

        static const int DEVICEMAPPING__MANAGEMENTINTERFACE = SALT + 8;

        static const int DEVICEMAPPING__METAINFORMATION = SALT + 9;

        static const int TRIGGER__DEVICE = SALT + 10;

        static const int TRIGGER__TARGET = SALT + 11;

        static const int TRIGGER__REFTRIGGERSCHEDULE = SALT + 12;

        static const int PORTMAPPING__RXLATENCYCORRECTION = SALT + 13;

        static const int PORTMAPPING__TXLATENCYCORRECTION = SALT + 14;

        static const int PORTMAPPING__DISABLERXFC = SALT + 15;

        static const int PORTMAPPING__DISABLETXFC = SALT + 16;

        static const int PORTMAPPING__REFTARGETPORT = SALT + 17;

        static const int PORTMAPPING__REFPORT = SALT + 18;

        static const int SHAREDBUFFER__REFVIRTUALLINK = SALT + 19;

        static const int DEDICATEDBUFFER__REFVIRTUALLINK = SALT + 20;

        static const int MAPPINGS__DEVICEMAPPINGS = SALT + 21;

        static const int MAPPINGS__CONTAININGVIRTUALLINKMAPPING = SALT + 22;

        static const int MAPPINGS__METAINFORMATION = SALT + 23;

        static const int MAPPINGS__REFVIRTUALLINKMAPPINGS = SALT + 24;

        static const int PORTMAPPINGS__METAINFORMATION = SALT + 25;

        static const int DEVICEMAPPINGS__DEVICEMAPPING = SALT + 26;

        static const int DEVICEMAPPINGS__METAINFORMATION = SALT + 27;

        static const int OUTPUTBUFFERS__DEDICATEDBUFFER = SALT + 28;

        static const int OUTPUTBUFFERS__SHAREDBUFFER = SALT + 29;

        static const int OUTPUTBUFFERS__COTSBUFFER = SALT + 30;

        static const int INPUTBUFFERS__SHAREDBUFFER = SALT + 31;

        static const int INPUTBUFFERS__DEDICATEDBUFFER = SALT + 32;

        static const int INPUTBUFFERS__COTSBUFFER = SALT + 33;

        static const int BUFFERMAPPING__OUTPUTBUFFERS = SALT + 34;

        static const int BUFFERMAPPING__INPUTBUFFERS = SALT + 35;

        static const int BUFFERMAPPING__METAINFORMATION = SALT + 36;

        static const int MEMORYBUFFER__BASEADDRESS = SALT + 37;

        static const int BUFFER__TYPE = SALT + 38;

        static const int BUFFER__DEPTH = SALT + 39;

        static const int BUFFER__SIZE = SALT + 40;

        static const int BUFFER__FLUSHONSCHEDULERESET = SALT + 41;

        static const int COTSBUFFER__REFTARGETPORT = SALT + 42;

        static const int QUEUEDOUTPUTBUFFER__REFOUTVIRTUALLINK = SALT + 43;

        static const int SWPORTMAPPING__ADDRESSLEARNINGENABLE = SALT + 44;

        static const int SWPORTMAPPING__BROADCASTFORWARDENABLE = SALT + 45;

        static const int SWPORTMAPPING__REFPERPORTBROADCASTBAGACCOUNT = SALT
                + 46;

        static const int SWPORTMAPPING__REFPERPORTUNICASTBAGACCOUNT = SALT + 47;

        static const int PERPORTBAGACCOUNTS__PERPORTBAGSETTING = SALT + 48;

        static const int SWPORTMAPPINGS__TARGETPORTMAPPING = SALT + 49;

        static const int ESPORTMAPPINGS__TARGETPORTMAPPING = SALT + 50;

        // IDs for classifiers for class Buffer 

        static const int
                BUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                BUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class BufferMapping 

        static const int
                BUFFERMAPPING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BUFFERMAPPING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                BUFFERMAPPING__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class COTSBuffer 

        static const int
                COTSBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                COTSBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                COTSBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int COTSBUFFER__TYPE = BUFFER__TYPE;

        static const int COTSBUFFER__DEPTH = BUFFER__DEPTH;

        static const int COTSBUFFER__SIZE = BUFFER__SIZE;

        static const int COTSBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        static const int COTSBUFFER__BASEADDRESS = MEMORYBUFFER__BASEADDRESS;

        // IDs for classifiers for class CriticalTrafficBuffer 

        static const int
                CRITICALTRAFFICBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                CRITICALTRAFFICBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                CRITICALTRAFFICBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int CRITICALTRAFFICBUFFER__TYPE = BUFFER__TYPE;

        static const int CRITICALTRAFFICBUFFER__DEPTH = BUFFER__DEPTH;

        static const int CRITICALTRAFFICBUFFER__SIZE = BUFFER__SIZE;

        static const int CRITICALTRAFFICBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        static const int CRITICALTRAFFICBUFFER__BASEADDRESS =
                MEMORYBUFFER__BASEADDRESS;

        // IDs for classifiers for class DedicatedBuffer 

        static const int
                DEDICATEDBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DEDICATEDBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                DEDICATEDBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int DEDICATEDBUFFER__TYPE = BUFFER__TYPE;

        static const int DEDICATEDBUFFER__DEPTH = BUFFER__DEPTH;

        static const int DEDICATEDBUFFER__SIZE = BUFFER__SIZE;

        static const int DEDICATEDBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        static const int DEDICATEDBUFFER__BASEADDRESS =
                MEMORYBUFFER__BASEADDRESS;

        // IDs for classifiers for class DeviceMapping 

        static const int
                DEVICEMAPPING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DEVICEMAPPING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                DEVICEMAPPING__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class DeviceMappings 

        static const int
                DEVICEMAPPINGS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DEVICEMAPPINGS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class EsPortMapping 

        static const int
                ESPORTMAPPING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                ESPORTMAPPING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                ESPORTMAPPING__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int ESPORTMAPPING__RXLATENCYCORRECTION =
                PORTMAPPING__RXLATENCYCORRECTION;

        static const int ESPORTMAPPING__TXLATENCYCORRECTION =
                PORTMAPPING__TXLATENCYCORRECTION;

        static const int ESPORTMAPPING__DISABLERXFC = PORTMAPPING__DISABLERXFC;

        static const int ESPORTMAPPING__DISABLETXFC = PORTMAPPING__DISABLETXFC;

        static const int ESPORTMAPPING__REFTARGETPORT =
                PORTMAPPING__REFTARGETPORT;

        static const int ESPORTMAPPING__REFPORT = PORTMAPPING__REFPORT;

        // IDs for classifiers for class EsPortMappings 

        static const int
                ESPORTMAPPINGS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                ESPORTMAPPINGS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int ESPORTMAPPINGS__METAINFORMATION =
                PORTMAPPINGS__METAINFORMATION;

        // IDs for classifiers for class HostBuffer 

        static const int
                HOSTBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                HOSTBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                HOSTBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int HOSTBUFFER__TYPE = BUFFER__TYPE;

        static const int HOSTBUFFER__DEPTH = BUFFER__DEPTH;

        static const int HOSTBUFFER__SIZE = BUFFER__SIZE;

        static const int HOSTBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        static const int HOSTBUFFER__BASEADDRESS = MEMORYBUFFER__BASEADDRESS;

        // IDs for classifiers for class InputBuffer 

        static const int
                INPUTBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                INPUTBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                INPUTBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int INPUTBUFFER__TYPE = BUFFER__TYPE;

        static const int INPUTBUFFER__DEPTH = BUFFER__DEPTH;

        static const int INPUTBUFFER__SIZE = BUFFER__SIZE;

        static const int INPUTBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        static const int INPUTBUFFER__BASEADDRESS = MEMORYBUFFER__BASEADDRESS;

        // IDs for classifiers for class InputBuffers 

        static const int
                INPUTBUFFERS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                INPUTBUFFERS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class Mappings 

        static const int
                MAPPINGS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                MAPPINGS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                MAPPINGS__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class MemoryBuffer 

        static const int
                MEMORYBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                MEMORYBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                MEMORYBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int MEMORYBUFFER__TYPE = BUFFER__TYPE;

        static const int MEMORYBUFFER__DEPTH = BUFFER__DEPTH;

        static const int MEMORYBUFFER__SIZE = BUFFER__SIZE;

        static const int MEMORYBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        // IDs for classifiers for class OutputBuffers 

        static const int
                OUTPUTBUFFERS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                OUTPUTBUFFERS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class PerPortBagAccount 

        static const int
                PERPORTBAGACCOUNT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PERPORTBAGACCOUNT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                PERPORTBAGACCOUNT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int
                PERPORTBAGACCOUNT__BAG =
                        ::Device_Specification::Device_SpecificationPackage::BAGACCOUNT__BAG;

        static const int
                PERPORTBAGACCOUNT__JITTER =
                        ::Device_Specification::Device_SpecificationPackage::BAGACCOUNT__JITTER;

        static const int
                PERPORTBAGACCOUNT__CONSTRAINTYPE =
                        ::Device_Specification::Device_SpecificationPackage::BAGACCOUNT__CONSTRAINTYPE;

        // IDs for classifiers for class PerPortBagAccounts 

        static const int
                PERPORTBAGACCOUNTS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PERPORTBAGACCOUNTS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                PERPORTBAGACCOUNTS__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class PortMapping 

        static const int
                PORTMAPPING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PORTMAPPING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                PORTMAPPING__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class PortMappings 

        static const int
                PORTMAPPINGS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PORTMAPPINGS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class QueuedOutputBuffer 

        static const int
                QUEUEDOUTPUTBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                QUEUEDOUTPUTBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                QUEUEDOUTPUTBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int QUEUEDOUTPUTBUFFER__TYPE = BUFFER__TYPE;

        static const int QUEUEDOUTPUTBUFFER__DEPTH = BUFFER__DEPTH;

        static const int QUEUEDOUTPUTBUFFER__SIZE = BUFFER__SIZE;

        static const int QUEUEDOUTPUTBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        static const int QUEUEDOUTPUTBUFFER__BASEADDRESS =
                MEMORYBUFFER__BASEADDRESS;

        // IDs for classifiers for class SharedBuffer 

        static const int
                SHAREDBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SHAREDBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SHAREDBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int SHAREDBUFFER__TYPE = BUFFER__TYPE;

        static const int SHAREDBUFFER__DEPTH = BUFFER__DEPTH;

        static const int SHAREDBUFFER__SIZE = BUFFER__SIZE;

        static const int SHAREDBUFFER__FLUSHONSCHEDULERESET =
                BUFFER__FLUSHONSCHEDULERESET;

        static const int SHAREDBUFFER__BASEADDRESS = MEMORYBUFFER__BASEADDRESS;

        // IDs for classifiers for class SwPortMapping 

        static const int
                SWPORTMAPPING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SWPORTMAPPING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SWPORTMAPPING__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int SWPORTMAPPING__RXLATENCYCORRECTION =
                PORTMAPPING__RXLATENCYCORRECTION;

        static const int SWPORTMAPPING__TXLATENCYCORRECTION =
                PORTMAPPING__TXLATENCYCORRECTION;

        static const int SWPORTMAPPING__DISABLERXFC = PORTMAPPING__DISABLERXFC;

        static const int SWPORTMAPPING__DISABLETXFC = PORTMAPPING__DISABLETXFC;

        static const int SWPORTMAPPING__REFTARGETPORT =
                PORTMAPPING__REFTARGETPORT;

        static const int SWPORTMAPPING__REFPORT = PORTMAPPING__REFPORT;

        // IDs for classifiers for class SwPortMappings 

        static const int
                SWPORTMAPPINGS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SWPORTMAPPINGS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int SWPORTMAPPINGS__METAINFORMATION =
                PORTMAPPINGS__METAINFORMATION;

        // IDs for classifiers for class Trigger 

        static const int
                TRIGGER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TRIGGER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getDeviceMapping();

        virtual ::ecore::EClass_ptr getInputBuffer();

        virtual ::ecore::EClass_ptr getTrigger();

        virtual ::ecore::EClass_ptr getPortMapping();

        virtual ::ecore::EClass_ptr getCriticalTrafficBuffer();

        virtual ::ecore::EClass_ptr getSharedBuffer();

        virtual ::ecore::EClass_ptr getDedicatedBuffer();

        virtual ::ecore::EClass_ptr getMappings();

        virtual ::ecore::EClass_ptr getPortMappings();

        virtual ::ecore::EClass_ptr getDeviceMappings();

        virtual ::ecore::EClass_ptr getOutputBuffers();

        virtual ::ecore::EClass_ptr getInputBuffers();

        virtual ::ecore::EClass_ptr getBufferMapping();

        virtual ::ecore::EClass_ptr getMemoryBuffer();

        virtual ::ecore::EClass_ptr getBuffer();

        virtual ::ecore::EClass_ptr getCOTSBuffer();

        virtual ::ecore::EClass_ptr getHostBuffer();

        virtual ::ecore::EClass_ptr getQueuedOutputBuffer();

        virtual ::ecore::EClass_ptr getSwPortMapping();

        virtual ::ecore::EClass_ptr getEsPortMapping();

        virtual ::ecore::EClass_ptr getPerPortBagAccounts();

        virtual ::ecore::EClass_ptr getPerPortBagAccount();

        virtual ::ecore::EClass_ptr getSwPortMappings();

        virtual ::ecore::EClass_ptr getEsPortMappings();

        virtual ::ecore::EEnum_ptr getBufferTypeEnum();

        virtual ::ecore::EDataType_ptr getFrequencyType();

        virtual ::ecore::EDataType_ptr getMemoryAddress();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EReference_ptr getDeviceMapping__refTargetDevice();

        virtual ::ecore::EReference_ptr getDeviceMapping__perPortBagAccounts();

        virtual ::ecore::EReference_ptr getDeviceMapping__portMappings();

        virtual ::ecore::EAttribute_ptr getDeviceMapping__agingTime();

        virtual ::ecore::EReference_ptr getDeviceMapping__antiMasquerading();

        virtual ::ecore::EReference_ptr getDeviceMapping__diagnostic();

        virtual ::ecore::EReference_ptr getDeviceMapping__trigger();

        virtual ::ecore::EReference_ptr getDeviceMapping__bufferMapping();

        virtual ::ecore::EReference_ptr getDeviceMapping__managementInterface();

        virtual ::ecore::EReference_ptr getDeviceMapping__metaInformation();

        virtual ::ecore::EAttribute_ptr getBuffer__type();

        virtual ::ecore::EAttribute_ptr getBuffer__depth();

        virtual ::ecore::EAttribute_ptr getBuffer__size();

        virtual ::ecore::EAttribute_ptr getBuffer__flushOnScheduleReset();

        virtual ::ecore::EAttribute_ptr getMemoryBuffer__baseAddress();

        virtual ::ecore::EAttribute_ptr getTrigger__device();

        virtual ::ecore::EAttribute_ptr getTrigger__target();

        virtual ::ecore::EReference_ptr getTrigger__refTriggerSchedule();

        virtual ::ecore::EAttribute_ptr getPortMapping__rxLatencyCorrection();

        virtual ::ecore::EAttribute_ptr getPortMapping__txLatencyCorrection();

        virtual ::ecore::EAttribute_ptr getPortMapping__disableRxFc();

        virtual ::ecore::EAttribute_ptr getPortMapping__disableTxFc();

        virtual ::ecore::EReference_ptr getPortMapping__refTargetPort();

        virtual ::ecore::EReference_ptr getPortMapping__refPort();

        virtual ::ecore::EReference_ptr getSharedBuffer__refVirtualLink();

        virtual ::ecore::EReference_ptr getDedicatedBuffer__refVirtualLink();

        virtual ::ecore::EReference_ptr getMappings__deviceMappings();

        virtual ::ecore::EReference_ptr
                getMappings__containingVirtualLinkMapping();

        virtual ::ecore::EReference_ptr getMappings__metaInformation();

        virtual ::ecore::EReference_ptr getMappings__refVirtualLinkMappings();

        virtual ::ecore::EReference_ptr getPortMappings__metaInformation();

        virtual ::ecore::EReference_ptr getDeviceMappings__deviceMapping();

        virtual ::ecore::EReference_ptr getDeviceMappings__metaInformation();

        virtual ::ecore::EReference_ptr getOutputBuffers__dedicatedBuffer();

        virtual ::ecore::EReference_ptr getOutputBuffers__sharedBuffer();

        virtual ::ecore::EReference_ptr getOutputBuffers__cotsBuffer();

        virtual ::ecore::EReference_ptr getInputBuffers__sharedBuffer();

        virtual ::ecore::EReference_ptr getInputBuffers__dedicatedBuffer();

        virtual ::ecore::EReference_ptr getInputBuffers__cotsBuffer();

        virtual ::ecore::EReference_ptr getBufferMapping__outputBuffers();

        virtual ::ecore::EReference_ptr getBufferMapping__inputBuffers();

        virtual ::ecore::EReference_ptr getBufferMapping__metaInformation();

        virtual ::ecore::EReference_ptr getCOTSBuffer__refTargetPort();

        virtual ::ecore::EReference_ptr
                getQueuedOutputBuffer__refOutVirtualLink();

        virtual ::ecore::EAttribute_ptr
                getSwPortMapping__addressLearningEnable();

        virtual ::ecore::EAttribute_ptr
                getSwPortMapping__broadcastForwardEnable();

        virtual ::ecore::EReference_ptr
                getSwPortMapping__refPerPortBroadcastBagAccount();

        virtual ::ecore::EReference_ptr
                getSwPortMapping__refPerPortUniCastBagAccount();

        virtual ::ecore::EReference_ptr
                getPerPortBagAccounts__perPortBagSetting();

        virtual ::ecore::EAttribute_ptr getBagAccount__bag();

        virtual ::ecore::EAttribute_ptr getBagAccount__jitter();

        virtual ::ecore::EAttribute_ptr getBagAccount__constrainType();

        virtual ::ecore::EReference_ptr getSwPortMappings__targetPortMapping();

        virtual ::ecore::EReference_ptr getEsPortMappings__targetPortMapping();

    protected:

        static std::auto_ptr< Device_Target_MappingPackage > s_instance;

        Device_Target_MappingPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_DeviceMappingEClass;

        ::ecore::EClass_ptr m_InputBufferEClass;

        ::ecore::EClass_ptr m_TriggerEClass;

        ::ecore::EClass_ptr m_PortMappingEClass;

        ::ecore::EClass_ptr m_CriticalTrafficBufferEClass;

        ::ecore::EClass_ptr m_SharedBufferEClass;

        ::ecore::EClass_ptr m_DedicatedBufferEClass;

        ::ecore::EClass_ptr m_MappingsEClass;

        ::ecore::EClass_ptr m_PortMappingsEClass;

        ::ecore::EClass_ptr m_DeviceMappingsEClass;

        ::ecore::EClass_ptr m_OutputBuffersEClass;

        ::ecore::EClass_ptr m_InputBuffersEClass;

        ::ecore::EClass_ptr m_BufferMappingEClass;

        ::ecore::EClass_ptr m_MemoryBufferEClass;

        ::ecore::EClass_ptr m_BufferEClass;

        ::ecore::EClass_ptr m_COTSBufferEClass;

        ::ecore::EClass_ptr m_HostBufferEClass;

        ::ecore::EClass_ptr m_QueuedOutputBufferEClass;

        ::ecore::EClass_ptr m_SwPortMappingEClass;

        ::ecore::EClass_ptr m_EsPortMappingEClass;

        ::ecore::EClass_ptr m_PerPortBagAccountsEClass;

        ::ecore::EClass_ptr m_PerPortBagAccountEClass;

        ::ecore::EClass_ptr m_SwPortMappingsEClass;

        ::ecore::EClass_ptr m_EsPortMappingsEClass;

        // EEnuminstances 

        ::ecore::EEnum_ptr m_BufferTypeEnumEEnum;

        // EDataType instances 

        ::ecore::EDataType_ptr m_FrequencyTypeEDataType;

        ::ecore::EDataType_ptr m_MemoryAddressEDataType;

        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EReference_ptr m_DeviceMapping__refTargetDevice;

        ::ecore::EReference_ptr m_DeviceMapping__perPortBagAccounts;

        ::ecore::EReference_ptr m_DeviceMapping__portMappings;

        ::ecore::EAttribute_ptr m_DeviceMapping__agingTime;

        ::ecore::EReference_ptr m_DeviceMapping__antiMasquerading;

        ::ecore::EReference_ptr m_DeviceMapping__diagnostic;

        ::ecore::EReference_ptr m_DeviceMapping__trigger;

        ::ecore::EReference_ptr m_DeviceMapping__bufferMapping;

        ::ecore::EReference_ptr m_DeviceMapping__managementInterface;

        ::ecore::EReference_ptr m_DeviceMapping__metaInformation;

        ::ecore::EAttribute_ptr m_Buffer__type;

        ::ecore::EAttribute_ptr m_Buffer__depth;

        ::ecore::EAttribute_ptr m_Buffer__size;

        ::ecore::EAttribute_ptr m_Buffer__flushOnScheduleReset;

        ::ecore::EAttribute_ptr m_MemoryBuffer__baseAddress;

        ::ecore::EAttribute_ptr m_Trigger__device;

        ::ecore::EAttribute_ptr m_Trigger__target;

        ::ecore::EReference_ptr m_Trigger__refTriggerSchedule;

        ::ecore::EAttribute_ptr m_PortMapping__rxLatencyCorrection;

        ::ecore::EAttribute_ptr m_PortMapping__txLatencyCorrection;

        ::ecore::EAttribute_ptr m_PortMapping__disableRxFc;

        ::ecore::EAttribute_ptr m_PortMapping__disableTxFc;

        ::ecore::EReference_ptr m_PortMapping__refTargetPort;

        ::ecore::EReference_ptr m_PortMapping__refPort;

        ::ecore::EReference_ptr m_SharedBuffer__refVirtualLink;

        ::ecore::EReference_ptr m_DedicatedBuffer__refVirtualLink;

        ::ecore::EReference_ptr m_Mappings__deviceMappings;

        ::ecore::EReference_ptr m_Mappings__containingVirtualLinkMapping;

        ::ecore::EReference_ptr m_Mappings__metaInformation;

        ::ecore::EReference_ptr m_Mappings__refVirtualLinkMappings;

        ::ecore::EReference_ptr m_PortMappings__metaInformation;

        ::ecore::EReference_ptr m_DeviceMappings__deviceMapping;

        ::ecore::EReference_ptr m_DeviceMappings__metaInformation;

        ::ecore::EReference_ptr m_OutputBuffers__dedicatedBuffer;

        ::ecore::EReference_ptr m_OutputBuffers__sharedBuffer;

        ::ecore::EReference_ptr m_OutputBuffers__cotsBuffer;

        ::ecore::EReference_ptr m_InputBuffers__sharedBuffer;

        ::ecore::EReference_ptr m_InputBuffers__dedicatedBuffer;

        ::ecore::EReference_ptr m_InputBuffers__cotsBuffer;

        ::ecore::EReference_ptr m_BufferMapping__outputBuffers;

        ::ecore::EReference_ptr m_BufferMapping__inputBuffers;

        ::ecore::EReference_ptr m_BufferMapping__metaInformation;

        ::ecore::EReference_ptr m_COTSBuffer__refTargetPort;

        ::ecore::EReference_ptr m_QueuedOutputBuffer__refOutVirtualLink;

        ::ecore::EAttribute_ptr m_SwPortMapping__addressLearningEnable;

        ::ecore::EAttribute_ptr m_SwPortMapping__broadcastForwardEnable;

        ::ecore::EReference_ptr m_SwPortMapping__refPerPortBroadcastBagAccount;

        ::ecore::EReference_ptr m_SwPortMapping__refPerPortUniCastBagAccount;

        ::ecore::EReference_ptr m_PerPortBagAccounts__perPortBagSetting;

        ::ecore::EAttribute_ptr m_BagAccount__bag;

        ::ecore::EAttribute_ptr m_BagAccount__jitter;

        ::ecore::EAttribute_ptr m_BagAccount__constrainType;

        ::ecore::EReference_ptr m_SwPortMappings__targetPortMapping;

        ::ecore::EReference_ptr m_EsPortMappings__targetPortMapping;

    };

} // Device_Target_Mapping


#endif // _DEVICE_TARGET_MAPPINGPACKAGE_HPP
