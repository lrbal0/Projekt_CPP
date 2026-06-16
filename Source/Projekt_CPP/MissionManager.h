// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MissionCommand.h"
#include "MissionReward.h"
#include "MissionManager.generated.h"


USTRUCT(BlueprintType)
struct FRewardConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Reward")
    TSubclassOf<UMissionReward> RewardClass;

    UPROPERTY(EditAnywhere, Category = "Reward")
    FName RewardItemID;

    UPROPERTY(EditAnywhere, Category = "Reward")
    int32 RewardAmount = 1;

    UPROPERTY(EditAnywhere, Category = "Reward")
    FString RewardName;
};

USTRUCT(BlueprintType)
struct FMissionConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Mission Setup")
    FString MissionName;

    UPROPERTY(EditAnywhere, Category = "Mission Setup")
    TSubclassOf<UMissionCommand> MissionClass;

    UPROPERTY(EditAnywhere, Category = "Mission Setup")
    FName TargetID;

    UPROPERTY(EditAnywhere, Category = "Mission Setup")
    int32 RequiredCount = 1;

    UPROPERTY(EditAnywhere, Category = "Mission Setup")
    TArray<FRewardConfig> MissionRewards;
};

/**
 * 
 */
UCLASS()
class PROJEKT_CPP_API AMissionManager : public AInfo
{
	GENERATED_BODY()
	
public:
    AMissionManager();
    void NotifyItemPickedUp(FName ItemID, int32 Amount);
    void NotifyButtonActivated(FString ButtonColor);
    void NotifyEnemyKilled(FName EnemyID);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Missions Setup")
    TArray<FMissionConfig> LevelMissionsSetup;

public:
    const TArray<UMissionCommand*>& GetActiveMissions() const { return ActiveMissions; }

private:
    void OnMissionFinished(UMissionCommand* CompletedMission);

    UPROPERTY()
    TArray<UMissionCommand*> ActiveMissions;

};
