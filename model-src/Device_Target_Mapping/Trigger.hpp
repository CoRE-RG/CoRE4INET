// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/Trigger.hpp
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

#ifndef DEVICE_TARGET_MAPPING_TRIGGER_HPP
#define DEVICE_TARGET_MAPPING_TRIGGER_HPP

#include <Device_Target_Mapping_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <Device_Specification_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(Trigger_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Target_Mapping
{

    class Trigger: public virtual ::System_Specification::ModelElement
    {
    public:
        Trigger();

        virtual ~Trigger();

        virtual void _initialize();

        // Operations


        // Attributes
        ::ecore::EString const& getDevice() const;
        void setDevice(::ecore::EString const& _device);

        ::ecore::EString const& getTarget() const;
        void setTarget(::ecore::EString const& _target);

        // References
        ::Device_Specification::TriggerSchedule_ptr getRefTriggerSchedule();
        void
                setRefTriggerSchedule(
                        ::Device_Specification::TriggerSchedule_ptr _refTriggerSchedule);

        /*PROTECTED REGION ID(Trigger) START*/
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

        /*PROTECTED REGION ID(TriggerImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_device;

        ::ecore::EString m_target;

        // References

        ::Device_Specification::TriggerSchedule_ptr m_refTriggerSchedule;

    };

} // Device_Target_Mapping

#endif // DEVICE_TARGET_MAPPING_TRIGGER_HPP
