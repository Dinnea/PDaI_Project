// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/Actor.h>
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

	AHnS_Character();
	AActor* AutoAttack();

	void TestAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupMesh();
	void SetupMovement();
	void CreateWeapon();
	void SetupHPBar();

	UPROPERTY(EditAnywhere, Category="Abilities");
	UChildActorComponent* Weapon;

	UPROPERTY(EditAnywhere, Category = "Abilities");
	UChildActorComponent* testAbility;


	UPROPERTY(EditAnywhere);
	USceneComponent* SpawnLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	USceneComponent* GetProjectileSpawnLocation();

};
