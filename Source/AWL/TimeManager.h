// Copyright of Wet Blanket Studios

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeManager.generated.h"


class AAWLGameState;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AWL_API UTimeManager : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UTimeManager();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	static void SetSun(AAWLGameState* GS, AActor* Sun);

	void Update(float DeltaTime);

	UPROPERTY(EditInstanceOnly)
	uint64 Ticks = 0;

	UPROPERTY(EditInstanceOnly)
	bool bUpdateSun = false;

	UPROPERTY(EditInstanceOnly)
	AActor* Sun;

	UPROPERTY(EditInstanceOnly)
	float SunPitch = 180.0;
};
