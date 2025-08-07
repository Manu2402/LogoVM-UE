// @ Manuel Solano

#include "LogoVMFactory.h"
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
	UCanvasDataAsset* CanvasDataAsset = Cast<UCanvasDataAsset>(StaticLoadObject(UCanvasDataAsset::StaticClass(), nullptr, TEXT("/LogoVM/Assets/CanvasDataAsset.CanvasDataAsset")));
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

	UTextureDataAsset* TextureDataAsset = Cast<UTextureDataAsset>(StaticLoadObject(UTextureDataAsset::StaticClass(), nullptr, TEXT("/LogoVM/Assets/TextureDataAsset.TextureDataAsset")));
	if (!TextureDataAsset)
	{
		RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to load the texture data asset!"));
		return nullptr;
	}

	TArray<FColor> OutPixels;
	
	const double CanvasAspectRatio = static_cast<double>(CanvasDataAsset->CanvasWidth) / static_cast<double>(CanvasDataAsset->CanvasHeight);
	const int32 TextureHeight = TextureDataAsset->TextureHeight;
	// Width is automatically computed in order to keep the same aspect ratio of the canvas.
	const int32 TextureWidth = FMath::RoundToInt(CanvasAspectRatio * TextureHeight);

	if (!TryResamplingCanvas(OutPixels, CanvasTilesColors, TextureWidth, TextureHeight, CanvasDataAsset->CanvasWidth, CanvasDataAsset->CanvasHeight))
	{
		return nullptr;
	}

	FCreateTexture2DParameters Texture2DParameters;
	return FImageUtils::CreateTexture2D(TextureWidth, TextureHeight, OutPixels, InParent, InName.ToString(), Flags, Texture2DParameters);
}

bool ULogoVMFactory::TryResamplingCanvas(TArray<FColor>& OutPixels, const TArray<FLinearColor>& CanvasTilesColors, const int32 InTextureWidth, const int32 InTextureHeight, const int32 InCanvasWidth, const int32 InCanvasHeight)
{
	OutPixels.SetNum(InTextureWidth * InTextureHeight);

	// Normalization.
	const float ScaleX = static_cast<float>(InCanvasWidth) / InTextureWidth;
	const float ScaleY = static_cast<float>(InCanvasHeight) / InTextureHeight;

	for (int32 Y = 0; Y < InTextureHeight; Y++)
	{
		for (int32 X = 0; X < InTextureWidth; X++)
		{
			const int32 PixelIndex = X + Y * InTextureWidth;

			const int32 CanvasX = FMath::Clamp(FMath::FloorToInt(X * ScaleX), 0, InCanvasWidth - 1);
			const int32 CanvasY = FMath::Clamp(FMath::FloorToInt(Y * ScaleY), 0, InCanvasHeight - 1);

			const int32 CanvasIndex = CanvasX + CanvasY * InCanvasWidth;

			if (!CanvasTilesColors.IsValidIndex(CanvasIndex))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("Unable to generate the texture: out of bounds during re-sampling!"), CanvasIndex);
				return false;
			}

			OutPixels[PixelIndex] = CanvasTilesColors[CanvasIndex].ToFColor(true);
		}
	}
	
	return true;
}
