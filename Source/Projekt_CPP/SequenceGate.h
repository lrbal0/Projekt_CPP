// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SequenceGate.generated.h"

class UMissionCommand;

UCLASS()
class PROJEKT_CPP_API ASequenceGate : public AActor
{
    GENERATED_BODY()

public:
    ASequenceGate();
    void InitializeGateBinding(UMissionCommand* SequenceMission);

protected:
    virtual void BeginPlay() override;

    // Direct C++ listener for the manager
    void HandleSequenceMissionFinished(UMissionCommand* CompletedMission);

};
