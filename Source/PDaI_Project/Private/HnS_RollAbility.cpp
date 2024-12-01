// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_RollAbility.h"
#include <PDaI_Project/HnS_PlayerController.h>
#include "GameFramework/Character.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

bool AHnS_RollAbility::Execute()
{
	if (!Super::Execute()) return false;
	
	if (auto* controller = Cast< AHnS_PlayerController>(user->GetController())) 
	{
		controller->SetStopMovement(true);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, user->GetActorLocation());
	}

	return true;
}
