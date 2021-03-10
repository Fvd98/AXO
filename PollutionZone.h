#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TrashType.h"
#include "PollutionZone.generated.h"

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerEnterZoneDelegate, APollutionZone*, NewZone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerCleanThresholdReachedDelegate, APollutionZone*, NewZone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FZoneCleanedDelegate, APollutionZone*, NewZone);

UCLASS()
class FRITESMOLLES_API APollutionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APollutionZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = "PollutionZone")
		void OnZoneOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TArray<TEnumAsByte<ETrashTypes>> GetnextProps(TMap<TEnumAsByte<ETrashTypes>, bool> AllowedTypes, int Amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PollutionZone")
		UBoxComponent* ZoneCollider;

	UFUNCTION(BlueprintCallable, Category = "PollutionZone")
		float GetPollutionLevel();

	UFUNCTION(BlueprintCallable, Category = "PollutionZone")
		void Clean();

	void UpdatePollutionUnits(int addedUnits);

	UPROPERTY(BlueprintReadOnly, Category = "PollutionZone")
		float MaxPollutionUnit = 0;

	UPROPERTY(BlueprintReadOnly, Category = "PollutionZone")
		float PollutionUnits = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PollutionZone")
		float CleanThreshold;

	UPROPERTY(BlueprintReadOnly, Category = "PollutionZone")
		bool bCleanThresholdReached = false;

	UPROPERTY(BlueprintReadOnly, Category = "PollutionZone")
		bool bClean = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PollutionZone")
		bool bStarterZone = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PollutionZone")
		FString ZoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PollutionZone")
		TMap<TEnumAsByte<ETrashTypes>, int> ZoneTrashInventory;

	UPROPERTY(BlueprintAssignable)
		FPlayerEnterZoneDelegate OnPlayerEnterZone;

	UPROPERTY(BlueprintAssignable)
		FPlayerCleanThresholdReachedDelegate OnCleanThresholdReached;

	UPROPERTY(BlueprintAssignable)
		FZoneCleanedDelegate OnZoneCleaned;
};
