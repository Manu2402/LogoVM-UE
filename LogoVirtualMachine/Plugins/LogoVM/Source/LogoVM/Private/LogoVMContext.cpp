// @ Manuel Solano

#include "LogoVMContext.h"
#include "LogoVMUtils.h"
#include "LogoVMBlueprintFunctionLibrary.h"
#include "LogoVM.h"

namespace LogoVM
{
	static constexpr int32 DefaultCanvasSize = 50; // (50x50).
	static constexpr int32 DefaultTurtlePosition = DefaultCanvasSize / 2; // Center of the canvas.
	static constexpr int32 DefaultTurtleRotation = 270; // UP (degrees).
	static constexpr bool bDefaultIsTurtleUp = false;
	
	FLogoVMContext::FLogoVMContext() : CanvasSize(FIntPoint(DefaultCanvasSize)),
		                               TurtlePosition(FIntPoint(DefaultTurtlePosition)),
		                               TurtleRotation(DefaultTurtleRotation),
	                                   bIsTurtleUp(bDefaultIsTurtleUp),
		                               DefaultBackgroundColor(Utils::AvailableColors[0])
	{
		InitLogoVM();
	}

	FLogoVMContext::FLogoVMContext(const FIntPoint InCanvasSize,
	                               const FIntPoint InTurtlePosition,
	                               const int32 InTurtleRotation,
	                               const bool bInIsTurtleUp,
	                               const int32 InDefaultBackgroundColor) :
	                               CanvasSize(InCanvasSize),
	                               TurtlePosition(InTurtlePosition),
								   // Recommended rotations (degrees): 0, 45, 90, 135, 180, 225, 270, 315, 360 
	                               TurtleRotation(InTurtleRotation),
								   bIsTurtleUp(bInIsTurtleUp),
	                               DefaultBackgroundColor(Utils::AvailableColors.IsValidIndex(InDefaultBackgroundColor) ? Utils::AvailableColors[InDefaultBackgroundColor]: Utils::AvailableColors[0])
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
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("EXECUTION FAILED: the command \"%s\" is not supported at the time!"), *CurrentToken);
				return false;
			}

			if (!Commands[CurrentToken](Tokens))
			{
				return false;
			}
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
		CanvasTilesColors.Init(DefaultBackgroundColor, CanvasResolution);
		ActiveColor = Utils::AvailableColors[1];

#pragma region Commands
		Commands.Add(TEXT("fd"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"forward\" command argument isn't a number!"));
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
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"forward\" command has finished with an out of bounds!"));
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
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"backward\" command argument isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);
			const FVector2D TurtleRotationVector = GetTurtleRotationVector();

			FIntPoint TurtleTraslation;
			TurtleTraslation.X = -(Arg * FMath::RoundToInt(TurtleRotationVector.X));
			TurtleTraslation.Y = -(Arg * FMath::RoundToInt(TurtleRotationVector.Y));

			const FIntPoint NewPosition = TurtlePosition + TurtleTraslation;

			if (Utils::IsOutOfBounds(NewPosition, CanvasSize))
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"backward\" command has finished with an out of bounds!"));
				return false;
			}

			Move(TurtlePosition, TurtleTraslation);
			TurtlePosition = NewPosition;

			return true;
		});
		Commands.Add(TEXT("rt"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"right turn\" command argument isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);
			TurtleRotation += Arg;
			
			return true;
		});
		Commands.Add(TEXT("lt"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"left turn\" command argument isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);
			TurtleRotation -= Arg;

			return true;
		});
		Commands.Add(TEXT("ct"), [this](TQueue<FString>& Tokens) -> bool
		{
			TurtlePosition = CanvasSize / 2;
			
			return true;
		});
		Commands.Add(TEXT("cs"), [this](TQueue<FString>& Tokens) -> bool
		{
			for (FLinearColor& TileColor : CanvasTilesColors)
			{
				TileColor = DefaultBackgroundColor;
			}

			return true;
		});
		Commands.Add(TEXT("pu"), [this](TQueue<FString>& Tokens) -> bool
		{
			bIsTurtleUp = true;

			return true;
		});
		Commands.Add(TEXT("pd"), [this](TQueue<FString>& Tokens) -> bool
		{
			bIsTurtleUp = false;

			return true;
		});
		Commands.Add(TEXT("pc"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"pen color\" command argument isn't a number!"));
				return false;
			}

			const int32 Arg = FCString::Atoi(*ArgToken);

			if (!Utils::AvailableColors.IsValidIndex(Arg))
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"pen color\" command argument isn't valid!"));
				return false;
			}

			ActiveColor = Utils::AvailableColors[Arg];
			
			return true;
		});
		Commands.Add(TEXT("repeat"), [this](TQueue<FString>& Tokens) -> bool
		{
			FString ArgToken;
			Tokens.Dequeue(ArgToken);

			if (!ArgToken.IsNumeric())
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"repeat\" command argument isn't a number!"));
				return false;
			}

			int32 Arg = FCString::Atoi(*ArgToken);

			if (Arg <= 1)
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"repeat\" command argument must be at least 2!"));
				return false;
			}

			TQueue<FString> InnerTokens;
			FString CurrentInnerToken;

			// First token check.
			if (!Tokens.Dequeue(CurrentInnerToken))
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"repeat\" command is failed to retreive it's body: tokens retreiving!"));
				return false;
			}

			if (!CurrentInnerToken.Equals(TEXT("[")))
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"repeat\" command is failed to retreive it's body: body isn't started with \"[\" token!"));
				return false;
			}

			int32 NestedBodies = 1;

			while (true)
			{
				if (!Tokens.Dequeue(CurrentInnerToken))
				{
					RUNTIME_LOG(LoggerLogoVM, Error, TEXT("The \"repeat\" command is failed to retreive it's body: tokens retreiving!"));
					return false;
				}

				if (CurrentInnerToken.Equals(TEXT("[")))
				{
					++NestedBodies;
				} 
				else if (CurrentInnerToken.Equals(TEXT("]")))
				{
					--NestedBodies;
					if (NestedBodies <= 0)
					{
						break;
					}
				}

				InnerTokens.Enqueue(CurrentInnerToken);
			}

			while (Arg-- > 0)
			{
				TQueue<FString> DumpInnerTokens;
				Utils::DumpTokens(DumpInnerTokens, InnerTokens);
				
				if (!Execute(DumpInnerTokens))
				{
					return false;
				}
			}

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

#if WITH_DEV_AUTOMATION_TESTS
	FIntPoint FLogoVMContext::GetTurtlePosition() const
	{
		return TurtlePosition;
	}

	int32 FLogoVMContext::GetTurtleRotation() const
	{
		return TurtleRotation;
	}

	bool FLogoVMContext::GetIsTurtleUp() const
	{
		return bIsTurtleUp;
	}

	FLinearColor FLogoVMContext::GetDefaultBackgroundColor() const
	{
		return DefaultBackgroundColor;
	}
#endif

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
		CanvasTilesColors[CurrentIndex] = ActiveColor;

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
			CanvasTilesColors[CurrentIndex] = ActiveColor;
		}
	}
}
