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
		FLogoVMContext(const FIntPoint InCanvasSize, const FIntPoint InTurtlePosition, const int32 InTurtleRotation, const bool bInIsTurtleUp, const int32 InDefaultBackgroundColor);
		
		~FLogoVMContext() = default;
		
		FLogoVMContext(const FLogoVMContext& Other) = delete;
		FLogoVMContext(FLogoVMContext&& Other) = delete;
		FLogoVMContext& operator=(const FLogoVMContext& Other) = delete;
		FLogoVMContext& operator=(FLogoVMContext&& Other) = delete;
		
		bool Execute(TQueue<FString>& Tokens);

		FIntPoint GetCanvasSize() const;
		const TArray<FLinearColor>& GetCanvasTilesColors() const;

#if WITH_DEV_AUTOMATION_TESTS
		FLinearColor GetDefaultBackgroundColor() const;
		FIntPoint GetTurtlePosition() const;
		int32 GetTurtleRotation() const;
		bool GetIsTurtleUp() const;
#endif
		
	private:
		FIntPoint CanvasSize;
		TMap<FString, FCommand> Commands;
		TArray<FLinearColor> CanvasTilesColors;
		const FLinearColor DefaultBackgroundColor;
		FLinearColor ActiveColor;
		FIntPoint TurtlePosition;
		int32 TurtleRotation; // Rotations are represented inversely, using clock-wise direction.
		bool bIsTurtleUp;

	private:
		void InitLogoVM();
		void Move(const FIntPoint OldTurtlePosition, const FIntPoint TurtleTraslation);
		void DumpTokens(TQueue<FString>& OutDumpedTokens, TQueue<FString>& TokensToDump);
		
		FVector2D GetTurtleRotationVector() const;
		
	};
}