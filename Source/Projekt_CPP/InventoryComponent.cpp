// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include <Kismet/GameplayStatics.h>
#include <MissionManager.h>

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UInventoryComponent::AddItem(FName ItemID, int Amount)
{
    if (Amount <= 0 || ItemID.IsNone()) return false;

    FItemData ItemDetails;
    if (!GetItemDetails(ItemID, ItemDetails))
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemID '%s' missing from MasterTable!"), *ItemID.ToString());
        return false;
    }

    const bool bAlreadyOwned = Items.Contains(ItemID);
    if (!ItemDetails.bIsStackable)
    {
        if (bAlreadyOwned) return false;
        Amount = 1;
    }

    int& CurrentAmount = Items.FindOrAdd(ItemID);
    CurrentAmount += Amount;

    if (UWorld* World = GetWorld())
    {
        if (AActor* ManagerActor = UGameplayStatics::GetActorOfClass(World, AMissionManager::StaticClass()))
        {
            if (AMissionManager* MissionManager = Cast<AMissionManager>(ManagerActor))
            {
                MissionManager->NotifyItemPickedUp(ItemID, Amount);
            }
        }
    }

    return true;
}

bool UInventoryComponent::HasItem(FName ItemID, int RequiredAmount) const
{
    if (ItemID.IsNone()) return false;

    const int* FoundAmount = Items.Find(ItemID);
    return FoundAmount && (*FoundAmount >= RequiredAmount);
}

bool UInventoryComponent::RemoveItem(FName ItemID, int Amount)
{
    if (!HasItem(ItemID, Amount)) return false;

    Items[ItemID] -= Amount;

    if (Items[ItemID] <= 0)
    {
        Items.Remove(ItemID);
    }
    return true;
}

bool UInventoryComponent::GetItemDetails(FName ItemID, FItemData& OutItemData) const
{
    if (!ItemMasterTable) return false;

    FItemData* FoundData = ItemMasterTable->FindRow<FItemData>(ItemID, TEXT("InventoryContext"));
    if (FoundData)
    {
        OutItemData = *FoundData;
        return true;
    }
    return false;
}
