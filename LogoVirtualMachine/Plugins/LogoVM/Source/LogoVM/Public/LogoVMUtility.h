// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"

namespace LogoVM
{
	namespace Utility
	{
		LOGOVM_API bool FilePathIsValid(const FString& FilePath);
		LOGOVM_API void Tokenize(TQueue<FString>& OutTokens, const FString& FileContent);
	}
}
