// @ Manuel Solano

#include "FLogoVM.h"
#include "LogoVM.h"
#include "LogoVMUtility.h"

namespace LogoVM
{
#pragma region FLogoVM
	// Odd resolutions on canvas in order to have a perfect center (not required).
	FLogoVM::FLogoVM() : CanvasSize(FIntPoint(15, 15)), Position(FIntPoint(CanvasSize.X * 0.5f, CanvasSize.Y * 0.5f)), Rotation(90), bIsPenUp(false)
	{
		InitLogoVM();
	}

	FLogoVM::FLogoVM(const FIntPoint InCanvasSize) : CanvasSize(InCanvasSize)
	{
		InitLogoVM();
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

			Commands[CurrentToken](Tokens);
		}

		return true;
	}

	FIntPoint FLogoVM::GetCanvasSize() const
	{
		return CanvasSize;
	}
	
	void FLogoVM::InitLogoVM()
	{
		const uint32 CanvasResolution = CanvasSize.X * CanvasSize.Y;
		TilesColors.Init(FLinearColor::White, CanvasResolution);

#pragma region Commands
		Commands.Add(TEXT("fd"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The forward command arguments isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);
			const FVector2D RotationVector = GetRotationVector();

			FIntPoint Translation;
			Translation.X = Arg * FMath::RoundToInt(RotationVector.X);
			Translation.Y = Arg * FMath::RoundToInt(RotationVector.Y);

			const FIntPoint NewPosition = Position + Translation;

			if (Utility::IsOutOfBounds(NewPosition, CanvasSize))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The forward command has finished with an out of bounds!"));
				return false;
			}

			Move(Position, Translation);
			Position = NewPosition;

			return true;
		});
		Commands.Add(TEXT("bk"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The backward command arguments isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);
			const FVector2D RotationVector = GetRotationVector();

			FIntPoint Translation;
			Translation.X = -(Arg * RotationVector.X);
			Translation.Y = -(Arg * RotationVector.Y);

			const FIntPoint NewPosition = Position + Translation;

			if (Utility::IsOutOfBounds(NewPosition, CanvasSize))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The backward command has finished with an out of bounds!"));
				return false;
			}

			Move(Position, Translation);
			Position = NewPosition;

			return true;
		});
		Commands.Add(TEXT("rt"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"rt\" command"));

			return true;
		});
		Commands.Add(TEXT("lt"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"lt\" command"));

			return true;
		});
		Commands.Add(TEXT("ct"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"ct\" command"));

			return true;
		});
		Commands.Add(TEXT("cs"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"cs\" command"));

			return true;
		});
		Commands.Add(TEXT("pu"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"pu\" command"));

			return true;
		});
		Commands.Add(TEXT("pd"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"pd\" command"));

			return true;
		});
		Commands.Add(TEXT("pc"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"pc\" command"));

			return true;
		});
		Commands.Add(TEXT("ps"), [this](TQueue<FString>& Tokens) -> bool
		{
			UE_LOG(LogTemp, Warning, TEXT("\"ps\" command"));

			return true;
		});
#pragma endregion // Commands
	}

	FVector2D FLogoVM::GetRotationVector() const
	{
		const double SinRotationVector = FMath::Sin(FMath::DegreesToRadians(Rotation));
		const double CosRotationVector = FMath::Cos(FMath::DegreesToRadians(Rotation));

		return FVector2D(CosRotationVector, SinRotationVector);
	}

	const TArray<FLinearColor>& FLogoVM::GetTilesColors() const
	{
		return TilesColors;
	}

	void FLogoVM::Move(const FIntPoint OldPosition, const FIntPoint Translation)
	{
		if (bIsPenUp)
		{
			return;
		}

		uint32 CurrentIndex = 0;
		FIntPoint Steps = { 0, 0 };

		do
		{
			CurrentIndex = (OldPosition.X + Steps.X) + ((OldPosition.Y + Steps.Y) * CanvasSize.X);
			TilesColors[CurrentIndex] = FLinearColor::Black;

			if (Steps.X != Translation.X)
			{
				Steps.X += FMath::Sign(Translation.X);
			}

			if (Steps.Y != Translation.Y)
			{
				Steps.Y += FMath::Sign(Translation.Y);
			}
		}
		while (Steps.X != Translation.X || Steps.Y != Translation.Y);
	}
#pragma endregion // FLogoVM
}
