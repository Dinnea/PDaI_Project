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

	void SetupMesh();
	void SetupMovement();

public:
	// Sets default values for this character's properties
	AHnS_Character();
	AActor* ShootBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere);
	UChildActorComponent* Weapon;

	UPROPERTY(EditAnywhere);
	USceneComponent* SpawnLocation;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHnS_Bullet> BulletToSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
