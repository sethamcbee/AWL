// Copyright of Wet Blanket Studios

#pragma once

#include "Date.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeManager.generated.h"

class AAWLGameState;
class UTimeManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMinuteUpdateDelegate, int, Minute);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHourUpdateDelegate, int, Hour);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDayUpdateDelegate, int, Day);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSeasonUpdateDelegate, ESeason, Season);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FYearUpdateDelegate, int, Year);

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
	static void RegisterSun(AAWLGameState* GS, AActor* Sun);

	void Update(float DeltaTime);

	void UpdateClocks(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void ForceUpdateClocks();

	UPROPERTY(BlueprintAssignable)
	FMinuteUpdateDelegate UpdateMinutes;

	UPROPERTY(BlueprintAssignable)
	FHourUpdateDelegate UpdateHours;

	UPROPERTY(BlueprintAssignable)
	FDayUpdateDelegate UpdateDays;

	UPROPERTY(BlueprintAssignable)
	FSeasonUpdateDelegate UpdateSeasons;

	UPROPERTY(BlueprintAssignable)
	FYearUpdateDelegate UpdateYears;

	UPROPERTY(VisibleInstanceOnly)
	uint64 Ticks = 0;

	UPROPERTY(VisibleInstanceOnly)
	uint64 WorldTick;

	UPROPERTY()
	float TimeSinceLastMinute;

	UPROPERTY()
	int Minute;

	UPROPERTY()
	int Hour;

	UPROPERTY()
	int Day;

	UPROPERTY()
	ESeason Season;

	UPROPERTY()
	int Year;

	UPROPERTY(VisibleInstanceOnly)
	bool bUpdateSun = false;

	UPROPERTY(VisibleInstanceOnly)
	AActor* Sun;

	UPROPERTY(VisibleInstanceOnly)
	float TOD;
};