// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "HnS_Weapon.generated.h"

class AHnS_Bullet;
class AHnS_WAbility;
UCLASS()
class PDAI_PROJECT_API AHnS_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHnS_Weapon();
	void SetPlayerPointer(ACharacter* PlayerPointer);
	void SetProjectileSpawnLocation(USceneComponent* pSpawnLocation);

	void SetReady(bool value);
	UFUNCTION(BlueprintCallable)
	AActor* Attack();
	AActor* W();

	//UPROPERTY(EditDefaultsOnly)
	//float damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Stats")
	float Damage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
	float cooldown = 5;


	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	TSubclassOf<AHnS_Bullet> BulletToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	TSubclassOf<AHnS_WAbility> WToSpawn;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponMesh;

	ACharacter* Player;

	class AHns_CharacterPlayer* controlledPlayer;

	UPROPERTY()
	USceneComponent* spawnLocation;

	FVector cachedDest_W;

private:
	bool ready = true;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
