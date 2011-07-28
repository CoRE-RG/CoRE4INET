// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * serializer/serializer.hpp
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

#ifndef _ECORECPPSERIALIZER_HPP
#define _ECORECPPSERIALIZER_HPP

#include <ecore/EObject.hpp>

#include <xercesc/dom/DOM.hpp>
#include "externalstr.hpp"
#include "../mapping.hpp"

namespace ecorecpp
{
namespace serializer
{

class serializer
{
public:

    serializer(const std::string& _filen);

    virtual ~serializer();

    void serialize(::ecore::EObject_ptr obj);

protected:

    ::ecorecpp::mapping::type_traits::string_t get_type(::ecore::EObject_ptr obj) const;

    ::ecorecpp::mapping::type_traits::string_t get_reference(::ecore::EObject_ptr from, ::ecore::EObject_ptr to) const;

    void serialize_node(xercesc::DOMElement* node, ::ecore::EObject_ptr obj);

    void create_node(xercesc::DOMElement * parent, ::ecore::EObject_ptr parent_obj,
            ::ecore::EObject_ptr child_obj,
            ::ecore::EStructuralFeature_ptr ef);

    std::string m_file;

    xercesc::DOMImplementation* m_impl;
    xercesc::DOMDocument * m_doc;
    xercesc::DOMElement* m_root;
    int m_level; // current_level
    ::ecore::EObject_ptr m_root_obj;
};

} // serializer
} // ecorecpp

#endif  /* _ECORECPPSERIALIZER_HPP */
