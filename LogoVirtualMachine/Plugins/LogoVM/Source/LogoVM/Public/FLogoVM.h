// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"
#include "FLogoVM.h"

namespace LogoVM
{
	class LOGOVM_API FLogoVM
	{
		using FCommand = TFunction<bool(TQueue<FString>& Tokens)>;
		
	public:
		FLogoVM();
		FLogoVM(const FIntPoint CanvasSize); // TO COMPLETE
		
		~FLogoVM() = default;
		
		FLogoVM(const FLogoVM& Other) = delete;
		FLogoVM(FLogoVM&& Other) = delete;
		FLogoVM& operator=(const FLogoVM& Other) = delete;
		FLogoVM& operator=(FLogoVM&& Other) = delete;
		
		bool Execute(TQueue<FString>& Tokens);

		FIntPoint GetCanvasSize() const;
		const TArray<FLinearColor>& GetTilesColors() const;
		
	private:
		FIntPoint CanvasSize;
		TMap<FString, FCommand> Commands;
		TArray<FLinearColor> TilesColors;
		FIntPoint Position;
		double Rotation; // Rotations are represented inversely, using clock-wise direction.
		bool bIsPenUp;

	private:
		void InitLogoVM();
		void Move(const FIntPoint OldPosition, const FIntPoint Translation);
		
		FVector2D GetRotationVector() const;

	};
}