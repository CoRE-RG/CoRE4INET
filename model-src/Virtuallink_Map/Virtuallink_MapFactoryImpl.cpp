// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/Virtuallink_MapFactoryImpl.cpp
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

#include <Virtuallink_Map/Virtuallink_MapFactory.hpp>
#include <Virtuallink_Map/Virtuallink_MapPackage.hpp>
#include <Virtuallink_Map/VirtualLinkMappings.hpp>
#include <Virtuallink_Map/VirtualLinkMap.hpp>
#include <Virtuallink_Map/VirtualLinkMapping.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Virtuallink_Map;

Virtuallink_MapFactory::Virtuallink_MapFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr Virtuallink_MapFactory::create(::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case Virtuallink_MapPackage::VIRTUALLINKMAPPINGS:
        return createVirtualLinkMappings();
    case Virtuallink_MapPackage::VIRTUALLINKMAP:
        return createVirtualLinkMap();
    case Virtuallink_MapPackage::VIRTUALLINKMAPPING:
        return createVirtualLinkMapping();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject Virtuallink_MapFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString Virtuallink_MapFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    default:
        throw "IllegalArgumentException";
    }
}

VirtualLinkMappings_ptr Virtuallink_MapFactory::createVirtualLinkMappings()
{
    return new VirtualLinkMappings();
}
VirtualLinkMap_ptr Virtuallink_MapFactory::createVirtualLinkMap()
{
    return new VirtualLinkMap();
}
VirtualLinkMapping_ptr Virtuallink_MapFactory::createVirtualLinkMapping()
{
    return new VirtualLinkMapping();
}

