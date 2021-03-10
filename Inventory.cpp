#include "Inventory.h"
#include "Collectable.h"
#include "Lootable.h"
#include <numeric>
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	unsortedInventory = {
		{ETrashTypes::Unsalvageable, 0},
		{ETrashTypes::EWaste, 0},
		{ETrashTypes::Plastic, 0},
		{ETrashTypes::Glass, 0},
		{ETrashTypes::Organic, 0},
		{ETrashTypes::Metal, 0},
		{ETrashTypes::Paper, 0},
	};
	sortedInventory = {
		{ETrashTypes::Unsalvageable, 0},
		{ETrashTypes::EWaste, 0},
		{ETrashTypes::Plastic, 0},
		{ETrashTypes::Glass, 0},
		{ETrashTypes::Organic, 0},
		{ETrashTypes::Metal, 0},
		{ETrashTypes::Paper, 0},
	};
}

// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// Initiate and attach collider sphere
	Collider = NewObject<USphereComponent>(this, TEXT("inventory_collider"));
	Collider->RegisterComponent();
	Collider->InitSphereRadius(ColliderRadius);
	Collider->SetSphereRadius(ColliderRadius);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionProfileName(TEXT("OverlapAll"));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &UInventory::OnOverlapBegin);
	Collider->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	Collider->SetRelativeLocation(ColliderOffset);
	SetNextUnsortedItem();
}

void UInventory::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UCollectable* OverlappingCollectabledItem = Cast<UCollectable>(OtherActor->GetComponentByClass(UCollectable::StaticClass()));
	// If the overlapping actor is a magnetized actor and it's priority is higher or equal, sets this magnet actor as the targeted magnet to which pull the owner actor to
	if (OverlappingCollectabledItem)
	{
		if (CurrentInventoryTotal() + OverlappingCollectabledItem->Data.value <= maxUnsortedInventory) {
			unsortedInventory[OverlappingCollectabledItem->Data.type] += OverlappingCollectabledItem->Data.value;
			unsortedInventoryItemData.Add(OverlappingCollectabledItem->Data);
			OverlappingCollectabledItem->bCollected = true;
			OtherActor->Destroy();
			if (currentSelectedUnsortedItem.value == -1) 
				SetNextUnsortedItem();
			else if (unsortedInventoryItemData.Num() < 5) 
				unsortedInventoryItemDataPeek = PeekNextUnsortedItems(4);

			OnUnsortedPickup.Broadcast();
		}
		else 
		{
			OnUnsortedFull.Broadcast();
		}
	}
}

// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int UInventory::CurrentInventoryTotal()
{
	int inventoryTotal = 0;
	for (auto& num : unsortedInventory)
		inventoryTotal += num.Value;
	return inventoryTotal;
}

void UInventory::PopSelectedUnsortedItem()
{
	unsortedInventory[currentSelectedUnsortedItem.type] -= currentSelectedUnsortedItem.value;
	SetNextUnsortedItem();
}

TArray<UTexture2D*> UInventory::PeekNextUnsortedItems(int amount)
{
	int count = unsortedInventoryItemData.Num();
	TArray<UTexture2D*> output;

	if (currentSelectedUnsortedItem.value != -1) 
		output.Add(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ULootable::GetIconPath(currentSelectedUnsortedItem))));
	
	int countToGet = FMath::Min(count, amount-1);

	for (int i = 0; i < countToGet; i++)
		output.Add(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ULootable::GetIconPath(unsortedInventoryItemData[i]))));

	while(output.Num() < amount)
		output.Add(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ULootable::GetIconPath(FTrashData()))));

	return output;
}

FTrashData UInventory::GetSelectedUnsortedItem()
{
	return currentSelectedUnsortedItem;
}

void UInventory::SetNextUnsortedItem()
{
	if (unsortedInventoryItemData.Num())
	{
		currentSelectedUnsortedItem = unsortedInventoryItemData[0];
		unsortedInventoryItemData.RemoveAt(0);
	}
	else
		currentSelectedUnsortedItem = FTrashData();
	unsortedInventoryItemDataPeek = PeekNextUnsortedItems(4);
}

bool UInventory::SpendSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources)
{
	if (!VerifySpendingSortedRessources(Ressources)) 
	{
		return false;
	}

	for (const TPair<TEnumAsByte<ETrashTypes>, int>& ressource : Ressources) {
		sortedInventory[ressource.Key] -= FMath::Abs(ressource.Value);
	}

	return true;
}

bool UInventory::VerifySpendingSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources)
{
	for (const TPair<TEnumAsByte<ETrashTypes>, int>& ressource : Ressources) {
		if (sortedInventory[ressource.Key] < FMath::Abs(ressource.Value)) {
			return false;
		}
	}
	return true;
}

void UInventory::ReceiveSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources)
{
	for (const TPair<TEnumAsByte<ETrashTypes>, int>& ressource : Ressources) {
		sortedInventory[ressource.Key] += FMath::Abs(ressource.Value);
	}
}

bool UInventory::TransactSortedRessources(TMap<TEnumAsByte<ETrashTypes>, int> Ressources)
{
	TMap<TEnumAsByte<ETrashTypes>, int> RessourcesSpent;
	TMap<TEnumAsByte<ETrashTypes>, int> RessourcesReceived;
	for (const TPair<TEnumAsByte<ETrashTypes>, int>& ressource : Ressources) {
		(FMath::IsNegativeDouble(ressource.Value) ? RessourcesSpent : RessourcesReceived).Add(ressource);
	}

	if (!SpendSortedRessources(RessourcesSpent))
		return false;

	ReceiveSortedRessources(RessourcesReceived);

	return true;
}

