// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MissionReward.h"
#include "EnemyCharacterLogic.h"
#include "Kismet/GameplayStatics.h"
#include "MissionCommand.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMissionComplete, UMissionCommand*);
/**
 * 
 */
UCLASS()
class PROJEKT_CPP_API UMissionCommand : public UObject
{
	GENERATED_BODY()

public:
    virtual void Initialize(FName TargetID, int32 RequiredCount, const FString& Name, UWorld* World) {}
    virtual void AddReward(UMissionReward* NewReward) { if (NewReward) Rewards.Add(NewReward); }

    bool IsCompleted() const { return bIsCompleted; }
    FString GetMissionName() const { return MissionName; }

    FOnMissionComplete OnMissionComplete;

protected:
    void CompleteObjective(UWorld* World)
    {
        if (bIsCompleted) return;
        bIsCompleted = true;

        AActor* PlayerCharacter = nullptr;
        if (World && World->GetFirstPlayerController())
        {
            PlayerCharacter = World->GetFirstPlayerController()->GetPawn();
        }

        for (UMissionReward* Reward : Rewards)
        {
            if (Reward) Reward->GrantReward(World, PlayerCharacter);
        }

        OnMissionComplete.Broadcast(this);
    }

    FString MissionName;

    UPROPERTY()
    TArray<UMissionReward*> Rewards;

private:
    bool bIsCompleted = false;

};

// button combination mission
UCLASS()
class PROJEKT_CPP_API UButtonSequenceMission : public UMissionCommand
{
    GENERATED_BODY()

public:
    virtual void Initialize(FName TargetID, int32 RequiredCount, const FString& Name, UWorld* World) override
    {
        RequiredSequence = TargetID.ToString(); // primjer: "RedBlueGreen"
        MissionName = Name;
        StoredWorld = World;
    }

    void RecordButtonPress(FString ButtonColor)
    {
        CurrentSequence += ButtonColor;

        // if sequence breaks midway, reset progress
        if (!RequiredSequence.StartsWith(CurrentSequence))
        {
            CurrentSequence.Empty();
            return;
        }

        // check if the puzzle is fully solved
        if (CurrentSequence == RequiredSequence)
        {
            CompleteObjective(StoredWorld);
        }
    }

private:
    FString RequiredSequence;
    FString CurrentSequence;

    UPROPERTY()
    UWorld* StoredWorld = nullptr;
};

// item collect mission
UCLASS()
class PROJEKT_CPP_API UCollectItemMission : public UMissionCommand
{
    GENERATED_BODY()

public:
    virtual void Initialize(FName TargetID, int32 RequiredCount, const FString& Name, UWorld* World) override
    {
        RequiredItemID = TargetID;
        GoalAmount = RequiredCount;
        MissionName = Name;
    }

    void OnItemPickedUp(FName ItemID, int32 Amount, UWorld* World)
    {
        if (ItemID == RequiredItemID)
        {
            CurrentAmount += Amount;
            if (CurrentAmount >= GoalAmount) CompleteObjective(World);
        }
    }

private:
    FName RequiredItemID;
    int32 GoalAmount = 0;
    int32 CurrentAmount = 0;
};

// kill enemies mission
UCLASS()
class PROJEKT_CPP_API UWaveSurvivalMission : public UMissionCommand
{
    GENERATED_BODY()

public:
    virtual void Initialize(FName TargetID, int32 RequiredCount, const FString& Name, UWorld* World) override
    {
        TotalRequiredKills = RequiredCount;
        MissionName = Name;
        StoredWorld = World;
    }

    void RegisterKill()
    {
        CurrentKills++;

        if (CurrentKills >= TotalRequiredKills)
        {
            CompleteObjective(StoredWorld);
        }
    }

private:
    int32 TotalRequiredKills = 0;
    int32 CurrentKills = 0;

    UPROPERTY()
    UWorld* StoredWorld = nullptr;
};
