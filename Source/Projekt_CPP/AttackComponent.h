// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJEKT_CPP_API UAttackComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAttackComponent();
    void Attack();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // the half-extents of the attack box (X=50 means total width is 100)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FVector BoxHalfExtents = FVector(100.0f, 50.0f, 50.0f);
    // MAKE SURE THE ATTACK DISTANCE IS EQUAL TO THE BOX EXTENTS "Z" SINCE A SMALL BOX WITH A LONG RANGE DOESNT HIT
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float AttackDistance = 200.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int DamageAmount = 20;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float AttackDelay = 0.2f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float TimeBetweenAttacks = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool bShowDebugBox = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    class USoundBase* AttackSound;

    UPROPERTY(BlueprintReadOnly)
    float AttackCooldownTimer;
    UPROPERTY(BlueprintReadOnly)
    bool bCanAttack;

private:
    void ExecuteAttackSweep();
    FTimerHandle AttackDelayTimerHandle;

};