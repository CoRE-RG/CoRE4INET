// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/DeviceMapping.hpp
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

#ifndef DEVICE_TARGET_MAPPING_DEVICEMAPPING_HPP
#define DEVICE_TARGET_MAPPING_DEVICEMAPPING_HPP

#include <Device_Target_Mapping_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Device_Targets_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(DeviceMapping_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Target_Mapping
{

    class DeviceMapping: public virtual ::System_Specification::NamedElement
    {
    public:
        DeviceMapping();

        virtual ~DeviceMapping();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::TimeType getAgingTime() const;
        void setAgingTime(::System_Specification::TimeType _agingTime);

        // References
        ::Device_Targets::TargetDevice_ptr getRefTargetDevice();
        void setRefTargetDevice(
                ::Device_Targets::TargetDevice_ptr _refTargetDevice);

        ::Device_Target_Mapping::PerPortBagAccounts_ptr getPerPortBagAccounts();
        void
                setPerPortBagAccounts(
                        ::Device_Target_Mapping::PerPortBagAccounts_ptr _perPortBagAccounts);

        ::Device_Target_Mapping::PortMappings_ptr getPortMappings();
        void setPortMappings(
                ::Device_Target_Mapping::PortMappings_ptr _portMappings);

        ::ecorecpp::mapping::EList< ::Device_Targets::AntiMasquerading >
                & getAntiMasquerading();

        ::Device_Targets::Diagnostic_ptr getDiagnostic();
        void setDiagnostic(::Device_Targets::Diagnostic_ptr _diagnostic);

        ::ecorecpp::mapping::EList< ::Device_Target_Mapping::Trigger >
                & getTrigger();

        ::Device_Target_Mapping::BufferMapping_ptr getBufferMapping();
        void setBufferMapping(
                ::Device_Target_Mapping::BufferMapping_ptr _bufferMapping);

        ::Device_Targets::ManagementInterface_ptr getManagementInterface();
        void setManagementInterface(
                ::Device_Targets::ManagementInterface_ptr _managementInterface);

        ::System_Specification::MetaInformation_ptr getMetaInformation();
        void setMetaInformation(
                ::System_Specification::MetaInformation_ptr _metaInformation);

        /*PROTECTED REGION ID(DeviceMapping) START*/
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

        /*PROTECTED REGION ID(DeviceMappingImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::TimeType m_agingTime;

        // References

        ::Device_Targets::TargetDevice_ptr m_refTargetDevice;

        ::Device_Target_Mapping::PerPortBagAccounts_ptr m_perPortBagAccounts;

        ::Device_Target_Mapping::PortMappings_ptr m_portMappings;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Device_Targets::AntiMasquerading > > m_antiMasquerading;

        ::Device_Targets::Diagnostic_ptr m_diagnostic;

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Device_Target_Mapping::Trigger > > m_trigger;

        ::Device_Target_Mapping::BufferMapping_ptr m_bufferMapping;

        ::Device_Targets::ManagementInterface_ptr m_managementInterface;

        ::System_Specification::MetaInformation_ptr m_metaInformation;

    };

} // Device_Target_Mapping

#endif // DEVICE_TARGET_MAPPING_DEVICEMAPPING_HPP
