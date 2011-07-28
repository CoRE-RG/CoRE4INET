// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mapping/EList.hpp
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

#ifndef ECORECPP_MAPPING_ELIST_HPP
#define ECORECPP_MAPPING_ELIST_HPP


#include <ecore_forward.hpp>
#include "out_ptr.hpp"
#include <ecore/EObject.hpp>

namespace ecorecpp
{
namespace mapping
{

typedef out_ptr< EList< ::ecore::EObject > > EList_ptr; // for any

template< typename T >
class EList
{
public:

    typedef out_ptr< EList< T > > ptr_type;

    inline T* operator[](size_t _index) const
    {
        return get(_index);
    }

    template< typename Q >
    inline void insert_all(EList< Q >& _q)
    {
        ptr_type _p(_q.asEListOf< T >());

        for (size_t i = 0; i < _p->size(); i++)
            push_back(_p->get(i));
    }

    inline void insert_all(EList& _q)
    {
        for (size_t i = 0; i < _q.size(); i++)
            push_back(_q.get(i));
    }

    virtual void insert_at(size_t _pos, T* _obj) = 0;

    virtual T* get(size_t _index) const = 0;

    virtual void push_back(T* _obj) = 0;

    virtual size_t size() const = 0;

    virtual void clear() = 0;

    /**
     * Permite tratar a una EList< T > como una EList< Q >
     */
    template< typename Q >
    inline typename EList< Q >::ptr_type asEListOf()
    {
        return new DelegateEList< Q, T > (*this);
    }

    virtual ~EList()
    {
    }

protected:
    EList()
    {
    }
};

/**
 * Ofrece la interfaz de una lista EList<T> para una EList<Q>
 * TODO: throw exception
 */
template< typename T, typename Q >
class DelegateEList: public EList< T >
{
public:

    typedef EList< Q > list_t;

    DelegateEList(list_t& _delegate) :
        m_delegate(_delegate)
    {
    }

    virtual T* get(size_t _index) const
    {
        return _cast< Q, T >::do_cast(m_delegate[_index]);
    }

    virtual void insert_at(size_t _pos, T* _obj)
    {
        m_delegate.insert_at(_pos, _cast< T, Q >::do_cast(_obj));
    }

    virtual void push_back(T* _obj)
    {
        m_delegate.push_back(_cast< T, Q >::do_cast(_obj));
    }

    virtual size_t size() const
    {
        return m_delegate.size();
    }

    virtual void clear()
    {
        return m_delegate.clear();
    }

    virtual ~DelegateEList()
    {
    }

protected:

    list_t& m_delegate;

    template< typename A, typename B >
    struct _cast
    {
        static inline B* do_cast(A* a)
        {
            return dynamic_cast< B* > (a);
        }
    };

    template< typename A >
    struct _cast< A, A >
    {
        static inline A* do_cast(A* a)
        {
            return a;
        }
    };
};

} // mapping
} // ecorecpp

#endif // ECORECPP_MAPPING_ELIST_HPP
