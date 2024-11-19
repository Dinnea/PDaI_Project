// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SelectPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API UBTTask_SelectPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_SelectPathPoint(FObjectInitializer const& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, Category="Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector patrolPathVectorKey;
};
