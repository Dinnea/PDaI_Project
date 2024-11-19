// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "BaseEnemy.h"
#include "HnS_Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"


ABaseEnemyController::ABaseEnemyController(FObjectInitializer const& objectInitializer)
{
	SetUpPerceptionSystem();
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

void ABaseEnemyController::SetUpPerceptionSystem()
{
	sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	if (sight) 
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		sight->SightRadius = 500.f;
		sight->LoseSightRadius = sight->SightRadius + 25.f;
		sight->PeripheralVisionAngleDegrees = 90;
		sight->SetMaxAge(5.f); //after 5 s the stimulus is forgotten
		sight->AutoSuccessRangeFromLastSeenLocation = 520.f;

		//Affiliation system not actively used in game, so to ensure no problems, all set to true
		sight->DetectionByAffiliation.bDetectEnemies = true;
		sight->DetectionByAffiliation.bDetectNeutrals = true;
		sight->DetectionByAffiliation.bDetectFriendlies = true;

		UPROPERTY()
		UAIPerceptionComponent* perception = GetPerceptionComponent();
		perception->SetDominantSense(*sight->GetSenseImplementation());
		perception->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyController::OnTargetDetected);
		perception->ConfigureSense(*sight);
	}

}

void ABaseEnemyController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (AHnS_Character* const character = Cast<AHnS_Character>(actor)) 
	{
		GetBlackboardComponent()->SetValueAsObject("targetActor", actor);
		//GetBlackboardComponent()->SetValueAsBool("hasSeenPlayer?", stimulus.WasSuccessfullySensed());
	}
}
