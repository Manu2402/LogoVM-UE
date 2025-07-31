// @ Manuel Solano

#include "LogoVMUtils.h"
#include "LogoVM.h"

namespace LogoVM
{
	namespace Utils
	{
		bool FilePathIsValid(const FString& InFilePath)
		{
			if (InFilePath.IsEmpty())
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("A Logo command with empty file path is invalid!"));
				return false;
			}
	
			TArray<FString> FilePathTokens;
			InFilePath.ParseIntoArray(FilePathTokens, TEXT("."));

			if (FilePathTokens.Num() <= 1)
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("A Logo command with missing base or with missing extension is invalid!"));
				return false;
			}
	
			if (!FilePathTokens.Last().Equals(TEXT("logo")))
			{
				RUNTIME_LOG(LoggerLogoVM, Warning, TEXT("A Logo command with a wrong extension as a file path's suffix is invalid!"));
				return false;
			}

			return true;
		}

		void Tokenize(TQueue<FString>& OutTokens, const FString& FileContent)
		{
			TArray<FString> Tokens;
			const TCHAR* Delimiters[] = { TEXT(" "), TEXT("\n"), TEXT("\r") };
			FileContent.ParseIntoArray(Tokens, Delimiters, UE_ARRAY_COUNT(Delimiters));

			// Load tokens into a queue.
			for (const FString& Token : Tokens)
			{
				OutTokens.Enqueue(Token);
			}
		}

		bool IsOutOfBounds(const FIntPoint Position, const FIntPoint CanvasSize)
		{
			return Position.X < 0 || Position.X >= CanvasSize.X || Position.Y < 0 || Position.Y >= CanvasSize.Y;
		}

		bool TrySpawnCanvas(TArray<AActor*>& OutCanvasTiles, UWorld* InWorld, const FIntPoint CanvasSize)
		{
			const uint32 CanvasResolution = CanvasSize.X * CanvasSize.Y;
			OutCanvasTiles.Empty(CanvasResolution);
		
			// Spawn canvas, composed by simple cubes as tiles.
			UClass* CubeClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/LogoVM/Blueprints/BP_Cube.BP_Cube_C"));

			if (!CubeClass)
			{
				RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to create the canvas: error when loading tile's body!"));
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

			for (int32 HeightIndex = 0; HeightIndex < CanvasSize.Y; HeightIndex++)
			{
				for (int32 WidthIndex = 0; WidthIndex < CanvasSize.X; WidthIndex++)
				{
					AActor* CanvasTile = InWorld->SpawnActor<AActor>(CubeClass, FVector::ZeroVector, Rotation, SpawnParameters);
					if (!CanvasTile)
					{
						RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to create the canvas: error when spawning a tile!"));
						return false;
					}

					if (bFirstCube)
					{
						UStaticMeshComponent* StaticMeshComponent = CanvasTile->FindComponentByClass<UStaticMeshComponent>();
						if (!StaticMeshComponent)
						{
							RUNTIME_LOG(LoggerLogoVM, Error, TEXT("Unable to create the canvas: error when spawning a tile's body!"));
							return false;
						}

						CubeScale = StaticMeshComponent->GetRelativeScale3D();
						CubeSize = { CubeDefaultSize.X * CubeScale.X, CubeDefaultSize.Y * CubeScale.Y, CubeDefaultSize.Z * CubeScale.Z };

						bFirstCube = false;
					}
			
					const FVector CurrentLocation = { CubeSize.X * WidthIndex, CubeSize.Y * HeightIndex, CubeDefaultSize.Z * CubeScale.Z * 0.5f };
					CanvasTile->SetActorLocation(CurrentLocation);

					// Loading all the tiles.
					OutCanvasTiles.Add(CanvasTile);
				}
			}

			// FEATURE: Find a way to merge in one static mesh all the cubes.

			return true;
		}
	}
}
