// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HnS_Bullet.generated.h"

UCLASS()
class PDAI_PROJECT_API AHnS_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHnS_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* BulletFX;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	virtual void BulletHit(AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* impactParticles;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* deathImpactParticles;

	UPROPERTY(EditDefaultsOnly)
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* hitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* ultimate_explosion;

	TArray<AActor*> ignoredActors;

	class AHnS_Character* ePlayerCharacter;

	AController* PlayerC;


	bool canDestroy = false;

	bool isOnUltimate = false;


	UPROPERTY(EditAnywhere)
	float timeToDestroy = 5.f;

	UPROPERTY(EditAnywhere)
	bool hurtsEnemies = true;

	void bulletDestroy(bool Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float Speed;

};
