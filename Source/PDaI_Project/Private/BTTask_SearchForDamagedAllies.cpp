// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchForDamagedAllies.h"
#include <PDaI_Project/BaseEnemyController.h>
#include <PDaI_Project/HnS_BaseEnemy.h>
#include <HnS_HealAbility.h>

UBTTask_SearchForDamagedAllies::UBTTask_SearchForDamagedAllies(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Search For Damaged Allies");
}

EBTNodeResult::Type UBTTask_SearchForDamagedAllies::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* NodeMemory)
{
	if (auto* const controller = Cast<ABaseEnemyController>(ownerComponent.GetAIOwner())) 
	{
		if (auto* const enemy = Cast<AHnS_BaseEnemy>(controller->GetPawn()))
		{
			if (auto* const healPtr = Cast<AHnS_HealAbility>(enemy->GetAbilityW())) 
			{
				if (auto* const blackboard = ownerComponent.GetBlackboardComponent())
				{

				}
			}

			
		}
		FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
