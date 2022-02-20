// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "SMEvent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AWL_API USMEvent : public UObject
{
	GENERATED_BODY()

public:
	USMEvent();
	~USMEvent();

	void BeginEvent();
};
