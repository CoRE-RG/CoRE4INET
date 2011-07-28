// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/SwitchConfigImpl.cpp
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

#include "SwitchConfig.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/DeviceConfig.hpp>
#include <ecore/EAnnotation.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(SwitchConfigImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void SwitchConfig::_initialize()
{
    // Supertypes
    ::Device_Specification::DeviceConfig::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(SwitchConfigImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject SwitchConfig::eGet(::ecore::EInt _featureID,
        ::ecore::EBoolean _resolve)
{
    ::ecore::EJavaObject _any;
    switch (_featureID)
    {
    case ::ecore::EcorePackage::EMODELELEMENT__EANNOTATIONS:
    {
        _any = m_eAnnotations->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::ecore::EcorePackage::ENAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::toAny(_any, m_name);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMARKER:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::toAny(
                _any, m_ctMarker);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMASK:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::toAny(
                _any, m_ctMask);
    }
        return _any;

    }
    throw "Error";
}

void SwitchConfig::eSet(::ecore::EInt _featureID,
        ::ecore::EJavaObject const& _newValue)
{
    switch (_featureID)
    {
    case ::ecore::EcorePackage::EMODELELEMENT__EANNOTATIONS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::ecore::EModelElement::getEAnnotations().clear();
        ::ecore::EModelElement::getEAnnotations().insert_all(*_t0);
    }
        return;
    case ::ecore::EcorePackage::ENAMEDELEMENT__NAME:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EString >::fromAny(_newValue,
                m_name);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMARKER:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::fromAny(
                _newValue, m_ctMarker);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMASK:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::fromAny(
                _newValue, m_ctMask);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean SwitchConfig::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::ecore::EcorePackage::EMODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::ecore::EcorePackage::ENAMEDELEMENT__NAME:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_name);
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMARKER:
        /*PROTECTED REGION ID(SwitchConfigeIsSet__SwitchConfigm_ctMarker) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMASK:
        /*PROTECTED REGION ID(SwitchConfigeIsSet__SwitchConfigm_ctMask) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void SwitchConfig::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr SwitchConfig::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getSwitchConfig();
    return _eclass;
}

