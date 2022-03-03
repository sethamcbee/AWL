// Copyright of Wet Blanket Studios


#include "SMEvent.h"


USMEvent::USMEvent()
{
	Tick = UINT64_MAX;
}


USMEvent::~USMEvent()
{
}


bool USMEvent::operator<(const USMEvent Other) const
{
	return Tick < Other.Tick;
}


void USMEvent::BeginEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("SMEvent called"));
}