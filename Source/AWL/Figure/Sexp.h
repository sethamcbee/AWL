/**
 * @file Sexp.h
 */

#pragma once

#include <iostream>
#include <list>
#include <variant>

#include "Literal.h"

namespace Figure
{

    struct Lexer;
    struct Sexp;

    using SexpList = std::list<Sexp>;

    struct SexpVector
    {
        SexpList value;
    };

    struct Sexp
    {
        using Value = std::variant<Bool, Char, Number, String, Id, SexpList, SexpVector>;

        Value value;
        Location pos;

        Sexp(Value v, Location p);
        Sexp(Lexer& l);

        void print(std::ostream& o) const;

        void error();
        void error(std::string_view m);
    };

}