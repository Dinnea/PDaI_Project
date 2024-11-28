// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToDynamicRange.h"
#include <PDaI_Project/BaseEnemyController.h>
#include <PDaI_Project/Hns_CharacterPlayer.h>
#include <PDaI_Project/HnS_BaseEnemy.h>

UBTTask_MoveToDynamicRange::UBTTask_MoveToDynamicRange(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Move To (Dynamic Range)");
}

EBTNodeResult::Type UBTTask_MoveToDynamicRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ABaseEnemyController* const controller = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const enemy = Cast<AHnS_BaseEnemy>(controller->GetPawn()))
		{
			AcceptableRadius = enemy->GetAttackRange();

			return Super::ExecuteTask(OwnerComp, NodeMemory);
		}
	}
	
	return EBTNodeResult::Failed;
}
