// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Inventory.h"
#include "Collectable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRITESMOLLES_API UCollectable : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollectable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void Expired();

	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collectable")
		class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
		float ColliderRadius = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
		FTrashData Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
		bool bPlayerCreated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
		bool bExpired = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectable")
		bool bCollected = false;
};