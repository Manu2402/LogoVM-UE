// Copyright Epic Games, Inc. All Rights Reserved.
// @ Manuel Solano

#pragma once

#include "Modules/ModuleManager.h"

class FLogoVMTestsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

};
