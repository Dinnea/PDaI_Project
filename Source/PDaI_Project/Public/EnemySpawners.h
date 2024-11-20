// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawners.generated.h"

UCLASS()
class PDAI_PROJECT_API AEnemySpawners : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawners();

	FVector GetSpawnPoint(int const index) const;
	UFUNCTION(BlueprintCallable)
	FVector GetSpawnPointWorldLoc(int const index) const;
	int Num() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> spawnPoints;
};
