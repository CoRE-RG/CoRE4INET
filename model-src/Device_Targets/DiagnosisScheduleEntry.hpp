// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/DiagnosisScheduleEntry.hpp
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

#ifndef DEVICE_TARGETS_DIAGNOSISSCHEDULEENTRY_HPP
#define DEVICE_TARGETS_DIAGNOSISSCHEDULEENTRY_HPP

#include <Device_Targets_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>
#include <System_Specification_forward.hpp>
#include <System_Specification/ModelElement.hpp>

/*PROTECTED REGION ID(DiagnosisScheduleEntry_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace Device_Targets
{

    class DiagnosisScheduleEntry: public virtual ::System_Specification::ModelElement
    {
    public:
        DiagnosisScheduleEntry();

        virtual ~DiagnosisScheduleEntry();

        virtual void _initialize();

        // Operations


        // Attributes
        ::System_Specification::TimeType getTime() const;
        void setTime(::System_Specification::TimeType _time);

        ::System_Specification::UniversalNumberType getItemAddress() const;
        void setItemAddress(
                ::System_Specification::UniversalNumberType _itemAddress);

        ::System_Specification::UniversalNumberType getItemsNumber() const;
        void setItemsNumber(
                ::System_Specification::UniversalNumberType _itemsNumber);

        // References


        /*PROTECTED REGION ID(DiagnosisScheduleEntry) START*/
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

        /*PROTECTED REGION ID(DiagnosisScheduleEntryImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::System_Specification::TimeType m_time;

        ::System_Specification::UniversalNumberType m_itemAddress;

        ::System_Specification::UniversalNumberType m_itemsNumber;

        // References

    };

} // Device_Targets

#endif // DEVICE_TARGETS_DIAGNOSISSCHEDULEENTRY_HPP
