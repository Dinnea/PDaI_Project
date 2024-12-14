// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "Hns_CharacterPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionComponent.h"
#include "HnS_BaseEnemy.h"


ABaseEnemyController::ABaseEnemyController(FObjectInitializer const& objectInitializer)
{
	SetUpPerceptionSystem();
}

void ABaseEnemyController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);

	if (auto* const enemy = Cast<AHnS_BaseEnemy>(InPawn)) 
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
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	UPROPERTY()
	UAIPerceptionComponent* perception = GetPerceptionComponent();

	if (sight) 
	{
		
		sight->SightRadius = 500.f;
		sight->LoseSightRadius = sight->SightRadius + 25.f;
		sight->PeripheralVisionAngleDegrees = 360;
		sight->SetMaxAge(5.f); //after 5 s the stimulus is forgotten
		sight->AutoSuccessRangeFromLastSeenLocation = 520.f;
	

		//Affiliation system not actively used in game, so to ensure no problems, all set to true
		sight->DetectionByAffiliation.bDetectEnemies = true;
		sight->DetectionByAffiliation.bDetectNeutrals = true;
		sight->DetectionByAffiliation.bDetectFriendlies = true;

		
		perception->SetDominantSense(*sight->GetSenseImplementation());
		perception->ConfigureSense(*sight);
	}

	hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing"));

	if (hearing) 
	{
		hearing->HearingRange = 2000.f;

		hearing->SetMaxAge(5.f);
		hearing->DetectionByAffiliation.bDetectEnemies = true;
		hearing->DetectionByAffiliation.bDetectNeutrals = true;
		hearing->DetectionByAffiliation.bDetectFriendlies = true;
		perception->ConfigureSense(*hearing);
	}

	if (hearing || sight) 
	{
		perception->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyController::OnTargetDetected);
	}

}

void ABaseEnemyController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>()) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SOUND"));
		if (auto* const ptr = Cast<AHnS_Bullet>(actor)) GetBlackboardComponent()->SetValueAsVector("soundLocation", actor->GetActorLocation());
	}
	else if (auto* const character = Cast<AHns_CharacterPlayer>(actor)) 
	{
		GetBlackboardComponent()->SetValueAsObject("targetActor", actor);
		//GetBlackboardComponent()->SetValueAsBool("hasSeenPlayer?", stimulus.WasSuccessfullySensed());
	}
}
