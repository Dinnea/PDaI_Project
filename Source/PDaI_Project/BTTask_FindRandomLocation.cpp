// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NavigationSystem.h"
#include "BaseEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* NodeMemory)
{
	//get ai controller + the npc

	if (ABaseEnemyController* const controller = Cast<ABaseEnemyController>(ownerComponent.GetAIOwner()))
	{
		if (APawn* const enemy = controller->GetPawn()) 
		{
			//find orginal location
			FVector const origin = enemy->GetActorLocation();
			

			if (UNavigationSystemV1* const navSystem = UNavigationSystemV1::GetCurrent(GetWorld())) 
			{
				FNavLocation location;

				if (navSystem->GetRandomPointInNavigableRadius(origin, searchRadius, location)) 
				{
					ownerComponent.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), location.Location);
				}

				FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
