// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AutoAttack.h"
#include <PDaI_Project/BaseEnemyController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <PDaI_Project/Hns_Character.h>
#include <Kismet/KismetMathLibrary.h>

UBTTask_AutoAttack::UBTTask_AutoAttack(FObjectInitializer const& objectInitializer)
{
	NodeName = TEXT("Auto Attack");
}

EBTNodeResult::Type UBTTask_AutoAttack::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* NodeMemory)
{
	//get ai controller + the npc

	if (ABaseEnemyController* const controller = Cast<ABaseEnemyController>(ownerComponent.GetAIOwner()))
	{
		if (auto* const enemy = Cast<AHnS_Character>(controller->GetPawn()))
		{
			if (auto* const blackboard = ownerComponent.GetBlackboardComponent())
			{
				AActor* const target = Cast<AActor>(blackboard->GetValueAsObject(GetSelectedBlackboardKey()));
				if (target)
				{
					//FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), target->GetActorLocation());
					//enemy->SetActorRotation(newRotation);
					//enemy->rotatePlayer(target->GetActorLocation());
					enemy->AutoAttack();
				}
			}
			
		}
		FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
