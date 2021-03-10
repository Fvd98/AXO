// Fill out your copyright notice in the Description page of Project Settings.

#include "SortingPedestal.h"
#include "SortingBin.h"
#include "Lootable.h"

// Sets default values
ASortingPedestal::ASortingPedestal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PedestalStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rootcomponent"));
	RootComponent = PedestalStaticMeshComponent;
	PedestalStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PedestalStaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	PedestalStaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	PedestalStaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
	OpenBinCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("OpenBinCollider"));
	OpenBinCollider->SetRelativeLocation(FVector(-7.68, 174.46, 146.33));
	OpenBinCollider->SetRelativeScale3D(FVector(3.25));
	OpenBinCollider->SetupAttachment(PedestalStaticMeshComponent, NAME_None);

	ActiveBins =
	{
			{ETrashTypes::Unsalvageable, true},
			{ETrashTypes::EWaste, true},
			{ETrashTypes::Plastic, true},
			{ETrashTypes::Glass, true},
			{ETrashTypes::Organic, true},
			{ETrashTypes::Metal, true},
			{ETrashTypes::Paper, true},
	};

	BinClass = ASortingBin::StaticClass();
	for (int i = 0; i < ETrashTypes::COUNT; i++) 
	{
		FString BinName = FString("Bin_").Append(ULootable::GetTrashTypeAsString((ETrashTypes)i));
		UChildActorComponent* CurrentBinComponent = CreateDefaultSubobject<UChildActorComponent>(*BinName);
		CurrentBinComponent->SetupAttachment(PedestalStaticMeshComponent, NAME_None);
		Bins.Add(CurrentBinComponent);
	}
}

// Called when the game starts or when spawned
void ASortingPedestal::BeginPlay()
{
	Super::BeginPlay();
}

void ASortingPedestal::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	PedestalStaticMeshComponent->SetStaticMesh(
		PedestalStaticMesh ? PedestalStaticMesh :
		Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Buildings/SM_SortingPedestal.SM_SortingPedestal'")))
	);
	PedestalStaticMeshComponent->SetMaterial(0, Cast<UMaterialInterface>(
		PedestalMaterial ? PedestalMaterial :
		StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, TEXT("MaterialInstanceConstant'/Game/Materials/Environnement/Building/M_WoodA1_Inst.M_WoodA1_Inst'"))
	));

	int count = Bins.Num();
	for (int i = 0; i < count; i++) {
		if(Bins[i]->GetChildActor())
			Bins[i]->DestroyChildActor();
		Bins[i]->SetChildActorClass(nullptr);
	}
	for (auto& bin : ActiveBins)
	{
		if (bin.Value)
		{
			UChildActorComponent* CurrentBinComponent = Bins[bin.Key];
			FVector CurrentBinPosition = CurrentBinComponent->GetRelativeLocation();
			if (CurrentBinPosition == FVector::ZeroVector)
			{
				CurrentBinComponent->SetRelativeLocation(CurrentBinPosition + GetBinDefaultOffsetPosition(bin.Key, 3, 150, 150) + FVector(0, 450, 0));
			}

			CurrentBinComponent->SetChildActorClass(BinClass);
			CurrentBinComponent->CreateChildActor();
			FString BinName = FString("Bin_").Append(ULootable::GetTrashTypeAsString(bin.Key));
			
			ASortingBin* CurrentBin = (ASortingBin*)CurrentBinComponent->GetChildActor();
			if (CurrentBin) 
			{
				#if WITH_EDITOR
					CurrentBin->SetActorLabel(BinName);
				#endif
				
				CurrentBin->TrashType = bin.Key;
				int TrashTypeAssetIndex = bin.Key + 1;
				UMaterialInstanceConstant* BinIconMaterial = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, *FString("MaterialInstanceConstant'/Game/Materials/Gameplay/INST_Bin_").Append(FString::FromInt(TrashTypeAssetIndex)).Append(".INST_Bin_").Append(FString::FromInt(TrashTypeAssetIndex)).Append("'")));
				CurrentBin->SkeletalMesh->SetMaterial(2, BinIconMaterial);
				UMaterialInstanceConstant* BinColorMaterial = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, *FString("MaterialInstanceConstant'/Game/Materials/Props/Bac/INST_Bin_Color_").Append(FString::FromInt(TrashTypeAssetIndex)).Append(".INST_Bin_Color_").Append(FString::FromInt(TrashTypeAssetIndex)).Append("'")));
				CurrentBin->SkeletalMesh->SetMaterial(0, BinColorMaterial);
				OpenBinCollider->OnComponentBeginOverlap.AddDynamic(CurrentBin, &ASortingBin::OnMinigameColliderOverlapBegin);
				OpenBinCollider->OnComponentEndOverlap.AddDynamic(CurrentBin, &ASortingBin::OnMinigameColliderOverlapEnd);
			}
		}
	}
}

FVector ASortingPedestal::GetBinDefaultOffsetPosition(int index, int binPerColumn, float XOffsetPerUnit, float YOffsetPerUnit)
{
	int rowIndex = index % binPerColumn; // residue
	int roundIndex = index - rowIndex;
	int columnIndex = roundIndex / binPerColumn;
	return FVector(rowIndex * XOffsetPerUnit, columnIndex * YOffsetPerUnit, 0);
}

// Called every frame
void ASortingPedestal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

