// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/Port.hpp
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

#ifndef SYSTEM_SPECIFICATION_PORT_HPP
#define SYSTEM_SPECIFICATION_PORT_HPP

#include <System_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification/NamedElement.hpp>

/*PROTECTED REGION ID(Port_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace System_Specification
{

    class Port: public virtual ::System_Specification::NamedElement
    {
    public:
        Port();

        virtual ~Port();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::SpeedEnum getTransmissionSpeed() const;
        void setTransmissionSpeed(
                ::System_Specification::SpeedEnum _transmissionSpeed);

        ::System_Specification::TimeType getStaticRxDelay() const;
        void setStaticRxDelay(::System_Specification::TimeType _staticRxDelay);

        ::System_Specification::TimeType getStaticTxDelay() const;
        void setStaticTxDelay(::System_Specification::TimeType _staticTxDelay);

        ::System_Specification::MediaType getMediaType() const;
        void setMediaType(::System_Specification::MediaType _mediaType);

        // References
        ::System_Specification::Device_ptr getDevice();
        void setDevice(::System_Specification::Device_ptr _device);

        /*PROTECTED REGION ID(Port) START*/
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

        /*PROTECTED REGION ID(PortImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::SpeedEnum m_transmissionSpeed;

        ::System_Specification::TimeType m_staticRxDelay;

        ::System_Specification::TimeType m_staticTxDelay;

        ::System_Specification::MediaType m_mediaType;

        // References

        ::System_Specification::Device_ptr m_device;

    };

} // System_Specification

#endif // SYSTEM_SPECIFICATION_PORT_HPP
