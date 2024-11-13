// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"

/**
 * 
 */

UCLASS()

class PDAI_PROJECT_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	 explicit ABaseEnemyController(FObjectInitializer const& objectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
