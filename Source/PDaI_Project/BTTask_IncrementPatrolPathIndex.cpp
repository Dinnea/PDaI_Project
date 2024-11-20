// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPatrolPathIndex.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemyController.h"
#include "HnS_BaseEnemy.h"

UBTTask_IncrementPatrolPathIndex::UBTTask_IncrementPatrolPathIndex(FObjectInitializer const& objectInitializer) : UBTTask_BlackboardBase(objectInitializer)
{
	NodeName = TEXT("Increment patrol path index");
}

EBTNodeResult::Type UBTTask_IncrementPatrolPathIndex::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory)
{

	if (auto* const controller = Cast<ABaseEnemyController>(ownerComponent.GetAIOwner()))
	{
		if (auto* const enemy = Cast<AHnS_BaseEnemy>(controller -> GetPawn())) 
		{
			if (auto* const blackboard = ownerComponent.GetBlackboardComponent()) 
			{
				int const pointsNr = enemy->GetPatrolPath()->Num();
				int const indexMin = 0;
				int const indexMax = pointsNr - 1;

				int index = blackboard->GetValueAsInt(GetSelectedBlackboardKey());

					if (biDirectional) 
					{
						if (index >= indexMax && direction == EDirection::Forward) direction = EDirection::Reverse;
						else if (index <= indexMin && direction == EDirection::Reverse) direction = EDirection::Forward;
					}
				blackboard->SetValueAsInt(GetSelectedBlackboardKey(), 
							(direction == EDirection::Forward ? ++index : --index) % pointsNr);
				FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
