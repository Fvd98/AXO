// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TrashType.h"
#include "Prop.h"
#include "NPC.h"
#include "Spawner.generated.h"

class APollutionZone;

UCLASS()
class FRITESMOLLES_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UFUNCTION()
	void NPCDiedHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void SetNextSpawningInterval();
	void SpawnNextNPCController();

	TArray<ANPC*> UnfinishedNPCInstances;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		APollutionZone* CurrentPollutionZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		UStaticMesh* SpawnerStaticMesh;
		
	UStaticMeshComponent* SpawnerStaticMeshComp;

	UBoxComponent* InitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner", DisplayName = "Spawn on landscape?")
		bool bSpawnOnLandscape = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner", meta = (EditCondition = "bSpawnOnLandscape"))
		float SpawningRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Spawn Counts")
		int SpawnAtBeginPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Spawn Counts")
		int SpawnLimitatOneTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Spawn Counts")
		int SpawnLimitatAllTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC")
		TMap<TSubclassOf<ANPC>, float> NPCSpawnClasses;

	#pragma region SpawnInterval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Spawn Interval", DisplayName = "Override default?")
		bool bOverrideNPSpawnInterval = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Spawn Interval", meta = (EditCondition = "bOverrideNPSpawnInterval", DisplayName = "Minimum Interval"))
		float minNPCSpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Spawn Interval", meta = (EditCondition = "bOverrideNPSpawnInterval", DisplayName = "Maximum Interval"))
		float maxNPCSpawnInterval;
	#pragma endregion

	#pragma region Size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Size", DisplayName = "Override default?")
		bool bOverrideNPCSize = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Size", meta = (EditCondition = "bOverrideNPCSize", DisplayName = "Minimum Size"))
		float minNPCSizeOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Size", meta = (EditCondition = "bOverrideNPCSize", DisplayName = "Maximum Size"))
		float maxNPCSizeOverride;
	#pragma endregion

	#pragma region Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Damage", DisplayName = "Override default?")
		bool bOverrideNPCDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Damage", meta = (EditCondition = "bOverrideNPCDamage", DisplayName = "Minimum Damage"))
		float minNPCDamageOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Damage", meta = (EditCondition = "bOverrideNPCDamage", DisplayName = "Minimum Damage"))
		float maxNPCDamageOverride;
	#pragma endregion

	#pragma region Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Health", DisplayName = "Override default?")
		bool bOverrideNPCHealth = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Health", meta = (EditCondition = "bOverrideNPCHealth", DisplayName = "Minimum Health"))
		float minNPCHealthOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Health", meta = (EditCondition = "bOverrideNPCHealth", DisplayName = "Minimum Health"))
		float maxNPCHealthOverride;
	#pragma endregion

	#pragma region Loot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC", DisplayName = "Loot")
		TMap<TEnumAsByte<ETrashTypes>, bool> SpawnAllowedTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Loot", DisplayName = "Override Prop Count?")
		bool bOverrideNPCPropCount = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Loot", meta = (EditCondition = "bOverrideNPCPropCount", DisplayName = "Prop Count"))
		int minNPCPropOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Loot", meta = (EditCondition = "bOverrideNPCPropCount", DisplayName = "Prop Count"))
		int maxNPCPropOverride;
	#pragma endregion

	#pragma region Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Speed", DisplayName = "Override default?")
		bool bOverrideNPCSpeed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Speed", meta = (EditCondition = "bOverrideNPCSpeed", DisplayName = "Minimum Speed"))
		float minNPCSpeedOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawned NPC|Speed", meta = (EditCondition = "bOverrideNPCSpeed", DisplayName = "Minimum Speed"))
		float maxNPCSpeedOverride;
	#pragma endregion

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SpawnDynamic();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void InitSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void setZone(APollutionZone* newPollutionZone);

	bool GetRandomSpawnPositionWhitinRadius(float Radius, FVector& OutResult);
	TSubclassOf<ANPC> GetRandomSpawnClass();

	float SpawnerTimer = 0;
	float SpawnNextInterval = 0;
	int SpawnedNPCAllTime = 0;
	int SpawnedNPCCurrentTime = 0;

	TArray<AProp*> TrashInstances;
};



