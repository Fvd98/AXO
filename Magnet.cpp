#include "Magnet.h"
#include "Magnetized.h"

// Sets default values for this component's properties
UMagnet::UMagnet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UMagnet::BeginPlay()
{
	Super::BeginPlay();

	// Initiate and attach collider sphere
	Collider = NewObject<USphereComponent>(this, TEXT("magnet_collider"));
	Collider->RegisterComponent();
	Collider->InitSphereRadius(AbsorbtionRadius); //To Verify
	Collider->SetSphereRadius(AbsorbtionRadius);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionProfileName(TEXT("OverlapAll"));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &UMagnet::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &UMagnet::OnOverlapEnd);
	Collider->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void UMagnet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UMagnetized* OverlappingMagnitizedItem = Cast<UMagnetized>(OtherActor->GetComponentByClass(UMagnetized::StaticClass()));
	// If the overlapping actor is a magnetized actor and it's priority is higher or equal, sets this magnet actor as the targeted magnet to which pull the owner actor to
	if (OverlappingMagnitizedItem)
	{
		if (!OverlappingMagnitizedItem->TargetedMagnet || (OverlappingMagnitizedItem->TargetedMagnet && OverlappingMagnitizedItem->TargetedMagnet->AbsorbtionPriority <= AbsorbtionPriority)) {
			OverlappingMagnitizedItem->SetTargetedMagnet(GetOwner(), this);
		}
	}
}

void UMagnet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UMagnetized* OverlappingMagnitizedItem = Cast<UMagnetized>(OtherActor->GetComponentByClass(UMagnetized::StaticClass()));
	// If the overlapping actor is a magnetized actor and is targeting this magnet actor, cancel velocity and unset magnet
	if (OverlappingMagnitizedItem && OverlappingMagnitizedItem->TargetedMagnet && OverlappingMagnitizedItem->TargetedMagnet->GetOwner() == GetOwner())
	{
		OverlappingMagnitizedItem->ResetTargetedMagnet(false);
	}
}


// Called every frame
void UMagnet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Tick currently disabled for this compoenent, reactivate above
}

