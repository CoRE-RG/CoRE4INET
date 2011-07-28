// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/IncomingImpl.cpp
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

#include "Incoming.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/FrameRelayDescriptor.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/Outgoing.hpp>
#include <System_Specification/Port.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(IncomingImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void Incoming::_initialize()
{
    // Supertypes
    ::Device_Specification::FrameRelayDescriptor::_initialize();

    // Rerefences
    for (size_t i = 0; i < m_outgoing->size(); i++)
    {
        (*m_outgoing)[i]->_initialize();
        (*m_outgoing)[i]->_setEContainer(
                this,
                ::Device_Specification::Device_SpecificationPackage::_instance()->getIncoming__outgoing());
    }

    /*PROTECTED REGION ID(IncomingImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject Incoming::eGet(::ecore::EInt _featureID,
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

    }
    throw "Error";
}

void Incoming::eSet(::ecore::EInt _featureID,
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

    }
    throw "Error";
}

::ecore::EBoolean Incoming::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Device_Specification::Device_SpecificationPackage::FRAMERELAYDESCRIPTOR__BUFFERDEPTH:
        /*PROTECTED REGION ID(IncomingeIsSet__Incomingm_bufferDepth) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_bufferDepth != 0;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__OUTGOING:
        return m_outgoing && m_outgoing->size();
    case ::Device_Specification::Device_SpecificationPackage::INCOMING__REFINPORT:
        return m_refInPort && m_refInPort->size();

    }
    throw "Error";
}

void Incoming::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr Incoming::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getIncoming();
    return _eclass;
}

