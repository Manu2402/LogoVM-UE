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
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("repeat"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("4"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("["));

	Tokens.Dequeue(CurrentToken);
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("fd"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("100"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("rt"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("90"));

	Tokens.Dequeue(CurrentToken);
	TestEqual(TEXT("The current token doesn't match with the expected token!"), *CurrentToken, TEXT("]"));
	
	return true;
}