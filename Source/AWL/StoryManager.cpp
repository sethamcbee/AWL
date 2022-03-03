// Copyright of Wet Blanket Studios


#include "StoryManager.h"

#include "AWLGameState.h"
#include "SMEvent.h"


// Sets default values for this component's properties
UStoryManager::UStoryManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	NextEventTick = UINT64_MAX;
}


// Called when the game starts
void UStoryManager::BeginPlay()
{
	Super::BeginPlay();

	auto GS = static_cast<AAWLGameState*>(GetWorld()->GetGameState());
	GS->bStoryManagerTick = true;
}


// Called every frame
void UStoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UStoryManager::Update(uint64 WorldTick)
{
	// Check if we have an event to begin.
	if (NextEventTick <= WorldTick && Events.Num() > 0)
	{
		USMEvent* EventToBegin = Events.CreateConstIterator()->Value;
		Events.Remove(NextEventTick);
		if (Events.Num() > 0)
		{
			auto It = Events.CreateConstIterator();
			NextEventTick = It->Key;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Out of Events"));
			NextEventTick = UINT64_MAX;
		}

		EventToBegin->BeginEvent();
	}
}


void UStoryManager::AddEvent(uint64 Tick, USMEvent* Event)
{
	if (Tick < NextEventTick)
	{
		NextEventTick = Tick;
	}
	// Todo: Check for collision.

	Events.Add(Tick, Event);
}