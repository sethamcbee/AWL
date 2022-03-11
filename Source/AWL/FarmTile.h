// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FarmTile.generated.h"

UCLASS()
class AWL_API AFarmTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
