// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/DiagnosisScheduleEntryImpl.cpp
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

#include "DiagnosisScheduleEntry.hpp"
#include <Device_Targets/Device_TargetsPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Targets;

/*PROTECTED REGION ID(DiagnosisScheduleEntryImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void DiagnosisScheduleEntry::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(DiagnosisScheduleEntryImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject DiagnosisScheduleEntry::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean _resolve)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
    {
        _any = m_eAnnotations->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_signature);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__TIME:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_time);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMADDRESS:
    {
        ::ecorecpp::mapping::any_traits<
                ::System_Specification::UniversalNumberType >::toAny(_any,
                m_itemAddress);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMSNUMBER:
    {
        ::ecorecpp::mapping::any_traits<
                ::System_Specification::UniversalNumberType >::toAny(_any,
                m_itemsNumber);
    }
        return _any;

    }
    throw "Error";
}

void DiagnosisScheduleEntry::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::System_Specification::ModelElement::getEAnnotations().clear();
        ::System_Specification::ModelElement::getEAnnotations().insert_all(*_t0);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_signature);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__TIME:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_time);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMADDRESS:
    {
        ::ecorecpp::mapping::any_traits<
                ::System_Specification::UniversalNumberType >::fromAny(
                _newValue, m_itemAddress);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMSNUMBER:
    {
        ::ecorecpp::mapping::any_traits<
                ::System_Specification::UniversalNumberType >::fromAny(
                _newValue, m_itemsNumber);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean DiagnosisScheduleEntry::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__TIME:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_time);
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMADDRESS:
        /*PROTECTED REGION ID(DiagnosisScheduleEntryeIsSet__DiagnosisScheduleEntrym_itemAddress) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_itemAddress != 0x0000;
        /*PROTECTED REGION END*/
    case ::Device_Targets::Device_TargetsPackage::DIAGNOSISSCHEDULEENTRY__ITEMSNUMBER:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::UniversalNumberType >::is_set(
                m_itemsNumber);

    }
    throw "Error";
}

void DiagnosisScheduleEntry::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr DiagnosisScheduleEntry::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (::Device_Targets::Device_TargetsPackage::_instance())->getDiagnosisScheduleEntry();
    return _eclass;
}

