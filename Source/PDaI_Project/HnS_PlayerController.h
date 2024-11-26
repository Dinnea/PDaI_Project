// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
//#include "InputActionValue.h"
#include "HnS_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float shortPressThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* autoAttack;
	
protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void autoAttackBullet(const FInputActionValue &value);

	class AHnS_Character* PlayerCharacter;

	bool canFire = true;

	UPROPERTY(EditAnywhere)
	float timeBetweenFires = 0.7f;

	void setCanFire(bool Value);

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector cachedDest;
	FVector cachedDest_attack;
	float followTime;
};
