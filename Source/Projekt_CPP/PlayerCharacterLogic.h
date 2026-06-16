// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterLogic.h"
#include "PlayerCharacterLogic.generated.h"

class UInventoryComponent;
struct FInputActionValue;

UCLASS()
class PROJEKT_CPP_API APlayerCharacterLogic : public ACharacterLogic
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterLogic();
	void HandleMoveInput(const FInputActionValue& Value);
	void HandleJumpInput(const FInputActionValue& Value);
	void HandleLookInput(const FInputActionValue& Value);
	void FireInteract();
	void FireAttack();
	void CheckForPickups();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAttackComponent* AttackComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

public:	
	UPROPERTY(BlueprintReadOnly)
	float PickupRange = 100.0f;

	FORCEINLINE UAttackComponent* GetAttackComponent() const { return AttackComponent; }
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

private:
	FTimerHandle PickupTimerHandle;
};
