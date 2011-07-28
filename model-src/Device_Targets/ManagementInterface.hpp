// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/ManagementInterface.hpp
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

#ifndef DEVICE_TARGETS_MANAGEMENTINTERFACE_HPP
#define DEVICE_TARGETS_MANAGEMENTINTERFACE_HPP

#include <Device_Targets_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(ManagementInterface_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Targets
{

    class ManagementInterface: public virtual ::System_Specification::ModelElement
    {
    public:
        ManagementInterface();

        virtual ~ManagementInterface();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EInt getConfigurationVersion() const;
        void setConfigurationVersion(::ecore::EInt _configurationVersion);

        ::System_Specification::SpeedEnum getSpeed() const;
        void setSpeed(::System_Specification::SpeedEnum _speed);

        ::System_Specification::TimeType getUnlockWrTimeout() const;
        void setUnlockWrTimeout(
                ::System_Specification::TimeType _unlockWrTimeout);

        ::System_Specification::TimeType getResetTimeout() const;
        void setResetTimeout(::System_Specification::TimeType _resetTimeout);

        ::System_Specification::MacAddressType getUnlockDestAddress() const;
        void setUnlockDestAddress(
                ::System_Specification::MacAddressType _unlockDestAddress);

        ::System_Specification::MacAddressType getSchedDiagDestAddress() const;
        void setSchedDiagDestAddress(
                ::System_Specification::MacAddressType _schedDiagDestAddress);

        ::System_Specification::MacAddressType getSourceAddress() const;
        void setSourceAddress(
                ::System_Specification::MacAddressType _sourceAddress);

        ::ecore::EByte getExpectedUnlocks() const;
        void setExpectedUnlocks(::ecore::EByte _expectedUnlocks);

        ::ecore::EByte getExpectedResets() const;
        void setExpectedResets(::ecore::EByte _expectedResets);

        ::Device_Targets::diagnosisScheduleModeEnum
                getDiagnosisScheduleMode() const;
        void
                setDiagnosisScheduleMode(
                        ::Device_Targets::diagnosisScheduleModeEnum _diagnosisScheduleMode);

        ::System_Specification::TimeType getApbTimeout() const;
        void setApbTimeout(::System_Specification::TimeType _apbTimeout);

        // References
        ::ecorecpp::mapping::EList< ::Device_Targets::MacAcceptanceEntry >
                & getMacAcceptanceEntry();

        /*PROTECTED REGION ID(ManagementInterface) START*/
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

        /*PROTECTED REGION ID(ManagementInterfaceImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EInt m_configurationVersion;

        ::System_Specification::SpeedEnum m_speed;

        ::System_Specification::TimeType m_unlockWrTimeout;

        ::System_Specification::TimeType m_resetTimeout;

        ::System_Specification::MacAddressType m_unlockDestAddress;

        ::System_Specification::MacAddressType m_schedDiagDestAddress;

        ::System_Specification::MacAddressType m_sourceAddress;

        ::ecore::EByte m_expectedUnlocks;

        ::ecore::EByte m_expectedResets;

        ::Device_Targets::diagnosisScheduleModeEnum m_diagnosisScheduleMode;

        ::System_Specification::TimeType m_apbTimeout;

        // References

        ::ecorecpp::mapping::out_ptr< ::ecorecpp::mapping::EList<
                ::Device_Targets::MacAcceptanceEntry > > m_macAcceptanceEntry;

    };

} // Device_Targets

#endif // DEVICE_TARGETS_MANAGEMENTINTERFACE_HPP
