// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/EndSystemConfigImpl.cpp
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

#include "EndSystemConfig.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/DeviceConfig.hpp>
#include <ecore/EAnnotation.hpp>
#include <Device_Specification/ExternalClockSynchronization.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(EndSystemConfigImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void EndSystemConfig::_initialize()
{
    // Supertypes
    ::Device_Specification::DeviceConfig::_initialize();

    // Rerefences
    if (m_externalClockSynchronization)
    {
        m_externalClockSynchronization->_initialize();
        m_externalClockSynchronization->_setEContainer(
                this,
                ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystemConfig__externalClockSynchronization());
    }

    /*PROTECTED REGION ID(EndSystemConfigImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject EndSystemConfig::eGet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__TSSOURCE:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Specification::TimeSourceEnum >::toAny(
                _any, m_tsSource);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALCLOCKSYNCHRONIZATION:
    {
        _any
                = static_cast< ::ecore::EObject* > (m_externalClockSynchronization);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__SOURCEMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::toAny(
                _any, m_sourceMacAddress);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__DESTMACADDRESSCF:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::toAny(
                _any, m_destMacAddressCF);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALSYNCACKREQUIRED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::toAny(_any,
                m_externalSyncAckRequired);
    }
        return _any;

    }
    throw "Error";
}

void EndSystemConfig::eSet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__TSSOURCE:
    {
        ::ecorecpp::mapping::any_traits< ::Device_Specification::TimeSourceEnum >::fromAny(
                _newValue, m_tsSource);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALCLOCKSYNCHRONIZATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::ExternalClockSynchronization_ptr
                _t1 =
                        dynamic_cast< ::Device_Specification::ExternalClockSynchronization_ptr > (_t0);
        ::Device_Specification::EndSystemConfig::setExternalClockSynchronization(
                _t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__SOURCEMACADDRESS:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::MacAddressType >::fromAny(
                _newValue, m_sourceMacAddress);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__DESTMACADDRESSCF:
    {
        ::ecorecpp::mapping::any_traits< ::System_Specification::CTMarkerType >::fromAny(
                _newValue, m_destMacAddressCF);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALSYNCACKREQUIRED:
    {
        ::ecorecpp::mapping::any_traits< ::ecore::EBoolean >::fromAny(
                _newValue, m_externalSyncAckRequired);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean EndSystemConfig::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::ecore::EcorePackage::EMODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::ecore::EcorePackage::ENAMEDELEMENT__NAME:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_name);
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMARKER:
        /*PROTECTED REGION ID(EndSystemConfigeIsSet__EndSystemConfigm_ctMarker) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::DEVICECONFIG__CTMASK:
        /*PROTECTED REGION ID(EndSystemConfigeIsSet__EndSystemConfigm_ctMask) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__TSSOURCE:
        /*PROTECTED REGION ID(EndSystemConfigeIsSet__EndSystemConfigm_tsSource) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALCLOCKSYNCHRONIZATION:
        return m_externalClockSynchronization;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__SOURCEMACADDRESS:
        /*PROTECTED REGION ID(EndSystemConfigeIsSet__EndSystemConfigm_sourceMacAddress) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__DESTMACADDRESSCF:
        /*PROTECTED REGION ID(EndSystemConfigeIsSet__EndSystemConfigm_destMacAddressCF) ENABLED START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return true;
        /*PROTECTED REGION END*/
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEMCONFIG__EXTERNALSYNCACKREQUIRED:
        /*PROTECTED REGION ID(EndSystemConfigeIsSet__EndSystemConfigm_externalSyncAckRequired) START*/
        // Please, enable the protected region if you changed it.
        // To do this, add the keyword ENABLED before START.
        return m_externalSyncAckRequired != false;
        /*PROTECTED REGION END*/

    }
    throw "Error";
}

void EndSystemConfig::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr EndSystemConfig::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getEndSystemConfig();
    return _eclass;
}

