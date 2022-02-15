// Copyright of Wet Blanket Studios


#include "Person.h"

#include "AWLGameState.h"
#include "AWLRand.h"
#include "Date.h"
#include "PersonParams.h"


// Sets default values
APerson::APerson()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(false);
}


// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLabel(TEXT("Person") + Name);
}


// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


APerson* GeneratePerson(UWorld* World, FAWLRand& Rng, const FPersonParams& Params)
{
	FTransform Transform;
	APerson* Person = World->SpawnActorDeferred<APerson>(APerson::StaticClass(), Transform);

	Person->PersonSeed = Rng.Peek();

	auto GS = World->GetGameState<AAWLGameState>();

	if (Params.Gender.IsSet())
	{
		Person->Gender = Params.Gender.GetValue();
	}
	else
	{
		if (Rng(0, 1))
		{
			Person->Gender = EGender::Male;
		}
		else
		{
			Person->Gender = EGender::Female;
		}
	}

	if (Params.Name.IsSet())
	{
		Person->Name = Params.Name.GetValue();
	}
	else
	{
		if (Person->Gender == EGender::Male)
		{
			Person->Name = GS->RandMaleName(Rng);
		}
		else
		{
			Person->Name = GS->RandFemaleName(Rng);
		}
	}

	if (Params.AgeYears.IsSet())
	{
		Person->AgeYears = Params.AgeYears.GetValue();
	}
	else
	{
		Person->AgeYears = Rng(0, 18);
	}

	Person->LifeStage = YearsToLifeStage(Person->AgeYears);

	Person->FinishSpawning(Transform);
	return Person;
}


APerson* GenerateAdult(UWorld* World, FAWLRand& Rng, FPersonParams Params)
{
	Params.AgeYears = RandAdultAge(Rng);
	return GeneratePerson(World, Rng, Params);
}


APerson* GenerateSpouse(UWorld* World, FAWLRand& Rng, APerson* Person, FPersonParams Params)
{
	// Later we'll check compatibility.
	auto Age = Person->AgeYears;

	auto DiffRangeYears = 6;
	auto DiffPrecision = 3;
	auto Min = Age - DiffRangeYears;
	auto Max = Age + DiffRangeYears;
	if (Max > DeathAgeYears - 1)
	{
		Max = DeathAgeYears - 1;
	}
	auto SpouseAge = Rng.Avg(Min, Max, DiffPrecision);
	if (SpouseAge < AdultAgeYears)
	{
		SpouseAge = AdultAgeYears;
	}

	Params.AgeYears = SpouseAge;

	// Determine whether couple is gay.
	if (Rng.Try(0.2))
	{
		Params.Gender = Person->Gender;
	}
	else
	{
		// Straight.
		if (Person->Gender == EGender::Male)
		{
			Params.Gender = EGender::Female;
		}
		else
		{
			Params.Gender = EGender::Male;
		}
	}

	return GeneratePerson(World, Rng, Params);
}


APerson* GenerateOffspring(UWorld* World, FAWLRand& Rng, APerson* Parent0, APerson* Parent1, FPersonParams Params)
{
	// Get age of younger parent.
	auto ParentAge = Parent0->AgeYears;
	if (Parent1->AgeYears < ParentAge)
	{
		ParentAge = Parent1->AgeYears;
	}

	// Later, we'll inherit traits. For now, we just ensure the age
	// of the offspring is logical.
	auto Min = BabyAgeYears;
	auto Max = ParentAge - AdultAgeYears;
	Params.AgeYears = Rng.Avg(Min, Max, 2);
	return GeneratePerson(World, Rng, Params);
}