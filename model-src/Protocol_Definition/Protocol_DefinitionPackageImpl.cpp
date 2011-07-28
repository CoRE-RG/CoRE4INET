// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Protocol_Definition/Protocol_DefinitionPackageImpl.cpp
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

#include <Protocol_Definition/Protocol_DefinitionPackage.hpp>
#include <Protocol_Definition/Protocol_DefinitionFactory.hpp>
#include <ecore.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EClass.hpp>
#include <ecore/EAttribute.hpp>
#include <ecore/EReference.hpp>
#include <ecore/EOperation.hpp>
#include <ecore/EParameter.hpp>
#include <ecore/EEnum.hpp>
#include <ecore/EEnumLiteral.hpp>
#include <ecore/EDataType.hpp>
#include <ecore/EGenericType.hpp>
#include <ecore/ETypeParameter.hpp>
#include <ecore/EcorePackage.hpp>
#include <ecore/EAnnotation.hpp>

using namespace ::Protocol_Definition;

Protocol_DefinitionPackage::Protocol_DefinitionPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = Protocol_DefinitionFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // Protocols
    m_ProtocolsEClass = new ::ecore::EClass();
    m_ProtocolsEClass->setClassifierID(PROTOCOLS);
    m_ProtocolsEClass->setEPackage(this);
    getEClassifiers().push_back(m_ProtocolsEClass);
    m_Protocols__protocols = new ::ecore::EReference();
    m_Protocols__protocols->setFeatureID(
            ::Protocol_Definition::Protocol_DefinitionPackage::PROTOCOLS__PROTOCOLS);
    m_ProtocolsEClass->getEStructuralFeatures().push_back(
            m_Protocols__protocols);

    // Protocol
    m_ProtocolEClass = new ::ecore::EClass();
    m_ProtocolEClass->setClassifierID(PROTOCOL);
    m_ProtocolEClass->setEPackage(this);
    getEClassifiers().push_back(m_ProtocolEClass);
    m_Protocol__ifgBitLength = new ::ecore::EAttribute();
    m_Protocol__ifgBitLength->setFeatureID(
            ::Protocol_Definition::Protocol_DefinitionPackage::PROTOCOL__IFGBITLENGTH);
    m_ProtocolEClass->getEStructuralFeatures().push_back(
            m_Protocol__ifgBitLength);
    m_Protocol__preambleBitLength = new ::ecore::EAttribute();
    m_Protocol__preambleBitLength->setFeatureID(
            ::Protocol_Definition::Protocol_DefinitionPackage::PROTOCOL__PREAMBLEBITLENGTH);
    m_ProtocolEClass->getEStructuralFeatures().push_back(
            m_Protocol__preambleBitLength);
    m_Protocol__sfdBitLength = new ::ecore::EAttribute();
    m_Protocol__sfdBitLength->setFeatureID(
            ::Protocol_Definition::Protocol_DefinitionPackage::PROTOCOL__SFDBITLENGTH);
    m_ProtocolEClass->getEStructuralFeatures().push_back(
            m_Protocol__sfdBitLength);
    m_Protocol__maximumTransmissionUnit = new ::ecore::EAttribute();
    m_Protocol__maximumTransmissionUnit->setFeatureID(
            ::Protocol_Definition::Protocol_DefinitionPackage::PROTOCOL__MAXIMUMTRANSMISSIONUNIT);
    m_ProtocolEClass->getEStructuralFeatures().push_back(
            m_Protocol__maximumTransmissionUnit);
    m_Protocol__description = new ::ecore::EAttribute();
    m_Protocol__description->setFeatureID(
            ::Protocol_Definition::Protocol_DefinitionPackage::PROTOCOL__DESCRIPTION);
    m_ProtocolEClass->getEStructuralFeatures().push_back(
            m_Protocol__description);

    // Create enums


    // Create data types


    // Initialize package
    setName("Protocol_Definition");
    setNsPrefix("prt");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/Protocol_Definition_V1");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_ProtocolsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_ProtocolEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // Protocols
    m_ProtocolsEClass->setName("Protocols");
    m_ProtocolsEClass->setAbstract(false);
    m_ProtocolsEClass->setInterface(false);
    m_Protocols__protocols->setEType(m_ProtocolEClass);
    m_Protocols__protocols->setName("protocols");
    m_Protocols__protocols->setDefaultValueLiteral("");
    m_Protocols__protocols->setLowerBound(0);
    m_Protocols__protocols->setUpperBound(-1);
    m_Protocols__protocols->setTransient(false);
    m_Protocols__protocols->setVolatile(false);
    m_Protocols__protocols->setChangeable(true);
    m_Protocols__protocols->setContainment(true);
    m_Protocols__protocols->setResolveProxies(true);
    m_Protocols__protocols->setUnique(true);
    m_Protocols__protocols->setDerived(false);
    m_Protocols__protocols->setOrdered(true);
    // Protocol
    m_ProtocolEClass->setName("Protocol");
    m_ProtocolEClass->setAbstract(false);
    m_ProtocolEClass->setInterface(false);
    m_Protocol__ifgBitLength->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Protocol__ifgBitLength->setName("ifgBitLength");
    m_Protocol__ifgBitLength->setDefaultValueLiteral("96");
    m_Protocol__ifgBitLength->setLowerBound(0);
    m_Protocol__ifgBitLength->setUpperBound(1);
    m_Protocol__ifgBitLength->setTransient(false);
    m_Protocol__ifgBitLength->setVolatile(false);
    m_Protocol__ifgBitLength->setChangeable(true);
    m_Protocol__ifgBitLength->setUnsettable(false);
    m_Protocol__ifgBitLength->setID(false);
    m_Protocol__ifgBitLength->setUnique(true);
    m_Protocol__ifgBitLength->setDerived(false);
    m_Protocol__ifgBitLength->setOrdered(true);
    m_Protocol__preambleBitLength->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Protocol__preambleBitLength->setName("preambleBitLength");
    m_Protocol__preambleBitLength->setDefaultValueLiteral("56");
    m_Protocol__preambleBitLength->setLowerBound(0);
    m_Protocol__preambleBitLength->setUpperBound(1);
    m_Protocol__preambleBitLength->setTransient(false);
    m_Protocol__preambleBitLength->setVolatile(false);
    m_Protocol__preambleBitLength->setChangeable(true);
    m_Protocol__preambleBitLength->setUnsettable(false);
    m_Protocol__preambleBitLength->setID(false);
    m_Protocol__preambleBitLength->setUnique(true);
    m_Protocol__preambleBitLength->setDerived(false);
    m_Protocol__preambleBitLength->setOrdered(true);
    m_Protocol__sfdBitLength->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Protocol__sfdBitLength->setName("sfdBitLength");
    m_Protocol__sfdBitLength->setDefaultValueLiteral("8");
    m_Protocol__sfdBitLength->setLowerBound(0);
    m_Protocol__sfdBitLength->setUpperBound(1);
    m_Protocol__sfdBitLength->setTransient(false);
    m_Protocol__sfdBitLength->setVolatile(false);
    m_Protocol__sfdBitLength->setChangeable(true);
    m_Protocol__sfdBitLength->setUnsettable(false);
    m_Protocol__sfdBitLength->setID(false);
    m_Protocol__sfdBitLength->setUnique(true);
    m_Protocol__sfdBitLength->setDerived(false);
    m_Protocol__sfdBitLength->setOrdered(true);
    m_Protocol__maximumTransmissionUnit->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_Protocol__maximumTransmissionUnit->setName("maximumTransmissionUnit");
    m_Protocol__maximumTransmissionUnit->setDefaultValueLiteral("1500");
    m_Protocol__maximumTransmissionUnit->setLowerBound(0);
    m_Protocol__maximumTransmissionUnit->setUpperBound(1);
    m_Protocol__maximumTransmissionUnit->setTransient(false);
    m_Protocol__maximumTransmissionUnit->setVolatile(false);
    m_Protocol__maximumTransmissionUnit->setChangeable(true);
    m_Protocol__maximumTransmissionUnit->setUnsettable(false);
    m_Protocol__maximumTransmissionUnit->setID(false);
    m_Protocol__maximumTransmissionUnit->setUnique(true);
    m_Protocol__maximumTransmissionUnit->setDerived(false);
    m_Protocol__maximumTransmissionUnit->setOrdered(true);
    m_Protocol__description->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_Protocol__description->setName("description");
    m_Protocol__description->setDefaultValueLiteral("");
    m_Protocol__description->setLowerBound(0);
    m_Protocol__description->setUpperBound(1);
    m_Protocol__description->setTransient(false);
    m_Protocol__description->setVolatile(false);
    m_Protocol__description->setChangeable(true);
    m_Protocol__description->setUnsettable(false);
    m_Protocol__description->setID(false);
    m_Protocol__description->setUnique(true);
    m_Protocol__description->setDerived(false);
    m_Protocol__description->setOrdered(true);

    // TODO: Initialize data types


    _initialize();
}

::ecore::EClass_ptr Protocol_DefinitionPackage::getProtocols()
{
    return m_ProtocolsEClass;
}
::ecore::EClass_ptr Protocol_DefinitionPackage::getProtocol()
{
    return m_ProtocolEClass;
}

::ecore::EReference_ptr Protocol_DefinitionPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr Protocol_DefinitionPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EReference_ptr Protocol_DefinitionPackage::getProtocols__protocols()
{
    return m_Protocols__protocols;
}
::ecore::EAttribute_ptr Protocol_DefinitionPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EAttribute_ptr Protocol_DefinitionPackage::getProtocol__ifgBitLength()
{
    return m_Protocol__ifgBitLength;
}
::ecore::EAttribute_ptr Protocol_DefinitionPackage::getProtocol__preambleBitLength()
{
    return m_Protocol__preambleBitLength;
}
::ecore::EAttribute_ptr Protocol_DefinitionPackage::getProtocol__sfdBitLength()
{
    return m_Protocol__sfdBitLength;
}
::ecore::EAttribute_ptr Protocol_DefinitionPackage::getProtocol__maximumTransmissionUnit()
{
    return m_Protocol__maximumTransmissionUnit;
}
::ecore::EAttribute_ptr Protocol_DefinitionPackage::getProtocol__description()
{
    return m_Protocol__description;
}

