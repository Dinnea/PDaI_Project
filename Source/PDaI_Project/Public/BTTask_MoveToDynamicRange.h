// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToDynamicRange.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API UBTTask_MoveToDynamicRange : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	explicit UBTTask_MoveToDynamicRange(FObjectInitializer const& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
