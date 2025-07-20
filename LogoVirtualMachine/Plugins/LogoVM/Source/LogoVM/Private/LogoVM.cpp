// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#include "LogoVM.h"

DEFINE_LOG_CATEGORY(LoggerLogoVM);

#define LOCTEXT_NAMESPACE "FLogoVMModule"

void FLogoVMModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FLogoVMModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FLogoVMModule::Exec(UWorld* InWorld, const TCHAR* Cmd /* Command's Steam */, FOutputDevice& Ar /* Console */)
{
	if (!FParse::Command(&Cmd, TEXT("Logo")))
	{
		return false;
	}

	const FString FilePath = FParse::Token(Cmd, false);
	if (!FilePathIsValid(FilePath))
	{
		return false;
	}

	// TODO: Implement Unit Tests

	// Loading .logo file, and read it.
	// ...

	return true;
}

bool FLogoVMModule::FilePathIsValid(const FString& InFilePath) const
{
	if (InFilePath.IsEmpty())
	{
		UE_LOG(LoggerLogoVM, Warning, TEXT("There isn't filepath!"))
		return false;
	}
	
	TArray<FString> FilePathTokens;
	InFilePath.ParseIntoArray(FilePathTokens, TEXT("."));

	if (FilePathTokens.Num() <= 1)
	{
		UE_LOG(LoggerLogoVM, Error, TEXT("This filepath has no extension or has no name!"));
		return false;
	}
	
	if (!FilePathTokens.Last().Equals(TEXT("Logo")))
	{
		UE_LOG(LoggerLogoVM, Error, TEXT("This filepath doesn't represent a LOGO program!"));
		return false;
	}

	// Correct Example: "logo path/to/logo/file.logo"
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLogoVMModule, LogoVM)