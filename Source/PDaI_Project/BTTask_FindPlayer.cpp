// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayer.h"

#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayer::UBTTask_FindPlayer(FObjectInitializer const& objectInitializer) 
{
	NodeName = TEXT("Find Player");
	
}

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* NodeMemory)
{
	if (ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) )
	{

	}
	
	return EBTNodeResult::Failed;
}

