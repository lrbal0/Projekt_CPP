// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void UGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    TargetLevelName = TEXT("Level2");
}

void UGameManager::Deinitialize()
{
    Super::Deinitialize();
}

UGameManager* UGameManager::GetInstance(const UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return nullptr;

    if (UGameInstance* GI = World->GetGameInstance())
    {
        return GI->GetSubsystem<UGameManager>();
    }
    return nullptr;
}

void UGameManager::HandleLevelCompleted()
{
    LoadLevelMap();
}

void UGameManager::LoadLevelMap()
{
    if (!TargetLevelName.IsNone() && GetWorld())
    {
        UGameplayStatics::OpenLevel(GetWorld(), TargetLevelName);
    }
}

