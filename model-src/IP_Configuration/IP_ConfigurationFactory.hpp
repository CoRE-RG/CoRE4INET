// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration/IP_ConfigurationFactory.hpp
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

#ifndef _IP_CONFIGURATIONFACTORY_HPP
#define _IP_CONFIGURATIONFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <IP_Configuration.hpp>

namespace IP_Configuration
{

    class IP_ConfigurationFactory: public virtual ::ecore::EFactory
    {
    public:

        static IP_ConfigurationFactory_ptr _instance();

        virtual Implementation_ptr createImplementation();
        virtual TTTechIp_ptr createTTTechIp();
        virtual TTTechSwIp_ptr createTTTechSwIp();
        virtual TTTechEsIp_ptr createTTTechEsIp();
        virtual IpLayout_ptr createIpLayout();
        virtual TTTechIpLayout_ptr createTTTechIpLayout();
        virtual IpConfigurations_ptr createIpConfigurations();
        virtual GeneralImplementationDescription_ptr
                createGeneralImplementationDescription();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< IP_ConfigurationFactory > s_instance;

        IP_ConfigurationFactory();

    };

} // IP_Configuration


#endif // _IP_CONFIGURATIONFACTORY_HPP
