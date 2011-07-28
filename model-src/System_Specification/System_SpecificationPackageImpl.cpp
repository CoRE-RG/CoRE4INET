// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/System_SpecificationPackageImpl.cpp
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

#include <System_Specification/System_SpecificationPackage.hpp>
#include <System_Specification/System_SpecificationFactory.hpp>
#include <ecore.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EAttribute.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EOperation.hpp>
#include <ecore/EParameter.hpp>
#include <ecore/EEnum.hpp>
#include <ecore/EEnumLiteral.hpp>
#include <ecore/EDataType.hpp>
#include <ecore/EGenericType.hpp>
#include <ecore/ETypeParameter.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EAnnotation.hpp>

using namespace ::System_Specification;

System_SpecificationPackage::System_SpecificationPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = System_SpecificationFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // ModelElement
    m_ModelElementEClass = new ::ecore::EClass();
    m_ModelElementEClass->setClassifierID(MODELELEMENT);
    m_ModelElementEClass->setEPackage(this);
    getEClassifiers().push_back(m_ModelElementEClass);
    m_ModelElement__signature = new ::ecore::EAttribute();
    m_ModelElement__signature->setFeatureID(
            ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE);
    m_ModelElementEClass->getEStructuralFeatures().push_back(
            m_ModelElement__signature);
    m_ModelElement__eAnnotations = new ::ecore::EReference();
    m_ModelElement__eAnnotations->setFeatureID(
            ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS);
    m_ModelElementEClass->getEStructuralFeatures().push_back(
            m_ModelElement__eAnnotations);

    // NamedElement
    m_NamedElementEClass = new ::ecore::EClass();
    m_NamedElementEClass->setClassifierID(NAMEDELEMENT);
    m_NamedElementEClass->setEPackage(this);
    getEClassifiers().push_back(m_NamedElementEClass);
    m_NamedElement__name = new ::ecore::EAttribute();
    m_NamedElement__name->setFeatureID(
            ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME);
    m_NamedElementEClass->getEStructuralFeatures().push_back(
            m_NamedElement__name);

    // MetaInformation
    m_MetaInformationEClass = new ::ecore::EClass();
    m_MetaInformationEClass->setClassifierID(METAINFORMATION);
    m_MetaInformationEClass->setEPackage(this);
    getEClassifiers().push_back(m_MetaInformationEClass);
    m_MetaInformation__author = new ::ecore::EAttribute();
    m_MetaInformation__author->setFeatureID(
            ::System_Specification::System_SpecificationPackage::METAINFORMATION__AUTHOR);
    m_MetaInformationEClass->getEStructuralFeatures().push_back(
            m_MetaInformation__author);
    m_MetaInformation__creationDate = new ::ecore::EAttribute();
    m_MetaInformation__creationDate->setFeatureID(
            ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONDATE);
    m_MetaInformationEClass->getEStructuralFeatures().push_back(
            m_MetaInformation__creationDate);
    m_MetaInformation__creationTool = new ::ecore::EAttribute();
    m_MetaInformation__creationTool->setFeatureID(
            ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOL);
    m_MetaInformationEClass->getEStructuralFeatures().push_back(
            m_MetaInformation__creationTool);
    m_MetaInformation__creationToolVersion = new ::ecore::EAttribute();
    m_MetaInformation__creationToolVersion->setFeatureID(
            ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOLVERSION);
    m_MetaInformationEClass->getEStructuralFeatures().push_back(
            m_MetaInformation__creationToolVersion);
    m_MetaInformation__licensee = new ::ecore::EAttribute();
    m_MetaInformation__licensee->setFeatureID(
            ::System_Specification::System_SpecificationPackage::METAINFORMATION__LICENSEE);
    m_MetaInformationEClass->getEStructuralFeatures().push_back(
            m_MetaInformation__licensee);
    m_MetaInformation__description = new ::ecore::EAttribute();
    m_MetaInformation__description->setFeatureID(
            ::System_Specification::System_SpecificationPackage::METAINFORMATION__DESCRIPTION);
    m_MetaInformationEClass->getEStructuralFeatures().push_back(
            m_MetaInformation__description);

    // SystemSpecification
    m_SystemSpecificationEClass = new ::ecore::EClass();
    m_SystemSpecificationEClass->setClassifierID(SYSTEMSPECIFICATION);
    m_SystemSpecificationEClass->setEPackage(this);
    getEClassifiers().push_back(m_SystemSpecificationEClass);
    m_SystemSpecification__metaInformation = new ::ecore::EReference();
    m_SystemSpecification__metaInformation->setFeatureID(
            ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__METAINFORMATION);
    m_SystemSpecificationEClass->getEStructuralFeatures().push_back(
            m_SystemSpecification__metaInformation);
    m_SystemSpecification__units = new ::ecore::EReference();
    m_SystemSpecification__units->setFeatureID(
            ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__UNITS);
    m_SystemSpecificationEClass->getEStructuralFeatures().push_back(
            m_SystemSpecification__units);
    m_SystemSpecification__virtualLinks = new ::ecore::EReference();
    m_SystemSpecification__virtualLinks->setFeatureID(
            ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__VIRTUALLINKS);
    m_SystemSpecificationEClass->getEStructuralFeatures().push_back(
            m_SystemSpecification__virtualLinks);
    m_SystemSpecification__devices = new ::ecore::EReference();
    m_SystemSpecification__devices->setFeatureID(
            ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__DEVICES);
    m_SystemSpecificationEClass->getEStructuralFeatures().push_back(
            m_SystemSpecification__devices);
    m_SystemSpecification__links = new ::ecore::EReference();
    m_SystemSpecification__links->setFeatureID(
            ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__LINKS);
    m_SystemSpecificationEClass->getEStructuralFeatures().push_back(
            m_SystemSpecification__links);
    m_SystemSpecification__periods = new ::ecore::EReference();
    m_SystemSpecification__periods->setFeatureID(
            ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__PERIODS);
    m_SystemSpecificationEClass->getEStructuralFeatures().push_back(
            m_SystemSpecification__periods);

    // Units
    m_UnitsEClass = new ::ecore::EClass();
    m_UnitsEClass->setClassifierID(UNITS);
    m_UnitsEClass->setEPackage(this);
    getEClassifiers().push_back(m_UnitsEClass);
    m_Units__time = new ::ecore::EReference();
    m_Units__time->setFeatureID(
            ::System_Specification::System_SpecificationPackage::UNITS__TIME);
    m_UnitsEClass->getEStructuralFeatures().push_back(m_Units__time);

    // Time
    m_TimeEClass = new ::ecore::EClass();
    m_TimeEClass->setClassifierID(TIME);
    m_TimeEClass->setEPackage(this);
    getEClassifiers().push_back(m_TimeEClass);

    // SITime
    m_SITimeEClass = new ::ecore::EClass();
    m_SITimeEClass->setClassifierID(SITIME);
    m_SITimeEClass->setEPackage(this);
    getEClassifiers().push_back(m_SITimeEClass);

    // RefTime
    m_RefTimeEClass = new ::ecore::EClass();
    m_RefTimeEClass->setClassifierID(REFTIME);
    m_RefTimeEClass->setEPackage(this);
    getEClassifiers().push_back(m_RefTimeEClass);
    m_RefTime__refType = new ::ecore::EReference();
    m_RefTime__refType->setFeatureID(
            ::System_Specification::System_SpecificationPackage::REFTIME__REFTYPE);
    m_RefTimeEClass->getEStructuralFeatures().push_back(m_RefTime__refType);

    // Devices
    m_DevicesEClass = new ::ecore::EClass();
    m_DevicesEClass->setClassifierID(DEVICES);
    m_DevicesEClass->setEPackage(this);
    getEClassifiers().push_back(m_DevicesEClass);
    m_Devices__device = new ::ecore::EReference();
    m_Devices__device->setFeatureID(
            ::System_Specification::System_SpecificationPackage::DEVICES__DEVICE);
    m_DevicesEClass->getEStructuralFeatures().push_back(m_Devices__device);

    // Device
    m_DeviceEClass = new ::ecore::EClass();
    m_DeviceEClass->setClassifierID(DEVICE);
    m_DeviceEClass->setEPackage(this);
    getEClassifiers().push_back(m_DeviceEClass);
    m_Device__capability = new ::ecore::EAttribute();
    m_Device__capability->setFeatureID(
            ::System_Specification::System_SpecificationPackage::DEVICE__CAPABILITY);
    m_DeviceEClass->getEStructuralFeatures().push_back(m_Device__capability);
    m_Device__port = new ::ecore::EReference();
    m_Device__port->setFeatureID(
            ::System_Specification::System_SpecificationPackage::DEVICE__PORT);
    m_DeviceEClass->getEStructuralFeatures().push_back(m_Device__port);

    // Port
    m_PortEClass = new ::ecore::EClass();
    m_PortEClass->setClassifierID(PORT);
    m_PortEClass->setEPackage(this);
    getEClassifiers().push_back(m_PortEClass);
    m_Port__transmissionSpeed = new ::ecore::EAttribute();
    m_Port__transmissionSpeed->setFeatureID(
            ::System_Specification::System_SpecificationPackage::PORT__TRANSMISSIONSPEED);
    m_PortEClass->getEStructuralFeatures().push_back(m_Port__transmissionSpeed);
    m_Port__staticRxDelay = new ::ecore::EAttribute();
    m_Port__staticRxDelay->setFeatureID(
            ::System_Specification::System_SpecificationPackage::PORT__STATICRXDELAY);
    m_PortEClass->getEStructuralFeatures().push_back(m_Port__staticRxDelay);
    m_Port__staticTxDelay = new ::ecore::EAttribute();
    m_Port__staticTxDelay->setFeatureID(
            ::System_Specification::System_SpecificationPackage::PORT__STATICTXDELAY);
    m_PortEClass->getEStructuralFeatures().push_back(m_Port__staticTxDelay);
    m_Port__mediaType = new ::ecore::EAttribute();
    m_Port__mediaType->setFeatureID(
            ::System_Specification::System_SpecificationPackage::PORT__MEDIATYPE);
    m_PortEClass->getEStructuralFeatures().push_back(m_Port__mediaType);
    m_Port__device = new ::ecore::EReference();
    m_Port__device->setFeatureID(
            ::System_Specification::System_SpecificationPackage::PORT__DEVICE);
    m_PortEClass->getEStructuralFeatures().push_back(m_Port__device);

    // Links
    m_LinksEClass = new ::ecore::EClass();
    m_LinksEClass->setClassifierID(LINKS);
    m_LinksEClass->setEPackage(this);
    getEClassifiers().push_back(m_LinksEClass);
    m_Links__link = new ::ecore::EReference();
    m_Links__link->setFeatureID(
            ::System_Specification::System_SpecificationPackage::LINKS__LINK);
    m_LinksEClass->getEStructuralFeatures().push_back(m_Links__link);

    // Link
    m_LinkEClass = new ::ecore::EClass();
    m_LinkEClass->setClassifierID(LINK);
    m_LinkEClass->setEPackage(this);
    getEClassifiers().push_back(m_LinkEClass);
    m_Link__cableLength = new ::ecore::EAttribute();
    m_Link__cableLength->setFeatureID(
            ::System_Specification::System_SpecificationPackage::LINK__CABLELENGTH);
    m_LinkEClass->getEStructuralFeatures().push_back(m_Link__cableLength);
    m_Link__maxSpeed = new ::ecore::EAttribute();
    m_Link__maxSpeed->setFeatureID(
            ::System_Specification::System_SpecificationPackage::LINK__MAXSPEED);
    m_LinkEClass->getEStructuralFeatures().push_back(m_Link__maxSpeed);
    m_Link__refSender = new ::ecore::EReference();
    m_Link__refSender->setFeatureID(
            ::System_Specification::System_SpecificationPackage::LINK__REFSENDER);
    m_LinkEClass->getEStructuralFeatures().push_back(m_Link__refSender);
    m_Link__refReceiver = new ::ecore::EReference();
    m_Link__refReceiver->setFeatureID(
            ::System_Specification::System_SpecificationPackage::LINK__REFRECEIVER);
    m_LinkEClass->getEStructuralFeatures().push_back(m_Link__refReceiver);

    // VirtualLinks
    m_VirtualLinksEClass = new ::ecore::EClass();
    m_VirtualLinksEClass->setClassifierID(VIRTUALLINKS);
    m_VirtualLinksEClass->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinksEClass);
    m_VirtualLinks__virtualLink = new ::ecore::EReference();
    m_VirtualLinks__virtualLink->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINKS__VIRTUALLINK);
    m_VirtualLinksEClass->getEStructuralFeatures().push_back(
            m_VirtualLinks__virtualLink);

    // VirtualLink
    m_VirtualLinkEClass = new ::ecore::EClass();
    m_VirtualLinkEClass->setClassifierID(VIRTUALLINK);
    m_VirtualLinkEClass->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinkEClass);
    m_VirtualLink__destMacAddressCF = new ::ecore::EAttribute();
    m_VirtualLink__destMacAddressCF->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__DESTMACADDRESSCF);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(
            m_VirtualLink__destMacAddressCF);
    m_VirtualLink__vlid = new ::ecore::EAttribute();
    m_VirtualLink__vlid->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__VLID);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(m_VirtualLink__vlid);
    m_VirtualLink__jitter = new ::ecore::EAttribute();
    m_VirtualLink__jitter->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__JITTER);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(
            m_VirtualLink__jitter);
    m_VirtualLink__maxE2eLatency = new ::ecore::EAttribute();
    m_VirtualLink__maxE2eLatency->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__MAXE2ELATENCY);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(
            m_VirtualLink__maxE2eLatency);
    m_VirtualLink__frameRoute = new ::ecore::EReference();
    m_VirtualLink__frameRoute->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__FRAMEROUTE);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(
            m_VirtualLink__frameRoute);
    m_VirtualLink__refSender = new ::ecore::EReference();
    m_VirtualLink__refSender->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFSENDER);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(
            m_VirtualLink__refSender);
    m_VirtualLink__refReceiver = new ::ecore::EReference();
    m_VirtualLink__refReceiver->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFRECEIVER);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(
            m_VirtualLink__refReceiver);
    m_VirtualLink__alias = new ::ecore::EReference();
    m_VirtualLink__alias->setFeatureID(
            ::System_Specification::System_SpecificationPackage::VIRTUALLINK__ALIAS);
    m_VirtualLinkEClass->getEStructuralFeatures().push_back(
            m_VirtualLink__alias);

    // PCFVirtualLink
    m_PCFVirtualLinkEClass = new ::ecore::EClass();
    m_PCFVirtualLinkEClass->setClassifierID(PCFVIRTUALLINK);
    m_PCFVirtualLinkEClass->setEPackage(this);
    getEClassifiers().push_back(m_PCFVirtualLinkEClass);

    // DataVirtualLink
    m_DataVirtualLinkEClass = new ::ecore::EClass();
    m_DataVirtualLinkEClass->setClassifierID(DATAVIRTUALLINK);
    m_DataVirtualLinkEClass->setEPackage(this);
    getEClassifiers().push_back(m_DataVirtualLinkEClass);
    m_DataVirtualLink__semantic = new ::ecore::EAttribute();
    m_DataVirtualLink__semantic->setFeatureID(
            ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__SEMANTIC);
    m_DataVirtualLinkEClass->getEStructuralFeatures().push_back(
            m_DataVirtualLink__semantic);
    m_DataVirtualLink__maxLength = new ::ecore::EAttribute();
    m_DataVirtualLink__maxLength->setFeatureID(
            ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__MAXLENGTH);
    m_DataVirtualLinkEClass->getEStructuralFeatures().push_back(
            m_DataVirtualLink__maxLength);
    m_DataVirtualLink__transparentClockEnable = new ::ecore::EAttribute();
    m_DataVirtualLink__transparentClockEnable->setFeatureID(
            ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__TRANSPARENTCLOCKENABLE);
    m_DataVirtualLinkEClass->getEStructuralFeatures().push_back(
            m_DataVirtualLink__transparentClockEnable);
    m_DataVirtualLink__refPeriod = new ::ecore::EReference();
    m_DataVirtualLink__refPeriod->setFeatureID(
            ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__REFPERIOD);
    m_DataVirtualLinkEClass->getEStructuralFeatures().push_back(
            m_DataVirtualLink__refPeriod);

    // RCVirtualLink
    m_RCVirtualLinkEClass = new ::ecore::EClass();
    m_RCVirtualLinkEClass->setClassifierID(RCVIRTUALLINK);
    m_RCVirtualLinkEClass->setEPackage(this);
    getEClassifiers().push_back(m_RCVirtualLinkEClass);

    // TTVirtualLink
    m_TTVirtualLinkEClass = new ::ecore::EClass();
    m_TTVirtualLinkEClass->setClassifierID(TTVIRTUALLINK);
    m_TTVirtualLinkEClass->setEPackage(this);
    getEClassifiers().push_back(m_TTVirtualLinkEClass);
    m_TTVirtualLink__release = new ::ecore::EAttribute();
    m_TTVirtualLink__release->setFeatureID(
            ::System_Specification::System_SpecificationPackage::TTVIRTUALLINK__RELEASE);
    m_TTVirtualLinkEClass->getEStructuralFeatures().push_back(
            m_TTVirtualLink__release);
    m_TTVirtualLink__deadline = new ::ecore::EAttribute();
    m_TTVirtualLink__deadline->setFeatureID(
            ::System_Specification::System_SpecificationPackage::TTVIRTUALLINK__DEADLINE);
    m_TTVirtualLinkEClass->getEStructuralFeatures().push_back(
            m_TTVirtualLink__deadline);

    // FrameRoute
    m_FrameRouteEClass = new ::ecore::EClass();
    m_FrameRouteEClass->setClassifierID(FRAMEROUTE);
    m_FrameRouteEClass->setEPackage(this);
    getEClassifiers().push_back(m_FrameRouteEClass);
    m_FrameRoute__segments = new ::ecore::EReference();
    m_FrameRoute__segments->setFeatureID(
            ::System_Specification::System_SpecificationPackage::FRAMEROUTE__SEGMENTS);
    m_FrameRouteEClass->getEStructuralFeatures().push_back(
            m_FrameRoute__segments);

    // FrameRouteSegment
    m_FrameRouteSegmentEClass = new ::ecore::EClass();
    m_FrameRouteSegmentEClass->setClassifierID(FRAMEROUTESEGMENT);
    m_FrameRouteSegmentEClass->setEPackage(this);
    getEClassifiers().push_back(m_FrameRouteSegmentEClass);
    m_FrameRouteSegment__hop = new ::ecore::EAttribute();
    m_FrameRouteSegment__hop->setFeatureID(
            ::System_Specification::System_SpecificationPackage::FRAMEROUTESEGMENT__HOP);
    m_FrameRouteSegmentEClass->getEStructuralFeatures().push_back(
            m_FrameRouteSegment__hop);
    m_FrameRouteSegment__refOutgoingLink = new ::ecore::EReference();
    m_FrameRouteSegment__refOutgoingLink->setFeatureID(
            ::System_Specification::System_SpecificationPackage::FRAMEROUTESEGMENT__REFOUTGOINGLINK);
    m_FrameRouteSegmentEClass->getEStructuralFeatures().push_back(
            m_FrameRouteSegment__refOutgoingLink);

    // Periods
    m_PeriodsEClass = new ::ecore::EClass();
    m_PeriodsEClass->setClassifierID(PERIODS);
    m_PeriodsEClass->setEPackage(this);
    getEClassifiers().push_back(m_PeriodsEClass);
    m_Periods__period = new ::ecore::EReference();
    m_Periods__period->setFeatureID(
            ::System_Specification::System_SpecificationPackage::PERIODS__PERIOD);
    m_PeriodsEClass->getEStructuralFeatures().push_back(m_Periods__period);

    // Period
    m_PeriodEClass = new ::ecore::EClass();
    m_PeriodEClass->setClassifierID(PERIOD);
    m_PeriodEClass->setEPackage(this);
    getEClassifiers().push_back(m_PeriodEClass);
    m_Period__phase = new ::ecore::EAttribute();
    m_Period__phase->setFeatureID(
            ::System_Specification::System_SpecificationPackage::PERIOD__PHASE);
    m_PeriodEClass->getEStructuralFeatures().push_back(m_Period__phase);

    // AbsolutePeriod
    m_AbsolutePeriodEClass = new ::ecore::EClass();
    m_AbsolutePeriodEClass->setClassifierID(ABSOLUTEPERIOD);
    m_AbsolutePeriodEClass->setEPackage(this);
    getEClassifiers().push_back(m_AbsolutePeriodEClass);
    m_AbsolutePeriod__periodLength = new ::ecore::EAttribute();
    m_AbsolutePeriod__periodLength->setFeatureID(
            ::System_Specification::System_SpecificationPackage::ABSOLUTEPERIOD__PERIODLENGTH);
    m_AbsolutePeriodEClass->getEStructuralFeatures().push_back(
            m_AbsolutePeriod__periodLength);

    // RelativePeriod
    m_RelativePeriodEClass = new ::ecore::EClass();
    m_RelativePeriodEClass->setClassifierID(RELATIVEPERIOD);
    m_RelativePeriodEClass->setEPackage(this);
    getEClassifiers().push_back(m_RelativePeriodEClass);
    m_RelativePeriod__refSuperperiod = new ::ecore::EReference();
    m_RelativePeriod__refSuperperiod->setFeatureID(
            ::System_Specification::System_SpecificationPackage::RELATIVEPERIOD__REFSUPERPERIOD);
    m_RelativePeriodEClass->getEStructuralFeatures().push_back(
            m_RelativePeriod__refSuperperiod);

    // SubPeriod
    m_SubPeriodEClass = new ::ecore::EClass();
    m_SubPeriodEClass->setClassifierID(SUBPERIOD);
    m_SubPeriodEClass->setEPackage(this);
    getEClassifiers().push_back(m_SubPeriodEClass);
    m_SubPeriod__periodicity = new ::ecore::EAttribute();
    m_SubPeriod__periodicity->setFeatureID(
            ::System_Specification::System_SpecificationPackage::SUBPERIOD__PERIODICITY);
    m_SubPeriodEClass->getEStructuralFeatures().push_back(
            m_SubPeriod__periodicity);

    // Alias
    m_AliasEClass = new ::ecore::EClass();
    m_AliasEClass->setClassifierID(ALIAS);
    m_AliasEClass->setEPackage(this);
    getEClassifiers().push_back(m_AliasEClass);
    m_Alias__domain = new ::ecore::EAttribute();
    m_Alias__domain->setFeatureID(
            ::System_Specification::System_SpecificationPackage::ALIAS__DOMAIN);
    m_AliasEClass->getEStructuralFeatures().push_back(m_Alias__domain);

    // Create enums

    m_CapabilitiesEnumEEnum = new ::ecore::EEnum();
    m_CapabilitiesEnumEEnum->setClassifierID(CAPABILITIESENUM);
    m_CapabilitiesEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_CapabilitiesEnumEEnum);

    m_SemanticEnumEEnum = new ::ecore::EEnum();
    m_SemanticEnumEEnum->setClassifierID(SEMANTICENUM);
    m_SemanticEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_SemanticEnumEEnum);

    m_SpeedEnumEEnum = new ::ecore::EEnum();
    m_SpeedEnumEEnum->setClassifierID(SPEEDENUM);
    m_SpeedEnumEEnum->setEPackage(this);
    getEClassifiers().push_back(m_SpeedEnumEEnum);

    m_TimeUnitEEnum = new ::ecore::EEnum();
    m_TimeUnitEEnum->setClassifierID(TIMEUNIT);
    m_TimeUnitEEnum->setEPackage(this);
    getEClassifiers().push_back(m_TimeUnitEEnum);

    m_MediaTypeEEnum = new ::ecore::EEnum();
    m_MediaTypeEEnum->setClassifierID(MEDIATYPE);
    m_MediaTypeEEnum->setEPackage(this);
    getEClassifiers().push_back(m_MediaTypeEEnum);

    // Create data types

    m_CTMarkerTypeEDataType = new ::ecore::EDataType();
    m_CTMarkerTypeEDataType->setClassifierID(CTMARKERTYPE);
    m_CTMarkerTypeEDataType->setEPackage(this);
    getEClassifiers().push_back(m_CTMarkerTypeEDataType);

    m_MacAddressTypeEDataType = new ::ecore::EDataType();
    m_MacAddressTypeEDataType->setClassifierID(MACADDRESSTYPE);
    m_MacAddressTypeEDataType->setEPackage(this);
    getEClassifiers().push_back(m_MacAddressTypeEDataType);

    m_TimeTypeEDataType = new ::ecore::EDataType();
    m_TimeTypeEDataType->setClassifierID(TIMETYPE);
    m_TimeTypeEDataType->setEPackage(this);
    getEClassifiers().push_back(m_TimeTypeEDataType);

    m_UniversalNumberTypeEDataType = new ::ecore::EDataType();
    m_UniversalNumberTypeEDataType->setClassifierID(UNIVERSALNUMBERTYPE);
    m_UniversalNumberTypeEDataType->setEPackage(this);
    getEClassifiers().push_back(m_UniversalNumberTypeEDataType);

    m_VirtualLinkIDTypeEDataType = new ::ecore::EDataType();
    m_VirtualLinkIDTypeEDataType->setClassifierID(VIRTUALLINKIDTYPE);
    m_VirtualLinkIDTypeEDataType->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinkIDTypeEDataType);

    // Initialize package
    setName("System_Specification");
    setNsPrefix("sys");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/System_Specification_V0");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_NamedElementEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_MetaInformationEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_SystemSpecificationEClass->getESuperTypes().push_back(
            m_ModelElementEClass);
    m_UnitsEClass->getESuperTypes().push_back(m_NamedElementEClass);
    m_TimeEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_SITimeEClass->getESuperTypes().push_back(m_TimeEClass);
    m_RefTimeEClass->getESuperTypes().push_back(m_TimeEClass);
    m_DevicesEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_DeviceEClass->getESuperTypes().push_back(m_NamedElementEClass);
    m_PortEClass->getESuperTypes().push_back(m_NamedElementEClass);
    m_LinksEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_LinkEClass->getESuperTypes().push_back(m_NamedElementEClass);
    m_VirtualLinksEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_VirtualLinkEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_PCFVirtualLinkEClass->getESuperTypes().push_back(m_VirtualLinkEClass);
    m_DataVirtualLinkEClass->getESuperTypes().push_back(m_VirtualLinkEClass);
    m_RCVirtualLinkEClass->getESuperTypes().push_back(m_DataVirtualLinkEClass);
    m_TTVirtualLinkEClass->getESuperTypes().push_back(m_DataVirtualLinkEClass);
    m_FrameRouteEClass->getESuperTypes().push_back(m_NamedElementEClass);
    m_FrameRouteSegmentEClass->getESuperTypes().push_back(m_NamedElementEClass);
    m_PeriodsEClass->getESuperTypes().push_back(m_ModelElementEClass);
    m_PeriodEClass->getESuperTypes().push_back(m_NamedElementEClass);
    m_AbsolutePeriodEClass->getESuperTypes().push_back(m_PeriodEClass);
    m_RelativePeriodEClass->getESuperTypes().push_back(m_PeriodEClass);
    m_SubPeriodEClass->getESuperTypes().push_back(m_RelativePeriodEClass);
    m_AliasEClass->getESuperTypes().push_back(m_NamedElementEClass);

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // ModelElement
    m_ModelElementEClass->setName("ModelElement");
    m_ModelElementEClass->setAbstract(false);
    m_ModelElementEClass->setInterface(false);
    m_ModelElement__signature->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_ModelElement__signature->setName("signature");
    m_ModelElement__signature->setDefaultValueLiteral("");
    m_ModelElement__signature->setLowerBound(0);
    m_ModelElement__signature->setUpperBound(1);
    m_ModelElement__signature->setTransient(false);
    m_ModelElement__signature->setVolatile(false);
    m_ModelElement__signature->setChangeable(true);
    m_ModelElement__signature->setUnsettable(false);
    m_ModelElement__signature->setID(false);
    m_ModelElement__signature->setUnique(true);
    m_ModelElement__signature->setDerived(false);
    m_ModelElement__signature->setOrdered(true);
    m_ModelElement__eAnnotations->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEAnnotation_());
    m_ModelElement__eAnnotations->setName("eAnnotations");
    m_ModelElement__eAnnotations->setDefaultValueLiteral("");
    m_ModelElement__eAnnotations->setLowerBound(0);
    m_ModelElement__eAnnotations->setUpperBound(-1);
    m_ModelElement__eAnnotations->setTransient(false);
    m_ModelElement__eAnnotations->setVolatile(false);
    m_ModelElement__eAnnotations->setChangeable(true);
    m_ModelElement__eAnnotations->setContainment(true);
    m_ModelElement__eAnnotations->setResolveProxies(false);
    m_ModelElement__eAnnotations->setUnique(true);
    m_ModelElement__eAnnotations->setDerived(false);
    m_ModelElement__eAnnotations->setOrdered(true);
    // NamedElement
    m_NamedElementEClass->setName("NamedElement");
    m_NamedElementEClass->setAbstract(false);
    m_NamedElementEClass->setInterface(false);
    m_NamedElement__name->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_NamedElement__name->setName("name");
    m_NamedElement__name->setDefaultValueLiteral("");
    m_NamedElement__name->setLowerBound(1);
    m_NamedElement__name->setUpperBound(1);
    m_NamedElement__name->setTransient(false);
    m_NamedElement__name->setVolatile(false);
    m_NamedElement__name->setChangeable(true);
    m_NamedElement__name->setUnsettable(false);
    m_NamedElement__name->setID(false);
    m_NamedElement__name->setUnique(true);
    m_NamedElement__name->setDerived(false);
    m_NamedElement__name->setOrdered(true);
    // MetaInformation
    m_MetaInformationEClass->setName("MetaInformation");
    m_MetaInformationEClass->setAbstract(false);
    m_MetaInformationEClass->setInterface(false);
    m_MetaInformation__author->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_MetaInformation__author->setName("author");
    m_MetaInformation__author->setDefaultValueLiteral("");
    m_MetaInformation__author->setLowerBound(0);
    m_MetaInformation__author->setUpperBound(1);
    m_MetaInformation__author->setTransient(false);
    m_MetaInformation__author->setVolatile(false);
    m_MetaInformation__author->setChangeable(true);
    m_MetaInformation__author->setUnsettable(false);
    m_MetaInformation__author->setID(false);
    m_MetaInformation__author->setUnique(true);
    m_MetaInformation__author->setDerived(false);
    m_MetaInformation__author->setOrdered(true);
    m_MetaInformation__creationDate->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEDate());
    m_MetaInformation__creationDate->setName("creationDate");
    m_MetaInformation__creationDate->setDefaultValueLiteral("");
    m_MetaInformation__creationDate->setLowerBound(0);
    m_MetaInformation__creationDate->setUpperBound(1);
    m_MetaInformation__creationDate->setTransient(false);
    m_MetaInformation__creationDate->setVolatile(false);
    m_MetaInformation__creationDate->setChangeable(true);
    m_MetaInformation__creationDate->setUnsettable(false);
    m_MetaInformation__creationDate->setID(false);
    m_MetaInformation__creationDate->setUnique(true);
    m_MetaInformation__creationDate->setDerived(false);
    m_MetaInformation__creationDate->setOrdered(true);
    m_MetaInformation__creationTool->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_MetaInformation__creationTool->setName("creationTool");
    m_MetaInformation__creationTool->setDefaultValueLiteral("");
    m_MetaInformation__creationTool->setLowerBound(0);
    m_MetaInformation__creationTool->setUpperBound(1);
    m_MetaInformation__creationTool->setTransient(false);
    m_MetaInformation__creationTool->setVolatile(false);
    m_MetaInformation__creationTool->setChangeable(true);
    m_MetaInformation__creationTool->setUnsettable(false);
    m_MetaInformation__creationTool->setID(false);
    m_MetaInformation__creationTool->setUnique(true);
    m_MetaInformation__creationTool->setDerived(false);
    m_MetaInformation__creationTool->setOrdered(true);
    m_MetaInformation__creationToolVersion->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_MetaInformation__creationToolVersion->setName("creationToolVersion");
    m_MetaInformation__creationToolVersion->setDefaultValueLiteral("");
    m_MetaInformation__creationToolVersion->setLowerBound(0);
    m_MetaInformation__creationToolVersion->setUpperBound(1);
    m_MetaInformation__creationToolVersion->setTransient(false);
    m_MetaInformation__creationToolVersion->setVolatile(false);
    m_MetaInformation__creationToolVersion->setChangeable(true);
    m_MetaInformation__creationToolVersion->setUnsettable(false);
    m_MetaInformation__creationToolVersion->setID(false);
    m_MetaInformation__creationToolVersion->setUnique(true);
    m_MetaInformation__creationToolVersion->setDerived(false);
    m_MetaInformation__creationToolVersion->setOrdered(true);
    m_MetaInformation__licensee->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_MetaInformation__licensee->setName("licensee");
    m_MetaInformation__licensee->setDefaultValueLiteral("");
    m_MetaInformation__licensee->setLowerBound(0);
    m_MetaInformation__licensee->setUpperBound(1);
    m_MetaInformation__licensee->setTransient(false);
    m_MetaInformation__licensee->setVolatile(false);
    m_MetaInformation__licensee->setChangeable(true);
    m_MetaInformation__licensee->setUnsettable(false);
    m_MetaInformation__licensee->setID(false);
    m_MetaInformation__licensee->setUnique(true);
    m_MetaInformation__licensee->setDerived(false);
    m_MetaInformation__licensee->setOrdered(true);
    m_MetaInformation__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_MetaInformation__description->setName("description");
    m_MetaInformation__description->setDefaultValueLiteral("");
    m_MetaInformation__description->setLowerBound(0);
    m_MetaInformation__description->setUpperBound(1);
    m_MetaInformation__description->setTransient(false);
    m_MetaInformation__description->setVolatile(false);
    m_MetaInformation__description->setChangeable(true);
    m_MetaInformation__description->setUnsettable(false);
    m_MetaInformation__description->setID(false);
    m_MetaInformation__description->setUnique(true);
    m_MetaInformation__description->setDerived(false);
    m_MetaInformation__description->setOrdered(true);
    // SystemSpecification
    m_SystemSpecificationEClass->setName("SystemSpecification");
    m_SystemSpecificationEClass->setAbstract(false);
    m_SystemSpecificationEClass->setInterface(false);
    m_SystemSpecification__metaInformation->setEType(m_MetaInformationEClass);
    m_SystemSpecification__metaInformation->setName("metaInformation");
    m_SystemSpecification__metaInformation->setDefaultValueLiteral("");
    m_SystemSpecification__metaInformation->setLowerBound(0);
    m_SystemSpecification__metaInformation->setUpperBound(1);
    m_SystemSpecification__metaInformation->setTransient(false);
    m_SystemSpecification__metaInformation->setVolatile(false);
    m_SystemSpecification__metaInformation->setChangeable(true);
    m_SystemSpecification__metaInformation->setContainment(true);
    m_SystemSpecification__metaInformation->setResolveProxies(true);
    m_SystemSpecification__metaInformation->setUnique(true);
    m_SystemSpecification__metaInformation->setDerived(false);
    m_SystemSpecification__metaInformation->setOrdered(true);
    m_SystemSpecification__units->setEType(m_UnitsEClass);
    m_SystemSpecification__units->setName("units");
    m_SystemSpecification__units->setDefaultValueLiteral("");
    m_SystemSpecification__units->setLowerBound(0);
    m_SystemSpecification__units->setUpperBound(1);
    m_SystemSpecification__units->setTransient(false);
    m_SystemSpecification__units->setVolatile(false);
    m_SystemSpecification__units->setChangeable(true);
    m_SystemSpecification__units->setContainment(true);
    m_SystemSpecification__units->setResolveProxies(true);
    m_SystemSpecification__units->setUnique(true);
    m_SystemSpecification__units->setDerived(false);
    m_SystemSpecification__units->setOrdered(true);
    m_SystemSpecification__virtualLinks->setEType(m_VirtualLinksEClass);
    m_SystemSpecification__virtualLinks->setName("virtualLinks");
    m_SystemSpecification__virtualLinks->setDefaultValueLiteral("");
    m_SystemSpecification__virtualLinks->setLowerBound(0);
    m_SystemSpecification__virtualLinks->setUpperBound(1);
    m_SystemSpecification__virtualLinks->setTransient(false);
    m_SystemSpecification__virtualLinks->setVolatile(false);
    m_SystemSpecification__virtualLinks->setChangeable(true);
    m_SystemSpecification__virtualLinks->setContainment(true);
    m_SystemSpecification__virtualLinks->setResolveProxies(true);
    m_SystemSpecification__virtualLinks->setUnique(true);
    m_SystemSpecification__virtualLinks->setDerived(false);
    m_SystemSpecification__virtualLinks->setOrdered(false);
    m_SystemSpecification__devices->setEType(m_DevicesEClass);
    m_SystemSpecification__devices->setName("devices");
    m_SystemSpecification__devices->setDefaultValueLiteral("");
    m_SystemSpecification__devices->setLowerBound(0);
    m_SystemSpecification__devices->setUpperBound(1);
    m_SystemSpecification__devices->setTransient(false);
    m_SystemSpecification__devices->setVolatile(false);
    m_SystemSpecification__devices->setChangeable(true);
    m_SystemSpecification__devices->setContainment(true);
    m_SystemSpecification__devices->setResolveProxies(true);
    m_SystemSpecification__devices->setUnique(true);
    m_SystemSpecification__devices->setDerived(false);
    m_SystemSpecification__devices->setOrdered(true);
    m_SystemSpecification__links->setEType(m_LinksEClass);
    m_SystemSpecification__links->setName("links");
    m_SystemSpecification__links->setDefaultValueLiteral("");
    m_SystemSpecification__links->setLowerBound(0);
    m_SystemSpecification__links->setUpperBound(1);
    m_SystemSpecification__links->setTransient(false);
    m_SystemSpecification__links->setVolatile(false);
    m_SystemSpecification__links->setChangeable(true);
    m_SystemSpecification__links->setContainment(true);
    m_SystemSpecification__links->setResolveProxies(true);
    m_SystemSpecification__links->setUnique(true);
    m_SystemSpecification__links->setDerived(false);
    m_SystemSpecification__links->setOrdered(true);
    m_SystemSpecification__periods->setEType(m_PeriodsEClass);
    m_SystemSpecification__periods->setName("periods");
    m_SystemSpecification__periods->setDefaultValueLiteral("");
    m_SystemSpecification__periods->setLowerBound(0);
    m_SystemSpecification__periods->setUpperBound(1);
    m_SystemSpecification__periods->setTransient(false);
    m_SystemSpecification__periods->setVolatile(false);
    m_SystemSpecification__periods->setChangeable(true);
    m_SystemSpecification__periods->setContainment(true);
    m_SystemSpecification__periods->setResolveProxies(true);
    m_SystemSpecification__periods->setUnique(true);
    m_SystemSpecification__periods->setDerived(false);
    m_SystemSpecification__periods->setOrdered(true);
    // Units
    m_UnitsEClass->setName("Units");
    m_UnitsEClass->setAbstract(false);
    m_UnitsEClass->setInterface(false);
    m_Units__time->setEType(m_TimeEClass);
    m_Units__time->setName("time");
    m_Units__time->setDefaultValueLiteral("");
    m_Units__time->setLowerBound(1);
    m_Units__time->setUpperBound(-1);
    m_Units__time->setTransient(false);
    m_Units__time->setVolatile(false);
    m_Units__time->setChangeable(true);
    m_Units__time->setContainment(true);
    m_Units__time->setResolveProxies(true);
    m_Units__time->setUnique(true);
    m_Units__time->setDerived(false);
    m_Units__time->setOrdered(true);
    // Time
    m_TimeEClass->setName("Time");
    m_TimeEClass->setAbstract(true);
    m_TimeEClass->setInterface(false);
    // SITime
    m_SITimeEClass->setName("SITime");
    m_SITimeEClass->setAbstract(false);
    m_SITimeEClass->setInterface(false);
    // RefTime
    m_RefTimeEClass->setName("RefTime");
    m_RefTimeEClass->setAbstract(false);
    m_RefTimeEClass->setInterface(false);
    m_RefTime__refType->setEType(m_TimeEClass);
    m_RefTime__refType->setName("refType");
    m_RefTime__refType->setDefaultValueLiteral("");
    m_RefTime__refType->setLowerBound(1);
    m_RefTime__refType->setUpperBound(1);
    m_RefTime__refType->setTransient(false);
    m_RefTime__refType->setVolatile(false);
    m_RefTime__refType->setChangeable(true);
    m_RefTime__refType->setContainment(false);
    m_RefTime__refType->setResolveProxies(true);
    m_RefTime__refType->setUnique(true);
    m_RefTime__refType->setDerived(false);
    m_RefTime__refType->setOrdered(false);
    // Devices
    m_DevicesEClass->setName("Devices");
    m_DevicesEClass->setAbstract(false);
    m_DevicesEClass->setInterface(false);
    m_Devices__device->setEType(m_DeviceEClass);
    m_Devices__device->setName("device");
    m_Devices__device->setDefaultValueLiteral("");
    m_Devices__device->setLowerBound(1);
    m_Devices__device->setUpperBound(-1);
    m_Devices__device->setTransient(false);
    m_Devices__device->setVolatile(false);
    m_Devices__device->setChangeable(true);
    m_Devices__device->setContainment(true);
    m_Devices__device->setResolveProxies(true);
    m_Devices__device->setUnique(true);
    m_Devices__device->setDerived(false);
    m_Devices__device->setOrdered(true);
    // Device
    m_DeviceEClass->setName("Device");
    m_DeviceEClass->setAbstract(false);
    m_DeviceEClass->setInterface(false);
    m_Device__capability->setEType(m_CapabilitiesEnumEEnum);
    m_Device__capability->setName("capability");
    m_Device__capability->setDefaultValueLiteral("");
    m_Device__capability->setLowerBound(0);
    m_Device__capability->setUpperBound(-1);
    m_Device__capability->setTransient(false);
    m_Device__capability->setVolatile(false);
    m_Device__capability->setChangeable(true);
    m_Device__capability->setUnsettable(false);
    m_Device__capability->setID(false);
    m_Device__capability->setUnique(true);
    m_Device__capability->setDerived(false);
    m_Device__capability->setOrdered(true);
    m_Device__port->setEType(m_PortEClass);
    m_Device__port->setName("port");
    m_Device__port->setDefaultValueLiteral("");
    m_Device__port->setLowerBound(0);
    m_Device__port->setUpperBound(-1);
    m_Device__port->setTransient(false);
    m_Device__port->setVolatile(false);
    m_Device__port->setChangeable(true);
    m_Device__port->setContainment(true);
    m_Device__port->setResolveProxies(true);
    m_Device__port->setUnique(true);
    m_Device__port->setDerived(false);
    m_Device__port->setOrdered(true);
    m_Device__port->setEOpposite(::ecore::instanceOf< ::ecore::EReference >(
            m_PortEClass->getEStructuralFeatures()[4]));
    // Port
    m_PortEClass->setName("Port");
    m_PortEClass->setAbstract(false);
    m_PortEClass->setInterface(false);
    m_Port__transmissionSpeed->setEType(m_SpeedEnumEEnum);
    m_Port__transmissionSpeed->setName("transmissionSpeed");
    m_Port__transmissionSpeed->setDefaultValueLiteral("1000Mbps");
    m_Port__transmissionSpeed->setLowerBound(0);
    m_Port__transmissionSpeed->setUpperBound(1);
    m_Port__transmissionSpeed->setTransient(false);
    m_Port__transmissionSpeed->setVolatile(false);
    m_Port__transmissionSpeed->setChangeable(true);
    m_Port__transmissionSpeed->setUnsettable(false);
    m_Port__transmissionSpeed->setID(false);
    m_Port__transmissionSpeed->setUnique(true);
    m_Port__transmissionSpeed->setDerived(false);
    m_Port__transmissionSpeed->setOrdered(true);
    m_Port__staticRxDelay->setEType(m_TimeTypeEDataType);
    m_Port__staticRxDelay->setName("staticRxDelay");
    m_Port__staticRxDelay->setDefaultValueLiteral("");
    m_Port__staticRxDelay->setLowerBound(0);
    m_Port__staticRxDelay->setUpperBound(1);
    m_Port__staticRxDelay->setTransient(false);
    m_Port__staticRxDelay->setVolatile(false);
    m_Port__staticRxDelay->setChangeable(true);
    m_Port__staticRxDelay->setUnsettable(false);
    m_Port__staticRxDelay->setID(false);
    m_Port__staticRxDelay->setUnique(true);
    m_Port__staticRxDelay->setDerived(false);
    m_Port__staticRxDelay->setOrdered(true);
    m_Port__staticTxDelay->setEType(m_TimeTypeEDataType);
    m_Port__staticTxDelay->setName("staticTxDelay");
    m_Port__staticTxDelay->setDefaultValueLiteral("");
    m_Port__staticTxDelay->setLowerBound(0);
    m_Port__staticTxDelay->setUpperBound(1);
    m_Port__staticTxDelay->setTransient(false);
    m_Port__staticTxDelay->setVolatile(false);
    m_Port__staticTxDelay->setChangeable(true);
    m_Port__staticTxDelay->setUnsettable(false);
    m_Port__staticTxDelay->setID(false);
    m_Port__staticTxDelay->setUnique(true);
    m_Port__staticTxDelay->setDerived(false);
    m_Port__staticTxDelay->setOrdered(true);
    m_Port__mediaType->setEType(m_MediaTypeEEnum);
    m_Port__mediaType->setName("mediaType");
    m_Port__mediaType->setDefaultValueLiteral("default");
    m_Port__mediaType->setLowerBound(0);
    m_Port__mediaType->setUpperBound(1);
    m_Port__mediaType->setTransient(false);
    m_Port__mediaType->setVolatile(false);
    m_Port__mediaType->setChangeable(true);
    m_Port__mediaType->setUnsettable(false);
    m_Port__mediaType->setID(false);
    m_Port__mediaType->setUnique(true);
    m_Port__mediaType->setDerived(false);
    m_Port__mediaType->setOrdered(true);
    m_Port__device->setEType(m_DeviceEClass);
    m_Port__device->setName("device");
    m_Port__device->setDefaultValueLiteral("");
    m_Port__device->setLowerBound(1);
    m_Port__device->setUpperBound(1);
    m_Port__device->setTransient(true);
    m_Port__device->setVolatile(false);
    m_Port__device->setChangeable(true);
    m_Port__device->setContainment(false);
    m_Port__device->setResolveProxies(true);
    m_Port__device->setUnique(true);
    m_Port__device->setDerived(false);
    m_Port__device->setOrdered(true);
    m_Port__device->setEOpposite(::ecore::instanceOf< ::ecore::EReference >(
            m_DeviceEClass->getEStructuralFeatures()[1]));
    // Links
    m_LinksEClass->setName("Links");
    m_LinksEClass->setAbstract(false);
    m_LinksEClass->setInterface(false);
    m_Links__link->setEType(m_LinkEClass);
    m_Links__link->setName("link");
    m_Links__link->setDefaultValueLiteral("");
    m_Links__link->setLowerBound(1);
    m_Links__link->setUpperBound(-1);
    m_Links__link->setTransient(false);
    m_Links__link->setVolatile(false);
    m_Links__link->setChangeable(true);
    m_Links__link->setContainment(true);
    m_Links__link->setResolveProxies(true);
    m_Links__link->setUnique(true);
    m_Links__link->setDerived(false);
    m_Links__link->setOrdered(true);
    // Link
    m_LinkEClass->setName("Link");
    m_LinkEClass->setAbstract(false);
    m_LinkEClass->setInterface(false);
    m_Link__cableLength->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBigDecimal());
    m_Link__cableLength->setName("cableLength");
    m_Link__cableLength->setDefaultValueLiteral("0");
    m_Link__cableLength->setLowerBound(0);
    m_Link__cableLength->setUpperBound(1);
    m_Link__cableLength->setTransient(false);
    m_Link__cableLength->setVolatile(false);
    m_Link__cableLength->setChangeable(true);
    m_Link__cableLength->setUnsettable(false);
    m_Link__cableLength->setID(false);
    m_Link__cableLength->setUnique(true);
    m_Link__cableLength->setDerived(false);
    m_Link__cableLength->setOrdered(true);
    m_Link__maxSpeed->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBigInteger());
    m_Link__maxSpeed->setName("maxSpeed");
    m_Link__maxSpeed->setDefaultValueLiteral("");
    m_Link__maxSpeed->setLowerBound(0);
    m_Link__maxSpeed->setUpperBound(1);
    m_Link__maxSpeed->setTransient(false);
    m_Link__maxSpeed->setVolatile(false);
    m_Link__maxSpeed->setChangeable(true);
    m_Link__maxSpeed->setUnsettable(false);
    m_Link__maxSpeed->setID(false);
    m_Link__maxSpeed->setUnique(true);
    m_Link__maxSpeed->setDerived(false);
    m_Link__maxSpeed->setOrdered(true);
    m_Link__refSender->setEType(m_PortEClass);
    m_Link__refSender->setName("refSender");
    m_Link__refSender->setDefaultValueLiteral("");
    m_Link__refSender->setLowerBound(1);
    m_Link__refSender->setUpperBound(1);
    m_Link__refSender->setTransient(false);
    m_Link__refSender->setVolatile(false);
    m_Link__refSender->setChangeable(true);
    m_Link__refSender->setContainment(false);
    m_Link__refSender->setResolveProxies(true);
    m_Link__refSender->setUnique(true);
    m_Link__refSender->setDerived(false);
    m_Link__refSender->setOrdered(false);
    m_Link__refReceiver->setEType(m_PortEClass);
    m_Link__refReceiver->setName("refReceiver");
    m_Link__refReceiver->setDefaultValueLiteral("");
    m_Link__refReceiver->setLowerBound(1);
    m_Link__refReceiver->setUpperBound(1);
    m_Link__refReceiver->setTransient(false);
    m_Link__refReceiver->setVolatile(false);
    m_Link__refReceiver->setChangeable(true);
    m_Link__refReceiver->setContainment(false);
    m_Link__refReceiver->setResolveProxies(true);
    m_Link__refReceiver->setUnique(true);
    m_Link__refReceiver->setDerived(false);
    m_Link__refReceiver->setOrdered(false);
    // VirtualLinks
    m_VirtualLinksEClass->setName("VirtualLinks");
    m_VirtualLinksEClass->setAbstract(false);
    m_VirtualLinksEClass->setInterface(false);
    m_VirtualLinks__virtualLink->setEType(m_VirtualLinkEClass);
    m_VirtualLinks__virtualLink->setName("virtualLink");
    m_VirtualLinks__virtualLink->setDefaultValueLiteral("");
    m_VirtualLinks__virtualLink->setLowerBound(1);
    m_VirtualLinks__virtualLink->setUpperBound(-1);
    m_VirtualLinks__virtualLink->setTransient(false);
    m_VirtualLinks__virtualLink->setVolatile(false);
    m_VirtualLinks__virtualLink->setChangeable(true);
    m_VirtualLinks__virtualLink->setContainment(true);
    m_VirtualLinks__virtualLink->setResolveProxies(true);
    m_VirtualLinks__virtualLink->setUnique(true);
    m_VirtualLinks__virtualLink->setDerived(false);
    m_VirtualLinks__virtualLink->setOrdered(true);
    // VirtualLink
    m_VirtualLinkEClass->setName("VirtualLink");
    m_VirtualLinkEClass->setAbstract(true);
    m_VirtualLinkEClass->setInterface(false);
    m_VirtualLink__destMacAddressCF->setEType(m_CTMarkerTypeEDataType);
    m_VirtualLink__destMacAddressCF->setName("destMacAddressCF");
    m_VirtualLink__destMacAddressCF->setDefaultValueLiteral("00:00:00:00");
    m_VirtualLink__destMacAddressCF->setLowerBound(1);
    m_VirtualLink__destMacAddressCF->setUpperBound(1);
    m_VirtualLink__destMacAddressCF->setTransient(false);
    m_VirtualLink__destMacAddressCF->setVolatile(false);
    m_VirtualLink__destMacAddressCF->setChangeable(true);
    m_VirtualLink__destMacAddressCF->setUnsettable(false);
    m_VirtualLink__destMacAddressCF->setID(false);
    m_VirtualLink__destMacAddressCF->setUnique(true);
    m_VirtualLink__destMacAddressCF->setDerived(false);
    m_VirtualLink__destMacAddressCF->setOrdered(true);
    m_VirtualLink__vlid->setEType(m_VirtualLinkIDTypeEDataType);
    m_VirtualLink__vlid->setName("vlid");
    m_VirtualLink__vlid->setDefaultValueLiteral("");
    m_VirtualLink__vlid->setLowerBound(1);
    m_VirtualLink__vlid->setUpperBound(1);
    m_VirtualLink__vlid->setTransient(false);
    m_VirtualLink__vlid->setVolatile(false);
    m_VirtualLink__vlid->setChangeable(true);
    m_VirtualLink__vlid->setUnsettable(false);
    m_VirtualLink__vlid->setID(false);
    m_VirtualLink__vlid->setUnique(true);
    m_VirtualLink__vlid->setDerived(false);
    m_VirtualLink__vlid->setOrdered(true);
    m_VirtualLink__jitter->setEType(m_TimeTypeEDataType);
    m_VirtualLink__jitter->setName("jitter");
    m_VirtualLink__jitter->setDefaultValueLiteral("");
    m_VirtualLink__jitter->setLowerBound(1);
    m_VirtualLink__jitter->setUpperBound(1);
    m_VirtualLink__jitter->setTransient(false);
    m_VirtualLink__jitter->setVolatile(false);
    m_VirtualLink__jitter->setChangeable(true);
    m_VirtualLink__jitter->setUnsettable(false);
    m_VirtualLink__jitter->setID(false);
    m_VirtualLink__jitter->setUnique(true);
    m_VirtualLink__jitter->setDerived(false);
    m_VirtualLink__jitter->setOrdered(true);
    m_VirtualLink__maxE2eLatency->setEType(m_TimeTypeEDataType);
    m_VirtualLink__maxE2eLatency->setName("maxE2eLatency");
    m_VirtualLink__maxE2eLatency->setDefaultValueLiteral("");
    m_VirtualLink__maxE2eLatency->setLowerBound(0);
    m_VirtualLink__maxE2eLatency->setUpperBound(1);
    m_VirtualLink__maxE2eLatency->setTransient(false);
    m_VirtualLink__maxE2eLatency->setVolatile(false);
    m_VirtualLink__maxE2eLatency->setChangeable(true);
    m_VirtualLink__maxE2eLatency->setUnsettable(false);
    m_VirtualLink__maxE2eLatency->setID(false);
    m_VirtualLink__maxE2eLatency->setUnique(true);
    m_VirtualLink__maxE2eLatency->setDerived(false);
    m_VirtualLink__maxE2eLatency->setOrdered(true);
    m_VirtualLink__frameRoute->setEType(m_FrameRouteEClass);
    m_VirtualLink__frameRoute->setName("frameRoute");
    m_VirtualLink__frameRoute->setDefaultValueLiteral("");
    m_VirtualLink__frameRoute->setLowerBound(0);
    m_VirtualLink__frameRoute->setUpperBound(3);
    m_VirtualLink__frameRoute->setTransient(false);
    m_VirtualLink__frameRoute->setVolatile(false);
    m_VirtualLink__frameRoute->setChangeable(true);
    m_VirtualLink__frameRoute->setContainment(true);
    m_VirtualLink__frameRoute->setResolveProxies(true);
    m_VirtualLink__frameRoute->setUnique(true);
    m_VirtualLink__frameRoute->setDerived(false);
    m_VirtualLink__frameRoute->setOrdered(true);
    m_VirtualLink__refSender->setEType(m_DeviceEClass);
    m_VirtualLink__refSender->setName("refSender");
    m_VirtualLink__refSender->setDefaultValueLiteral("");
    m_VirtualLink__refSender->setLowerBound(1);
    m_VirtualLink__refSender->setUpperBound(1);
    m_VirtualLink__refSender->setTransient(false);
    m_VirtualLink__refSender->setVolatile(false);
    m_VirtualLink__refSender->setChangeable(true);
    m_VirtualLink__refSender->setContainment(false);
    m_VirtualLink__refSender->setResolveProxies(true);
    m_VirtualLink__refSender->setUnique(true);
    m_VirtualLink__refSender->setDerived(false);
    m_VirtualLink__refSender->setOrdered(false);
    m_VirtualLink__refReceiver->setEType(m_DeviceEClass);
    m_VirtualLink__refReceiver->setName("refReceiver");
    m_VirtualLink__refReceiver->setDefaultValueLiteral("");
    m_VirtualLink__refReceiver->setLowerBound(1);
    m_VirtualLink__refReceiver->setUpperBound(-1);
    m_VirtualLink__refReceiver->setTransient(false);
    m_VirtualLink__refReceiver->setVolatile(false);
    m_VirtualLink__refReceiver->setChangeable(true);
    m_VirtualLink__refReceiver->setContainment(false);
    m_VirtualLink__refReceiver->setResolveProxies(true);
    m_VirtualLink__refReceiver->setUnique(true);
    m_VirtualLink__refReceiver->setDerived(false);
    m_VirtualLink__refReceiver->setOrdered(false);
    m_VirtualLink__alias->setEType(m_AliasEClass);
    m_VirtualLink__alias->setName("alias");
    m_VirtualLink__alias->setDefaultValueLiteral("");
    m_VirtualLink__alias->setLowerBound(0);
    m_VirtualLink__alias->setUpperBound(-1);
    m_VirtualLink__alias->setTransient(false);
    m_VirtualLink__alias->setVolatile(false);
    m_VirtualLink__alias->setChangeable(true);
    m_VirtualLink__alias->setContainment(true);
    m_VirtualLink__alias->setResolveProxies(true);
    m_VirtualLink__alias->setUnique(true);
    m_VirtualLink__alias->setDerived(false);
    m_VirtualLink__alias->setOrdered(true);
    // PCFVirtualLink
    m_PCFVirtualLinkEClass->setName("PCFVirtualLink");
    m_PCFVirtualLinkEClass->setAbstract(false);
    m_PCFVirtualLinkEClass->setInterface(false);
    // DataVirtualLink
    m_DataVirtualLinkEClass->setName("DataVirtualLink");
    m_DataVirtualLinkEClass->setAbstract(false);
    m_DataVirtualLinkEClass->setInterface(false);
    m_DataVirtualLink__semantic->setEType(m_SemanticEnumEEnum);
    m_DataVirtualLink__semantic->setName("semantic");
    m_DataVirtualLink__semantic->setDefaultValueLiteral("state");
    m_DataVirtualLink__semantic->setLowerBound(0);
    m_DataVirtualLink__semantic->setUpperBound(1);
    m_DataVirtualLink__semantic->setTransient(false);
    m_DataVirtualLink__semantic->setVolatile(false);
    m_DataVirtualLink__semantic->setChangeable(true);
    m_DataVirtualLink__semantic->setUnsettable(false);
    m_DataVirtualLink__semantic->setID(false);
    m_DataVirtualLink__semantic->setUnique(true);
    m_DataVirtualLink__semantic->setDerived(false);
    m_DataVirtualLink__semantic->setOrdered(true);
    m_DataVirtualLink__maxLength->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_DataVirtualLink__maxLength->setName("maxLength");
    m_DataVirtualLink__maxLength->setDefaultValueLiteral("1500");
    m_DataVirtualLink__maxLength->setLowerBound(0);
    m_DataVirtualLink__maxLength->setUpperBound(1);
    m_DataVirtualLink__maxLength->setTransient(false);
    m_DataVirtualLink__maxLength->setVolatile(false);
    m_DataVirtualLink__maxLength->setChangeable(true);
    m_DataVirtualLink__maxLength->setUnsettable(false);
    m_DataVirtualLink__maxLength->setID(false);
    m_DataVirtualLink__maxLength->setUnique(true);
    m_DataVirtualLink__maxLength->setDerived(false);
    m_DataVirtualLink__maxLength->setOrdered(true);
    m_DataVirtualLink__transparentClockEnable->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEBoolean());
    m_DataVirtualLink__transparentClockEnable->setName("transparentClockEnable");
    m_DataVirtualLink__transparentClockEnable->setDefaultValueLiteral("false");
    m_DataVirtualLink__transparentClockEnable->setLowerBound(0);
    m_DataVirtualLink__transparentClockEnable->setUpperBound(1);
    m_DataVirtualLink__transparentClockEnable->setTransient(false);
    m_DataVirtualLink__transparentClockEnable->setVolatile(false);
    m_DataVirtualLink__transparentClockEnable->setChangeable(true);
    m_DataVirtualLink__transparentClockEnable->setUnsettable(false);
    m_DataVirtualLink__transparentClockEnable->setID(false);
    m_DataVirtualLink__transparentClockEnable->setUnique(true);
    m_DataVirtualLink__transparentClockEnable->setDerived(false);
    m_DataVirtualLink__transparentClockEnable->setOrdered(true);
    m_DataVirtualLink__refPeriod->setEType(m_PeriodEClass);
    m_DataVirtualLink__refPeriod->setName("refPeriod");
    m_DataVirtualLink__refPeriod->setDefaultValueLiteral("");
    m_DataVirtualLink__refPeriod->setLowerBound(0);
    m_DataVirtualLink__refPeriod->setUpperBound(1);
    m_DataVirtualLink__refPeriod->setTransient(false);
    m_DataVirtualLink__refPeriod->setVolatile(false);
    m_DataVirtualLink__refPeriod->setChangeable(true);
    m_DataVirtualLink__refPeriod->setContainment(false);
    m_DataVirtualLink__refPeriod->setResolveProxies(true);
    m_DataVirtualLink__refPeriod->setUnique(true);
    m_DataVirtualLink__refPeriod->setDerived(false);
    m_DataVirtualLink__refPeriod->setOrdered(true);
    // RCVirtualLink
    m_RCVirtualLinkEClass->setName("RCVirtualLink");
    m_RCVirtualLinkEClass->setAbstract(false);
    m_RCVirtualLinkEClass->setInterface(false);
    // TTVirtualLink
    m_TTVirtualLinkEClass->setName("TTVirtualLink");
    m_TTVirtualLinkEClass->setAbstract(false);
    m_TTVirtualLinkEClass->setInterface(false);
    m_TTVirtualLink__release->setEType(m_TimeTypeEDataType);
    m_TTVirtualLink__release->setName("release");
    m_TTVirtualLink__release->setDefaultValueLiteral("");
    m_TTVirtualLink__release->setLowerBound(0);
    m_TTVirtualLink__release->setUpperBound(1);
    m_TTVirtualLink__release->setTransient(false);
    m_TTVirtualLink__release->setVolatile(false);
    m_TTVirtualLink__release->setChangeable(true);
    m_TTVirtualLink__release->setUnsettable(false);
    m_TTVirtualLink__release->setID(false);
    m_TTVirtualLink__release->setUnique(true);
    m_TTVirtualLink__release->setDerived(false);
    m_TTVirtualLink__release->setOrdered(true);
    m_TTVirtualLink__deadline->setEType(m_TimeTypeEDataType);
    m_TTVirtualLink__deadline->setName("deadline");
    m_TTVirtualLink__deadline->setDefaultValueLiteral("");
    m_TTVirtualLink__deadline->setLowerBound(0);
    m_TTVirtualLink__deadline->setUpperBound(1);
    m_TTVirtualLink__deadline->setTransient(false);
    m_TTVirtualLink__deadline->setVolatile(false);
    m_TTVirtualLink__deadline->setChangeable(true);
    m_TTVirtualLink__deadline->setUnsettable(false);
    m_TTVirtualLink__deadline->setID(false);
    m_TTVirtualLink__deadline->setUnique(true);
    m_TTVirtualLink__deadline->setDerived(false);
    m_TTVirtualLink__deadline->setOrdered(true);
    // FrameRoute
    m_FrameRouteEClass->setName("FrameRoute");
    m_FrameRouteEClass->setAbstract(false);
    m_FrameRouteEClass->setInterface(false);
    m_FrameRoute__segments->setEType(m_FrameRouteSegmentEClass);
    m_FrameRoute__segments->setName("segments");
    m_FrameRoute__segments->setDefaultValueLiteral("");
    m_FrameRoute__segments->setLowerBound(1);
    m_FrameRoute__segments->setUpperBound(-1);
    m_FrameRoute__segments->setTransient(false);
    m_FrameRoute__segments->setVolatile(false);
    m_FrameRoute__segments->setChangeable(true);
    m_FrameRoute__segments->setContainment(true);
    m_FrameRoute__segments->setResolveProxies(false);
    m_FrameRoute__segments->setUnique(true);
    m_FrameRoute__segments->setDerived(false);
    m_FrameRoute__segments->setOrdered(true);
    // FrameRouteSegment
    m_FrameRouteSegmentEClass->setName("FrameRouteSegment");
    m_FrameRouteSegmentEClass->setAbstract(false);
    m_FrameRouteSegmentEClass->setInterface(false);
    m_FrameRouteSegment__hop->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_FrameRouteSegment__hop->setName("hop");
    m_FrameRouteSegment__hop->setDefaultValueLiteral("");
    m_FrameRouteSegment__hop->setLowerBound(0);
    m_FrameRouteSegment__hop->setUpperBound(1);
    m_FrameRouteSegment__hop->setTransient(false);
    m_FrameRouteSegment__hop->setVolatile(false);
    m_FrameRouteSegment__hop->setChangeable(true);
    m_FrameRouteSegment__hop->setUnsettable(false);
    m_FrameRouteSegment__hop->setID(false);
    m_FrameRouteSegment__hop->setUnique(true);
    m_FrameRouteSegment__hop->setDerived(false);
    m_FrameRouteSegment__hop->setOrdered(true);
    m_FrameRouteSegment__refOutgoingLink->setEType(m_LinkEClass);
    m_FrameRouteSegment__refOutgoingLink->setName("refOutgoingLink");
    m_FrameRouteSegment__refOutgoingLink->setDefaultValueLiteral("");
    m_FrameRouteSegment__refOutgoingLink->setLowerBound(1);
    m_FrameRouteSegment__refOutgoingLink->setUpperBound(-1);
    m_FrameRouteSegment__refOutgoingLink->setTransient(false);
    m_FrameRouteSegment__refOutgoingLink->setVolatile(false);
    m_FrameRouteSegment__refOutgoingLink->setChangeable(true);
    m_FrameRouteSegment__refOutgoingLink->setContainment(false);
    m_FrameRouteSegment__refOutgoingLink->setResolveProxies(true);
    m_FrameRouteSegment__refOutgoingLink->setUnique(true);
    m_FrameRouteSegment__refOutgoingLink->setDerived(false);
    m_FrameRouteSegment__refOutgoingLink->setOrdered(false);
    // Periods
    m_PeriodsEClass->setName("Periods");
    m_PeriodsEClass->setAbstract(false);
    m_PeriodsEClass->setInterface(false);
    m_Periods__period->setEType(m_PeriodEClass);
    m_Periods__period->setName("period");
    m_Periods__period->setDefaultValueLiteral("");
    m_Periods__period->setLowerBound(0);
    m_Periods__period->setUpperBound(-1);
    m_Periods__period->setTransient(false);
    m_Periods__period->setVolatile(false);
    m_Periods__period->setChangeable(true);
    m_Periods__period->setContainment(true);
    m_Periods__period->setResolveProxies(true);
    m_Periods__period->setUnique(true);
    m_Periods__period->setDerived(false);
    m_Periods__period->setOrdered(true);
    // Period
    m_PeriodEClass->setName("Period");
    m_PeriodEClass->setAbstract(true);
    m_PeriodEClass->setInterface(false);
    m_Period__phase->setEType(m_TimeTypeEDataType);
    m_Period__phase->setName("phase");
    m_Period__phase->setDefaultValueLiteral("0ms");
    m_Period__phase->setLowerBound(0);
    m_Period__phase->setUpperBound(1);
    m_Period__phase->setTransient(false);
    m_Period__phase->setVolatile(false);
    m_Period__phase->setChangeable(true);
    m_Period__phase->setUnsettable(false);
    m_Period__phase->setID(false);
    m_Period__phase->setUnique(true);
    m_Period__phase->setDerived(false);
    m_Period__phase->setOrdered(true);
    // AbsolutePeriod
    m_AbsolutePeriodEClass->setName("AbsolutePeriod");
    m_AbsolutePeriodEClass->setAbstract(false);
    m_AbsolutePeriodEClass->setInterface(false);
    m_AbsolutePeriod__periodLength->setEType(m_TimeTypeEDataType);
    m_AbsolutePeriod__periodLength->setName("periodLength");
    m_AbsolutePeriod__periodLength->setDefaultValueLiteral("");
    m_AbsolutePeriod__periodLength->setLowerBound(1);
    m_AbsolutePeriod__periodLength->setUpperBound(1);
    m_AbsolutePeriod__periodLength->setTransient(false);
    m_AbsolutePeriod__periodLength->setVolatile(false);
    m_AbsolutePeriod__periodLength->setChangeable(true);
    m_AbsolutePeriod__periodLength->setUnsettable(false);
    m_AbsolutePeriod__periodLength->setID(false);
    m_AbsolutePeriod__periodLength->setUnique(true);
    m_AbsolutePeriod__periodLength->setDerived(false);
    m_AbsolutePeriod__periodLength->setOrdered(true);
    // RelativePeriod
    m_RelativePeriodEClass->setName("RelativePeriod");
    m_RelativePeriodEClass->setAbstract(true);
    m_RelativePeriodEClass->setInterface(false);
    m_RelativePeriod__refSuperperiod->setEType(m_PeriodEClass);
    m_RelativePeriod__refSuperperiod->setName("refSuperperiod");
    m_RelativePeriod__refSuperperiod->setDefaultValueLiteral("");
    m_RelativePeriod__refSuperperiod->setLowerBound(1);
    m_RelativePeriod__refSuperperiod->setUpperBound(1);
    m_RelativePeriod__refSuperperiod->setTransient(false);
    m_RelativePeriod__refSuperperiod->setVolatile(false);
    m_RelativePeriod__refSuperperiod->setChangeable(true);
    m_RelativePeriod__refSuperperiod->setContainment(false);
    m_RelativePeriod__refSuperperiod->setResolveProxies(true);
    m_RelativePeriod__refSuperperiod->setUnique(true);
    m_RelativePeriod__refSuperperiod->setDerived(false);
    m_RelativePeriod__refSuperperiod->setOrdered(true);
    // SubPeriod
    m_SubPeriodEClass->setName("SubPeriod");
    m_SubPeriodEClass->setAbstract(false);
    m_SubPeriodEClass->setInterface(false);
    m_SubPeriod__periodicity->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_SubPeriod__periodicity->setName("periodicity");
    m_SubPeriod__periodicity->setDefaultValueLiteral("");
    m_SubPeriod__periodicity->setLowerBound(1);
    m_SubPeriod__periodicity->setUpperBound(1);
    m_SubPeriod__periodicity->setTransient(false);
    m_SubPeriod__periodicity->setVolatile(false);
    m_SubPeriod__periodicity->setChangeable(true);
    m_SubPeriod__periodicity->setUnsettable(false);
    m_SubPeriod__periodicity->setID(false);
    m_SubPeriod__periodicity->setUnique(true);
    m_SubPeriod__periodicity->setDerived(false);
    m_SubPeriod__periodicity->setOrdered(true);
    // Alias
    m_AliasEClass->setName("Alias");
    m_AliasEClass->setAbstract(false);
    m_AliasEClass->setInterface(false);
    m_Alias__domain->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Alias__domain->setName("domain");
    m_Alias__domain->setDefaultValueLiteral("");
    m_Alias__domain->setLowerBound(0);
    m_Alias__domain->setUpperBound(1);
    m_Alias__domain->setTransient(false);
    m_Alias__domain->setVolatile(false);
    m_Alias__domain->setChangeable(true);
    m_Alias__domain->setUnsettable(false);
    m_Alias__domain->setID(false);
    m_Alias__domain->setUnique(true);
    m_Alias__domain->setDerived(false);
    m_Alias__domain->setOrdered(true);

    // TODO: Initialize data types

    // CTMarkerType
    m_CTMarkerTypeEDataType->setName("CTMarkerType");
    m_CTMarkerTypeEDataType->setSerializable(true);

    // MacAddressType
    m_MacAddressTypeEDataType->setName("MacAddressType");
    m_MacAddressTypeEDataType->setSerializable(true);

    // TimeType
    m_TimeTypeEDataType->setName("TimeType");
    m_TimeTypeEDataType->setSerializable(true);

    // UniversalNumberType
    m_UniversalNumberTypeEDataType->setName("UniversalNumberType");
    m_UniversalNumberTypeEDataType->setSerializable(true);

    // VirtualLinkIDType
    m_VirtualLinkIDTypeEDataType->setName("VirtualLinkIDType");
    m_VirtualLinkIDTypeEDataType->setSerializable(true);

    // CapabilitiesEnum
    m_CapabilitiesEnumEEnum->setName("CapabilitiesEnum");
    m_CapabilitiesEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // syncClient
        _el->setName("syncClient");
        _el->setValue(0);
        _el->setLiteral("syncClient");
        _el->setEEnum(m_CapabilitiesEnumEEnum);
        m_CapabilitiesEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // syncMaster
        _el->setName("syncMaster");
        _el->setValue(1);
        _el->setLiteral("syncMaster");
        _el->setEEnum(m_CapabilitiesEnumEEnum);
        m_CapabilitiesEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // compressionMaster
        _el->setName("compressionMaster");
        _el->setValue(2);
        _el->setLiteral("compressionMaster");
        _el->setEEnum(m_CapabilitiesEnumEEnum);
        m_CapabilitiesEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // managementModule
        _el->setName("managementModule");
        _el->setValue(3);
        _el->setLiteral("managementModule");
        _el->setEEnum(m_CapabilitiesEnumEEnum);
        m_CapabilitiesEnumEEnum->getELiterals().push_back(_el);
    }

    // SemanticEnum
    m_SemanticEnumEEnum->setName("SemanticEnum");
    m_SemanticEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // state
        _el->setName("state");
        _el->setValue(0);
        _el->setLiteral("state");
        _el->setEEnum(m_SemanticEnumEEnum);
        m_SemanticEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // queue
        _el->setName("queue");
        _el->setValue(1);
        _el->setLiteral("queue");
        _el->setEEnum(m_SemanticEnumEEnum);
        m_SemanticEnumEEnum->getELiterals().push_back(_el);
    }

    // SpeedEnum
    m_SpeedEnumEEnum->setName("SpeedEnum");
    m_SpeedEnumEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // 1000Mbps
        _el->setName("1000Mbps");
        _el->setValue(0);
        _el->setLiteral("1000Mbps");
        _el->setEEnum(m_SpeedEnumEEnum);
        m_SpeedEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // 500Mbps
        _el->setName("500Mbps");
        _el->setValue(1);
        _el->setLiteral("500Mbps");
        _el->setEEnum(m_SpeedEnumEEnum);
        m_SpeedEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // 100Mbps
        _el->setName("100Mbps");
        _el->setValue(2);
        _el->setLiteral("100Mbps");
        _el->setEEnum(m_SpeedEnumEEnum);
        m_SpeedEnumEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // 10Mbps
        _el->setName("10Mbps");
        _el->setValue(3);
        _el->setLiteral("10Mbps");
        _el->setEEnum(m_SpeedEnumEEnum);
        m_SpeedEnumEEnum->getELiterals().push_back(_el);
    }

    // TimeUnit
    m_TimeUnitEEnum->setName("TimeUnit");
    m_TimeUnitEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // ns
        _el->setName("ns");
        _el->setValue(0);
        _el->setLiteral("ns");
        _el->setEEnum(m_TimeUnitEEnum);
        m_TimeUnitEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // ps
        _el->setName("ps");
        _el->setValue(1);
        _el->setLiteral("ps");
        _el->setEEnum(m_TimeUnitEEnum);
        m_TimeUnitEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // ms
        _el->setName("ms");
        _el->setValue(2);
        _el->setLiteral("ms");
        _el->setEEnum(m_TimeUnitEEnum);
        m_TimeUnitEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // us
        _el->setName("us");
        _el->setValue(3);
        _el->setLiteral("us");
        _el->setEEnum(m_TimeUnitEEnum);
        m_TimeUnitEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // s
        _el->setName("s");
        _el->setValue(4);
        _el->setLiteral("s");
        _el->setEEnum(m_TimeUnitEEnum);
        m_TimeUnitEEnum->getELiterals().push_back(_el);
    }

    // MediaType
    m_MediaTypeEEnum->setName("MediaType");
    m_MediaTypeEEnum->setSerializable(true);

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // default
        _el->setName("default");
        _el->setValue(0);
        _el->setLiteral("default");
        _el->setEEnum(m_MediaTypeEEnum);
        m_MediaTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // fiber
        _el->setName("fiber");
        _el->setValue(1);
        _el->setLiteral("fiber");
        _el->setEEnum(m_MediaTypeEEnum);
        m_MediaTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // copper
        _el->setName("copper");
        _el->setValue(2);
        _el->setLiteral("copper");
        _el->setEEnum(m_MediaTypeEEnum);
        m_MediaTypeEEnum->getELiterals().push_back(_el);
    }

    {
        ::ecore::EEnumLiteral_ptr _el = new ::ecore::EEnumLiteral();
        // other
        _el->setName("other");
        _el->setValue(3);
        _el->setLiteral("other");
        _el->setEEnum(m_MediaTypeEEnum);
        m_MediaTypeEEnum->getELiterals().push_back(_el);
    }

    _initialize();
}

::ecore::EClass_ptr System_SpecificationPackage::getModelElement()
{
    return m_ModelElementEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getNamedElement()
{
    return m_NamedElementEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getMetaInformation()
{
    return m_MetaInformationEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getSystemSpecification()
{
    return m_SystemSpecificationEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getUnits()
{
    return m_UnitsEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getTime()
{
    return m_TimeEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getSITime()
{
    return m_SITimeEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getRefTime()
{
    return m_RefTimeEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getDevices()
{
    return m_DevicesEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getDevice()
{
    return m_DeviceEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getPort()
{
    return m_PortEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getLinks()
{
    return m_LinksEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getLink()
{
    return m_LinkEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getVirtualLinks()
{
    return m_VirtualLinksEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getVirtualLink()
{
    return m_VirtualLinkEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getPCFVirtualLink()
{
    return m_PCFVirtualLinkEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getDataVirtualLink()
{
    return m_DataVirtualLinkEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getRCVirtualLink()
{
    return m_RCVirtualLinkEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getTTVirtualLink()
{
    return m_TTVirtualLinkEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getFrameRoute()
{
    return m_FrameRouteEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getFrameRouteSegment()
{
    return m_FrameRouteSegmentEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getPeriods()
{
    return m_PeriodsEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getPeriod()
{
    return m_PeriodEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getAbsolutePeriod()
{
    return m_AbsolutePeriodEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getRelativePeriod()
{
    return m_RelativePeriodEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getSubPeriod()
{
    return m_SubPeriodEClass;
}
::ecore::EClass_ptr System_SpecificationPackage::getAlias()
{
    return m_AliasEClass;
}
::ecore::EEnum_ptr System_SpecificationPackage::getCapabilitiesEnum()
{
    return m_CapabilitiesEnumEEnum;
}
::ecore::EDataType_ptr System_SpecificationPackage::getCTMarkerType()
{
    return m_CTMarkerTypeEDataType;
}
::ecore::EDataType_ptr System_SpecificationPackage::getMacAddressType()
{
    return m_MacAddressTypeEDataType;
}
::ecore::EEnum_ptr System_SpecificationPackage::getSemanticEnum()
{
    return m_SemanticEnumEEnum;
}
::ecore::EEnum_ptr System_SpecificationPackage::getSpeedEnum()
{
    return m_SpeedEnumEEnum;
}
::ecore::EEnum_ptr System_SpecificationPackage::getTimeUnit()
{
    return m_TimeUnitEEnum;
}
::ecore::EDataType_ptr System_SpecificationPackage::getTimeType()
{
    return m_TimeTypeEDataType;
}
::ecore::EDataType_ptr System_SpecificationPackage::getUniversalNumberType()
{
    return m_UniversalNumberTypeEDataType;
}
::ecore::EDataType_ptr System_SpecificationPackage::getVirtualLinkIDType()
{
    return m_VirtualLinkIDTypeEDataType;
}
::ecore::EEnum_ptr System_SpecificationPackage::getMediaType()
{
    return m_MediaTypeEEnum;
}

::ecore::EReference_ptr System_SpecificationPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getMetaInformation__author()
{
    return m_MetaInformation__author;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getMetaInformation__creationDate()
{
    return m_MetaInformation__creationDate;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getMetaInformation__creationTool()
{
    return m_MetaInformation__creationTool;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getMetaInformation__creationToolVersion()
{
    return m_MetaInformation__creationToolVersion;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getMetaInformation__licensee()
{
    return m_MetaInformation__licensee;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getMetaInformation__description()
{
    return m_MetaInformation__description;
}
::ecore::EReference_ptr System_SpecificationPackage::getSystemSpecification__metaInformation()
{
    return m_SystemSpecification__metaInformation;
}
::ecore::EReference_ptr System_SpecificationPackage::getSystemSpecification__units()
{
    return m_SystemSpecification__units;
}
::ecore::EReference_ptr System_SpecificationPackage::getSystemSpecification__virtualLinks()
{
    return m_SystemSpecification__virtualLinks;
}
::ecore::EReference_ptr System_SpecificationPackage::getSystemSpecification__devices()
{
    return m_SystemSpecification__devices;
}
::ecore::EReference_ptr System_SpecificationPackage::getSystemSpecification__links()
{
    return m_SystemSpecification__links;
}
::ecore::EReference_ptr System_SpecificationPackage::getSystemSpecification__periods()
{
    return m_SystemSpecification__periods;
}
::ecore::EReference_ptr System_SpecificationPackage::getUnits__time()
{
    return m_Units__time;
}
::ecore::EReference_ptr System_SpecificationPackage::getRefTime__refType()
{
    return m_RefTime__refType;
}
::ecore::EReference_ptr System_SpecificationPackage::getDevices__device()
{
    return m_Devices__device;
}
::ecore::EReference_ptr System_SpecificationPackage::getDevice__port()
{
    return m_Device__port;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getDevice__capability()
{
    return m_Device__capability;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getPort__transmissionSpeed()
{
    return m_Port__transmissionSpeed;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getPort__staticRxDelay()
{
    return m_Port__staticRxDelay;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getPort__staticTxDelay()
{
    return m_Port__staticTxDelay;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getPort__mediaType()
{
    return m_Port__mediaType;
}
::ecore::EReference_ptr System_SpecificationPackage::getPort__device()
{
    return m_Port__device;
}
::ecore::EReference_ptr System_SpecificationPackage::getLinks__link()
{
    return m_Links__link;
}
::ecore::EReference_ptr System_SpecificationPackage::getLink__refSender()
{
    return m_Link__refSender;
}
::ecore::EReference_ptr System_SpecificationPackage::getLink__refReceiver()
{
    return m_Link__refReceiver;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getLink__cableLength()
{
    return m_Link__cableLength;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getLink__maxSpeed()
{
    return m_Link__maxSpeed;
}
::ecore::EReference_ptr System_SpecificationPackage::getVirtualLinks__virtualLink()
{
    return m_VirtualLinks__virtualLink;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getVirtualLink__destMacAddressCF()
{
    return m_VirtualLink__destMacAddressCF;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getVirtualLink__vlid()
{
    return m_VirtualLink__vlid;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getVirtualLink__jitter()
{
    return m_VirtualLink__jitter;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getVirtualLink__maxE2eLatency()
{
    return m_VirtualLink__maxE2eLatency;
}
::ecore::EReference_ptr System_SpecificationPackage::getVirtualLink__frameRoute()
{
    return m_VirtualLink__frameRoute;
}
::ecore::EReference_ptr System_SpecificationPackage::getVirtualLink__refSender()
{
    return m_VirtualLink__refSender;
}
::ecore::EReference_ptr System_SpecificationPackage::getVirtualLink__refReceiver()
{
    return m_VirtualLink__refReceiver;
}
::ecore::EReference_ptr System_SpecificationPackage::getVirtualLink__alias()
{
    return m_VirtualLink__alias;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getDataVirtualLink__semantic()
{
    return m_DataVirtualLink__semantic;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getDataVirtualLink__maxLength()
{
    return m_DataVirtualLink__maxLength;
}
::ecore::EReference_ptr System_SpecificationPackage::getDataVirtualLink__refPeriod()
{
    return m_DataVirtualLink__refPeriod;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getDataVirtualLink__transparentClockEnable()
{
    return m_DataVirtualLink__transparentClockEnable;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getTTVirtualLink__release()
{
    return m_TTVirtualLink__release;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getTTVirtualLink__deadline()
{
    return m_TTVirtualLink__deadline;
}
::ecore::EReference_ptr System_SpecificationPackage::getFrameRoute__segments()
{
    return m_FrameRoute__segments;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getFrameRouteSegment__hop()
{
    return m_FrameRouteSegment__hop;
}
::ecore::EReference_ptr System_SpecificationPackage::getFrameRouteSegment__refOutgoingLink()
{
    return m_FrameRouteSegment__refOutgoingLink;
}
::ecore::EReference_ptr System_SpecificationPackage::getPeriods__period()
{
    return m_Periods__period;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getPeriod__phase()
{
    return m_Period__phase;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getAbsolutePeriod__periodLength()
{
    return m_AbsolutePeriod__periodLength;
}
::ecore::EReference_ptr System_SpecificationPackage::getRelativePeriod__refSuperperiod()
{
    return m_RelativePeriod__refSuperperiod;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getSubPeriod__periodicity()
{
    return m_SubPeriod__periodicity;
}
::ecore::EAttribute_ptr System_SpecificationPackage::getAlias__domain()
{
    return m_Alias__domain;
}

