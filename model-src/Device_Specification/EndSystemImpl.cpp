// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Device_Specification/EndSystemImpl.cpp
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

#include "EndSystem.hpp"
#include <Device_Specification/Device_SpecificationPackage.hpp>
#include <Device_Specification/DeviceSpecification.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <Device_Specification/BagAccounts.hpp>
#include <Device_Specification/VirtualLinkSchedules.hpp>
#include <Device_Specification/BestEffortRouting.hpp>
#include <Device_Specification/FlowControl.hpp>
#include <Device_Specification/Periods.hpp>
#include <Device_Target_Mapping/DeviceMapping.hpp>
#include <Device_Specification/EndSystemConfig.hpp>
#include <Device_Specification/TriggerSchedules.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Device_Specification;

/*PROTECTED REGION ID(EndSystemImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void EndSystem::_initialize()
{
    // Supertypes
    ::Device_Specification::DeviceSpecification::_initialize();

    // Rerefences
    if (m_config)
    {
        m_config->_initialize();
        m_config->_setEContainer(
                this,
                ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystem__config());
    }
    if (m_triggerSchedules)
    {
        m_triggerSchedules->_initialize();
        m_triggerSchedules->_setEContainer(
                this,
                ::Device_Specification::Device_SpecificationPackage::_instance()->getEndSystem__triggerSchedules());
    }

    /*PROTECTED REGION ID(EndSystemImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject EndSystem::eGet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__UNITS:
    {
        _any = static_cast< ::ecore::EObject* > (m_units);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BAGACCOUNTS:
    {
        _any = static_cast< ::ecore::EObject* > (m_bagAccounts);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__VLSCHEDULES:
    {
        _any = static_cast< ::ecore::EObject* > (m_vlSchedules);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BESTEFFORTROUTING:
    {
        _any = static_cast< ::ecore::EObject* > (m_bestEffortRouting);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__FLOWCONTROL:
    {
        _any = static_cast< ::ecore::EObject* > (m_flowControl);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__PERIODS:
    {
        _any = static_cast< ::ecore::EObject* > (m_periods);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__REFDEVICEMAPPING:
    {
        _any = static_cast< ::ecore::EObject* > (m_refDeviceMapping);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__CONFIG:
    {
        _any = static_cast< ::ecore::EObject* > (m_config);
    }
        return _any;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__TRIGGERSCHEDULES:
    {
        _any = static_cast< ::ecore::EObject* > (m_triggerSchedules);
    }
        return _any;

    }
    throw "Error";
}

void EndSystem::eSet(::ecore::EInt _featureID,
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
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setMetaInformation(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__UNITS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Units_ptr _t1 =
                dynamic_cast< ::System_Specification::Units_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setUnits(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BAGACCOUNTS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::BagAccounts_ptr _t1 =
                dynamic_cast< ::Device_Specification::BagAccounts_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setBagAccounts(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__VLSCHEDULES:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::VirtualLinkSchedules_ptr
                _t1 =
                        dynamic_cast< ::Device_Specification::VirtualLinkSchedules_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setVlSchedules(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BESTEFFORTROUTING:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::BestEffortRouting_ptr
                _t1 =
                        dynamic_cast< ::Device_Specification::BestEffortRouting_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setBestEffortRouting(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__FLOWCONTROL:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::FlowControl_ptr _t1 =
                dynamic_cast< ::Device_Specification::FlowControl_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setFlowControl(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__PERIODS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::Periods_ptr _t1 =
                dynamic_cast< ::Device_Specification::Periods_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setPeriods(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__REFDEVICEMAPPING:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Target_Mapping::DeviceMapping_ptr
                _t1 =
                        dynamic_cast< ::Device_Target_Mapping::DeviceMapping_ptr > (_t0);
        ::Device_Specification::DeviceSpecification::setRefDeviceMapping(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__CONFIG:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::EndSystemConfig_ptr
                _t1 =
                        dynamic_cast< ::Device_Specification::EndSystemConfig_ptr > (_t0);
        ::Device_Specification::EndSystem::setConfig(_t1);
    }
        return;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__TRIGGERSCHEDULES:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Specification::TriggerSchedules_ptr
                _t1 =
                        dynamic_cast< ::Device_Specification::TriggerSchedules_ptr > (_t0);
        ::Device_Specification::EndSystem::setTriggerSchedules(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean EndSystem::eIsSet(::ecore::EInt _featureID)
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
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__METAINFORMATION:
        return m_metaInformation;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__UNITS:
        return m_units;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BAGACCOUNTS:
        return m_bagAccounts;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__VLSCHEDULES:
        return m_vlSchedules;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__BESTEFFORTROUTING:
        return m_bestEffortRouting;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__FLOWCONTROL:
        return m_flowControl;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__PERIODS:
        return m_periods;
    case ::Device_Specification::Device_SpecificationPackage::DEVICESPECIFICATION__REFDEVICEMAPPING:
        return m_refDeviceMapping;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__CONFIG:
        return m_config;
    case ::Device_Specification::Device_SpecificationPackage::ENDSYSTEM__TRIGGERSCHEDULES:
        return m_triggerSchedules;

    }
    throw "Error";
}

void EndSystem::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr EndSystem::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Device_Specification::Device_SpecificationPackage_ptr > (::Device_Specification::Device_SpecificationPackage::_instance())->getEndSystem();
    return _eclass;
}

