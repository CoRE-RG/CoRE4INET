// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification_forward.hpp
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

#ifndef _SYSTEM_SPECIFICATION_FORWARD_HPP
#define _SYSTEM_SPECIFICATION_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(System_Specification_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace System_Specification
{

    // EDataType
    /*PROTECTED REGION ID(System_Specification_CapabilitiesEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t CapabilitiesEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_CTMarkerType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t CTMarkerType;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_MacAddressType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t MacAddressType;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_SemanticEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t SemanticEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_SpeedEnum) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t SpeedEnum;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_TimeUnit) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t TimeUnit;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_TimeType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t TimeType;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_UniversalNumberType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef int UniversalNumberType;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_VirtualLinkIDType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t VirtualLinkIDType;
    /*PROTECTED REGION END*/
    /*PROTECTED REGION ID(System_Specification_MediaType) ENABLED START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    typedef ::ecorecpp::mapping::type_traits::string_t MediaType;
    /*PROTECTED REGION END*/

    // EClass

    // ModelElement
    class ModelElement;
    typedef ModelElement* ModelElement_ptr;

    // NamedElement
    class NamedElement;
    typedef NamedElement* NamedElement_ptr;

    // MetaInformation
    class MetaInformation;
    typedef MetaInformation* MetaInformation_ptr;

    // SystemSpecification
    class SystemSpecification;
    typedef SystemSpecification* SystemSpecification_ptr;

    // Units
    class Units;
    typedef Units* Units_ptr;

    // Time
    class Time;
    typedef Time* Time_ptr;

    // SITime
    class SITime;
    typedef SITime* SITime_ptr;

    // RefTime
    class RefTime;
    typedef RefTime* RefTime_ptr;

    // Devices
    class Devices;
    typedef Devices* Devices_ptr;

    // Device
    class Device;
    typedef Device* Device_ptr;

    // Port
    class Port;
    typedef Port* Port_ptr;

    // Links
    class Links;
    typedef Links* Links_ptr;

    // Link
    class Link;
    typedef Link* Link_ptr;

    // VirtualLinks
    class VirtualLinks;
    typedef VirtualLinks* VirtualLinks_ptr;

    // VirtualLink
    class VirtualLink;
    typedef VirtualLink* VirtualLink_ptr;

    // PCFVirtualLink
    class PCFVirtualLink;
    typedef PCFVirtualLink* PCFVirtualLink_ptr;

    // DataVirtualLink
    class DataVirtualLink;
    typedef DataVirtualLink* DataVirtualLink_ptr;

    // RCVirtualLink
    class RCVirtualLink;
    typedef RCVirtualLink* RCVirtualLink_ptr;

    // TTVirtualLink
    class TTVirtualLink;
    typedef TTVirtualLink* TTVirtualLink_ptr;

    // FrameRoute
    class FrameRoute;
    typedef FrameRoute* FrameRoute_ptr;

    // FrameRouteSegment
    class FrameRouteSegment;
    typedef FrameRouteSegment* FrameRouteSegment_ptr;

    // Periods
    class Periods;
    typedef Periods* Periods_ptr;

    // Period
    class Period;
    typedef Period* Period_ptr;

    // AbsolutePeriod
    class AbsolutePeriod;
    typedef AbsolutePeriod* AbsolutePeriod_ptr;

    // RelativePeriod
    class RelativePeriod;
    typedef RelativePeriod* RelativePeriod_ptr;

    // SubPeriod
    class SubPeriod;
    typedef SubPeriod* SubPeriod_ptr;

    // Alias
    class Alias;
    typedef Alias* Alias_ptr;

    // Package & Factory
    class System_SpecificationFactory;
    typedef System_SpecificationFactory * System_SpecificationFactory_ptr;
    class System_SpecificationPackage;
    typedef System_SpecificationPackage * System_SpecificationPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // System_Specification


#endif // _SYSTEM_SPECIFICATION_FORWARD_HPP
