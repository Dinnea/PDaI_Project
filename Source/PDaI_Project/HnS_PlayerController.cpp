// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"

AHnS_PlayerController::AHnS_PlayerController()
{
	this->bShowMouseCursor = true;
	this->cachedDest = FVector::ZeroVector;
}

void AHnS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
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
		// Setup mouse input events
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Started, this, &AHnS_PlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Triggered, this, &AHnS_PlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Completed, this, &AHnS_PlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(setDestination, ETriggerEvent::Canceled, this, &AHnS_PlayerController::OnSetDestinationReleased);
	}
	else
	{
		//log error maybe??
	}
}

void AHnS_PlayerController::OnInputStarted()
{
	StopMovement();
}

void AHnS_PlayerController::OnSetDestinationTriggered()
{

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
}
