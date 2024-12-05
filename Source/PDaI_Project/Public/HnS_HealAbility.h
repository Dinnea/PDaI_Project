// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HnS_Ability.h"
#include <PDaI_Project/HnS_Character.h>
#include <PDaI_Project/HnS_BaseEnemy.h>
#include "HnS_HealAbility.generated.h"



/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API AHnS_HealAbility : public AHnS_Ability
{
	GENERATED_BODY()
	

public:
	virtual bool Execute() override;
	AHnS_HealAbility();

protected:
	void BeginPlay();

private:
	UPROPERTY(EditDefaultsOnly)
	float hpThreshold = 0.5f;

	float range = 500;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* vfx;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* CollisionSphere;

	TArray<AHnS_BaseEnemy*> enemiesInRange;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	ACharacter* ReturnNearestNeedsHealing();

	bool IsHPBelowThreshold(AHnS_Character* tar);
	void StartCollisionChecking();
};
