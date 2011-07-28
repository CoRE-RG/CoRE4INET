// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Protocol_Definition_forward.hpp
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

#ifndef _PROTOCOL_DEFINITION_FORWARD_HPP
#define _PROTOCOL_DEFINITION_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(Protocol_Definition_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace Protocol_Definition
{

    // EDataType


    // EClass

    // Protocols
    class Protocols;
    typedef Protocols* Protocols_ptr;

    // Protocol
    class Protocol;
    typedef Protocol* Protocol_ptr;

    // Package & Factory
    class Protocol_DefinitionFactory;
    typedef Protocol_DefinitionFactory * Protocol_DefinitionFactory_ptr;
    class Protocol_DefinitionPackage;
    typedef Protocol_DefinitionPackage * Protocol_DefinitionPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // Protocol_Definition


#endif // _PROTOCOL_DEFINITION_FORWARD_HPP
