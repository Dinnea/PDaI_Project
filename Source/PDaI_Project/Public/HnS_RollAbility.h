// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HnS_Ability.h"
#include "HnS_RollAbility.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API AHnS_RollAbility : public AHnS_Ability
{
	GENERATED_BODY()
public:
	virtual bool Execute() override;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Stats")
	float rollingDuration = 1.012;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Distance;

	UPROPERTY(EditAnywhere, Category = "Interp")
	float WaitTime;

	UPROPERTY(EditAnywhere, Category = "Interp")
	float InterpSpeed;

private:
	void EndRoll();
	FVector destVector;
	FVector cachedDest_roll;
	
};
