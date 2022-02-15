// Copyright of Wet Blanket Studios

#pragma once

#include "Date.h"
#include "PersonParams.h"
#include "Gender.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Person.generated.h"

class ALot;
class FAWLRand;

UCLASS()
class AWL_API APerson : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	uint64 PersonSeed;

	UPROPERTY(EditInstanceOnly)
	EGender Gender;

	UPROPERTY(EditInstanceOnly)
	FString Name;
	
	UPROPERTY(EditInstanceOnly)
	ALot* Home;
	
	UPROPERTY(EditInstanceOnly)
	int8 AgeYears;

	UPROPERTY(EditInstanceOnly)
	ELifeStage LifeStage;
	
	UPROPERTY(EditInstanceOnly)
	int16 Birthday;
};

APerson* GeneratePerson(UWorld* World, FAWLRand& Rng, const FPersonParams& Params = DefaultPersonParams);
APerson* GenerateAdult(UWorld* World, FAWLRand& Rng, FPersonParams Params = DefaultPersonParams);
APerson* GenerateSpouse(UWorld* World, FAWLRand& Rng, APerson* Spouse, FPersonParams Params = DefaultPersonParams);
APerson* GenerateOffspring(UWorld* World, FAWLRand& Rng, APerson* Parent0, APerson* Parent1, FPersonParams Params = DefaultPersonParams);

FString AgeToString(int AgeYears);