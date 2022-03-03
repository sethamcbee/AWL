// Copyright of Wet Blanket Studios


#include "SMBirthdayEvent.h"

#include "AWLGameState.h"
#include "Person.h"
#include "StoryManager.h"
#include "TimeManager.h"


void USMBirthdayEvent::BeginEvent()
{
	Person->AgeYears += 1;

	// Add birthday for next year.
	auto GS = Person->GetWorld()->GetGameState<AAWLGameState>();
	Tick += YearsToTicks(1);
	GS->StoryManager->AddEvent(this);

	UE_LOG(LogTemp, Warning, TEXT("Birthday event"));
}
