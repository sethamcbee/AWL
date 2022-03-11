// Copyright of Wet Blanket Studios


#include "FarmField.h"

#include "FarmTileManager.h"


// Sets default values
AFarmField::AFarmField()
{
	PrimaryActorTick.bCanEverTick = true;

	FarmTileManager = CreateDefaultSubobject<UFarmTileManager>("UFarmTileManager");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/TemplateFloor.TemplateFloor'"));
	UStaticMesh* Asset = MeshAsset.Object;

	auto Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Comp->SetStaticMesh(Asset);
	Comp->SetupAttachment(GetRootComponent());
}


// Called when the game starts or when spawned
void AFarmField::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AFarmField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

