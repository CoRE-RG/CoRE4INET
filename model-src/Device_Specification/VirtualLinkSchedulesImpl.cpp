// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/VirtualLinkSchedulesImpl.cpp
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

#include "VirtualLinkSchedules.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/VirtualLinkSchedule.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(VirtualLinkSchedulesImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void VirtualLinkSchedules::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_vlSchedule->size(); i++)
    {
        (*m_vlSchedule)[i]->_initialize();
        (*m_vlSchedule)[i]->_setEContainer(
                this,
                ::Device_Specification::Device_SpecificationPackage::_instance()->getVirtualLinkSchedules__vlSchedule());
    }

    /*PROTECTED REGION ID(VirtualLinkSchedulesImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject VirtualLinkSchedules::eGet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any, m_name);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__VLSCHEDULE:
    {
        _any = m_vlSchedule->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__SCHEDULESTARTAFTERSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_scheduleStartAfterSync);
    }
        return _any;

    }
    throw "Error";
}

void VirtualLinkSchedules::eSet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_name);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__VLSCHEDULE:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Specification::VirtualLinkSchedules::getVlSchedule().clear();
        ::Device_Specification::VirtualLinkSchedules::getVlSchedule().insert_all(
                *_t0);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__SCHEDULESTARTAFTERSYNC:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_scheduleStartAfterSync);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean VirtualLinkSchedules::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::System_Specification::System_SpecificationPackage::NAMEDELEMENT__NAME:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_name);
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__VLSCHEDULE:
        return m_vlSchedule && m_vlSchedule->size();
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULES__SCHEDULESTARTAFTERSYNC:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(
                m_scheduleStartAfterSync);

    }
    throw "Error";
}

void VirtualLinkSchedules::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr VirtualLinkSchedules::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getVirtualLinkSchedules();
    return _eclass;
}

