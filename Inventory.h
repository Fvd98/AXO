// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TrashType.h"
#include "Trash.h"
#include "Engine/Texture2D.h"
#include "Inventory.generated.h"

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnsortedFullDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnsortedPickupDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSortedDelegate, bool, bGood, ETrashTypes, Type, FString, Name);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRITESMOLLES_API UInventory : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

	// Called when something enters the Sphere collider
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int CurrentInventoryTotal();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		FTrashData GetSelectedUnsortedItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void PopSelectedUnsortedItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		TArray<UTexture2D*> PeekNextUnsortedItems(int amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool SpendSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool VerifySpendingSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void ReceiveSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool TransactSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FUnsortedFullDelegate OnUnsortedFull;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FUnsortedPickupDelegate OnUnsortedPickup;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FSortedDelegate OnSorted;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SetNextUnsortedItem();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Inventory containing every type of trash but all as one pile of cumulated trash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TMap<TEnumAsByte<ETrashTypes>, int> unsortedInventory;

	// Array of all collected unsorted trash's data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FTrashData> unsortedInventoryItemData;

	// Next trashes in queue to be shot/used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<UTexture2D*> unsortedInventoryItemDataPeek;

	// Next trash in queue to be shot/used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FTrashData currentSelectedUnsortedItem;

	// Inventory containing every type of trash that has been sorted
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TMap<TEnumAsByte<ETrashTypes>, int> sortedInventory;

	// Maximum amount of unsorted trash that the actor can hold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int maxUnsortedInventory = 40;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		float ColliderRadius = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		FVector ColliderOffset = FVector(0, 0, -90);
};