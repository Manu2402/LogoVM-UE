// @ Manuel Solano

#include "LogoVM/Public/LogoVMContext.h"
#include "LogoVM/Public/LogoVMUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_MissingCommand, "LogoVM.Executor.MissingCommand", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_MissingCommand::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false };

	const FString LogoContent = TEXT("dummy_command");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The current command shouldn't supported at the time!"), bExecutionResult, false);

	return true;
}

#pragma region Forward

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardStringArg, "LogoVM.Executor.Forward.StringArg", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardStringArg::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false };

	const FString LogoContent = TEXT("fd number");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"forward\" command should take just a numeric value as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardOutOfBounds, "LogoVM.Executor.Forward.OutOfBounds", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardOutOfBounds::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 14), 90, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"forward\" command should finish with an out of bounds!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardUp, "LogoVM.Executor.Forward.Up", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardUp::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 270 /* UP */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 7);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 4);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardDown, "LogoVM.Executor.Forward.Down", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardDown::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90 /* DOWN */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 7);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 10);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardLeft, "LogoVM.Executor.Forward.Left", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardLeft::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 180 /* LEFT */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 4);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 7);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardRight, "LogoVM.Executor.Forward.Right", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardRight::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 0 /* RIGHT */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 10);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 7);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardUpLeft, "LogoVM.Executor.Forward.UpLeft", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardUpLeft::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 225 /* UP-LEFT */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 4);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 4);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardUpRight, "LogoVM.Executor.Forward.UpRight", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardUpRight::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 315 /* UP-RIGHT */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 10);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 4);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardDownLeft, "LogoVM.Executor.Forward.DownLeft", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardDownLeft::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 135 /* DOWN-LEFT */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 4);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 10);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ForwardDownRight, "LogoVM.Executor.Forward.DownRight", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ForwardDownRight::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 45 /* DOWN-RIGHT */, false };

	const FString LogoContent = TEXT("fd 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 10);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 10);

	return true;
}

#pragma endregion // Forward

#pragma region Backward

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardStringArg, "LogoVM.Executor.Backward.StringArg", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardStringArg::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false };

	const FString LogoContent = TEXT("bk number");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"backward\" command should take just a numeric value as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardOutOfBounds, "LogoVM.Executor.Backward.OutOfBounds", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardOutOfBounds::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 14), 270, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"backward\" command should finish with an out of bounds!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardUp, "LogoVM.Executor.Backward.Up", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardUp::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 270 /* UP */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 7);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 10);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardDown, "LogoVM.Executor.Backward.Down", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardDown::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90 /* DOWN */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 7);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 4);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardLeft, "LogoVM.Executor.Backward.Left", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardLeft::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 180 /* LEFT */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 10);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 7);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardRight, "LogoVM.Executor.Backward.Right", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardRight::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 0 /* RIGHT */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 4);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 7);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardUpLeft, "LogoVM.Executor.Backward.UpLeft", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardUpLeft::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 225 /* UP-LEFT */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 10);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 10);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardUpRight, "LogoVM.Executor.Backward.UpRight", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardUpRight::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 315 /* UP-RIGHT */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 4);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 10);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardDownLeft, "LogoVM.Executor.Backward.DownLeft", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardDownLeft::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 135 /* DOWN-LEFT */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 10);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 4);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_BackwardDownRight, "LogoVM.Executor.Backward.DownRight", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_BackwardDownRight::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 45 /* DOWN-RIGHT */, false };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 4);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 4);

	return true;
}

#pragma endregion // Backward

#pragma region PenColor

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_PenColorStringArg, "LogoVM.Executor.PenColor.StringArg", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_PenColorStringArg::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("pc number");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"pen color\" command should take just a numeric value as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_PenColorOutOfBoundsWithNegativeValue, "LogoVM.Executor.PenColor.OutOfBounds.NegativeValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_PenColorOutOfBoundsWithNegativeValue::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("pc -1");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"pen color\" command should take only a positive numeric value as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_PenColorOutOfBoundsWithPositiveValue, "LogoVM.Executor.PenColor.OutOfBounds.PositiveValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_PenColorOutOfBoundsWithPositiveValue::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("pc 42");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"pen color\" command shouldn't take a too much bigger argument value!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_PenColor, "LogoVM.Executor.PenColor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_PenColor::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("pc 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"pen color\" command shouldn't fail!"), bExecutionResult, true);

	return true;
}

#pragma endregion // PenColor