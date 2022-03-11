// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FarmTileManager.generated.h"

class AFarmTile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWL_API UFarmTileManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFarmTileManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<AFarmTile*> Tiles;
};
