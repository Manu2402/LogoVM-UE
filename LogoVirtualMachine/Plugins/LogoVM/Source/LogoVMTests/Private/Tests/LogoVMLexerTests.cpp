// @ Manuel Solano

#include "FLogoVM.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMLexerTest_Tokenize, "LogoVM.Lexer.Tokenize", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLogoVMLexerTest_Tokenize::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVM LogoVM;
	const FString LogoContent = TEXT("repeat 4 \n [ fd 100 rt 90 ] \n");
	
	LogoVM.Tokenize(LogoContent);

	FString CurrentToken;

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("repeat")), *CurrentToken, TEXT("repeat"));

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("4")), *CurrentToken, TEXT("4"));

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("[")), *CurrentToken, TEXT("["));

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("fd")), *CurrentToken, TEXT("fd"));

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("100")), *CurrentToken, TEXT("100"));

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("rt")), *CurrentToken, TEXT("rt"));

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("90")), *CurrentToken, TEXT("90"));

	LogoVM.TokensDequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s is not equal to: %s)"), *CurrentToken, TEXT("]")), *CurrentToken, TEXT("]"));
	
	return true;
}