// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/SystemSpecification.hpp
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

#ifndef SYSTEM_SPECIFICATION_SYSTEMSPECIFICATION_HPP
#define SYSTEM_SPECIFICATION_SYSTEMSPECIFICATION_HPP

#include <System_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(SystemSpecification_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace System_Specification
{

    class SystemSpecification: public virtual ::System_Specification::ModelElement
    {
    public:
        SystemSpecification();

        virtual ~SystemSpecification();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        ::System_Specification::Units_ptr getUnits();
        void setUnits(::System_Specification::Units_ptr _units);

        ::System_Specification::VirtualLinks_ptr getVirtualLinks();
        void setVirtualLinks(
                ::System_Specification::VirtualLinks_ptr _virtualLinks);

        ::System_Specification::Devices_ptr getDevices();
        void setDevices(::System_Specification::Devices_ptr _devices);

        ::System_Specification::Links_ptr getLinks();
        void setLinks(::System_Specification::Links_ptr _links);

        ::System_Specification::Periods_ptr getPeriods();
        void setPeriods(::System_Specification::Periods_ptr _periods);

        /*PROTECTED REGION ID(SystemSpecification) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(SystemSpecificationImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::System_Specification::MetaInformation_ptr m_metaInformation;

        ::System_Specification::Units_ptr m_units;

        ::System_Specification::VirtualLinks_ptr m_virtualLinks;

        ::System_Specification::Devices_ptr m_devices;

        ::System_Specification::Links_ptr m_links;

        ::System_Specification::Periods_ptr m_periods;

    };

} // System_Specification

#endif // SYSTEM_SPECIFICATION_SYSTEMSPECIFICATION_HPP
