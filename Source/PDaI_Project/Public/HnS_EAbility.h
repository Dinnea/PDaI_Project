// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HnS_EAbility.generated.h"

UCLASS()
class PDAI_PROJECT_API AHnS_EAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHnS_EAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AHnS_Character* ePlayerCharacter;

	TArray<AActor*> ignoredActors;

	//class AHnS_Weapon* eWeapon;

	void disableCrouch();

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* E_FX;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* E_aura;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* E_activate;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* trapMesh;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* E_ImmobilityEffect;

	UPROPERTY(EditAnywhere)
	float zOffset;

	UPROPERTY(EditAnywhere)
	float baseDamage;

	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	float effect_duration;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	class USoundBase* explosionSound;

	void despawn(AHnS_Character* otherPlayer);

	void despawn_delay(AHnS_Character* targetPlayer);

	UParticleSystemComponent* trap_active_particle;

	UParticleSystemComponent* immobility_effect;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
