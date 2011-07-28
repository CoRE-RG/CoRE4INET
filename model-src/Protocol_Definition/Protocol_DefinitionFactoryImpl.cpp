// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Protocol_Definition/Protocol_DefinitionFactoryImpl.cpp
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

#include <Protocol_Definition/Protocol_DefinitionFactory.hpp>
#include <Protocol_Definition/Protocol_DefinitionPackage.hpp>
#include <Protocol_Definition/Protocols.hpp>
#include <Protocol_Definition/Protocol.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::Protocol_Definition;

Protocol_DefinitionFactory::Protocol_DefinitionFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr Protocol_DefinitionFactory::create(
        ::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case Protocol_DefinitionPackage::PROTOCOLS:
        return createProtocols();
    case Protocol_DefinitionPackage::PROTOCOL:
        return createProtocol();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject Protocol_DefinitionFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString Protocol_DefinitionFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    default:
        throw "IllegalArgumentException";
    }
}

Protocols_ptr Protocol_DefinitionFactory::createProtocols()
{
    return new Protocols();
}
Protocol_ptr Protocol_DefinitionFactory::createProtocol()
{
    return new Protocol();
}

