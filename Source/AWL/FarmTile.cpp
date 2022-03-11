// Copyright of Wet Blanket Studios


#include "FarmTile.h"


AFarmTile::AFarmTile()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/TemplateFloor.TemplateFloor'"));
	UStaticMesh* Asset = MeshAsset.Object;

	auto Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Comp->SetStaticMesh(Asset);
	Comp->SetupAttachment(GetRootComponent());
}


void AFarmTile::BeginPlay()
{
	static float Scale = 0.03;

	Super::BeginPlay();

	auto NewTransform = GetRootComponent()->GetComponentTransform();
	auto OldScale = NewTransform.GetScale3D();
	auto NewScale = OldScale * Scale;
	NewTransform.SetScale3D(NewScale);
	GetRootComponent()->SetWorldTransform(NewTransform);
}


void AFarmTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

