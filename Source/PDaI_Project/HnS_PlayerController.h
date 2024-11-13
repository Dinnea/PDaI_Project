// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "HnS_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PDAI_PROJECT_API AHnS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHnS_PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* defaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* setDestination;
	
protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

private:
	FVector cachedDest;
};
