// @ Manuel Solano

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "LogoVMFactory.generated.h"

UCLASS()
class LOGOVM_API ULogoVMFactory : public UFactory
{
	GENERATED_BODY()

public:
	ULogoVMFactory();

	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
	
};
