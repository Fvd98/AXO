#include "Collectable.h"
#include "PollutionZone.h"
#include "Inventory.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values for this component's properties
UCollectable::UCollectable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCollectable::BeginPlay()
{
	Super::BeginPlay();

	// Initiate and attach collider sphere
	Collider = NewObject<USphereComponent>(this, TEXT("collectable_collider"));
	Collider->RegisterComponent();
	Collider->InitSphereRadius(ColliderRadius); //To Verify
	Collider->SetSphereRadius(ColliderRadius);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionProfileName(TEXT("OverlapAll"));
	Collider->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	//prevent collision with the other actors
	Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->SetGenerateOverlapEvents(false);

	FTimerHandle Timer;
	GetOwner()->GetWorldTimerManager().SetTimer(Timer, this, &UCollectable::Expired, 25);
}

void UCollectable::Expired()
{
	bExpired = true;
	GetOwner()->Destroy();
}

void UCollectable::BeginDestroy()
{
	Super::BeginDestroy();
	if (bExpired && !bCollected)
	{
		if (Data.zone_ref) 
		{
			Data.zone_ref->UpdatePollutionUnits(1);
			Data.zone_ref->ZoneTrashInventory[Data.type] += Data.value;
		}
	}
}

// Called every frame
void UCollectable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

