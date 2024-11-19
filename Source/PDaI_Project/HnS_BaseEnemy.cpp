// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_BaseEnemy.h"

AHnS_BaseEnemy::AHnS_BaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHnS_BaseEnemy::Tick(float DeltaTime)
{
}

UBehaviorTree* AHnS_BaseEnemy::GetBehaviorTree() const
{
	return behaviorTree;
}

APatrolPath* AHnS_BaseEnemy::GetPatrolPath() const
{
	return patrolPath;
}

void AHnS_BaseEnemy::BeginPlay()
{
}
