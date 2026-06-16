// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	CurrentHealth = MaxHealth;
	bIsDead = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// take damage and heal function
void UHealthComponent::HandleModifyHealth(int Amount)
{
	if (bIsDead) return;	

	int oldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0, MaxHealth);
	
	if (CurrentHealth == oldHealth) return;

	OnHealthChangedDelegate.Broadcast(CurrentHealth, MaxHealth, Amount);

	if (CurrentHealth == 0)
	{
		OnDeathDeletage.Broadcast();
		bIsDead = true;

		UE_LOG(LogTemp, Warning, TEXT("ded"), *GetName());
	}

}

