// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/Virtuallink_MapPackageImpl.cpp
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

#include <Virtuallink_Map/Virtuallink_MapPackage.hpp>
#include <Virtuallink_Map/Virtuallink_MapFactory.hpp>
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
#include <System_Specification/System_SpecificationPackage.hpp>
#include <ecore/EAnnotation.hpp>
#include <System_Specification/MetaInformation.hpp>
#include <System_Specification/VirtualLink.hpp>

using namespace ::Virtuallink_Map;

Virtuallink_MapPackage::Virtuallink_MapPackage()
{

    s_instance.reset(this);

    // Factory
    ::ecore::EFactory_ptr _fa = Virtuallink_MapFactory::_instance();
    setEFactoryInstance(_fa);
    _fa->setEPackage(this);

    // Create classes and their features

    // VirtualLinkMappings
    m_VirtualLinkMappingsEClass = new ::ecore::EClass();
    m_VirtualLinkMappingsEClass->setClassifierID(VIRTUALLINKMAPPINGS);
    m_VirtualLinkMappingsEClass->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinkMappingsEClass);
    m_VirtualLinkMappings__virtualLinkMapping = new ::ecore::EReference();
    m_VirtualLinkMappings__virtualLinkMapping->setFeatureID(
            ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__VIRTUALLINKMAPPING);
    m_VirtualLinkMappingsEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkMappings__virtualLinkMapping);
    m_VirtualLinkMappings__metaInformation = new ::ecore::EReference();
    m_VirtualLinkMappings__metaInformation->setFeatureID(
            ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPINGS__METAINFORMATION);
    m_VirtualLinkMappingsEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkMappings__metaInformation);

    // VirtualLinkMap
    m_VirtualLinkMapEClass = new ::ecore::EClass();
    m_VirtualLinkMapEClass->setClassifierID(VIRTUALLINKMAP);
    m_VirtualLinkMapEClass->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinkMapEClass);
    m_VirtualLinkMap__id = new ::ecore::EAttribute();
    m_VirtualLinkMap__id->setFeatureID(
            ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAP__ID);
    m_VirtualLinkMapEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkMap__id);
    m_VirtualLinkMap__VL_Name = new ::ecore::EAttribute();
    m_VirtualLinkMap__VL_Name->setFeatureID(
            ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAP__VL_NAME);
    m_VirtualLinkMapEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkMap__VL_Name);
    m_VirtualLinkMap__refVirtualLink = new ::ecore::EReference();
    m_VirtualLinkMap__refVirtualLink->setFeatureID(
            ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAP__REFVIRTUALLINK);
    m_VirtualLinkMapEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkMap__refVirtualLink);

    // VirtualLinkMapping
    m_VirtualLinkMappingEClass = new ::ecore::EClass();
    m_VirtualLinkMappingEClass->setClassifierID(VIRTUALLINKMAPPING);
    m_VirtualLinkMappingEClass->setEPackage(this);
    getEClassifiers().push_back(m_VirtualLinkMappingEClass);
    m_VirtualLinkMapping__virtualLinkMap = new ::ecore::EReference();
    m_VirtualLinkMapping__virtualLinkMap->setFeatureID(
            ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPING__VIRTUALLINKMAP);
    m_VirtualLinkMappingEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkMapping__virtualLinkMap);
    m_VirtualLinkMapping__metaInformation = new ::ecore::EReference();
    m_VirtualLinkMapping__metaInformation->setFeatureID(
            ::Virtuallink_Map::Virtuallink_MapPackage::VIRTUALLINKMAPPING__METAINFORMATION);
    m_VirtualLinkMappingEClass->getEStructuralFeatures().push_back(
            m_VirtualLinkMapping__metaInformation);

    // Create enums


    // Create data types


    // Initialize package
    setName("Virtuallink_Map");
    setNsPrefix("vlm");
    setNsURI("http://www.tttech.com/Schema/TTEthernet/Virtuallink_Map_V1");

    // TODO: bounds for type parameters

    // Add supertypes to classes
    m_VirtualLinkMappingsEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_VirtualLinkMapEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getModelElement());
    m_VirtualLinkMappingEClass->getESuperTypes().push_back(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getNamedElement());

    // TODO: Initialize classes and features; add operations and parameters
    // TODO: GenericTypes
    // VirtualLinkMappings
    m_VirtualLinkMappingsEClass->setName("VirtualLinkMappings");
    m_VirtualLinkMappingsEClass->setAbstract(false);
    m_VirtualLinkMappingsEClass->setInterface(false);
    m_VirtualLinkMappings__virtualLinkMapping->setEType(
            m_VirtualLinkMappingEClass);
    m_VirtualLinkMappings__virtualLinkMapping->setName("virtualLinkMapping");
    m_VirtualLinkMappings__virtualLinkMapping->setDefaultValueLiteral("");
    m_VirtualLinkMappings__virtualLinkMapping->setLowerBound(0);
    m_VirtualLinkMappings__virtualLinkMapping->setUpperBound(-1);
    m_VirtualLinkMappings__virtualLinkMapping->setTransient(false);
    m_VirtualLinkMappings__virtualLinkMapping->setVolatile(false);
    m_VirtualLinkMappings__virtualLinkMapping->setChangeable(true);
    m_VirtualLinkMappings__virtualLinkMapping->setContainment(true);
    m_VirtualLinkMappings__virtualLinkMapping->setResolveProxies(true);
    m_VirtualLinkMappings__virtualLinkMapping->setUnique(true);
    m_VirtualLinkMappings__virtualLinkMapping->setDerived(false);
    m_VirtualLinkMappings__virtualLinkMapping->setOrdered(true);
    m_VirtualLinkMappings__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_VirtualLinkMappings__metaInformation->setName("metaInformation");
    m_VirtualLinkMappings__metaInformation->setDefaultValueLiteral("");
    m_VirtualLinkMappings__metaInformation->setLowerBound(0);
    m_VirtualLinkMappings__metaInformation->setUpperBound(1);
    m_VirtualLinkMappings__metaInformation->setTransient(false);
    m_VirtualLinkMappings__metaInformation->setVolatile(false);
    m_VirtualLinkMappings__metaInformation->setChangeable(true);
    m_VirtualLinkMappings__metaInformation->setContainment(true);
    m_VirtualLinkMappings__metaInformation->setResolveProxies(true);
    m_VirtualLinkMappings__metaInformation->setUnique(true);
    m_VirtualLinkMappings__metaInformation->setDerived(false);
    m_VirtualLinkMappings__metaInformation->setOrdered(true);
    // VirtualLinkMap
    m_VirtualLinkMapEClass->setName("VirtualLinkMap");
    m_VirtualLinkMapEClass->setAbstract(false);
    m_VirtualLinkMapEClass->setInterface(false);
    m_VirtualLinkMap__id->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEInt());
    m_VirtualLinkMap__id->setName("id");
    m_VirtualLinkMap__id->setDefaultValueLiteral("");
    m_VirtualLinkMap__id->setLowerBound(1);
    m_VirtualLinkMap__id->setUpperBound(1);
    m_VirtualLinkMap__id->setTransient(false);
    m_VirtualLinkMap__id->setVolatile(false);
    m_VirtualLinkMap__id->setChangeable(true);
    m_VirtualLinkMap__id->setUnsettable(false);
    m_VirtualLinkMap__id->setID(false);
    m_VirtualLinkMap__id->setUnique(true);
    m_VirtualLinkMap__id->setDerived(false);
    m_VirtualLinkMap__id->setOrdered(true);
    m_VirtualLinkMap__VL_Name->setEType(
            dynamic_cast< ::ecore::EcorePackage* > (::ecore::EcorePackage::_instance())->getEString());
    m_VirtualLinkMap__VL_Name->setName("VL_Name");
    m_VirtualLinkMap__VL_Name->setDefaultValueLiteral("");
    m_VirtualLinkMap__VL_Name->setLowerBound(1);
    m_VirtualLinkMap__VL_Name->setUpperBound(1);
    m_VirtualLinkMap__VL_Name->setTransient(false);
    m_VirtualLinkMap__VL_Name->setVolatile(false);
    m_VirtualLinkMap__VL_Name->setChangeable(true);
    m_VirtualLinkMap__VL_Name->setUnsettable(false);
    m_VirtualLinkMap__VL_Name->setID(false);
    m_VirtualLinkMap__VL_Name->setUnique(true);
    m_VirtualLinkMap__VL_Name->setDerived(false);
    m_VirtualLinkMap__VL_Name->setOrdered(true);
    m_VirtualLinkMap__refVirtualLink->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getVirtualLink());
    m_VirtualLinkMap__refVirtualLink->setName("refVirtualLink");
    m_VirtualLinkMap__refVirtualLink->setDefaultValueLiteral("");
    m_VirtualLinkMap__refVirtualLink->setLowerBound(1);
    m_VirtualLinkMap__refVirtualLink->setUpperBound(1);
    m_VirtualLinkMap__refVirtualLink->setTransient(false);
    m_VirtualLinkMap__refVirtualLink->setVolatile(false);
    m_VirtualLinkMap__refVirtualLink->setChangeable(true);
    m_VirtualLinkMap__refVirtualLink->setContainment(false);
    m_VirtualLinkMap__refVirtualLink->setResolveProxies(true);
    m_VirtualLinkMap__refVirtualLink->setUnique(true);
    m_VirtualLinkMap__refVirtualLink->setDerived(false);
    m_VirtualLinkMap__refVirtualLink->setOrdered(true);
    // VirtualLinkMapping
    m_VirtualLinkMappingEClass->setName("VirtualLinkMapping");
    m_VirtualLinkMappingEClass->setAbstract(false);
    m_VirtualLinkMappingEClass->setInterface(false);
    m_VirtualLinkMapping__virtualLinkMap->setEType(m_VirtualLinkMapEClass);
    m_VirtualLinkMapping__virtualLinkMap->setName("virtualLinkMap");
    m_VirtualLinkMapping__virtualLinkMap->setDefaultValueLiteral("");
    m_VirtualLinkMapping__virtualLinkMap->setLowerBound(0);
    m_VirtualLinkMapping__virtualLinkMap->setUpperBound(-1);
    m_VirtualLinkMapping__virtualLinkMap->setTransient(false);
    m_VirtualLinkMapping__virtualLinkMap->setVolatile(false);
    m_VirtualLinkMapping__virtualLinkMap->setChangeable(true);
    m_VirtualLinkMapping__virtualLinkMap->setContainment(true);
    m_VirtualLinkMapping__virtualLinkMap->setResolveProxies(true);
    m_VirtualLinkMapping__virtualLinkMap->setUnique(true);
    m_VirtualLinkMapping__virtualLinkMap->setDerived(false);
    m_VirtualLinkMapping__virtualLinkMap->setOrdered(true);
    m_VirtualLinkMapping__metaInformation->setEType(
            dynamic_cast< ::System_Specification::System_SpecificationPackage* > (::System_Specification::System_SpecificationPackage::_instance())->getMetaInformation());
    m_VirtualLinkMapping__metaInformation->setName("metaInformation");
    m_VirtualLinkMapping__metaInformation->setDefaultValueLiteral("");
    m_VirtualLinkMapping__metaInformation->setLowerBound(0);
    m_VirtualLinkMapping__metaInformation->setUpperBound(1);
    m_VirtualLinkMapping__metaInformation->setTransient(false);
    m_VirtualLinkMapping__metaInformation->setVolatile(false);
    m_VirtualLinkMapping__metaInformation->setChangeable(true);
    m_VirtualLinkMapping__metaInformation->setContainment(true);
    m_VirtualLinkMapping__metaInformation->setResolveProxies(true);
    m_VirtualLinkMapping__metaInformation->setUnique(true);
    m_VirtualLinkMapping__metaInformation->setDerived(false);
    m_VirtualLinkMapping__metaInformation->setOrdered(true);

    // TODO: Initialize data types


    _initialize();
}

::ecore::EClass_ptr Virtuallink_MapPackage::getVirtualLinkMappings()
{
    return m_VirtualLinkMappingsEClass;
}
::ecore::EClass_ptr Virtuallink_MapPackage::getVirtualLinkMap()
{
    return m_VirtualLinkMapEClass;
}
::ecore::EClass_ptr Virtuallink_MapPackage::getVirtualLinkMapping()
{
    return m_VirtualLinkMappingEClass;
}

::ecore::EReference_ptr Virtuallink_MapPackage::getModelElement__eAnnotations()
{
    return m_ModelElement__eAnnotations;
}
::ecore::EAttribute_ptr Virtuallink_MapPackage::getModelElement__signature()
{
    return m_ModelElement__signature;
}
::ecore::EReference_ptr Virtuallink_MapPackage::getVirtualLinkMappings__virtualLinkMapping()
{
    return m_VirtualLinkMappings__virtualLinkMapping;
}
::ecore::EReference_ptr Virtuallink_MapPackage::getVirtualLinkMappings__metaInformation()
{
    return m_VirtualLinkMappings__metaInformation;
}
::ecore::EAttribute_ptr Virtuallink_MapPackage::getVirtualLinkMap__id()
{
    return m_VirtualLinkMap__id;
}
::ecore::EAttribute_ptr Virtuallink_MapPackage::getVirtualLinkMap__VL_Name()
{
    return m_VirtualLinkMap__VL_Name;
}
::ecore::EReference_ptr Virtuallink_MapPackage::getVirtualLinkMap__refVirtualLink()
{
    return m_VirtualLinkMap__refVirtualLink;
}
::ecore::EAttribute_ptr Virtuallink_MapPackage::getNamedElement__name()
{
    return m_NamedElement__name;
}
::ecore::EReference_ptr Virtuallink_MapPackage::getVirtualLinkMapping__virtualLinkMap()
{
    return m_VirtualLinkMapping__virtualLinkMap;
}
::ecore::EReference_ptr Virtuallink_MapPackage::getVirtualLinkMapping__metaInformation()
{
    return m_VirtualLinkMapping__metaInformation;
}

