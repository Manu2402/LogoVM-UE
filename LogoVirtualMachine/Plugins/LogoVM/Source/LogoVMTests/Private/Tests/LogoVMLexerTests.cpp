// @ Manuel Solano

#include "LogoVMUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMLexerTest_Tokenize, "LogoVM.Lexer.Tokenize", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMLexerTest_Tokenize::RunTest(const FString& Parameters)
{
	const FString LogoContent = TEXT("repeat 4 \n [ fd 100 rt 90 ] \n");

	TQueue<FString> Tokens;
	LogoVM::Utils::Tokenize(Tokens, LogoContent);

	FString CurrentToken;

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("repeat")), *CurrentToken, TEXT("repeat"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("4")), *CurrentToken, TEXT("4"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("[")), *CurrentToken, TEXT("["));

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("fd")), *CurrentToken, TEXT("fd"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("100")), *CurrentToken, TEXT("100"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("rt")), *CurrentToken, TEXT("rt"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("90")), *CurrentToken, TEXT("90"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(FString::Printf(TEXT("The current token: %s should be equal to: %s)"), *CurrentToken, TEXT("]")), *CurrentToken, TEXT("]"));
	
	return true;
}

// Add more tests (cover all commands).