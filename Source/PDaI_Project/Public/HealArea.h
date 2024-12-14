// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealArea.generated.h"

UCLASS()
class PDAI_PROJECT_API AHealArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealArea();

	UPROPERTY(EditAnywhere)
	float healInterval;

	UPROPERTY(EditAnywhere)
	float healPerTick;

	UPROPERTY(EditAnywhere)
	float auraActivationCooldown;

	UPROPERTY(EditAnywhere)
	int initialUseAmount;

	UPROPERTY(EditAnywhere)
	int ticksAmount;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* greenFlare1;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* greenFlare2;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* greenFlare3;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* greenFlare4;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* redFlare1;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* redFlare2;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* redFlare3;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* redFlare4;

	int prevTickAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AHnS_Character* controlled_player;

	class AHnS_PlayerController* PlayerC;

	FTimerHandle hTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* CollisionSphere;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void heal();

	void aura_cooldown();

	void flare_toggleVisibility(bool color);

	bool canHeal = false;

	bool canUseAura = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
