// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/DeviceSpecification.hpp
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

#ifndef DEVICE_SPECIFICATION_DEVICESPECIFICATION_HPP
#define DEVICE_SPECIFICATION_DEVICESPECIFICATION_HPP

#include <Device_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Target_Mapping_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(DeviceSpecification_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Specification
{

    class DeviceSpecification: public virtual ::System_Specification::NamedElement
    {
    public:
        DeviceSpecification();

        virtual ~DeviceSpecification();

        virtual void _initialize();

        // Operations


        // Attributes

        // References
        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        ::System_Specification::Units_ptr getUnits();
        void setUnits(::System_Specification::Units_ptr _units);

        ::Device_Specification::BagAccounts_ptr getBagAccounts();
        void setBagAccounts(
                ::Device_Specification::BagAccounts_ptr _bagAccounts);

        ::Device_Specification::VirtualLinkSchedules_ptr getVlSchedules();
        void setVlSchedules(
                ::Device_Specification::VirtualLinkSchedules_ptr _vlSchedules);

        ::Device_Specification::BestEffortRouting_ptr getBestEffortRouting();
        void
                setBestEffortRouting(
                        ::Device_Specification::BestEffortRouting_ptr _bestEffortRouting);

        ::Device_Specification::FlowControl_ptr getFlowControl();
        void setFlowControl(
                ::Device_Specification::FlowControl_ptr _flowControl);

        ::Device_Specification::Periods_ptr getPeriods();
        void setPeriods(::Device_Specification::Periods_ptr _periods);

        ::Device_Target_Mapping::DeviceMapping_ptr getRefDeviceMapping();
        void setRefDeviceMapping(
                ::Device_Target_Mapping::DeviceMapping_ptr _refDeviceMapping);

        /*PROTECTED REGION ID(DeviceSpecification) START*/
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

        /*PROTECTED REGION ID(DeviceSpecificationImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes


        // References

        ::System_Specification::MetaInformation_ptr m_metaInformation;

        ::System_Specification::Units_ptr m_units;

        ::Device_Specification::BagAccounts_ptr m_bagAccounts;

        ::Device_Specification::VirtualLinkSchedules_ptr m_vlSchedules;

        ::Device_Specification::BestEffortRouting_ptr m_bestEffortRouting;

        ::Device_Specification::FlowControl_ptr m_flowControl;

        ::Device_Specification::Periods_ptr m_periods;

        ::Device_Target_Mapping::DeviceMapping_ptr m_refDeviceMapping;

    };

} // Device_Specification

#endif // DEVICE_SPECIFICATION_DEVICESPECIFICATION_HPP
