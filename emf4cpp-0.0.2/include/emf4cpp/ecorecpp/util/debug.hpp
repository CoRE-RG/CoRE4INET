// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * util/debug.hpp
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

#ifndef ECOREUTILDEBUG_HPP
#define ECOREUTILDEBUG_HPP

#include <iostream>

#ifdef DEBUG

#define DEBUG_MSG( X, Y ) \
        std::X <<__FILE__ << ":" <<__LINE__ << ":" << __FUNCTION__ << ": " << Y << std::endl

#else

#define DEBUG_MSG(X, Y)

#endif

#define ERROR_MSG(Y) \
        std::wcerr <<__FILE__ << ":" <<__LINE__ << ":" << __FUNCTION__ << ": " << Y << std::endl

#endif // ECOREUTILDEBUG_HPP
