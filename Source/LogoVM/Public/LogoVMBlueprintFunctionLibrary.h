// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogoVMBlueprintFunctionLibrary.generated.h"

UCLASS()
class LOGOVM_API ULogoVMBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()

	// "WorldContext" --> Trick for abstract the world handler from blueprints.
	UFUNCTION(BlueprintCallable, Category = "LogoVMBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool LogoVMExecuteFromPath(UObject* WorldContextObject, const FString& Cmd, const int32 CanvasWidth, const int32 CanvasHeight, TArray<FLinearColor>& CanvasTilesColors);
	
	UFUNCTION(BlueprintCallable, Category = "LogoVMBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
    static bool LogoVMExecuteFromContent(UObject* WorldContextObject, const FString& Content, const int32 CanvasWidth, const int32 CanvasHeight, TArray<FLinearColor>& CanvasTilesColors);
};
