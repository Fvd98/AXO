// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PurchasableStructure.h"
#include "Interactable.h"
#include "WorldZone.generated.h"

UCLASS()
class FRITESMOLLES_API AWorldZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
		UBoxComponent* ZoneCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Zone")
		int ZoneId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
		bool bIsClean;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
		AInteractable* InteractCleanupRef;

	UPurchasableStructure* PurchasableCleanupRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
		void CleanZone();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
