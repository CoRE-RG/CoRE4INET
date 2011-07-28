// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/DataVirtualLinkImpl.cpp
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

#include "DataVirtualLink.hpp"
#include <System_Specification/System_SpecificationPackage.hpp>
#include <System_Specification/VirtualLink.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/FrameRoute.hpp>
#include <System_Specification/Device.hpp>
#include <System_Specification/Alias.hpp>
#include <System_Specification/Period.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::System_Specification;

/*PROTECTED REGION ID(DataVirtualLinkImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void DataVirtualLink::_initialize()
{
    // Supertypes
    ::System_Specification::VirtualLink::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(DataVirtualLinkImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject DataVirtualLink::eGet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__DESTMACADDRESSCF:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::toAny(
                _any, m_destMacAddressCF);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__VLID:
    {
        ::ecorecpp::mapping::any_traits<
                ::System_Specification::VirtualLinkIDType >::toAny(_any, m_vlid);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__JITTER:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_jitter);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__MAXE2ELATENCY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_maxE2eLatency);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__FRAMEROUTE:
    {
        _any = m_frameRoute->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFSENDER:
    {
        _any = static_cast< ::ecore::EObject* > (m_refSender);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFRECEIVER:
    {
        _any = m_refReceiver->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__ALIAS:
    {
        _any = m_alias->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__SEMANTIC:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::SemanticEnum >::toAny(
                _any, m_semantic);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__MAXLENGTH:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_maxLength);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__REFPERIOD:
    {
        _any = static_cast< ::ecore::EObject* > (m_refPeriod);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__TRANSPARENTCLOCKENABLE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_transparentClockEnable);
    }
        return _any;

    }
    throw "Error";
}

void DataVirtualLink::eSet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__DESTMACADDRESSCF:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::fromAny(
                _newValue, m_destMacAddressCF);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__VLID:
    {
        ::ecorecpp::mapping::any_traits<
                ::System_Specification::VirtualLinkIDType >::fromAny(_newValue,
                m_vlid);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__JITTER:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_jitter);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__MAXE2ELATENCY:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_maxE2eLatency);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__FRAMEROUTE:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::System_Specification::VirtualLink::getFrameRoute().clear();
        ::System_Specification::VirtualLink::getFrameRoute().insert_all(*_t0);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFSENDER:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Device_ptr _t1 =
                dynamic_cast< ::System_Specification::Device_ptr > (_t0);
        ::System_Specification::VirtualLink::setRefSender(_t1);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFRECEIVER:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::System_Specification::VirtualLink::getRefReceiver().clear();
        ::System_Specification::VirtualLink::getRefReceiver().insert_all(*_t0);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__ALIAS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::System_Specification::VirtualLink::getAlias().clear();
        ::System_Specification::VirtualLink::getAlias().insert_all(*_t0);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__SEMANTIC:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::SemanticEnum >::fromAny(
                _newValue, m_semantic);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__MAXLENGTH:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_maxLength);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__REFPERIOD:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Period_ptr _t1 =
                dynamic_cast< ::System_Specification::Period_ptr > (_t0);
        ::System_Specification::DataVirtualLink::setRefPeriod(_t1);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__TRANSPARENTCLOCKENABLE:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_transparentClockEnable);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean DataVirtualLink::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__DESTMACADDRESSCF:
        /*PROTECTED REGION ID(DataVirtualLinkeIsSet__DataVirtualLinkm_destMacAddressCF) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__VLID:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::VirtualLinkIDType >::is_set(m_vlid);
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__JITTER:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_jitter);
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__MAXE2ELATENCY:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_maxE2eLatency);
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__FRAMEROUTE:
        return m_frameRoute && m_frameRoute->size();
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFSENDER:
        return m_refSender;
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__REFRECEIVER:
        return m_refReceiver && m_refReceiver->size();
    case ::System_Specification::System_SpecificationPackage::VIRTUALLINK__ALIAS:
        return m_alias && m_alias->size();
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__SEMANTIC:
        /*PROTECTED REGION ID(DataVirtualLinkeIsSet__DataVirtualLinkm_semantic) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__MAXLENGTH:
        /*PROTECTED REGION ID(DataVirtualLinkeIsSet__DataVirtualLinkm_maxLength) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_maxLength != 1500;
        /*PROTECTED REGION END*/
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__REFPERIOD:
        return m_refPeriod;
    case ::System_Specification::System_SpecificationPackage::DATAVIRTUALLINK__TRANSPARENTCLOCKENABLE:
        /*PROTECTED REGION ID(DataVirtualLinkeIsSet__DataVirtualLinkm_transparentClockEnable) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_transparentClockEnable != false;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void DataVirtualLink::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr DataVirtualLink::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (::System_Specification::System_SpecificationPackage::_instance())->getDataVirtualLink();
    return _eclass;
}

