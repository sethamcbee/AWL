// Copyright of Wet Blanket Studios

#pragma once

#include "Date.h"
#include "PersonParams.h"
#include "Gender.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Person.generated.h"

class ALot;
struct FAWLRand;
struct FSexp;

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

	void ToSexp(FSexp& Out) const;

	UPROPERTY(VisibleInstanceOnly)
	uint64 PersonSeed;

	UPROPERTY(VisibleInstanceOnly)
	EGender Gender;

	UPROPERTY(VisibleInstanceOnly)
	FString Name;
	
	UPROPERTY(VisibleInstanceOnly)
	ALot* Home;
	
	UPROPERTY(VisibleInstanceOnly)
	int8 AgeYears;

	UPROPERTY(VisibleInstanceOnly)
	ELifeStage LifeStage;
	
	UPROPERTY(VisibleInstanceOnly)
	int16 Birthday;
};

APerson* GeneratePerson(UWorld* World, FAWLRand& Rng, const FPersonParams& Params = DefaultPersonParams);
APerson* GenerateAdult(UWorld* World, FAWLRand& Rng, FPersonParams Params = DefaultPersonParams);
APerson* GenerateSpouse(UWorld* World, FAWLRand& Rng, APerson* Spouse, FPersonParams Params = DefaultPersonParams);
APerson* GenerateOffspring(UWorld* World, FAWLRand& Rng, APerson* Parent0, APerson* Parent1, FPersonParams Params = DefaultPersonParams);

FString AgeToString(int AgeYears);