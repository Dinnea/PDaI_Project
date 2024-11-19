// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayer.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayer::UBTTask_FindPlayer(FObjectInitializer const& objectInitializer) 
{
	NodeName = TEXT("Find Player");
	
}

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* NodeMemory)
{
	if (ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) )
	{
		FVector playerLocation = player->GetActorLocation();
		if (searchRandom) 
		{
			FNavLocation location;
			if (UNavigationSystemV1* const navSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (navSystem->GetRandomPointInNavigableRadius(playerLocation, searchRadius, location)) 
				{
					ownerComponent.GetBlackboardComponent()->SetValueAsObject("targetActor", player);
					//ownerComponent.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), location.Location);
					FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else 
		{
			ownerComponent.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);
			FinishLatentTask(ownerComponent, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
		
	}
	
	return EBTNodeResult::Failed;
}

