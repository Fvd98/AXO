#include "Magnetized.h"
#include "Magnet.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values for this component's properties
UMagnetized::UMagnetized()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UMagnetized::BeginPlay()
{
	Super::BeginPlay();

	// Initiate and attach particle systems
	AttractionParticleSystem = NewObject<UParticleSystemComponent>(this, TEXT("attraction_particle_system"));
	AttractionParticleSystem->RegisterComponent();
	AttractionParticleSystem->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	AttractionParticleSystem->InitializeSystem();
	AttractionParticleSystem->InitParticles();
	AttractionParticleSystem->SetTemplate(Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, TEXT("ParticleSystem'/Game/ParticleSystems/PS_BubblePop.PS_BubblePop'"))));
	AttractionParticleSystem->DeactivateSystem();

	AttractableParticleSystem = NewObject<UParticleSystemComponent>(this, TEXT("attractable_particle_system"));
	AttractableParticleSystem->RegisterComponent();
	AttractableParticleSystem->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	AttractableParticleSystem->InitializeSystem();
	AttractableParticleSystem->InitParticles();
	AttractableParticleSystem->SetTemplate(Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, TEXT("ParticleSystem'/Game/ParticleSystems/PS_TrashGlo.PS_TrashGlo'"))));
	AttractableParticleSystem->ActivateSystem();

	// Initiate and attach collider sphere
	Collider = NewObject<USphereComponent>(this, TEXT("magnetized_collider"));
	Collider->RegisterComponent();
	Collider->InitSphereRadius(AbsorbtionRadius); //To Verify
	Collider->SetSphereRadius(AbsorbtionRadius);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionProfileName(TEXT("OverlapAll"));
	Collider->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	//prevent collision with the other actors
	GetOwnerPrimitiveRoot()->SetGenerateOverlapEvents(false);
}



// Called every frame
void UMagnetized::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetedMagnet)
	{
		FVector DirectionVector = (TargetedMagnet->Collider->GetComponentLocation() + TargetedPositionOffsetOverride.Get(TargetedPositionOffset)) - Collider->GetComponentLocation();

		float ActorsDistance = DirectionVector.Size();
		UPrimitiveComponent* PrimitiveRoot = GetOwnerPrimitiveRoot();
		// The owner actor has reach minimum distance of absorbtion from the epicenter of the collider sphere
		if (ActorsDistance < MinimumEpicenterDistanceRadiusOverride.Get(MinimumEpicenterDistanceRadius))
		{
			// cancel velocity and unset target, at this point other systems can decide what to do with the object (e.g. absorb the item in the magnet's inventory)
			ResetTargetedMagnet(true);
		}
		// The owner is pulled toward the target magnet actor
		else 
		{
			DirectionVector.Normalize(0.0001);
			// The closer the stronger the force (black hole effect)
			float AbsorbtionMultiplier = 1 - (!AbsorbtionVelocityOverride.IsSet() * (FMath::Min(ActorsDistance, TargetedMagnetRadius) / TargetedMagnetRadius));
			DirectionVector *= AbsorbtionVelocityOverride.Get(AbsorbtionVelocity) * AbsorbtionMultiplier;
			PrimitiveRoot->AddForce(DirectionVector);
		}
	}
}

void UMagnetized::ResetRootLinearVelocityWithRoot(UPrimitiveComponent* PrimitiveRoot)
{
	PrimitiveRoot->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
}

void UMagnetized::ResetRootLinearVelocity()
{
	ResetRootLinearVelocityWithRoot(GetOwnerPrimitiveRoot());
}

void UMagnetized::SetTargetedMagnet(AActor* target, UMagnet* targetMaget)
{
	TargetedMagnet = targetMaget;
	TargetedMagnetRadius = targetMaget->AbsorbtionRadius;
	if (targetMaget->AbsorbtionVelocityOverride.IsSet())
		AbsorbtionVelocityOverride = targetMaget->AbsorbtionVelocityOverride;
	if (targetMaget->MinimumEpicenterDistanceRadiusOverride.IsSet())
		MinimumEpicenterDistanceRadiusOverride = targetMaget->MinimumEpicenterDistanceRadiusOverride;
	if (targetMaget->TargetedPositionOffsetOverride.IsSet())
		TargetedPositionOffsetOverride = targetMaget->TargetedPositionOffsetOverride;
	AttractionParticleSystem->ActivateSystem();
	AttractableParticleSystem->DeactivateSystem();
	if(targetMaget->bResetMagnetizedActorOnBeginMagnetization)
		ResetRootLinearVelocity();
}

void UMagnetized::ResetTargetedMagnet(bool resetVelocity)
{
	TargetedMagnet = nullptr;
	TargetedMagnetRadius = 0;
	AttractionParticleSystem->DeactivateSystem();
	AttractableParticleSystem->ActivateSystem();
	if(resetVelocity)
		ResetRootLinearVelocity();
	AbsorbtionVelocityOverride.Reset();
	MinimumEpicenterDistanceRadiusOverride.Reset();
	TargetedPositionOffsetOverride.Reset();
}

UPrimitiveComponent* UMagnetized::GetOwnerPrimitiveRoot() {
	return Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

