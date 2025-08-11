// @ Manuel Solano

#include "LogoVM/Public/LogoVMContext.h"
#include "LogoVM/Public/LogoVMUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_MissingCommand, "LogoVM.Executor.MissingCommand", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_MissingCommand::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 14), 90, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 270 /* UP */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90 /* DOWN */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 180 /* LEFT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 0 /* RIGHT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 225 /* UP-LEFT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 315 /* UP-RIGHT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 135 /* DOWN-LEFT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 45 /* DOWN-RIGHT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 14), 270, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 270 /* UP */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90 /* DOWN */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 180 /* LEFT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 0 /* RIGHT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 225 /* UP-LEFT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 315 /* UP-RIGHT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 135 /* DOWN-LEFT */, false, 1 };

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
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 45 /* DOWN-RIGHT */, false, 1 };

	const FString LogoContent = TEXT("bk 3");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 4);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 4);

	return true;
}

#pragma endregion // Backward

#pragma region RightTurn

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RightTurnStringArg, "LogoVM.Executor.RightTurn.StringArg", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RightTurnStringArg::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false, 1 };

	const FString LogoContent = TEXT("rt angle");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"right turn\" command should take just a numeric value as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RightTurn, "LogoVM.Executor.RightTurn", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RightTurn::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 270 /* UP */, false, 1 };

	const FString LogoContent = TEXT("rt 90");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's rotation is not what it should be!"), LogoVM.GetTurtleRotation(), 360);

	return true;
}

#pragma endregion // RightTurn

#pragma region LeftTurn

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_LeftTurnStringArg, "LogoVM.Executor.LeftTurn.StringArg", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_LeftTurnStringArg::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 90, false, 1 };

	const FString LogoContent = TEXT("lt angle");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"left turn\" command should take just a numeric value as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_LeftTurn, "LogoVM.Executor.LeftTurn", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_LeftTurn::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(15, 15), FIntPoint(7, 7), 270 /* UP */, false, 1 };

	const FString LogoContent = TEXT("lt 90");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's rotation is not what it should be!"), LogoVM.GetTurtleRotation(), 180);

	return true;
}

#pragma endregion // LeftTurn

#pragma region CenterTurtle

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_CenterTurtle, "LogoVM.Executor.CenterTurtle", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_CenterTurtle::RunTest(const FString& Parameters)
{
	const FIntPoint CanvasSize = { 15, 15 };
	
	LogoVM::FLogoVMContext LogoVM = { CanvasSize, FIntPoint(1, 1), 270 /* UP */, false, 1 };

	const FString LogoContent = TEXT("ct");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	const FIntPoint CanvasCenter = CanvasSize / 2;

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, CanvasCenter.X);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, CanvasCenter.Y);

	return true;
}

#pragma endregion // CenterTurtle

#pragma region ClearScreen

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_ClearScreen, "LogoVM.Executor.ClearScreen", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_ClearScreen::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(2, 2), FIntPoint::ZeroValue, 90, false, 6 };

	const FString LogoContent = TEXT("fd 1 \n cs");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	const FLinearColor DefaultAvailableColor = LogoVM.GetDefaultBackgroundColor();

	TestEqual(TEXT("In the canvas should be four colors!"), 4, LogoVM.GetCanvasTilesColors().Num());
	TestEqual(TEXT("The unique color in the canvas should be white!"), DefaultAvailableColor, LogoVM.GetCanvasTilesColors()[0]);
	TestEqual(TEXT("The unique color in the canvas should be white!"), DefaultAvailableColor, LogoVM.GetCanvasTilesColors()[1]);
	TestEqual(TEXT("The unique color in the canvas should be white!"), DefaultAvailableColor, LogoVM.GetCanvasTilesColors()[2]);
	TestEqual(TEXT("The unique color in the canvas should be white!"), DefaultAvailableColor, LogoVM.GetCanvasTilesColors()[3]);

	return true;
}

#pragma endregion // ClearScreen

#pragma region PenUp

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_PenUp, "LogoVM.Executor.PenUp", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_PenUp::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("pu");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"pen up\" command should had set \bIsTurtleUp\" to true!"), LogoVM.GetIsTurtleUp(), true);

	return true;
}
	
#pragma endregion // PenUp

#pragma region PenDown

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_PenDown, "LogoVM.Executor.PenDown", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_PenDown::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("pd");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"pen down\" command should had set \bIsTurtleUp\" to false!"), LogoVM.GetIsTurtleUp(), false);

	return true;
}
	
#pragma endregion // PenDown

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

#pragma region Repeat

// "repeat" (complete command)
// "repeat [ repeat [ ... ] ] (nested repeat)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RepeatStringArg, "LogoVM.Executor.Repeat.StringArg", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RepeatStringArg::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("repeat number [ fd 10 ]");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"repeat\" command should take just a numeric value as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RepeatValidArg, "LogoVM.Executor.Repeat.ValidArg", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RepeatValidArg::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("repeat 1 [ fd 10 ]");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"repeat\" command should take just a numeric value > 1 as an argument!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RepeatMissingBody, "LogoVM.Executor.Repeat.MissingBody", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RepeatMissingBody::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("repeat 5");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"repeat\" command should have a body!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RepeatVoidBody, "LogoVM.Executor.Repeat.VoidBody", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RepeatVoidBody::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("repeat 5 [ ]");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"repeat\" command can have a void body!"), bExecutionResult, true);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RepeatMissingOpenedSquareBracket, "LogoVM.Executor.Repeat.MissingOpenedSquareBracket", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RepeatMissingOpenedSquareBracket::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("repeat 5 fd 10 ]");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"repeat\" command should have next to the argument an opened square bracket!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RepeatMissingClosedSquareBracket, "LogoVM.Executor.Repeat.MissingClosedSquareBracket", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RepeatMissingClosedSquareBracket::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM;

	const FString LogoContent = TEXT("repeat 5 [ fd 10 ");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	const bool bExecutionResult = LogoVM.Execute(Tokens);

	TestEqual(TEXT("The \"repeat\" command should have a closed square bracket, in order to close the body!"), bExecutionResult, false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_Repeat, "LogoVM.Executor.Repeat", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_Repeat::RunTest(const FString& Parameters)
{
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(3), FIntPoint(0), 0, false, 0 };

	const FString LogoContent = TEXT("repeat 4 [ fd 2 rt 90 ]");
	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 0);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 0);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLogoVMExecutorTest_RepeatNested, "LogoVM.Executor.Repeat.Nested", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FLogoVMExecutorTest_RepeatNested::RunTest(const FString& Parameters)
{
	const int32 CanvasSize = 20;
	LogoVM::FLogoVMContext LogoVM = { FIntPoint(CanvasSize), FIntPoint(7), 270, false, 0 };

	const FString LogoContent = TEXT("repeat 4 [ repeat 4 [ fd 3 rt 90 ] rt 90 fd 3 ]");

	TQueue<FString> Tokens;

	LogoVM::Utils::Tokenize(Tokens, LogoContent);
	LogoVM.Execute(Tokens);

	TestEqual(TEXT("The turtle's position on X axis is not what it should be!"), LogoVM.GetTurtlePosition().X, 7);
	TestEqual(TEXT("The turtle's position on Y axis is not what it should be!"), LogoVM.GetTurtlePosition().Y, 7);
	
	return true;
}

#pragma endregion // Repeat