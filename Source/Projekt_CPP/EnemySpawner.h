// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCharacterLogic.h"
#include "EnemySpawner.generated.h"

UCLASS()
class PROJEKT_CPP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The DataTable containing your FEnemyData rows
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
	UDataTable* EnemyDataTable;

	// The Row Name (ID) of the enemy you want to spawn from the table
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
	FName EnemyRowID;

	// The concrete blueprint/C++ class of the enemy to instantiate
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
	TSubclassOf<AEnemyCharacterLogic> EnemyClassToSpawn;

public:	
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	AEnemyCharacterLogic* SpawnEnemy();

};
