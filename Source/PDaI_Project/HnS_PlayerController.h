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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ability1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* EAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RAbility;

	FVector cachedDest_attack;

	FVector cachedDest_W;

	FVector cachedDest_E;
	void q_ability();
	float GetQCooldown();
	void TriggerQ();

	void TriggerR();
	float GetRCooldown();


protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void autoAttackBullet(const FInputActionValue& value);
	
	void OnAbility1();
	void enableMovement();
	void setTimeBetweenFires();
	void e_ability(const FInputActionValue& value);
	
	void setCanCastE();
	void setCanCastR();
	FVector getClickLocation();

	class AHnS_Character* PlayerCharacter;


	bool isRolling = false;

	float prevTimeBetweenFires = 0.f;

	//FTimerHandle qTimerHandle;

	UPROPERTY(BlueprintReadOnly)
	bool canRoll = true;

	UPROPERTY(BlueprintReadOnly)
	bool canCastE = true;

	UPROPERTY(BlueprintReadOnly)
	bool canCastR = true;

	UPROPERTY(EditAnywhere)
	float timeBetweenFires = 0.7f;

	UPROPERTY(EditAnywhere)
	float QCooldown = 7.f;

	UPROPERTY(EditAnywhere)
	float ECooldown = 13.f;

	UPROPERTY(EditAnywhere)
	float RCooldown = 90.f;

	UPROPERTY(EditAnywhere)
	float rollingTime;

	void setCanCastQ(bool Value);

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector cachedDest;
	float followTime;
};
