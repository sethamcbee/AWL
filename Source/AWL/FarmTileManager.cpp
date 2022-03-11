// Copyright of Wet Blanket Studios


#include "FarmTileManager.h"


UFarmTileManager::UFarmTileManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UFarmTileManager::BeginPlay()
{
	Super::BeginPlay();
}


void UFarmTileManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

