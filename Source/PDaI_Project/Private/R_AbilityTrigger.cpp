// Fill out your copyright notice in the Description page of Project Settings.


#include "R_AbilityTrigger.h"
#include <PDaI_Project/HnS_PlayerController.h>
#include <PDaI_Project/HnS_Character.h>

bool AR_AbilityTrigger::Execute(bool flag)
{
	if (!Super::Execute(flag)) return false;

	if (auto* controller = Cast<AHnS_PlayerController>(user->GetController()))
	{
		user->AbilityR();
	}

	return true;
}

void AR_AbilityTrigger::SetCooldown()
{
	if (auto* controller = Cast<AHnS_PlayerController>(user->GetController()))
	{
		cooldown = controller->GetRCooldown();
	}
}

//void AR_AbilityTrigger::BeginPlay()
//{
//	Super::BeginPlay();
//
//	if (auto* controller = Cast<AHnS_PlayerController>(user->GetController()))
//	{
//		cooldown = controller->GetRCooldown();
//	}
//}
