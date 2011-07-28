// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parser/handler-xerces.hpp
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

#ifndef _ECORECPPPARSERHANDLER_HPP
#define    _ECORECPPPARSERHANDLER_HPP

#include "unresolved_reference.hpp"

#include <xercesc/sax/HandlerBase.hpp>
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <list>
#include <string>

namespace ecorecpp
{
namespace parser
{

class handler: public xercesc::HandlerBase
{
public:

    handler();

    virtual ~handler();

    void startElement(const XMLCh * const name,
            xercesc::AttributeList& attributes);

    void endElement(const XMLCh * const name);

    void characters(const XMLCh * const chars, const XMLSize_t length);

    ::ecore::EObject_ptr getRootElement();

    void resolveReferences();

protected:

    std::list< ::ecore::EObject_ptr > m_objects;
    std::list< ::ecorecpp::mapping::type_traits::string_t > m_stack;

    ::ecore::EPackage_ptr m_current_metamodel;
    ::ecorecpp::mapping::type_traits::string_t m_current_namespace;

    std::list< unresolved_reference_t > m_unresolved_references;

    int m_level;

    bool m_expected_literal;
    ::ecorecpp::mapping::type_traits::string_t m_expected_literal_name;

private:

    inline bool isAtCurrentNamespace(const ::ecorecpp::mapping::type_traits::string_t& _name);
};

} // parser
} // ecorecpp

#endif    /* _ECORECPPPARSERHANDLER_HPP */
