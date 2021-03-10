#pragma once

#include "SArray.generated.h"


USTRUCT(BlueprintType)
struct FSArray
{
	GENERATED_USTRUCT_BODY()

	TArray<FString> Array;

	FSArray(TArray<FString> preset_array) {
		Array = preset_array;
	}

	FSArray() {
		Array = {};
	}
};
