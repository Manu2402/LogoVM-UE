// @ Manuel Solano

#include "FLogoVM.h"

namespace LogoVM
{
#pragma region FLogoVM
	FLogoVM::FLogoVM()
	{
		
	}

	FLogoVM::~FLogoVM()
	{
		
	}

	void FLogoVM::Tokenize(const FString& FileContent)
	{
		TArray<FString> TokensArray;
		const TCHAR* Delimiters[] = { TEXT(" "), TEXT("\n") };
		FileContent.ParseIntoArray(TokensArray, Delimiters, UE_ARRAY_COUNT(Delimiters));

		// Load tokens into a queue.
		for (const FString& Token : TokensArray)
		{
			TokensEnqueue(Token);
		}
	}

	bool FLogoVM::TokensEnqueue(const FString& Token)
	{
		return Tokens.Enqueue(Token);
	}

	bool FLogoVM::TokensDequeue(FString& Token)
	{
		return Tokens.Dequeue(Token);
	}
#pragma endregion // FLogoVM
}
