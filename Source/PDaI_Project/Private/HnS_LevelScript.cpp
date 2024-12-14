// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_LevelScript.h"

void AHnS_LevelScript::MassEnemySpawn(TSubclassOf<AHnS_BaseEnemy> enemy, AEnemySpawner* spawner, float number, float radius)
{
	
	auto* const _spawner = Cast<AEnemySpawner>(spawner);
	for (int i = 0; i < number; i++) 
	{
		_spawner->SpawnAtRandomLocation(enemy, radius);
	}
	
}

void AHnS_LevelScript::SpecificEnemySpawn(TArray<TSubclassOf<AHnS_BaseEnemy>> enemyList, AEnemySpawner* spawner, float radius)
{
	auto* const _spawner = Cast<AEnemySpawner>(spawner);
	for (TSubclassOf<AHnS_BaseEnemy> enemy : enemyList)
	{
		_spawner->SpawnAtRandomLocation(enemy, radius);
	}
}

void AHnS_LevelScript::MassSpawnTimer(TSubclassOf<AHnS_BaseEnemy> enemy, AEnemySpawner* spawner, float number, float radius, float spawnInterval)
{
	FTimerHandle spawnTimer;

	FTimerDelegate spawnerDelegate;

	spawnerDelegate.BindUFunction(this, "MassEnemySpawn", enemy, spawner, number, radius);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ene spawn"));
	GetWorld()->GetTimerManager().SetTimer(spawnTimer, spawnerDelegate, spawnInterval, true); //will spawn enemies constantly
}

void AHnS_LevelScript::SpecificSpawnTimer(TArray<TSubclassOf<AHnS_BaseEnemy>> enemyList, AEnemySpawner* spawner, float radius, float spawnInterval)
{
	FTimerHandle spawnTimer;

	FTimerDelegate spawnerDelegate;

	spawnerDelegate.BindUFunction(this, "SpecificEnemySpawn", enemyList, spawner, radius);

	GetWorld()->GetTimerManager().SetTimer(spawnTimer, spawnerDelegate, spawnInterval, true); //will spawn enemies constantly
}
