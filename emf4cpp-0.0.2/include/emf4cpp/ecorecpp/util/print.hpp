// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * util/print.hpp
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

#ifndef ECOREUTILPRINT_HPP
#define ECOREUTILPRINT_HPP

#include <ecore.hpp>
#include <iostream>

namespace ecorecpp
{
namespace util
{

void print_all(::ecore::EPackage_ptr pkg);
void print(::ecore::EPackage_ptr pkg);

void print(std::ostream& out, const ::ecore::EObject_ptr obj, int level = 0);

} // util
} // ecorecpp

template <typename Stream>
inline Stream& operator<<(Stream& out,
        const ::ecore::EObject_ptr obj)
{
    ::ecorecpp::util::print(out, obj, 0);
    return out;
}

#endif // ECOREUTILPRINT_HPP
