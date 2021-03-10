#include "Prop.h"

// Sets default values
AProp::AProp()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rootcomponent"));
	RootComponent = StaticMeshComponent;
	Magnetized = CreateDefaultSubobject<UMagnetized>(TEXT("Magnetized"));
	Collectable = CreateDefaultSubobject<UCollectable>(TEXT("Collectable"));

	StaticMeshComponent->SetReceivesDecals(false);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	Magnetized->AbsorbtionVelocity = 3000;
	Magnetized->AbsorbtionRadius = 10;
	Magnetized->MinimumEpicenterDistanceRadius = 40;
	Magnetized->TargetedPositionOffset.Z = -40;
	Collectable->ColliderRadius = 10;
}

// Called when the game starts or when spawned
void AProp::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetMassScale(NAME_None, 0.1f);
	StaticMeshComponent->SetMassOverrideInKg(NAME_None, 1.0f, true);
	StaticMeshComponent->SetLinearDamping(0.0001);
	StaticMeshComponent->BodyInstance.SetPhysMaterialOverride(Cast<UPhysicalMaterial>(StaticLoadObject(UPhysicalMaterial::StaticClass(), NULL, *FString("PhysicalMaterial'/Game/PhysicsMaterials/PM_Prop.PM_Prop'"))));
}

// Called every frame
void AProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

