// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_RollAbility.h"
#include <PDaI_Project/HnS_PlayerController.h>
#include "GameFramework/Character.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <PDaI_Project/HnS_Character.h>
#include <Kismet/KismetMathLibrary.h>

bool AHnS_RollAbility::Execute()
{
	if (!Super::Execute()) return false;
	
	if (auto* controller = Cast< AHnS_PlayerController>(userPtr->GetController()))
	{
		controller->SetStopMovement(true);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, userPtr->GetActorLocation());
		//enable movement code was here

		//character roll function
		userPtr->SetInvulnerable(true);
		FHitResult attackHit;
		bool attackHitSuccessful = false;

		FVector ActorLocation = userPtr->GetActorLocation();

		attackHitSuccessful = controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, attackHit);

		if (attackHitSuccessful) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Debug test"));
			cachedDest_roll = attackHit.Location;
		}

		userPtr->rotatePlayer(cachedDest_roll);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Roll debug"));
		}
		FRotator rotVector = UKismetMathLibrary::FindLookAtRotation(cachedDest_roll, ActorLocation);
		destVector = GetActorLocation() + GetActorForwardVector() * Distance;



	}
	return true;
}

void AHnS_RollAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (userPtr->isRolling) 
	{
		SetActorLocation(FMath::VInterpConstantTo(userPtr->GetActorLocation(), destVector, DeltaTime, InterpSpeed));
	}

}

void AHnS_RollAbility::BeginPlay()
{
	if(userPtr = Cast<AHnS_Character>(user)){}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Error. Roll user not assigned"));
	}
}
