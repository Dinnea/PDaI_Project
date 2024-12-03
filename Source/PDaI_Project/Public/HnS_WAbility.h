// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HnS_WAbility.generated.h"

UCLASS()
class PDAI_PROJECT_API AHnS_WAbility : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHnS_WAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* W_FX;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* Particle;

	UPROPERTY(EditAnywhere)
	float WDistance;

	UPROPERTY(EditAnywhere)
	float damageInterval;

	UPROPERTY(EditAnywhere)
	int fireTicks;

	UPROPERTY(EditAnywhere)
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	int prevFireTicks;

	FTimerHandle mTimerHandle;

	FVector wDestVector;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	void setLocationAfterDelay();

	void fireDamage(AActor* actorToDamage, AController* damageInstigator);

	class AHnS_PlayerController* pController;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
