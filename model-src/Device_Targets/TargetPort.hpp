// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TargetPort.hpp
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

#ifndef DEVICE_TARGETS_TARGETPORT_HPP
#define DEVICE_TARGETS_TARGETPORT_HPP

#include <Device_Targets_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(TargetPort_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Targets
{

    class TargetPort: public virtual ::System_Specification::NamedElement
    {
    public:
        TargetPort();

        virtual ~TargetPort();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::TimeType getRxLatency() const;
        void setRxLatency(::System_Specification::TimeType _rxLatency);

        ::System_Specification::TimeType getTxLatency() const;
        void setTxLatency(::System_Specification::TimeType _txLatency);

        ::System_Specification::SpeedEnum getSpeed() const;
        void setSpeed(::System_Specification::SpeedEnum _speed);

        ::Device_Targets::PortTypeType getPortType() const;
        void setPortType(::Device_Targets::PortTypeType _portType);

        ::ecore::EInt getPortSerialNumber() const;
        void setPortSerialNumber(::ecore::EInt _portSerialNumber);

        // References


        /*PROTECTED REGION ID(TargetPort) START*/
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

        /*PROTECTED REGION ID(TargetPortImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::TimeType m_rxLatency;

        ::System_Specification::TimeType m_txLatency;

        ::System_Specification::SpeedEnum m_speed;

        ::Device_Targets::PortTypeType m_portType;

        ::ecore::EInt m_portSerialNumber;

        // References

    };

} // Device_Targets

#endif // DEVICE_TARGETS_TARGETPORT_HPP
