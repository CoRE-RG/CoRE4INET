// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/System_SpecificationFactory.hpp
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

#ifndef _SYSTEM_SPECIFICATIONFACTORY_HPP
#define _SYSTEM_SPECIFICATIONFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <System_Specification.hpp>

namespace System_Specification
{

    class System_SpecificationFactory: public virtual ::ecore::EFactory
    {
    public:

        static System_SpecificationFactory_ptr _instance();

        virtual ModelElement_ptr createModelElement();
        virtual NamedElement_ptr createNamedElement();
        virtual MetaInformation_ptr createMetaInformation();
        virtual SystemSpecification_ptr createSystemSpecification();
        virtual Units_ptr createUnits();
        virtual Time_ptr createTime();
        virtual SITime_ptr createSITime();
        virtual RefTime_ptr createRefTime();
        virtual Devices_ptr createDevices();
        virtual Device_ptr createDevice();
        virtual Port_ptr createPort();
        virtual Links_ptr createLinks();
        virtual Link_ptr createLink();
        virtual VirtualLinks_ptr createVirtualLinks();
        virtual VirtualLink_ptr createVirtualLink();
        virtual PCFVirtualLink_ptr createPCFVirtualLink();
        virtual DataVirtualLink_ptr createDataVirtualLink();
        virtual RCVirtualLink_ptr createRCVirtualLink();
        virtual TTVirtualLink_ptr createTTVirtualLink();
        virtual FrameRoute_ptr createFrameRoute();
        virtual FrameRouteSegment_ptr createFrameRouteSegment();
        virtual Periods_ptr createPeriods();
        virtual Period_ptr createPeriod();
        virtual AbsolutePeriod_ptr createAbsolutePeriod();
        virtual RelativePeriod_ptr createRelativePeriod();
        virtual SubPeriod_ptr createSubPeriod();
        virtual Alias_ptr createAlias();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< System_SpecificationFactory > s_instance;

        System_SpecificationFactory();

    };

} // System_Specification


#endif // _SYSTEM_SPECIFICATIONFACTORY_HPP
