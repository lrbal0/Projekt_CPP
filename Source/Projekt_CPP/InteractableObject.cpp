// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableObject::HandleInteract_Implementation(AActor* Interactee)
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACTED WITH %s"), *GetName());

}
