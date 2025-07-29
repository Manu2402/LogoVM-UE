// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"

namespace LogoVM
{
	namespace Utils
	{
		LOGOVM_API bool FilePathIsValid(const FString& FilePath);
		LOGOVM_API bool IsOutOfBounds(const FIntPoint Position, const FIntPoint CanvasSize);
		LOGOVM_API void Tokenize(TQueue<FString>& OutTokens, const FString& FileContent);
		
		bool TrySpawnCanvas(TArray<AActor*>& OutCanvasTiles, UWorld* InWorld, FIntPoint CanvasSize);
	}
}
