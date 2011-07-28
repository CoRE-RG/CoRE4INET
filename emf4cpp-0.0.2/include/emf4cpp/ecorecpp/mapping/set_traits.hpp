// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mapping/set_traits.hpp
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

#ifndef ECORECPP_MAPPING_SETTRAITS_HPP
#define    ECORECPP_MAPPING_SETTRAITS_HPP

#include "type_traits.hpp"

namespace ecorecpp
{
namespace mapping
{

template< typename T >
struct set_traits
{
    static inline T default_value()
    {
        return (T) 0;
    }

    static inline bool is_set(T value)
    {
        return value != default_value();
    }

    static inline void unset(T& value)
    {
        value = default_value();
    }
};

template< >
struct set_traits< bool >
{
    static inline bool default_value()
    {
        return false;
    }

    static inline bool is_set(bool value)
    {
        return value != default_value();
    }

    static inline void unset(bool& value)
    {
        value = default_value();
    }
};

template< >
struct set_traits< type_traits::string_t >
{
    static const type_traits::string_t _default;

    static inline const type_traits::string_t& default_value()
    {
        return _default;
    }

    static inline bool is_set(const type_traits::string_t& value)
    {
        return !value.empty();
    }

    static inline void unset(type_traits::string_t& value)
    {
        value.clear();
    }
};

template< >
struct set_traits< any >
{
    static const any _default;

    static inline const any& default_value()
    {
        return _default;
    }

    static inline bool is_set(const any& value)
    {
        return !value.empty();
    }

    static inline void unset(any& value)
    {
        any old_value;
        value.swap(old_value);
    }
};

} // mapping
} // ecorecpp

#endif // ECORECPP_MAPPING_SETTRAITS_HPP
