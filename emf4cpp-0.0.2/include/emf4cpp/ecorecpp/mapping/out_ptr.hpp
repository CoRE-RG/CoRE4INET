// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * mapping/out_ptr.hpp
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

#ifndef ECORECPP_OUT_PTR_HPP
#define ECORECPP_OUT_PTR_HPP

namespace ecorecpp
{
namespace mapping
{

// A delegating pointer. Every copy gives ownership to the copy
template< typename T >
class out_ptr
{
    T* d;
    bool own;

public:
    typedef T element_type;

    out_ptr() :
        d(0), own(false)
    {
    }

    // ctor.
    out_ptr(T* t, bool ownership = true) :
        d(t), own(ownership)
    {
    }

    out_ptr(out_ptr const& other) :
        own(other.own)
    {
        out_ptr& o = const_cast< out_ptr& > (other);
        d = o.release();
    }

    // dtor
    ~out_ptr()
    {
        _delete();
    }

    out_ptr& operator=(out_ptr const& other)
    {
        if (this != &other)
        {
            _reset();
            _copy(other);
        }
        return *this;
    }

    T* get() const
    {
        return d;
    }

    element_type& operator*() const
    {
        return *d;
    }

    element_type* operator->() const
    {
        return d;
    }

    T* release()
    {
        own = false;
        T* ret = d;
        d = 0;
        return ret;
    }

    // Reset also resets ownership to true by default
    void reset(T* other, bool ownership = true)
    {
        _reset(other, ownership);
    }

    operator bool() const
    {
        return d != 0;
    }

private:
    void _delete()
    {
        if (own && d)
            delete d;
        d = 0;
        own = false;
    }

    void _reset(T* other, bool ownership)
    {
        _delete();
        d = other;
        own = ownership;
    }

    void _copy(out_ptr const& other)
    {
        out_ptr& o = const_cast< out_ptr& > (other);
        _reset(o.release(), other.own);
    }
};

} // mapping
} // ecorecpp

#endif // ECORECPP_OUT_PTR_HPP
