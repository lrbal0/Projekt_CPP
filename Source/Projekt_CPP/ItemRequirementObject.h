// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerInteractable.h"
#include "ItemRequirementObject.generated.h"

UCLASS()
class PROJEKT_CPP_API AItemRequirementObject : public AActor, public IPlayerInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemRequirementObject();
	virtual void HandleInteract_Implementation(AActor* Interactee);
	virtual void FireOnCompletion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName RequiredItemID = NAME_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int RequiredAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	class USoundBase* UnlockSound;

private:
	bool bHasCompleted = false;

};
