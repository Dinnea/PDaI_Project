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
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
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
		Subsystem->AddMappingContext(defaultMappingContext, 0);
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
		EnhancedInputComponent->BindAction(QAbility, ETriggerEvent::Started, this, &AHnS_PlayerController:: TriggerQ);
		EnhancedInputComponent->BindAction(EAbility, ETriggerEvent::Started, this, &AHnS_PlayerController::e_ability);
		EnhancedInputComponent->BindAction(RAbility, ETriggerEvent::Started, this, &AHnS_PlayerController::TriggerR);
	}
	else
	{
		//log error maybe??
	}
}

void AHnS_PlayerController::OnInputStarted()
{
	//StopMovement();
	cachedDest = getClickLocation();
	FVector location = cachedDest;
	FRotator rotation = FRotator::ZeroRotator;
	FVector scale = FVector(0.1f, 0.1f, 0.1f);
	FTransform transform;
	transform.SetLocation(location);
	transform.SetRotation(FQuat(rotation));
	transform.SetScale3D(scale);
	UParticleSystemComponent* particleComponent = UGameplayStatics::SpawnEmitterAtLocation(this, clickDestEffect, location, rotation, true);
	if (particleComponent)
	{
		// Apply the desired scale
		particleComponent->SetWorldScale3D(scale);
	}
}

void AHnS_PlayerController::OnSetDestinationTriggered()
{
	if (!isRolling && !PlayerCharacter->trap_crouch && !dead)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Movement debug!"));
		GetCharacter()->GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
		followTime += GetWorld()->GetDeltaSeconds();

		cachedDest = getClickLocation();

		APawn* controlledPawn = GetPawn();
		if (controlledPawn != nullptr) {
			FVector direction = (cachedDest - controlledPawn->GetActorLocation()).GetSafeNormal();
			controlledPawn->AddMovementInput(direction, 1.0, false);
		}
	}
}

void AHnS_PlayerController::OnSetDestinationReleased()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(followTime));
	if (followTime <= shortPressThreshold && !isRolling && !dead)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Navigation movement debug"));
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, cachedDest);
	}
	followTime = 0.f;
}

void AHnS_PlayerController::autoAttackBullet(const FInputActionValue& value)
{
	cachedDest_attack = getClickLocation();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bullet debug!"));
	if (PlayerCharacter && !dead && canUseAbilities)
	{
		/*
		APawn* ludek = GetPawn();
		FVector PlayerLoc = ludek->GetActorLocation();
		FVector CursorLocation = cachedDest_attack;
		FRotator PlayerRotation = UKismetMathLibrary::FindLookAtRotation(CursorLocation, PlayerLoc);
		FRotator newPlayerRotation = FRotator(ludek->GetActorRotation().Pitch, PlayerRotation.Yaw - 180, ludek->GetActorRotation().Roll);
		ludek->SetActorRotation(newPlayerRotation); //ludek->GetActorRotation().Yaw
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *(PlayerRotation.ToString()));
		*/
		PlayerCharacter->rotatePlayer(cachedDest_attack);

		if (PlayerCharacter->RCasted) { PlayerCharacter->UltimateAutoAttack(); }
		else { PlayerCharacter->AutoAttack();
		GetCharacter()->GetCharacterMovement()->DisableMovement(); }
	}
}

void AHnS_PlayerController::OnAbility1()
{
	cachedDest_W = getClickLocation();
	if (PlayerCharacter && !dead && canUseAbilities)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Clicked use ability W key");
		GetCharacter()->GetCharacterMovement()->DisableMovement();
		PlayerCharacter->rotatePlayer(cachedDest_W);

		PlayerCharacter->AbilityW();
	}
}
void AHnS_PlayerController::q_ability()
{

	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PlayerCharacter->GetActorLocation());
	isRolling = true;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PlayerCharacter->GetActorLocation()); //Overwrite old move destination to stop movement on Q pressed event
	//StopMovement();
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_PlayerController::enableMovement);
	FTimerHandle mTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(mTimerHandle, Delegate, rollingTime, false);
	PlayerCharacter->roll();
	if (!isRolling)
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("false"));
		cachedDest = PlayerCharacter->destVector;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, canRoll ? TEXT("True") : TEXT("False"));
	//if (canRoll)
	//{
	//	
	//	canRoll = false;
	//	//GetWorldTimerManager().ClearTimer(qTimerHandle);
	//	FTimerDelegate qDelegate = FTimerDelegate::CreateUObject(this, &AHnS_PlayerController::setCanCastQ, true);
	//	FTimerHandle qTimerHandle;
	//	GetWorld()->GetTimerManager().SetTimer(qTimerHandle, qDelegate, QCooldown, false);
	//}
}

float AHnS_PlayerController::GetQCooldown()
{
	return QCooldown;
}

void AHnS_PlayerController::TriggerQ()
{
	if (PlayerCharacter && !dead && canUseAbilities)
	{
		PlayerCharacter->TriggerAbilityQ();
	}
}

void AHnS_PlayerController::enableMovement()
{
	isRolling = false;
	PlayerCharacter->updateRoll();
	PlayerCharacter->invulnerable = false;
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, cachedDest);
	prevTimeBetweenFires = timeBetweenFires;
	timeBetweenFires = timeBetweenFires - 0.3;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(timeBetweenFires));

	FTimerDelegate tDelegate = FTimerDelegate::CreateUObject(this, &AHnS_PlayerController::setTimeBetweenFires);
	FTimerHandle tTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(tTimerHandle, tDelegate, 2, false);
}

void AHnS_PlayerController::setTimeBetweenFires()
{
	timeBetweenFires = prevTimeBetweenFires;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(timeBetweenFires));
}

void AHnS_PlayerController::e_ability(const FInputActionValue& value)
{
	if (PlayerCharacter && !dead && canUseAbilities)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Clicked use ability E key");
		cachedDest_E = getClickLocation();
		GetCharacter()->GetCharacterMovement()->DisableMovement();
		GetCharacter()->GetCharacterMovement()->DisableMovement();
		PlayerCharacter->rotatePlayer(cachedDest_E);

		PlayerCharacter->AbilityE();
	}
}

void AHnS_PlayerController::TriggerR()
{
	if (PlayerCharacter && !dead && canUseAbilities)
	{
		PlayerCharacter->TriggerAbilityR();
	}

	/*if (PlayerCharacter && canCastR)
	{
		

		canCastR = false;
		FTimerDelegate ult_Delegate = FTimerDelegate::CreateUObject(this, &AHnS_PlayerController::setCanCastR);
		FTimerHandle ult_TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ult_TimerHandle, ult_Delegate, RCooldown, false);
	}*/
}

float AHnS_PlayerController::GetRCooldown()
{
	return RCooldown;
}

void AHnS_PlayerController::setDead(bool flag)
{
	dead = flag;
}

void AHnS_PlayerController::setCanCastE()
{
	canCastE = true;
}

void AHnS_PlayerController::setCanCastR()
{
	canCastR = true;
}

void AHnS_PlayerController::setCanUseAbilities(bool flag)
{
	canUseAbilities = flag;
}

FVector AHnS_PlayerController::getClickLocation()
{
	FHitResult attackHit;
	bool attackHitSuccessful = false;

	attackHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, attackHit);

	if (attackHitSuccessful) {
		return attackHit.Location;
	}
	else
	{
		return FVector::ZeroVector;
	}
	return FVector();
}

/*
void AHnS_PlayerController::setCanFire(bool Value)
{
	canFire = true;
}
*/

void AHnS_PlayerController::setCanCastQ(bool Value)
{
	canRoll = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(GetWorldTimerManager().GetTimerElapsed(qTimerHandle)));
}

