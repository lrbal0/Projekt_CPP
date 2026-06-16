// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceGate.h"
#include "Kismet/GameplayStatics.h"
#include "MissionManager.h"
#include <GameManager.h>

// Sets default values
ASequenceGate::ASequenceGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// ovo nece radit ako je u beginplay
void ASequenceGate::InitializeGateBinding(UMissionCommand* SequenceMission)
{
    if (SequenceMission)
    {
        SequenceMission->OnMissionComplete.AddUObject(this, &ASequenceGate::HandleSequenceMissionFinished);
    }
}

// Called when the game starts or when spawned
void ASequenceGate::BeginPlay()
{
	Super::BeginPlay();
    
}

void ASequenceGate::HandleSequenceMissionFinished(UMissionCommand* CompletedMission)
{
    if (GEngine)
    {
        FString InteractedMessage = FString::Printf(TEXT("Correct Sequence!"));
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, InteractedMessage);
    }

    if (UGameManager* GameManager = UGameManager::GetInstance(this))
    {
        GameManager->HandleLevelCompleted();
    }
}


