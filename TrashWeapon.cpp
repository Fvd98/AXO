#include "TrashWeapon.h"
#include "Trash.h"
#include "ThirdPersonCamera.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "GameFramework/Character.h"

ATrashWeapon::ATrashWeapon() 
{

}

void ATrashWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Find all trajectory points
	TArray<UActorComponent*> comps = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (size_t i = 0; i < comps.Num(); i++)
	{
		if (comps[i]->ComponentHasTag(TrajectoryMeshTag))
		{
			TrajectoryMeshes.Add(Cast<UStaticMeshComponent>(comps[i]));
		}
	}
}

void ATrashWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsHidden())
	{
		// Update spline comp
		FVector Direction = Super::GetFireDirection(PlayerCamera->GetForwardVector(), PlayerCamera->GetComponentLocation());
		UpdateSplinePositions(Direction, DefaultVelocity, GetWorld()->GetGravityZ());
	}
}

void ATrashWeapon::Fire(FVector FireDirection)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UInventory* PlayerInventory = Cast<UInventory>(Player->GetComponentByClass(UInventory::StaticClass()));
	UThirdPersonCamera* FoundPlayerCamera = Cast<UThirdPersonCamera>(Player->GetComponentByClass(UThirdPersonCamera::StaticClass()));
	if (PlayerInventory && FoundPlayerCamera)
	{
		// Set the trash projectile's direction
		FTransform SpawnTransform = GetTransform();
		SpawnTransform.SetRotation(FireDirection.ToOrientationQuat());

		CurrentShootedTrash = PlayerInventory->GetSelectedUnsortedItem();
		if (CurrentShootedTrash.value > 0)
		{
			AProp* Prop = ULootable::GetSpawnableProp(GetWorld(), SpawnTransform, CurrentShootedTrash);
			Prop->Collectable->bPlayerCreated = true;
			Prop->FinishSpawning(SpawnTransform);

			// yeets the prop's root component
			UStaticMeshComponent* PropRoot = Cast<UStaticMeshComponent>(Prop->GetRootComponent());

			FireDirection.Normalize();
			FireDirection *= DefaultVelocity;

			PropRoot->AddImpulse(FireDirection, NAME_None, true);

			PlayerInventory->PopSelectedUnsortedItem();

			// Wrap that up
			FireCooldown = GetWorld()->GetRealTimeSeconds() + 0;//(1.0f / FireRate);
		}
	}

	ShouldFire = false;
	HasFired = true;
}

void ATrashWeapon::UpdateSplinePositions(FVector Direction, float Velocity, float Gravity) 
{
	FVector HorizontalDirection = EndPoint - GetActorLocation();
	HorizontalDirection.Z = 0;
	
	// Magic number cause I'm desperate
	Velocity *= 2;
	Velocity /= 3;

	// velocities

	float CurrentX = 0;
	float CurrentY = 0;

	// Find the middle point.
	// Approximate how much time it takes to reach EndPoint, half that, calculate x,y from it.
	float Distance = FVector::Distance(GetActorLocation(), EndPoint);
	float TimeToReach = Distance / Velocity;
	float Angle = FMath::DegreesToRadians(Direction.Rotation().Pitch);
	FVector CurrentDirection = Direction;

	for (size_t i = 0; i < TrajectoryMeshes.Num(); i++)
	{
		float iteration = float(i);
		float num = float(TrajectoryMeshes.Num());
		float CurrentTtr = ((TimeToReach / num) * iteration);

		CurrentX = Velocity * CurrentTtr * FMath::Cos(Angle);
		CurrentY = (Velocity * CurrentTtr * FMath::Sin(Angle)) - ((0.5f) * FMath::Abs(Gravity) * FMath::Pow(CurrentTtr, 2));

		HorizontalDirection.Normalize();
		FVector Location = GetActorLocation() + (HorizontalDirection * CurrentX);
		Location.Z += CurrentY;

		TrajectoryMeshes[i]->SetWorldLocation(Location);
	}
}

void ATrashWeapon::SetWeaponVisibility(bool bVisible) 
{
	Super::SetWeaponVisibility(bVisible);
	for (size_t i = 0; i < TrajectoryMeshes.Num(); i++)
	{
		TrajectoryMeshes[i]->SetVisibility(bVisible);
	}
}