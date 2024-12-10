// Fill out your copyright notice in the Description page of Project Settings.


#include "Q_AbilityTrigger.h"
#include "PDaI_Project/HnS_Character.h"
#include <PDaI_Project/HnS_PlayerController.h>

bool AQ_AbilityTrigger::Execute(bool flag)
{
	if (!Super::Execute(flag)) return false;

	if (auto* controller = Cast<AHnS_PlayerController>(user->GetController())) 
	{
		controller->q_ability();
	}

	return true;
}

void AQ_AbilityTrigger::SetCooldown()
{
	if (auto* controller = Cast<AHnS_PlayerController>(user->GetController()))
	{
		cooldown = controller->GetQCooldown();
	}
}

