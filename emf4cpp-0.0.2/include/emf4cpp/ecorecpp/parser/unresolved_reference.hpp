// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parser/unresolved_reference.hpp
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

#ifndef _ECORECPPREFUNRESOLVED_HPP
#define    _ECORECPPREFUNRESOLVED_HPP

#include <string>
#include <ecore.hpp>
#include "../mapping.hpp"

namespace ecorecpp
{
namespace parser
{

struct unresolved_reference_t
{

    inline unresolved_reference_t(::ecorecpp::mapping::type_traits::string_t const& x,
                                  ::ecorecpp::mapping::type_traits::string_t const& r,
                                  ::ecore::EObject_ptr eo,
                                  ::ecore::EClass_ptr ec) :
        xpath(x), ref_name(r), eobject(eo), eclass(ec)
    {
    }

    ::ecorecpp::mapping::type_traits::string_t xpath;
    ::ecorecpp::mapping::type_traits::string_t ref_name;
    ::ecore::EObject_ptr eobject;
    ::ecore::EClass_ptr eclass;
};

} // parser
} // ecorecpp

#endif    /* _ECORECPPREFUNRESOLVED_HPP */
