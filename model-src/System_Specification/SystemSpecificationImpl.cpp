// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * System_Specification/SystemSpecificationImpl.cpp
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

#include "SystemSpecification.hpp"
#include <System_Specification/System_SpecificationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <System_Specification/VirtualLinks.hpp>
#include <System_Specification/Devices.hpp>
#include <System_Specification/Links.hpp>
#include <System_Specification/Periods.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::System_Specification;

/*PROTECTED REGION ID(SystemSpecificationImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void SystemSpecification::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    if (m_metaInformation)
    {
        m_metaInformation->_initialize();
        m_metaInformation->_setEContainer(
                this,
                ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__metaInformation());
    }
    if (m_units)
    {
        m_units->_initialize();
        m_units->_setEContainer(
                this,
                ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__units());
    }
    if (m_virtualLinks)
    {
        m_virtualLinks->_initialize();
        m_virtualLinks->_setEContainer(
                this,
                ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__virtualLinks());
    }
    if (m_devices)
    {
        m_devices->_initialize();
        m_devices->_setEContainer(
                this,
                ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__devices());
    }
    if (m_links)
    {
        m_links->_initialize();
        m_links->_setEContainer(
                this,
                ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__links());
    }
    if (m_periods)
    {
        m_periods->_initialize();
        m_periods->_setEContainer(
                this,
                ::System_Specification::System_SpecificationPackage::_instance()->getSystemSpecification__periods());
    }

    /*PROTECTED REGION ID(SystemSpecificationImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject SystemSpecification::eGet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__UNITS:
    {
        _any = static_cast< ::ecore::EObject* > (m_units);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__VIRTUALLINKS:
    {
        _any = static_cast< ::ecore::EObject* > (m_virtualLinks);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__DEVICES:
    {
        _any = static_cast< ::ecore::EObject* > (m_devices);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__LINKS:
    {
        _any = static_cast< ::ecore::EObject* > (m_links);
    }
        return _any;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__PERIODS:
    {
        _any = static_cast< ::ecore::EObject* > (m_periods);
    }
        return _any;

    }
    throw "Error";
}

void SystemSpecification::eSet(::ecore::EInt _featureID,
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
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::System_Specification::SystemSpecification::setMetaInformation(_t1);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__UNITS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Units_ptr _t1 =
                dynamic_cast< ::System_Specification::Units_ptr > (_t0);
        ::System_Specification::SystemSpecification::setUnits(_t1);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__VIRTUALLINKS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::VirtualLinks_ptr _t1 =
                dynamic_cast< ::System_Specification::VirtualLinks_ptr > (_t0);
        ::System_Specification::SystemSpecification::setVirtualLinks(_t1);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__DEVICES:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Devices_ptr _t1 =
                dynamic_cast< ::System_Specification::Devices_ptr > (_t0);
        ::System_Specification::SystemSpecification::setDevices(_t1);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__LINKS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Links_ptr _t1 =
                dynamic_cast< ::System_Specification::Links_ptr > (_t0);
        ::System_Specification::SystemSpecification::setLinks(_t1);
    }
        return;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__PERIODS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Periods_ptr _t1 =
                dynamic_cast< ::System_Specification::Periods_ptr > (_t0);
        ::System_Specification::SystemSpecification::setPeriods(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean SystemSpecification::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__METAINFORMATION:
        return m_metaInformation;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__UNITS:
        return m_units;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__VIRTUALLINKS:
        return m_virtualLinks;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__DEVICES:
        return m_devices;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__LINKS:
        return m_links;
    case ::System_Specification::System_SpecificationPackage::SYSTEMSPECIFICATION__PERIODS:
        return m_periods;

    }
    throw "Error";
}

void SystemSpecification::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr SystemSpecification::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::System_Specification::System_SpecificationPackage_ptr > (::System_Specification::System_SpecificationPackage::_instance())->getSystemSpecification();
    return _eclass;
}

