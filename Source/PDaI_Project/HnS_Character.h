// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/Actor.h>
#include <HnS_Ability.h>
#include "HnS_Character.generated.h"



class USpringArmComponent;
class UCameraComponent;
class AHnS_Bullet;

UCLASS()
class PDAI_PROJECT_API AHnS_Character : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY()
	UCharacterMovementComponent* charMovement;


	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess="true"))
	class UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HPBar", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArm1;

public:
	// Sets default values for this character's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(BlueprintReadOnly)
	bool playRollAnimation = false;

	UPROPERTY(BlueprintReadOnly)
	bool trap_crouch = false;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* onFireParticleEffect;

	UParticleSystemComponent* onFireInstance;

	float globalDeltaTime;
	float Zpos;
	FVector destVector;
	bool invulnerable = false;

	FVector cachedDest_roll;


	AHnS_Character();
	float roll();
	bool AutoAttack();

	bool AbilityW();

	void updateRoll();

	void rotatePlayer(FVector destination);

	bool AbilityE();

	void setCrouch(bool flag);

	void disableOnFire();

	void enableOnFire(float duration);

	UFUNCTION(BlueprintCallable)
	AHnS_Ability* GetAbility(int ability);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupMesh();
	void SetupMovement();
	void CreateWeapon();
	void SetupHPBar();
	void enableMovement();
	void onFire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities");
	UChildActorComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities");
	UChildActorComponent* abilityW;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities");
	UChildActorComponent* abilityE;

	UPROPERTY(EditAnywhere);
	USceneComponent* SpawnLocation;

	UPROPERTY(EditAnywhere, Category="Interp")
	float WaitTime;

	UPROPERTY(EditAnywhere, Category = "Interp")
	float InterpSpeed;

	UPROPERTY(EditAnywhere, Category = "Interp")
	float Distance;

	FTimerHandle fTimerHandle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
