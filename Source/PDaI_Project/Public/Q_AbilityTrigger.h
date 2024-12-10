// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HnS_Ability.h"
#include "Q_AbilityTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API AQ_AbilityTrigger : public AHnS_Ability
{
	GENERATED_BODY()

public:
	virtual bool Execute(bool flag) override;
	void SetCooldown();	
};
