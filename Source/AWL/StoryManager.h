// Copyright of Wet Blanket Studios

#pragma once

#include "Containers/Map.h" 

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StoryManager.generated.h"

class USMEvent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWL_API UStoryManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStoryManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Update(uint64 WorldTick);

	void AddEvent(uint64 Tick, USMEvent* Event);

	//UPROPERTY(VisibleInstanceOnly)
	TMultiMap<uint64, USMEvent*> Events;

	UPROPERTY(VisibleInstanceOnly)
	uint64 NextEventTick;
};
