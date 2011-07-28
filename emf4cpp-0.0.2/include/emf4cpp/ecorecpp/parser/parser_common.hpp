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

#ifndef _PARSER_COMMON_HPP
#define    _PARSER_COMMON_HPP

#include <deque>
#include <sstream>
#include "../mapping.hpp"

#ifdef __GNUG__
#define EXPECT_TRUE(x) __builtin_expect (x, 1)
#define EXPECT_FALSE(x) __builtin_expect (x, 0)
#else
#define EXPECT_TRUE(x) x
#define EXPECT_FALSE(x) x
#endif

namespace ecorecpp
{

namespace parser
{

using namespace mapping;

////////////////////////////////////////////////////////////////////////
// parser state
template< typename SemanticState >
struct State
{
    // For reference, the SemanticState itself.
    typedef SemanticState SemType;

    // buffer
    const type_traits::char_t* buf_;
    // actual pos
    const type_traits::char_t* pos_;
    // buf_fer length
    size_t len_;

    // The inner semantic state.
    SemanticState& ss_;

    // State stack, for backtracking
    std::deque< const type_traits::char_t* > pos_stack_;

    // ctor
    State(SemanticState& ss, const type_traits::char_t* b, size_t l)
        : buf_(b), pos_(b), len_(l), ss_(ss)
    {
    }

    SemanticState&
    semantic_state()
    {
        return ss_;
    }

    inline bool at_end() const
    {
        return static_cast< size_t > (pos_ - buf_) == len_;
    }

    inline bool match_at_pos_advance(type_traits::char_t c)
    {
        if (!at_end() && (*pos_ == c))
        {
            ++pos_;
            return true;
        }
        return false;
    }

    inline bool match_at_pos(type_traits::char_t c) const
    {
        return !at_end() && (*pos_ == c);
    }

    inline type_traits::char_t char_at_pos() const
    {
        return *pos_;
    }

    inline const type_traits::char_t* pos() const
    {
        return pos_;
    }

    inline void advance()
    {
        if (EXPECT_TRUE (!at_end()))
            ++pos_;

        // TODO: throw at_end
    }

    inline void skip(size_t how_many)
    {
        if (static_cast< size_t > (pos_ - buf_) + how_many <= len_)
            pos_ += how_many;

        // TODO: throw at_end
    }

    // Common interface
    inline void push_state()
    {
        pos_stack_.push_front(pos_);
    }

    inline void rollback()
    {
        pos_ = pos_stack_.front();
        pos_stack_.pop_front();
    }

    inline void commit()
    {
        pos_stack_.pop_front();
    }
};

////////////////////////////////////////////////////////////////////////
// parser
// based on the wonderful yard parser http://code.google.com/p/yardparser/

template< bool b >
struct identity
{
    template< typename whatever >
    static inline bool match(whatever const&)
    {
        return b;
    }
};

typedef identity< true > true_;
typedef identity< false > false_;

// lambda, empty rule
typedef true_ empty_;

// end of input
struct eoi_
{
    template< typename S >
    static inline bool match(S & state)
    {
        return state.at_end();
    }
};

template< type_traits::char_t c >
struct char_
{
    template< typename S >
    static inline bool match(S & state)
    {
        return state.match_at_pos_advance(c);
    }
};

// NOTE: I could have implemented this thing other way
// but it would need a negative match with another Truth Environment
// or something...
template< type_traits::char_t c >
struct notchar_
{
    template< typename S >
    static inline bool match(S & state)
    {
        if (EXPECT_FALSE (state.at_end()))
            return false;

        if (EXPECT_FALSE (state.match_at_pos(c)))
            return false;

        state.advance();
        return true;
    }
};

template< type_traits::char_t c0, type_traits::char_t c1,
          type_traits::char_t c2 = 0, type_traits::char_t c3 = 0,
          type_traits::char_t c4 = 0, type_traits::char_t c5 = 0,
          type_traits::char_t c6 = 0, type_traits::char_t c7 = 0,
          type_traits::char_t c8 = 0, type_traits::char_t c9 = 0,
          type_traits::char_t c10 = 0>
struct notchar_inlist_
{
    template< typename S >
    static inline bool match(S & state)
    {
        if (EXPECT_FALSE (state.at_end()))
            return false;

        type_traits::char_t c = state.char_at_pos();
        if (c == c0 || c == c1 || c == c2 || c == c3 || c == c4 ||
            c == c5 || c == c6 || c == c7 || c == c8 || c == c9 ||
            c == c10)
            return false;

        state.advance();
        return true;
    }
};


// wcharacter range, not inclusive
template< type_traits::char_t c1, type_traits::char_t c2 >
struct crange_
{
    template< typename S >
    static inline bool match(S & state)
    {
        if (EXPECT_FALSE (state.at_end()))
            return false;

        type_traits::char_t c = state.char_at_pos();
        if (EXPECT_TRUE (c >= c1 && c < c2))
        {
            state.advance();
            return true;
        }
        return false;
    }
};

// wcharacter range, inclusive
template< type_traits::char_t c1, type_traits::char_t c2 >
struct cirange_
{
    template< typename S >
    static inline bool match(S & state)
    {
        if (EXPECT_FALSE (state.at_end()))
            return false;

        type_traits::char_t c = state.char_at_pos();
        if (EXPECT_TRUE (c >= c1 && c <= c2))
        {
            state.advance();
            return true;
        }
        return false;
    }
};

struct anychar_
{
    template< typename S >
    static inline bool match(S & state)
    {
        if (EXPECT_FALSE (state.at_end()))
            return false;

        state.advance();
        return true;
    }
};

// Semantic Rule: for rules that want a process_match operation to be
// called in their A type. Usually tends to be the class itself, but
// I'll try different approaches using the state...
template< typename A, typename C0 >
struct semantic_rule
{
    template< typename S >
    static inline bool match(S & state)
    {
        const type_traits::char_t* p = state.pos();

        // Try the rule itself
        bool result;
        if (true == (result = C0::match(state)))
            A::process_match(state, std::make_pair(p, state.pos() - p));

        return result;
    }
};

// Ordered sequence of elements: abc
template< typename C0, typename C1, typename C2 = true_, typename C3 = true_,
        typename C4 = true_, typename C5 = true_, typename C6 = true_,
        typename C7 = true_ >
struct seq_
{
    template< typename S >
    static inline bool match(S & state)
    {
        state.push_state();

        bool var = C0::match(state) && C1::match(state) && C2::match(state)
                && C3::match(state) && C4::match(state) && C5::match(state)
                && C6::match(state) && C7::match(state);
        var ? state.commit() : state.rollback();

        return var;
    }
};

// Element decission: a|b
template< typename C0, typename C1, typename C2 = false_, typename C3 = false_,
        typename C4 = false_, typename C5 = false_, typename C6 = false_,
        typename C7 = false_ >
struct or_
{
    template< typename S >
    static inline bool match(S & state)
    {
        state.push_state();

        bool var = C0::match(state) || C1::match(state) || C2::match(state)
                || C3::match(state) || C4::match(state) || C5::match(state)
                || C6::match(state) || C7::match(state);

        var ? state.commit() : state.rollback();

        return var;
    }
};

// One or more repetitions: a+
template< typename C0 >
struct plus_
{
    template< typename S >
    static inline bool match(S & state)
    {
        if (!C0::match(state))
            return false;
        // Note: yes, I unroll this loop intentionally
        while (C0::match(state) && C0::match(state) && C0::match(state)
                && C0::match(state) && C0::match(state) && C0::match(state)
                && C0::match(state) && C0::match(state) && C0::match(state)
                && C0::match(state))
            ;
        return true;
    }
};

// Zero or more repetitions: a*
template< typename C0 >
struct star_
{
    template< typename S >
    static inline bool match(S & state)
    {
        while (C0::match(state) && C0::match(state) && C0::match(state)
                && C0::match(state) && C0::match(state) && C0::match(state)
                && C0::match(state) && C0::match(state) && C0::match(state)
                && C0::match(state))
            ;
        return true;
    }
};

// Optional (special star_ case): a?
template< typename C0 >
struct opt_
{
    template< typename S >
    static inline bool match(S & state)
    {
        C0::match(state);
        return true;
    }
};

}
}

#endif
