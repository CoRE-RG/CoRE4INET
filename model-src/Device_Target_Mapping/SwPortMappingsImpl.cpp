// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/SwPortMappingsImpl.cpp
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

#include "SwPortMappings.hpp"
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <Device_Target_Mapping/PortMappings.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <Device_Target_Mapping/SwPortMapping.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Target_Mapping;

/*PROTECTED REGION ID(SwPortMappingsImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void SwPortMappings::_initialize()
{
    // Supertypes
    ::Device_Target_Mapping::PortMappings::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_targetPortMapping->size(); i++)
    {
        (*m_targetPortMapping)[i]->_initialize();
        (*m_targetPortMapping)[i]->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getSwPortMappings__targetPortMapping());
    }

    /*PROTECTED REGION ID(SwPortMappingsImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject SwPortMappings::eGet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPINGS__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPINGS__TARGETPORTMAPPING:
    {
        _any = m_targetPortMapping->asEListOf< ::ecore::EObject > ();
    }
        return _any;

    }
    throw "Error";
}

void SwPortMappings::eSet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPINGS__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::Device_Target_Mapping::PortMappings::setMetaInformation(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPINGS__TARGETPORTMAPPING:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Target_Mapping::SwPortMappings::getTargetPortMapping().clear();
        ::Device_Target_Mapping::SwPortMappings::getTargetPortMapping().insert_all(
                *_t0);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean SwPortMappings::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Target_Mapping::Device_Target_MappingPackage::PORTMAPPINGS__METAINFORMATION:
        return m_metaInformation;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::SWPORTMAPPINGS__TARGETPORTMAPPING:
        return m_targetPortMapping && m_targetPortMapping->size();

    }
    throw "Error";
}

void SwPortMappings::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr SwPortMappings::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage_ptr > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getSwPortMappings();
    return _eclass;
}

