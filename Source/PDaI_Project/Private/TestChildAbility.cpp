// Fill out your copyright notice in the Description page of Project Settings.


#include "TestChildAbility.h"

bool ATestChildAbility::Execute() 
{
	if (!Super::Execute())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Failed to execute."));
		return false;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ability is executed."));
	return true;
}
