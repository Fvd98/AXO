#pragma once

#include "TrashType.h"
#include "Trash.generated.h"

class APollutionZone;

USTRUCT(BlueprintType)
struct FTrashData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	TArray<FString> mesh_paths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	TArray<FString> icon_paths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	int value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	TEnumAsByte<ETrashTypes> type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	APollutionZone* zone_ref;

	FTrashData() {
		type = ETrashTypes::Unsalvageable;
		name = "Nothing";
		value = -1;
		mesh_paths = { "StaticMesh'/Game/Geometry/StaticMeshes/Enviro/Rocks/SM_LowRock.SM_LowRock'" };
		icon_paths = { "Texture2D'/Game/Materials/Textures/UserIcon/icons_vide.icons_vide'" };
		zone_ref = nullptr;
	}

	FTrashData(ETrashTypes preset_type, FString preset_name, int32 preset_value, TArray<FString> preset_mesh_paths, TArray<FString> preset_icon_paths, APollutionZone* preset_zone_ref) {
		type = preset_type;
		name = preset_name;
		value = preset_value;
		mesh_paths = preset_mesh_paths;
		icon_paths = preset_icon_paths;
		zone_ref = preset_zone_ref;
	}

	FTrashData(ETrashTypes preset_type, int32 preset_value, TArray<FString> preset_mesh_paths, TArray<FString> preset_icon_paths) {
		type = preset_type;
		name = "";
		value = preset_value;
		mesh_paths = preset_mesh_paths;
		icon_paths = preset_icon_paths;
	}
};
