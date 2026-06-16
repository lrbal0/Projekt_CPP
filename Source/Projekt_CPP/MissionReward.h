// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryComponent.h"
#include "MissionReward.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJEKT_CPP_API UMissionReward : public UObject
{
    GENERATED_BODY()

public:
    virtual void GrantReward(UWorld* World, AActor* PlayerActor) {}
    FString GetRewardName() const { return RewardName; }

protected:
    FString RewardName;
};

UCLASS()
class PROJEKT_CPP_API UGrantItemReward : public UMissionReward
{
    GENERATED_BODY()

public:
    void Setup(FName ItemID, int32 Amount, FString Name)
    {
        RewardItemID = ItemID;
        RewardAmount = Amount;
        RewardName = Name;
    }

    virtual void GrantReward(UWorld* World, AActor* PlayerActor) override
    {
        if (!PlayerActor) return;

        UInventoryComponent* Inventory = PlayerActor->FindComponentByClass<UInventoryComponent>();
        if (Inventory)
        {
            Inventory->AddItem(RewardItemID, RewardAmount);
        }
    }

private:
    FName RewardItemID;
    int32 RewardAmount = 0;
};
