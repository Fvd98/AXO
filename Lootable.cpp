#include "Lootable.h"
#include "Engine/SkeletalMeshSocket.h"


const FTrashMap ULootable::AllLoots = {{
	//Unsalvageable
	{
		"Car tire",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Car_Wheel.SM_Car_Wheel'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Wheel.UT_TrashIcon_Wheel'",
			},
		}
	},
	{
		"Fish bones",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_FishBones.SM_FishBones'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_FishBone.UT_TrashIcon_FishBone'",
			},
		}
	},
	{
		"Cleaner bottle",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_WindexBottle.SM_WindexBottle'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Windex.UT_TrashIcon_Windex'",
			},
		}
	},
	{
		"Broken salsa jar",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_BrokenJar.SM_BrokenJar'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_BrokenGlass.UT_TrashIcon_BrokenGlass'",
			},
		}
	},
	{
		"Toothpaste tube",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_ToothPaste.SM_ToothPaste'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_PateADent.UT_TrashIcon_PateADent'",
			},
		}
	},
	{
		"Styrofoam foodtray",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Stryofoam_SetD.SM_Stryofoam_SetD'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Styrofoam_SetA.SM_Styrofoam_SetA'"
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_FoodTray_setA-D_.UT_TrashIcon_FoodTray_setA-D_'",
			},
		}
	},
	{
		"Styrofoam cup",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Styrofoam_SetE.SM_Styrofoam_SetE'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Styrofoam_SetC.SM_Styrofoam_SetC'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Gobelet.UT_TrashIcon_Gobelet'",
			},
		}
	},
	{
		"Yogurt",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Yogurt.SM_Yogurt'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Yogurt.UT_TrashIcon_Yogurt'",
			},
		}
	},
	{
		"Styrofoam plate",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Styrofoam_SetB.SM_Styrofoam_SetB'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Assiette_setB_.UT_TrashIcon_Assiette_setB_'",
			},
		}
	},
	{
		"Plate",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Plate.SM_Plate'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_PorcelainePlate.UT_TrashIcon_PorcelainePlate'",
			},
		}
	},
	{
		"Coffee cup",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Coffee.SM_Coffee'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_CoffeeCup.UT_TrashIcon_CoffeeCup'",
			},
		}
	},
	{
		"Takeout box",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Styrofoam_SetF.SM_Styrofoam_SetF'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_TakeOut_setF_.UT_TrashIcon_TakeOut_setF_'",
			},
		}
	},
	/*{ //DISABLED UNTIL MESH IS FIXED
		"Face mask",
		FTrashData
		{
			ETrashTypes::Unsalvageable,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Face_Mask_First_Variation.SM_Face_Mask_First_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Face_Mask_Second_Variation.SM_Face_Mask_Second_Variation'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_FaceMask.UT_TrashIcon_FaceMask'",
			},
		}
	},*/

	//EWaste
	{
		"Placeholder (EWaste)",
		FTrashData
		{
			ETrashTypes::EWaste,
			1,
			{
				
			},
			{

			},
		}
	},
	//Plastic
	{
		"Detergent bottle",
		FTrashData
		{
			ETrashTypes::Plastic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Detergent_First_Variation.SM_Detergent_First_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Detergent_Second_Variation.SM_Detergent_Second_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Detergent_Third_Variation.SM_Detergent_Third_Variation'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Detergeant.UT_TrashIcon_Detergeant'",
			},
		}
	},
	{
		"Ketchup bottle",
		FTrashData
		{
			ETrashTypes::Plastic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Ketchup_first_Variation.SM_Ketchup_first_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Ketcup_Second_Variation.SM_Ketcup_Second_Variation'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Ketchup.UT_TrashIcon_Ketchup'",
			},
		}
	},
	{
		"Water bottle",
		FTrashData
		{
			ETrashTypes::Plastic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_WaterBottle.SM_WaterBottle'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_WaterBottle.UT_TrashIcon_WaterBottle'",
			},
		}
	},
	//Glass
	{
		"Canning jar",
		FTrashData
		{
			ETrashTypes::Glass,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_MasonJar.SM_MasonJar'"
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_MasonJar.UT_TrashIcon_MasonJar'"
			},
		},
	},
	{
		"Sparkling water bottle",
		FTrashData
		{
			ETrashTypes::Glass,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Perrier.SM_Perrier'"
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_PerrierBottle.UT_TrashIcon_PerrierBottle'"
			},
		},
	},
	{
		"Sparkling juice bottle",
		FTrashData
		{
			ETrashTypes::Glass,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_AppleCider.SM_AppleCider'"
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_CiderBottle.UT_TrashIcon_CiderBottle'"
			},
		},
	},
	{
		"Salsa jar",
		FTrashData
		{
			ETrashTypes::Glass,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Salsa.SM_Salsa'"
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_SalsaPot.UT_TrashIcon_SalsaPot'"
			},
		},
	},
	//Organic
	{
		"Banana peel",
		FTrashData
		{
			ETrashTypes::Organic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_BananaPeel.SM_BananaPeel'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Banana.UT_TrashIcon_Banana'",
			},
		}
	},
	{
		"Apple",
		FTrashData
		{
			ETrashTypes::Organic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Apple_First_Variation.SM_Apple_First_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Apple_Second_Variation.SM_Apple_Second_Variation'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_apple.UT_TrashIcon_apple'",
			},
		}
	},
	{
		"Toilet paper",
		FTrashData
		{
			ETrashTypes::Organic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_ToiletPaper.SM_ToiletPaper'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_ToiletPaper.UT_TrashIcon_ToiletPaper'",
			},
		}
	},
	{
		"Soiled pizza box",
		FTrashData
		{
			ETrashTypes::Organic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_PizzaBox.SM_PizzaBox'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_PizzaBox.UT_TrashIcon_PizzaBox'",
			},
		}
	},
	{
		"Soiled newspaper",
		FTrashData
		{
			ETrashTypes::Organic,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Newspapers.SM_Newspapers'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Soilenewspaper.UT_TrashIcon_Soilenewspaper'",
			},
		}
	},
	//Metal
	{
		"Can",
		FTrashData
		{
			ETrashTypes::Metal,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_First_Variation.SM_Can_First_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_Second_Variation.SM_Can_Second_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_Third_Variation.SM_Can_Third_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_Big.SM_Can_Big'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Cannette.UT_TrashIcon_Cannette'",
			},
		},
	},
	{
		"Soup can",
		FTrashData
		{
			ETrashTypes::Metal,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_Big.SM_Can_Big'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Can_Big.UT_TrashIcon_Can_Big'",
			},
		},
	},
	{
		"Bean can",
		FTrashData
		{
			ETrashTypes::Metal,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_Small.SM_Can_Small'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Can_Small.UT_TrashIcon_Can_Small'",
			},
		},
	},
	{
		"Anchovy can",
		FTrashData
		{
			ETrashTypes::Metal,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_Sardine.SM_Can_Sardine'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Can_Sardine.UT_TrashIcon_Can_Sardine'",
			},
		},
	},
	{
		"Soda can",
		FTrashData
		{
			ETrashTypes::Metal,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Can_Soda.SM_Can_Soda'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Can_Soda.UT_TrashIcon_Can_Soda'",
			},
		},
	},
	//Paper
	{
		"Cereal box",
		FTrashData
		{
			ETrashTypes::Paper,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Cereal_Box_first_Variation.SM_Cereal_Box_first_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Cereal_Second_Variation.SM_Cereal_Second_Variation'",
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Cereal_third_Variation.SM_Cereal_third_Variation'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_CerealBox.UT_TrashIcon_CerealBox'",
			},
		}
	},
	{
		"Newspaper",
		FTrashData
		{
			ETrashTypes::Paper,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_Newspapers.SM_Newspapers'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_Journal.UT_TrashIcon_Journal'",
			},
		}
	},
	{
		"Milk carton",
		FTrashData
		{
			ETrashTypes::Paper,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_MilkBox.SM_MilkBox'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_MilkBox.UT_TrashIcon_MilkBox'",
			},
		}
	},
	{
		"Juice box",
		FTrashData
		{
			ETrashTypes::Paper,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_JuiceBox.SM_JuiceBox'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_JuiceBox.UT_TrashIcon_JuiceBox'",
			},
		}
	},
	{
		"Chicken broth box",
		FTrashData
		{
			ETrashTypes::Paper,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_ChickenJuice.SM_ChickenJuice'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_ChickenBroth.UT_TrashIcon_ChickenBroth'",
			},
		}
	},
	{
		"Tissue box",
		FTrashData
		{
			ETrashTypes::Paper,
			1,
			{
				"StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Props/SM_TissueBox.SM_TissueBox'",
			},
			{
				"Texture2D'/Game/Materials/Textures/UserIcon/UT_TrashIcon_TissueBox.UT_TrashIcon_TissueBox'",
			},
		}
	},
}};

TMap<TEnumAsByte<ETrashTypes>, FTrashMap> ULootable::GetinitLootTypeMaps(FTrashMap _AllLoots)
{
	TMap<TEnumAsByte<ETrashTypes>, FTrashMap> _LootTypeMaps = {
		{ETrashTypes::Unsalvageable, {}},
		{ETrashTypes::EWaste, {}},
		{ETrashTypes::Plastic, {}},
		{ETrashTypes::Glass, {}},
		{ETrashTypes::Organic, {}},
		{ETrashTypes::Metal, {}},
		{ETrashTypes::Paper, {}},
	};

	for (TPair<FString, FTrashData> loot : _AllLoots.data) {
		loot.Value.name = loot.Key;
		_LootTypeMaps[loot.Value.type].data.Add(loot);
	}

	return _LootTypeMaps;
}

const TMap<TEnumAsByte<ETrashTypes>, FTrashMap> ULootable::LootTypeMaps = ULootable::GetinitLootTypeMaps(ULootable::AllLoots);

// Sets default values for this component's properties
ULootable::ULootable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void ULootable::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> components = GetOwner()->GetComponents().Array();
	for (UActorComponent* component : components)
	{
		if (component->IsA(USkeletalMeshComponent::StaticClass()) && !SkeletonMesh)
		{
			SkeletonMesh = Cast<USkeletalMeshComponent>(component);
		}
		if (component->IsA(UDamageableEntity::StaticClass()) && !DamageableEntity)
		{
			DamageableEntity = Cast<UDamageableEntity>(component);
		}
	}

	if (SkeletonMesh)
	{
		TArray<USkeletalMeshSocket*> sockets = SkeletonMesh->SkeletalMesh->GetActiveSocketList();
		for (USkeletalMeshSocket* socket : sockets)
		{
			if (PresetProps.Num())
			{
				FTrashSocketData trash_socket = FTrashSocketData{ socket->SocketName, GenerateProp(PresetProps.Pop(), ZoneRef) };
				Attach(trash_socket);
			}
			else
				FreeSockets.Add(socket->SocketName);
		}

		if (DamageableEntity) {
			FScriptDelegate Delegate;
			Delegate.BindUFunction(this, "UpdateFromDamage");
			DamageableEntity->OnTakeDamage.Add(Delegate);
		}
	}
	
}

FTrashData ULootable::GenerateSingleMesh(FTrashData trash)
{
	int count = trash.mesh_paths.Num();
	if (count != 1)
	{
		if (!count) 
		{
			trash.mesh_paths = { "StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Rocks/SM_LowRock.SM_LowRock'" };
		}
		else 
		{
			trash.mesh_paths = { trash.mesh_paths[FMath::RandRange(0, trash.mesh_paths.Num() - 1)] };
		}
	}
	return trash;
}

FTrashData ULootable::GenerateSingleIcon(FTrashData trash)
{
	int count = trash.icon_paths.Num();
	if (count != 1)
	{
		if (!count)
		{
			trash.icon_paths = {"Texture2D'/Game/Materials/Textures/UserIcon/UT_IconTrash.UT_IconTrash'" };
		}
		else
		{
			trash.icon_paths = { trash.icon_paths[FMath::RandRange(0, trash.icon_paths.Num() - 1)] };
		}
	}
	return trash;
}

FTrashData ULootable::GenerateProp(ETrashTypes type, APollutionZone* zone_ref)
{
	FTrashMap LootOfGivenType = GetLootTableByType(type);
	TArray<FString> LootOfGivenTypeNames;
	LootOfGivenType.data.GenerateKeyArray(LootOfGivenTypeNames);
	FString RandomLootName = LootOfGivenTypeNames[FMath::RandHelper(LootOfGivenTypeNames.Num())];
	FTrashData RandomLoot = LootOfGivenType.data[RandomLootName];

	if (zone_ref)
		RandomLoot.zone_ref = zone_ref;
	RandomLoot = GenerateSingleMesh(RandomLoot);
	RandomLoot = GenerateSingleIcon(RandomLoot);
	return RandomLoot;
}

FString ULootable::GetIconPath(FTrashData trash)
{
	return trash.icon_paths[0];
}

FString ULootable::GetMeshPath(FTrashData trash)
{
	return trash.mesh_paths[0];
}

// attaches a given socket data's mesh to a socket
void ULootable::Attach(FTrashSocketData socket)
{
	UStaticMeshComponent* prop = NewObject<UStaticMeshComponent>(this, MakeUniqueObjectName(SkeletonMesh, UStaticMeshComponent::StaticClass(), FName(TEXT("TrashSocketMesh"))));
	socket.trash = GenerateSingleMesh(socket.trash);
	prop->SetStaticMesh(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *GetMeshPath(socket.trash))));
	prop->RegisterComponent();
	prop->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	prop->SetCollisionProfileName(TEXT("OverlapAll"));

	if (prop->AttachToComponent(SkeletonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), socket.socketName))
	{
		socket.meshComponent = prop;
		socket.meshComponent->SetRelativeRotation(FRotator(
			FMath::FRandRange(-180.f, 180.f),
			FMath::FRandRange(-180.f, 180.f),
			FMath::FRandRange(-180.f, 180.f)
		));
		UsedSockets.Add(socket);
	}
}

// returns a spawnable prop based on given paramerters
AProp* ULootable::GetSpawnableProp(UWorld* propWorld, const FTransform propTransform, FTrashData propData)
{
	AProp* NewProp = propWorld->SpawnActorDeferred<AProp>(AProp::StaticClass(), propTransform, (AActor*)nullptr, (APawn*)nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	UStaticMeshComponent* NewTrashInstanceRoot = Cast<UStaticMeshComponent>(NewProp->GetRootComponent());
	NewTrashInstanceRoot->SetStaticMesh(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *GetMeshPath(propData))));
	NewProp->Collectable->Data = propData;
	NewProp->Collectable->bPlayerCreated = false;
	return NewProp;
}

FString ULootable::GetTrashTypeAsString(ETrashTypes type)
{
	switch (type)
	{
		case ETrashTypes::Unsalvageable:
			return "Unsalvageable";
			break;
		case ETrashTypes::EWaste:
			return "EWaste";
			break;
		case ETrashTypes::Plastic:
			return "Plastic";
			break;
		case ETrashTypes::Glass:
			return "Glass";
			break;
		case ETrashTypes::Organic:
			return "Organic";
			break;
		case ETrashTypes::Metal:
			return "Metal";
			break;
		case ETrashTypes::Paper:
			return "Paper";
			break;
	}
	return "Invalid Type";
}

// pops a socket "yeeting" trash into the air
void ULootable::UpdateFromDamage()
{
	float newPops;
	if (DamageableEntity->GetCurrentHealth() / DamageableEntity->GetMaxHealth() >= 0.05)
	{
		int32 totalSockets = FreeSockets.Num() + UsedSockets.Num();
		float thetaPop = DamageableEntity->GetMaxHealth() / totalSockets;
		float previousPopingthreshold = DamageableEntity->GetMaxHealth() - (thetaPop * FreeSockets.Num());
		float popdiff = previousPopingthreshold - DamageableEntity->GetCurrentHealth();
		newPops = popdiff / thetaPop;
	}
	else
	{
		newPops = UsedSockets.Num();
	}
	if (newPops >= 1)
	{
		UWorld* world = GetWorld();
		for (int i = 0; i < newPops; i++)
		{
			// gets next socket and add it's name to the free socket list
			FTrashSocketData nextTrashSocket = UsedSockets.Pop();
			FreeSockets.Add(nextTrashSocket.socketName);

			// prepare the spawn of the prop (location, rotation, spawn settings, etc.)
			const FVector propLocation = SkeletonMesh->GetSocketLocation(nextTrashSocket.socketName);
			const FTransform nextTrashTransform = FTransform(FQuat(SkeletonMesh->GetSocketRotation(nextTrashSocket.socketName)), propLocation);
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// calculates in which direction the prop should pop (Yeet!)
			FVector impulseDirection = propLocation - GetOwner()->GetActorLocation();
			impulseDirection.Normalize(0.00001);
			impulseDirection.Z = FMath::Abs(FMath::Max3(impulseDirection.X, impulseDirection.Y, impulseDirection.Z) * 1.75);
			FVector impulse = (impulseDirection) * 400;

			// create the prop, set it's static mesh and spawn it
			AProp* NewTrashInstance = GetSpawnableProp(world, nextTrashTransform, nextTrashSocket.trash);
			NewTrashInstance->FinishSpawning(nextTrashTransform);

			if (NewTrashInstance->Collectable->Data.zone_ref)
			{
				NewTrashInstance->Collectable->Data.zone_ref->UpdatePollutionUnits(-1);
			}

			// yeets the prop's root component
			UStaticMeshComponent* NewTrashInstanceRoot = Cast<UStaticMeshComponent>(NewTrashInstance->GetRootComponent());
			NewTrashInstanceRoot->AddImpulse(impulse, NAME_None, false);

			// destroys the mesh attached to the socket
			nextTrashSocket.meshComponent->DestroyComponent();

			if (!UsedSockets.Num())
				OnOwnerLooted.Broadcast();
		}
	}
}

// Called every frame
void ULootable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FTrashMap ULootable::GetLootTableByType(ETrashTypes type)
{
	return LootTypeMaps[type];
}

FTrashData ULootable::GetLootDataByName(FString name)
{
	return AllLoots.data[name];
}
