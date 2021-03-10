// Fill out your copyright notice in the Description page of Project Settings.

#include "SortingBin.h"
#include "Components/CapsuleComponent.h"
#include "FritesMollesCharacter.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "PollutionZone.h"
#include "Prop.h"

// Sets default values
ASortingBin::ASortingBin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh_0"));
	RootComponent = SkeletalMesh;
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	SkeletalMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SkeletalMesh->SetSkeletalMesh(Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, TEXT("SkeletalMesh'/Game/Geometry/StaticMeshes/Gameplay/SK_BacRecyclage.SK_BacRecyclage'"))));

	SortCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SortBinCollider"));
	SortCollider->SetRelativeLocation(FVector(0, 0, 110));
	SortCollider->SetRelativeScale3D(FVector(0.75, 0.5, 1.45));
	SortCollider->SetupAttachment(SkeletalMesh, NAME_None);
	SortCollider->OnComponentBeginOverlap.AddDynamic(this, &ASortingBin::OnSortColliderOverlapBegin);

	SucessParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SuccessParticle"));
	SucessParticleSystemComp->SetupAttachment(SkeletalMesh, NAME_None);
	SucessParticleSystemComp->SetRelativeLocation(FVector(0, 0, 220));
	SucessParticleSystemComp->SetTemplate(Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, TEXT("ParticleSystem'/Game/Materials/Textures/FX/PS_AcceptCircle.PS_AcceptCircle'"))));

	FailureParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FailureParticle"));
	FailureParticleSystemComp->SetupAttachment(SkeletalMesh, NAME_None);
	FailureParticleSystemComp->SetRelativeLocation(FVector(0, 0, 220));
	FailureParticleSystemComp->SetTemplate(Cast<UParticleSystem>(StaticLoadObject(UParticleSystem::StaticClass(), NULL, TEXT("ParticleSystem'/Game/ParticleSystems/PS_Reject.PS_Reject'"))));

	// Create magnet component
	Magnet = CreateDefaultSubobject<UMagnet>(TEXT("Magnet"));
	Magnet->bResetMagnetizedActorOnBeginMagnetization = true;
	Magnet->AbsorbtionPriority = 2;
	Magnet->MinimumEpicenterDistanceRadiusOverride = 2;
	Magnet->AbsorbtionVelocityOverride = 14000;
	Magnet->AbsorbtionRadius = 50;
	Magnet->TargetedPositionOffsetOverride = FVector(0, 0, 10);
}

// Called when the game starts or when spawned
void ASortingBin::BeginPlay()
{
	Super::BeginPlay();
	Magnet->Collider->SetRelativeLocation(FVector(0, 0, 160));
	Magnet->Collider->SetGenerateOverlapEvents(false);
	SortCollider->SetGenerateOverlapEvents(false);
	SucessParticleSystemComp->InitParticles();
	FailureParticleSystemComp->InitParticles();
}

// Called every frame
void ASortingBin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void ASortingBin::OnMinigameColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AFritesMollesCharacter::StaticClass()) && OtherComp->IsA(UCapsuleComponent::StaticClass()))
	{
		FTimerHandle MemberTimerHandle;
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &ASortingBin::OpenBin, FMath::FRandRange(0, 0.5f), false);
		Magnet->Collider->SetGenerateOverlapEvents(true);
		SortCollider->SetGenerateOverlapEvents(true);
	}
}

void ASortingBin::OnMinigameColliderOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AFritesMollesCharacter::StaticClass()) && OtherComp->IsA(UCapsuleComponent::StaticClass()))
	{
		FTimerHandle MemberTimerHandle;
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &ASortingBin::CloseBin, FMath::FRandRange(0, 0.5f), false);
		Magnet->Collider->SetGenerateOverlapEvents(false);
		SortCollider->SetGenerateOverlapEvents(false);
	}
}

void ASortingBin::OpenBin()
{
	SkeletalMesh->PlayAnimation(Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("AnimSequence'/Game/Animations/Bins/ANIM_BacRecyclage_Open.ANIM_BacRecyclage_Open'"))), false);
}

void ASortingBin::CloseBin()
{
	SkeletalMesh->PlayAnimation(Cast<UAnimSequence>(StaticLoadObject(UAnimSequence::StaticClass(), NULL, TEXT("AnimSequence'/Game/Animations/Bins/ANIM_BacRecyclage_Closing.ANIM_BacRecyclage_Closing'"))), false);
}

void ASortingBin::OnSortColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UCollectable* OverlappingCollectabledItem = Cast<UCollectable>(OtherActor->GetComponentByClass(UCollectable::StaticClass()));
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UInventory* PlayerInventory = Cast<UInventory>(Player->GetComponentByClass(UInventory::StaticClass()));
	// If the overlapping actor is a collectable actor
	if (OverlappingCollectabledItem && PlayerInventory)
	{
		if (TrashType == ETrashTypes::Unsalvageable) 
		{
			if (OverlappingCollectabledItem->Data.type == ETrashTypes::Unsalvageable)
			{
				SortSuccess(PlayerInventory, OverlappingCollectabledItem);
			}
			else 
			{
				SortFailure(PlayerInventory, OverlappingCollectabledItem);
			}
		}
		else if (TrashType == OverlappingCollectabledItem->Data.type)
		{
			SortSuccess(PlayerInventory, OverlappingCollectabledItem);
		}
		else 
		{
			SortFailure(PlayerInventory, OverlappingCollectabledItem);
		}
		OtherActor->Destroy();
	}
}

void ASortingBin::SortSuccess(UInventory* PlayerInventory, UCollectable* Item)
{
	SucessParticleSystemComp->ActivateSystem();
	PlayerInventory->OnSorted.Broadcast(true, Item->Data.type, Item->Data.name);
	PlayerInventory->ReceiveSortedRessources(
	{
		{ Item->Data.type, Item->Data.value},
	});
	if (Item->Data.zone_ref)
	{
		Item->Data.zone_ref->UpdatePollutionUnits(-2);
	}
}

void ASortingBin::SortFailure(UInventory* PlayerInventory, UCollectable* Item)
{
	FailureParticleSystemComp->ActivateSystem();
	PlayerInventory->OnSorted.Broadcast(false, Item->Data.type, Item->Data.name);
	PlayerInventory->ReceiveSortedRessources({
		{ETrashTypes::Unsalvageable, Item->Data.value},
	});
	Item->bCollected = true;
	if (Item->Data.zone_ref)
	{
		Item->Data.zone_ref->UpdatePollutionUnits(1);
		Item->Data.zone_ref->ZoneTrashInventory[Item->Data.type] += Item->Data.value;
	}
}

