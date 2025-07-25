// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"
#include "FLogoVM.h"

namespace LogoVM
{
	class LOGOVM_API FLogoVM
	{
	using FCommand = TFunction<bool(FLogoVM& LogoVM, TQueue<FString>& Tokens)>;
		
	public:
		FLogoVM();
		FLogoVM(const FVector2D CanvasSize);
		~FLogoVM();
		
		FLogoVM(const FLogoVM& Other) = delete;
		FLogoVM(FLogoVM&& Other) = delete;
		FLogoVM& operator=(const FLogoVM& Other) = delete;
		FLogoVM& operator=(FLogoVM&& Other) = delete;

		bool Execute(TQueue<FString>& Tokens);

		FVector2D GetCanvasSize() const;

	private:
		FVector2D CanvasSize;
		TMap<FString, FCommand> Commands;

	private:
		void InitLogoVM();

	};
	
}