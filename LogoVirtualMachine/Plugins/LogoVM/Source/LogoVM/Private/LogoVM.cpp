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
	if (!InWorld)
	{
		return false;
	}
	
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
		UE_LOG(LoggerLogoVM, Error, TEXT("Loading failed: %s!"), *FilePath);
		return false;
	}

	TQueue<FString>	Tokens;
	LogoVM::Utility::Tokenize(Tokens, FileContent);
	
	LogoVM::FLogoVM LogoVM({14, 7});

	if (!SpawnCanvas(InWorld, LogoVM))
	{
		return false;
	}
	
	return LogoVM.Execute(Tokens);
}

bool FLogoVMModule::SpawnCanvas(UWorld* InWorld, LogoVM::FLogoVM& LogoVM)
{
	// Spawn canvas, composed by cubes as tiles.
	UClass* CubeClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/LogoVM/Blueprints/BP_Cube.BP_Cube_C"));

	if (!CubeClass)
	{
		UE_LOG(LoggerLogoVM, Error, TEXT("Unable to load the canvas!"));
		return false;
	}

	// To adapt the canvas generation by cube's scale.
	const FVector CubeDefaultSize = { 100, 100, 100 }; // 100 cm
	const FRotator Rotation = FRotator::ZeroRotator;

	FVector CubeScale = FVector::OneVector;
	FVector CubeSize = FVector::OneVector;
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	bool bFirstCube = true;

	for (int32 HeightIndex = 0; HeightIndex < LogoVM.GetCanvasSize().Y; HeightIndex++)
	{
		for (int32 WidthIndex = 0; WidthIndex < LogoVM.GetCanvasSize().X; WidthIndex++)
		{
			AActor* Cube = InWorld->SpawnActor<AActor>(CubeClass, FVector::ZeroVector, Rotation, SpawnParameters);
			if (!Cube)
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("Unable to create the canvas: ACTOR!"));
				return false;
			}

			if (bFirstCube)
			{
				UStaticMeshComponent* StaticMeshComponent = Cube->FindComponentByClass<UStaticMeshComponent>();
				if (!StaticMeshComponent)
				{
					UE_LOG(LoggerLogoVM, Error, TEXT("Unable to create the canvas: MESH"));
					return false;
				}

				CubeScale = StaticMeshComponent->GetRelativeScale3D();
				CubeSize = { CubeDefaultSize.X * CubeScale.X, CubeDefaultSize.Y * CubeScale.Y, CubeDefaultSize.Z * CubeScale.Z };

				bFirstCube = false;
			}
			
			FVector CurrentLocation = { CubeSize.X * WidthIndex, CubeSize.Y * HeightIndex, CubeDefaultSize.Z * CubeScale.Z * 0.5f };
			Cube->SetActorLocation(CurrentLocation);
		}
	}

	// FEATURE: Find a way to merge in one static mesh all the cubes.

	return true;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLogoVMModule, LogoVM)