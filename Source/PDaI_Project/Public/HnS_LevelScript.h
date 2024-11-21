// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "PDaI_Project/HnS_BaseEnemy.h"
#include "HnS_LevelScript.generated.h"


/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API AHnS_LevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
	void TEST()
	{
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Testing level blueprint."));
	}

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawning", meta = ( AllowPrivateAccess = "true")

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
	TArray<AHnS_BaseEnemy*> enemies;
};
