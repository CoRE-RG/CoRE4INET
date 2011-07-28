// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/PortMapping.hpp
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

#ifndef DEVICE_TARGET_MAPPING_PORTMAPPING_HPP
#define DEVICE_TARGET_MAPPING_PORTMAPPING_HPP

#include <Device_Target_Mapping_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <Device_Targets_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(PortMapping_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Target_Mapping
{

    class PortMapping: public virtual ::System_Specification::NamedElement
    {
    public:
        PortMapping();

        virtual ~PortMapping();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::TimeType getRxLatencyCorrection() const;
        void setRxLatencyCorrection(
                ::System_Specification::TimeType _rxLatencyCorrection);

        ::System_Specification::TimeType getTxLatencyCorrection() const;
        void setTxLatencyCorrection(
                ::System_Specification::TimeType _txLatencyCorrection);

        ::ecore::EBoolean isDisableRxFc() const;
        void setDisableRxFc(::ecore::EBoolean _disableRxFc);

        ::ecore::EBoolean isDisableTxFc() const;
        void setDisableTxFc(::ecore::EBoolean _disableTxFc);

        // References
        ::Device_Targets::TargetPort_ptr getRefTargetPort();
        void setRefTargetPort(::Device_Targets::TargetPort_ptr _refTargetPort);

        ::System_Specification::Port_ptr getRefPort();
        void setRefPort(::System_Specification::Port_ptr _refPort);

        /*PROTECTED REGION ID(PortMapping) START*/
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

        /*PROTECTED REGION ID(PortMappingImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::TimeType m_rxLatencyCorrection;

        ::System_Specification::TimeType m_txLatencyCorrection;

        ::ecore::EBoolean m_disableRxFc;

        ::ecore::EBoolean m_disableTxFc;

        // References

        ::Device_Targets::TargetPort_ptr m_refTargetPort;

        ::System_Specification::Port_ptr m_refPort;

    };

} // Device_Target_Mapping

#endif // DEVICE_TARGET_MAPPING_PORTMAPPING_HPP
