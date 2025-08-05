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

	// Trick for abstract the world handler from blueprints.
	UFUNCTION(BlueprintCallable, Category = "LogoVMBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static bool LogoVMExecuteFromPath(UObject* WorldContextObject, const FString& Cmd);
	
	UFUNCTION(BlueprintCallable, Category = "LogoVMBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
    static bool LogoVMExecuteFromContent(UObject* WorldContextObject, const FString& Content);
};
