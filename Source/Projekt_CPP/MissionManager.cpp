// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionManager.h"
#include "GameManager.h"
#include <SequenceGate.h>

AMissionManager::AMissionManager()
{

    PrimaryActorTick.bCanEverTick = false;

}

void AMissionManager::NotifyItemPickedUp(FName ItemID, int32 Amount)
{
    for (UMissionCommand* Mission : ActiveMissions)
    {
        if (UCollectItemMission* ItemMission = Cast<UCollectItemMission>(Mission))
        {
            ItemMission->OnItemPickedUp(ItemID, Amount, GetWorld());
        }
    }

}

void AMissionManager::NotifyButtonActivated(FString ButtonColor)
{
    for (UMissionCommand* Mission : ActiveMissions)
    {
        if (UButtonSequenceMission* SequenceMission = Cast<UButtonSequenceMission>(Mission))
        {
            SequenceMission->RecordButtonPress(ButtonColor);
        }
    }
}

void AMissionManager::NotifyEnemyKilled(FName EnemyID)
{
    for (UMissionCommand* Mission : ActiveMissions)
    {
        if (UWaveSurvivalMission* WaveMission = Cast<UWaveSurvivalMission>(Mission))
        {
            WaveMission->RegisterKill();
        }
    }
}

void AMissionManager::BeginPlay()
{
    Super::BeginPlay();

    // check level missions config
    for (const FMissionConfig& MissionConfig : LevelMissionsSetup)
    {
        if (!MissionConfig.MissionClass) continue;

        // 2. initialize specific mission class for each mission config
        UMissionCommand* NewMission = NewObject<UMissionCommand>(this, MissionConfig.MissionClass);
        if (NewMission)
        {
            NewMission->Initialize(MissionConfig.TargetID, MissionConfig.RequiredCount, MissionConfig.MissionName, GetWorld());
            NewMission->OnMissionComplete.AddUObject(this, &AMissionManager::OnMissionFinished);

            if (NewMission && NewMission->IsA<UButtonSequenceMission>())
            {
                // Find the sequence gate in the map
                if (AActor* GateActor = UGameplayStatics::GetActorOfClass(GetWorld(), ASequenceGate::StaticClass()))
                {
                    if (ASequenceGate* SequenceGate = Cast<ASequenceGate>(GateActor))
                    {
                        // Push the mission instance straight into the gate!
                        SequenceGate->InitializeGateBinding(NewMission);
                    }
                }
            }

            // 3. bind rewards for the mission
            for (const FRewardConfig& RewardConfig : MissionConfig.MissionRewards)
            {
                if (!RewardConfig.RewardClass) continue;

                UMissionReward* NewReward = NewObject<UMissionReward>(NewMission, RewardConfig.RewardClass);

                // 4. if the reward grants items, do special setup
                if (UGrantItemReward* ItemReward = Cast<UGrantItemReward>(NewReward))
                {
                    ItemReward->Setup(RewardConfig.RewardItemID, RewardConfig.RewardAmount, RewardConfig.RewardName);
                }

                // 5. setup the reward in the mission before adding
                NewMission->AddReward(NewReward);
            }

            // 6. add the initialized mission
            ActiveMissions.Add(NewMission);
        }
    }

}

void AMissionManager::OnMissionFinished(UMissionCommand* CompletedMission)
{
    if (CompletedMission)
    {
        
    }

}
