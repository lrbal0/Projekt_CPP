// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterLogic.h"
#include "AttackComponent.h"
#include "InventoryComponent.h"
#include "InputActionValue.h"
#include "PlayerInteractable.h"
#include "PickupableObject.h"

// Sets default values
APlayerCharacterLogic::APlayerCharacterLogic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("AttackComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void APlayerCharacterLogic::HandleMoveInput(const FInputActionValue& Value)
{
	Move(Value.Get<FVector2D>());
}

void APlayerCharacterLogic::HandleJumpInput(const FInputActionValue& Value)
{
	// true = want jump, false = no jump
	if (Value.Get<bool>()) Jump();
	else StopJumping();
}

void APlayerCharacterLogic::HandleLookInput(const FInputActionValue& Value)
{
	Look(Value.Get<FVector2D>());
}

// Called when the game starts or when spawned
void APlayerCharacterLogic::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(
		PickupTimerHandle,
		this,
		&APlayerCharacterLogic::CheckForPickups,
		0.05f,
		true
	);
}

void APlayerCharacterLogic::FireInteract()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController) return;

	// 1. get raycast start and rotation
	FVector TraceStart;
	FRotator CameraRotation;
	PlayerController->GetPlayerViewPoint(TraceStart, CameraRotation);

	// 2. get raycast end
	float InteractRange = 1000.0f;
	FVector TraceEnd = TraceStart + (CameraRotation.Vector() * InteractRange);

	// 3. launch raycast
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	AActor* HitActor = nullptr;
	bool bHit = GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		TraceParams
	);

	if (bHit)
	{
		HitActor = HitResult.GetActor();
	}

	if (HitActor)
	{
		// check if the target is interactable
		if (HitActor->GetClass()->ImplementsInterface(UPlayerInteractable::StaticClass()))
		{
			// execute interactable interface function
			IPlayerInteractable::Execute_HandleInteract(HitActor, this);
		}
	}
}

void APlayerCharacterLogic::FireAttack()
{
	AttackComponent->Attack();
}

void APlayerCharacterLogic::CheckForPickups()
{
	UInventoryComponent* Inventory = FindComponentByClass<UInventoryComponent>();
	if (!Inventory) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FVector Center = GetActorLocation();

	// 1. setup sweep
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(PickupRange);
	TArray<FHitResult> HitResults;

	// 2. sweep
	bool bHit = World->SweepMultiByObjectType(
		HitResults,
		Center,
		Center,
		FQuat::Identity,
		ObjectQueryParams,
		CollisionShape,
		QueryParams
	);

	// 3. try casting pickupable object on every hitresult
	if (bHit)
	{
		for (const FHitResult& Result : HitResults)
		{
			AActor* HitActor = Result.GetActor();
			APickupableObject* Pickup = Cast<APickupableObject>(HitActor);

			if (Pickup)
			{
				FName PickupItemID;
				int PickupItemAmount;

				if (Pickup->GetItemData(PickupItemID, PickupItemAmount))
				{
					if (Inventory->AddItem(PickupItemID, PickupItemAmount))
					{
						Pickup->Destroy();
					}
				}
			}
		}
	}

}

