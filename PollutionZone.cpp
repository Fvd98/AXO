#include "PollutionZone.h"
#include "FritesMollesCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Spawner.h"

// Sets default values
APollutionZone::APollutionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ZoneCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Rootcomponent"));
	RootComponent = ZoneCollider;
	ZoneCollider->InitBoxExtent(FVector(150, 150, 150));
	ZoneCollider->OnComponentBeginOverlap.AddDynamic(this, &APollutionZone::OnZoneOverlapBegin);

	ZoneName = "Unnamed lands";
	CleanThreshold = 0.85;
	ZoneTrashInventory = {
		{ETrashTypes::Unsalvageable, 0},
		{ETrashTypes::EWaste, 0},
		{ETrashTypes::Plastic, 0},
		{ETrashTypes::Glass, 0},
		{ETrashTypes::Organic, 0},
		{ETrashTypes::Metal, 0},
		{ETrashTypes::Paper, 0},
	};
}

// Called when the game starts or when spawned
void APollutionZone::BeginPlay()
{
	Super::BeginPlay();

	for (auto& inventoryTypeCount : ZoneTrashInventory)
	{
		MaxPollutionUnit += (inventoryTypeCount.Value * 3);
	}

	TArray<UPrimitiveComponent*> OverlappingCollidersT;
	UKismetSystemLibrary::ComponentOverlapComponents(ZoneCollider, ZoneCollider->GetComponentTransform(), {}, UBoxComponent::StaticClass(), {}, OverlappingCollidersT);
	for (auto& OverlappingColliderT : OverlappingCollidersT)
	{
		AActor* OverlappingActorT = OverlappingColliderT->GetOwner();
		if (OverlappingActorT->IsA(ASpawner::StaticClass()))
		{
			ASpawner* SpawnerFound = (ASpawner*)OverlappingActorT;
			SpawnerFound->setZone(this);
		}
	}

	if (bStarterZone) 
	{
		AFritesMollesCharacter* Player = (AFritesMollesCharacter*)GetWorld()->GetFirstPlayerController()->GetPawn();
		if (Player) 
		{
			Player->SetZone(this);
			Player->OnPlayerChangeZone.Broadcast();
		}
			
	}
	
	PollutionUnits = MaxPollutionUnit;
}

void APollutionZone::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void APollutionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APollutionZone::OnZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AFritesMollesCharacter::StaticClass()) && OtherComp->IsA(UCapsuleComponent::StaticClass()))
	{
		AFritesMollesCharacter* OverlappingCharacter = Cast<AFritesMollesCharacter>(OtherActor);
		OverlappingCharacter->SetZone(this);
		OnPlayerEnterZone.Broadcast(this);
	}
}

TArray<TEnumAsByte<ETrashTypes>> APollutionZone::GetnextProps(TMap<TEnumAsByte<ETrashTypes>, bool> AllowedTypes, int Amount)
{
	TArray<TEnumAsByte<ETrashTypes>> nextProps;
	TArray<ETrashTypes> PossibleTypes;
	for (auto& type : AllowedTypes)
	{
		if (type.Value && ZoneTrashInventory[type.Key])
			PossibleTypes.Add(type.Key);
	}
	if (PossibleTypes.Num()) 
	{
		for (int i = 0; i < Amount; i++)
		{
			if (!PossibleTypes.Num())
				break;
			int nextPropTypeIndex = FMath::RandRange(0, PossibleTypes.Num() - 1);
			ETrashTypes nextProp = PossibleTypes[nextPropTypeIndex];
			ZoneTrashInventory[nextProp]--;
			if (!ZoneTrashInventory[nextProp])
				PossibleTypes.RemoveAt(nextPropTypeIndex);
			nextProps.Add(nextProp);
		}
	}
	//TODO: disable spawner, and subscibe it to next trash coming in for possible reactivation

	return nextProps;
}

float APollutionZone::GetPollutionLevel()
{
	return FMath::Min(1.f, PollutionUnits / MaxPollutionUnit);
}

void APollutionZone::Clean()
{
	if (!bClean) 
	{
		bClean = true;
		OnZoneCleaned.Broadcast(this);
	}
}

void APollutionZone::UpdatePollutionUnits(int addedUnits)
{
	PollutionUnits += addedUnits;

	if (!bCleanThresholdReached && (1 - PollutionUnits/MaxPollutionUnit) >= CleanThreshold)
	{
		bCleanThresholdReached = true;
		OnCleanThresholdReached.Broadcast(this);
	}
	UWorld* world = GetWorld();
	if (world) 
	{
		AFritesMollesCharacter* MainCharacterRef = (AFritesMollesCharacter*)GetWorld()->GetFirstPlayerController()->GetPawn();
		if (MainCharacterRef)
			MainCharacterRef->OnPlayerUpdatedZone.Broadcast();
	}
}

