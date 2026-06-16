// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (MultiLine = true))
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<UTexture2D> Icon = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool bIsConsumable = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool bIsStackable = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJEKT_CPP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
    bool AddItem(FName ItemID, int Amount = 1);
    bool HasItem(FName ItemID, int RequiredAmount = 1) const;
    bool RemoveItem(FName ItemID, int Amount = 1);
    bool GetItemDetails(FName ItemID, FItemData& OutItemData) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
    // assignable data table that holds all items
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UDataTable> ItemMasterTable;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<FName, int> Items;

};
