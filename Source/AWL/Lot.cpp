// Copyright of Wet Blanket Studios


#include "Lot.h"

#include "AWLGameState.h"
#include "AWLRand.h"
#include "FSexp.h"
#include "Person.h"


// Sets default values
ALot::ALot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(false);

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/TemplateFloor.TemplateFloor'"));
	UStaticMesh* Asset = MeshAsset.Object;

	auto Comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Comp->SetStaticMesh(Asset);
	Comp->SetupAttachment(GetRootComponent());
}


// Called when the game starts or when spawned
void ALot::BeginPlay()
{
	static float Height = 20.0;
	static float Gap = 15.0 * 100;
	static float Scale = 0.3;

	Super::BeginPlay();

	auto GS = static_cast<AAWLGameState*>(GetWorld()->GetGameState());

	// Transform.
	auto NewTransform = GetRootComponent()->GetComponentTransform();
	auto NewTranslation = NewTransform.GetTranslation();
	auto NewScale = NewTransform.GetScale3D();

	NewTranslation.X = GS->LotOffset;
	NewTranslation.Y = GS->WorldRand(-2000, 2000);
	NewTranslation.Z = Height;
	NewScale *= Scale;
	NewTransform.SetTranslationAndScale3D(NewTranslation, NewScale);
	GetRootComponent()->SetWorldTransform(NewTransform);

	// Iterate.
	GS->LotOffset += Gap;
}


// Called every frame
void ALot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALot::ToSexp(FSexp& Out) const
{
	TArray<FSexp> ExpArray;

	FSexp SeedExp = UIntToSexp(LotSeed);
	ExpArray.Add(SeedExp);

	Out = ArrayToSexp(ExpArray);
}


bool ALot::IsOccupied() const
{
	return false;
}


ALot* GenerateEmptyLot(UWorld* World, FAWLRand& Rng)
{
	return World->SpawnActor<ALot>(ALot::StaticClass());
}


ALot* GenerateLot(UWorld* World, FAWLRand& Rng)
{
	FTransform Transform;
	ALot* Lot = World->SpawnActorDeferred<ALot>(ALot::StaticClass(), Transform);

	Lot->LotSeed = Rng.Peek();

	bool bDone = false;
	while (!bDone)
	{
		bDone = true;

		FVector Location;
		FRotator Rotation;
		FActorSpawnParameters SpawnInfo;

		if (Rng.Try(0.3))
		{
			// Generate single.
			APerson* Single = GenerateAdult(World, Rng);
			Single->Home = Lot;
			Lot->Occupants.Add(Single);
		}
		else if (Rng.Try(0.35))
		{
			// Generate couple.
			APerson* Spouse0 = GenerateAdult(World, Rng);
			Spouse0->Home = Lot;
			Lot->Occupants.Add(Spouse0);
			APerson* Spouse1 = GenerateSpouse(World, Rng, Spouse0);
			Spouse1->Home = Lot;
			Lot->Occupants.Add(Spouse1);
		}
		else if (Rng.Try(0.35))
		{
			// Generate family.
			APerson* Spouse0 = GenerateAdult(World, Rng);
			Spouse0->Home = Lot;
			Lot->Occupants.Add(Spouse0);
			APerson* Spouse1 = GenerateSpouse(World, Rng, Spouse0);
			Spouse1->Home = Lot;
			Lot->Occupants.Add(Spouse1);
			APerson* Kid = GenerateOffspring(World, Rng, Spouse0, Spouse1);
			Kid->Home = Lot;
			Lot->Occupants.Add(Kid);
		}
		else
		{
			bDone = false;
		}
	}

	Lot->FinishSpawning(Transform);
	return Lot;
}
