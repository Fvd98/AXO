// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Magnet.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRITESMOLLES_API UMagnet : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagnet();

	// Called when something enters the Sphere collider
	UFUNCTION(BlueprintCallable, Category = "Magnet")
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when something leaves the Sphere collider
	UFUNCTION(BlueprintCallable, Category = "Magnet")
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sphere collider used to detect magnets arround the owner actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magnet")
		class USphereComponent* Collider;

	// Radius of the sphere collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
		float AbsorbtionRadius = 500.0f;

	// Absorbtion velocity override of the magnetized actor toward the owner actor
	TOptional<float> AbsorbtionVelocityOverride;

	// Radius override within which the absorbtion stops until the magnet gets out of the collider and returns back in
	TOptional<float> MinimumEpicenterDistanceRadiusOverride;

	TOptional<FVector> TargetedPositionOffsetOverride;

	// Radius of the sphere collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
		int AbsorbtionPriority = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
		bool bResetMagnetizedActorOnBeginMagnetization = false;
};
