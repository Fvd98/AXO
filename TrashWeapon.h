// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"

#include "Inventory.h"
#include "Lootable.h"
#include "Prop.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "TrashWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FRITESMOLLES_API ATrashWeapon : public AWeapon
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrashWeapon")
		FName TrajectoryMeshTag;

	TArray<UStaticMeshComponent*> TrajectoryMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrashWeapon")
		FTrashData CurrentShootedTrash = FTrashData();


protected:

	ATrashWeapon();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void Fire(FVector CameraForwards) override;
	virtual void UpdateSplinePositions(FVector Direction, float Velocity, float Gravity);
	virtual void SetWeaponVisibility(bool bVisible) override;
};
