// Fill out your copyright notice in the Description page of Project Settings.


#include "LockedButton.h"
#include "MissionManager.h"
#include "Kismet/GameplayStatics.h"

ALockedButton::ALockedButton()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALockedButton::FireOnCompletion()
{
    UWorld* CurrentWorld = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
    if (CurrentWorld)
    {
        if (AActor* ManagerActor = UGameplayStatics::GetActorOfClass(CurrentWorld, AMissionManager::StaticClass()))
        {
            if (AMissionManager* MissionManager = Cast<AMissionManager>(ManagerActor))
            {
                if (ClickSound)
                {
                    UGameplayStatics::PlaySoundAtLocation(this, ClickSound, GetActorLocation());
                }

                if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Successfully notified MissionManager!"));
                MissionManager->NotifyButtonActivated(ButtonColorName);
            }
        }
        else
        {
            if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CRITICAL ERROR: MissionManager NOT found in level!"));
        }
    }
}

