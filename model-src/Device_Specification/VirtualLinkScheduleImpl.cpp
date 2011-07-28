// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/VirtualLinkScheduleImpl.cpp
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

#include "VirtualLinkSchedule.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <Device_Specification/CTIncoming.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(VirtualLinkScheduleImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void VirtualLinkSchedule::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_incoming->size(); i++)
    {
        (*m_incoming)[i]->_initialize();
        (*m_incoming)[i]->_setEContainer(
                this,
                ::Device_Specification::Device_SpecificationPackage::_instance()->getVirtualLinkSchedule__incoming());
    }

    /*PROTECTED REGION ID(VirtualLinkScheduleImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject VirtualLinkSchedule::eGet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__PRIORITY:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::toAny(_any,
                m_priority);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__REFVIRTUALLINK:
    {
        _any = static_cast< ::ecore::EObject* > (m_refVirtualLink);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__INCOMING:
    {
        _any = m_incoming->asEListOf< ::ecore::EObject > ();
    }
        return _any;

    }
    throw "Error";
}

void VirtualLinkSchedule::eSet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__PRIORITY:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EByte >::fromAny(_newValue,
                m_priority);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__REFVIRTUALLINK:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::VirtualLink_ptr _t1 =
                dynamic_cast< ::System_Specification::VirtualLink_ptr > (_t0);
        ::Device_Specification::VirtualLinkSchedule::setRefVirtualLink(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__INCOMING:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Specification::VirtualLinkSchedule::getIncoming().clear();
        ::Device_Specification::VirtualLinkSchedule::getIncoming().insert_all(
                *_t0);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean VirtualLinkSchedule::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__PRIORITY:
        /*PROTECTED REGION ID(VirtualLinkScheduleeIsSet__VirtualLinkSchedulem_priority) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_priority != 6;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__REFVIRTUALLINK:
        return m_refVirtualLink;
    case ::Device_Specification::Device_SpecificationPackage::VIRTUALLINKSCHEDULE__INCOMING:
        return m_incoming && m_incoming->size();

    }
    throw "Error";
}

void VirtualLinkSchedule::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr VirtualLinkSchedule::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getVirtualLinkSchedule();
    return _eclass;
}

