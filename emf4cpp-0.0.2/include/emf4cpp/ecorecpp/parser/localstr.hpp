// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parser/localstr.hpp
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

#ifndef _ECORECPPLOCALSTR_HPP
#define    _ECORECPPLOCALSTR_HPP

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

namespace ecorecpp
{
namespace parser
{

typedef std::basic_string<XMLCh> XercesString;

class localstr
{
public:
    inline localstr(const XMLCh* const toTranscode)
    {
        m_local = xercesc::XMLString::transcode(toTranscode);
    }

    inline localstr()
    : m_local(0)
    {
    }

    inline localstr(const localstr& other)
    : m_local(other.m_local)
    {
        const_cast<localstr&>(other).m_local = 0;
    }

    inline ~localstr()
    {
        if(m_local)
            xercesc::XMLString::release(&m_local);
    }

    inline const char* local() const
    {
        return m_local;
    }

private:

    char* m_local;
};

} // parser
} // ecorecpp

inline std::ostream& operator<<(std::ostream& target,
        const ::ecorecpp::parser::localstr& toDump)
{
    target << toDump.local();
    return target;
}

#endif    /* _ECORECPPLOCALSTR_HPP */
