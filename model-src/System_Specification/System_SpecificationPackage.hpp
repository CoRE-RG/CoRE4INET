// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/System_SpecificationPackage.hpp
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

#ifndef _SYSTEM_SPECIFICATIONPACKAGE_HPP
#define _SYSTEM_SPECIFICATIONPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <System_Specification_forward.hpp>

namespace System_Specification
{

    /*PROTECTED REGION ID(System_Specification_SALT) START*/
    // Please, enable the protected SALT if you changed it.
    // To do this, add the keyword ENABLED before START.
#define SALT 0
    /*PROTECTED REGION END*/

    class System_SpecificationPackage: public virtual ::ecore::EPackage
    {
    public:

        static System_SpecificationPackage_ptr _instance();

        // IDs for classifiers

        static const int ABSOLUTEPERIOD = SALT + 0;

        static const int ALIAS = SALT + 1;

        static const int CAPABILITIESENUM = SALT + 2;

        static const int CTMARKERTYPE = SALT + 3;

        static const int DATAVIRTUALLINK = SALT + 4;

        static const int DEVICE = SALT + 5;

        static const int DEVICES = SALT + 6;

        static const int FRAMEROUTE = SALT + 7;

        static const int FRAMEROUTESEGMENT = SALT + 8;

        static const int LINK = SALT + 9;

        static const int LINKS = SALT + 10;

        static const int MACADDRESSTYPE = SALT + 11;

        static const int MEDIATYPE = SALT + 12;

        static const int METAINFORMATION = SALT + 13;

        static const int MODELELEMENT = SALT + 14;

        static const int NAMEDELEMENT = SALT + 15;

        static const int PCFVIRTUALLINK = SALT + 16;

        static const int PERIOD = SALT + 17;

        static const int PERIODS = SALT + 18;

        static const int PORT = SALT + 19;

        static const int RCVIRTUALLINK = SALT + 20;

        static const int REFTIME = SALT + 21;

        static const int RELATIVEPERIOD = SALT + 22;

        static const int SEMANTICENUM = SALT + 23;

        static const int SITIME = SALT + 24;

        static const int SPEEDENUM = SALT + 25;

        static const int SUBPERIOD = SALT + 26;

        static const int SYSTEMSPECIFICATION = SALT + 27;

        static const int TIME = SALT + 28;

        static const int TIMETYPE = SALT + 29;

        static const int TIMEUNIT = SALT + 30;

        static const int TTVIRTUALLINK = SALT + 31;

        static const int UNITS = SALT + 32;

        static const int UNIVERSALNUMBERTYPE = SALT + 33;

        static const int VIRTUALLINK = SALT + 34;

        static const int VIRTUALLINKIDTYPE = SALT + 35;

        static const int VIRTUALLINKS = SALT + 36;

        static const int MODELELEMENT__EANNOTATIONS = SALT + 0;

        static const int MODELELEMENT__SIGNATURE = SALT + 1;

        static const int NAMEDELEMENT__NAME = SALT + 2;

        static const int METAINFORMATION__AUTHOR = SALT + 3;

        static const int METAINFORMATION__CREATIONDATE = SALT + 4;

        static const int METAINFORMATION__CREATIONTOOL = SALT + 5;

        static const int METAINFORMATION__CREATIONTOOLVERSION = SALT + 6;

        static const int METAINFORMATION__LICENSEE = SALT + 7;

        static const int METAINFORMATION__DESCRIPTION = SALT + 8;

        static const int SYSTEMSPECIFICATION__METAINFORMATION = SALT + 9;

        static const int SYSTEMSPECIFICATION__UNITS = SALT + 10;

        static const int SYSTEMSPECIFICATION__VIRTUALLINKS = SALT + 11;

        static const int SYSTEMSPECIFICATION__DEVICES = SALT + 12;

        static const int SYSTEMSPECIFICATION__LINKS = SALT + 13;

        static const int SYSTEMSPECIFICATION__PERIODS = SALT + 14;

        static const int UNITS__TIME = SALT + 15;

        static const int REFTIME__REFTYPE = SALT + 16;

        static const int DEVICES__DEVICE = SALT + 17;

        static const int DEVICE__PORT = SALT + 18;

        static const int DEVICE__CAPABILITY = SALT + 19;

        static const int PORT__TRANSMISSIONSPEED = SALT + 20;

        static const int PORT__STATICRXDELAY = SALT + 21;

        static const int PORT__STATICTXDELAY = SALT + 22;

        static const int PORT__MEDIATYPE = SALT + 23;

        static const int PORT__DEVICE = SALT + 24;

        static const int LINKS__LINK = SALT + 25;

        static const int LINK__REFSENDER = SALT + 26;

        static const int LINK__REFRECEIVER = SALT + 27;

        static const int LINK__CABLELENGTH = SALT + 28;

        static const int LINK__MAXSPEED = SALT + 29;

        static const int VIRTUALLINKS__VIRTUALLINK = SALT + 30;

        static const int VIRTUALLINK__DESTMACADDRESSCF = SALT + 31;

        static const int VIRTUALLINK__VLID = SALT + 32;

        static const int VIRTUALLINK__JITTER = SALT + 33;

        static const int VIRTUALLINK__MAXE2ELATENCY = SALT + 34;

        static const int VIRTUALLINK__FRAMEROUTE = SALT + 35;

        static const int VIRTUALLINK__REFSENDER = SALT + 36;

        static const int VIRTUALLINK__REFRECEIVER = SALT + 37;

        static const int VIRTUALLINK__ALIAS = SALT + 38;

        static const int DATAVIRTUALLINK__SEMANTIC = SALT + 39;

        static const int DATAVIRTUALLINK__MAXLENGTH = SALT + 40;

        static const int DATAVIRTUALLINK__REFPERIOD = SALT + 41;

        static const int DATAVIRTUALLINK__TRANSPARENTCLOCKENABLE = SALT + 42;

        static const int TTVIRTUALLINK__RELEASE = SALT + 43;

        static const int TTVIRTUALLINK__DEADLINE = SALT + 44;

        static const int FRAMEROUTE__SEGMENTS = SALT + 45;

        static const int FRAMEROUTESEGMENT__HOP = SALT + 46;

        static const int FRAMEROUTESEGMENT__REFOUTGOINGLINK = SALT + 47;

        static const int PERIODS__PERIOD = SALT + 48;

        static const int PERIOD__PHASE = SALT + 49;

        static const int ABSOLUTEPERIOD__PERIODLENGTH = SALT + 50;

        static const int RELATIVEPERIOD__REFSUPERPERIOD = SALT + 51;

        static const int SUBPERIOD__PERIODICITY = SALT + 52;

        static const int ALIAS__DOMAIN = SALT + 53;

        // IDs for classifiers for class AbsolutePeriod 

        static const int ABSOLUTEPERIOD__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int ABSOLUTEPERIOD__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int ABSOLUTEPERIOD__NAME = NAMEDELEMENT__NAME;

        static const int ABSOLUTEPERIOD__PHASE = PERIOD__PHASE;

        // IDs for classifiers for class Alias 

        static const int ALIAS__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int ALIAS__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int ALIAS__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class DataVirtualLink 

        static const int DATAVIRTUALLINK__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int DATAVIRTUALLINK__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int DATAVIRTUALLINK__DESTMACADDRESSCF =
                VIRTUALLINK__DESTMACADDRESSCF;

        static const int DATAVIRTUALLINK__VLID = VIRTUALLINK__VLID;

        static const int DATAVIRTUALLINK__JITTER = VIRTUALLINK__JITTER;

        static const int DATAVIRTUALLINK__MAXE2ELATENCY =
                VIRTUALLINK__MAXE2ELATENCY;

        static const int DATAVIRTUALLINK__FRAMEROUTE = VIRTUALLINK__FRAMEROUTE;

        static const int DATAVIRTUALLINK__REFSENDER = VIRTUALLINK__REFSENDER;

        static const int DATAVIRTUALLINK__REFRECEIVER =
                VIRTUALLINK__REFRECEIVER;

        static const int DATAVIRTUALLINK__ALIAS = VIRTUALLINK__ALIAS;

        // IDs for classifiers for class Device 

        static const int DEVICE__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int DEVICE__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int DEVICE__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class Devices 

        static const int DEVICES__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int DEVICES__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class FrameRoute 

        static const int FRAMEROUTE__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int FRAMEROUTE__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int FRAMEROUTE__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class FrameRouteSegment 

        static const int FRAMEROUTESEGMENT__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int FRAMEROUTESEGMENT__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int FRAMEROUTESEGMENT__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class Link 

        static const int LINK__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int LINK__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int LINK__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class Links 

        static const int LINKS__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int LINKS__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class MetaInformation 

        static const int METAINFORMATION__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int METAINFORMATION__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class ModelElement 


        // IDs for classifiers for class NamedElement 

        static const int NAMEDELEMENT__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int NAMEDELEMENT__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class PCFVirtualLink 

        static const int PCFVIRTUALLINK__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int PCFVIRTUALLINK__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int PCFVIRTUALLINK__DESTMACADDRESSCF =
                VIRTUALLINK__DESTMACADDRESSCF;

        static const int PCFVIRTUALLINK__VLID = VIRTUALLINK__VLID;

        static const int PCFVIRTUALLINK__JITTER = VIRTUALLINK__JITTER;

        static const int PCFVIRTUALLINK__MAXE2ELATENCY =
                VIRTUALLINK__MAXE2ELATENCY;

        static const int PCFVIRTUALLINK__FRAMEROUTE = VIRTUALLINK__FRAMEROUTE;

        static const int PCFVIRTUALLINK__REFSENDER = VIRTUALLINK__REFSENDER;

        static const int PCFVIRTUALLINK__REFRECEIVER = VIRTUALLINK__REFRECEIVER;

        static const int PCFVIRTUALLINK__ALIAS = VIRTUALLINK__ALIAS;

        // IDs for classifiers for class Period 

        static const int PERIOD__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int PERIOD__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int PERIOD__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class Periods 

        static const int PERIODS__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int PERIODS__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class Port 

        static const int PORT__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int PORT__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int PORT__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class RCVirtualLink 

        static const int RCVIRTUALLINK__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int RCVIRTUALLINK__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int RCVIRTUALLINK__DESTMACADDRESSCF =
                VIRTUALLINK__DESTMACADDRESSCF;

        static const int RCVIRTUALLINK__VLID = VIRTUALLINK__VLID;

        static const int RCVIRTUALLINK__JITTER = VIRTUALLINK__JITTER;

        static const int RCVIRTUALLINK__MAXE2ELATENCY =
                VIRTUALLINK__MAXE2ELATENCY;

        static const int RCVIRTUALLINK__FRAMEROUTE = VIRTUALLINK__FRAMEROUTE;

        static const int RCVIRTUALLINK__REFSENDER = VIRTUALLINK__REFSENDER;

        static const int RCVIRTUALLINK__REFRECEIVER = VIRTUALLINK__REFRECEIVER;

        static const int RCVIRTUALLINK__ALIAS = VIRTUALLINK__ALIAS;

        static const int RCVIRTUALLINK__SEMANTIC = DATAVIRTUALLINK__SEMANTIC;

        static const int RCVIRTUALLINK__MAXLENGTH = DATAVIRTUALLINK__MAXLENGTH;

        static const int RCVIRTUALLINK__REFPERIOD = DATAVIRTUALLINK__REFPERIOD;

        static const int RCVIRTUALLINK__TRANSPARENTCLOCKENABLE =
                DATAVIRTUALLINK__TRANSPARENTCLOCKENABLE;

        // IDs for classifiers for class RefTime 

        static const int REFTIME__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int REFTIME__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class RelativePeriod 

        static const int RELATIVEPERIOD__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int RELATIVEPERIOD__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int RELATIVEPERIOD__NAME = NAMEDELEMENT__NAME;

        static const int RELATIVEPERIOD__PHASE = PERIOD__PHASE;

        // IDs for classifiers for class SITime 

        static const int SITIME__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int SITIME__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class SubPeriod 

        static const int SUBPERIOD__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int SUBPERIOD__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int SUBPERIOD__NAME = NAMEDELEMENT__NAME;

        static const int SUBPERIOD__PHASE = PERIOD__PHASE;

        static const int SUBPERIOD__REFSUPERPERIOD =
                RELATIVEPERIOD__REFSUPERPERIOD;

        // IDs for classifiers for class SystemSpecification 

        static const int SYSTEMSPECIFICATION__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int SYSTEMSPECIFICATION__SIGNATURE =
                MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class Time 

        static const int TIME__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int TIME__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class TTVirtualLink 

        static const int TTVIRTUALLINK__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int TTVIRTUALLINK__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int TTVIRTUALLINK__DESTMACADDRESSCF =
                VIRTUALLINK__DESTMACADDRESSCF;

        static const int TTVIRTUALLINK__VLID = VIRTUALLINK__VLID;

        static const int TTVIRTUALLINK__JITTER = VIRTUALLINK__JITTER;

        static const int TTVIRTUALLINK__MAXE2ELATENCY =
                VIRTUALLINK__MAXE2ELATENCY;

        static const int TTVIRTUALLINK__FRAMEROUTE = VIRTUALLINK__FRAMEROUTE;

        static const int TTVIRTUALLINK__REFSENDER = VIRTUALLINK__REFSENDER;

        static const int TTVIRTUALLINK__REFRECEIVER = VIRTUALLINK__REFRECEIVER;

        static const int TTVIRTUALLINK__ALIAS = VIRTUALLINK__ALIAS;

        static const int TTVIRTUALLINK__SEMANTIC = DATAVIRTUALLINK__SEMANTIC;

        static const int TTVIRTUALLINK__MAXLENGTH = DATAVIRTUALLINK__MAXLENGTH;

        static const int TTVIRTUALLINK__REFPERIOD = DATAVIRTUALLINK__REFPERIOD;

        static const int TTVIRTUALLINK__TRANSPARENTCLOCKENABLE =
                DATAVIRTUALLINK__TRANSPARENTCLOCKENABLE;

        // IDs for classifiers for class Units 

        static const int UNITS__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int UNITS__SIGNATURE = MODELELEMENT__SIGNATURE;

        static const int UNITS__NAME = NAMEDELEMENT__NAME;

        // IDs for classifiers for class VirtualLink 

        static const int VIRTUALLINK__EANNOTATIONS = MODELELEMENT__EANNOTATIONS;

        static const int VIRTUALLINK__SIGNATURE = MODELELEMENT__SIGNATURE;

        // IDs for classifiers for class VirtualLinks 

        static const int VIRTUALLINKS__EANNOTATIONS =
                MODELELEMENT__EANNOTATIONS;

        static const int VIRTUALLINKS__SIGNATURE = MODELELEMENT__SIGNATURE;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getModelElement();

        virtual ::ecore::EClass_ptr getNamedElement();

        virtual ::ecore::EClass_ptr getMetaInformation();

        virtual ::ecore::EClass_ptr getSystemSpecification();

        virtual ::ecore::EClass_ptr getUnits();

        virtual ::ecore::EClass_ptr getTime();

        virtual ::ecore::EClass_ptr getSITime();

        virtual ::ecore::EClass_ptr getRefTime();

        virtual ::ecore::EClass_ptr getDevices();

        virtual ::ecore::EClass_ptr getDevice();

        virtual ::ecore::EClass_ptr getPort();

        virtual ::ecore::EClass_ptr getLinks();

        virtual ::ecore::EClass_ptr getLink();

        virtual ::ecore::EClass_ptr getVirtualLinks();

        virtual ::ecore::EClass_ptr getVirtualLink();

        virtual ::ecore::EClass_ptr getPCFVirtualLink();

        virtual ::ecore::EClass_ptr getDataVirtualLink();

        virtual ::ecore::EClass_ptr getRCVirtualLink();

        virtual ::ecore::EClass_ptr getTTVirtualLink();

        virtual ::ecore::EClass_ptr getFrameRoute();

        virtual ::ecore::EClass_ptr getFrameRouteSegment();

        virtual ::ecore::EClass_ptr getPeriods();

        virtual ::ecore::EClass_ptr getPeriod();

        virtual ::ecore::EClass_ptr getAbsolutePeriod();

        virtual ::ecore::EClass_ptr getRelativePeriod();

        virtual ::ecore::EClass_ptr getSubPeriod();

        virtual ::ecore::EClass_ptr getAlias();

        virtual ::ecore::EEnum_ptr getCapabilitiesEnum();

        virtual ::ecore::EDataType_ptr getCTMarkerType();

        virtual ::ecore::EDataType_ptr getMacAddressType();

        virtual ::ecore::EEnum_ptr getSemanticEnum();

        virtual ::ecore::EEnum_ptr getSpeedEnum();

        virtual ::ecore::EEnum_ptr getTimeUnit();

        virtual ::ecore::EDataType_ptr getTimeType();

        virtual ::ecore::EDataType_ptr getUniversalNumberType();

        virtual ::ecore::EDataType_ptr getVirtualLinkIDType();

        virtual ::ecore::EEnum_ptr getMediaType();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getModelElement__signature();

        virtual ::ecore::EAttribute_ptr getNamedElement__name();

        virtual ::ecore::EAttribute_ptr getMetaInformation__author();

        virtual ::ecore::EAttribute_ptr getMetaInformation__creationDate();

        virtual ::ecore::EAttribute_ptr getMetaInformation__creationTool();

        virtual ::ecore::EAttribute_ptr
                getMetaInformation__creationToolVersion();

        virtual ::ecore::EAttribute_ptr getMetaInformation__licensee();

        virtual ::ecore::EAttribute_ptr getMetaInformation__description();

        virtual ::ecore::EReference_ptr
                getSystemSpecification__metaInformation();

        virtual ::ecore::EReference_ptr getSystemSpecification__units();

        virtual ::ecore::EReference_ptr getSystemSpecification__virtualLinks();

        virtual ::ecore::EReference_ptr getSystemSpecification__devices();

        virtual ::ecore::EReference_ptr getSystemSpecification__links();

        virtual ::ecore::EReference_ptr getSystemSpecification__periods();

        virtual ::ecore::EReference_ptr getUnits__time();

        virtual ::ecore::EReference_ptr getRefTime__refType();

        virtual ::ecore::EReference_ptr getDevices__device();

        virtual ::ecore::EReference_ptr getDevice__port();

        virtual ::ecore::EAttribute_ptr getDevice__capability();

        virtual ::ecore::EAttribute_ptr getPort__transmissionSpeed();

        virtual ::ecore::EAttribute_ptr getPort__staticRxDelay();

        virtual ::ecore::EAttribute_ptr getPort__staticTxDelay();

        virtual ::ecore::EAttribute_ptr getPort__mediaType();

        virtual ::ecore::EReference_ptr getPort__device();

        virtual ::ecore::EReference_ptr getLinks__link();

        virtual ::ecore::EReference_ptr getLink__refSender();

        virtual ::ecore::EReference_ptr getLink__refReceiver();

        virtual ::ecore::EAttribute_ptr getLink__cableLength();

        virtual ::ecore::EAttribute_ptr getLink__maxSpeed();

        virtual ::ecore::EReference_ptr getVirtualLinks__virtualLink();

        virtual ::ecore::EAttribute_ptr getVirtualLink__destMacAddressCF();

        virtual ::ecore::EAttribute_ptr getVirtualLink__vlid();

        virtual ::ecore::EAttribute_ptr getVirtualLink__jitter();

        virtual ::ecore::EAttribute_ptr getVirtualLink__maxE2eLatency();

        virtual ::ecore::EReference_ptr getVirtualLink__frameRoute();

        virtual ::ecore::EReference_ptr getVirtualLink__refSender();

        virtual ::ecore::EReference_ptr getVirtualLink__refReceiver();

        virtual ::ecore::EReference_ptr getVirtualLink__alias();

        virtual ::ecore::EAttribute_ptr getDataVirtualLink__semantic();

        virtual ::ecore::EAttribute_ptr getDataVirtualLink__maxLength();

        virtual ::ecore::EReference_ptr getDataVirtualLink__refPeriod();

        virtual ::ecore::EAttribute_ptr
                getDataVirtualLink__transparentClockEnable();

        virtual ::ecore::EAttribute_ptr getTTVirtualLink__release();

        virtual ::ecore::EAttribute_ptr getTTVirtualLink__deadline();

        virtual ::ecore::EReference_ptr getFrameRoute__segments();

        virtual ::ecore::EAttribute_ptr getFrameRouteSegment__hop();

        virtual ::ecore::EReference_ptr getFrameRouteSegment__refOutgoingLink();

        virtual ::ecore::EReference_ptr getPeriods__period();

        virtual ::ecore::EAttribute_ptr getPeriod__phase();

        virtual ::ecore::EAttribute_ptr getAbsolutePeriod__periodLength();

        virtual ::ecore::EReference_ptr getRelativePeriod__refSuperperiod();

        virtual ::ecore::EAttribute_ptr getSubPeriod__periodicity();

        virtual ::ecore::EAttribute_ptr getAlias__domain();

    protected:

        static std::auto_ptr< System_SpecificationPackage > s_instance;

        System_SpecificationPackage();

        // EClass instances 

        ::ecore::EClass_ptr m_ModelElementEClass;

        ::ecore::EClass_ptr m_NamedElementEClass;

        ::ecore::EClass_ptr m_MetaInformationEClass;

        ::ecore::EClass_ptr m_SystemSpecificationEClass;

        ::ecore::EClass_ptr m_UnitsEClass;

        ::ecore::EClass_ptr m_TimeEClass;

        ::ecore::EClass_ptr m_SITimeEClass;

        ::ecore::EClass_ptr m_RefTimeEClass;

        ::ecore::EClass_ptr m_DevicesEClass;

        ::ecore::EClass_ptr m_DeviceEClass;

        ::ecore::EClass_ptr m_PortEClass;

        ::ecore::EClass_ptr m_LinksEClass;

        ::ecore::EClass_ptr m_LinkEClass;

        ::ecore::EClass_ptr m_VirtualLinksEClass;

        ::ecore::EClass_ptr m_VirtualLinkEClass;

        ::ecore::EClass_ptr m_PCFVirtualLinkEClass;

        ::ecore::EClass_ptr m_DataVirtualLinkEClass;

        ::ecore::EClass_ptr m_RCVirtualLinkEClass;

        ::ecore::EClass_ptr m_TTVirtualLinkEClass;

        ::ecore::EClass_ptr m_FrameRouteEClass;

        ::ecore::EClass_ptr m_FrameRouteSegmentEClass;

        ::ecore::EClass_ptr m_PeriodsEClass;

        ::ecore::EClass_ptr m_PeriodEClass;

        ::ecore::EClass_ptr m_AbsolutePeriodEClass;

        ::ecore::EClass_ptr m_RelativePeriodEClass;

        ::ecore::EClass_ptr m_SubPeriodEClass;

        ::ecore::EClass_ptr m_AliasEClass;

        // EEnuminstances 

        ::ecore::EEnum_ptr m_CapabilitiesEnumEEnum;

        ::ecore::EEnum_ptr m_SemanticEnumEEnum;

        ::ecore::EEnum_ptr m_SpeedEnumEEnum;

        ::ecore::EEnum_ptr m_TimeUnitEEnum;

        ::ecore::EEnum_ptr m_MediaTypeEEnum;

        // EDataType instances 

        ::ecore::EDataType_ptr m_CTMarkerTypeEDataType;

        ::ecore::EDataType_ptr m_MacAddressTypeEDataType;

        ::ecore::EDataType_ptr m_TimeTypeEDataType;

        ::ecore::EDataType_ptr m_UniversalNumberTypeEDataType;

        ::ecore::EDataType_ptr m_VirtualLinkIDTypeEDataType;

        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_ModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ModelElement__signature;

        ::ecore::EAttribute_ptr m_NamedElement__name;

        ::ecore::EAttribute_ptr m_MetaInformation__author;

        ::ecore::EAttribute_ptr m_MetaInformation__creationDate;

        ::ecore::EAttribute_ptr m_MetaInformation__creationTool;

        ::ecore::EAttribute_ptr m_MetaInformation__creationToolVersion;

        ::ecore::EAttribute_ptr m_MetaInformation__licensee;

        ::ecore::EAttribute_ptr m_MetaInformation__description;

        ::ecore::EReference_ptr m_SystemSpecification__metaInformation;

        ::ecore::EReference_ptr m_SystemSpecification__units;

        ::ecore::EReference_ptr m_SystemSpecification__virtualLinks;

        ::ecore::EReference_ptr m_SystemSpecification__devices;

        ::ecore::EReference_ptr m_SystemSpecification__links;

        ::ecore::EReference_ptr m_SystemSpecification__periods;

        ::ecore::EReference_ptr m_Units__time;

        ::ecore::EReference_ptr m_RefTime__refType;

        ::ecore::EReference_ptr m_Devices__device;

        ::ecore::EReference_ptr m_Device__port;

        ::ecore::EAttribute_ptr m_Device__capability;

        ::ecore::EAttribute_ptr m_Port__transmissionSpeed;

        ::ecore::EAttribute_ptr m_Port__staticRxDelay;

        ::ecore::EAttribute_ptr m_Port__staticTxDelay;

        ::ecore::EAttribute_ptr m_Port__mediaType;

        ::ecore::EReference_ptr m_Port__device;

        ::ecore::EReference_ptr m_Links__link;

        ::ecore::EReference_ptr m_Link__refSender;

        ::ecore::EReference_ptr m_Link__refReceiver;

        ::ecore::EAttribute_ptr m_Link__cableLength;

        ::ecore::EAttribute_ptr m_Link__maxSpeed;

        ::ecore::EReference_ptr m_VirtualLinks__virtualLink;

        ::ecore::EAttribute_ptr m_VirtualLink__destMacAddressCF;

        ::ecore::EAttribute_ptr m_VirtualLink__vlid;

        ::ecore::EAttribute_ptr m_VirtualLink__jitter;

        ::ecore::EAttribute_ptr m_VirtualLink__maxE2eLatency;

        ::ecore::EReference_ptr m_VirtualLink__frameRoute;

        ::ecore::EReference_ptr m_VirtualLink__refSender;

        ::ecore::EReference_ptr m_VirtualLink__refReceiver;

        ::ecore::EReference_ptr m_VirtualLink__alias;

        ::ecore::EAttribute_ptr m_DataVirtualLink__semantic;

        ::ecore::EAttribute_ptr m_DataVirtualLink__maxLength;

        ::ecore::EReference_ptr m_DataVirtualLink__refPeriod;

        ::ecore::EAttribute_ptr m_DataVirtualLink__transparentClockEnable;

        ::ecore::EAttribute_ptr m_TTVirtualLink__release;

        ::ecore::EAttribute_ptr m_TTVirtualLink__deadline;

        ::ecore::EReference_ptr m_FrameRoute__segments;

        ::ecore::EAttribute_ptr m_FrameRouteSegment__hop;

        ::ecore::EReference_ptr m_FrameRouteSegment__refOutgoingLink;

        ::ecore::EReference_ptr m_Periods__period;

        ::ecore::EAttribute_ptr m_Period__phase;

        ::ecore::EAttribute_ptr m_AbsolutePeriod__periodLength;

        ::ecore::EReference_ptr m_RelativePeriod__refSuperperiod;

        ::ecore::EAttribute_ptr m_SubPeriod__periodicity;

        ::ecore::EAttribute_ptr m_Alias__domain;

    };

} // System_Specification


#endif // _SYSTEM_SPECIFICATIONPACKAGE_HPP
