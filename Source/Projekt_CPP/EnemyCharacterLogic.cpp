// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterLogic.h"
#include "AttackComponent.h"
#include "HealthComponent.h"
#include "PlayerCharacterLogic.h"
#include "MyAIController.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include <MissionManager.h>

// Sets default values
AEnemyCharacterLogic::AEnemyCharacterLogic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = AMyAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bOrientRotationToMovement = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
    }
}

// enemy builder function
void AEnemyCharacterLogic::ConfigureFromData(FName _enemyID, const FEnemyData& Data)
{
    EnemyID = _enemyID;
    BaseSpeed = Data.BaseSpeed;

    if (AttackComponent)
    {
        AttackComponent->DamageAmount = Data.BaseDamage;
        AttackComponent->AttackDistance = Data.AttackRange;
        AttackComponent->AttackDelay = Data.AttackDelay;
        AttackComponent->TimeBetweenAttacks = Data.PostAttackDelay;
        AttackComponent->BoxHalfExtents = Data.BoxHalfExtents;
    }

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
    }

}

void AEnemyCharacterLogic::AttackPlayer()
{
    if (AttackComponent && AttackComponent->bCanAttack)
    {
        AttackComponent->Attack();
        CooldownTimer = 0.0f;
        CurrentState = EEnemyState::AttackCooldown;
    }

}

void AEnemyCharacterLogic::SetTargetPlayer(APlayerCharacterLogic* _player)
{
    TargetPlayer = _player;

}

// Called when the game starts or when spawned
void AEnemyCharacterLogic::BeginPlay()
{
	Super::BeginPlay();
	
    if (HealthComponent)
    {
        HealthComponent->OnDeathDeletage.AddDynamic(this, &AEnemyCharacterLogic::HandleDeath);
    }

    if (!TargetPlayer)
    {
        APlayerCharacterLogic* FoundPlayer = Cast<APlayerCharacterLogic>(GetWorld()->GetFirstPlayerController()->GetPawn());
        SetTargetPlayer(FoundPlayer);
    }

}

void AEnemyCharacterLogic::HandleDeath()
{
    OnEnemyDeath.Broadcast(EnemyID);

    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        AIController->StopMovement();
        AIController->UnPossess();
    }

    if (UWorld* World = GetWorld())
    {
        if (AActor* ManagerActor = UGameplayStatics::GetActorOfClass(World, AMissionManager::StaticClass()))
        {
            if (AMissionManager* MissionManager = Cast<AMissionManager>(ManagerActor))
            {
                MissionManager->NotifyEnemyKilled(EnemyID);
            }
        }
    }

    Destroy();

}

// tick handles the state machine with strategies and the attack cooldown
void AEnemyCharacterLogic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AAIController* AIController = Cast<AAIController>(GetController());

    if (!TargetPlayer || !AIController)
    {
        if (AIController) AIController->StopMovement();
        return;
    }

    switch (CurrentState)
    {
    case EEnemyState::WalkTowardsPlayer:
        UpdateWalkTowardsPlayer();
        break;

    case EEnemyState::ChaseAndAttack:
        UpdateChaseAndAttack();
        break;

    case EEnemyState::AttackCooldown:
        UpdateAttackCooldown(DeltaTime);
        break;
    }

}

void AEnemyCharacterLogic::UpdateWalkTowardsPlayer()
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (!AIController) return;

    // use normal walking speed
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
    }

    // rotate to player
    if (TargetPlayer)
    {
        FRotator LookAtRotation = FRotationMatrix::MakeFromX(TargetPlayer->GetActorLocation() - GetActorLocation()).Rotator();
        LookAtRotation.Pitch = 0.0f;
        LookAtRotation.Roll = 0.0f;
        SetActorRotation(LookAtRotation);
    }

    AIController->MoveToActor(TargetPlayer, 0.0f);

    // if player is close enough for attacking, transition into chasing
    float Distance = FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation());
    if (Distance <= AttackComponent->AttackDistance * 1.5f)
    {
        CurrentState = EEnemyState::ChaseAndAttack;
    }

}

void AEnemyCharacterLogic::UpdateChaseAndAttack()
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (!AIController) return;

    // use faster sprinting speed
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * 1.5f;
    }

    // rotate to player
    if (TargetPlayer)
    {
        FRotator LookAtRotation = FRotationMatrix::MakeFromX(TargetPlayer->GetActorLocation() - GetActorLocation()).Rotator();
        LookAtRotation.Pitch = 0.0f;
        LookAtRotation.Roll = 0.0f;
        SetActorRotation(LookAtRotation);
    }

    float Distance = FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation());

    // if in attack range
    if (Distance <= AttackComponent->AttackDistance)
    {
        // stop moving to attack
        AIController->StopMovement();

        // if can attack, attack, and then transition into cooldown
        if (AttackComponent && AttackComponent->bCanAttack)
        {
            AttackComponent->Attack();

            CooldownTimer = 0.0f;
            CurrentState = EEnemyState::AttackCooldown;
        }
    }
    else
    {
        AIController->MoveToActor(TargetPlayer, 0.0f);
    }

}

void AEnemyCharacterLogic::UpdateAttackCooldown(float DeltaTime)
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController) AIController->StopMovement();

    CooldownTimer += DeltaTime;

    // after the timer has elapsed, transition into going towards the player again
    if (CooldownTimer >= AttackComponent->TimeBetweenAttacks)
    {
        CooldownTimer = 0.0f;
        CurrentState = EEnemyState::WalkTowardsPlayer;
    }

}

