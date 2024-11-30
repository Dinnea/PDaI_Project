// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HnS_Ability.h"
#include "TestChildAbility.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API ATestChildAbility : public AHnS_Ability
{
	GENERATED_BODY()

public:
	virtual bool Execute() override;
	
};
