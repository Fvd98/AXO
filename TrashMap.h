#pragma once

#include "Trash.h"
#include "TrashType.h"
#include "TrashMap.generated.h"

USTRUCT(BlueprintType)
struct FTrashMap
{
	GENERATED_USTRUCT_BODY()

	TMap<FString, FTrashData> data;

	FTrashMap(TMap<FString, FTrashData> preset_map) {
		data = preset_map;
	}

	FTrashMap() {
		data = {};
	}
};
