// Copyright of Wet Blanket Studios


#include "FSexp.h"

#include "Figure/Lexer.h"
#include "Figure/Sexp.h"

#include <fstream>
#include <iostream>
#include <variant>


FSexp::FSexp()
{}


FSexp::FSexp(const Figure::Sexp& Sexp)
{
	FromSexp(Sexp);
}


FSexp::FSexp(const char* Path)
{
	Load(Path);
}


void FSexp::FromSexp(const Figure::Sexp& Sexp)
{
	auto Sval = &Sexp.value;
	if (const Figure::Bool* B = std::get_if<Figure::Bool>(Sval))
	{
		FSexpBool BValue{ B->value };
		Value.Set<FSexpBool>(BValue);
	}
	else if (const Figure::Char* C = std::get_if<Figure::Char>(Sval))
	{
		// Error.
	}
	else if (const Figure::Number* N = std::get_if<Figure::Number>(Sval))
	{
		FSexpInt NValue{ N->value };
		Value.Set<FSexpInt>(NValue);
	}
	else if (const Figure::String* Str = std::get_if<Figure::String>(Sval))
	{
		FSexpString StrValue{ Str->value.c_str() };
		Value.Set<FSexpString>(StrValue);
	}
	else if (const Figure::Id* Sym = std::get_if<Figure::Id>(Sval))
	{
		// Check if this is a real symbol.
		const char* CStr = Sym->value.c_str();
		if (CStr[0] == '_')
		{
			if (CStr[1] == 'f')
			{
				std::string FloatString = CStr + 2;
				FSexpFloat FloatValue{ std::stof(FloatString) };
				Value.Set<FSexpFloat>(FloatValue);
			}
			else if (CStr[1] == 'u')
			{
				std::string UIntString = CStr + 2;
				FSexpUInt UIntValue{ std::stoull(UIntString) };
				Value.Set<FSexpUInt>(UIntValue);
			}
			else
			{
				// Error.
			}
		}
		else
		{
			FSexpSymbol SymValue{ Sym->value.c_str() };
			Value.Set<FSexpSymbol>(SymValue);
		}
	}
	else if (const Figure::SexpList* L = std::get_if<Figure::SexpList>(Sval))
	{
		FSexpList LValue;
		for (const auto& Element : *L)
		{
			FSexp SubSexp(Element);
			LValue.Value.Add(SubSexp);
		}
		Value.Set<FSexpList>(LValue);
	}
	else
	{
		// Error.
	}
}


Figure::Sexp FSexp::ToSexp() const
{
	if (auto Symbol = Value.TryGet<FSexpSymbol>())
	{
		std::string Str = TCHAR_TO_UTF8(*Symbol->Value);
		Figure::Id Id{ Str };
		return Figure::Sexp{ Id, 0 };
	}
	else if (auto String = Value.TryGet<FSexpString>())
	{
		std::string Str = TCHAR_TO_UTF8(*Symbol->Value);
		Figure::String S{ Str };
		return Figure::Sexp{ S, 0 };
	}
	else if (auto Int = Value.TryGet<FSexpInt>())
	{
		int I = Int->Value;
		Figure::Number N{ I };
		return Figure::Sexp{ N, 0 };
	}
	else if (auto UInt = Value.TryGet<FSexpUInt>())
	{
		int I = UInt->Value;
		Figure::Id Id{ "_u" };
		Id.value += std::to_string(I);
		return Figure::Sexp{ Id, 0 };
	}
	else if (auto Float = Value.TryGet<FSexpFloat>())
	{
		float F = Float->Value;
		Figure::Id Id{ "_f" };
		Id.value += std::to_string(F);
		return Figure::Sexp{ Id, 0 };
	}
	else if (auto Bool = Value.TryGet<FSexpBool>())
	{
		bool B = Bool->Value;
		Figure::Bool BV{ B };
		return Figure::Sexp{ BV, 0 };
	}
	else if (auto List = Value.TryGet<FSexpList>())
	{
		Figure::SexpList SList;
		for (const FSexp& Element : List->Value)
		{
			Figure::Sexp SElement{ Element.ToSexp() };
			SList.push_back(SElement);
		}
		return Figure::Sexp{ SList, 0 };
	}
	else
	{
		// Error.
		Figure::Id Id{ "ERROR" };
		return Figure::Sexp{ Id, 0 };
	}
}


void FSexp::Load(const char* Path)
{
	auto File = std::ifstream(Path);
	auto Lexer = Figure::Lexer(File);
	auto Sexp = Figure::Sexp(Lexer);
	FromSexp(Sexp);
}


void FSexp::Save(const char* Path) const
{
	auto File = std::ofstream(Path);
	ToSexp().print(File);
}


FSexp SymbolToSexp(const FString& Symbol)
{
	FSexp Sexp;
	Sexp.Value.Set<FSexpSymbol>(FSexpSymbol{ Symbol });
	return Sexp;
}


FSexp StringToSexp(const FString& String)
{
	FSexp Sexp;
	Sexp.Value.Set<FSexpString>(FSexpString{ String });
	return Sexp;
}


FSexp IntToSexp(int64 Int)
{
	FSexp Sexp;
	Sexp.Value.Set<FSexpInt>(FSexpInt{ Int });
	return Sexp;
}


FSexp UIntToSexp(uint64 UInt)
{
	FSexp Sexp;
	Sexp.Value.Set<FSexpUInt>(FSexpUInt{ UInt });
	return Sexp;
}


FSexp FloatToSexp(float Float)
{
	FSexp Sexp;
	Sexp.Value.Set<FSexpFloat>(FSexpFloat{ Float });
	return Sexp;
}


FSexp BoolToSexp(bool Bool)
{
	FSexp Sexp;
	Sexp.Value.Set<FSexpBool>(FSexpBool{ Bool });
	return Sexp;
}


FSexp ArrayToSexp(const TArray<FSexp>& Array)
{
	FSexp Sexp;
	Sexp.Value.Set<FSexpList>(FSexpList{ Array });
	return Sexp;
}


const FString& SymbolFromSexp(const FSexp& Sexp)
{
	return Sexp.Value.Get<FSexpSymbol>().Value;
}


const FString& StringFromSexp(const FSexp& Sexp)
{
	return Sexp.Value.Get<FSexpString>().Value;
}


int64 IntFromSexp(const FSexp& Sexp)
{
	return Sexp.Value.Get<FSexpInt>().Value;
}


uint64 UIntFromSexp(const FSexp& Sexp)
{
	return Sexp.Value.Get<FSexpUInt>().Value;
}


float FloatFromSexp(const FSexp& Sexp)
{
	return Sexp.Value.Get<FSexpFloat>().Value;
}


bool BoolFromSexp(const FSexp& Sexp)
{
	return Sexp.Value.Get<FSexpBool>().Value;
}


const TArray<FSexp>& ArrayFromSexp(const FSexp& Sexp)
{
	return Sexp.Value.Get<FSexpList>().Value;
}