// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mapping/any_traits.hpp
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

#ifndef ECORECPP_MAPPING_ANYTRAITS_HPP
#define    ECORECPP_MAPPING_ANYTRAITS_HPP

#include "type_traits.hpp"

namespace ecorecpp
{
namespace mapping
{

template< typename T >
struct any_traits
{
    static inline void fromAny(const any& _any, T& _t)
    {
        _t = any::any_cast< T >(_any);
    }

    static inline void toAny(any& _any, const T& _t)
    {
        _any = _t;
    }
};

template< >
struct any_traits< type_traits::string_t >
{
    static inline void fromAny(const any& _any, type_traits::string_t& _t)
    {
        if (_any.type() == type_id<const type_traits::string_t*>::id())
            _t = *any::any_cast< const type_traits::string_t* >(_any);
        else if (_any.type() == type_id<type_traits::string_t*>::id())
            _t = *any::any_cast< type_traits::string_t* >(_any);
    }

    static inline void toAny(any& _any, const type_traits::string_t& _t)
    {
        _any = &_t;
    }
};

} // mapping
} // ecorecpp

#endif // ECORECPP_MAPPING_ANYTRAITS_HPP
