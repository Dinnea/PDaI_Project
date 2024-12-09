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

	UPROPERTY(EditAnywhere, Category = "Q Ability")
	float QMultiplier;

	UPROPERTY(EditAnywhere, Category = "Q Ability")
	float QEffectDuration;

	UPROPERTY(BlueprintReadOnly)
	bool playRollAnimation = false;

	UPROPERTY(BlueprintReadOnly)
	bool trap_crouch = false;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* onFireParticleEffect;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* onFireInstance;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* UltimateFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	USceneComponent* R_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	USceneComponent* Q_Particle;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* qBuffParticleEffect;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* Q_FX;

	float globalDeltaTime;
	float Zpos;
	float prevMaxWalkSpeed;
	FVector destVector;
	bool invulnerable = false;
	bool isPlacingTrap = false;
	bool RCasted = false;
	bool QCasted = false;
	float prevCooldown;

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

	bool UltimateAutoAttack();

	void AbilityR();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupMesh();
	void SetupMovement();
	void CreateWeapon();
	void SetupHPBar();
	void enableMovement();
	void onFire();
	void disableRBuff();
	void disableQBuff();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Abilities");
	UChildActorComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities");
	UChildActorComponent* abilityW;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities");
	UChildActorComponent* abilityE;

	UPROPERTY(EditAnywhere, Category = "Abilities");
	UChildActorComponent* RBullet;

	UPROPERTY(EditAnywhere);
	USceneComponent* SpawnLocation;

	UPROPERTY(EditAnywhere, Category="Interp")
	float WaitTime;

	UPROPERTY(EditAnywhere, Category = "Interp")
	float InterpSpeed;

	UPROPERTY(EditAnywhere, Category = "Interp")
	float Distance;

	UPROPERTY(EditAnywhere, Category = "Ultimate Ability")
	float rDuration;

	UPROPERTY(EditAnywhere, Category = "Ultimate Ability")
	float RSpeedMultiplier;

	FTimerHandle fTimerHandle;

	class AHnS_Ability* autoAttack;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
