// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LoggerLogoVM, Log, All);

class FLogoVMModule : public IModuleInterface, public FSelfRegisteringExec
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// FSelfRegisteringExec --> Console's commands listener.
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	
};
