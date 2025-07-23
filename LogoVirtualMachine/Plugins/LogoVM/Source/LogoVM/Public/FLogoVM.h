// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"

namespace LogoVM
{
	class LOGOVM_API FLogoVM
	{
	public:
		FLogoVM();
		~FLogoVM();

		void Tokenize(const FString& FileContent);

		bool TokensEnqueue(const FString& Token);
		bool TokensDequeue(FString& Token);

	private:
		TQueue<FString> Tokens;
	
	};
}