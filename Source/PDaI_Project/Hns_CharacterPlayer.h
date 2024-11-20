// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HnS_Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Hns_CharacterPlayer.generated.h"


/**
 * 
 */


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PDAI_PROJECT_API AHns_CharacterPlayer : public AHnS_Character
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* stimulusSource;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* camera;

	void SetupStimulusSouce();
	void SetupCamera();

public:
	AHns_CharacterPlayer();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
