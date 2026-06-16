// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemRequirementObject.h"
#include "LockedButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_CPP_API ALockedButton : public AItemRequirementObject
{
    GENERATED_BODY()

public:
    ALockedButton();

protected:
    virtual void FireOnCompletion() override;
	
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString ButtonColorName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    class USoundBase* ClickSound;

};
