// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lot.generated.h"

class APerson;
class FAWLRand;

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

	bool IsOccupied() const;
	
	UPROPERTY(EditInstanceOnly)
	uint64 LotSeed;

	UPROPERTY(EditInstanceOnly)
	TArray<APerson*> Occupants;
};

ALot* GenerateLot(UWorld* World, FAWLRand& Rng);