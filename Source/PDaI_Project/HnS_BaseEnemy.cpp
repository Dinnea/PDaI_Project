// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_BaseEnemy.h"

AHnS_BaseEnemy::AHnS_BaseEnemy()
{
	this->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	PrimaryActorTick.bCanEverTick = true;
	SetupMesh();
	SetupMovement();
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHnS_BaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHnS_BaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UBehaviorTree* AHnS_BaseEnemy::GetBehaviorTree() const
{
	return behaviorTree;
}

APatrolPath* AHnS_BaseEnemy::GetPatrolPath() const
{
	return patrolPath;
}

float AHnS_BaseEnemy::GetAttackRange() const
{
	return attackRange;
}

void AHnS_BaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AHnS_BaseEnemy::Die()
{
	Destroy();
}
