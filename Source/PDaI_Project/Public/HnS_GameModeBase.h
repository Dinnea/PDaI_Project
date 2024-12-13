// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HnS_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API AHnS_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isGameOver = false;

	UFUNCTION(BlueprintCallable)
	void AddScore(float value);

	UFUNCTION(BlueprintCallable)
	float GetScore();

	UFUNCTION(BlueprintCallable)
	void ResetScore();

protected:
	float score = 0;
	
};
