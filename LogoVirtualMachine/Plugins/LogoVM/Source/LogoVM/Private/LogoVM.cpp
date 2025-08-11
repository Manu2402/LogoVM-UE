// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#include "LogoVM.h"
#include "LogoVMBlueprintFunctionLibrary.h"
#include "Assets/CanvasDataAsset.h"

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

	bool FLogoVMModule::Exec(UWorld* InWorld, const TCHAR* Cmd /* Commands stream */, FOutputDevice& Ar /* Console */)
	{
		UCanvasDataAsset* CanvasDataAsset = Cast<UCanvasDataAsset>(StaticLoadObject(UCanvasDataAsset::StaticClass(), nullptr, TEXT(CANVAS_DATA_ASSET_PATH)));
		if (!CanvasDataAsset)
		{
			RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to load the \"Canvas Data Asset\"!"));
			return false;
		}
		
		TArray<FLinearColor> CanvasTilesColors;
		return ULogoVMBlueprintFunctionLibrary::LogoVMExecuteFromPath(InWorld, Cmd, CanvasDataAsset->CanvasWidth, CanvasDataAsset->CanvasHeight, CanvasTilesColors);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(LogoVM::FLogoVMModule, LogoVM)