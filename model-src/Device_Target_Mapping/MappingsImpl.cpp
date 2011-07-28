// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Target_Mapping/MappingsImpl.cpp
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

#include "Mappings.hpp"
#include <Device_Target_Mapping/Device_Target_MappingPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Target_Mapping/DeviceMappings.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Target_Mapping;

/*PROTECTED REGION ID(MappingsImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void Mappings::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences
    if (m_deviceMappings)
    {
        m_deviceMappings->_initialize();
        m_deviceMappings->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getMappings__deviceMappings());
    }
    if (m_containingVirtualLinkMapping)
    {
        m_containingVirtualLinkMapping->_initialize();
        m_containingVirtualLinkMapping->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getMappings__containingVirtualLinkMapping());
    }
    if (m_metaInformation)
    {
        m_metaInformation->_initialize();
        m_metaInformation->_setEContainer(
                this,
                ::Device_Target_Mapping::Device_Target_MappingPackage::_instance()->getMappings__metaInformation());
    }

    /*PROTECTED REGION ID(MappingsImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject Mappings::eGet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__DEVICEMAPPINGS:
    {
        _any = static_cast< ::ecore::EObject* > (m_deviceMappings);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__CONTAININGVIRTUALLINKMAPPING:
    {
        _any
                = static_cast< ::ecore::EObject* > (m_containingVirtualLinkMapping);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__REFVIRTUALLINKMAPPINGS:
    {
        _any = static_cast< ::ecore::EObject* > (m_refVirtualLinkMappings);
    }
        return _any;

    }
    throw "Error";
}

void Mappings::eSet(::ecore::EInt _featureID,
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__DEVICEMAPPINGS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Target_Mapping::DeviceMappings_ptr
                _t1 =
                        dynamic_cast< ::Device_Target_Mapping::DeviceMappings_ptr > (_t0);
        ::Device_Target_Mapping::Mappings::setDeviceMappings(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__CONTAININGVIRTUALLINKMAPPING:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Virtuallink_Map::VirtualLinkMapping_ptr _t1 =
                dynamic_cast< ::Virtuallink_Map::VirtualLinkMapping_ptr > (_t0);
        ::Device_Target_Mapping::Mappings::setContainingVirtualLinkMapping(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::Device_Target_Mapping::Mappings::setMetaInformation(_t1);
    }
        return;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__REFVIRTUALLINKMAPPINGS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Virtuallink_Map::VirtualLinkMapping_ptr _t1 =
                dynamic_cast< ::Virtuallink_Map::VirtualLinkMapping_ptr > (_t0);
        ::Device_Target_Mapping::Mappings::setRefVirtualLinkMappings(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean Mappings::eIsSet(::ecore::EInt _featureID)
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
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__DEVICEMAPPINGS:
        return m_deviceMappings;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__CONTAININGVIRTUALLINKMAPPING:
        return m_containingVirtualLinkMapping;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__METAINFORMATION:
        return m_metaInformation;
    case ::Device_Target_Mapping::Device_Target_MappingPackage::MAPPINGS__REFVIRTUALLINKMAPPINGS:
        return m_refVirtualLinkMappings;

    }
    throw "Error";
}

void Mappings::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr Mappings::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Target_Mapping::Device_Target_MappingPackage_ptr > (::Device_Target_Mapping::Device_Target_MappingPackage::_instance())->getMappings();
    return _eclass;
}

