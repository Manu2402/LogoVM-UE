// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"

namespace LogoVM
{
	namespace Utils
	{
		// For avoid re-definition in another classes that imports this ".h". 
		inline const TArray<FLinearColor> AvailableColors = 
		{
			FLinearColor::White,
			FLinearColor::Black,
			FLinearColor::Red,
			FLinearColor::Green,
			FLinearColor::Blue,
			FLinearColor::Yellow,
			FLinearColor(0.f, 1.f, 1.f), // Cyan
			FLinearColor(0.35f, 0.13f, 0.55f), // Magenta
			FLinearColor(1.f, 0.65f, 0.f) // Orange

			// You can expand the set of available colors!
		};
		
		LOGOVM_API bool FilePathIsValid(const FString& FilePath);
		LOGOVM_API bool IsOutOfBounds(const FIntPoint Position, const FIntPoint CanvasSize);
		LOGOVM_API void Tokenize(TQueue<FString>& OutTokens, const FString& FileContent);
		
		bool TrySpawnCanvas(TArray<AActor*>& OutCanvasTiles, UWorld* InWorld, FIntPoint CanvasSize);
	}
}
