// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IP_ConfigurationPackage.hpp
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

#ifndef _IP_CONFIGURATIONPACKAGE_HPP
#define _IP_CONFIGURATIONPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <IP_Configuration_forward.hpp>

#include <System_Specification/System_SpecificationPackage.hpp>

namespace IP_Configuration
{

    /*PROTECTED REGION ID(IP_Configuration_SALT) ENABLED START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 4000
    /*PROTECTED REGION END*/

    class IP_ConfigurationPackage: public virtual ::ecore::EPackage
    {
    public:

        static IP_ConfigurationPackage_ptr _instance();

        // IDs for classifiers

        static const int GENERALIMPLEMENTATIONDESCRIPTION = SALT + 0;

        static const int IMPLEMENTATION = SALT + 1;

        static const int IPCONFIGURATIONS = SALT + 2;

        static const int IPLAYOUT = SALT + 3;

        static const int TTTECHESIP = SALT + 4;

        static const int TTTECHIP = SALT + 5;

        static const int TTTECHIPLAYOUT = SALT + 6;

        static const int TTTECHSWIP = SALT + 7;

        static const int IMPLEMENTATION__DESCRIPTION = SALT + 0;

        static const int IMPLEMENTATION__DETAILS = SALT + 1;

        static const int TTTECHIP__PORTINFO = SALT + 2;

        static const int TTTECHIP__REFIPLAYOUT = SALT + 3;

        static const int TTTECHIP__METAINFORMATION = SALT + 4;

        static const int TTTECHIP__NUMDIAGNOSISSCHEDULEENTRIES = SALT + 5;

        static const int TTTECHIP__VLIDBITS = SALT + 6;

        static const int TTTECHIP__NUMSCHEDULEENTRIES = SALT + 7;

        static const int TTTECHIP__NUMPHYSICALPORTS = SALT + 8;

        static const int TTTECHIP__MAXINTEGRATIONCYCLES = SALT + 9;

        static const int TTTECHIP__NUMMACACCEPTANCEENTRIES = SALT + 10;

        static const int TTTECHIP__NUMSUBSCHEDULES = SALT + 11;

        static const int TTTECHIP__LAYER2MEMBYTEGRANULARITY = SALT + 12;

        static const int TTTECHIP__LAYER2MEMBYTESIZE = SALT + 13;

        static const int TTTECHIP__SYNCHRONIZATIONDELAYTICKS = SALT + 14;

        static const int TTTECHSWIP__NUMBAGENTRIES = SALT + 15;

        static const int TTTECHSWIP__NUMDYNAMICCOTSROUTES = SALT + 16;

        static const int TTTECHSWIP__NUMANTIMASQUERADINGENTRIES = SALT + 17;

        static const int TTTECHSWIP__NUMSTATICCOTSROUTES = SALT + 18;

        static const int TTTECHSWIP__SYNCHRONIZATIONDELAYTICKSCM = SALT + 19;

        static const int TTTECHESIP__NUMSHAREDBUFFERS = SALT + 20;

        static const int TTTECHESIP__NUMDEDICATEDBUFFERS = SALT + 21;

        static const int TTTECHESIP__BUFFERMEMORYSIZE = SALT + 22;

        static const int TTTECHESIP__NUMQUEUEDCTIDBUFFER = SALT + 23;

        static const int TTTECHESIP__HOSTMEMBYTEGRANULARITY = SALT + 24;

        static const int TTTECHESIP__HOSTMEMBYTESIZE = SALT + 25;

        static const int TTTECHESIP__MAXSTATEENTRIES = SALT + 26;

        static const int TTTECHESIP__MAXQUEUEENTRIES = SALT + 27;

        static const int IPLAYOUT__DESCRIPTION = SALT + 28;

        static const int IPLAYOUT__VERSION = SALT + 29;

        static const int IPLAYOUT__METAINFORMATION = SALT + 30;

        static const int IPLAYOUT__ID = SALT + 31;

        static const int TTTECHIPLAYOUT__PINNING = SALT + 32;

        static const int IPCONFIGURATIONS__IMPLEMENTATION = SALT + 33;

        static const int IPCONFIGURATIONS__IPLAYOUT = SALT + 34;

        static const int IPCONFIGURATIONS__METAINFORMATION = SALT + 35;

        static const int GENERALIMPLEMENTATIONDESCRIPTION__SOURCE = SALT + 36;

        // IDs for classifiers for class GeneralImplementationDescription 

        static const int
                GENERALIMPLEMENTATIONDESCRIPTION__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                GENERALIMPLEMENTATIONDESCRIPTION__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                GENERALIMPLEMENTATIONDESCRIPTION__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int GENERALIMPLEMENTATIONDESCRIPTION__DESCRIPTION =
                IMPLEMENTATION__DESCRIPTION;

        static const int GENERALIMPLEMENTATIONDESCRIPTION__DETAILS =
                IMPLEMENTATION__DETAILS;

        // IDs for classifiers for class Implementation 

        static const int
                IMPLEMENTATION__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                IMPLEMENTATION__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                IMPLEMENTATION__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class IpConfigurations 

        static const int
                IPCONFIGURATIONS__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                IPCONFIGURATIONS__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class IpLayout 

        static const int
                IPLAYOUT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                IPLAYOUT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                IPLAYOUT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        // IDs for classifiers for class TTTechEsIp 

        static const int
                TTTECHESIP__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTTECHESIP__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TTTECHESIP__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int TTTECHESIP__DESCRIPTION = IMPLEMENTATION__DESCRIPTION;

        static const int TTTECHESIP__DETAILS = IMPLEMENTATION__DETAILS;

        static const int TTTECHESIP__PORTINFO = TTTECHIP__PORTINFO;

        static const int TTTECHESIP__REFIPLAYOUT = TTTECHIP__REFIPLAYOUT;

        static const int TTTECHESIP__METAINFORMATION =
                TTTECHIP__METAINFORMATION;

        static const int TTTECHESIP__NUMDIAGNOSISSCHEDULEENTRIES =
                TTTECHIP__NUMDIAGNOSISSCHEDULEENTRIES;

        static const int TTTECHESIP__VLIDBITS = TTTECHIP__VLIDBITS;

        static const int TTTECHESIP__NUMSCHEDULEENTRIES =
                TTTECHIP__NUMSCHEDULEENTRIES;

        static const int TTTECHESIP__NUMPHYSICALPORTS =
                TTTECHIP__NUMPHYSICALPORTS;

        static const int TTTECHESIP__MAXINTEGRATIONCYCLES =
                TTTECHIP__MAXINTEGRATIONCYCLES;

        static const int TTTECHESIP__NUMMACACCEPTANCEENTRIES =
                TTTECHIP__NUMMACACCEPTANCEENTRIES;

        static const int TTTECHESIP__NUMSUBSCHEDULES =
                TTTECHIP__NUMSUBSCHEDULES;

        static const int TTTECHESIP__LAYER2MEMBYTEGRANULARITY =
                TTTECHIP__LAYER2MEMBYTEGRANULARITY;

        static const int TTTECHESIP__LAYER2MEMBYTESIZE =
                TTTECHIP__LAYER2MEMBYTESIZE;

        static const int TTTECHESIP__SYNCHRONIZATIONDELAYTICKS =
                TTTECHIP__SYNCHRONIZATIONDELAYTICKS;

        // IDs for classifiers for class TTTechIp 

        static const int
                TTTECHIP__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTTECHIP__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TTTECHIP__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int TTTECHIP__DESCRIPTION = IMPLEMENTATION__DESCRIPTION;

        static const int TTTECHIP__DETAILS = IMPLEMENTATION__DETAILS;

        // IDs for classifiers for class TTTechIpLayout 

        static const int
                TTTECHIPLAYOUT__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTTECHIPLAYOUT__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TTTECHIPLAYOUT__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int TTTECHIPLAYOUT__DESCRIPTION = IPLAYOUT__DESCRIPTION;

        static const int TTTECHIPLAYOUT__VERSION = IPLAYOUT__VERSION;

        static const int TTTECHIPLAYOUT__METAINFORMATION =
                IPLAYOUT__METAINFORMATION;

        static const int TTTECHIPLAYOUT__ID = IPLAYOUT__ID;

        // IDs for classifiers for class TTTechSwIp 

        static const int
                TTTECHSWIP__EANNOTATIONS =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS;

        static const int
                TTTECHSWIP__SIGNATURE =
                        ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE;

        static const int
                TTTECHSWIP__NAME =
                        ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME;

        static const int TTTECHSWIP__DESCRIPTION = IMPLEMENTATION__DESCRIPTION;

        static const int TTTECHSWIP__DETAILS = IMPLEMENTATION__DETAILS;

        static const int TTTECHSWIP__PORTINFO = TTTECHIP__PORTINFO;

        static const int TTTECHSWIP__REFIPLAYOUT = TTTECHIP__REFIPLAYOUT;

        static const int TTTECHSWIP__METAINFORMATION =
                TTTECHIP__METAINFORMATION;

        static const int TTTECHSWIP__NUMDIAGNOSISSCHEDULEENTRIES =
                TTTECHIP__NUMDIAGNOSISSCHEDULEENTRIES;

        static const int TTTECHSWIP__VLIDBITS = TTTECHIP__VLIDBITS;

        static const int TTTECHSWIP__NUMSCHEDULEENTRIES =
                TTTECHIP__NUMSCHEDULEENTRIES;

        static const int TTTECHSWIP__NUMPHYSICALPORTS =
                TTTECHIP__NUMPHYSICALPORTS;

        static const int TTTECHSWIP__MAXINTEGRATIONCYCLES =
                TTTECHIP__MAXINTEGRATIONCYCLES;

        static const int TTTECHSWIP__NUMMACACCEPTANCEENTRIES =
                TTTECHIP__NUMMACACCEPTANCEENTRIES;

        static const int TTTECHSWIP__NUMSUBSCHEDULES =
                TTTECHIP__NUMSUBSCHEDULES;

        static const int TTTECHSWIP__LAYER2MEMBYTEGRANULARITY =
                TTTECHIP__LAYER2MEMBYTEGRANULARITY;

        static const int TTTECHSWIP__LAYER2MEMBYTESIZE =
                TTTECHIP__LAYER2MEMBYTESIZE;

        static const int TTTECHSWIP__SYNCHRONIZATIONDELAYTICKS =
                TTTECHIP__SYNCHRONIZATIONDELAYTICKS;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getImplementation();

        virtual ::ecore::EClass_ptr getTTTechIp();

        virtual ::ecore::EClass_ptr getTTTechSwIp();

        virtual ::ecore::EClass_ptr getTTTechEsIp();

        virtual ::ecore::EClass_ptr getIpLayout();

        virtual ::ecore::EClass_ptr getTTTechIpLayout();

        virtual ::ecore::EClass_ptr getIpConfigurations();

        virtual ::ecore::EClass_ptr getGeneralImplementationDescription();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EAttribute_ptr getImplementation__description();

        virtual ::ecore::EReference_ptr getImplementation__details();

        virtual ::ecore::EReference_ptr getTTTechIp__portinfo();

        virtual ::ecore::EReference_ptr getTTTechIp__refIpLayout();

        virtual ::ecore::EReference_ptr getTTTechIp__metaInformation();

        virtual ::ecore::EAttribute_ptr
                getTTTechIp__numDiagnosisScheduleEntries();

        virtual ::ecore::EAttribute_ptr getTTTechIp__vlIdBits();

        virtual ::ecore::EAttribute_ptr getTTTechIp__numScheduleEntries();

        virtual ::ecore::EAttribute_ptr getTTTechIp__numPhysicalPorts();

        virtual ::ecore::EAttribute_ptr getTTTechIp__maxIntegrationCycles();

        virtual ::ecore::EAttribute_ptr getTTTechIp__numMacAcceptanceEntries();

        virtual ::ecore::EAttribute_ptr getTTTechIp__numSubSchedules();

        virtual ::ecore::EAttribute_ptr getTTTechIp__layer2MemByteGranularity();

        virtual ::ecore::EAttribute_ptr getTTTechIp__layer2memByteSize();

        virtual ::ecore::EAttribute_ptr
                getTTTechIp__synchronizationDelayTicks();

        virtual ::ecore::EAttribute_ptr getTTTechSwIp__numBagEntries();

        virtual ::ecore::EAttribute_ptr getTTTechSwIp__numDynamicCotsRoutes();

        virtual ::ecore::EAttribute_ptr
                getTTTechSwIp__numAntiMasqueradingEntries();

        virtual ::ecore::EAttribute_ptr getTTTechSwIp__numStaticCotsRoutes();

        virtual ::ecore::EAttribute_ptr
                getTTTechSwIp__synchronizationDelayTicksCM();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__numSharedBuffers();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__numDedicatedBuffers();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__bufferMemorySize();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__numQueuedCtidBuffer();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__hostMemByteGranularity();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__hostMemByteSize();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__maxStateEntries();

        virtual ::ecore::EAttribute_ptr getTTTechEsIp__maxQueueEntries();

        virtual ::ecore::EAttribute_ptr getIpLayout__description();

        virtual ::ecore::EAttribute_ptr getIpLayout__Version();

        virtual ::ecore::EReference_ptr getIpLayout__metaInformation();

        virtual ::ecore::EAttribute_ptr getIpLayout__ID();

        virtual ::ecore::EAttribute_ptr getTTTechIpLayout__pinning();

        virtual ::ecore::EReference_ptr getIpConfigurations__implementation();

        virtual ::ecore::EReference_ptr getIpConfigurations__ipLayout();

        virtual ::ecore::EReference_ptr getIpConfigurations__metaInformation();

        virtual ::ecore::EAttribute_ptr
                getGeneralImplementationDescription__source();

    protected:

        static std::auto_ptr< IP_ConfigurationPackage > s_instance;

        IP_ConfigurationPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_ImplementationEClass;

        ::ecore::EClass_ptr m_TTTechIpEClass;

        ::ecore::EClass_ptr m_TTTechSwIpEClass;

        ::ecore::EClass_ptr m_TTTechEsIpEClass;

        ::ecore::EClass_ptr m_IpLayoutEClass;

        ::ecore::EClass_ptr m_TTTechIpLayoutEClass;

        ::ecore::EClass_ptr m_IpConfigurationsEClass;

        ::ecore::EClass_ptr m_GeneralImplementationDescriptionEClass;

        // EEnuminstances 


        // EDataType instances 


        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EAttribute_ptr m_Implementation__description;

        ::ecore::EReference_ptr m_Implementation__details;

        ::ecore::EReference_ptr m_TTTechIp__portinfo;

        ::ecore::EReference_ptr m_TTTechIp__refIpLayout;

        ::ecore::EReference_ptr m_TTTechIp__metaInformation;

        ::ecore::EAttribute_ptr m_TTTechIp__numDiagnosisScheduleEntries;

        ::ecore::EAttribute_ptr m_TTTechIp__vlIdBits;

        ::ecore::EAttribute_ptr m_TTTechIp__numScheduleEntries;

        ::ecore::EAttribute_ptr m_TTTechIp__numPhysicalPorts;

        ::ecore::EAttribute_ptr m_TTTechIp__maxIntegrationCycles;

        ::ecore::EAttribute_ptr m_TTTechIp__numMacAcceptanceEntries;

        ::ecore::EAttribute_ptr m_TTTechIp__numSubSchedules;

        ::ecore::EAttribute_ptr m_TTTechIp__layer2MemByteGranularity;

        ::ecore::EAttribute_ptr m_TTTechIp__layer2memByteSize;

        ::ecore::EAttribute_ptr m_TTTechIp__synchronizationDelayTicks;

        ::ecore::EAttribute_ptr m_TTTechSwIp__numBagEntries;

        ::ecore::EAttribute_ptr m_TTTechSwIp__numDynamicCotsRoutes;

        ::ecore::EAttribute_ptr m_TTTechSwIp__numAntiMasqueradingEntries;

        ::ecore::EAttribute_ptr m_TTTechSwIp__numStaticCotsRoutes;

        ::ecore::EAttribute_ptr m_TTTechSwIp__synchronizationDelayTicksCM;

        ::ecore::EAttribute_ptr m_TTTechEsIp__numSharedBuffers;

        ::ecore::EAttribute_ptr m_TTTechEsIp__numDedicatedBuffers;

        ::ecore::EAttribute_ptr m_TTTechEsIp__bufferMemorySize;

        ::ecore::EAttribute_ptr m_TTTechEsIp__numQueuedCtidBuffer;

        ::ecore::EAttribute_ptr m_TTTechEsIp__hostMemByteGranularity;

        ::ecore::EAttribute_ptr m_TTTechEsIp__hostMemByteSize;

        ::ecore::EAttribute_ptr m_TTTechEsIp__maxStateEntries;

        ::ecore::EAttribute_ptr m_TTTechEsIp__maxQueueEntries;

        ::ecore::EAttribute_ptr m_IpLayout__description;

        ::ecore::EAttribute_ptr m_IpLayout__Version;

        ::ecore::EReference_ptr m_IpLayout__metaInformation;

        ::ecore::EAttribute_ptr m_IpLayout__ID;

        ::ecore::EAttribute_ptr m_TTTechIpLayout__pinning;

        ::ecore::EReference_ptr m_IpConfigurations__implementation;

        ::ecore::EReference_ptr m_IpConfigurations__ipLayout;

        ::ecore::EReference_ptr m_IpConfigurations__metaInformation;

        ::ecore::EAttribute_ptr m_GeneralImplementationDescription__source;

    };

} // IP_Configuration


#endif // _IP_CONFIGURATIONPACKAGE_HPP
