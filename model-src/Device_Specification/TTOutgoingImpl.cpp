// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/TTOutgoingImpl.cpp
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

#include "TTOutgoing.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/CTOutgoing.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Port.hpp>
#include <System_Specification/Period.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(TTOutgoingImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void TTOutgoing::_initialize()
{
    // Supertypes
    ::Device_Specification::CTOutgoing::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(TTOutgoingImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject TTOutgoing::eGet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__APPENDSEQUENCENUMBER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_appendSequenceNumber);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__REFOUTPORT:
    {
        _any = m_refOutPort->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWSTART:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_sendWindowStart);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWEND:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::toAny(
                _any, m_sendWindowEnd);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__REFPERIOD:
    {
        _any = static_cast< ::ecore::EObject* > (m_refPeriod);
    }
        return _any;

    }
    throw "Error";
}

void TTOutgoing::eSet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__APPENDSEQUENCENUMBER:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_appendSequenceNumber);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__REFOUTPORT:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Device_Specification::Outgoing::getRefOutPort().clear();
        ::Device_Specification::Outgoing::getRefOutPort().insert_all(*_t0);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWSTART:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_sendWindowStart);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWEND:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::TimeType >::fromAny(
                _newValue, m_sendWindowEnd);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__REFPERIOD:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Period_ptr _t1 =
                dynamic_cast< ::System_Specification::Period_ptr > (_t0);
        ::Device_Specification::TTOutgoing::setRefPeriod(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean TTOutgoing::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Specification::Device_SpecificationPackage::FRAMERELAYDESCRIPTOR__BUFFERDEPTH:
        /*PROTECTED REGION ID(TTOutgoingeIsSet__TTOutgoingm_bufferDepth) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_bufferDepth != 0;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__APPENDSEQUENCENUMBER:
        /*PROTECTED REGION ID(TTOutgoingeIsSet__TTOutgoingm_appendSequenceNumber) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_appendSequenceNumber != false;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__REFOUTPORT:
        return m_refOutPort && m_refOutPort->size();
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWSTART:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_sendWindowStart);
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__SENDWINDOWEND:
        return ::ecorecpp::mapping::set_traits<
                ::System_Specification::TimeType >::is_set(m_sendWindowEnd);
    case ::Device_Specification::Device_SpecificationPackage::TTOUTGOING__REFPERIOD:
        return m_refPeriod;

    }
    throw "Error";
}

void TTOutgoing::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr TTOutgoing::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getTTOutgoing();
    return _eclass;
}

