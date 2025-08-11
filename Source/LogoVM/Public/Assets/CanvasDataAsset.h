// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CanvasDataAsset.generated.h"

UCLASS()
class LOGOVM_API UCanvasDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Canvas", meta = (ClampMin = 1))
	int32 CanvasWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Canvas", meta = (ClampMin = 1))
	int32 CanvasHeight;
	
};
