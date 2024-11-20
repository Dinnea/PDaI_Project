// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawners.h"

// Sets default values
AEnemySpawners::AEnemySpawners()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector AEnemySpawners::GetSpawnPoint(int const index) const
{
	return spawnPoints[index];
}

FVector AEnemySpawners::GetSpawnPointWorldLoc(int const index) const
{
	return spawnPoints[index] + this->GetActorLocation();
}


int AEnemySpawners::Num() const
{
	return spawnPoints.Num();
}


