// @ Manuel Solano

#include "LogoVMUtility.h"
#include "LogoVM.h"

namespace LogoVM
{
	namespace Utility
	{
		bool FilePathIsValid(const FString& InFilePath)
		{
			if (InFilePath.IsEmpty())
			{
				UE_LOG(LoggerLogoVM, Warning, TEXT("Logo command with empty file path is invalid!"))
				return false;
			}
	
			TArray<FString> FilePathTokens;
			InFilePath.ParseIntoArray(FilePathTokens, TEXT("."));

			if (FilePathTokens.Num() <= 1)
			{
				UE_LOG(LoggerLogoVM, Warning, TEXT("Logo command with missing base or with missing extension is invalid!"));
				return false;
			}
	
			if (!FilePathTokens.Last().Equals(TEXT("logo")))
			{
				UE_LOG(LoggerLogoVM, Warning, TEXT("Logo command with a wrong extension as a file path's suffix is invalid!"));
				return false;
			}

			return true;
		}
	}
}
