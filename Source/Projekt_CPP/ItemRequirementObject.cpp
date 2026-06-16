// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRequirementObject.h"
#include "PlayerCharacterLogic.h"
#include "InventoryComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AItemRequirementObject::AItemRequirementObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItemRequirementObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemRequirementObject::HandleInteract_Implementation(AActor* Interactee)
{
    if (bHasCompleted)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Pressing button..."));
        FireOnCompletion();
        return;
    }

    if (!Interactee) return;

    APlayerCharacterLogic* Player = Cast<APlayerCharacterLogic>(Interactee);
    if (!Player)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Interactee is not PlayerCharacterLogic!"));
        return;
    }

    UInventoryComponent* Inventory = Player->GetInventoryComponent();
    if (!Inventory)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Player has no Inventory Component!"));
        return;
    }

    // Check if player has the required item
    if (Inventory->HasItem(RequiredItemID, RequiredAmount))
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Found item: %s! Unlocking..."), *RequiredItemID.ToString()));
        bHasCompleted = true;

        if (UnlockSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, UnlockSound, GetActorLocation());
        }
       
        FItemData ItemDetails;
        if (Inventory->GetItemDetails(RequiredItemID, ItemDetails))
        {
            if (ItemDetails.bIsConsumable)
            {
                Inventory->RemoveItem(RequiredItemID, RequiredAmount);
            }
        }
    }
    else
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Missing item: %s"), *RequiredItemID.ToString()));
    }

}

void AItemRequirementObject::FireOnCompletion()
{
    

}
