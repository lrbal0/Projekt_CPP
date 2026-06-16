// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

/**
 * 
 */
class FSubsystemCollectionBase;

UCLASS()
class PROJEKT_CPP_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    static UGameManager* GetInstance(const UObject* WorldContextObject);

    void HandleLevelCompleted();

private:
    void LoadLevelMap();

    UPROPERTY()
    FName TargetLevelName;
};
