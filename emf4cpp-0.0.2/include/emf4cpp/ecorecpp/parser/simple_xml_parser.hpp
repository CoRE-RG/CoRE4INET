// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * parser/simple_xml_parser.hpp
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

#ifndef _ECORECPPSIMPLEXMLPARSER_HPP
#define    _ECORECPPSIMPLEXMLPARSER_HPP

#include <deque>
#include <cassert>
#include <sstream>
#include <vector>
#include "../mapping.hpp"
#include "parser_common.hpp"
#include "reference_parser.hpp"

namespace ecorecpp
{
using namespace mapping;
using namespace parser;

namespace xml_parser
{

typedef std::pair< const type_traits::char_t*, size_t > match_pair;
typedef std::deque< std::pair< match_pair, match_pair > > attr_list_t;

// struct Handler
// {
//     virtual void processing_tag (match_pair const& tag,
//                                  attr_list_t const& attr_list) = 0;
//     virtual void start_tag (match_pair const& tag,
//                             attr_list_t const& attr_list) = 0;
//     virtual void end_tag (match_pair const& tag) = 0;
//     virtual void characters (match_pair const& chars) = 0;
// };

template<typename Handler>
struct SemanticState
{
    inline SemanticState(Handler& h_)
        : h (h_)
    {
    }

    inline void new_id(match_pair const& mp )
    {
        ids.push_back (mp);
    }

    inline void new_start_tag()
    {
        h.start_tag (ids.back(), attr_list);
        attr_list.clear();
    }

    inline void new_processing_tag()
    {
        h.processing_tag (ids.back(), attr_list);
        attr_list.clear();
        ids.pop_back();
    }


    inline void new_comment_tag()
    {
        
    }


    inline void new_end_tag ()
    {
        h.end_tag (ids.back());
        ids.pop_back();
    }

    inline void new_characters(match_pair const& mp)
    {
        h.characters (mp);
    }

    inline void new_attr ()
    {
        match_pair val = ids.back();
        ids.pop_back();
        match_pair name = ids.back();
        ids.pop_back();

        attr_list.push_back (std::make_pair (name, val));
    }

    std::deque< match_pair > ids;
    attr_list_t attr_list;
    Handler& h;
};


namespace grammar
{

// space
struct space // hand made supposed to be fast.
// : or_< char_< ' ' > , char_< '\t' > , char_< '\n' > , char_< '\r' > >
{
    template< typename S >
    static inline bool match(S & state)
    {
        if (EXPECT_FALSE (state.at_end()))
            return false;

        type_traits::char_t c = state.char_at_pos();
        bool ret = c == ' ' || c == '\n' || c == '\r' || c == '\t';
        if (ret)
            state.advance();

        return ret;
    }
};

// One or more spaces
struct spaces_: plus_< space >
{
};

struct string_:
        semantic_rule<string_,
                      seq_< char_<'"'> , star_< notchar_<'"'> >, char_<'"'> > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        match_pair mp (s.first + 1, s.second - 2);
        state.semantic_state().new_id (mp);
    }
};

struct id_ :
        semantic_rule<id_,
                      plus_ < notchar_inlist_ < '<', '>', '/', '?', ' ',
                                                 '\t', '\n', '\r', '=',
                                                 '"' > > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& s)
    {
        state.semantic_state().new_id (s);
    }
};

struct value_ : string_
{
};

struct attr_bit_ :
        semantic_rule<attr_bit_,
                      seq_< id_, opt_<spaces_>, char_<'='>, opt_<spaces_>, value_ > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const&)
    {
        state.semantic_state().new_attr();
    }
};

struct attr_list_ : seq_< or_< seq_ < attr_bit_, star_< seq_ <spaces_, attr_bit_> > >,
                               empty_
                               >, opt_<spaces_> >
{
};

// processing tag <? xxx ?>
struct processing_ :
        semantic_rule<processing_,
                        seq_< char_<'<'>, char_<'?'>,
                              opt_<spaces_>,
                              id_,
                              opt_< seq_< spaces_, attr_list_> >,
                              char_<'?'>, char_<'>'> > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const&)
    {
        state.semantic_state().new_processing_tag();
    }
};


// comment tag <!-- xxx -->
struct comment_ :
        semantic_rule<comment_,
                        seq_< seq_< char_<'<'>, char_<'!'> >,
                              star_< notchar_<'>'> >,
                              char_<'>'> > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const&)
    {
        state.semantic_state().new_comment_tag();
    }
};

// Optimization rule to minimize backtracking
struct start_tag_common_ : seq_< char_<'<'>,
                                 id_,
                                 opt_< seq_< spaces_, attr_list_ > > >
{
};

// start&end tag
struct unique_tag_end_ :
        semantic_rule<unique_tag_end_,
                      seq_<char_<'/'>, char_<'>'> > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const&)
    {
        state.semantic_state().new_start_tag();
        state.semantic_state().new_end_tag();
    }
};

// end tag
struct end_tag_ :
    semantic_rule<end_tag_,
                    seq_< char_<'<'>, char_<'/'>,
                          id_,
                          char_<'>'> > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const&)
    {
        state.semantic_state().new_end_tag();
    }
};

// start tag
struct start_tag_end_ :
        semantic_rule<start_tag_end_,
                      char_<'>'> >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const&)
    {
        state.semantic_state().new_start_tag();
    }
};

// optimization
struct start_tag_or_unique_start_ :
    seq_< start_tag_common_, or_< start_tag_end_, unique_tag_end_> >
{
};


// intersticial space between tags
struct inner_space_ :
    semantic_rule<inner_space_,
                  plus_< notchar_<'<'> > >
{
    // Semantic rule
    template< typename S >
    static inline void process_match(S& state, match_pair const& mp)
    {
        state.semantic_state().new_characters(mp);
    }
};

// an XML bit of information
struct xml_bit_ : or_ <
    start_tag_or_unique_start_,
    end_tag_,
    processing_,
    comment_,
    inner_space_
    >
{
};


struct the_xml : seq_< star_< xml_bit_ >,
                       eoi_ >
{
};


} // grammar

} // parser
} // ecorecpp

#endif    /* _ECORECPPSIMPLEXMLPARSER_HPP */
