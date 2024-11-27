// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AutoAttack.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API UBTTask_AutoAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_AutoAttack(FObjectInitializer const& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* NodeMemory) override;
	
};
