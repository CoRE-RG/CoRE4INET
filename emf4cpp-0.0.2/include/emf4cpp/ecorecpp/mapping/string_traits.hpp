// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mapping/string_traits.hpp
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

#ifndef ECORECPP_MAPPING_STRINGTRAITS_HPP
#define    ECORECPP_MAPPING_STRINGTRAITS_HPP

#include "type_traits.hpp"

#include <stdlib.h>

#include <iostream>
namespace ecorecpp
{
namespace mapping
{

// Default trait
template< typename T >
struct string_traits
{
    static inline any fromString(const type_traits::string_t & _str)
    {
        type_traits::stringstream_t _ss(_str);
        T t;
        _ss >> t;
        return t;
    }

    static inline type_traits::string_t toString(any const& _any)
    {
        T _t = any::any_cast< T >(_any);
        type_traits::stringstream_t _ss;

        _ss << _t;

        return _ss.str();
    }
};

template< >
struct string_traits< bool >
{
    static any fromString(const type_traits::string_t & _str)
    {
        if (_str == "true")
            return true;
        else if (_str == "false")
            return false;

        throw "fromString exception";
    }

    static inline type_traits::string_t toString(any const& _any)
    {
        bool _t = any::any_cast< bool >(_any);

        if (_t)
            return "true";

        return "false";
    }
};

template< >
struct string_traits< type_traits::string_t >
{
    static inline any fromString(const type_traits::string_t & _str)
    {
        return &_str;
    }

    static inline type_traits::string_t toString(any const& _any)
    {
        return *any::any_cast< const type_traits::string_t* >(_any);
    }
};

template< >
struct string_traits< unsigned char >
{
    static inline any fromString(const type_traits::string_t & _str)
    {
        return (unsigned char) atoi(_str.c_str());
    }

    static inline type_traits::string_t toString(any const& _any)
    {
    	std::stringstream sstr;
    	sstr << (int)any::any_cast< unsigned char >(_any);
        return sstr.str();
    }
};

template< >
struct string_traits< char >
{
    static inline any fromString(const type_traits::string_t & _str)
    {
        // TODO
        throw "Not implemented! string_traits< char > fromString";
    }

    static inline type_traits::string_t toString(any const& _any)
    {
        // TODO
        throw "Not implemented! string_traits< char > toString";
    }
};

template< >
struct string_traits< std::vector< unsigned char > >
{
    static inline any fromString(
            const type_traits::string_t & _str)
    {
        // TODO
        throw "Not implemented! string_traits< std::vector< unsigned char > > fromString";
    }

    static inline type_traits::string_t toString(any const& _any)
    {
        // TODO
        throw "Not implemented! string_traits< std::vector< unsigned char > > toString";
    }
};

template< >
struct string_traits< any >
{
    static inline any fromString(const type_traits::string_t & _str)
    {
        throw "Impossible! string_traits< any > fromString";
    }

    static inline type_traits::string_t toString(any const& _any)
    {
        throw "Impossible! string_traits< any > toString";
    }
};

} // mapping
} // ecorecpp

#endif // ECORECPP_MAPPING_STRINGTRAITS_HPP
