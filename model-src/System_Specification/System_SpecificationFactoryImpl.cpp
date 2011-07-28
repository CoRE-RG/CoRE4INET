// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/System_SpecificationFactoryImpl.cpp
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

#include <System_Specification/System_SpecificationFactory.hpp>
#include <System_Specification/System_SpecificationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <System_Specification/NamedElement.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/SystemSpecification.hpp>
#include <System_Specification/Units.hpp>
#include <System_Specification/Time.hpp>
#include <System_Specification/SITime.hpp>
#include <System_Specification/RefTime.hpp>
#include <System_Specification/Devices.hpp>
#include <System_Specification/Device.hpp>
#include <System_Specification/Port.hpp>
#include <System_Specification/Links.hpp>
#include <System_Specification/Link.hpp>
#include <System_Specification/VirtualLinks.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <System_Specification/PCFVirtualLink.hpp>
#include <System_Specification/DataVirtualLink.hpp>
#include <System_Specification/RCVirtualLink.hpp>
#include <System_Specification/TTVirtualLink.hpp>
#include <System_Specification/FrameRoute.hpp>
#include <System_Specification/FrameRouteSegment.hpp>
#include <System_Specification/Periods.hpp>
#include <System_Specification/Period.hpp>
#include <System_Specification/AbsolutePeriod.hpp>
#include <System_Specification/RelativePeriod.hpp>
#include <System_Specification/SubPeriod.hpp>
#include <System_Specification/Alias.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::System_Specification;

System_SpecificationFactory::System_SpecificationFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr System_SpecificationFactory::create(
        ::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case System_SpecificationPackage::MODELELEMENT:
        return createModelElement();
    case System_SpecificationPackage::NAMEDELEMENT:
        return createNamedElement();
    case System_SpecificationPackage::METAINFORMATION:
        return createMetaInformation();
    case System_SpecificationPackage::SYSTEMSPECIFICATION:
        return createSystemSpecification();
    case System_SpecificationPackage::UNITS:
        return createUnits();
    case System_SpecificationPackage::TIME:
        return createTime();
    case System_SpecificationPackage::SITIME:
        return createSITime();
    case System_SpecificationPackage::REFTIME:
        return createRefTime();
    case System_SpecificationPackage::DEVICES:
        return createDevices();
    case System_SpecificationPackage::DEVICE:
        return createDevice();
    case System_SpecificationPackage::PORT:
        return createPort();
    case System_SpecificationPackage::LINKS:
        return createLinks();
    case System_SpecificationPackage::LINK:
        return createLink();
    case System_SpecificationPackage::VIRTUALLINKS:
        return createVirtualLinks();
    case System_SpecificationPackage::VIRTUALLINK:
        return createVirtualLink();
    case System_SpecificationPackage::PCFVIRTUALLINK:
        return createPCFVirtualLink();
    case System_SpecificationPackage::DATAVIRTUALLINK:
        return createDataVirtualLink();
    case System_SpecificationPackage::RCVIRTUALLINK:
        return createRCVirtualLink();
    case System_SpecificationPackage::TTVIRTUALLINK:
        return createTTVirtualLink();
    case System_SpecificationPackage::FRAMEROUTE:
        return createFrameRoute();
    case System_SpecificationPackage::FRAMEROUTESEGMENT:
        return createFrameRouteSegment();
    case System_SpecificationPackage::PERIODS:
        return createPeriods();
    case System_SpecificationPackage::PERIOD:
        return createPeriod();
    case System_SpecificationPackage::ABSOLUTEPERIOD:
        return createAbsolutePeriod();
    case System_SpecificationPackage::RELATIVEPERIOD:
        return createRelativePeriod();
    case System_SpecificationPackage::SUBPERIOD:
        return createSubPeriod();
    case System_SpecificationPackage::ALIAS:
        return createAlias();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject System_SpecificationFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    case System_SpecificationPackage::CAPABILITIESENUM:
    {
        ::ecore::EJavaObject _any;
        System_SpecificationPackage_ptr
                _epkg =
                        dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (getEPackage());
        return _epkg->getCapabilitiesEnum()->getEEnumLiteralByLiteral(
                _literalValue)->getValue();
    }
    case System_SpecificationPackage::CTMARKERTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::CTMarkerType >::fromString(
                _literalValue);
    case System_SpecificationPackage::MACADDRESSTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::MacAddressType >::fromString(
                _literalValue);
    case System_SpecificationPackage::SEMANTICENUM:
    {
        ::ecore::EJavaObject _any;
        System_SpecificationPackage_ptr
                _epkg =
                        dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (getEPackage());
        return _epkg->getSemanticEnum()->getEEnumLiteralByLiteral(_literalValue)->getValue();
    }
    case System_SpecificationPackage::SPEEDENUM:
    {
        ::ecore::EJavaObject _any;
        System_SpecificationPackage_ptr
                _epkg =
                        dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (getEPackage());
        return _epkg->getSpeedEnum()->getEEnumLiteralByLiteral(_literalValue)->getValue();
    }
    case System_SpecificationPackage::TIMEUNIT:
    {
        ::ecore::EJavaObject _any;
        System_SpecificationPackage_ptr
                _epkg =
                        dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (getEPackage());
        return _epkg->getTimeUnit()->getEEnumLiteralByLiteral(_literalValue)->getValue();
    }
    case System_SpecificationPackage::TIMETYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::TimeType >::fromString(_literalValue);
    case System_SpecificationPackage::UNIVERSALNUMBERTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::UniversalNumberType >::fromString(
                _literalValue);
    case System_SpecificationPackage::VIRTUALLINKIDTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::VirtualLinkIDType >::fromString(
                _literalValue);
    case System_SpecificationPackage::MEDIATYPE:
    {
        ::ecore::EJavaObject _any;
        System_SpecificationPackage_ptr
                _epkg =
                        dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (getEPackage());
        return _epkg->getMediaType()->getEEnumLiteralByLiteral(_literalValue)->getValue();
    }
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString System_SpecificationFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    case System_SpecificationPackage::CAPABILITIESENUM:
    {
        System_SpecificationPackage_ptr _epkg =
                ::System_Specification::instanceOf<
                        ::System_Specification::System_SpecificationPackage >(
                        getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getCapabilitiesEnum()->getEEnumLiteral(_value)->getName();
    }
    case System_SpecificationPackage::CTMARKERTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::CTMarkerType >::toString(_instanceValue);
    case System_SpecificationPackage::MACADDRESSTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::MacAddressType >::toString(
                _instanceValue);
    case System_SpecificationPackage::SEMANTICENUM:
    {
        System_SpecificationPackage_ptr _epkg =
                ::System_Specification::instanceOf<
                        ::System_Specification::System_SpecificationPackage >(
                        getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getSemanticEnum()->getEEnumLiteral(_value)->getName();
    }
    case System_SpecificationPackage::SPEEDENUM:
    {
        System_SpecificationPackage_ptr _epkg =
                ::System_Specification::instanceOf<
                        ::System_Specification::System_SpecificationPackage >(
                        getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getSpeedEnum()->getEEnumLiteral(_value)->getName();
    }
    case System_SpecificationPackage::TIMEUNIT:
    {
        System_SpecificationPackage_ptr _epkg =
                ::System_Specification::instanceOf<
                        ::System_Specification::System_SpecificationPackage >(
                        getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getTimeUnit()->getEEnumLiteral(_value)->getName();
    }
    case System_SpecificationPackage::TIMETYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::TimeType >::toString(_instanceValue);
    case System_SpecificationPackage::UNIVERSALNUMBERTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::UniversalNumberType >::toString(
                _instanceValue);
    case System_SpecificationPackage::VIRTUALLINKIDTYPE:
        return ::ecorecpp::mapping::string_traits<
                ::System_Specification::VirtualLinkIDType >::toString(
                _instanceValue);
    case System_SpecificationPackage::MEDIATYPE:
    {
        System_SpecificationPackage_ptr _epkg =
                ::System_Specification::instanceOf<
                        ::System_Specification::System_SpecificationPackage >(
                        getEPackage());
        ::ecore::EInt _value = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EInt >(_instanceValue);
        return _epkg->getMediaType()->getEEnumLiteral(_value)->getName();
    }
    default:
        throw "IllegalArgumentException";
    }
}

ModelElement_ptr System_SpecificationFactory::createModelElement()
{
    return new ModelElement();
}
NamedElement_ptr System_SpecificationFactory::createNamedElement()
{
    return new NamedElement();
}
MetaInformation_ptr System_SpecificationFactory::createMetaInformation()
{
    return new MetaInformation();
}
SystemSpecification_ptr System_SpecificationFactory::createSystemSpecification()
{
    return new SystemSpecification();
}
Units_ptr System_SpecificationFactory::createUnits()
{
    return new Units();
}
Time_ptr System_SpecificationFactory::createTime()
{
    return new Time();
}
SITime_ptr System_SpecificationFactory::createSITime()
{
    return new SITime();
}
RefTime_ptr System_SpecificationFactory::createRefTime()
{
    return new RefTime();
}
Devices_ptr System_SpecificationFactory::createDevices()
{
    return new Devices();
}
Device_ptr System_SpecificationFactory::createDevice()
{
    return new Device();
}
Port_ptr System_SpecificationFactory::createPort()
{
    return new Port();
}
Links_ptr System_SpecificationFactory::createLinks()
{
    return new Links();
}
Link_ptr System_SpecificationFactory::createLink()
{
    return new Link();
}
VirtualLinks_ptr System_SpecificationFactory::createVirtualLinks()
{
    return new VirtualLinks();
}
VirtualLink_ptr System_SpecificationFactory::createVirtualLink()
{
    return new VirtualLink();
}
PCFVirtualLink_ptr System_SpecificationFactory::createPCFVirtualLink()
{
    return new PCFVirtualLink();
}
DataVirtualLink_ptr System_SpecificationFactory::createDataVirtualLink()
{
    return new DataVirtualLink();
}
RCVirtualLink_ptr System_SpecificationFactory::createRCVirtualLink()
{
    return new RCVirtualLink();
}
TTVirtualLink_ptr System_SpecificationFactory::createTTVirtualLink()
{
    return new TTVirtualLink();
}
FrameRoute_ptr System_SpecificationFactory::createFrameRoute()
{
    return new FrameRoute();
}
FrameRouteSegment_ptr System_SpecificationFactory::createFrameRouteSegment()
{
    return new FrameRouteSegment();
}
Periods_ptr System_SpecificationFactory::createPeriods()
{
    return new Periods();
}
Period_ptr System_SpecificationFactory::createPeriod()
{
    return new Period();
}
AbsolutePeriod_ptr System_SpecificationFactory::createAbsolutePeriod()
{
    return new AbsolutePeriod();
}
RelativePeriod_ptr System_SpecificationFactory::createRelativePeriod()
{
    return new RelativePeriod();
}
SubPeriod_ptr System_SpecificationFactory::createSubPeriod()
{
    return new SubPeriod();
}
Alias_ptr System_SpecificationFactory::createAlias()
{
    return new Alias();
}

