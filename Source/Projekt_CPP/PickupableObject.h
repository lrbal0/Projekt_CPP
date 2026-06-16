// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableObject.generated.h"

UCLASS()
class PROJEKT_CPP_API APickupableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupableObject();
	bool GetItemData(FName& OutItemID, int& OutAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemID = NAME_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Amount = 1;

	UPROPERTY(BlueprintReadOnly)
	float RotationSpeed = 100.0f;
};
