// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/Optional.h"
#include "Magnetized.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRITESMOLLES_API UMagnetized : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagnetized();

	// Called when something leaves the Sphere collider
	UFUNCTION(BlueprintCallable, Category = "Magnetized")
		void ResetRootLinearVelocityWithRoot(class UPrimitiveComponent* PrimitiveRoot);

	// Called when something leaves the Sphere collider
	UFUNCTION(BlueprintCallable, Category = "Magnetized")
		void ResetRootLinearVelocity();

	UFUNCTION(BlueprintCallable, Category = "Magnetized")
		void SetTargetedMagnet(AActor* target, UMagnet* targetMaget);

	UFUNCTION(BlueprintCallable, Category = "Magnetized")
		void ResetTargetedMagnet(bool resetVelocity);

	UFUNCTION(BlueprintCallable, Category = "Magnetized")
		UPrimitiveComponent* GetOwnerPrimitiveRoot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sphere collider used to detect magnets arround the owner actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magnetized")
		class USphereComponent* Collider;

	// Absorbtion velocity of the owner actor toward the magnet actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetized")
		float AbsorbtionVelocity = 1000.0f;

	TOptional<float> AbsorbtionVelocityOverride;

	// Radius of the sphere collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetized")
		float AbsorbtionRadius = 250.0f;

	// Radius within which the absorbtion stops until the magnet gets out of the collider and returns back in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetized")
		float MinimumEpicenterDistanceRadius = 100.0f;

	TOptional<float> MinimumEpicenterDistanceRadiusOverride;

	// Radius within which the absorbtion stops until the magnet gets out of the collider and returns back in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnetized")
		FVector TargetedPositionOffset = FVector(0,0,50);

	TOptional<FVector> TargetedPositionOffsetOverride;

	// Particles while the item is attracted to it's target
	UParticleSystemComponent* AttractionParticleSystem;

	// Particles while the item isn't attracted to it's target
	UParticleSystemComponent* AttractableParticleSystem;

	// Targeted magnet actor
	UMagnet* TargetedMagnet = nullptr;

	// Targeted magnet actor's radius (prevent having to fetch it from the magnet actor every tick)
	float TargetedMagnetRadius = 0;
};