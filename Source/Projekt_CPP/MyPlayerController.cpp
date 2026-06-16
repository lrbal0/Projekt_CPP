// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "PlayerCharacterLogic.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}

void AMyPlayerController::OnPossess(APawn* PossessedPawn)
{
    Super::OnPossess(PossessedPawn);

    // Bind Actions
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // Get Character Logic from Pawn
        APlayerCharacterLogic* PlayerCharacterLogic = Cast<APlayerCharacterLogic>(PossessedPawn);
        if (PlayerCharacterLogic)
        {
            if (MoveAction)
                EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, PlayerCharacterLogic, &APlayerCharacterLogic::HandleMoveInput);

            if (JumpAction)
                EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, PlayerCharacterLogic, &APlayerCharacterLogic::HandleJumpInput);
                EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, PlayerCharacterLogic, &APlayerCharacterLogic::HandleJumpInput);

            if (LookAction)
                EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, PlayerCharacterLogic, &APlayerCharacterLogic::HandleLookInput);

            if (InteractAction)
                EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, PlayerCharacterLogic, &APlayerCharacterLogic::FireInteract);

            if (AttackAction)
                EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, PlayerCharacterLogic, &APlayerCharacterLogic::FireAttack);
        }
    }
}
