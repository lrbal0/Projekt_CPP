// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "HealthComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    AttackCooldownTimer = 0.0f;
    bCanAttack = true;

    // ...

}

// Called when the game starts
void UAttackComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bCanAttack)
    {
        AttackCooldownTimer += DeltaTime;

        // attacking activated when timer = timebetweenattacks
        if (AttackCooldownTimer >= TimeBetweenAttacks)
        {
            bCanAttack = true;
            AttackCooldownTimer = 0.f;
        }
    }
}

void UAttackComponent::Attack()
{
    if (!bCanAttack) return;

    AActor* Owner = GetOwner();
    if (!Owner) return;

    UWorld* World = GetWorld();
    if (!World) return;


    World->GetTimerManager().SetTimer(
        AttackDelayTimerHandle,
        this,
        &UAttackComponent::ExecuteAttackSweep,
        AttackDelay,
        false
    );

}

void UAttackComponent::ExecuteAttackSweep()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    UWorld* World = GetWorld();
    if (!World) return;

    bCanAttack = false;

    UGameplayStatics::PlaySoundAtLocation(this, AttackSound, Owner->GetActorLocation());

    // 1. calculate the center position of the attack box relative to owner orientation
    FVector OwnerLocation = Owner->GetActorLocation();
    FVector OwnerForward = Owner->GetActorForwardVector();
    FVector BoxCenter = OwnerLocation + (OwnerForward * AttackDistance);
    FQuat BoxRotation = Owner->GetActorQuat();

    // 2. setup collision query parameters and perform box overlap
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Owner);

    TArray<FOverlapResult> OverlapResults;
    ECollisionChannel CollisionChannel = ECC_Pawn;

    FCollisionShape CollisionShape = FCollisionShape::MakeBox(BoxHalfExtents);
    bool bHasOverlap = World->OverlapMultiByChannel(
        OverlapResults,
        BoxCenter,
        BoxRotation,
        CollisionChannel,
        CollisionShape,
        QueryParams
    );

    if (bShowDebugBox)
    {
        FColor DebugColor = bHasOverlap ? FColor::Red : FColor::Green;
        DrawDebugBox(World, BoxCenter, BoxHalfExtents, BoxRotation, DebugColor, false, 1.5f, 0, 2.0f);
    }

    // 3. check overlap for healthcomponent, if found modify health
    if (bHasOverlap)
    {
        for (const FOverlapResult& Result : OverlapResults)
        {
            AActor* HitActor = Result.GetActor();
            if (HitActor)
            {
                UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>();
                if (HealthComp)
                {
                    HealthComp->HandleModifyHealth(-DamageAmount);
                }
            }
        }
    }

}