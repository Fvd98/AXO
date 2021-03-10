#include "Spawner.h"
#include "PollutionZone.h"
#include "Engine/World.h"
#include "NPC_AIController.h"
#include "Landscape.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Rootcomponent"));
	RootComponent = InitCollider;
	InitCollider->SetBoxExtent(FVector(5, 5, 5));

	SpawnerStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SpawnerStaticMeshComp->SetupAttachment(InitCollider);
	SpawnerStaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SpawnerStaticMeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	SpawnerStaticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SpawnerStaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	SpawningRadius = 150;
	SpawnAtBeginPlay = 0;
	SpawnLimitatOneTime = 0;
	SpawnLimitatAllTime = 0;

	SpawnAllowedTypes =
	{
			{ETrashTypes::Unsalvageable, false},
			{ETrashTypes::EWaste, false},
			{ETrashTypes::Plastic, false},
			{ETrashTypes::Glass, false},
			{ETrashTypes::Organic, false},
			{ETrashTypes::Metal, false},
			{ETrashTypes::Paper, false},
	};

	#if WITH_EDITOR
		this->bRunConstructionScriptOnDrag = true;
	#endif
}

void ASpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpawnerStaticMeshComp->SetStaticMesh(
		SpawnerStaticMesh ? SpawnerStaticMesh :
		Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Geometry/StaticMeshes/FX/SM_Sphere.SM_Sphere'")))
	);
	SpawnerStaticMeshComp->SetRelativeScale3D(SpawnerStaticMesh ? FVector::OneVector : FVector(5, 5, 2));
	SpawnerStaticMeshComp->SetMaterial(0,
		SpawnerStaticMesh ? nullptr :
		Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("Material'/Game/Materials/Environnement/M_Collectible.M_Collectible'")))
	);

	#if WITH_EDITOR
		if (GetWorld() && !GetWorld()->GetGameInstance()) 
		{
			UKismetSystemLibrary::FlushPersistentDebugLines(this);
			UKismetSystemLibrary::DrawDebugCylinder(this, GetActorLocation(), GetActorLocation() + FVector(0, 0, 150), SpawningRadius ? SpawningRadius : 5, 12, FLinearColor::Green, 10000, 5);
		}
	#endif
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	if (!SpawnerStaticMesh)
	{
		SpawnerStaticMeshComp->SetStaticMesh(nullptr);
	}
}

void ASpawner::setZone(APollutionZone* newPollutionZone)
{
	if (newPollutionZone) 
	{
		CurrentPollutionZone = newPollutionZone;
		InitSpawner();
	}
}

void ASpawner::InitSpawner()
{
	for (int i = 0; i < SpawnAtBeginPlay; i++)
	{
		SpawnDynamic();
	}

	SetNextSpawningInterval();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bSpawnerTimerThresholdReached = SpawnerTimer > SpawnNextInterval;
	if (!bSpawnerTimerThresholdReached)
		SpawnerTimer += DeltaTime;

	if ((!SpawnLimitatOneTime || SpawnedNPCCurrentTime < FMath::Max(SpawnLimitatOneTime, 1)) && (!SpawnLimitatAllTime || SpawnedNPCAllTime < FMath::Max(SpawnLimitatAllTime, 1)) && bSpawnerTimerThresholdReached)
	{
		do
		{
			if (!SpawnLimitatAllTime || SpawnedNPCAllTime < FMath::Max(SpawnLimitatAllTime, 1))
				SpawnDynamic();

			SpawnerTimer -= SpawnNextInterval;
		} while (SpawnerTimer > SpawnNextInterval);
		SetNextSpawningInterval();
	}
}

void ASpawner::SpawnDynamic()
{

	float NPCSize = bOverrideNPCSize ? FMath::RandRange(FMath::Max(0.01f, minNPCSizeOverride), maxNPCSizeOverride) : 1;
	int NPCSizePercent = NPCSize < 1 ? NPCSize * 100 : 0;
	int NPCPropCount = bOverrideNPCPropCount 
		? FMath::RandRange(FMath::Min(1, minNPCPropOverride), FMath::Min(5, maxNPCPropOverride))
		: bOverrideNPCSize && NPCSize < 1
			? ((NPCSizePercent - (NPCSizePercent % 20)) / 20) + 1
			: 5;

	TArray<TEnumAsByte<ETrashTypes>> GivenZoneTrash = CurrentPollutionZone->GetnextProps(SpawnAllowedTypes, NPCPropCount);

	if (GivenZoneTrash.Num()) 
	{
		TSubclassOf<ANPC> NPCSpawnClass = GetRandomSpawnClass();

		FVector NPCSpawnCoordinates;
		if (bSpawnOnLandscape)
			GetRandomSpawnPositionWhitinRadius(SpawningRadius, NPCSpawnCoordinates);
		else
			NPCSpawnCoordinates = GetActorLocation() + FVector(0, 0, 50);
		FRotator NPCSpawnRotator = FRotator(0, FMath::RandRange(0, 360), 0);
		FTransform NPCSpawnTransform = FTransform(NPCSpawnRotator, NPCSpawnCoordinates);

		ANPC* NewNPC = GetWorld()->SpawnActorDeferred<ANPC>(NPCSpawnClass, NPCSpawnTransform, (AActor*)nullptr, (APawn*)nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

		NewNPC->LootableComp->ZoneRef = CurrentPollutionZone;
		NewNPC->LootableComp->PresetProps = GivenZoneTrash;
		NewNPC->SetActorScale3D(FVector(NPCSize));
		NewNPC->SludgeEffectSize *= NPCSize;
		NewNPC->MeleeRange *= NPCSize;

		/* TODO : Change Range Damage*/
		/*float NPCRangeDamage = bOverrideNPCDamage
			? FMath::RandRange(FMath::Max(0.f, minNPCSizeOverride), maxNPCSizeOverride)
			: /*GET CURRENT RANGE DAMAGE;*/

		NewNPC->MeleeDamage = bOverrideNPCDamage
			? FMath::RandRange(FMath::Max(0.1f, minNPCDamageOverride), maxNPCDamageOverride)
			: bOverrideNPCSize
			? NewNPC->MeleeDamage * NPCSize
			: NewNPC->MeleeDamage;

		/* TODO : Assign to Damagabale entity */
		NewNPC->DamageableEntityComp->SetMaxHealth(bOverrideNPCHealth
			? FMath::RandRange(FMath::Max(0.f, minNPCHealthOverride), maxNPCHealthOverride)
			: bOverrideNPCSize
			? NewNPC->DamageableEntityComp->GetMaxHealth() * NPCSize
			: NewNPC->DamageableEntityComp->GetMaxHealth()
		, true);

		float NPCWalkSpeedModifier = NewNPC->WalkSpeed * (1 - NPCSize) / 2;
		NewNPC->WalkSpeed = bOverrideNPCSpeed
			? FMath::RandRange(FMath::Max(0.f, minNPCSpeedOverride), maxNPCSpeedOverride)
			: bOverrideNPCSize && NPCSize != 1
			? NPCSize < 1
				? NewNPC->WalkSpeed + NPCWalkSpeedModifier
				: NewNPC->WalkSpeed - NPCWalkSpeedModifier
					: NewNPC->WalkSpeed;
		
		NewNPC->FinishSpawning(NPCSpawnTransform);
		FTimerHandle Timer;
		UnfinishedNPCInstances.Add(NewNPC);
		GetWorldTimerManager().SetTimer(Timer, this, &ASpawner::SpawnNextNPCController, 0.05);
		SpawnedNPCAllTime++;
		SpawnedNPCCurrentTime++;
		NewNPC->LootableComp->OnOwnerLooted.AddDynamic(this, &ASpawner::NPCDiedHandler);
	}
}

void ASpawner::SpawnNextNPCController()
{
	UnfinishedNPCInstances[0]->SpawnDefaultController();
	UnfinishedNPCInstances.RemoveAt(0, 1, true);
}

void ASpawner::NPCDiedHandler()
{
	SpawnedNPCCurrentTime--;
}

bool ASpawner::GetRandomSpawnPositionWhitinRadius(float Radius, FVector& OutResult)
{
	UWorld* World = GetWorld();

	// Gets a random point whitin the given radius around the spawner actor
	FVector SpawnerLocation = GetActorLocation();
	float angle = FMath::RandRange(0.f, 1.f) * 2 * PI;
	float radius = Radius * FMath::Sqrt(FMath::RandRange(0.f, 1.f));
	FVector RandomXYPointCircle = FVector(radius * FMath::Cos(angle), radius * FMath::Sin(angle), 0);
	RandomXYPointCircle += FVector(SpawnerLocation.X, SpawnerLocation.Y, 0);

	// Find the active landscape
	TArray<AActor*> FoundLandscapesT;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscape::StaticClass(), FoundLandscapesT);
	if (FoundLandscapesT.Num())
	{
		ALandscape* landscape = (ALandscape*)FoundLandscapesT[0];

		FCollisionQueryParams collisionParams(FName(TEXT("FoliageClusterPlacementTrace")), true, this);

		// Traces a line from top to bottom returning the fist hit Static object point of collision
		FVector startTraceHeight = FVector(0, 0, 1000);
		const FVector startVector = RandomXYPointCircle + startTraceHeight;
		const FVector endVector = RandomXYPointCircle - startTraceHeight;

		FHitResult result(ForceInit);
		if (landscape->ActorLineTraceSingle(result, startVector, endVector, ECC_Visibility, collisionParams)) {
			OutResult = result.ImpactPoint + FVector(0, 0, 50);
			return true;
		}
	}

	return false;
}

TSubclassOf<ANPC> ASpawner::GetRandomSpawnClass()
{
	TSubclassOf<ANPC> NPCSpawnClass;
	TArray<TSubclassOf<ANPC>> PossibleSpawnClasses;
	NPCSpawnClasses.GetKeys(PossibleSpawnClasses);
	int NPCSpawnClassesCount = NPCSpawnClasses.Num();
	if (NPCSpawnClassesCount)
	{
		float TotalChances = 0;
		for (auto& classChances : NPCSpawnClasses)
		{
			TotalChances += classChances.Value;
		}

		float RandomPick = FMath::RandRange(0.f, TotalChances);
		float CurrentCount = 0;
		for (auto& classChances : NPCSpawnClasses)
		{
			float newStep = CurrentCount + classChances.Value;
			if (RandomPick <= newStep)
			{
				NPCSpawnClass = classChances.Key;
				break;
			}
			CurrentCount = newStep;
		}
		check(NPCSpawnClass);
	}
	else
	{
		NPCSpawnClass = ANPC::StaticClass();
	}
	return NPCSpawnClass;
}

void ASpawner::SetNextSpawningInterval() 
{
	if (!minNPCSpawnInterval && !maxNPCSpawnInterval)
		SpawnNextInterval = 2.5f;
	else if (!minNPCSpawnInterval || !maxNPCSpawnInterval)
		SpawnNextInterval = minNPCSpawnInterval ? FMath::Abs(minNPCSpawnInterval) : FMath::Abs(maxNPCSpawnInterval);
	else
		SpawnNextInterval = FMath::RandRange(FMath::Max(minNPCSpawnInterval, 0.01f), FMath::Max(minNPCSpawnInterval, maxNPCSpawnInterval));
}




