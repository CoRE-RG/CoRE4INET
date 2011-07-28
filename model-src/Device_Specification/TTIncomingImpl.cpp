// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/TTIncomingImpl.cpp
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

#include "TTIncoming.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/CTIncoming.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/Outgoing.hpp>
#include <System_Specification/Port.hpp>
#include <Device_Specification/IntegrityCheck.hpp>
#include <System_Specification/Period.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(TTIncomingImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void TTIncoming::_initialize()
{
    // Supertypes
    ::Device_Specification::CTIncoming::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(TTIncomingImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject TTIncoming::eGet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::FRAMERELAYDESCRIPTOR__BUFFERDEPTH:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::toAny(_any,
                m_bufferDepth);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__OUTGOING:
    {
        _any = m_outgoing->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__REFINPORT:
    {
        _any = m_refInPort->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REMOVESEQUENCENUMBER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_removeSequenceNumber);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REDUNDANCYFUNCTION:
    {
        _any = static_cast< ::ecore::EObject* > (m_redundancyFunction);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWSTART:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_receiveWindowStart);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWEND:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_receiveWindowEnd);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__PERMANENCEPIT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_permanencePit);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__REFPERIOD:
    {
        _any = static_cast< ::ecore::EObject* > (m_refPeriod);
    }
        return _any;

    }
    throw "Error";
}

void TTIncoming::eSet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::FRAMERELAYDESCRIPTOR__BUFFERDEPTH:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EInt >::fromAny(_newValue,
                m_bufferDepth);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__OUTGOING:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Specification::Incoming::getOutgoing().clear();
        ::Device_Specification::Incoming::getOutgoing().insert_all(*_t0);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__REFINPORT:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Specification::Incoming::getRefInPort().clear();
        ::Device_Specification::Incoming::getRefInPort().insert_all(*_t0);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REMOVESEQUENCENUMBER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_removeSequenceNumber);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REDUNDANCYFUNCTION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::IntegrityCheck_ptr
                _t1 =
                        dynamic_cast< ::Device_Specification::IntegrityCheck_ptr > (_t0);
        ::Device_Specification::CTIncoming::setRedundancyFunction(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWSTART:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_receiveWindowStart);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWEND:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_receiveWindowEnd);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__PERMANENCEPIT:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_permanencePit);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__REFPERIOD:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Period_ptr _t1 =
                dynamic_cast< ::System_Specification::Period_ptr > (_t0);
        ::Device_Specification::TTIncoming::setRefPeriod(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean TTIncoming::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Specification::Device_SpecificationPackage::FRAMERELAYDESCRIPTOR__BUFFERDEPTH:
        /*PROTECTED REGION ID(TTIncomingeIsSet__TTIncomingm_bufferDepth) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_bufferDepth != 0;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__OUTGOING:
        return m_outgoing && m_outgoing->size();
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__REFINPORT:
        return m_refInPort && m_refInPort->size();
    case ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REMOVESEQUENCENUMBER:
        /*PROTECTED REGION ID(TTIncomingeIsSet__TTIncomingm_removeSequenceNumber) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_removeSequenceNumber != false;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::CTINCOMING__REDUNDANCYFUNCTION:
        return m_redundancyFunction;
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWSTART:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_receiveWindowStart);
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__RECEIVEWINDOWEND:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_receiveWindowEnd);
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__PERMANENCEPIT:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_permanencePit);
    case ::Device_Specification::Device_SpecificationPackage::TTINCOMING__REFPERIOD:
        return m_refPeriod;

    }
    throw "Error";
}

void TTIncoming::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr TTIncoming::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getTTIncoming();
    return _eclass;
}

