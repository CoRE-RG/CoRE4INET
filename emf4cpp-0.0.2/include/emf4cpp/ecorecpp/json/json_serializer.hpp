// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * serializer/json_serializer.hpp
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

#ifndef _ECORECPPJSON_SERIALIZER_HPP
#define _ECORECPPJSON_SERIALIZER_HPP

#include <ecore/EObject.hpp>
#include <iostream>
#include <list>
#include <cassert>

#include "../mapping.hpp"

namespace ecorecpp
{
namespace json
{

using ::ecorecpp::mapping::type_traits::string_t;
using ::ecorecpp::mapping::type_traits::char_t;

static const char_t *_indent_precalc[] = {
    "",
    "  ",
    "    ",
    "      ",
    "        ",
    "          ",
    "            ",
    "              ",
    "                ",
    "                  ",
    "                    ",
    "                      ",
    "                        ",
    "                          ",
    "                            ",
    "                              ",
    "                                ",
    "                                  ",
    "                                    ",
    "                                      "
// (dotimes (i 20) (insert "\"" (let ((s "")) (dotimes (j i) (setq s (concat "  " s))) s) "\"," #xA))
};

struct json_serializer
{
private:
    std::ostream& out;
    unsigned int level;
    std::list< bool > has_value;
    bool indent;

    inline void _indent()
    {
        if(has_value.size())
            new_line();

        unsigned int mylevel = level;
        if (level >= sizeof(_indent_precalc) / sizeof (const char_t*))
            mylevel = sizeof(_indent_precalc) / sizeof (const char_t*) - 1;
        out << _indent_precalc[mylevel];
    }

public:
    inline json_serializer(std::ostream& _out, bool ind=false) :
        out(_out), level(0), indent (ind)
    {
    }

    inline void open_object()
    {
        comma();
        _indent();
        out << "{";

        has_value.push_back(false);
        ++level;
    }

    inline void close_object()
    {
        --level;
        _indent();
        out << "}";

        has_value.pop_back();
    }

    inline void open_array()
    {
        comma();
        _indent();
        out << "[";

        has_value.push_back(false);
        ++level;
    }

    inline void close_array()
    {
        --level;
        _indent();
        out << "]";

        has_value.pop_back();
    }

    inline void add_child(const string_t& _name)
    {
        comma(false);
        _indent();
        out << "\"" << _name << "\" : ";
    }

    // TODO: template
    inline void add_attribute(const string_t& _name, const string_t& _value)
    {
        comma();
        _indent();
        out << "\"" << _name << "\" : \"" << _value << "\"";
    }

    inline void add_value(const string_t& _value)
    {
        assert(has_value.size());

        has_value.back() = true;
        out << _value;
    }

private:

    inline void comma(bool _new = true)
    {
        if (has_value.size())
        {
            if (has_value.back())
                out << ", ";

            has_value.back() = _new;
        }
    }

    inline void new_line()
    {
        out << "\n";
    }
};

} // json
} // ecorecpp

#endif /* _ECORECPPJSON_SERIALIZER_HPP */
