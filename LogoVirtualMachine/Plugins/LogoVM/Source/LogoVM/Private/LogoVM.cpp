// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#include "LogoVM.h"
#include "LogoVMUtility.h"
#include "FLogoVM.h"

#define LOCTEXT_NAMESPACE "FLogoVMModule"

DEFINE_LOG_CATEGORY(LoggerLogoVM);

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
	if (!LogoVM::Utility::FilePathIsValid(FilePath))
	{
		return false;
	}
	
	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		return false;
	}

	LogoVM::FLogoVM LogoVM;
	LogoVM.Tokenize(FileContent);
	
	// Interpret sequentially all tokens...
	
	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLogoVMModule, LogoVM)