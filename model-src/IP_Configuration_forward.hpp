// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * IP_Configuration_forward.hpp
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

#ifndef _IP_CONFIGURATION_FORWARD_HPP
#define _IP_CONFIGURATION_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(IP_Configuration_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace IP_Configuration
{

    // EDataType


    // EClass

    // Implementation
    class Implementation;
    typedef Implementation* Implementation_ptr;

    // TTTechIp
    class TTTechIp;
    typedef TTTechIp* TTTechIp_ptr;

    // TTTechSwIp
    class TTTechSwIp;
    typedef TTTechSwIp* TTTechSwIp_ptr;

    // TTTechEsIp
    class TTTechEsIp;
    typedef TTTechEsIp* TTTechEsIp_ptr;

    // IpLayout
    class IpLayout;
    typedef IpLayout* IpLayout_ptr;

    // TTTechIpLayout
    class TTTechIpLayout;
    typedef TTTechIpLayout* TTTechIpLayout_ptr;

    // IpConfigurations
    class IpConfigurations;
    typedef IpConfigurations* IpConfigurations_ptr;

    // GeneralImplementationDescription
    class GeneralImplementationDescription;
    typedef GeneralImplementationDescription
            * GeneralImplementationDescription_ptr;

    // Package & Factory
    class IP_ConfigurationFactory;
    typedef IP_ConfigurationFactory * IP_ConfigurationFactory_ptr;
    class IP_ConfigurationPackage;
    typedef IP_ConfigurationPackage * IP_ConfigurationPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // IP_Configuration


#endif // _IP_CONFIGURATION_FORWARD_HPP
