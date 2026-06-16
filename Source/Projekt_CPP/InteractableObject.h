// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerInteractable.h"
#include "InteractableObject.generated.h"

UCLASS()
class PROJEKT_CPP_API AInteractableObject : public AActor, public IPlayerInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();
	virtual void HandleInteract_Implementation(AActor* Interactee) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
