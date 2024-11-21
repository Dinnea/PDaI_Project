// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PDaI_Project/HnS_BaseEnemy.h"
#include "EnemySpawner.generated.h"

/// <summary>
/// Needs to be placed above the terrain, or the spawned enemies will vanish.
/// </summary>
UCLASS()
class PDAI_PROJECT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AHnS_BaseEnemy* SpawnAtSpawnerLocation(TSubclassOf<AHnS_BaseEnemy> enemyToSpawn);

	UFUNCTION(BlueprintCallable)
	AHnS_BaseEnemy* SpawnAtLocation(TSubclassOf<AHnS_BaseEnemy> enemyToSpawn, FVector location, FRotator rotation = FRotator(0.f, 0.f, 0.f));

	//UFUNCTION(BlueprintCallable)
	//FVector GetRandomLocation(float radius);
	//UFUNCTION(BlueprintCallable)
	//AHnS_BaseEnemy* SpawnAtRandomLocation(TSubclassOf<AHnS_BaseEnemy> enemyToSpawn, float radius);

protected:
	virtual void BeginPlay() override;

private: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;
	
};
