// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldZone.h"

// Sets default values
AWorldZone::AWorldZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ZoneCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneCollider"));
}

// Called when the game starts or when spawned
void AWorldZone::BeginPlay()
{
	Super::BeginPlay();
	if (InteractCleanupRef)
	{
		PurchasableCleanupRef = Cast<UPurchasableStructure>(InteractCleanupRef->GetComponentByClass(UPurchasableStructure::StaticClass()));
		if (PurchasableCleanupRef)
		{
			PurchasableCleanupRef->OnPurchase.AddDynamic(this, &AWorldZone::CleanZone);
		}
	}
	if (!bIsClean)
	{
		ZoneCollider->SetActive(false);
		ZoneCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called every frame
void AWorldZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldZone::CleanZone()
{
	bIsClean = true;
	ZoneCollider->SetActive(true);
	ZoneCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

