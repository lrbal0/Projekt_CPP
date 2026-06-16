// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "EnemyCharacterLogic.h"

AMyAIController::AMyAIController()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemyCharacterLogic* Enemy = Cast<AEnemyCharacterLogic>(InPawn);
}
