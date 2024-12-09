// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "StructsAndEnums.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)

struct FCooldownWidget
{
	GENERATED_USTRUCT_BODY()

	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float height;

	FCooldownWidget() 
	{
		width = 100;
		height = 100;
	}
	FCooldownWidget(float pWidth, float pHeight)
	{
		width = pWidth;
		height = pHeight;
	}
	

};
