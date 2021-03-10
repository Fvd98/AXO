// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "DamageableEntity.h"
#include "Projectile.h"
#include "Weapon.generated.h"

UCLASS()
class FRITESMOLLES_API AWeapon : public AActor
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MeshComp;

	// This is not a new camera. It's a reference towards the existing one.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* PlayerCameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AActor> ProjectileRef;

	// If the target actor is not a projectile, the weapon will rely on this instead
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float DefaultVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool HasFired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		bool ShouldFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		// Used for UI purposes
		int WeaponID;

protected:
	// Shots per second. (1 / FireRate) = Shot Cooldown.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireRate = 1.0f;

	// After this range, the aim point will be at that amount of units forwards from the crosshair
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAccurateRange = 50000.0f;

	// When the weapon will be ready to fire again
	float FireCooldown;

	// After this range, the aim point will be at that amount of units forwards from the crosshair
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAngleOfLaunch = 35.0f;
	
	// Lower threshold for angle compensation
	float MinVelocityAngleCompensation = 1000;
	// Higher threshold for angle compensation
	float MaxVelocityAngleCompensation = 3000;
	// Amount of angle compensation, in degrees
	float AngleCompensationCap = 10;

	// Right compensation in degrees, since we're shooting from the left
	float HorizontalCompensation = 0.5f;

	// The end point of the shooting.
	FVector EndPoint;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Find the direction in which to fire
	virtual FVector GetFireDirection(FVector CameraDirection, FVector CameraPosition);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Fire(FVector CameraForwards);

	// To allow various actions from press and release (for autos, semi-autos, bows, throwables, etc.)
	virtual void PressFire();
	virtual void ReleaseFire();

	// To allow ADS and other things
	virtual void PressAltFire();
	virtual void ReleaseAltFire();

	// Override to disable the weapon
	virtual void SetWeaponVisibility(bool bVisible);
};
