/**
 * @file sexp.cc
 */

#include "Sexp.h"
#include "Lexer.h"

#include <variant>

namespace Figure
{

    Sexp::Sexp(Value v, Location p)
    {
        value = v;
        pos = p;
    }

    Sexp::Sexp(Lexer& l)
    {
        Token tok = l.get_token();
        pos = tok.pos;
        if (auto id = std::get_if<Id>(&tok.value))
        {
            value = *id;
        }
        else if (auto b = std::get_if<Bool>(&tok.value))
        {
            value = *b;
        }
        else if (auto n = std::get_if<Number>(&tok.value))
        {
            value = *n;
        }
        else if (auto c = std::get_if<Char>(&tok.value))
        {
            value = *c;
        }
        else if (auto s = std::get_if<String>(&tok.value))
        {
            value = *s;
        }
        else if (std::get_if<LeftParen>(&tok.value))
        {
            value = SexpList{};
            SexpList& list = std::get<SexpList>(value);
            tok = l.get_token();
            while (!std::get_if<RightParen>(&tok.value))
            {
                l.push_token(tok);
                Sexp element{ l };
                list.push_back(element);
                tok = l.get_token();
            }
        }
        else if (std::get_if<VectorParen>(&tok.value))
        {
            value = SexpVector{};
            SexpVector& vec = std::get<SexpVector>(value);
            SexpList& list = vec.value;
            tok = l.get_token();
            while (!std::get_if<RightParen>(&tok.value))
            {
                l.push_token(tok);
                Sexp element{ l };
                list.push_back(element);
                tok = l.get_token();
            }
        }
        else if (std::get_if<Apostrophe>(&tok.value))
        {
            value = SexpList{};
            SexpList& list = std::get<SexpList>(value);
            Sexp quote{ Id{"quote"}, pos };
            list.push_back(quote);
            Sexp quoted{ l };
            list.push_back(quoted);
        }
        else if (std::get_if<Backtick>(&tok.value))
        {
            value = SexpList{};
            SexpList& list = std::get<SexpList>(value);
            Sexp quasiquote{ Id{"quasiquote"}, pos };
            list.push_back(quasiquote);
            Sexp datum{ l };
            list.push_back(datum);
        }
        else if (std::get_if<Comma>(&tok.value))
        {
            value = SexpList{};
            SexpList& list = std::get<SexpList>(value);
            Sexp unquote{ Id{"unquote"}, pos };
            list.push_back(unquote);
            Sexp datum{ l };
            list.push_back(datum);
        }
        else if (std::get_if<CommaAt>(&tok.value))
        {
            value = SexpList{};
            SexpList& list = std::get<SexpList>(value);
            Sexp splice{ Id{"unquote-splicing"}, pos };
            list.push_back(splice);
            Sexp datum{ l };
            list.push_back(datum);
        }
        else if (std::get_if<Dot>(&tok.value))
        {
            value = Id{ "." };
        }
        else
        {
            error("Invalid datum.\n");
        }
    }

    void Sexp::print(std::ostream& o) const
    {
        if (auto id = std::get_if<Id>(&value))
        {
            o << id->value;
        }
        else if (auto b = std::get_if<Bool>(&value))
        {
            o << b->value;
        }
        else if (auto n = std::get_if<Number>(&value))
        {
            o << n->value;
        }
        else if (auto c = std::get_if<Char>(&value))
        {
            o << c->value;
        }
        else if (auto s = std::get_if<String>(&value))
        {
            o << "\"" << s->value << "\"";
        }
        else if (auto l = std::get_if<SexpList>(&value))
        {
            o << "(";
            const char* space = "";
            for (const auto& sexp : *l)
            {
                o << space;
                sexp.print(o);
                space = " ";
            }
            o << ")";
        }
        else if (auto v = std::get_if<SexpVector>(&value))
        {
            const auto& l1 = v->value;
            o << "#(";
            const char* space = "";
            for (const auto& sexp : l1)
            {
                o << space;
                sexp.print(o);
                space = " ";
            }
            o << ")";
        }
    }

    void Sexp::error()
    {
        error("Unspecified error.");
    }

    void Sexp::error(std::string_view msg)
    {
        std::cerr << "\nAt character: " << pos << std::endl;
        std::cerr << "S-exp parsing error: " << msg << std::endl;
        exit(1);
    }

}