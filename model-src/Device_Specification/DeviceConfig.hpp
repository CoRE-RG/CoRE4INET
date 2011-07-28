// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/DeviceConfig.hpp
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

#ifndef DEVICE_SPECIFICATION_DEVICECONFIG_HPP
#define DEVICE_SPECIFICATION_DEVICECONFIG_HPP

#include <Device_Specification_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <ecore/ENamedElement.hpp>

/*PROTECTED REGION ID(DeviceConfig_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Specification
{

    class DeviceConfig: public virtual ::ecore::ENamedElement
    {
    public:
        DeviceConfig();

        virtual ~DeviceConfig();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::CTMarkerType getCtMarker() const;
        void setCtMarker(::System_Specification::CTMarkerType _ctMarker);

        ::System_Specification::CTMarkerType getCtMask() const;
        void setCtMask(::System_Specification::CTMarkerType _ctMask);

        // References


        /*PROTECTED REGION ID(DeviceConfig) START*/
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

        /*PROTECTED REGION ID(DeviceConfigImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::CTMarkerType m_ctMarker;

        ::System_Specification::CTMarkerType m_ctMask;

        // References

    };

} // Device_Specification

#endif // DEVICE_SPECIFICATION_DEVICECONFIG_HPP
