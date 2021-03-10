// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrashType.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Containers/Array.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "SortingPedestal.generated.h"

UCLASS()
class FRITESMOLLES_API ASortingPedestal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASortingPedestal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	FVector GetBinDefaultOffsetPosition(int index, int binPerColumn, float XOffsetPerUnit, float YOffsetPerUnit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* PedestalStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestal")
		UStaticMesh* PedestalStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestal")
		UMaterial* PedestalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestal")
		UBoxComponent* OpenBinCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestal")
		TSubclassOf<class ASortingBin> BinClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestal")
		TArray<UChildActorComponent*> Bins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pedestal")
		TMap<TEnumAsByte<ETrashTypes>, bool> ActiveBins;
};
