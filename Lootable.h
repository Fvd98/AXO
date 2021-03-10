#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TrashSocket.h"
#include "DamageableEntity.h"
#include "TrashType.h"
#include "SArray.h"
#include "TrashMap.h"
#include "Prop.h"
#include "PollutionZone.h"
#include "Lootable.generated.h"

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOwnerLootedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FRITESMOLLES_API ULootable : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULootable();

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		void Attach(FTrashSocketData trash);

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		void UpdateFromDamage();

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		static FString GetIconPath(FTrashData trash);

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		static FString GetMeshPath(FTrashData trash);

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		static FTrashData GenerateSingleMesh(FTrashData trash);

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		static FTrashData GenerateSingleIcon(FTrashData trash);

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		static FTrashData GenerateProp(ETrashTypes type, APollutionZone* zone_ref);

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		static AProp* GetSpawnableProp(UWorld* propWorld, FTransform propTransform, FTrashData propData);

	UFUNCTION(BlueprintCallable, Category = "Lootable")
		static FString GetTrashTypeAsString(ETrashTypes type);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	static const TMap<TEnumAsByte<ETrashTypes>, FTrashMap> LootTypeMaps;
	static TMap<TEnumAsByte<ETrashTypes>, FTrashMap> GetinitLootTypeMaps(FTrashMap AllLoots);
	static const FTrashMap AllLoots;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lootable")
		TArray<TEnumAsByte<ETrashTypes>> PresetProps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lootable")
		APollutionZone* ZoneRef;

	UPROPERTY(BlueprintAssignable)
		FOnOwnerLootedDelegate OnOwnerLooted;

	TArray<FTrashSocketData> UsedSockets;
	TArray<FName> FreeSockets;
	USkeletalMeshComponent* SkeletonMesh;
	UDamageableEntity* DamageableEntity;

	static FTrashMap GetLootTableByType(ETrashTypes type);
	static FTrashData GetLootDataByName(FString name);
};

