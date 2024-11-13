// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BehaviorTree.h"


ABaseEnemyController::ABaseEnemyController(FObjectInitializer const& objectInitializer)
{
}

void ABaseEnemyController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);

	if (ABaseEnemy* const enemy = Cast<ABaseEnemy>(InPawn)) 
	{
		if (UBehaviorTree* const behaviorTree = enemy->GetBehaviorTree()) 
		{
			UBlackboardComponent* blackboard;

			UseBlackboard(behaviorTree->BlackboardAsset, blackboard);

			Blackboard = blackboard;

			RunBehaviorTree(behaviorTree);
		}
	}
}
