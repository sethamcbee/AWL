// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "SMEvent.h"
#include "SMBirthdayEvent.generated.h"

class APerson;

/**
 * 
 */
UCLASS()
class AWL_API USMBirthdayEvent : public USMEvent
{
	GENERATED_BODY()
	
public:

	virtual void BeginEvent();

	UPROPERTY(VisibleInstanceOnly)
	APerson* Person;
};
