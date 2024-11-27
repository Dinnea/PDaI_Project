// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "PDaI_Project/HnS_BaseEnemy.h"
#include <EnemySpawner.h>
#include "HnS_LevelScript.generated.h"



/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API AHnS_LevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Enemy Spawning")
	void MassEnemySpawn(TSubclassOf<AHnS_BaseEnemy> enemy, AEnemySpawner* spawner, float number, float radius);

	UFUNCTION(BlueprintCallable, Category = "Enemy Spawning")
	void SpecificEnemySpawn(TArray<TSubclassOf<AHnS_BaseEnemy>> enemyList, AEnemySpawner* spawner, float radius);

	UFUNCTION(BlueprintCallable, Category = "Enemy Spawning")
	void MassSpawnTimer(TSubclassOf<AHnS_BaseEnemy> enemy, AEnemySpawner* spawner, float number, float radius, float spawnInterval);

	UFUNCTION(BlueprintCallable, Category = "Enemy Spawning")
	void SpecificSpawnTimer(TArray<TSubclassOf<AHnS_BaseEnemy>> enemyList, AEnemySpawner* spawner, float radius, float spawnInterval);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AEnemySpawner>> spawners;
};
