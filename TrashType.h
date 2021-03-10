#pragma once

#include "TrashType.generated.h"

UENUM(BlueprintType)
enum ETrashTypes
{
	Unsalvageable,
	EWaste,
	Plastic,
	Glass,
	Organic,
	Metal,
	Paper,
	COUNT
};
