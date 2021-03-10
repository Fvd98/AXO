#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.h"
#include "Magnetized.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Prop.generated.h"

UCLASS()
class FRITESMOLLES_API AProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop")
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Prop")
		UMagnetized* Magnetized;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Prop")
		UCollectable* Collectable;
};
