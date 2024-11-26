// Fill out your copyright notice in the Description page of Project Settings.

#include "HnS_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include <string>
#include "Kismet/KismetMathLibrary.h"
#include "HnS_Character.h"

AHnS_PlayerController::AHnS_PlayerController()
{
	this->bShowMouseCursor = true;
	this->cachedDest = FVector::ZeroVector;
	followTime = 0;
	this->cachedDest_attack = FVector::ZeroVector;
}

void AHnS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, GetPawn()->GetFName().ToString());
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
		EnhancedInputComponent->BindAction(autoAttack, ETriggerEvent::Started, this, &AHnS_PlayerController::autoAttackBullet);
	
		//ability input events
		EnhancedInputComponent->BindAction(ability1, ETriggerEvent::Started, this, &AHnS_PlayerController::OnAbility1);
	EnhancedInputComponent->BindAction(QAbility, ETriggerEvent::Started, this, &AHnS_PlayerController::q_ability);

		EnhancedInputComponent->BindAction(QAbility, ETriggerEvent::Started, this, &AHnS_PlayerController::q_ability);
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Movement debug!"));
	GetCharacter()->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(followTime));
	if (followTime <= shortPressThreshold)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Navigation movement debug"));
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, cachedDest);
	}
	followTime = 0.f;
}

void AHnS_PlayerController::autoAttackBullet(const FInputActionValue &value)
{
	FHitResult attackHit;
	bool attackHitSuccessful = false;

	attackHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, attackHit);

	if (attackHitSuccessful) {
		cachedDest_attack = attackHit.Location;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bullet debug!"));
	if (PlayerCharacter)// && canFire)
	{

		GetCharacter()->GetCharacterMovement()->DisableMovement();
		APawn* instigatorPawn = GetPawn();
		FVector PlayerLoc = instigatorPawn->GetActorLocation();
		FVector CursorLocation = cachedDest_attack;
		FRotator PlayerRotation = UKismetMathLibrary::FindLookAtRotation(CursorLocation, PlayerLoc);
		FRotator newPlayerRotation = FRotator(instigatorPawn->GetActorRotation().Pitch, PlayerRotation.Yaw - 180, instigatorPawn->GetActorRotation().Roll);
		instigatorPawn->SetActorRotation(newPlayerRotation);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *(PlayerRotation.ToString()));

		PlayerCharacter->AutoAttack();

	}
}

void AHnS_PlayerController::OnAbility1()
{
	if (PlayerCharacter) 
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "AAAAA");
		PlayerCharacter->TestAbility();
	}
}
void AHnS_PlayerController::q_ability(const FInputActionValue& value)
{
	if (canRoll)
	{
		PlayerCharacter->roll();
	}
	canRoll = false;
	FTimerDelegate qDelegate = FTimerDelegate::CreateUObject(this, &AHnS_PlayerController::setCanCastQ, true);
	FTimerHandle qTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(qTimerHandle, qDelegate, QCooldown, false);
}

void AHnS_PlayerController::setCanCastQ(bool Value)
{
	canRoll = true;
}

