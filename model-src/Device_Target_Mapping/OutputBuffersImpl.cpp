// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/OutputBuffersImpl.cpp
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

#include "OutputBuffers.hpp"
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Target_Mapping/DedicatedBuffer.hpp>
#include <Device_Target_Mapping/SharedBuffer.hpp>
#include <Device_Target_Mapping/COTSBuffer.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Target_Mapping;

/*PROTECTED REGION ID(OutputBuffersImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void OutputBuffers::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_dedicatedBuffer->size(); i++)
    {
        (*m_dedicatedBuffer)[i]->_initialize();
        (*m_dedicatedBuffer)[i]->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getOutputBuffers__dedicatedBuffer());
    }
    for (size_t i = 0; i < m_sharedBuffer->size(); i++)
    {
        (*m_sharedBuffer)[i]->_initialize();
        (*m_sharedBuffer)[i]->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getOutputBuffers__sharedBuffer());
    }
    for (size_t i = 0; i < m_cotsBuffer->size(); i++)
    {
        (*m_cotsBuffer)[i]->_initialize();
        (*m_cotsBuffer)[i]->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getOutputBuffers__cotsBuffer());
    }

    /*PROTECTED REGION ID(OutputBuffersImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject OutputBuffers::eGet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__DEDICATEDBUFFER:
    {
        _any = m_dedicatedBuffer->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__SHAREDBUFFER:
    {
        _any = m_sharedBuffer->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__COTSBUFFER:
    {
        _any = m_cotsBuffer->asEListOf< ::ecore::EObject > ();
    }
        return _any;

    }
    throw "Error";
}

void OutputBuffers::eSet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__DEDICATEDBUFFER:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Target_Mapping::OutputBuffers::getDedicatedBuffer().clear();
        ::Device_Target_Mapping::OutputBuffers::getDedicatedBuffer().insert_all(
                *_t0);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__SHAREDBUFFER:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Target_Mapping::OutputBuffers::getSharedBuffer().clear();
        ::Device_Target_Mapping::OutputBuffers::getSharedBuffer().insert_all(
                *_t0);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__COTSBUFFER:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Target_Mapping::OutputBuffers::getCotsBuffer().clear();
        ::Device_Target_Mapping::OutputBuffers::getCotsBuffer().insert_all(*_t0);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean OutputBuffers::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__DEDICATEDBUFFER:
        return m_dedicatedBuffer && m_dedicatedBuffer->size();
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__SHAREDBUFFER:
        return m_sharedBuffer && m_sharedBuffer->size();
    case ::Device_Target_Mapping::Device_Target_MappingPackage::OUTPUTBUFFERS__COTSBUFFER:
        return m_cotsBuffer && m_cotsBuffer->size();

    }
    throw "Error";
}

void OutputBuffers::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr OutputBuffers::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage_ptr > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getOutputBuffers();
    return _eclass;
}

