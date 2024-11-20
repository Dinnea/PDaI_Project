// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SelectPathPoint.h"
#include "BaseEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HnS_BaseEnemy.h"

UBTTask_SelectPathPoint::UBTTask_SelectPathPoint(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Select Path Point");
}

EBTNodeResult::Type UBTTask_SelectPathPoint::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{
	if (auto* const controller = Cast<ABaseEnemyController>(ownerComponent.GetAIOwner())) 
	{
		if (auto* const blackboard = ownerComponent.GetBlackboardComponent()) 
		{
			int const index = blackboard->GetValueAsInt(GetSelectedBlackboardKey());

			if (auto* enemy = Cast<AHnS_BaseEnemy>(controller->GetPawn())) 
			{
				auto* path = enemy->GetPatrolPath();

				auto const localPosition = path->GetPatrolPoint(index);

				auto const globalPosition = path->GetActorTransform().TransformPosition(localPosition);

				blackboard->SetValueAsVector(patrolPathVectorKey.SelectedKeyName, globalPosition);

				FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;

			}
		}

	}

	return EBTNodeResult::Failed;
}
