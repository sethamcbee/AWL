// Copyright of Wet Blanket Studios

#pragma once

#include "Gender.h"

#include "CoreMinimal.h"

class ALot;

class AWL_API FPersonParams
{
public:
	FPersonParams();
	~FPersonParams();

	TOptional<EGender> Gender;
	TOptional<FString> Name;
	TOptional<ALot*> Home;
	TOptional<int8> AgeYears;
	TOptional<int16> Birthday;
};

extern FPersonParams DefaultPersonParams;