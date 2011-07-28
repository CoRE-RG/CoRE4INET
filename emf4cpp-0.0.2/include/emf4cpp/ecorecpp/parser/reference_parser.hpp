// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parser/reference_parser.hpp
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

#ifndef _ECORECPPPARSERREF_HPP
#define    _ECORECPPPARSERREF_HPP

#include <cassert>
#include <sstream>
#include <vector>
#include "parser_common.hpp"

namespace ecorecpp
{
namespace ref_parser
{
using namespace parser;

typedef std::pair< const ::ecorecpp::mapping::type_traits::char_t*, size_t > match_pair;

struct path_item
{
    ::ecorecpp::mapping::type_traits::string_t m_id;
    int m_index;
    ::ecorecpp::mapping::type_traits::string_t m_constraintKey;
    ::ecorecpp::mapping::type_traits::string_t m_constraintValue;

    inline path_item(const ::ecorecpp::mapping::type_traits::string_t& id,
                     int index,
                     const ::ecorecpp::mapping::type_traits::string_t& constraintKey,
                     const ::ecorecpp::mapping::type_traits::string_t& constraintValue)
        : m_id(id), m_index(index), m_constraintKey(constraintKey), m_constraintValue(constraintValue)
    {
    }

    inline bool is_collection()
    {
        return (m_index != -1) || !m_constraintKey.empty();
    }

    inline ::ecorecpp::mapping::type_traits::string_t& get_id()
    {
        return m_id;
    }

    inline int get_index()
    {
        return m_index;
    }

    inline ::ecorecpp::mapping::type_traits::string_t& get_constraintKey()
    {
        return m_constraintKey;
    }

    inline ::ecorecpp::mapping::type_traits::string_t& get_constraintValue()
    {
        return m_constraintValue;
    }
};

typedef std::vector< path_item > path_t;

struct processed_reference_t
{
    ::ecorecpp::mapping::type_traits::string_t m_package;
    ::ecorecpp::mapping::type_traits::string_t m_type;
    ::ecorecpp::mapping::type_traits::string_t m_uri;
    path_t m_path;

    inline path_t& get_path()
    {
        return m_path;
    }

    inline ::ecorecpp::mapping::type_traits::string_t& get_uri()
    {
        return m_uri;
    }

    inline ::ecorecpp::mapping::type_traits::string_t& get_type()
    {
        return m_type;
    }

    inline ::ecorecpp::mapping::type_traits::string_t& get_package()
    {
        return m_package;
    }
};

typedef std::vector< processed_reference_t > references_t;

struct SemanticState
{
    inline SemanticState()
        : m_current_index(-1)
    {
    }

    inline void new_type()
    {
        assert(m_current_id.size() == 2);
        m_current.m_package = m_current_id[0];
        m_current.m_type = m_current_id[1];
        m_current_id.clear();
    }

    inline void new_uri(const ::ecorecpp::mapping::type_traits::string_t & _uri)
    {
        m_current.m_uri = _uri;
    }

    inline void new_id(const ::ecorecpp::mapping::type_traits::string_t & _id)
    {
        m_current_id.push_back(_id);
    }

    inline void new_index(int _index)
    {
        m_current_index = _index;
    }

    inline void new_constraintKey(const ::ecorecpp::mapping::type_traits::string_t & _constraintKey)
    {
        m_current_constraintKey = _constraintKey;
    }

    inline void new_constraintValue(const ::ecorecpp::mapping::type_traits::string_t & _constraintValue)
    {
        m_current_constraintValue = _constraintValue;
    }

    inline void new_path_item()
    {
        m_current.m_path.push_back(path_item(m_current_id.back(), m_current_index, m_current_constraintKey, m_current_constraintValue));
        m_current_id.clear();
        m_current_index = -1;
        m_current_constraintKey.clear();
        m_current_constraintValue.clear();
    }

    inline void new_reference()
    {
        m_references.push_back(m_current);
        m_current = processed_reference_t();
    }

    std::vector< ::ecorecpp::mapping::type_traits::string_t > m_current_id;
    int m_current_index;
    ::ecorecpp::mapping::type_traits::string_t m_current_constraintKey;
    ::ecorecpp::mapping::type_traits::string_t m_current_constraintValue;

    processed_reference_t m_current;
    references_t m_references;

    inline references_t& get_references()
    {
        return m_references;
    }
};


namespace grammar
{

// space
struct space: or_< char_< ' ' > , char_< '\t' > , char_< '\n' > , char_< '\r' > >
{
};

// One or more spaces
struct spaces_: plus_< space >
{
};

struct letter_: or_< cirange_< 'A', 'Z' > , cirange_< 'a', 'z' > >
{
};

struct word_: plus_< letter_ >
{
};

struct digit_: cirange_< '0', '9' >
{
};

struct number_: plus_< digit_ >
{
};

struct id_: semantic_rule< id_,
                           seq_< letter_, star_< or_< letter_, digit_ > > > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        ::ecorecpp::mapping::type_traits::string_t _item(s.first, s.second);
        state.semantic_state().new_id(_item);
    }
};

struct index_ : semantic_rule< index_, number_ >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        ::ecorecpp::mapping::type_traits::string_t _item(s.first, s.second);
        ::ecorecpp::mapping::type_traits::stringstream_t _ss(_item);
        int _index;
        _ss >> _index;
        state.semantic_state().new_index(_index);
    }
};

struct constraintKey_ : semantic_rule< constraintKey_,
                   star_<
                       notchar_< '=' >
                       >
                   >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        ::ecorecpp::mapping::type_traits::string_t _item(s.first, s.second);
        state.semantic_state().new_constraintKey(_item);
    }
};

struct constraintValue_ : semantic_rule< constraintValue_,
                   star_<
                       notchar_< '\'' >
                       >
                   >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        ::ecorecpp::mapping::type_traits::string_t _item(s.first, s.second);
        state.semantic_state().new_constraintValue(_item);
    }
};

struct constraint_ : semantic_rule< constraint_,
                   seq_<
                       char_< '[' >,
                       constraintKey_,
                       char_< '=' >,
                       char_< '\'' >,
                       constraintValue_,
                       char_< '\'' >,
                       char_< ']' >
                       >
                   >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
    }
};

struct path_item:
    semantic_rule< path_item,
                   seq_<
                       char_< '/' >,
                       or_<
                           id_,
                           seq_<
                               char_< '@' >,
                               id_,
                               opt_< 
                                   or_<
                                       seq_<
                                           char_<'.'>,
                                           index_
                                           >,
                                       constraint_
                                       >
                                   >
                               >
                           >
                       >
                   >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        state.semantic_state().new_path_item();
    }
};

struct path: semantic_rule< path,
                            seq_< char_< '/' > , star_< path_item > > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        // Nothing to do
    }
};

struct type_: semantic_rule< type_,
                             seq_< id_, char_< ':' > , id_ > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        state.semantic_state().new_type();
    }
};

struct uri_: semantic_rule< uri_,
                            plus_< notchar_< '#' > > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        ::ecorecpp::mapping::type_traits::string_t _uri(s.first, s.second);
        state.semantic_state().new_uri(_uri);
    }
};

struct reference: semantic_rule<
    reference,
    seq_<
        opt_< spaces_ > ,
        or_<
            seq_ <
                opt_<
                    or_<
                        seq_<
                            type_,
                            spaces_,
                            uri_
                            >,
                        uri_
                        >
                    >,
                char_< '#' >,
                path
                >,
            path
            >,
        opt_< spaces_ >
        >
    >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        state.semantic_state().new_reference();
    }
};

struct references: plus_< reference >
{
};

} // grammar

} // ref_parser
} // ecorecpp

#endif    /* _ECORECPPPARSERREF_HPP */
