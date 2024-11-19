// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_IncrementPatrolPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API UBTTask_IncrementPatrolPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_IncrementPatrolPathIndex(FObjectInitializer const& objectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComponent, uint8* nodeMemory) override;

private:
	enum class EDirection {Forward, Reverse};

	EDirection direction = EDirection::Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="true"))
	bool biDirectional = false;
	
};
