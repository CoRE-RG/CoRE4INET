// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IP_ConfigurationFactoryImpl.cpp
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

#include <IP_Configuration/IP_ConfigurationFactory.hpp>
#include <IP_Configuration/IP_ConfigurationPackage.hpp>
#include <IP_Configuration/Implementation.hpp>
#include <IP_Configuration/TTTechIp.hpp>
#include <IP_Configuration/TTTechSwIp.hpp>
#include <IP_Configuration/TTTechEsIp.hpp>
#include <IP_Configuration/IpLayout.hpp>
#include <IP_Configuration/TTTechIpLayout.hpp>
#include <IP_Configuration/IpConfigurations.hpp>
#include <IP_Configuration/GeneralImplementationDescription.hpp>

#include <ecore.hpp>
#include <ecorecpp/mapping.hpp>

using namespace ::IP_Configuration;

IP_ConfigurationFactory::IP_ConfigurationFactory()
{
    s_instance.reset(this);
}

::ecore::EObject_ptr IP_ConfigurationFactory::create(
        ::ecore::EClass_ptr _eClass)
{
    switch (_eClass->getClassifierID())
    {
    case IP_ConfigurationPackage::IMPLEMENTATION:
        return createImplementation();
    case IP_ConfigurationPackage::TTTECHIP:
        return createTTTechIp();
    case IP_ConfigurationPackage::TTTECHSWIP:
        return createTTTechSwIp();
    case IP_ConfigurationPackage::TTTECHESIP:
        return createTTTechEsIp();
    case IP_ConfigurationPackage::IPLAYOUT:
        return createIpLayout();
    case IP_ConfigurationPackage::TTTECHIPLAYOUT:
        return createTTTechIpLayout();
    case IP_ConfigurationPackage::IPCONFIGURATIONS:
        return createIpConfigurations();
    case IP_ConfigurationPackage::GENERALIMPLEMENTATIONDESCRIPTION:
        return createGeneralImplementationDescription();
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EJavaObject IP_ConfigurationFactory::createFromString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EString const& _literalValue)
{
    switch (_eDataType->getClassifierID())
    {
    default:
        throw "IllegalArgumentException";
    }
}

::ecore::EString IP_ConfigurationFactory::convertToString(
        ::ecore::EDataType_ptr _eDataType,
        ::ecore::EJavaObject const& _instanceValue)
{
    switch (_eDataType->getClassifierID())
    {
    default:
        throw "IllegalArgumentException";
    }
}

Implementation_ptr IP_ConfigurationFactory::createImplementation()
{
    return new Implementation();
}
TTTechIp_ptr IP_ConfigurationFactory::createTTTechIp()
{
    return new TTTechIp();
}
TTTechSwIp_ptr IP_ConfigurationFactory::createTTTechSwIp()
{
    return new TTTechSwIp();
}
TTTechEsIp_ptr IP_ConfigurationFactory::createTTTechEsIp()
{
    return new TTTechEsIp();
}
IpLayout_ptr IP_ConfigurationFactory::createIpLayout()
{
    return new IpLayout();
}
TTTechIpLayout_ptr IP_ConfigurationFactory::createTTTechIpLayout()
{
    return new TTTechIpLayout();
}
IpConfigurations_ptr IP_ConfigurationFactory::createIpConfigurations()
{
    return new IpConfigurations();
}
GeneralImplementationDescription_ptr IP_ConfigurationFactory::createGeneralImplementationDescription()
{
    return new GeneralImplementationDescription();
}

