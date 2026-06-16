// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
    SpawnEnemy();
}

AEnemyCharacterLogic* AEnemySpawner::SpawnEnemy()
{
    if (!EnemyClassToSpawn)
    {
        return nullptr;
    }

    if (!EnemyDataTable)
    {
        return nullptr;
    }

    // 1. get data for enemy
    FEnemyData* EnemyData = EnemyDataTable->FindRow<FEnemyData>(EnemyRowID, TEXT("EnemySpawner"));

    if (!EnemyData)
    {
        return nullptr;
    }

    // 2. set up parameters and spawn
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    SpawnParams.Owner = this;

    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    AEnemyCharacterLogic* NewEnemy = GetWorld()->SpawnActor<AEnemyCharacterLogic>(EnemyClassToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

    // 3. build the enemy
    if (NewEnemy)
    {
        NewEnemy->ConfigureFromData(EnemyRowID, *EnemyData);
        return NewEnemy;
    }

    return nullptr;
}

