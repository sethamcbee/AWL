// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "Misc/TVariant.h" 

namespace Figure
{
	struct Sexp;
}

struct FSexp;

struct FSexpSymbol
{
	FString Value;
};

struct FSexpString
{
	FString Value;
};

struct FSexpInt
{
	int64 Value;
};

struct FSexpUInt
{
	uint64 Value;
};

struct FSexpFloat
{
	float Value;
};

struct FSexpBool
{
	bool Value;
};

struct FSexpList
{
	TArray<FSexp> Value;
};

struct FSexp
{
	using FSexpVal = TVariant<FSexpSymbol, FSexpString, FSexpInt, FSexpUInt, FSexpFloat, FSexpBool, FSexpList>;

	FSexp();

	FSexp(const Figure::Sexp& Sexp);

	FSexp(const char* Path);

	// Convert from Figure::Sexp.
	void FromSexp(const Figure::Sexp& Sexp);

	// Convert to Figure::Sexp.
	Figure::Sexp ToSexp() const;

	void Load(const char* Path);

	void Save(const char* Path) const;

	FSexpVal Value;
};

// Helper functions.

FSexp SymbolToSexp(const FString& Symbol);
FSexp StringToSexp(const FString& String);
FSexp IntToSexp(int64 Int);
FSexp UIntToSexp(uint64 UInt);
FSexp FloatToSexp(float Float);
FSexp BoolToSexp(bool Bool);
FSexp ArrayToSexp(const TArray<FSexp>& Array);

const FString& SymbolFromSexp(const FSexp& Sexp);
const FString& StringFromSexp(const FSexp& Sexp);
int64 IntFromSexp(const FSexp& Sexp);
uint64 UIntFromSexp(const FSexp& Sexp);
float FloatFromSexp(const FSexp& Sexp);
bool BoolFromSexp(const FSexp& Sexp);
const TArray<FSexp>& ArrayFromSexp(const FSexp& Sexp);