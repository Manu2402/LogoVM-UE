// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TextureDataAsset.generated.h"

UCLASS()
class LOGOVM_API UTextureDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Canvas", meta = (ClampMin = 1))
	int32 TextureHeight;
	
};
