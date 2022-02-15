// Copyright of Wet Blanket Studios


#include "TimeManager.h"

#include "AWLGameState.h"
#include "Date.h"
#include "Misc/MessageDialog.h"


// Sets default values for this component's properties
UTimeManager::UTimeManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTimeManager::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.SetTickFunctionEnable(false);
}


// Called every frame
void UTimeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTimeManager::SetSun(AAWLGameState* GS, AActor* Actor)
{
	GS->TimeManager->Sun = Actor;
	GS->bTimeTick = true;
	GS->TimeManager->bUpdateSun = true;
}


void UTimeManager::Update(float DeltaTime)
{
	++Ticks;

	if (bUpdateSun)
	{
		float DeltaPitch = 360.0 * DeltaTime; // deg per min
		DeltaPitch /= (float)MinuteLengthTicks; // deg/min / (ticks/min) = deg / tick

		SunPitch += DeltaPitch;
		FRotator NewRotation = FRotator(SunPitch, 0, 0.0);

		// Check if SunPitch wrapped around axis.
		if (SunPitch > 360.0)
		{
			SunPitch -= 360.0;
		}

		FQuat QuatRotation = FQuat(NewRotation);

		Sun->SetActorRotation(QuatRotation);
	}
}