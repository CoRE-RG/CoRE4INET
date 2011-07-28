// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/DedicatedBufferImpl.cpp
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

#include "DedicatedBuffer.hpp"
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <Device_Target_Mapping/CriticalTrafficBuffer.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Target_Mapping;

/*PROTECTED REGION ID(DedicatedBufferImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void DedicatedBuffer::_initialize()
{
    // Supertypes
    ::Device_Target_Mapping::CriticalTrafficBuffer::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(DedicatedBufferImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject DedicatedBuffer::eGet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__TYPE:
    {
        ::ecorecpp::mapping::any_traits<
                ::Device_Target_Mapping::BufferTypeEnum >::toAny(_any, m_type);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__DEPTH:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any, m_depth);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__SIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any, m_size);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__FLUSHONSCHEDULERESET:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_flushOnScheduleReset);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MEMORYBUFFER__BASEADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Target_Mapping::MemoryAddress >::toAny(
                _any, m_baseAddress);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEDICATEDBUFFER__REFVIRTUALLINK:
    {
        _any = static_cast< ::ecore::EObject* > (m_refVirtualLink);
    }
        return _any;

    }
    throw "Error";
}

void DedicatedBuffer::eSet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__TYPE:
    {
        ::ecorecpp::mapping::any_traits<
                ::Device_Target_Mapping::BufferTypeEnum >::fromAny(_newValue,
                m_type);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__DEPTH:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_depth);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__SIZE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_size);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__FLUSHONSCHEDULERESET:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_flushOnScheduleReset);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MEMORYBUFFER__BASEADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Target_Mapping::MemoryAddress >::fromAny(
                _newValue, m_baseAddress);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEDICATEDBUFFER__REFVIRTUALLINK:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::VirtualLink_ptr _t1 =
                dynamic_cast< ::System_Specification::VirtualLink_ptr > (_t0);
        ::Device_Target_Mapping::DedicatedBuffer::setRefVirtualLink(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean DedicatedBuffer::eIsSet(::ecore::EInt _featureID)
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__TYPE:
        /*PROTECTED REGION ID(DedicatedBuffereIsSet__DedicatedBufferm_type) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__DEPTH:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(m_depth);
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__SIZE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EInt >::is_set(m_size);
    case ::Device_Target_Mapping::Device_Target_MappingPackage::BUFFER__FLUSHONSCHEDULERESET:
        /*PROTECTED REGION ID(DedicatedBuffereIsSet__DedicatedBufferm_flushOnScheduleReset) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_flushOnScheduleReset != false;
        /*PROTECTED REGION END*/
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MEMORYBUFFER__BASEADDRESS:
        return ::ecorecpp::mapping::set_traits<
                ::Device_Target_Mapping::MemoryAddress >::is_set(m_baseAddress);
    case ::Device_Target_Mapping::Device_Target_MappingPackage::DEDICATEDBUFFER__REFVIRTUALLINK:
        return m_refVirtualLink;

    }
    throw "Error";
}

void DedicatedBuffer::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr DedicatedBuffer::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage_ptr > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getDedicatedBuffer();
    return _eclass;
}

