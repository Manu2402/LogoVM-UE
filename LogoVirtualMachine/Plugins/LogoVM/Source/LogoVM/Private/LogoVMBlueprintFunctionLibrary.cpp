// @ Manuel Solano

#include "LogoVMBlueprintFunctionLibrary.h"
#include "LogoVMContext.h"
#include "LogoVMUtils.h"
#include "LogoVM.h"
#include "Misc/OutputDeviceNull.h"

bool ULogoVMBlueprintFunctionLibrary::LogoVMExecuteFromPath(UObject* WorldContextObject, const FString& Cmd)
{
	const TCHAR* CmdChars = Cmd.GetCharArray().GetData();

	// The command must start with the "logo" word!
	if (!FParse::Command(&CmdChars, TEXT("Logo")))
	{
		return false;
	}

	// The command must contain a valid file path to a ".logo" file!
	const FString FilePath = FParse::Token(CmdChars, false);
	if (!LogoVM::Utils::FilePathIsValid(FilePath))
	{
		return false;
	}

	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The loading of \"%s\"'s content is failed!"), *FilePath);
		return false;
	}

	return LogoVMExecuteFromContent(WorldContextObject, FileContent);
}

bool ULogoVMBlueprintFunctionLibrary::LogoVMExecuteFromContent(UObject* WorldContextObject, const FString& Content)
{
	if (!WorldContextObject)
	{
		return false;
	}

	if (!GEngine)
	{
		return false;
	}
	
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	if (!World)
	{
		return false;
	}
	
	TQueue<FString> Tokens;
	LogoVM::Utils::Tokenize(Tokens, Content);

	// LOGO Virtual Machine.
	LogoVM::FLogoVMContext LogoVMContext = { FIntPoint(50, 50), FIntPoint(25, 25), 270, false, 0 };

	TArray<AActor*> CanvasTiles;
	if (!LogoVM::Utils::TrySpawnCanvas(CanvasTiles, World, LogoVMContext.GetCanvasSize()))
	{
		return false;
	}

	if (!LogoVMContext.Execute(Tokens))
	{
		return false;
	}

	const TArray<FLinearColor>& CanvasTilesColors = LogoVMContext.GetCanvasTilesColors();

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
			RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to call the \"Init\" function in BP_Cube!"));
			return false;
		}

		if (!CanvasTiles[Index]->CallFunctionByNameWithArguments(*SetColorFunction, OutputDeviceNull, nullptr, true))
		{
			RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to call the \"SetColor\" function in BP_Cube!"));
			return false;
		}
	}

	return true;
}
