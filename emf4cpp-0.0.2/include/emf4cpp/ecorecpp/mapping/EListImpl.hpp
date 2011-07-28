// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mapping/EListImpl.hpp
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

#ifndef ECORECPP_MAPPING_ELISTIMPL_HPP
#define ECORECPP_MAPPING_ELISTIMPL_HPP

#include "EList.hpp"
#include "any.hpp"
#include <vector>
#include <ecore/EReference.hpp>
#include <ecorecpp/notify.hpp>

namespace ecorecpp
{
namespace mapping
{

template< typename T >
class EListImpl: public EList< T >
{
public:

    virtual T* get(size_t _index) const
    {
        return m_content[_index];
    }

    virtual void insert_at(size_t _pos, T* _obj)
    {
        m_content[_pos] = _obj;
    }

    virtual void push_back(T* _obj)
    {
        m_content.push_back(_obj);
    }

    virtual size_t size() const
    {
        return m_content.size();
    }

    virtual void clear()
    {
        return m_content.clear();
    }

    virtual ~EListImpl()
    {
    }

    // TODO: temporal, protected
    EListImpl()
    {
    }

protected:

    std::vector< T* > m_content;
};

template< typename T, int upper_bound = -1, bool containment = false,
        bool opposite = false >
class ReferenceEListImpl: public EListImpl< T >
{
public:

    ReferenceEListImpl(::ecore::EObject_ptr _this,
            ::ecore::EReference_ptr _ref, ::ecore::EReference_ptr _opp = NULL) :
        m_this(_this), m_ref(_ref), m_opp(_opp), m_opposite(*this)
    {
    }

    virtual void insert_at(size_t _pos, T* _obj)
    {
        contaiment_t< T, containment >::free(base_t::m_content[_pos]);

        base_t::m_content[_pos] = _obj;

        m_opposite.set(_obj);
    }

    virtual void push_back(T* _obj)
    {
        base_t::m_content.push_back(_obj);
    }

    virtual void clear()
    {
        contaiment_t< T, containment >::free_all(base_t::m_content);

        base_t::m_content.clear();
    }

    virtual ~ReferenceEListImpl()
    {
        contaiment_t< T, containment >::free_all(base_t::m_content);
    }

protected:

    ::ecore::EObject_ptr m_this; // owner object
    ::ecore::EReference_ptr m_ref;
    ::ecore::EReference_ptr m_opp;

    template< typename Q, bool _free = false >
    struct contaiment_t
    {
        static inline void free_all(std::vector< Q* >& _v)
        {
        }

        static inline void free(Q* _p)
        {
        }
    };

    template< typename Q >
    struct contaiment_t< Q, true >
    {
        static inline void free_all(std::vector< Q* >& _v)
        {
            for (size_t i = 0; i < _v.size(); i++)
                delete _v[i];
        }

        static inline void free(Q* _p)
        {
            delete _p;
        }
    };

    template< typename Q, bool _opposite = false >
    struct opposite_t
    {
        inline opposite_t(ReferenceEListImpl& _parent)
        {
        }

        inline void set(::ecore::EObject_ptr _obj)
        {
        }
    };

    template< typename Q >
    struct opposite_t< Q, true >
    {
        inline opposite_t(ReferenceEListImpl& _parent)
        : m_parent(_parent)
        {
        }

        inline void set(::ecore::EObject_ptr _obj)
        {
        }

        ReferenceEListImpl& m_parent;
    };

    typedef EListImpl< T > base_t;

    opposite_t< T, opposite > m_opposite;

};

} // mapping
} // ecorecpp

#endif // ECORECPP_MAPPING_ELISTIMPL_HPP
