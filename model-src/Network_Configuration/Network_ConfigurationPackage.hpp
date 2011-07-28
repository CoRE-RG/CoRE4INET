// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/Network_ConfigurationPackage.hpp
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

#ifndef _NETWORK_CONFIGURATIONPACKAGE_HPP
#define _NETWORK_CONFIGURATIONPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <Network_Configuration_forward.hpp>

#include <System_Specification/System_SpecificationPackage.hpp>

namespace Network_Configuration
{

    /*PROTECTED REGION ID(Network_Configuration_SALT) ENABLED START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 5000
    /*PROTECTED REGION END*/

    class Network_ConfigurationPackage: public virtual ::ecore::EPackage
    {
    public:

        static Network_ConfigurationPackage_ptr _instance();

        // IDs for classifiers

        static const int ACTIVESYNCCOMPONENT = SALT + 0;

        static const int ACTIVESYNCCOMPONENTINTEGRITYCONFIG = SALT + 1;

        static const int AVGMODEENUM = SALT + 2;

        static const int BUSGUARDIAN = SALT + 3;

        static const int CLIQUEDETECTION = SALT + 4;

        static const int COMPRESSIONMASTER = SALT + 5;

        static const int COMPRESSIONMASTERINTEGRITYCONFIG = SALT + 6;

        static const int DEVICEREFERRINGELEMENT = SALT + 7;

        static const int DISTRIBUTEDSYNCMASTER = SALT + 8;

        static const int FAULTTOLERANCEENUM = SALT + 9;

        static const int INTEGRITYCONFIGBASE = SALT + 10;

        static const int INTEGRITYCONFIGURATIONS = SALT + 11;

        static const int INTEGRITYLEVELENUM = SALT + 12;

        static const int NETWORKCONFIG = SALT + 13;

        static const int PERIODS = SALT + 14;

        static const int STANDALONESYNCMASTER = SALT + 15;

        static const int SYNCBASE = SALT + 16;

        static const int SYNCCLIENT = SALT + 17;

        static const int SYNCCLIENTINTEGRITYCONFIG = SALT + 18;

        static const int SYNCDOMAIN = SALT + 19;

        static const int SYNCHRONIZATION = SALT + 20;

        static const int SYNCMASTER = SALT + 21;

        static const int SYNCMASTERINTEGRITYCONFIG = SALT + 22;

        static const int SYNCPRIORITY = SALT + 23;

        static const int DEVICEREFERRINGELEMENT__REFDEVICESPECIFICATION = SALT
                + 0;

        static const int DEVICEREFERRINGELEMENT__REFSYNCCONFIGURATION = SALT
                + 1;

        static const int DEVICEREFERRINGELEMENT__REFDEVICE = SALT + 2;

        static const int NETWORKCONFIG__METAINFORMATION = SALT + 3;

        static const int NETWORKCONFIG__UNITS = SALT + 4;

        static const int NETWORKCONFIG__SYNCHRONIZATION = SALT + 5;

        static const int NETWORKCONFIG__DEVICEREFERRINGELEMENT = SALT + 6;

        static const int NETWORKCONFIG__REFSYSTEMSPECIFICATION = SALT + 7;

        static const int NETWORKCONFIG__REFMAPPINGS = SALT + 8;

        static const int NETWORKCONFIG__REFPROTOCOL = SALT + 9;

        static const int NETWORKCONFIG__PERIODS = SALT + 10;

        static const int NETWORKCONFIG__REFVIRTUALLINKMAPPING = SALT + 11;

        static const int SYNCHRONIZATION__SYNCDOMAIN = SALT + 12;

        static const int SYNCHRONIZATION__INTEGRITYCONFIGURATIONS = SALT + 13;

        static const int SYNCDOMAIN__SYNCDOMAINID = SALT + 14;

        static const int SYNCDOMAIN__CLUSTERCYCLEDURATION = SALT + 15;

        static const int SYNCDOMAIN__INTEGRATIONCYCLEDURATION = SALT + 16;

        static const int SYNCDOMAIN__MAXPCFTRANSMISSIONDELAY = SALT + 17;

        static const int SYNCDOMAIN__SYNCPRIORITY = SALT + 18;

        static const int SYNCDOMAIN__FAULTTOLERANCELEVEL = SALT + 19;

        static const int SYNCDOMAIN__INTEGRITYLEVEL = SALT + 20;

        static const int SYNCDOMAIN__AVGMODE = SALT + 21;

        static const int SYNCPRIORITY__VALUE = SALT + 22;

        static const int SYNCPRIORITY__SYNCCLIENT = SALT + 23;

        static const int SYNCPRIORITY__SYNCMASTER = SALT + 24;

        static const int SYNCPRIORITY__COMPRESSIONMASTER = SALT + 25;

        static const int SYNCBASE__SCHEDULEDRECEIVEPIT = SALT + 26;

        static const int SYNCBASE__ACCEPTANCEWINDOW = SALT + 27;

        static const int SYNCBASE__LISTENTIMEOUT = SALT + 28;

        static const int SYNCBASE__PRIORITYFALLBACKCYCLES = SALT + 29;

        static const int SYNCBASE__SYNCTOSTABLEENABLED = SALT + 30;

        static const int SYNCCLIENT__REFINTEGRITYCONFIG = SALT + 31;

        static const int ACTIVESYNCCOMPONENT__SOURCEMACADDRESS = SALT + 32;

        static const int ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION = SALT + 33;

        static const int COMPRESSIONMASTER__BUSGUARDIAN = SALT + 34;

        static const int COMPRESSIONMASTER__CLIQUEDETECTION = SALT + 35;

        static const int COMPRESSIONMASTER__OBSERVATIONWINDOWSIZE = SALT + 36;

        static const int COMPRESSIONMASTER__CAENABLETIMEOUT = SALT + 37;

        static const int COMPRESSIONMASTER__WAIT4IN0TIMEOUT = SALT + 38;

        static const int COMPRESSIONMASTER__REFINTEGRITYCONFIG = SALT + 39;

        static const int CLIQUEDETECTION__TENTATIVESYNCRELAYENABLED = SALT + 40;

        static const int CLIQUEDETECTION__SYNCRELAYENABLED = SALT + 41;

        static const int CLIQUEDETECTION__STABLERELAYENABLED = SALT + 42;

        static const int CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPASYNCENABLED =
                SALT + 43;

        static const int CLIQUEDETECTION__TENTATIVESYNCMEMBERSHIPSYNCENABLED =
                SALT + 44;

        static const int CLIQUEDETECTION__SYNCMEMBERSHIPASYNCENABLED = SALT
                + 45;

        static const int CLIQUEDETECTION__SYNCMEMBERSHIPSYNCENABLED = SALT + 46;

        static const int CLIQUEDETECTION__STABLEMEMBERSHIPASYNCENABLED = SALT
                + 47;

        static const int CLIQUEDETECTION__STABLEMEMBERSHIPSYNCENABLED = SALT
                + 48;

        static const int INTEGRITYCONFIGURATIONS__SYNCCLIENTINTEGRITYCONFIG =
                SALT + 49;

        static const int
                INTEGRITYCONFIGURATIONS__COMPRESSIONMASTERINTEGRITYCONFIG =
                        SALT + 50;

        static const int INTEGRITYCONFIGURATIONS__SYNCMASTERINTEGRITYCONFIG =
                SALT + 51;

        static const int INTEGRITYCONFIGURATIONS__NAME = SALT + 52;

        static const int INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD = SALT
                + 53;

        static const int INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES = SALT + 54;

        static const int INTEGRITYCONFIGBASE__NUMSTABLECYCLES = SALT + 55;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__WAITTHRESHOLDASYNC = SALT
                        + 56;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD =
                        SALT + 57;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD =
                        SALT + 58;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC =
                        SALT + 59;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC =
                        SALT + 60;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD =
                        SALT + 61;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDASYNC = SALT
                        + 62;

        static const int ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDSYNC =
                SALT + 63;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDASYNC = SALT
                        + 64;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDSYNC = SALT
                        + 65;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__INTEGRATETOTENTATIVETHRESHOLD =
                        SALT + 66;

        static const int SYNCMASTERINTEGRITYCONFIG__INTEGRATETOWAITTHRESHOLD =
                SALT + 67;

        static const int PERIODS__PERIOD = SALT + 68;

        static const int SYNCMASTER__MEMBERSHIPBIT = SALT + 69;

        static const int SYNCMASTER__INITIALINTEGRATIONCYCLE = SALT + 70;

        static const int SYNCMASTER__REFINTEGRITYCONFIG = SALT + 71;

        static const int SYNCMASTER__CAOFFSET = SALT + 72;

        static const int SYNCMASTER__COLDSTARTTIMEOUT = SALT + 73;

        static const int SYNCMASTER__CSOFFSET = SALT + 74;

        static const int SYNCMASTER__RESTARTTIMEOUTASYNC = SALT + 75;

        static const int SYNCMASTER__RESTARTTIMEOUTSYNC = SALT + 76;

        static const int SYNCMASTER__CLKSYNCFILTERMAX = SALT + 77;

        static const int SYNCMASTER__REFPCFVLIDCOLDSTART = SALT + 78;

        static const int SYNCMASTER__REFPCFVLIDCOLDSTARTACK = SALT + 79;

        // IDs for classifiers for class ActiveSyncComponent 

        static const int
                ACTIVESYNCCOMPONENT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                ACTIVESYNCCOMPONENT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                ACTIVESYNCCOMPONENT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int ACTIVESYNCCOMPONENT__SCHEDULEDRECEIVEPIT =
                SYNCBASE__SCHEDULEDRECEIVEPIT;

        static const int ACTIVESYNCCOMPONENT__ACCEPTANCEWINDOW =
                SYNCBASE__ACCEPTANCEWINDOW;

        static const int ACTIVESYNCCOMPONENT__LISTENTIMEOUT =
                SYNCBASE__LISTENTIMEOUT;

        static const int ACTIVESYNCCOMPONENT__PRIORITYFALLBACKCYCLES =
                SYNCBASE__PRIORITYFALLBACKCYCLES;

        static const int ACTIVESYNCCOMPONENT__SYNCTOSTABLEENABLED =
                SYNCBASE__SYNCTOSTABLEENABLED;

        // IDs for classifiers for class ActiveSyncComponentIntegrityConfig 

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__INTEGRATETOSYNCTHRESHOLD =
                        INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD;

        static const int ACTIVESYNCCOMPONENTINTEGRITYCONFIG__NUMUNSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES;

        static const int ACTIVESYNCCOMPONENTINTEGRITYCONFIG__NUMSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMSTABLECYCLES;

        // IDs for classifiers for class BusGuardian 

        static const int
                BUSGUARDIAN__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                BUSGUARDIAN__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class CliqueDetection 

        static const int
                CLIQUEDETECTION__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                CLIQUEDETECTION__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class CompressionMaster 

        static const int
                COMPRESSIONMASTER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                COMPRESSIONMASTER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                COMPRESSIONMASTER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int COMPRESSIONMASTER__SCHEDULEDRECEIVEPIT =
                SYNCBASE__SCHEDULEDRECEIVEPIT;

        static const int COMPRESSIONMASTER__ACCEPTANCEWINDOW =
                SYNCBASE__ACCEPTANCEWINDOW;

        static const int COMPRESSIONMASTER__LISTENTIMEOUT =
                SYNCBASE__LISTENTIMEOUT;

        static const int COMPRESSIONMASTER__PRIORITYFALLBACKCYCLES =
                SYNCBASE__PRIORITYFALLBACKCYCLES;

        static const int COMPRESSIONMASTER__SYNCTOSTABLEENABLED =
                SYNCBASE__SYNCTOSTABLEENABLED;

        static const int COMPRESSIONMASTER__SOURCEMACADDRESS =
                ACTIVESYNCCOMPONENT__SOURCEMACADDRESS;

        static const int COMPRESSIONMASTER__REFPCFVLIDINTEGRATION =
                ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION;

        // IDs for classifiers for class CompressionMasterIntegrityConfig 

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__INTEGRATETOSYNCTHRESHOLD =
                        INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD;

        static const int COMPRESSIONMASTERINTEGRITYCONFIG__NUMUNSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES;

        static const int COMPRESSIONMASTERINTEGRITYCONFIG__NUMSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMSTABLECYCLES;

        static const int COMPRESSIONMASTERINTEGRITYCONFIG__WAITTHRESHOLDASYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__WAITTHRESHOLDASYNC;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD =
                        ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD =
                        ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC =
                        ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC =
                        ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD =
                        ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD;

        static const int COMPRESSIONMASTERINTEGRITYCONFIG__SYNCTHRESHOLDASYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDASYNC;

        static const int COMPRESSIONMASTERINTEGRITYCONFIG__SYNCTHRESHOLDSYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDSYNC;

        static const int
                COMPRESSIONMASTERINTEGRITYCONFIG__STABLETHRESHOLDASYNC =
                        ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDASYNC;

        static const int COMPRESSIONMASTERINTEGRITYCONFIG__STABLETHRESHOLDSYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDSYNC;

        // IDs for classifiers for class DeviceReferringElement 

        static const int
                DEVICEREFERRINGELEMENT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DEVICEREFERRINGELEMENT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                DEVICEREFERRINGELEMENT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class DistributedSyncMaster 

        static const int
                DISTRIBUTEDSYNCMASTER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                DISTRIBUTEDSYNCMASTER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                DISTRIBUTEDSYNCMASTER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int DISTRIBUTEDSYNCMASTER__SCHEDULEDRECEIVEPIT =
                SYNCBASE__SCHEDULEDRECEIVEPIT;

        static const int DISTRIBUTEDSYNCMASTER__ACCEPTANCEWINDOW =
                SYNCBASE__ACCEPTANCEWINDOW;

        static const int DISTRIBUTEDSYNCMASTER__LISTENTIMEOUT =
                SYNCBASE__LISTENTIMEOUT;

        static const int DISTRIBUTEDSYNCMASTER__PRIORITYFALLBACKCYCLES =
                SYNCBASE__PRIORITYFALLBACKCYCLES;

        static const int DISTRIBUTEDSYNCMASTER__SYNCTOSTABLEENABLED =
                SYNCBASE__SYNCTOSTABLEENABLED;

        static const int DISTRIBUTEDSYNCMASTER__SOURCEMACADDRESS =
                ACTIVESYNCCOMPONENT__SOURCEMACADDRESS;

        static const int DISTRIBUTEDSYNCMASTER__REFPCFVLIDINTEGRATION =
                ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION;

        static const int DISTRIBUTEDSYNCMASTER__MEMBERSHIPBIT =
                SYNCMASTER__MEMBERSHIPBIT;

        static const int DISTRIBUTEDSYNCMASTER__INITIALINTEGRATIONCYCLE =
                SYNCMASTER__INITIALINTEGRATIONCYCLE;

        static const int DISTRIBUTEDSYNCMASTER__REFINTEGRITYCONFIG =
                SYNCMASTER__REFINTEGRITYCONFIG;

        static const int DISTRIBUTEDSYNCMASTER__CAOFFSET = SYNCMASTER__CAOFFSET;

        static const int DISTRIBUTEDSYNCMASTER__COLDSTARTTIMEOUT =
                SYNCMASTER__COLDSTARTTIMEOUT;

        static const int DISTRIBUTEDSYNCMASTER__CSOFFSET = SYNCMASTER__CSOFFSET;

        static const int DISTRIBUTEDSYNCMASTER__RESTARTTIMEOUTASYNC =
                SYNCMASTER__RESTARTTIMEOUTASYNC;

        static const int DISTRIBUTEDSYNCMASTER__RESTARTTIMEOUTSYNC =
                SYNCMASTER__RESTARTTIMEOUTSYNC;

        static const int DISTRIBUTEDSYNCMASTER__CLKSYNCFILTERMAX =
                SYNCMASTER__CLKSYNCFILTERMAX;

        static const int DISTRIBUTEDSYNCMASTER__REFPCFVLIDCOLDSTART =
                SYNCMASTER__REFPCFVLIDCOLDSTART;

        static const int DISTRIBUTEDSYNCMASTER__REFPCFVLIDCOLDSTARTACK =
                SYNCMASTER__REFPCFVLIDCOLDSTARTACK;

        // IDs for classifiers for class IntegrityConfigBase 

        static const int
                INTEGRITYCONFIGBASE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                INTEGRITYCONFIGBASE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                INTEGRITYCONFIGBASE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class IntegrityConfigurations 

        static const int
                INTEGRITYCONFIGURATIONS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                INTEGRITYCONFIGURATIONS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class NetworkConfig 

        static const int
                NETWORKCONFIG__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                NETWORKCONFIG__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class Periods 

        static const int
                PERIODS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                PERIODS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class StandaloneSyncMaster 

        static const int
                STANDALONESYNCMASTER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                STANDALONESYNCMASTER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                STANDALONESYNCMASTER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int STANDALONESYNCMASTER__SCHEDULEDRECEIVEPIT =
                SYNCBASE__SCHEDULEDRECEIVEPIT;

        static const int STANDALONESYNCMASTER__ACCEPTANCEWINDOW =
                SYNCBASE__ACCEPTANCEWINDOW;

        static const int STANDALONESYNCMASTER__LISTENTIMEOUT =
                SYNCBASE__LISTENTIMEOUT;

        static const int STANDALONESYNCMASTER__PRIORITYFALLBACKCYCLES =
                SYNCBASE__PRIORITYFALLBACKCYCLES;

        static const int STANDALONESYNCMASTER__SYNCTOSTABLEENABLED =
                SYNCBASE__SYNCTOSTABLEENABLED;

        static const int STANDALONESYNCMASTER__SOURCEMACADDRESS =
                ACTIVESYNCCOMPONENT__SOURCEMACADDRESS;

        static const int STANDALONESYNCMASTER__REFPCFVLIDINTEGRATION =
                ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION;

        static const int STANDALONESYNCMASTER__MEMBERSHIPBIT =
                SYNCMASTER__MEMBERSHIPBIT;

        static const int STANDALONESYNCMASTER__INITIALINTEGRATIONCYCLE =
                SYNCMASTER__INITIALINTEGRATIONCYCLE;

        static const int STANDALONESYNCMASTER__REFINTEGRITYCONFIG =
                SYNCMASTER__REFINTEGRITYCONFIG;

        static const int STANDALONESYNCMASTER__CAOFFSET = SYNCMASTER__CAOFFSET;

        static const int STANDALONESYNCMASTER__COLDSTARTTIMEOUT =
                SYNCMASTER__COLDSTARTTIMEOUT;

        static const int STANDALONESYNCMASTER__CSOFFSET = SYNCMASTER__CSOFFSET;

        static const int STANDALONESYNCMASTER__RESTARTTIMEOUTASYNC =
                SYNCMASTER__RESTARTTIMEOUTASYNC;

        static const int STANDALONESYNCMASTER__RESTARTTIMEOUTSYNC =
                SYNCMASTER__RESTARTTIMEOUTSYNC;

        static const int STANDALONESYNCMASTER__CLKSYNCFILTERMAX =
                SYNCMASTER__CLKSYNCFILTERMAX;

        static const int STANDALONESYNCMASTER__REFPCFVLIDCOLDSTART =
                SYNCMASTER__REFPCFVLIDCOLDSTART;

        static const int STANDALONESYNCMASTER__REFPCFVLIDCOLDSTARTACK =
                SYNCMASTER__REFPCFVLIDCOLDSTARTACK;

        // IDs for classifiers for class SyncBase 

        static const int
                SYNCBASE__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCBASE__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SYNCBASE__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class SyncClient 

        static const int
                SYNCCLIENT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCCLIENT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SYNCCLIENT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int SYNCCLIENT__SCHEDULEDRECEIVEPIT =
                SYNCBASE__SCHEDULEDRECEIVEPIT;

        static const int SYNCCLIENT__ACCEPTANCEWINDOW =
                SYNCBASE__ACCEPTANCEWINDOW;

        static const int SYNCCLIENT__LISTENTIMEOUT = SYNCBASE__LISTENTIMEOUT;

        static const int SYNCCLIENT__PRIORITYFALLBACKCYCLES =
                SYNCBASE__PRIORITYFALLBACKCYCLES;

        static const int SYNCCLIENT__SYNCTOSTABLEENABLED =
                SYNCBASE__SYNCTOSTABLEENABLED;

        // IDs for classifiers for class SyncClientIntegrityConfig 

        static const int
                SYNCCLIENTINTEGRITYCONFIG__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCCLIENTINTEGRITYCONFIG__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SYNCCLIENTINTEGRITYCONFIG__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int SYNCCLIENTINTEGRITYCONFIG__INTEGRATETOSYNCTHRESHOLD =
                INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD;

        static const int SYNCCLIENTINTEGRITYCONFIG__NUMUNSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES;

        static const int SYNCCLIENTINTEGRITYCONFIG__NUMSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMSTABLECYCLES;

        // IDs for classifiers for class SyncDomain 

        static const int
                SYNCDOMAIN__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCDOMAIN__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SYNCDOMAIN__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class Synchronization 

        static const int
                SYNCHRONIZATION__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCHRONIZATION__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SYNCHRONIZATION__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class SyncMaster 

        static const int
                SYNCMASTER__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCMASTER__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SYNCMASTER__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int SYNCMASTER__SCHEDULEDRECEIVEPIT =
                SYNCBASE__SCHEDULEDRECEIVEPIT;

        static const int SYNCMASTER__ACCEPTANCEWINDOW =
                SYNCBASE__ACCEPTANCEWINDOW;

        static const int SYNCMASTER__LISTENTIMEOUT = SYNCBASE__LISTENTIMEOUT;

        static const int SYNCMASTER__PRIORITYFALLBACKCYCLES =
                SYNCBASE__PRIORITYFALLBACKCYCLES;

        static const int SYNCMASTER__SYNCTOSTABLEENABLED =
                SYNCBASE__SYNCTOSTABLEENABLED;

        static const int SYNCMASTER__SOURCEMACADDRESS =
                ACTIVESYNCCOMPONENT__SOURCEMACADDRESS;

        static const int SYNCMASTER__REFPCFVLIDINTEGRATION =
                ACTIVESYNCCOMPONENT__REFPCFVLIDINTEGRATION;

        // IDs for classifiers for class SyncMasterIntegrityConfig 

        static const int
                SYNCMASTERINTEGRITYCONFIG__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCMASTERINTEGRITYCONFIG__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                SYNCMASTERINTEGRITYCONFIG__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int SYNCMASTERINTEGRITYCONFIG__INTEGRATETOSYNCTHRESHOLD =
                INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD;

        static const int SYNCMASTERINTEGRITYCONFIG__NUMUNSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES;

        static const int SYNCMASTERINTEGRITYCONFIG__NUMSTABLECYCLES =
                INTEGRITYCONFIGBASE__NUMSTABLECYCLES;

        static const int SYNCMASTERINTEGRITYCONFIG__WAITTHRESHOLDASYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__WAITTHRESHOLDASYNC;

        static const int SYNCMASTERINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOSYNCTHRESHOLD;

        static const int SYNCMASTERINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__UNSYNCTOTENTATIVETHRESHOLD;

        static const int
                SYNCMASTERINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC =
                        ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDASYNC;

        static const int SYNCMASTERINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVESYNCTHRESHOLDSYNC;

        static const int SYNCMASTERINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__TENTATIVETOSYNCTHRESHOLD;

        static const int SYNCMASTERINTEGRITYCONFIG__SYNCTHRESHOLDASYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDASYNC;

        static const int SYNCMASTERINTEGRITYCONFIG__SYNCTHRESHOLDSYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__SYNCTHRESHOLDSYNC;

        static const int SYNCMASTERINTEGRITYCONFIG__STABLETHRESHOLDASYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDASYNC;

        static const int SYNCMASTERINTEGRITYCONFIG__STABLETHRESHOLDSYNC =
                ACTIVESYNCCOMPONENTINTEGRITYCONFIG__STABLETHRESHOLDSYNC;

        // IDs for classifiers for class SyncPriority 

        static const int
                SYNCPRIORITY__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                SYNCPRIORITY__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getDeviceReferringElement();

        virtual ::ecore::EClass_ptr getNetworkConfig();

        virtual ::ecore::EClass_ptr getSynchronization();

        virtual ::ecore::EClass_ptr getSyncDomain();

        virtual ::ecore::EClass_ptr getSyncPriority();

        virtual ::ecore::EClass_ptr getSyncBase();

        virtual ::ecore::EClass_ptr getSyncClient();

        virtual ::ecore::EClass_ptr getActiveSyncComponent();

        virtual ::ecore::EClass_ptr getDistributedSyncMaster();

        virtual ::ecore::EClass_ptr getCompressionMaster();

        virtual ::ecore::EClass_ptr getCliqueDetection();

        virtual ::ecore::EClass_ptr getBusGuardian();

        virtual ::ecore::EClass_ptr getIntegrityConfigurations();

        virtual ::ecore::EClass_ptr getIntegrityConfigBase();

        virtual ::ecore::EClass_ptr getSyncClientIntegrityConfig();

        virtual ::ecore::EClass_ptr getActiveSyncComponentIntegrityConfig();

        virtual ::ecore::EClass_ptr getCompressionMasterIntegrityConfig();

        virtual ::ecore::EClass_ptr getSyncMasterIntegrityConfig();

        virtual ::ecore::EClass_ptr getPeriods();

        virtual ::ecore::EEnum_ptr getAvgModeEnum();

        virtual ::ecore::EEnum_ptr getFaultToleranceEnum();

        virtual ::ecore::EEnum_ptr getIntegrityLevelEnum();

        virtual ::ecore::EClass_ptr getSyncMaster();

        virtual ::ecore::EClass_ptr getStandaloneSyncMaster();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EReference_ptr
                getDeviceReferringElement__refDeviceSpecification();

        virtual ::ecore::EReference_ptr
                getDeviceReferringElement__refSyncConfiguration();

        virtual ::ecore::EReference_ptr getDeviceReferringElement__refDevice();

        virtual ::ecore::EReference_ptr getNetworkConfig__metaInformation();

        virtual ::ecore::EReference_ptr getNetworkConfig__units();

        virtual ::ecore::EReference_ptr getNetworkConfig__synchronization();

        virtual ::ecore::EReference_ptr
                getNetworkConfig__deviceReferringElement();

        virtual ::ecore::EReference_ptr
                getNetworkConfig__refSystemSpecification();

        virtual ::ecore::EReference_ptr getNetworkConfig__refMappings();

        virtual ::ecore::EReference_ptr getNetworkConfig__refProtocol();

        virtual ::ecore::EReference_ptr getNetworkConfig__periods();

        virtual ::ecore::EReference_ptr
                getNetworkConfig__refVirtualLinkMapping();

        virtual ::ecore::EReference_ptr getSynchronization__syncDomain();

        virtual ::ecore::EReference_ptr
                getSynchronization__integrityConfigurations();

        virtual ::ecore::EAttribute_ptr getSyncDomain__syncDomainId();

        virtual ::ecore::EAttribute_ptr getSyncDomain__clusterCycleDuration();

        virtual ::ecore::EAttribute_ptr
                getSyncDomain__integrationCycleDuration();

        virtual ::ecore::EAttribute_ptr
                getSyncDomain__maxPcfTransmissionDelay();

        virtual ::ecore::EReference_ptr getSyncDomain__syncPriority();

        virtual ::ecore::EAttribute_ptr getSyncDomain__faultToleranceLevel();

        virtual ::ecore::EAttribute_ptr getSyncDomain__integrityLevel();

        virtual ::ecore::EAttribute_ptr getSyncDomain__avgMode();

        virtual ::ecore::EAttribute_ptr getSyncPriority__value();

        virtual ::ecore::EReference_ptr getSyncPriority__syncClient();

        virtual ::ecore::EReference_ptr getSyncPriority__syncMaster();

        virtual ::ecore::EReference_ptr getSyncPriority__compressionMaster();

        virtual ::ecore::EAttribute_ptr getSyncBase__scheduledReceivePit();

        virtual ::ecore::EAttribute_ptr getSyncBase__acceptanceWindow();

        virtual ::ecore::EAttribute_ptr getSyncBase__listenTimeout();

        virtual ::ecore::EAttribute_ptr getSyncBase__priorityFallbackCycles();

        virtual ::ecore::EAttribute_ptr getSyncBase__syncToStableEnabled();

        virtual ::ecore::EReference_ptr getSyncClient__refIntegrityConfig();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponent__sourceMacAddress();

        virtual ::ecore::EReference_ptr
                getActiveSyncComponent__refPcfVlidIntegration();

        virtual ::ecore::EAttribute_ptr getSyncMaster__membershipBit();

        virtual ::ecore::EAttribute_ptr
                getSyncMaster__initialIntegrationCycle();

        virtual ::ecore::EReference_ptr getSyncMaster__refIntegrityConfig();

        virtual ::ecore::EAttribute_ptr getSyncMaster__caOffset();

        virtual ::ecore::EAttribute_ptr getSyncMaster__coldstartTimeout();

        virtual ::ecore::EAttribute_ptr getSyncMaster__csOffset();

        virtual ::ecore::EAttribute_ptr getSyncMaster__restartTimeoutAsync();

        virtual ::ecore::EAttribute_ptr getSyncMaster__restartTimeoutSync();

        virtual ::ecore::EAttribute_ptr getSyncMaster__clksyncFilterMax();

        virtual ::ecore::EReference_ptr getSyncMaster__refPcfVlidColdstart();

        virtual ::ecore::EReference_ptr getSyncMaster__refPcfVlidColdstartAck();

        virtual ::ecore::EReference_ptr getCompressionMaster__busGuardian();

        virtual ::ecore::EReference_ptr getCompressionMaster__cliqueDetection();

        virtual ::ecore::EAttribute_ptr
                getCompressionMaster__observationWindowSize();

        virtual ::ecore::EAttribute_ptr getCompressionMaster__caEnableTimeout();

        virtual ::ecore::EAttribute_ptr getCompressionMaster__wait4in0Timeout();

        virtual ::ecore::EReference_ptr
                getCompressionMaster__refIntegrityConfig();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__tentativeSyncRelayEnabled();

        virtual ::ecore::EAttribute_ptr getCliqueDetection__syncRelayEnabled();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__stableRelayEnabled();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__tentativeSyncMembershipAsyncEnabled();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__tentativeSyncMembershipSyncEnabled();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__syncMembershipAsyncEnabled();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__syncMembershipSyncEnabled();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__stableMembershipAsyncEnabled();

        virtual ::ecore::EAttribute_ptr
                getCliqueDetection__stableMembershipSyncEnabled();

        virtual ::ecore::EReference_ptr
                getIntegrityConfigurations__syncClientIntegrityConfig();

        virtual ::ecore::EReference_ptr
                getIntegrityConfigurations__compressionMasterIntegrityConfig();

        virtual ::ecore::EReference_ptr
                getIntegrityConfigurations__syncMasterIntegrityConfig();

        virtual ::ecore::EAttribute_ptr getIntegrityConfigurations__name();

        virtual ::ecore::EAttribute_ptr
                getIntegrityConfigBase__integrateToSyncThreshold();

        virtual ::ecore::EAttribute_ptr
                getIntegrityConfigBase__numUnstableCycles();

        virtual ::ecore::EAttribute_ptr
                getIntegrityConfigBase__numStableCycles();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__waitThresholdAsync();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__syncThresholdAsync();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__syncThresholdSync();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__stableThresholdAsync();

        virtual ::ecore::EAttribute_ptr
                getActiveSyncComponentIntegrityConfig__stableThresholdSync();

        virtual ::ecore::EAttribute_ptr
                getCompressionMasterIntegrityConfig__integrateToTentativeThreshold();

        virtual ::ecore::EAttribute_ptr
                getSyncMasterIntegrityConfig__integrateToWaitThreshold();

        virtual ::ecore::EReference_ptr getPeriods__period();

    protected:

        static std::auto_ptr< Network_ConfigurationPackage > s_instance;

        Network_ConfigurationPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_DeviceReferringElementEClass;

        ::ecore::EClass_ptr m_NetworkConfigEClass;

        ::ecore::EClass_ptr m_SynchronizationEClass;

        ::ecore::EClass_ptr m_SyncDomainEClass;

        ::ecore::EClass_ptr m_SyncPriorityEClass;

        ::ecore::EClass_ptr m_SyncBaseEClass;

        ::ecore::EClass_ptr m_SyncClientEClass;

        ::ecore::EClass_ptr m_ActiveSyncComponentEClass;

        ::ecore::EClass_ptr m_DistributedSyncMasterEClass;

        ::ecore::EClass_ptr m_CompressionMasterEClass;

        ::ecore::EClass_ptr m_CliqueDetectionEClass;

        ::ecore::EClass_ptr m_BusGuardianEClass;

        ::ecore::EClass_ptr m_IntegrityConfigurationsEClass;

        ::ecore::EClass_ptr m_IntegrityConfigBaseEClass;

        ::ecore::EClass_ptr m_SyncClientIntegrityConfigEClass;

        ::ecore::EClass_ptr m_ActiveSyncComponentIntegrityConfigEClass;

        ::ecore::EClass_ptr m_CompressionMasterIntegrityConfigEClass;

        ::ecore::EClass_ptr m_SyncMasterIntegrityConfigEClass;

        ::ecore::EClass_ptr m_PeriodsEClass;

        ::ecore::EClass_ptr m_SyncMasterEClass;

        ::ecore::EClass_ptr m_StandaloneSyncMasterEClass;

        // EEnuminstances 

        ::ecore::EEnum_ptr m_AvgModeEnumEEnum;

        ::ecore::EEnum_ptr m_FaultToleranceEnumEEnum;

        ::ecore::EEnum_ptr m_IntegrityLevelEnumEEnum;

        // EDataType instances 


        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EReference_ptr
                m_DeviceReferringElement__refDeviceSpecification;

        ::ecore::EReference_ptr m_DeviceReferringElement__refSyncConfiguration;

        ::ecore::EReference_ptr m_DeviceReferringElement__refDevice;

        ::ecore::EReference_ptr m_NetworkConfig__metaInformation;

        ::ecore::EReference_ptr m_NetworkConfig__units;

        ::ecore::EReference_ptr m_NetworkConfig__synchronization;

        ::ecore::EReference_ptr m_NetworkConfig__deviceReferringElement;

        ::ecore::EReference_ptr m_NetworkConfig__refSystemSpecification;

        ::ecore::EReference_ptr m_NetworkConfig__refMappings;

        ::ecore::EReference_ptr m_NetworkConfig__refProtocol;

        ::ecore::EReference_ptr m_NetworkConfig__periods;

        ::ecore::EReference_ptr m_NetworkConfig__refVirtualLinkMapping;

        ::ecore::EReference_ptr m_Synchronization__syncDomain;

        ::ecore::EReference_ptr m_Synchronization__integrityConfigurations;

        ::ecore::EAttribute_ptr m_SyncDomain__syncDomainId;

        ::ecore::EAttribute_ptr m_SyncDomain__clusterCycleDuration;

        ::ecore::EAttribute_ptr m_SyncDomain__integrationCycleDuration;

        ::ecore::EAttribute_ptr m_SyncDomain__maxPcfTransmissionDelay;

        ::ecore::EReference_ptr m_SyncDomain__syncPriority;

        ::ecore::EAttribute_ptr m_SyncDomain__faultToleranceLevel;

        ::ecore::EAttribute_ptr m_SyncDomain__integrityLevel;

        ::ecore::EAttribute_ptr m_SyncDomain__avgMode;

        ::ecore::EAttribute_ptr m_SyncPriority__value;

        ::ecore::EReference_ptr m_SyncPriority__syncClient;

        ::ecore::EReference_ptr m_SyncPriority__syncMaster;

        ::ecore::EReference_ptr m_SyncPriority__compressionMaster;

        ::ecore::EAttribute_ptr m_SyncBase__scheduledReceivePit;

        ::ecore::EAttribute_ptr m_SyncBase__acceptanceWindow;

        ::ecore::EAttribute_ptr m_SyncBase__listenTimeout;

        ::ecore::EAttribute_ptr m_SyncBase__priorityFallbackCycles;

        ::ecore::EAttribute_ptr m_SyncBase__syncToStableEnabled;

        ::ecore::EReference_ptr m_SyncClient__refIntegrityConfig;

        ::ecore::EAttribute_ptr m_ActiveSyncComponent__sourceMacAddress;

        ::ecore::EReference_ptr m_ActiveSyncComponent__refPcfVlidIntegration;

        ::ecore::EAttribute_ptr m_SyncMaster__membershipBit;

        ::ecore::EAttribute_ptr m_SyncMaster__initialIntegrationCycle;

        ::ecore::EReference_ptr m_SyncMaster__refIntegrityConfig;

        ::ecore::EAttribute_ptr m_SyncMaster__caOffset;

        ::ecore::EAttribute_ptr m_SyncMaster__coldstartTimeout;

        ::ecore::EAttribute_ptr m_SyncMaster__csOffset;

        ::ecore::EAttribute_ptr m_SyncMaster__restartTimeoutAsync;

        ::ecore::EAttribute_ptr m_SyncMaster__restartTimeoutSync;

        ::ecore::EAttribute_ptr m_SyncMaster__clksyncFilterMax;

        ::ecore::EReference_ptr m_SyncMaster__refPcfVlidColdstart;

        ::ecore::EReference_ptr m_SyncMaster__refPcfVlidColdstartAck;

        ::ecore::EReference_ptr m_CompressionMaster__busGuardian;

        ::ecore::EReference_ptr m_CompressionMaster__cliqueDetection;

        ::ecore::EAttribute_ptr m_CompressionMaster__observationWindowSize;

        ::ecore::EAttribute_ptr m_CompressionMaster__caEnableTimeout;

        ::ecore::EAttribute_ptr m_CompressionMaster__wait4in0Timeout;

        ::ecore::EReference_ptr m_CompressionMaster__refIntegrityConfig;

        ::ecore::EAttribute_ptr m_CliqueDetection__tentativeSyncRelayEnabled;

        ::ecore::EAttribute_ptr m_CliqueDetection__syncRelayEnabled;

        ::ecore::EAttribute_ptr m_CliqueDetection__stableRelayEnabled;

        ::ecore::EAttribute_ptr
                m_CliqueDetection__tentativeSyncMembershipAsyncEnabled;

        ::ecore::EAttribute_ptr
                m_CliqueDetection__tentativeSyncMembershipSyncEnabled;

        ::ecore::EAttribute_ptr m_CliqueDetection__syncMembershipAsyncEnabled;

        ::ecore::EAttribute_ptr m_CliqueDetection__syncMembershipSyncEnabled;

        ::ecore::EAttribute_ptr m_CliqueDetection__stableMembershipAsyncEnabled;

        ::ecore::EAttribute_ptr m_CliqueDetection__stableMembershipSyncEnabled;

        ::ecore::EReference_ptr
                m_IntegrityConfigurations__syncClientIntegrityConfig;

        ::ecore::EReference_ptr
                m_IntegrityConfigurations__compressionMasterIntegrityConfig;

        ::ecore::EReference_ptr
                m_IntegrityConfigurations__syncMasterIntegrityConfig;

        ::ecore::EAttribute_ptr m_IntegrityConfigurations__name;

        ::ecore::EAttribute_ptr m_IntegrityConfigBase__integrateToSyncThreshold;

        ::ecore::EAttribute_ptr m_IntegrityConfigBase__numUnstableCycles;

        ::ecore::EAttribute_ptr m_IntegrityConfigBase__numStableCycles;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__waitThresholdAsync;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__unsyncToSyncThreshold;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__unsyncToTentativeThreshold;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdAsync;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__tentativeSyncThresholdSync;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__tentativeToSyncThreshold;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__syncThresholdAsync;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__syncThresholdSync;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__stableThresholdAsync;

        ::ecore::EAttribute_ptr
                m_ActiveSyncComponentIntegrityConfig__stableThresholdSync;

        ::ecore::EAttribute_ptr
                m_CompressionMasterIntegrityConfig__integrateToTentativeThreshold;

        ::ecore::EAttribute_ptr
                m_SyncMasterIntegrityConfig__integrateToWaitThreshold;

        ::ecore::EReference_ptr m_Periods__period;

    };

} // Network_Configuration


#endif // _NETWORK_CONFIGURATIONPACKAGE_HPP
