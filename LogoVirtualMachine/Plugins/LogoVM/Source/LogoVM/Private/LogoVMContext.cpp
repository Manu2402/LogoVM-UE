// @ Manuel Solano

#include "LogoVMContext.h"
#include "LogoVMUtils.h"
#include "LogoVM.h"

namespace LogoVM
{
#pragma region FLogoVMContext
	static constexpr int32 DefaultCanvasSize = 15; // 15x15 tiles.
	static constexpr int32 DefaultTurtlePosition = static_cast<int32>(DefaultCanvasSize * 0.5f); // Center of the canvas.
	static constexpr int32 DefaultTurtleRotation = 270; // UP (degrees).
	static constexpr bool bDefaultIsTurtleUp = false;

	static const FLinearColor DefaultTileColor = FLinearColor::White;
	
	// Odd resolutions on canvas in order to have a perfect center (not required).
	FLogoVMContext::FLogoVMContext() : CanvasSize(FIntPoint(DefaultCanvasSize)), TurtlePosition(FIntPoint(DefaultTurtlePosition)), TurtleRotation(DefaultTurtleRotation), bIsTurtleUp(bDefaultIsTurtleUp)
	{
		InitLogoVM();
	}

	FLogoVMContext::FLogoVMContext(const FIntPoint InCanvasSize, const FIntPoint InTurtlePosition, const int32 InTurtleRotation, const bool bInIsTurtleUp) : CanvasSize(InCanvasSize), TurtlePosition(InTurtlePosition), TurtleRotation(InTurtleRotation), bIsTurtleUp(bInIsTurtleUp)
	{
		InitLogoVM();
	}

	bool FLogoVMContext::Execute(TQueue<FString>& Tokens)
	{
		FString CurrentToken;
		while (Tokens.Dequeue(CurrentToken))
		{
			if (!Commands.Contains(CurrentToken))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("EXECUTION FAILED: the command \"%s\" is not supported at the time!"), *CurrentToken);
				return false;
			}

			Commands[CurrentToken](Tokens);
		}

		return true;
	}

	FIntPoint FLogoVMContext::GetCanvasSize() const
	{
		return CanvasSize;
	}
	
	void FLogoVMContext::InitLogoVM()
	{
		const uint32 CanvasResolution = CanvasSize.X * CanvasSize.Y;
		CanvasTilesColors.Init(DefaultTileColor, CanvasResolution);

#pragma region Commands
		Commands.Add(TEXT("fd"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The forward command argument isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);
			const FVector2D TurtleRotationVector = GetTurtleRotationVector();

			FIntPoint TurtleTraslation;
			TurtleTraslation.X = Arg * FMath::RoundToInt(TurtleRotationVector.X);
			TurtleTraslation.Y = Arg * FMath::RoundToInt(TurtleRotationVector.Y);

			const FIntPoint NewPosition = TurtlePosition + TurtleTraslation;

			if (Utils::IsOutOfBounds(NewPosition, CanvasSize))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The forward command has finished with an out of bounds!"));
				return false;
			}

			Move(TurtlePosition, TurtleTraslation);
			TurtlePosition = NewPosition;

			return true;
		});
		Commands.Add(TEXT("bk"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The backward command argument isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);
			const FVector2D TurtleRotationVector = GetTurtleRotationVector();

			FIntPoint TurtleTraslation;
			TurtleTraslation.X = -(Arg * TurtleRotationVector.X);
			TurtleTraslation.Y = -(Arg * TurtleRotationVector.Y);

			const FIntPoint NewPosition = TurtlePosition + TurtleTraslation;

			if (Utils::IsOutOfBounds(NewPosition, CanvasSize))
			{
				UE_LOG(LoggerLogoVM, Error, TEXT("The backward command has finished with an out of bounds!"));
				return false;
			}

			Move(TurtlePosition, TurtleTraslation);
			TurtlePosition = NewPosition;

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

	FVector2D FLogoVMContext::GetTurtleRotationVector() const
	{
		const double SinRotationVector = FMath::Sin(FMath::DegreesToRadians(TurtleRotation));
		const double CosRotationVector = FMath::Cos(FMath::DegreesToRadians(TurtleRotation));

		return FVector2D(CosRotationVector, SinRotationVector);
	}

	const TArray<FLinearColor>& FLogoVMContext::GetCanvasTilesColors() const
	{
		return CanvasTilesColors;
	}

	void FLogoVMContext::Move(const FIntPoint OldTurtlePosition, const FIntPoint TurtleTraslation)
	{
		if (bIsTurtleUp)
		{
			return;
		}

		uint32 CurrentIndex = 0;
		FIntPoint Steps = FIntPoint::ZeroValue;

		// Coloring on the pre-movement position.
		CurrentIndex = (OldTurtlePosition.X + Steps.X) + ((OldTurtlePosition.Y + Steps.Y) * CanvasSize.X);
		CanvasTilesColors[CurrentIndex] = FLinearColor::Black;

		while (Steps.X != TurtleTraslation.X || Steps.Y != TurtleTraslation.Y)
		{
			if (Steps.X != TurtleTraslation.X)
			{
				Steps.X += FMath::Sign(TurtleTraslation.X);
			}

			if (Steps.Y != TurtleTraslation.Y)
			{
				Steps.Y += FMath::Sign(TurtleTraslation.Y);
			}
			
			// Coloring.
			CurrentIndex = (OldTurtlePosition.X + Steps.X) + ((OldTurtlePosition.Y + Steps.Y) * CanvasSize.X);
			CanvasTilesColors[CurrentIndex] = FLinearColor::Black;
		}
	}
#pragma endregion // FLogoVMContext
}
