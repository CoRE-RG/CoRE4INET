// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mapping/list.hpp
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

#ifndef ECORECPP_MAPPING_LIST_HPP
#define ECORECPP_MAPPING_LIST_HPP

#include "out_ptr.hpp"
#include <vector>
#include <ecore_forward.hpp>

namespace ecorecpp
{
namespace mapping
{

class EEListBase
{
public:

    virtual ::ecore::EObject_ptr operator[](size_t _index) = 0;

    virtual size_t size() = 0;

    virtual ~EEListBase()
    {
    }

protected:
    EEListBase()
    {
    }
};

typedef out_ptr< EEListBase > EEListBase_ptr;

template< typename T >
class EEList: public EEListBase
{
public:

    EEList(std::vector< T* >& t) :
        m_vector(t)
    {
    }

    virtual ~EEList()
    {
    }

    virtual ::ecore::EObject_ptr operator[](size_t _index)
    {
        return m_vector[_index];
    }

    virtual size_t size()
    {
        return m_vector.size();
    }

protected:

    std::vector< T* >& m_vector;
};

} // mapping
} // ecorecpp

#endif // ECORECPP_MAPPING_LIST_HPP
