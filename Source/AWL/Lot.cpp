// Copyright of Wet Blanket Studios


#include "Lot.h"

#include "AWLRand.h"
#include "Person.h"


// Sets default values
ALot::ALot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(false);
}


// Called when the game starts or when spawned
void ALot::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ALot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


bool ALot::IsOccupied() const
{
	return false;
}


ALot* GenerateLot(UWorld* World, FAWLRand& Rng)
{
	FTransform Transform;
	ALot* Lot = World->SpawnActorDeferred<ALot>(ALot::StaticClass(), Transform);

	Lot->LotSeed = Rng.Peek();

	bool bDone = false;
	while (!bDone)
	{
		bDone = true;

		FVector Location;
		FRotator Rotation;
		FActorSpawnParameters SpawnInfo;

		if (Rng.Try(0.3))
		{
			// Generate single.
			APerson* Single = GenerateAdult(World, Rng);
			Single->Home = Lot;
			Lot->Occupants.Add(Single);
		}
		else if (Rng.Try(0.35))
		{
			// Generate couple.
			APerson* Spouse0 = GenerateAdult(World, Rng);
			Spouse0->Home = Lot;
			Lot->Occupants.Add(Spouse0);
			APerson* Spouse1 = GenerateSpouse(World, Rng, Spouse0);
			Spouse1->Home = Lot;
			Lot->Occupants.Add(Spouse1);
		}
		else if (Rng.Try(0.35))
		{
			// Generate family.
			APerson* Spouse0 = GenerateAdult(World, Rng);
			Spouse0->Home = Lot;
			Lot->Occupants.Add(Spouse0);
			APerson* Spouse1 = GenerateSpouse(World, Rng, Spouse0);
			Spouse1->Home = Lot;
			Lot->Occupants.Add(Spouse1);
			APerson* Kid = GenerateOffspring(World, Rng, Spouse0, Spouse1);
			Kid->Home = Lot;
			Lot->Occupants.Add(Kid);
		}
		else
		{
			bDone = false;
		}
	}

	Lot->FinishSpawning(Transform);
	return Lot;
}
