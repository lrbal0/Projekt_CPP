// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterLogic.h"
#include "Engine/DataTable.h"
#include "EnemyCharacterLogic.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float BaseDamage = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRange = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
	float AttackDelay = 0.125f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float PostAttackDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	FVector BoxHalfExtents = FVector(50.f, 50.f, 50.f);
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	WalkTowardsPlayer,
	ChaseAndAttack,
	AttackCooldown
};

class UAttackComponent;
class APlayerCharacterLogic;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, FName);

UCLASS()
class PROJEKT_CPP_API AEnemyCharacterLogic : public ACharacterLogic
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacterLogic();

	void ConfigureFromData(FName _enemyID, const FEnemyData& Data);
	void AttackPlayer();
	void SetTargetPlayer(APlayerCharacterLogic* _player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName EnemyID;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAttackComponent* AttackComponent;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEnemyState CurrentState = EEnemyState::WalkTowardsPlayer;

	UPROPERTY(BlueprintReadOnly)
	APlayerCharacterLogic* TargetPlayer = nullptr;

	FORCEINLINE UAttackComponent* GetAttackComponent() const { return AttackComponent; }
	FORCEINLINE APlayerCharacterLogic* GetTargetPlayer() const { return TargetPlayer; }
	FORCEINLINE FName GetEnemyID() const { return EnemyID; }

	FOnEnemyDeath OnEnemyDeath;

private:
	void UpdateWalkTowardsPlayer();
	void UpdateChaseAndAttack();
	void UpdateAttackCooldown(float DeltaTime);

	float CooldownTimer = 0.0f;

};
