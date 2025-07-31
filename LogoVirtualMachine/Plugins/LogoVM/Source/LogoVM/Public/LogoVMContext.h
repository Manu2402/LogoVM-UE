// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"

namespace LogoVM
{
	class LOGOVM_API FLogoVMContext
	{

	using FCommand = TFunction<bool(TQueue<FString>& Tokens)>;
		
	public:
		FLogoVMContext();
		FLogoVMContext(const FIntPoint InCanvasSize, const FIntPoint InTurtlePosition, const int32 InTurtleRotation, const bool bInIsTurtleUp);
		
		~FLogoVMContext() = default;
		
		FLogoVMContext(const FLogoVMContext& Other) = delete;
		FLogoVMContext(FLogoVMContext&& Other) = delete;
		FLogoVMContext& operator=(const FLogoVMContext& Other) = delete;
		FLogoVMContext& operator=(FLogoVMContext&& Other) = delete;
		
		bool Execute(TQueue<FString>& Tokens);

		FIntPoint GetCanvasSize() const;
		const TArray<FLinearColor>& GetCanvasTilesColors() const;

		FIntPoint GetTurtlePosition() const;
		
	private:
		FIntPoint CanvasSize;
		TMap<FString, FCommand> Commands;
		TArray<FLinearColor> CanvasTilesColors;
		FLinearColor ActiveColor;
		FIntPoint TurtlePosition;
		double TurtleRotation; // Rotations are represented inversely, using clock-wise direction.
		bool bIsTurtleUp;

	private:
		void InitLogoVM();
		FVector2D GetTurtleRotationVector() const;
		void Move(const FIntPoint OldTurtlePosition, const FIntPoint TurtleTraslation);

	};
}