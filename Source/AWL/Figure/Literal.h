/**
 * @file Literal.h
 */

#pragma once

#include <iostream>
#include <string>

namespace Figure
{

    using Location = size_t;

    struct Lexer;

    struct Bool
    {
        using Value = bool;

        Value value;
    };

    static inline std::ostream& operator<<(std::ostream& o, const Bool& b)
    {
        if (b.value)
        {
            o << "#t";
        }
        else
        {
            o << "#f";
        }
        return o;
    }

    struct Number
    {
        using Value = double;

        Value value;
    };

    static inline std::ostream& operator<<(std::ostream& o, const Number& n)
    {
        o << n.value;
        return o;
    }

    struct Char
    {
        using Value = char;

        Value value;

        operator Value() const
        {
            return value;
        }

        operator Value& ()
        {
            return value;
        }
    };

    static inline std::ostream& operator<<(std::ostream& o, const Char& c)
    {
        o << c.value;
        return o;
    }

    struct String
    {
        using Value = std::string;

        Value value;

        bool operator<(const String& rhs) const
        {
            return value < rhs.value;
        }
    };

    static inline std::ostream& operator<<(std::ostream& o, const String& str)
    {
        o << "\"" << str.value << "\"";
        return o;
    }

    struct Id
    {
        using Value = std::string;

        Value value;

        operator Value() const
        {
            return value;
        }

        operator Value& ()
        {
            return value;
        }

        bool operator<(const Id& rhs) const
        {
            return value < rhs.value;
        }
    };

    static inline std::ostream& operator<<(std::ostream& o, const Id& id)
    {
        o << id.value;
        return o;
    }

}