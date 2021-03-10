// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	HasFired = false;

	FireCooldown = GetWorld()->GetRealTimeSeconds();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ShouldFire)
	{
		Fire(GetFireDirection(PlayerCamera->GetForwardVector(), PlayerCamera->GetComponentLocation()));
	}
	else
	{
		HasFired = false;
	}
}

// When fire is pressed
void AWeapon::PressFire()
{
	if (FireCooldown < GetWorld()->GetRealTimeSeconds())
	{
		ShouldFire = true;
	}
}

// When fire is released
void AWeapon::ReleaseFire()
{
}

void AWeapon::PressAltFire()
{
}

void AWeapon::ReleaseAltFire()
{
}

// Called when the weapon should fire
void AWeapon::Fire(FVector FireDirection)
{
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Name = "WeaponProjectile";

	// Set the projectile's direction
	FTransform SpawnTransform = GetTransform();
	SpawnTransform.SetRotation(FireDirection.ToOrientationQuat());

	AProjectile* Projectile = (AProjectile*)GetWorld()->SpawnActor<AProjectile>(ProjectileRef, SpawnTransform);

	// Wrap that up
	FireCooldown = GetWorld()->GetRealTimeSeconds() + (1.0f / FireRate);

	// Set fire to false. This is a semi-automatic weapon. An auto-weapon will override this function anyways.
	ShouldFire = false;
	HasFired = true;
}

FVector AWeapon::GetFireDirection(FVector CameraDirection, FVector CameraPosition)
{
	// Prepare for raycast
	FHitResult* HitResult = new FHitResult();
	// Only go forwards from the player
	FVector StartTrace = CameraPosition + (CameraDirection * (PlayerCameraSpringArm->TargetArmLength * 1.25));
	FVector EndTrace = ((CameraDirection * MaxAccurateRange) + StartTrace);
	FVector FireDirection;
	FCollisionQueryParams TraceParams = FCollisionQueryParams();

	bool hasHit = GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams);
	// If we hit something lined up with the crosshair
	if (hasHit)
	{
		EndPoint = HitResult->ImpactPoint;
	}
	else
	{
		// Else, just fire towards the center of the crosshair plus the max range's distance
		EndPoint = EndTrace;
	}

	// Prepare for gravity compensation algorithm

	FString text;
	// Find velocity
	float Vel;
	AProjectile* Projectile = Cast<AProjectile>(ProjectileRef);
	if (Projectile)
	{
		Vel = Projectile->Velocity;
		text = FString::SanitizeFloat(Vel);
	}
	else
	{
		Vel = DefaultVelocity;
		text = FString::SanitizeFloat(Vel);
	}

	// Find gravity
	float G = GetWorld()->GetGravityZ();
	if (Projectile)
	{
		G *= Projectile->ProjectileMovementComp->ProjectileGravityScale;
	}
	text = FString::SanitizeFloat(G);

	// Find the horizontal and vertical targets
	float Dx = FVector::Distance(GetActorLocation(), EndPoint);
	float Dy = EndPoint.Z - GetActorLocation().Z;
	float Vel2 = FMath::Pow(Vel, 2);
	float Vel4 = FMath::Pow(Vel, 4);

	// Finally, compensate for gravity. FUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU
	float TargetAngle;
	float ToRoot = (Vel4 - G * ((G*FMath::Pow(Dx, 2)) + (2 * Dy*Vel2)));
	if (ToRoot >= 0.0f)
	{
		float TargetAngleA = FMath::Atan((Vel2 + FMath::Sqrt(ToRoot)) / (G * Dx));
		float TargetAngleB = FMath::Atan((Vel2 - FMath::Sqrt(ToRoot)) / (G * Dx));
		TargetAngle = FMath::Min(TargetAngleA, TargetAngleB);
		TargetAngle = FMath::RadiansToDegrees(TargetAngle);
		TargetAngle = FMath::Min(MaxAngleOfLaunch, TargetAngle + 90);
		text = FString::SanitizeFloat(TargetAngle);
	}
	else
	{
		TargetAngle = MaxAngleOfLaunch;
	}

	// Add extra compensations;
	float CompPercentage = ((Vel - MinVelocityAngleCompensation)) / (MaxVelocityAngleCompensation - MinVelocityAngleCompensation);
	CompPercentage = 1 - CompPercentage;
	TargetAngle = TargetAngle + (AngleCompensationCap * CompPercentage);

	// FINALLY, Apply this angle to an horizontal launch direction
	FVector InitialLaunch = EndPoint - GetActorLocation();

	FRotator Rot = InitialLaunch.ToOrientationRotator();
	Rot.Pitch += TargetAngle;
	Rot.Yaw += HorizontalCompensation;

	FVector LaunchAngle = Rot.Vector();
	return LaunchAngle;
}

void AWeapon::SetWeaponVisibility(bool bVisible)
{
	SetActorHiddenInGame(!bVisible);
}
