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

	UPROPERTY(EditAnywhere)
	float duration;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* WSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* fireSound;


	int prevFireTicks;

	FTimerHandle mTimerHandle;

	FVector wDestVector;

	bool canDamage = false;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void setLocationAfterDelay();

	void fireDamage(AActor* actorToDamage, AController* damageInstigator);

	void enableDamage();

	void disableEffect();

	class AHnS_PlayerController* pController;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
