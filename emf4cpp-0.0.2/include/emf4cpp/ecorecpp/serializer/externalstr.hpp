// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * serializer/externalstr.hpp
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

#ifndef _ECORECPPEXTERNALSTR_HPP
#define _ECORECPPEXTERNALSTR_HPP

#include <xercesc/util/XMLString.hpp>
#include <string>

namespace ecorecpp
{
namespace serializer
{

class externalstr
{
public:

    inline externalstr(const char* const toTranscode)
    {
        m_unicode = xercesc::XMLString::transcode(toTranscode);
    }

    inline externalstr(const std::string& toTranscode)
    {
        m_unicode = xercesc::XMLString::transcode(toTranscode.c_str());
    }

    inline ~externalstr()
    {
        xercesc::XMLString::release(&m_unicode);
    }

    inline const XMLCh* unicode() const
    {
        return m_unicode;
    }

private:

    XMLCh* m_unicode;
};

} // serializer
} // ecorecpp

#endif  /* _ECORECPPEXTERNALSTR_HPP */
