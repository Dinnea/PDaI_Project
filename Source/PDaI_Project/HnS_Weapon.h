// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "Public/HnS_Ability.h"
#include "HnS_Weapon.generated.h"

UCLASS()
class PDAI_PROJECT_API AHnS_Weapon : public AHnS_Ability
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHnS_Weapon();
	void SetProjectileSpawnLocation(USceneComponent* pSpawnLocation);

	virtual bool Execute() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	TSubclassOf<AHnS_Bullet> BulletToSpawn;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY()
	USceneComponent* spawnLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
