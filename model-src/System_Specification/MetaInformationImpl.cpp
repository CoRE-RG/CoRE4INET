// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/MetaInformationImpl.cpp
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

#include "MetaInformation.hpp"
#include <System_Specification/System_SpecificationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::System_Specification;

/*PROTECTED REGION ID(MetaInformationImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void MetaInformation::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(MetaInformationImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject MetaInformation::eGet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__AUTHOR:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_author);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONDATE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EDate >::toAny(_any,
                m_creationDate);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOL:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_creationTool);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOLVERSION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_creationToolVersion);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__LICENSEE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_licensee);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any,
                m_description);
    }
        return _any;

    }
    throw "Error";
}

void MetaInformation::eSet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__AUTHOR:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_author);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONDATE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EDate >::fromAny(_newValue,
                m_creationDate);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOL:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_creationTool);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOLVERSION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_creationToolVersion);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__LICENSEE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_licensee);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__DESCRIPTION:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_description);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean MetaInformation::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__AUTHOR:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_author);
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONDATE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EDate >::is_set(
                m_creationDate);
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOL:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_creationTool);
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__CREATIONTOOLVERSION:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_creationToolVersion);
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__LICENSEE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_licensee);
    case ::System_Specification::System_SpecificationPackage::METAINFORMATION__DESCRIPTION:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_description);

    }
    throw "Error";
}

void MetaInformation::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr MetaInformation::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation();
    return _eclass;
}

