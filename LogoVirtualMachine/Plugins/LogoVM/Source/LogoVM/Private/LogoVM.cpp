// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#include "LogoVM.h"
#include "LogoVMUtility.h"
#include "FLogoVM.h"
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

	bool FLogoVMModule::Exec(UWorld* InWorld, const TCHAR* Cmd /* Command's Steam */, FOutputDevice& Ar /* Console */)
	{
		if (!InWorld)
		{
			return false;
		}
	
		if (!FParse::Command(&Cmd, TEXT("Logo")))
		{
			return false;
		}

		const FString FilePath = FParse::Token(Cmd, false);
		if (!Utility::FilePathIsValid(FilePath))
		{
			return false;
		}
	
		FString FileContent;
		if (!FFileHelper::LoadFileToString(FileContent, *FilePath))
		{
			UE_LOG(LoggerLogoVM, Error, TEXT("Loading failed: %s!"), *FilePath);
			return false;
		}

		TQueue<FString>	Tokens;
		Utility::Tokenize(Tokens, FileContent);
	
		FLogoVM LogoVM;

		TArray<AActor*> Tiles;
		if (!Utility::TrySpawnCanvas(Tiles, InWorld, LogoVM.GetCanvasSize()))
		{
			return false;
		}
	
		if (!LogoVM.Execute(Tokens))
		{
			return false;
		}

		const TArray<FLinearColor>& TilesColors =  LogoVM.GetTilesColors();

		for (int32 Index = 0; Index < Tiles.Num(); Index++)
		{
			// In order to call "Init", found in "BP_Cube".
			const FString InitFunction = TEXT("Init");
			
			// In order to call "SetColor { R, G, B, A }", found in "BP_Cube".
			// "Tiles" and "TilesColors" has same size at this point! So, i avoid overengineering.
			const FString SetColorFunction = FString::Printf(TEXT("SetColor %s"), *(TilesColors[Index].ToString()));

			FOutputDeviceNull OutputDeviceNull;
			
			if (!Tiles[Index]->CallFunctionByNameWithArguments(*InitFunction, OutputDeviceNull, nullptr, true))
			{
				return false;
			}
			
			if (!Tiles[Index]->CallFunctionByNameWithArguments(*SetColorFunction, OutputDeviceNull, nullptr, true))
			{
				return false;
			}
		}

		return true;
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(LogoVM::FLogoVMModule, LogoVM)