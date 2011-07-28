// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * Virtuallink_Map/Virtuallink_MapFactory.hpp
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

#ifndef _VIRTUALLINK_MAPFACTORY_HPP
#define _VIRTUALLINK_MAPFACTORY_HPP

#include <ecore/EFactory.hpp>
#include <Virtuallink_Map.hpp>

namespace Virtuallink_Map
{

    class Virtuallink_MapFactory: public virtual ::ecore::EFactory
    {
    public:

        static Virtuallink_MapFactory_ptr _instance();

        virtual VirtualLinkMappings_ptr createVirtualLinkMappings();
        virtual VirtualLinkMap_ptr createVirtualLinkMap();
        virtual VirtualLinkMapping_ptr createVirtualLinkMapping();

        virtual ::ecore::EObject_ptr create(::ecore::EClass_ptr _eClass);
        virtual ::ecore::EJavaObject createFromString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EString const& _literalValue);
        virtual ::ecore::EString convertToString(
                ::ecore::EDataType_ptr _eDataType,
                ::ecore::EJavaObject const& _instanceValue);

    protected:

        static std::auto_ptr< Virtuallink_MapFactory > s_instance;

        Virtuallink_MapFactory();

    };

} // Virtuallink_Map


#endif // _VIRTUALLINK_MAPFACTORY_HPP
