// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HnS_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API UHnS_GameInstance : public UGameInstance
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
