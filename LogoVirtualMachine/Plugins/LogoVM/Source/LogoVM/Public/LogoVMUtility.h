// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"

namespace LogoVM
{
	namespace Utility
	{
		LOGOVM_API bool FilePathIsValid(const FString& FilePath);
		LOGOVM_API void Tokenize(TQueue<FString>& OutTokens, const FString& FileContent);
		LOGOVM_API bool IsOutOfBounds(const FIntPoint Position, const FIntPoint CanvasSize);
		
		bool TrySpawnCanvas(TArray<AActor*>& Tiles, UWorld* InWorld, const FIntPoint CanvasSize);
	}
}
