// @ Manuel Solano

#include "FLogoVM.h"
#include "LogoVM.h"
#include "Engine/World.h"

namespace LogoVM
{
#pragma region FLogoVM
	FLogoVM::FLogoVM() : CanvasSize(FVector2D(15))
	{
		InitLogoVM();
	}

	FLogoVM::FLogoVM(const FVector2D InCanvasSize) : CanvasSize(InCanvasSize)
	{
		InitLogoVM();
	}

	FLogoVM::~FLogoVM()
	{
	}

	bool FLogoVM::Execute(TQueue<FString>& Tokens)
	{
		FString CurrentToken;
		while (Tokens.Dequeue(CurrentToken))
		{
			if (!Commands.Contains(CurrentToken))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("Execution failed: the current command: %s is not supported at the time!"), *CurrentToken);
				return false;
			}

			Commands[CurrentToken](*this, Tokens);
		}

		return true;
	}

	FVector2D FLogoVM::GetCanvasSize() const
	{
		return CanvasSize;
	}

	void FLogoVM::InitLogoVM()
	{
#pragma region Commands
		Commands.Add(TEXT("fd"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"fd\" command"));

			return true;
		});
		Commands.Add(TEXT("bk"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"bk\" command"));

			return true;
		});
		Commands.Add(TEXT("rt"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"rt\" command"));

			return true;
		});
		Commands.Add(TEXT("lt"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"lt\" command"));

			return true;
		});
		Commands.Add(TEXT("ct"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"ct\" command"));

			return true;
		});
		Commands.Add(TEXT("cs"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"cs\" command"));

			return true;
		});
		Commands.Add(TEXT("pu"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"pu\" command"));

			return true;
		});
		Commands.Add(TEXT("pd"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"pd\" command"));

			return true;
		});
		Commands.Add(TEXT("pc"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"pc\" command"));

			return true;
		});
		Commands.Add(TEXT("ps"), [](FLogoVM& LogoVM, TQueue<FString>& Tokens)
		{
			UE_LOG(LogTemp, Warning, TEXT("\"ps\" command"));

			return true;
		});
#pragma region // Commands
	}
#pragma endregion // FLogoVM
}
