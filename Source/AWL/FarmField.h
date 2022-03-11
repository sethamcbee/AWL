// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FarmField.generated.h"

class UFarmTileManager;

UCLASS()
class AWL_API AFarmField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFarmField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleInstanceOnly)
	UFarmTileManager* FarmTileManager;
};
