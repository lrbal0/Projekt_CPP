// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterLogic.h"
#include "HealthComponent.h"
#include "AttackComponent.h"
#include "InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "PlayerInteractable.h"
#include "PickupableObject.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"

// Sets default values
ACharacterLogic::ACharacterLogic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidgetComp"));
	HealthWidgetComponent->SetupAttachment(GetRootComponent());

	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawSize(FVector2D(150.0f, 20.0f));
	HealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	}

}

// Called when the game starts or when spawned
void ACharacterLogic::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	}

	if (HealthWidgetComponent)
	{
		if (UHealthBarWidget* HealthUI = Cast<UHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject()))
		{
			HealthUI->InitializeHealthWidget(HealthComponent);
		}
	}
}

void ACharacterLogic::Move(const FVector2D MoveDir)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDir, MoveDir.Y);
		AddMovementInput(RightDir, MoveDir.X);
	}

}

void ACharacterLogic::Look(const FVector2D LookDir)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookDir.X);
		AddControllerPitchInput(LookDir.Y);
	}

}

