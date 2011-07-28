// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/Device_SpecificationPackage.hpp
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

#ifndef _DEVICE_SPECIFICATIONPACKAGE_HPP
#define _DEVICE_SPECIFICATIONPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <Device_Specification_forward.hpp>

#include <System_Specification/System_SpecificationPackage.hpp>
#include <ecore/EcorePackage.hpp>

namespace Device_Specification
{

    /*PROTECTED REGION ID(Device_Specification_SALT) ENABLED START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 1000
    /*PROTECTED REGION END*/

    class Device_SpecificationPackage: public virtual ::ecore::EPackage
    {
    public:

        static Device_SpecificationPackage_ptr _instance();

        // IDs for classifiers

        static const int BAGACCOUNT = SALT + 0;

        static const int BAGACCOUNTS = SALT + 1;

        static const int BEINCOMING = SALT + 2;

        static const int BEOUTGOING = SALT + 3;

        static const int BEROUTEINCOMING = SALT + 4;

        static const int BEROUTEOUTGOING = SALT + 5;

        static const int BESTEFFORTROUTING = SALT + 6;

        static const int BUFFER = SALT + 7;

        static const int BUFFERS = SALT + 8;

        static const int CONSTRAINTYPE = SALT + 9;

        static const int CTINCOMING = SALT + 10;

        static const int CTOUTGOING = SALT + 11;

        static const int DEVICECONFIG = SALT + 12;

        static const int DEVICESPECIFICATION = SALT + 13;

        static const int DUALENTRYBUFFER = SALT + 14;

        static const int ENDSYSTEM = SALT + 15;

        static const int ENDSYSTEMCONFIG = SALT + 16;

        static const int EXTERNALCLOCKSYNCHRONIZATION = SALT + 17;

        static const int FIFOQUEUE = SALT + 18;

        static const int FLOWCONTROL = SALT + 19;

        static const int FLOWCONTROLVALUE = SALT + 20;

        static const int FRAMERELAYDESCRIPTOR = SALT + 21;

        static const int INCOMING = SALT + 22;

        static const int INCOMINGBAGACCOUNT = SALT + 23;

        static const int INTEGRITYCHECK = SALT + 24;

        static const int OUTGOING = SALT + 25;

        static const int OUTGOINGBAGACCOUNT = SALT + 26;

        static const int PERIODS = SALT + 27;

        static const int RCINCOMING = SALT + 28;

        static const int RCOUTGOING = SALT + 29;

        static const int RCREDUNDANCYMANAGEMENT = SALT + 30;

        static const int REDUNDANCYMANAGEMENT = SALT + 31;

        static const int SINGLEENTRYBUFFER = SALT + 32;

        static const int SWITCH = SALT + 33;

        static const int SWITCHCONFIG = SALT + 34;

        static const int TIMESOURCEENUM = SALT + 35;

        static const int TRIGGERSCHEDULE = SALT + 36;

        static const int TRIGGERSCHEDULES = SALT + 37;

        static const int TRIPLEENTRYBUFFER = SALT + 38;

        static const int TTINCOMING = SALT + 39;

        static const int TTOUTGOING = SALT + 40;

        static const int TTREDUNDANCYMANAGEMENT = SALT + 41;

        static const int VIRTUALLINKSCHEDULE = SALT + 42;

        static const int VIRTUALLINKSCHEDULES = SALT + 43;

        static const int DEVICESPECIFICATION__METAINFORMATION = SALT + 0;

        static const int DEVICESPECIFICATION__UNITS = SALT + 1;

        static const int DEVICESPECIFICATION__BAGACCOUNTS = SALT + 2;

        static const int DEVICESPECIFICATION__VLSCHEDULES = SALT + 3;

        static const int DEVICESPECIFICATION__BESTEFFORTROUTING = SALT + 4;

        static const int DEVICESPECIFICATION__FLOWCONTROL = SALT + 5;

        static const int DEVICESPECIFICATION__PERIODS = SALT + 6;

        static const int DEVICESPECIFICATION__REFDEVICEMAPPING = SALT + 7;

        static const int ENDSYSTEM__CONFIG = SALT + 8;

        static const int ENDSYSTEM__TRIGGERSCHEDULES = SALT + 9;

        static const int SWITCH__CONFIG = SALT + 10;

        static const int DEVICECONFIG__CTMARKER = SALT + 11;

        static const int DEVICECONFIG__CTMASK = SALT + 12;

        static const int ENDSYSTEMCONFIG__TSSOURCE = SALT + 13;

        static const int ENDSYSTEMCONFIG__EXTERNALCLOCKSYNCHRONIZATION = SALT
                + 14;

        static const int ENDSYSTEMCONFIG__SOURCEMACADDRESS = SALT + 15;

        static const int ENDSYSTEMCONFIG__DESTMACADDRESSCF = SALT + 16;

        static const int ENDSYSTEMCONFIG__EXTERNALSYNCACKREQUIRED = SALT + 17;

        static const int EXTERNALCLOCKSYNCHRONIZATION__MAXEXTCORRVALUE = SALT
                + 18;

        static const int BAGACCOUNTS__INCOMINGBAGACCOUNT = SALT + 19;

        static const int BAGACCOUNTS__OUTGOINGBAGACCOUNT = SALT + 20;

        static const int BAGACCOUNT__BAG = SALT + 21;

        static const int BAGACCOUNT__JITTER = SALT + 22;

        static const int BAGACCOUNT__CONSTRAINTYPE = SALT + 23;

        static const int VIRTUALLINKSCHEDULES__VLSCHEDULE = SALT + 24;

        static const int VIRTUALLINKSCHEDULES__SCHEDULESTARTAFTERSYNC = SALT
                + 25;

        static const int VIRTUALLINKSCHEDULE__PRIORITY = SALT + 26;

        static const int VIRTUALLINKSCHEDULE__REFVIRTUALLINK = SALT + 27;

        static const int VIRTUALLINKSCHEDULE__INCOMING = SALT + 28;

        static const int BUFFERS__BUFFER = SALT + 29;

        static const int FIFOQUEUE__LENGTH = SALT + 30;

        static const int INCOMING__OUTGOING = SALT + 31;

        static const int INCOMING__REFINPORT = SALT + 32;

        static const int CTINCOMING__REMOVESEQUENCENUMBER = SALT + 33;

        static const int CTINCOMING__REDUNDANCYFUNCTION = SALT + 34;

        static const int OUTGOING__APPENDSEQUENCENUMBER = SALT + 35;

        static const int OUTGOING__REFOUTPORT = SALT + 36;

        static const int RCINCOMING__REFBAGACCOUNT = SALT + 37;

        static const int TTINCOMING__RECEIVEWINDOWSTART = SALT + 38;

        static const int TTINCOMING__RECEIVEWINDOWEND = SALT + 39;

        static const int TTINCOMING__PERMANENCEPIT = SALT + 40;

        static const int TTINCOMING__REFPERIOD = SALT + 41;

        static const int RCOUTGOING__REFBAGACCOUNT = SALT + 42;

        static const int RCOUTGOING__MAXDISPATCHDELAY = SALT + 43;

        static const int TTOUTGOING__SENDWINDOWSTART = SALT + 44;

        static const int TTOUTGOING__SENDWINDOWEND = SALT + 45;

        static const int TTOUTGOING__REFPERIOD = SALT + 46;

        static const int BESTEFFORTROUTING__ENABLEDYNAMICROUTING = SALT + 47;

        static const int BESTEFFORTROUTING__BEROUTEINCOMING = SALT + 48;

        static const int BEROUTEINCOMING__DESTINATIONMACADDRESS = SALT + 49;

        static const int BEROUTEINCOMING__ADDRMASK = SALT + 50;

        static const int FLOWCONTROL__XON = SALT + 51;

        static const int FLOWCONTROL__XOFF = SALT + 52;

        static const int FLOWCONTROLVALUE__VALUE = SALT + 53;

        static const int FLOWCONTROLVALUE__THRESHOLD = SALT + 54;

        static const int TRIGGERSCHEDULES__TRIGGERSCHEDULE = SALT + 55;

        static const int TRIGGERSCHEDULE__REFPERIOD = SALT + 56;

        static const int REDUNDANCYMANAGEMENT__REDUNDANCYTIMEOUT = SALT + 57;

        static const int RCREDUNDANCYMANAGEMENT__MAXSEQUENCENUMBERRANGE = SALT
                + 58;

        static const int PERIODS__PERIOD = SALT + 59;

        static const int FRAMERELAYDESCRIPTOR__BUFFERDEPTH = SALT + 60;

        // IDs for classifiers for class BagAccount 

        static const int
                BAGACCOUNT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BAGACCOUNT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                BAGACCOUNT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class BagAccounts 

        static const int
                BAGACCOUNTS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BAGACCOUNTS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class BEIncoming 

        static const int
                BEINCOMING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BEINCOMING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int BEINCOMING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int BEINCOMING__OUTGOING = INCOMING__OUTGOING;

        static const int BEINCOMING__REFINPORT = INCOMING__REFINPORT;

        static const int BEINCOMING__REMOVESEQUENCENUMBER =
                CTINCOMING__REMOVESEQUENCENUMBER;

        static const int BEINCOMING__REDUNDANCYFUNCTION =
                CTINCOMING__REDUNDANCYFUNCTION;

        // IDs for classifiers for class BEOutgoing 

        static const int
                BEOUTGOING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BEOUTGOING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int BEOUTGOING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int BEOUTGOING__APPENDSEQUENCENUMBER =
                OUTGOING__APPENDSEQUENCENUMBER;

        static const int BEOUTGOING__REFOUTPORT = OUTGOING__REFOUTPORT;

        // IDs for classifiers for class BERouteIncoming 

        static const int
                BEROUTEINCOMING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BEROUTEINCOMING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int BEROUTEINCOMING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int BEROUTEINCOMING__OUTGOING = INCOMING__OUTGOING;

        static const int BEROUTEINCOMING__REFINPORT = INCOMING__REFINPORT;

        // IDs for classifiers for class BERouteOutgoing 

        static const int
                BEROUTEOUTGOING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BEROUTEOUTGOING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int BEROUTEOUTGOING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int BEROUTEOUTGOING__APPENDSEQUENCENUMBER =
                OUTGOING__APPENDSEQUENCENUMBER;

        static const int BEROUTEOUTGOING__REFOUTPORT = OUTGOING__REFOUTPORT;

        // IDs for classifiers for class BestEffortRouting 

        static const int
                BESTEFFORTROUTING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BESTEFFORTROUTING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

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

        // IDs for classifiers for class Buffers 

        static const int
                BUFFERS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BUFFERS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class CTIncoming 

        static const int
                CTINCOMING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                CTINCOMING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int CTINCOMING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int CTINCOMING__OUTGOING = INCOMING__OUTGOING;

        static const int CTINCOMING__REFINPORT = INCOMING__REFINPORT;

        // IDs for classifiers for class CTOutgoing 

        static const int
                CTOUTGOING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                CTOUTGOING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int CTOUTGOING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int CTOUTGOING__APPENDSEQUENCENUMBER =
                OUTGOING__APPENDSEQUENCENUMBER;

        static const int CTOUTGOING__REFOUTPORT = OUTGOING__REFOUTPORT;

        // IDs for classifiers for class DeviceConfig 

        static const int DEVICECONFIG__EANNOTATIONS =
                ::ecore::EcorePackage::EMODELELEMENT__EANNOTATIONS;

        static const int DEVICECONFIG__NAME =
                ::ecore::EcorePackage::ENAMEDELEMENT__NAME;

        // IDs for classifiers for class DeviceSpecification 

        static const int
                DEVICESPECIFICATION__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DEVICESPECIFICATION__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                DEVICESPECIFICATION__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class DualEntryBuffer 

        static const int
                DUALENTRYBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DUALENTRYBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                DUALENTRYBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class EndSystem 

        static const int
                ENDSYSTEM__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                ENDSYSTEM__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                ENDSYSTEM__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int ENDSYSTEM__METAINFORMATION =
                DEVICESPECIFICATION__METAINFORMATION;

        static const int ENDSYSTEM__UNITS = DEVICESPECIFICATION__UNITS;

        static const int ENDSYSTEM__BAGACCOUNTS =
                DEVICESPECIFICATION__BAGACCOUNTS;

        static const int ENDSYSTEM__VLSCHEDULES =
                DEVICESPECIFICATION__VLSCHEDULES;

        static const int ENDSYSTEM__BESTEFFORTROUTING =
                DEVICESPECIFICATION__BESTEFFORTROUTING;

        static const int ENDSYSTEM__FLOWCONTROL =
                DEVICESPECIFICATION__FLOWCONTROL;

        static const int ENDSYSTEM__PERIODS = DEVICESPECIFICATION__PERIODS;

        static const int ENDSYSTEM__REFDEVICEMAPPING =
                DEVICESPECIFICATION__REFDEVICEMAPPING;

        // IDs for classifiers for class EndSystemConfig 

        static const int ENDSYSTEMCONFIG__EANNOTATIONS =
                ::ecore::EcorePackage::EMODELELEMENT__EANNOTATIONS;

        static const int ENDSYSTEMCONFIG__NAME =
                ::ecore::EcorePackage::ENAMEDELEMENT__NAME;

        static const int ENDSYSTEMCONFIG__CTMARKER = DEVICECONFIG__CTMARKER;

        static const int ENDSYSTEMCONFIG__CTMASK = DEVICECONFIG__CTMASK;

        // IDs for classifiers for class ExternalClockSynchronization 

        static const int
                EXTERNALCLOCKSYNCHRONIZATION__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                EXTERNALCLOCKSYNCHRONIZATION__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class FIFOQueue 

        static const int
                FIFOQUEUE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                FIFOQUEUE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                FIFOQUEUE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class FlowControl 

        static const int
                FLOWCONTROL__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                FLOWCONTROL__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class FlowControlValue 

        static const int
                FLOWCONTROLVALUE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                FLOWCONTROLVALUE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class FrameRelayDescriptor 

        static const int
                FRAMERELAYDESCRIPTOR__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                FRAMERELAYDESCRIPTOR__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class Incoming 

        static const int
                INCOMING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                INCOMING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int INCOMING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        // IDs for classifiers for class IncomingBagAccount 

        static const int
                INCOMINGBAGACCOUNT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                INCOMINGBAGACCOUNT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                INCOMINGBAGACCOUNT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int INCOMINGBAGACCOUNT__BAG = BAGACCOUNT__BAG;

        static const int INCOMINGBAGACCOUNT__JITTER = BAGACCOUNT__JITTER;

        static const int INCOMINGBAGACCOUNT__CONSTRAINTYPE =
                BAGACCOUNT__CONSTRAINTYPE;

        // IDs for classifiers for class IntegrityCheck 

        static const int
                INTEGRITYCHECK__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                INTEGRITYCHECK__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class Outgoing 

        static const int
                OUTGOING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                OUTGOING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int OUTGOING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        // IDs for classifiers for class OutgoingBagAccount 

        static const int
                OUTGOINGBAGACCOUNT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                OUTGOINGBAGACCOUNT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                OUTGOINGBAGACCOUNT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int OUTGOINGBAGACCOUNT__BAG = BAGACCOUNT__BAG;

        static const int OUTGOINGBAGACCOUNT__JITTER = BAGACCOUNT__JITTER;

        static const int OUTGOINGBAGACCOUNT__CONSTRAINTYPE =
                BAGACCOUNT__CONSTRAINTYPE;

        // IDs for classifiers for class Periods 

        static const int
                PERIODS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PERIODS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class RCIncoming 

        static const int
                RCINCOMING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                RCINCOMING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int RCINCOMING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int RCINCOMING__OUTGOING = INCOMING__OUTGOING;

        static const int RCINCOMING__REFINPORT = INCOMING__REFINPORT;

        static const int RCINCOMING__REMOVESEQUENCENUMBER =
                CTINCOMING__REMOVESEQUENCENUMBER;

        static const int RCINCOMING__REDUNDANCYFUNCTION =
                CTINCOMING__REDUNDANCYFUNCTION;

        // IDs for classifiers for class RCOutgoing 

        static const int
                RCOUTGOING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                RCOUTGOING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int RCOUTGOING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int RCOUTGOING__APPENDSEQUENCENUMBER =
                OUTGOING__APPENDSEQUENCENUMBER;

        static const int RCOUTGOING__REFOUTPORT = OUTGOING__REFOUTPORT;

        // IDs for classifiers for class RCRedundancyManagement 

        static const int
                RCREDUNDANCYMANAGEMENT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                RCREDUNDANCYMANAGEMENT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int RCREDUNDANCYMANAGEMENT__REDUNDANCYTIMEOUT =
                REDUNDANCYMANAGEMENT__REDUNDANCYTIMEOUT;

        // IDs for classifiers for class RedundancyManagement 

        static const int
                REDUNDANCYMANAGEMENT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                REDUNDANCYMANAGEMENT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class SingleEntryBuffer 

        static const int
                SINGLEENTRYBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SINGLEENTRYBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SINGLEENTRYBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class Switch 

        static const int
                SWITCH__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SWITCH__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SWITCH__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int SWITCH__METAINFORMATION =
                DEVICESPECIFICATION__METAINFORMATION;

        static const int SWITCH__UNITS = DEVICESPECIFICATION__UNITS;

        static const int SWITCH__BAGACCOUNTS = DEVICESPECIFICATION__BAGACCOUNTS;

        static const int SWITCH__VLSCHEDULES = DEVICESPECIFICATION__VLSCHEDULES;

        static const int SWITCH__BESTEFFORTROUTING =
                DEVICESPECIFICATION__BESTEFFORTROUTING;

        static const int SWITCH__FLOWCONTROL = DEVICESPECIFICATION__FLOWCONTROL;

        static const int SWITCH__PERIODS = DEVICESPECIFICATION__PERIODS;

        static const int SWITCH__REFDEVICEMAPPING =
                DEVICESPECIFICATION__REFDEVICEMAPPING;

        // IDs for classifiers for class SwitchConfig 

        static const int SWITCHCONFIG__EANNOTATIONS =
                ::ecore::EcorePackage::EMODELELEMENT__EANNOTATIONS;

        static const int SWITCHCONFIG__NAME =
                ::ecore::EcorePackage::ENAMEDELEMENT__NAME;

        static const int SWITCHCONFIG__CTMARKER = DEVICECONFIG__CTMARKER;

        static const int SWITCHCONFIG__CTMASK = DEVICECONFIG__CTMASK;

        // IDs for classifiers for class TriggerSchedule 

        static const int
                TRIGGERSCHEDULE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TRIGGERSCHEDULE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TRIGGERSCHEDULE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class TriggerSchedules 

        static const int
                TRIGGERSCHEDULES__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TRIGGERSCHEDULES__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class TripleEntryBuffer 

        static const int
                TRIPLEENTRYBUFFER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TRIPLEENTRYBUFFER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TRIPLEENTRYBUFFER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class TTIncoming 

        static const int
                TTINCOMING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTINCOMING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int TTINCOMING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int TTINCOMING__OUTGOING = INCOMING__OUTGOING;

        static const int TTINCOMING__REFINPORT = INCOMING__REFINPORT;

        static const int TTINCOMING__REMOVESEQUENCENUMBER =
                CTINCOMING__REMOVESEQUENCENUMBER;

        static const int TTINCOMING__REDUNDANCYFUNCTION =
                CTINCOMING__REDUNDANCYFUNCTION;

        // IDs for classifiers for class TTOutgoing 

        static const int
                TTOUTGOING__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTOUTGOING__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int TTOUTGOING__BUFFERDEPTH =
                FRAMERELAYDESCRIPTOR__BUFFERDEPTH;

        static const int TTOUTGOING__APPENDSEQUENCENUMBER =
                OUTGOING__APPENDSEQUENCENUMBER;

        static const int TTOUTGOING__REFOUTPORT = OUTGOING__REFOUTPORT;

        // IDs for classifiers for class TTRedundancyManagement 

        static const int
                TTREDUNDANCYMANAGEMENT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTREDUNDANCYMANAGEMENT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int TTREDUNDANCYMANAGEMENT__REDUNDANCYTIMEOUT =
                REDUNDANCYMANAGEMENT__REDUNDANCYTIMEOUT;

        // IDs for classifiers for class VirtualLinkSchedule 

        static const int
                VIRTUALLINKSCHEDULE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                VIRTUALLINKSCHEDULE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class VirtualLinkSchedules 

        static const int
                VIRTUALLINKSCHEDULES__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                VIRTUALLINKSCHEDULES__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                VIRTUALLINKSCHEDULES__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getDeviceSpecification();

        virtual ::ecore::EClass_ptr getEndSystem();

        virtual ::ecore::EClass_ptr getSwitch();

        virtual ::ecore::EClass_ptr getDeviceConfig();

        virtual ::ecore::EClass_ptr getEndSystemConfig();

        virtual ::ecore::EClass_ptr getExternalClockSynchronization();

        virtual ::ecore::EClass_ptr getSwitchConfig();

        virtual ::ecore::EClass_ptr getBagAccounts();

        virtual ::ecore::EClass_ptr getBagAccount();

        virtual ::ecore::EClass_ptr getIncomingBagAccount();

        virtual ::ecore::EClass_ptr getOutgoingBagAccount();

        virtual ::ecore::EClass_ptr getVirtualLinkSchedules();

        virtual ::ecore::EClass_ptr getVirtualLinkSchedule();

        virtual ::ecore::EClass_ptr getBuffers();

        virtual ::ecore::EClass_ptr getBuffer();

        virtual ::ecore::EClass_ptr getFIFOQueue();

        virtual ::ecore::EClass_ptr getSingleEntryBuffer();

        virtual ::ecore::EClass_ptr getDualEntryBuffer();

        virtual ::ecore::EClass_ptr getTripleEntryBuffer();

        virtual ::ecore::EClass_ptr getIncoming();

        virtual ::ecore::EClass_ptr getCTIncoming();

        virtual ::ecore::EClass_ptr getOutgoing();

        virtual ::ecore::EClass_ptr getRCIncoming();

        virtual ::ecore::EClass_ptr getTTIncoming();

        virtual ::ecore::EClass_ptr getBEIncoming();

        virtual ::ecore::EClass_ptr getRCOutgoing();

        virtual ::ecore::EClass_ptr getCTOutgoing();

        virtual ::ecore::EClass_ptr getTTOutgoing();

        virtual ::ecore::EClass_ptr getBEOutgoing();

        virtual ::ecore::EClass_ptr getBestEffortRouting();

        virtual ::ecore::EClass_ptr getBERouteIncoming();

        virtual ::ecore::EClass_ptr getBERouteOutgoing();

        virtual ::ecore::EClass_ptr getFlowControl();

        virtual ::ecore::EClass_ptr getFlowControlValue();

        virtual ::ecore::EClass_ptr getTriggerSchedules();

        virtual ::ecore::EClass_ptr getTriggerSchedule();

        virtual ::ecore::EClass_ptr getIntegrityCheck();

        virtual ::ecore::EClass_ptr getRedundancyManagement();

        virtual ::ecore::EClass_ptr getRCRedundancyManagement();

        virtual ::ecore::EClass_ptr getTTRedundancyManagement();

        virtual ::ecore::EClass_ptr getPeriods();

        virtual ::ecore::EEnum_ptr getConstrainType();

        virtual ::ecore::EEnum_ptr getTimeSourceEnum();

        virtual ::ecore::EClass_ptr getFrameRelayDescriptor();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EReference_ptr
                getDeviceSpecification__metaInformation();

        virtual ::ecore::EReference_ptr getDeviceSpecification__units();

        virtual ::ecore::EReference_ptr getDeviceSpecification__bagAccounts();

        virtual ::ecore::EReference_ptr getDeviceSpecification__vlSchedules();

        virtual ::ecore::EReference_ptr
                getDeviceSpecification__bestEffortRouting();

        virtual ::ecore::EReference_ptr getDeviceSpecification__flowControl();

        virtual ::ecore::EReference_ptr getDeviceSpecification__periods();

        virtual ::ecore::EReference_ptr
                getDeviceSpecification__refDeviceMapping();

        virtual ::ecore::EReference_ptr getEndSystem__config();

        virtual ::ecore::EReference_ptr getEndSystem__triggerSchedules();

        virtual ::ecore::EReference_ptr getSwitch__config();

        virtual ::ecore::EReference_ptr getEModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getENamedElement__name();

        virtual ::ecore::EAttribute_ptr getDeviceConfig__ctMarker();

        virtual ::ecore::EAttribute_ptr getDeviceConfig__ctMask();

        virtual ::ecore::EAttribute_ptr getEndSystemConfig__tsSource();

        virtual ::ecore::EReference_ptr
                getEndSystemConfig__externalClockSynchronization();

        virtual ::ecore::EAttribute_ptr getEndSystemConfig__sourceMacAddress();

        virtual ::ecore::EAttribute_ptr getEndSystemConfig__destMacAddressCF();

        virtual ::ecore::EAttribute_ptr
                getEndSystemConfig__externalSyncAckRequired();

        virtual ::ecore::EAttribute_ptr
                getExternalClockSynchronization__maxExtCorrValue();

        virtual ::ecore::EReference_ptr getBagAccounts__incomingBagAccount();

        virtual ::ecore::EReference_ptr getBagAccounts__outgoingBagAccount();

        virtual ::ecore::EAttribute_ptr getBagAccount__bag();

        virtual ::ecore::EAttribute_ptr getBagAccount__jitter();

        virtual ::ecore::EAttribute_ptr getBagAccount__constrainType();

        virtual ::ecore::EReference_ptr getVirtualLinkSchedules__vlSchedule();

        virtual ::ecore::EAttribute_ptr
                getVirtualLinkSchedules__scheduleStartAfterSync();

        virtual ::ecore::EAttribute_ptr getVirtualLinkSchedule__priority();

        virtual ::ecore::EReference_ptr
                getVirtualLinkSchedule__refVirtualLink();

        virtual ::ecore::EReference_ptr getVirtualLinkSchedule__incoming();

        virtual ::ecore::EReference_ptr getBuffers__buffer();

        virtual ::ecore::EAttribute_ptr getFIFOQueue__length();

        virtual ::ecore::EAttribute_ptr getFrameRelayDescriptor__bufferDepth();

        virtual ::ecore::EReference_ptr getIncoming__outgoing();

        virtual ::ecore::EReference_ptr getIncoming__refInPort();

        virtual ::ecore::EAttribute_ptr getCTIncoming__removeSequenceNumber();

        virtual ::ecore::EReference_ptr getCTIncoming__redundancyFunction();

        virtual ::ecore::EAttribute_ptr getOutgoing__appendSequenceNumber();

        virtual ::ecore::EReference_ptr getOutgoing__refOutPort();

        virtual ::ecore::EReference_ptr getRCIncoming__refBagAccount();

        virtual ::ecore::EAttribute_ptr getTTIncoming__receiveWindowStart();

        virtual ::ecore::EAttribute_ptr getTTIncoming__receiveWindowEnd();

        virtual ::ecore::EAttribute_ptr getTTIncoming__permanencePit();

        virtual ::ecore::EReference_ptr getTTIncoming__refPeriod();

        virtual ::ecore::EReference_ptr getRCOutgoing__refBagAccount();

        virtual ::ecore::EAttribute_ptr getRCOutgoing__maxDispatchDelay();

        virtual ::ecore::EAttribute_ptr getTTOutgoing__sendWindowStart();

        virtual ::ecore::EAttribute_ptr getTTOutgoing__sendWindowEnd();

        virtual ::ecore::EReference_ptr getTTOutgoing__refPeriod();

        virtual ::ecore::EAttribute_ptr
                getBestEffortRouting__enableDynamicRouting();

        virtual ::ecore::EReference_ptr getBestEffortRouting__beRouteIncoming();

        virtual ::ecore::EAttribute_ptr
                getBERouteIncoming__destinationMacAddress();

        virtual ::ecore::EAttribute_ptr getBERouteIncoming__addrMask();

        virtual ::ecore::EReference_ptr getFlowControl__xon();

        virtual ::ecore::EReference_ptr getFlowControl__xoff();

        virtual ::ecore::EAttribute_ptr getFlowControlValue__value();

        virtual ::ecore::EAttribute_ptr getFlowControlValue__threshold();

        virtual ::ecore::EReference_ptr getTriggerSchedules__triggerSchedule();

        virtual ::ecore::EReference_ptr getTriggerSchedule__refPeriod();

        virtual ::ecore::EAttribute_ptr
                getRedundancyManagement__redundancyTimeout();

        virtual ::ecore::EAttribute_ptr
                getRCRedundancyManagement__maxSequenceNumberRange();

        virtual ::ecore::EReference_ptr getPeriods__period();

    protected:

        static std::auto_ptr< Device_SpecificationPackage > s_instance;

        Device_SpecificationPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_DeviceSpecificationEClass;

        ::ecore::EClass_ptr m_EndSystemEClass;

        ::ecore::EClass_ptr m_SwitchEClass;

        ::ecore::EClass_ptr m_DeviceConfigEClass;

        ::ecore::EClass_ptr m_EndSystemConfigEClass;

        ::ecore::EClass_ptr m_ExternalClockSynchronizationEClass;

        ::ecore::EClass_ptr m_SwitchConfigEClass;

        ::ecore::EClass_ptr m_BagAccountsEClass;

        ::ecore::EClass_ptr m_BagAccountEClass;

        ::ecore::EClass_ptr m_IncomingBagAccountEClass;

        ::ecore::EClass_ptr m_OutgoingBagAccountEClass;

        ::ecore::EClass_ptr m_VirtualLinkSchedulesEClass;

        ::ecore::EClass_ptr m_VirtualLinkScheduleEClass;

        ::ecore::EClass_ptr m_BuffersEClass;

        ::ecore::EClass_ptr m_BufferEClass;

        ::ecore::EClass_ptr m_FIFOQueueEClass;

        ::ecore::EClass_ptr m_SingleEntryBufferEClass;

        ::ecore::EClass_ptr m_DualEntryBufferEClass;

        ::ecore::EClass_ptr m_TripleEntryBufferEClass;

        ::ecore::EClass_ptr m_IncomingEClass;

        ::ecore::EClass_ptr m_CTIncomingEClass;

        ::ecore::EClass_ptr m_OutgoingEClass;

        ::ecore::EClass_ptr m_RCIncomingEClass;

        ::ecore::EClass_ptr m_TTIncomingEClass;

        ::ecore::EClass_ptr m_BEIncomingEClass;

        ::ecore::EClass_ptr m_RCOutgoingEClass;

        ::ecore::EClass_ptr m_CTOutgoingEClass;

        ::ecore::EClass_ptr m_TTOutgoingEClass;

        ::ecore::EClass_ptr m_BEOutgoingEClass;

        ::ecore::EClass_ptr m_BestEffortRoutingEClass;

        ::ecore::EClass_ptr m_BERouteIncomingEClass;

        ::ecore::EClass_ptr m_BERouteOutgoingEClass;

        ::ecore::EClass_ptr m_FlowControlEClass;

        ::ecore::EClass_ptr m_FlowControlValueEClass;

        ::ecore::EClass_ptr m_TriggerSchedulesEClass;

        ::ecore::EClass_ptr m_TriggerScheduleEClass;

        ::ecore::EClass_ptr m_IntegrityCheckEClass;

        ::ecore::EClass_ptr m_RedundancyManagementEClass;

        ::ecore::EClass_ptr m_RCRedundancyManagementEClass;

        ::ecore::EClass_ptr m_TTRedundancyManagementEClass;

        ::ecore::EClass_ptr m_PeriodsEClass;

        ::ecore::EClass_ptr m_FrameRelayDescriptorEClass;

        // EEnuminstances 

        ::ecore::EEnum_ptr m_ConstrainTypeEEnum;

        ::ecore::EEnum_ptr m_TimeSourceEnumEEnum;

        // EDataType instances 


        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EReference_ptr m_DeviceSpecification__metaInformation;

        ::ecore::EReference_ptr m_DeviceSpecification__units;

        ::ecore::EReference_ptr m_DeviceSpecification__bagAccounts;

        ::ecore::EReference_ptr m_DeviceSpecification__vlSchedules;

        ::ecore::EReference_ptr m_DeviceSpecification__bestEffortRouting;

        ::ecore::EReference_ptr m_DeviceSpecification__flowControl;

        ::ecore::EReference_ptr m_DeviceSpecification__periods;

        ::ecore::EReference_ptr m_DeviceSpecification__refDeviceMapping;

        ::ecore::EReference_ptr m_EndSystem__config;

        ::ecore::EReference_ptr m_EndSystem__triggerSchedules;

        ::ecore::EReference_ptr m_Switch__config;

        ::ecore::EReference_ptr m_EModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ENamedElement__name;

        ::ecore::EAttribute_ptr m_DeviceConfig__ctMarker;

        ::ecore::EAttribute_ptr m_DeviceConfig__ctMask;

        ::ecore::EAttribute_ptr m_EndSystemConfig__tsSource;

        ::ecore::EReference_ptr m_EndSystemConfig__externalClockSynchronization;

        ::ecore::EAttribute_ptr m_EndSystemConfig__sourceMacAddress;

        ::ecore::EAttribute_ptr m_EndSystemConfig__destMacAddressCF;

        ::ecore::EAttribute_ptr m_EndSystemConfig__externalSyncAckRequired;

        ::ecore::EAttribute_ptr m_ExternalClockSynchronization__maxExtCorrValue;

        ::ecore::EReference_ptr m_BagAccounts__incomingBagAccount;

        ::ecore::EReference_ptr m_BagAccounts__outgoingBagAccount;

        ::ecore::EAttribute_ptr m_BagAccount__bag;

        ::ecore::EAttribute_ptr m_BagAccount__jitter;

        ::ecore::EAttribute_ptr m_BagAccount__constrainType;

        ::ecore::EReference_ptr m_VirtualLinkSchedules__vlSchedule;

        ::ecore::EAttribute_ptr m_VirtualLinkSchedules__scheduleStartAfterSync;

        ::ecore::EAttribute_ptr m_VirtualLinkSchedule__priority;

        ::ecore::EReference_ptr m_VirtualLinkSchedule__refVirtualLink;

        ::ecore::EReference_ptr m_VirtualLinkSchedule__incoming;

        ::ecore::EReference_ptr m_Buffers__buffer;

        ::ecore::EAttribute_ptr m_FIFOQueue__length;

        ::ecore::EAttribute_ptr m_FrameRelayDescriptor__bufferDepth;

        ::ecore::EReference_ptr m_Incoming__outgoing;

        ::ecore::EReference_ptr m_Incoming__refInPort;

        ::ecore::EAttribute_ptr m_CTIncoming__removeSequenceNumber;

        ::ecore::EReference_ptr m_CTIncoming__redundancyFunction;

        ::ecore::EAttribute_ptr m_Outgoing__appendSequenceNumber;

        ::ecore::EReference_ptr m_Outgoing__refOutPort;

        ::ecore::EReference_ptr m_RCIncoming__refBagAccount;

        ::ecore::EAttribute_ptr m_TTIncoming__receiveWindowStart;

        ::ecore::EAttribute_ptr m_TTIncoming__receiveWindowEnd;

        ::ecore::EAttribute_ptr m_TTIncoming__permanencePit;

        ::ecore::EReference_ptr m_TTIncoming__refPeriod;

        ::ecore::EReference_ptr m_RCOutgoing__refBagAccount;

        ::ecore::EAttribute_ptr m_RCOutgoing__maxDispatchDelay;

        ::ecore::EAttribute_ptr m_TTOutgoing__sendWindowStart;

        ::ecore::EAttribute_ptr m_TTOutgoing__sendWindowEnd;

        ::ecore::EReference_ptr m_TTOutgoing__refPeriod;

        ::ecore::EAttribute_ptr m_BestEffortRouting__enableDynamicRouting;

        ::ecore::EReference_ptr m_BestEffortRouting__beRouteIncoming;

        ::ecore::EAttribute_ptr m_BERouteIncoming__destinationMacAddress;

        ::ecore::EAttribute_ptr m_BERouteIncoming__addrMask;

        ::ecore::EReference_ptr m_FlowControl__xon;

        ::ecore::EReference_ptr m_FlowControl__xoff;

        ::ecore::EAttribute_ptr m_FlowControlValue__value;

        ::ecore::EAttribute_ptr m_FlowControlValue__threshold;

        ::ecore::EReference_ptr m_TriggerSchedules__triggerSchedule;

        ::ecore::EReference_ptr m_TriggerSchedule__refPeriod;

        ::ecore::EAttribute_ptr m_RedundancyManagement__redundancyTimeout;

        ::ecore::EAttribute_ptr
                m_RCRedundancyManagement__maxSequenceNumberRange;

        ::ecore::EReference_ptr m_Periods__period;

    };

} // Device_Specification


#endif // _DEVICE_SPECIFICATIONPACKAGE_HPP
