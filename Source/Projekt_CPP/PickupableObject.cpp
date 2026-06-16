// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableObject.h"

// Sets default values
APickupableObject::APickupableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void APickupableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    float YawRotation = RotationSpeed * DeltaTime;
    FRotator NewRotation = FRotator(0.0f, YawRotation, 0.0f);

    AddActorLocalRotation(NewRotation);
}

bool APickupableObject::GetItemData(FName& OutItemID, int& OutAmount)
{
    if (ItemID.IsNone()) return false;

    OutItemID = ItemID;
    OutAmount = Amount;
    return true;

}

