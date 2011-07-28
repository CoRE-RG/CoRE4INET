// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/TTTechIpTargetDevice.hpp
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

#ifndef DEVICE_TARGETS_TTTECHIPTARGETDEVICE_HPP
#define DEVICE_TARGETS_TTTECHIPTARGETDEVICE_HPP

#include <Device_Targets_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <IP_Configuration_forward.hpp>
#include <Device_Target_Mapping_forward.hpp>
#include <Device_Targets/TargetDevice.hpp>

/*PROTECTED REGION ID(TTTechIpTargetDevice_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Targets
{

    class TTTechIpTargetDevice: public virtual ::Device_Targets::TargetDevice
    {
    public:
        TTTechIpTargetDevice();

        virtual ~TTTechIpTargetDevice();

        virtual void _initialize();

        // Operations


        // Attributes
        ::Device_Target_Mapping::FrequencyType getClockSpeed() const;
        void setClockSpeed(::Device_Target_Mapping::FrequencyType _clockSpeed);

        ::ecore::EBoolean isMediaControlEnabled() const;
        void setMediaControlEnabled(::ecore::EBoolean _mediaControlEnabled);

        // References


        /*PROTECTED REGION ID(TTTechIpTargetDevice) START*/
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

        /*PROTECTED REGION ID(TTTechIpTargetDeviceImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::Device_Target_Mapping::FrequencyType m_clockSpeed;

        ::ecore::EBoolean m_mediaControlEnabled;

        // References

    };

} // Device_Targets

#endif // DEVICE_TARGETS_TTTECHIPTARGETDEVICE_HPP
