// Fill out your copyright notice in the Description page of Project Settings.

#include <string>
#include "HnS_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HnS_Character.h"

AHnS_PlayerController::AHnS_PlayerController()
{
	this->bShowMouseCursor = true;
	this->cachedDest = FVector::ZeroVector;
	followTime = 0;
}

void AHnS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AHnS_Character>(GetPawn());
}

void AHnS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) 
	{
		Subsystem ->AddMappingContext(defaultMappingContext, 0);
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("EnhancedInput debug!"));
		// Setup mouse input events
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Started, this, &AHnS_PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Triggered, this, &AHnS_PlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Completed, this, &AHnS_PlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Canceled, this, &AHnS_PlayerController::OnSetDestinationReleased);
		//Setup basic attack input events
		EnhancedInputComponent->BindAction(autoAttack, ETriggerEvent::Triggered, this, &AHnS_PlayerController::autoAttackBullet);
	}
	else
	{
		//log error maybe??
	}
}

void AHnS_PlayerController::OnInputStarted()
{
	//StopMovement();
}

void AHnS_PlayerController::OnSetDestinationTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Movement debug!"));
	followTime += GetWorld()->GetDeltaSeconds();
	FHitResult hit;
	bool hitSuccessful = false;

	hitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit);

	if (hitSuccessful) {
		cachedDest = hit.Location;
	}

	APawn* controlledPawn = GetPawn();
	if (controlledPawn != nullptr) {
		FVector direction = (cachedDest - controlledPawn->GetActorLocation()).GetSafeNormal();
		controlledPawn->AddMovementInput(direction, 1.0, false);
	}
}

void AHnS_PlayerController::OnSetDestinationReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(followTime));
	if (followTime <= shortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, cachedDest);
	}
	followTime = 0.f;
}

void AHnS_PlayerController::autoAttackBullet(const FInputActionValue &value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bullet debug!"));
	if (PlayerCharacter)
	{
		PlayerCharacter->ShootBullet();
	}
}

