// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification_forward.hpp
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

#ifndef _DEVICE_SPECIFICATION_FORWARD_HPP
#define _DEVICE_SPECIFICATION_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(Device_Specification_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace Device_Specification
{

    // EDataType
    /*PROTECTED REGION ID(Device_Specification_ConstrainType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t ConstrainType;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(Device_Specification_TimeSourceEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t TimeSourceEnum;
    /*PROTECTED REGION END*/

    // EClass

    // DeviceSpecification
    class DeviceSpecification;
    typedef DeviceSpecification* DeviceSpecification_ptr;

    // EndSystem
    class EndSystem;
    typedef EndSystem* EndSystem_ptr;

    // Switch
    class Switch;
    typedef Switch* Switch_ptr;

    // DeviceConfig
    class DeviceConfig;
    typedef DeviceConfig* DeviceConfig_ptr;

    // EndSystemConfig
    class EndSystemConfig;
    typedef EndSystemConfig* EndSystemConfig_ptr;

    // ExternalClockSynchronization
    class ExternalClockSynchronization;
    typedef ExternalClockSynchronization* ExternalClockSynchronization_ptr;

    // SwitchConfig
    class SwitchConfig;
    typedef SwitchConfig* SwitchConfig_ptr;

    // BagAccounts
    class BagAccounts;
    typedef BagAccounts* BagAccounts_ptr;

    // BagAccount
    class BagAccount;
    typedef BagAccount* BagAccount_ptr;

    // IncomingBagAccount
    class IncomingBagAccount;
    typedef IncomingBagAccount* IncomingBagAccount_ptr;

    // OutgoingBagAccount
    class OutgoingBagAccount;
    typedef OutgoingBagAccount* OutgoingBagAccount_ptr;

    // VirtualLinkSchedules
    class VirtualLinkSchedules;
    typedef VirtualLinkSchedules* VirtualLinkSchedules_ptr;

    // VirtualLinkSchedule
    class VirtualLinkSchedule;
    typedef VirtualLinkSchedule* VirtualLinkSchedule_ptr;

    // Buffers
    class Buffers;
    typedef Buffers* Buffers_ptr;

    // Buffer
    class Buffer;
    typedef Buffer* Buffer_ptr;

    // FIFOQueue
    class FIFOQueue;
    typedef FIFOQueue* FIFOQueue_ptr;

    // SingleEntryBuffer
    class SingleEntryBuffer;
    typedef SingleEntryBuffer* SingleEntryBuffer_ptr;

    // DualEntryBuffer
    class DualEntryBuffer;
    typedef DualEntryBuffer* DualEntryBuffer_ptr;

    // TripleEntryBuffer
    class TripleEntryBuffer;
    typedef TripleEntryBuffer* TripleEntryBuffer_ptr;

    // Incoming
    class Incoming;
    typedef Incoming* Incoming_ptr;

    // CTIncoming
    class CTIncoming;
    typedef CTIncoming* CTIncoming_ptr;

    // Outgoing
    class Outgoing;
    typedef Outgoing* Outgoing_ptr;

    // RCIncoming
    class RCIncoming;
    typedef RCIncoming* RCIncoming_ptr;

    // TTIncoming
    class TTIncoming;
    typedef TTIncoming* TTIncoming_ptr;

    // BEIncoming
    class BEIncoming;
    typedef BEIncoming* BEIncoming_ptr;

    // RCOutgoing
    class RCOutgoing;
    typedef RCOutgoing* RCOutgoing_ptr;

    // CTOutgoing
    class CTOutgoing;
    typedef CTOutgoing* CTOutgoing_ptr;

    // TTOutgoing
    class TTOutgoing;
    typedef TTOutgoing* TTOutgoing_ptr;

    // BEOutgoing
    class BEOutgoing;
    typedef BEOutgoing* BEOutgoing_ptr;

    // BestEffortRouting
    class BestEffortRouting;
    typedef BestEffortRouting* BestEffortRouting_ptr;

    // BERouteIncoming
    class BERouteIncoming;
    typedef BERouteIncoming* BERouteIncoming_ptr;

    // BERouteOutgoing
    class BERouteOutgoing;
    typedef BERouteOutgoing* BERouteOutgoing_ptr;

    // FlowControl
    class FlowControl;
    typedef FlowControl* FlowControl_ptr;

    // FlowControlValue
    class FlowControlValue;
    typedef FlowControlValue* FlowControlValue_ptr;

    // TriggerSchedules
    class TriggerSchedules;
    typedef TriggerSchedules* TriggerSchedules_ptr;

    // TriggerSchedule
    class TriggerSchedule;
    typedef TriggerSchedule* TriggerSchedule_ptr;

    // IntegrityCheck
    class IntegrityCheck;
    typedef IntegrityCheck* IntegrityCheck_ptr;

    // RedundancyManagement
    class RedundancyManagement;
    typedef RedundancyManagement* RedundancyManagement_ptr;

    // RCRedundancyManagement
    class RCRedundancyManagement;
    typedef RCRedundancyManagement* RCRedundancyManagement_ptr;

    // TTRedundancyManagement
    class TTRedundancyManagement;
    typedef TTRedundancyManagement* TTRedundancyManagement_ptr;

    // Periods
    class Periods;
    typedef Periods* Periods_ptr;

    // FrameRelayDescriptor
    class FrameRelayDescriptor;
    typedef FrameRelayDescriptor* FrameRelayDescriptor_ptr;

    // Package & Factory
    class Device_SpecificationFactory;
    typedef Device_SpecificationFactory * Device_SpecificationFactory_ptr;
    class Device_SpecificationPackage;
    typedef Device_SpecificationPackage * Device_SpecificationPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // Device_Specification


#endif // _DEVICE_SPECIFICATION_FORWARD_HPP
