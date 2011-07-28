// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Network_Configuration/NetworkConfigImpl.cpp
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

#include "NetworkConfig.hpp"
#include <Network_Configuration/Network_ConfigurationPackage.hpp>
#include <System_Specification/ModelElement.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/Units.hpp>
#include <Network_Configuration/Synchronization.hpp>
#include <Network_Configuration/DeviceReferringElement.hpp>
#include <System_Specification/SystemSpecification.hpp>
#include <Device_Target_Mapping/Mappings.hpp>
#include <Protocol_Definition/Protocol.hpp>
#include <Network_Configuration/Periods.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EStructuralFeature.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EObject.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Network_Configuration;

/*PROTECTED REGION ID(NetworkConfigImpl.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

void NetworkConfig::_initialize()
{
    // Supertypes
    ::System_Specification::ModelElement::_initialize();

    // Rerefences
    if (m_metaInformation)
    {
        m_metaInformation->_initialize();
        m_metaInformation->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__metaInformation());
    }
    if (m_units)
    {
        m_units->_initialize();
        m_units->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__units());
    }
    if (m_synchronization)
    {
        m_synchronization->_initialize();
        m_synchronization->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__synchronization());
    }
    for (size_t i = 0; i < m_deviceReferringElement->size(); i++)
    {
        (*m_deviceReferringElement)[i]->_initialize();
        (*m_deviceReferringElement)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__deviceReferringElement());
    }
    for (size_t i = 0; i < m_periods->size(); i++)
    {
        (*m_periods)[i]->_initialize();
        (*m_periods)[i]->_setEContainer(
                this,
                ::Network_Configuration::Network_ConfigurationPackage::_instance()->getNetworkConfig__periods());
    }

    /*PROTECTED REGION ID(NetworkConfigImpl__initialize) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

// Operations


// EObject
::ecore::EJavaObject NetworkConfig::eGet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__METAINFORMATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_metaInformation);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__UNITS:
    {
        _any = static_cast< ::ecore::EObject* > (m_units);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__SYNCHRONIZATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_synchronization);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__DEVICEREFERRINGELEMENT:
    {
        _any = m_deviceReferringElement->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFSYSTEMSPECIFICATION:
    {
        _any = static_cast< ::ecore::EObject* > (m_refSystemSpecification);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFMAPPINGS:
    {
        _any = static_cast< ::ecore::EObject* > (m_refMappings);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFPROTOCOL:
    {
        _any = static_cast< ::ecore::EObject* > (m_refProtocol);
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__PERIODS:
    {
        _any = m_periods->asEListOf< ::ecore::EObject > ();
    }
        return _any;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFVIRTUALLINKMAPPING:
    {
        _any = static_cast< ::ecore::EObject* > (m_refVirtualLinkMapping);
    }
        return _any;

    }
    throw "Error";
}

void NetworkConfig::eSet(::ecore::EInt _featureID,
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
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__METAINFORMATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::MetaInformation_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::MetaInformation_ptr > (_t0);
        ::Network_Configuration::NetworkConfig::setMetaInformation(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__UNITS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::Units_ptr _t1 =
                dynamic_cast< ::System_Specification::Units_ptr > (_t0);
        ::Network_Configuration::NetworkConfig::setUnits(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__SYNCHRONIZATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Network_Configuration::Synchronization_ptr
                _t1 =
                        dynamic_cast< ::Network_Configuration::Synchronization_ptr > (_t0);
        ::Network_Configuration::NetworkConfig::setSynchronization(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__DEVICEREFERRINGELEMENT:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::NetworkConfig::getDeviceReferringElement().clear();
        ::Network_Configuration::NetworkConfig::getDeviceReferringElement().insert_all(
                *_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFSYSTEMSPECIFICATION:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::System_Specification::SystemSpecification_ptr
                _t1 =
                        dynamic_cast< ::System_Specification::SystemSpecification_ptr > (_t0);
        ::Network_Configuration::NetworkConfig::setRefSystemSpecification(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFMAPPINGS:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Device_Target_Mapping::Mappings_ptr _t1 =
                dynamic_cast< ::Device_Target_Mapping::Mappings_ptr > (_t0);
        ::Network_Configuration::NetworkConfig::setRefMappings(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFPROTOCOL:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Protocol_Definition::Protocol_ptr _t1 =
                dynamic_cast< ::Protocol_Definition::Protocol_ptr > (_t0);
        ::Network_Configuration::NetworkConfig::setRefProtocol(_t1);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__PERIODS:
    {
        ::ecorecpp::mapping::EList_ptr _t0 =
                ::ecorecpp::mapping::any::any_cast<
                        ::ecorecpp::mapping::EList_ptr >(_newValue);
        ::Network_Configuration::NetworkConfig::getPeriods().clear();
        ::Network_Configuration::NetworkConfig::getPeriods().insert_all(*_t0);
    }
        return;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFVIRTUALLINKMAPPING:
    {
        ::ecore::EObject_ptr _t0 = ::ecorecpp::mapping::any::any_cast<
                ::ecore::EObject_ptr >(_newValue);
        ::Virtuallink_Map::VirtualLinkMapping_ptr _t1 =
                dynamic_cast< ::Virtuallink_Map::VirtualLinkMapping_ptr > (_t0);
        ::Network_Configuration::NetworkConfig::setRefVirtualLinkMapping(_t1);
    }
        return;

    }
    throw "Error";
}

::ecore::EBoolean NetworkConfig::eIsSet(::ecore::EInt _featureID)
{
    switch (_featureID)
    {
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__EANNOTATIONS:
        return m_eAnnotations && m_eAnnotations->size();
    case ::System_Specification::System_SpecificationPackage::MODELELEMENT__SIGNATURE:
        return ::ecorecpp::mapping::set_traits< ::ecore::EString >::is_set(
                m_signature);
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__METAINFORMATION:
        return m_metaInformation;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__UNITS:
        return m_units;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__SYNCHRONIZATION:
        return m_synchronization;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__DEVICEREFERRINGELEMENT:
        return m_deviceReferringElement && m_deviceReferringElement->size();
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFSYSTEMSPECIFICATION:
        return m_refSystemSpecification;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFMAPPINGS:
        return m_refMappings;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFPROTOCOL:
        return m_refProtocol;
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__PERIODS:
        return m_periods && m_periods->size();
    case ::Network_Configuration::Network_ConfigurationPackage::NETWORKCONFIG__REFVIRTUALLINKMAPPING:
        return m_refVirtualLinkMapping;

    }
    throw "Error";
}

void NetworkConfig::eUnset(::ecore::EInt _featureID)
{
    switch (_featureID)
    {

    }
    throw "Error";
}

::ecore::EClass_ptr NetworkConfig::_eClass()
{
    static ::ecore::EClass_ptr
            _eclass =
                    dynamic_cast< ::Network_Configuration::Network_ConfigurationPackage_ptr > (::Network_Configuration::Network_ConfigurationPackage::_instance())->getNetworkConfig();
    return _eclass;
}

