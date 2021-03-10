// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrashType.h"
#include "Inventory.h"
#include "Collectable.h"
#include "Animation/AnimSequence.h"
#include "Components/BoxComponent.h"
#include "Magnet.h"
#include "SortingBin.generated.h"

UCLASS()
class FRITESMOLLES_API ASortingBin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASortingBin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SortSuccess(UInventory* PlayerInventory, UCollectable* Item);

	void SortFailure(UInventory* PlayerInventory, UCollectable* Item);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bin")
		USkeletalMeshComponent* SkeletalMesh;

	/** Magnet attracting magnetized actors */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bin")
		UMagnet* Magnet;

	UParticleSystemComponent* SucessParticleSystemComp;
	UParticleSystemComponent* FailureParticleSystemComp;

	UFUNCTION(BlueprintCallable, Category = "Bin")
		void OnMinigameColliderOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Bin")
		void OnMinigameColliderOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OpenBin();

	void CloseBin();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bin")
		UBoxComponent* SortCollider;

	UFUNCTION(BlueprintCallable, Category = "Bin")
		void OnSortColliderOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bin")
		TEnumAsByte<ETrashTypes> TrashType;
};
