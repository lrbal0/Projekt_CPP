// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <HealthComponent.h>
#include <Components/ProgressBar.h>
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_CPP_API UHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void InitializeHealthWidget(UHealthComponent* HealthComponent);

protected:
    UFUNCTION()
    void UpdateHealthBar(int CurrentHealth, int MaxHealth, int ChangeAmount);

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;
};