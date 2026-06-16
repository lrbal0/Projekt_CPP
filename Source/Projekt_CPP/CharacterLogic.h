// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterLogic.generated.h"

class UHealthComponent;
class UAttackComponent;
class UInventoryComponent;
class UWidgetComponent;

UCLASS()
class PROJEKT_CPP_API ACharacterLogic : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterLogic();
	virtual void Move(const FVector2D MoveDir);
	virtual void Look(const FVector2D LookDir);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthWidgetComponent;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseSpeed = 500.0f;

	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }

};
