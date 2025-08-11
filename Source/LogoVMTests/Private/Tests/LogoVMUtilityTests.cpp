// @ Manuel Solano

#include "LogoVMUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMUtility_CanvasResample, "LogoVM.Utility.CanvasResample", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMUtility_CanvasResample::RunTest(const FString& Parameters)
{
	TArray<FColor> OutPixels;

	const int32 CanvasWidth = 3; 
	const int32 CanvasHeight = 3;
	
	const TArray<FLinearColor> CanvasTilesColors = 
	{
		// 0 --> White.
		// 1 --> Black.
		LogoVM::Utils::AvailableColors[0],
		LogoVM::Utils::AvailableColors[1],
		LogoVM::Utils::AvailableColors[0],
		LogoVM::Utils::AvailableColors[0],
		LogoVM::Utils::AvailableColors[1],
		LogoVM::Utils::AvailableColors[0],
		LogoVM::Utils::AvailableColors[0],
		LogoVM::Utils::AvailableColors[0],
		LogoVM::Utils::AvailableColors[0]
	};

	const int32 TextureHeight = 6; // Pixels.
	
	const double CanvasAspectRatio = static_cast<double>(CanvasWidth) / static_cast<double>(CanvasHeight);
	const int32 TextureWidth = FMath::RoundToInt(CanvasAspectRatio * TextureHeight);

	const bool bResult = LogoVM::Utils::TryResamplingCanvas(OutPixels, CanvasTilesColors, TextureWidth, TextureHeight, CanvasWidth, CanvasHeight);
	TestEqual(TEXT("The resampling operation shouldn't fail!"), bResult, true);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[0], CanvasTilesColors[0]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[1], CanvasTilesColors[0]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[2], CanvasTilesColors[1]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[3], CanvasTilesColors[1]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[4], CanvasTilesColors[2]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[5], CanvasTilesColors[2]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[6], CanvasTilesColors[0]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[7], CanvasTilesColors[0]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[8], CanvasTilesColors[1]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[9], CanvasTilesColors[1]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[10], CanvasTilesColors[2]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[11], CanvasTilesColors[2]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[12], CanvasTilesColors[3]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[13], CanvasTilesColors[3]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[14], CanvasTilesColors[4]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[15], CanvasTilesColors[4]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[16], CanvasTilesColors[5]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[17], CanvasTilesColors[5]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[18], CanvasTilesColors[3]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[19], CanvasTilesColors[3]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[20], CanvasTilesColors[4]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[21], CanvasTilesColors[4]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[22], CanvasTilesColors[5]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[23], CanvasTilesColors[5]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[24], CanvasTilesColors[6]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[25], CanvasTilesColors[6]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[26], CanvasTilesColors[7]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[27], CanvasTilesColors[7]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[28], CanvasTilesColors[8]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[29], CanvasTilesColors[8]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[30], CanvasTilesColors[6]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[31], CanvasTilesColors[6]);

	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[32], CanvasTilesColors[7]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[33], CanvasTilesColors[7]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[34], CanvasTilesColors[8]);
	TestEqual(TEXT("The current pixel color doesn't match with the sampled color!"), OutPixels[35], CanvasTilesColors[8]);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMUtility_DumpTokens, "LogoVM.Utility.DumpTokens", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMUtility_DumpTokens::RunTest(const FString& Parameters)
{
	TQueue<FString> OutDumpedTokens;

	TQueue<FString> TokensToDump;
	TokensToDump.Enqueue(TEXT("fd"));
	TokensToDump.Enqueue(TEXT("10"));
	TokensToDump.Enqueue(TEXT("rt"));
	TokensToDump.Enqueue(TEXT("90"));
	TokensToDump.Enqueue(TEXT("ct"));

	LogoVM::Utils::DumpTokens(OutDumpedTokens, TokensToDump);
	
	FString OutDumpedTokens_CurrentToken;
	FString TokensToDump_CurrentToken;
	
	OutDumpedTokens.Dequeue(OutDumpedTokens_CurrentToken);
	TokensToDump.Dequeue(TokensToDump_CurrentToken);
	TestEqual(TEXT("The dumped token doesn't match with the original token to dump!"), OutDumpedTokens_CurrentToken, TokensToDump_CurrentToken);

	OutDumpedTokens.Dequeue(OutDumpedTokens_CurrentToken);
	TokensToDump.Dequeue(TokensToDump_CurrentToken);
	TestEqual(TEXT("The dumped token doesn't match with the original token to dump!"), OutDumpedTokens_CurrentToken, TokensToDump_CurrentToken);

	OutDumpedTokens.Dequeue(OutDumpedTokens_CurrentToken);
	TokensToDump.Dequeue(TokensToDump_CurrentToken);
	TestEqual(TEXT("The dumped token doesn't match with the original token to dump!"), OutDumpedTokens_CurrentToken, TokensToDump_CurrentToken);

	OutDumpedTokens.Dequeue(OutDumpedTokens_CurrentToken);
	TokensToDump.Dequeue(TokensToDump_CurrentToken);
	TestEqual(TEXT("The dumped token doesn't match with the original token to dump!"), OutDumpedTokens_CurrentToken, TokensToDump_CurrentToken);

	OutDumpedTokens.Dequeue(OutDumpedTokens_CurrentToken);
	TokensToDump.Dequeue(TokensToDump_CurrentToken);
	TestEqual(TEXT("The dumped token doesn't match with the original token to dump!"), OutDumpedTokens_CurrentToken, TokensToDump_CurrentToken);

	TestEqual(TEXT("Both queues should are empty!"), OutDumpedTokens.IsEmpty(), TokensToDump.IsEmpty());
	
	return true;
}