// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map_forward.hpp
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

#ifndef _VIRTUALLINK_MAP_FORWARD_HPP
#define _VIRTUALLINK_MAP_FORWARD_HPP

#include <ecorecpp/mapping_forward.hpp>

/*PROTECTED REGION ID(Virtuallink_Map_forward) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
// Additional headers here
/*PROTECTED REGION END*/

// EPackage


#include <ecore_forward.hpp> // for EDataTypes
namespace Virtuallink_Map
{

    // EDataType


    // EClass

    // VirtualLinkMappings
    class VirtualLinkMappings;
    typedef VirtualLinkMappings* VirtualLinkMappings_ptr;

    // VirtualLinkMap
    class VirtualLinkMap;
    typedef VirtualLinkMap* VirtualLinkMap_ptr;

    // VirtualLinkMapping
    class VirtualLinkMapping;
    typedef VirtualLinkMapping* VirtualLinkMapping_ptr;

    // Package & Factory
    class Virtuallink_MapFactory;
    typedef Virtuallink_MapFactory * Virtuallink_MapFactory_ptr;
    class Virtuallink_MapPackage;
    typedef Virtuallink_MapPackage * Virtuallink_MapPackage_ptr;

    template< typename T, typename S >
    inline T* instanceOf(S* _s)
    {
        return dynamic_cast< T* > (_s);
    }

} // Virtuallink_Map


#endif // _VIRTUALLINK_MAP_FORWARD_HPP
