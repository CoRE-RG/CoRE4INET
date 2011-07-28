// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/Device_SpecificationFactory.hpp
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

#ifndef _DEVICE_SPECIFICATIONFACTORY_HPP
#define _DEVICE_SPECIFICATIONFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <Device_Specification.hpp>

namespace Device_Specification
{

    class Device_SpecificationFactory: public virtual ::ecore::EFactory
    {
    public:

        static Device_SpecificationFactory_ptr _instance();

        virtual DeviceSpecification_ptr createDeviceSpecification();
        virtual EndSystem_ptr createEndSystem();
        virtual Switch_ptr createSwitch();
        virtual DeviceConfig_ptr createDeviceConfig();
        virtual EndSystemConfig_ptr createEndSystemConfig();
        virtual ExternalClockSynchronization_ptr
                createExternalClockSynchronization();
        virtual SwitchConfig_ptr createSwitchConfig();
        virtual BagAccounts_ptr createBagAccounts();
        virtual BagAccount_ptr createBagAccount();
        virtual IncomingBagAccount_ptr createIncomingBagAccount();
        virtual OutgoingBagAccount_ptr createOutgoingBagAccount();
        virtual VirtualLinkSchedules_ptr createVirtualLinkSchedules();
        virtual VirtualLinkSchedule_ptr createVirtualLinkSchedule();
        virtual Buffers_ptr createBuffers();
        virtual Buffer_ptr createBuffer();
        virtual FIFOQueue_ptr createFIFOQueue();
        virtual SingleEntryBuffer_ptr createSingleEntryBuffer();
        virtual DualEntryBuffer_ptr createDualEntryBuffer();
        virtual TripleEntryBuffer_ptr createTripleEntryBuffer();
        virtual Incoming_ptr createIncoming();
        virtual CTIncoming_ptr createCTIncoming();
        virtual Outgoing_ptr createOutgoing();
        virtual RCIncoming_ptr createRCIncoming();
        virtual TTIncoming_ptr createTTIncoming();
        virtual BEIncoming_ptr createBEIncoming();
        virtual RCOutgoing_ptr createRCOutgoing();
        virtual CTOutgoing_ptr createCTOutgoing();
        virtual TTOutgoing_ptr createTTOutgoing();
        virtual BEOutgoing_ptr createBEOutgoing();
        virtual BestEffortRouting_ptr createBestEffortRouting();
        virtual BERouteIncoming_ptr createBERouteIncoming();
        virtual BERouteOutgoing_ptr createBERouteOutgoing();
        virtual FlowControl_ptr createFlowControl();
        virtual FlowControlValue_ptr createFlowControlValue();
        virtual TriggerSchedules_ptr createTriggerSchedules();
        virtual TriggerSchedule_ptr createTriggerSchedule();
        virtual IntegrityCheck_ptr createIntegrityCheck();
        virtual RedundancyManagement_ptr createRedundancyManagement();
        virtual RCRedundancyManagement_ptr createRCRedundancyManagement();
        virtual TTRedundancyManagement_ptr createTTRedundancyManagement();
        virtual Periods_ptr createPeriods();
        virtual FrameRelayDescriptor_ptr createFrameRelayDescriptor();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< Device_SpecificationFactory > s_instance;

        Device_SpecificationFactory();

    };

} // Device_Specification


#endif // _DEVICE_SPECIFICATIONFACTORY_HPP
