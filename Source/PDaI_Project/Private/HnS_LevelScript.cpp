// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_LevelScript.h"

void AHnS_LevelScript::MassEnemySpawn(TSubclassOf<AHnS_BaseEnemy> enemy, AEnemySpawner* spawner, float number, float radius)
{
	
	auto* const test = Cast<AEnemySpawner>(spawner);
	for (int i = 0; i < number; i++) 
	{
		test->SpawnAtRandomLocation(enemy, radius);
	}
	
}
