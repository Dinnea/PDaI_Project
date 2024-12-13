// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolPath.h"
#include "HnS_Character.h"
#include "HnS_BaseEnemy.generated.h"

/**
 * 
 */
class UBehaviorTree;
UCLASS()
class PDAI_PROJECT_API AHnS_BaseEnemy : public AHnS_Character
{
	GENERATED_BODY()

public:
	AHnS_BaseEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;	
	APatrolPath* GetPatrolPath() const;

	float GetAttackRange() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Die() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* behaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	APatrolPath* patrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float attackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points", meta = (AllowPrivateAccess = "true"))
	float points = 1;

	
};
