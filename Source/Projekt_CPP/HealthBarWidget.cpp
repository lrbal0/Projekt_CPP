// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "HealthComponent.h"

void UHealthBarWidget::InitializeHealthWidget(UHealthComponent* HealthComp)
{
    if (!HealthComp || !HealthProgressBar) return;

    float HealthPercent = static_cast<float>(HealthComp->CurrentHealth) / static_cast<float>(HealthComp->MaxHealth);

    HealthComp->OnHealthChangedDelegate.AddDynamic(this, &UHealthBarWidget::UpdateHealthBar);
    UpdateHealthBar(HealthComp->CurrentHealth, HealthComp->MaxHealth, 0);
}

void UHealthBarWidget::UpdateHealthBar(int CurrentHealth, int MaxHealth, int ChangeAmount)
{
    if (HealthProgressBar && MaxHealth > 0)
    {
        float HealthPercent = static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);
        HealthProgressBar->SetPercent(HealthPercent);
    }
}