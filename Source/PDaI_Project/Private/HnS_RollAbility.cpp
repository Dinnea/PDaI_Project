// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_RollAbility.h"
#include <PDaI_Project/HnS_PlayerController.h>
#include "GameFramework/Character.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <PDaI_Project/HnS_Character.h>
#include <Kismet/KismetMathLibrary.h>

bool AHnS_RollAbility::Execute()
{
	if (!Super::Execute())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("on cooldown"));
		return false;
	}
	
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("off cooldown"));
		if (auto* controller = Cast< AHnS_PlayerController>(user->GetController()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Got controller"));
			controller->SetStopMovement(true);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, user->GetActorLocation());
			//enable movement code was here
			FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_RollAbility::EndRoll);
			FTimerHandle mTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(mTimerHandle, Delegate, rollingDuration, false);
			//character roll function
			user->SetInvulnerable(true);
			FHitResult attackHit;
			bool attackHitSuccessful = false;

			FVector ActorLocation = user->GetActorLocation();
			attackHitSuccessful = controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, attackHit);

			if (attackHitSuccessful) {
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Debug test"));
				cachedDest_roll = attackHit.Location;
			}

			user->rotatePlayer(cachedDest_roll);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Roll debug"));
			}
			FRotator rotVector = UKismetMathLibrary::FindLookAtRotation(cachedDest_roll, ActorLocation);
			destVector = user->GetActorLocation() + user->GetActorForwardVector() * Distance;
			user->isRolling = true;

		}
		return true;
	}
}

void AHnS_RollAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (user->isRolling) 
	{
		user->SetActorLocation(FMath::VInterpConstantTo(user->GetActorLocation(), destVector, DeltaTime, InterpSpeed));
	}

}

void AHnS_RollAbility::BeginPlay()
{
	Super::BeginPlay();
}

void AHnS_RollAbility::EndRoll()
{
	if (auto* controller = Cast< AHnS_PlayerController>(user->GetController()))
	{
		controller->SetStopMovement(false);
		user->isRolling = false;
		user->invulnerable = false;
	}
}
