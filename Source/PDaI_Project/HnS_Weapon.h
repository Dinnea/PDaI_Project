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
	void SetAbilitySpawnLocation(USceneComponent* pSpawnLocation);

	virtual bool Execute(bool flag) override;
	virtual bool ExecuteRSubclass() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	TSubclassOf<AActor> objectToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	TSubclassOf<class AHnS_RBullet> r_objectToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	FVector Offset;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	class AHnS_Character* pCharacter;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
