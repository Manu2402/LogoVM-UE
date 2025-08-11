// @ Manuel Solano

#include "LogoVMFactory.h"
#include "LogoVMUtils.h"
#include "LogoVMBlueprintFunctionLibrary.h"
#include "Assets/CanvasDataAsset.h"
#include "Assets/TextureDataAsset.h"
#include "ImageUtils.h"
#include "LogoVM.h"

ULogoVMFactory::ULogoVMFactory()
{
	bEditorImport = true;
	SupportedClass = UTexture2D::StaticClass();

	Formats.Add(TEXT("logo;Logo asset"));
}

UObject* ULogoVMFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UCanvasDataAsset* CanvasDataAsset = Cast<UCanvasDataAsset>(StaticLoadObject(UCanvasDataAsset::StaticClass(), nullptr, TEXT(CANVAS_DATA_ASSET_PATH)));
	if (!CanvasDataAsset)
	{
		RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to load the canvas data asset!"));
		return nullptr;
	}

	const FString Cmd = TEXT("logo ") + Filename;
	TArray<FLinearColor> CanvasTilesColors;
	if (!ULogoVMBlueprintFunctionLibrary::LogoVMExecuteFromPath(nullptr, Cmd, CanvasDataAsset->CanvasWidth, CanvasDataAsset->CanvasHeight, CanvasTilesColors))
	{
		UE_LOG(LoggerLogoVM, Error, TEXT("Unable to generate the texture: something is failed during the execution!"))
		return nullptr;
	}

	UTextureDataAsset* TextureDataAsset = Cast<UTextureDataAsset>(StaticLoadObject(UTextureDataAsset::StaticClass(), nullptr, TEXT(TEXTURE_DATA_ASSET_PATH)));
	if (!TextureDataAsset)
	{
		RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to load the texture data asset!"));
		return nullptr;
	}

	TArray<FColor> OutPixels;
	
	const double CanvasAspectRatio = static_cast<double>(CanvasDataAsset->CanvasWidth) / static_cast<double>(CanvasDataAsset->CanvasHeight);
	const int32 TextureHeight = TextureDataAsset->TextureHeight;
	// "Width" is automatically computed in order to keep the same aspect ratio of the canvas.
	const int32 TextureWidth = FMath::RoundToInt(CanvasAspectRatio * TextureHeight);

	if (!LogoVM::Utils::TryResamplingCanvas(OutPixels, CanvasTilesColors, TextureWidth, TextureHeight, CanvasDataAsset->CanvasWidth, CanvasDataAsset->CanvasHeight))
	{
		return nullptr;
	}

	FCreateTexture2DParameters Texture2DParameters;
	return FImageUtils::CreateTexture2D(TextureWidth, TextureHeight, OutPixels, InParent, InName.ToString(), Flags, Texture2DParameters);
}
