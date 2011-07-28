// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/VirtualLinkMappingsImpl.cpp
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

#include "VirtualLinkMappings.hpp"
#include <Virtuallink_Map/Virtuallink_MapPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Virtuallink_Map;

/*PROTECTED REGION ID(VirtualLinkMappingsImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void VirtualLinkMappings::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_virtualLinkMapping->size(); i++)
    {
        (*m_virtualLinkMapping)[i]->_initialize();
        (*m_virtualLinkMapping)[i]->_setEContainer(
                this,
                ::Virtuallink_Map::Virtuallink_MapPackage::_instance()->getVirtualLinkMappings__virtualLinkMapping());
    }
    if (m_metaInformation)
    {
        m_metaInformation->_initialize();
        m_metaInformation->_setEContainer(
                this,
                ::Virtuallink_Map::Virtuallink_MapPackage::_instance()->getVirtualLinkMappings__metaInformation());
    }

    /*PROTECTED REGION ID(VirtualLinkMappingsImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject VirtualLinkMappings::eGet(::ecore::EInt _featureID,
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
    case ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__VIRTUALLINKMAPPING:
    {
        _any = m_virtualLinkMapping->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;

    }
    throw "Error";
}

void VirtualLinkMappings::eSet(::ecore::EInt _featureID,
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
    case ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__VIRTUALLINKMAPPING:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Virtuallink_Map::VirtualLinkMappings::getVirtualLinkMapping().clear();
        ::Virtuallink_Map::VirtualLinkMappings::getVirtualLinkMapping().insert_all(
                *_t0);
    }
        return;
    case ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::Virtuallink_Map::VirtualLinkMappings::setMetaInformation(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean VirtualLinkMappings::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__VIRTUALLINKMAPPING:
        return m_virtualLinkMapping && m_virtualLinkMapping->size();
    case ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__METAINFORMATION:
        return m_metaInformation;

    }
    throw "Error";
}

void VirtualLinkMappings::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr VirtualLinkMappings::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Virtuallink_Map::Virtuallink_MapPackage_ptr > (::Virtuallink_Map::Virtuallink_MapPackage::_instance())->getVirtualLinkMappings();
    return _eclass;
}

