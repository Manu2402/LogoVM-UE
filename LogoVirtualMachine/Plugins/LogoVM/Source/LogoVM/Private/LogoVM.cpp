// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#include "LogoVM.h"
#include "LogoVMUtils.h"
#include "LogoVMContext.h"
#include "IContentBrowserSingleton.h"
#include "Misc/OutputDeviceNull.h"

#define LOCTEXT_NAMESPACE "FLogoVMModule"

DEFINE_LOG_CATEGORY(LoggerLogoVM);

namespace LogoVM
{
	void FLogoVMModule::StartupModule()
	{
		// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	}

	void FLogoVMModule::ShutdownModule()
	{
		// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
		// we call this function before unloading the module.
	}

	bool FLogoVMModule::Exec(UWorld* InWorld, const TCHAR* Cmd /* Command's stream */, FOutputDevice& Ar /* Console */)
	{
		if (!InWorld)
		{
			return false;
		}

		// The command must start with the "logo" word!
		if (!FParse::Command(&Cmd, TEXT("Logo")))
		{
			return false;
		}

		// The command must contain a valid file path to a ".logo" file!
		const FString FilePath = FParse::Token(Cmd, false);
		if (!Utils::FilePathIsValid(FilePath))
		{
			return false;
		}
	
		FString FileContent;
		if (!FFileHelper::LoadFileToString(FileContent, *FilePath))
		{
			UE_LOG(LoggerLogoVM, Error, TEXT("Loading of \"%s\"'s content is failed!"), *FilePath);
			return false;
		}

		TQueue<FString>	Tokens;
		Utils::Tokenize(Tokens, FileContent);
	
		FLogoVMContext LogoVMContext;

		TArray<AActor*> CanvasTiles;
		if (!Utils::TrySpawnCanvas(CanvasTiles, InWorld, LogoVMContext.GetCanvasSize()))
		{
			return false;
		}
	
		if (!LogoVMContext.Execute(Tokens))
		{
			return false;
		}

		const TArray<FLinearColor>& CanvasTilesColors =  LogoVMContext.GetCanvasTilesColors();

		for (int32 Index = 0; Index < CanvasTiles.Num(); Index++)
		{
			// In order to call "Init", found in "BP_Cube".
			const FString InitFunction = TEXT("Init");
			
			// In order to call "SetColor { R, G, B, A }", found in "BP_Cube".
			// "CanvasTiles" and "CanvasTilesColors" has same size at this point! So, i avoid overengineering.
			const FString SetColorFunction = FString::Printf(TEXT("SetColor %s"), *(CanvasTilesColors[Index].ToString()));

			FOutputDeviceNull OutputDeviceNull;
			
			if (!CanvasTiles[Index]->CallFunctionByNameWithArguments(*InitFunction, OutputDeviceNull, nullptr, true))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("Unable to call the \"Init\" function in BP_Cube!"));
				return false;
			}
			
			if (!CanvasTiles[Index]->CallFunctionByNameWithArguments(*SetColorFunction, OutputDeviceNull, nullptr, true))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("Unable to call the \"SetColor\" function in BP_Cube!"));
				return false;
			}
		}

		return true;
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(LogoVM::FLogoVMModule, LogoVM)