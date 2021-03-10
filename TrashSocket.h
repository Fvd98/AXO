#pragma once

#include "Trash.h"
#include "TrashSocket.generated.h"

USTRUCT(BlueprintType)
struct FTrashSocketData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	FTrashData trash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trash")
	FName socketName;

	UStaticMeshComponent* meshComponent;

	FTrashSocketData(FName preset_name, FTrashData preset_trash) {
		trash = preset_trash;
		socketName = preset_name;
		meshComponent = nullptr;
	}

	FTrashSocketData(FName preset_name) {
		trash = FTrashData();
		socketName = preset_name;
		meshComponent = nullptr;
	}

	FTrashSocketData() {
		trash = FTrashData();
		socketName = FName(TEXT("Socket_Name"));
		meshComponent = nullptr;
	}
};