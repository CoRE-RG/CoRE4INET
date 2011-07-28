// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parser/handler.hpp
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
#include "simple_xml_parser.hpp"
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include <list>
#include <string>

namespace ecorecpp
{
namespace parser
{

class handler
{
public:

    handler();

    ~handler();

    void processing_tag (xml_parser::match_pair const& tag,
                         xml_parser::attr_list_t const& attr_list);

    void start_tag (xml_parser::match_pair const& tag,
                    xml_parser::attr_list_t const& attr_list);

    void end_tag (xml_parser::match_pair const& tag);

    void characters (xml_parser::match_pair const& chars);

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
    bool m_expected_reference;
    ::ecorecpp::mapping::type_traits::string_t m_expected_literal_name;

private:

    inline bool isAtCurrentNamespace(const ::ecorecpp::mapping::type_traits::string_t& _name) const
    {
        return _name.find(':') == ::ecorecpp::mapping::type_traits::string_t::npos;
    }
};

} // parser
} // ecorecpp

#endif    /* _ECORECPPPARSERHANDLER_HPP */
