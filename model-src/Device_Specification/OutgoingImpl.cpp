// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/OutgoingImpl.cpp
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

#include "Outgoing.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/FrameRelayDescriptor.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(OutgoingImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void Outgoing::_initialize()
{
    // Supertypes
    ::Device_Specification::FrameRelayDescriptor::_initialize();

    // Rerefences

    /*PROTECTED REGION ID(OutgoingImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject Outgoing::eGet(::ecore::EInt _featureID,
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

    }
    throw "Error";
}

void Outgoing::eSet(::ecore::EInt _featureID,
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

    }
    throw "Error";
}

::ecore::EBoolean Outgoing::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Specification::Device_SpecificationPackage::FRAMERELAYDESCRIPTOR__BUFFERDEPTH:
        /*PROTECTED REGION ID(OutgoingeIsSet__Outgoingm_bufferDepth) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_bufferDepth != 0;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__APPENDSEQUENCENUMBER:
        /*PROTECTED REGION ID(OutgoingeIsSet__Outgoingm_appendSequenceNumber) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_appendSequenceNumber != false;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::OUTGOING__REFOUTPORT:
        return m_refOutPort && m_refOutPort->size();

    }
    throw "Error";
}

void Outgoing::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr Outgoing::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getOutgoing();
    return _eclass;
}

