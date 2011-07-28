// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Targets/MacAcceptanceEntryImpl.cpp
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

#include "MacAcceptanceEntry.hpp"
#include <Device_Targets/Device_TargetsPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Targets/AccessControl.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Targets;

/*PROTECTED REGION ID(MacAcceptanceEntryImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void MacAcceptanceEntry::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_accessControl->size(); i++)
    {
        (*m_accessControl)[i]->_initialize();
        (*m_accessControl)[i]->_setEContainer(
                this,
                ::Device_Targets::Device_TargetsPackage::_instance()->getMacAcceptanceEntry__accessControl());
    }

    /*PROTECTED REGION ID(MacAcceptanceEntryImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject MacAcceptanceEntry::eGet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCEPTANCEMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::toAny(
                _any, m_acceptanceMacAddress);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ADDRESSTYPE:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Targets::addressTypeEnum >::toAny(
                _any, m_addressType);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCESSCONTROL:
    {
        _any = m_accessControl->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__UNLOCKENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_unlockEnabled);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESETENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_resetEnabled);
    }
        return _any;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESPONSEDESTMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::toAny(
                _any, m_responseDestMacAddress);
    }
        return _any;

    }
    throw "Error";
}

void MacAcceptanceEntry::eSet(::ecore::EInt _featureID,
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
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCEPTANCEMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::fromAny(
                _newValue, m_acceptanceMacAddress);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ADDRESSTYPE:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Targets::addressTypeEnum >::fromAny(
                _newValue, m_addressType);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCESSCONTROL:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Targets::MacAcceptanceEntry::getAccessControl().clear();
        ::Device_Targets::MacAcceptanceEntry::getAccessControl().insert_all(
                *_t0);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__UNLOCKENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_unlockEnabled);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESETENABLED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_resetEnabled);
    }
        return;
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESPONSEDESTMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::fromAny(
                _newValue, m_responseDestMacAddress);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean MacAcceptanceEntry::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCEPTANCEMACADDRESS:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::MacAddressType >::is_set(
                m_acceptanceMacAddress);
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ADDRESSTYPE:
        return ::ecorecpp::mapping::set_traits<
                ::Device_Targets::addressTypeEnum >::is_set(m_addressType);
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__ACCESSCONTROL:
        return m_accessControl && m_accessControl->size();
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__UNLOCKENABLED:
        return ::ecorecpp::mapping::set_traits< ::ecore::EBoolean >::is_set(
                m_unlockEnabled);
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESETENABLED:
        return ::ecorecpp::mapping::set_traits< ::ecore::EBoolean >::is_set(
                m_resetEnabled);
    case ::Device_Targets::Device_TargetsPackage::MACACCEPTANCEENTRY__RESPONSEDESTMACADDRESS:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::MacAddressType >::is_set(
                m_responseDestMacAddress);

    }
    throw "Error";
}

void MacAcceptanceEntry::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr MacAcceptanceEntry::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Targets::Device_TargetsPackage_ptr > (::Device_Targets::Device_TargetsPackage::_instance())->getMacAcceptanceEntry();
    return _eclass;
}

