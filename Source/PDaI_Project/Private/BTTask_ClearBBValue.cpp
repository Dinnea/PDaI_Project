// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBBValue.h"
#include <PDaI_Project/BaseEnemyController.h>
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBBValue::UBTTask_ClearBBValue(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Clear BB value");
}

EBTNodeResult::Type UBTTask_ClearBBValue::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* NodeMemory)
{
	if (ABaseEnemyController* const controller = Cast<ABaseEnemyController>(ownerComponent.GetAIOwner()))
	{
		if (auto* const blackboard = ownerComponent.GetBlackboardComponent())
		{
			blackboard->ClearValue(GetSelectedBlackboardKey());
			FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
