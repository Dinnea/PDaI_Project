// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
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

private:
	class UAISenseConfig_Sight* sight;
	class UAISenseConfig_Hearing* hearing;

	void SetUpPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);
	
};
