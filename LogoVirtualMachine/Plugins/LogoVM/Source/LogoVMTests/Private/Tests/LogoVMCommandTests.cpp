// @ Manuel Solano

#include "LogoVM/Public/LogoVMUtility.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMCommandTest_EmptyPath, "LogoVM.Command.EmptyPath", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLogoVMCommandTest_EmptyPath::RunTest(const FString& Parameters)
{
	const FString FilePath = TEXT("");
	
	TestFalse(TEXT("Logo command with empty file path should be invalid!"), LogoVM::Utility::FilePathIsValid(FilePath));
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMCommandTest_MissingBaseName, "LogoVM.Command.MissingBaseName", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLogoVMCommandTest_MissingBaseName::RunTest(const FString& Parameters)
{
	const FString FilePath = TEXT(".logo");

	TestFalse(TEXT("Logo command with missing base name should be invalid!"), LogoVM::Utility::FilePathIsValid(FilePath));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMCommandTest_MissingExtension, "LogoVM.Command.MissingExtension", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLogoVMCommandTest_MissingExtension::RunTest(const FString& Parameters)
{
	const FString FilePath = TEXT("path/to/file");

	TestFalse(TEXT("Logo command without extension as a file path's suffix should be invalid!"), LogoVM::Utility::FilePathIsValid(FilePath));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMCommandTest_WrongExtension, "LogoVM.Command.WrongExtension", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLogoVMCommandTest_WrongExtension::RunTest(const FString& Parameters)
{
	const FString FilePath = TEXT("path/to/file.png");

	TestFalse(TEXT("Logo command with a wrong extension as a file path's suffix should be invalid!"), LogoVM::Utility::FilePathIsValid(FilePath));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMCommandTest_CorrectCommand, "LogoVM.Command.CorrectCommand", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FLogoVMCommandTest_CorrectCommand::RunTest(const FString& Parameters)
{
	const FString FilePath = TEXT("path/to/file.logo");

	TestTrue(TEXT("The correct Logo command should be valid!"), LogoVM::Utility::FilePathIsValid(FilePath));

	return true;
}