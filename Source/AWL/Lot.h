// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lot.generated.h"

class APerson;
struct FAWLRand;
struct FSexp;

UCLASS()
class AWL_API ALot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToSexp(FSexp& Out) const;

	bool IsOccupied() const;
	
	UPROPERTY(VisibleInstanceOnly)
	uint64 LotSeed;

	UPROPERTY(VisibleInstanceOnly)
	TArray<APerson*> Occupants;
};

ALot* GenerateEmptyLot(UWorld* World, FAWLRand& Rng);
ALot* GenerateLot(UWorld* World, FAWLRand& Rng);