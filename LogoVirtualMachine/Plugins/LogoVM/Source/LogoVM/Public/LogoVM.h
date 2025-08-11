// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LoggerLogoVM, Log, All);

#define CANVAS_DATA_ASSET_PATH "/LogoVM/Assets/CanvasDataAsset.CanvasDataAsset"
#define TEXTURE_DATA_ASSET_PATH "/LogoVM/Assets/TextureDataAsset.TextureDataAsset"
#define BLUEPRINT_CUBE_CLASS_PATH "/LogoVM/Blueprints/BP_Cube.BP_Cube_C"


// Macro to avoid "runtime error logs" when automation tests are being performed.
#define RUNTIME_LOG(CategoryName, Verbosity, FormatString, ...)         \
	if (!GIsAutomationTesting)                                          \
	{                                                                   \
		UE_LOG(CategoryName, Verbosity, FormatString, ##__VA_ARGS__)    \
	}                                                                   \

namespace LogoVM
{
	class FLogoVMModule : public IModuleInterface, public FSelfRegisteringExec
	{
	public:

		/** IModuleInterface implementation */
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;

		// FSelfRegisteringExec --> Console's commands listener.
		virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
		
	};
}
