// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/IntegrityConfigBaseImpl.cpp
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

#include "IntegrityConfigBase.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <System_Specification/NamedElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(IntegrityConfigBaseImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void IntegrityConfigBase::_initialize()
{
    // Supertypes
    ::System_Specification::NamedElement::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(IntegrityConfigBaseImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject IntegrityConfigBase::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_integrateToSyncThreshold);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numUnstableCycles);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_numStableCycles);
    }
        return _any;

    }
    throw "Error";
}

void IntegrityConfigBase::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_integrateToSyncThreshold);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numUnstableCycles);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMSTABLECYCLES:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_numStableCycles);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean IntegrityConfigBase::eIsSet(::ecore::EInt _featureID)
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
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__INTEGRATETOSYNCTHRESHOLD:
        /*PROTECTED REGION ID(IntegrityConfigBaseeIsSet__IntegrityConfigBasem_integrateToSyncThreshold) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_integrateToSyncThreshold != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMUNSTABLECYCLES:
        /*PROTECTED REGION ID(IntegrityConfigBaseeIsSet__IntegrityConfigBasem_numUnstableCycles) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numUnstableCycles != 0;
        /*PROTECTED REGION END*/
    case ::Network_Configuration::Network_ConfigurationPackage::INTEGRITYCONFIGBASE__NUMSTABLECYCLES:
        /*PROTECTED REGION ID(IntegrityConfigBaseeIsSet__IntegrityConfigBasem_numStableCycles) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_numStableCycles != 0;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void IntegrityConfigBase::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr IntegrityConfigBase::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getIntegrityConfigBase();
    return _eclass;
}

