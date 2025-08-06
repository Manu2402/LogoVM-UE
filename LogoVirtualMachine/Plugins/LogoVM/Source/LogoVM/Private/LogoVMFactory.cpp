// @ Manuel Solano

#include "LogoVMFactory.h"
#include "LogoVMBlueprintFunctionLibrary.h"
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
	// (60x60)
	const int32 CanvasSizeX = 60;
	const int32 CanvasSizeY = 60;

	const FString Cmd = TEXT("logo ") + Filename;
	TArray<FLinearColor> CanvasTilesColors;
	if (!ULogoVMBlueprintFunctionLibrary::LogoVMExecuteFromPath(nullptr, Cmd, CanvasSizeX, CanvasSizeY, CanvasTilesColors))
	{
		UE_LOG(LoggerLogoVM, Error, TEXT("Unable to generate the texture: something is failed during the execution!"))
		return nullptr;
	}

	TArray<FColor> OutPixels;
	const int32 PixelSize = 15; // (15x15 pixels).

	const int32 TextureSizeX = CanvasSizeX * PixelSize;
	const int32 TextureSizeY = CanvasSizeY * PixelSize;
	
	if (!TryGeneratePixelsFromPixelSize(OutPixels, CanvasTilesColors, TextureSizeX, TextureSizeY, CanvasSizeX, PixelSize))
	{
		return nullptr;
	}

	FCreateTexture2DParameters Texture2DParameters;
	return FImageUtils::CreateTexture2D(TextureSizeX, TextureSizeY, OutPixels, InParent, InName.ToString(), Flags, Texture2DParameters);
}

bool ULogoVMFactory::TryGeneratePixelsFromPixelSize(TArray<FColor>& OutPixels, const TArray<FLinearColor>& CanvasTilesColors, const int32 InTextureSizeX, const int32 InTextureSizeY, const int32 InCanvasSizeX, const int32 InPixelSize)
{
	OutPixels.AddDefaulted(CanvasTilesColors.Num() * static_cast<int32>((FMath::Pow(InPixelSize, 2.f))));

	for (int32 Index = 0; Index < CanvasTilesColors.Num(); Index++)
	{
		FColor CurrentColor = CanvasTilesColors[Index].ToFColor(true);
		
		for (int32 HeightIndex = 0; HeightIndex < InPixelSize; HeightIndex++)
		{
			for (int32 WidthIndex = 0; WidthIndex < InPixelSize; WidthIndex++)
			{
				// Re-sampling from (CanvasSizeX * CanvasSizeY) grid to (TextureSizeX * TextureSizeY) grid.
				const int32 NavigationFactor = ((Index / InCanvasSizeX) * InTextureSizeX + (Index % InCanvasSizeX));
				const int32 CurrentIndex = (NavigationFactor * InPixelSize) + WidthIndex + (HeightIndex * InTextureSizeX);

				if (CurrentIndex < 0 || CurrentIndex >= OutPixels.Num())
				{
					UE_LOG(LoggerLogoVM, Error, TEXT("Unable to generate the texture: out of bounds during re-sampling!"))
					return false;
				}
				
				OutPixels[CurrentIndex] = CurrentColor;
			}
		}
	}

	return true;
}
