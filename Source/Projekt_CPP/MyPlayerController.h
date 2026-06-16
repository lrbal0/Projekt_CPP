// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJEKT_CPP_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Input Actions")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Input Actions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Input Actions")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Input Actions")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input|Input Actions")
	UInputAction* AttackAction;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* PossessedPawn) override;
};
