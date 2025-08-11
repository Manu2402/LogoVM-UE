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
			/* 0 */ FLinearColor::White,                              
			/* 1 */ FLinearColor::Black,
			/* 2 */ FLinearColor::Red,
			/* 3 */ FLinearColor::Green,
			/* 4 */ FLinearColor::Blue,
			/* 5 */ FLinearColor::Yellow,
			/* 6 */ FLinearColor(0.f, 1.f, 1.f),       // Cyan
			/* 7 */ FLinearColor(0.35f, 0.13f, 0.55f), // Magenta
			/* 8 */ FLinearColor(1.f, 0.65f, 0.f)      // Orange

			// You can expand the set of available colors!
		};
		
		LOGOVM_API bool FilePathIsValid(const FString& FilePath);
		LOGOVM_API bool IsOutOfBounds(const FIntPoint Position, const FIntPoint CanvasSize);
		LOGOVM_API void Tokenize(TQueue<FString>& OutTokens, const FString& FileContent);
	    LOGOVM_API bool TryResamplingCanvas(TArray<FColor>& OutPixels, const TArray<FLinearColor>& CanvasTilesColors, const int32 InTextureWidth, const int32 InTextureHeight, const int32 InCanvasWidth,  const int32 InCanvasHeight);
		
		bool TrySpawnCanvas(TArray<AActor*>& OutCanvasTiles, UWorld* InWorld, FIntPoint CanvasSize);
	}
}
