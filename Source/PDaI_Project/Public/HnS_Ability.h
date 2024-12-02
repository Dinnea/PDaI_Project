// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HnS_Ability.generated.h"

UCLASS()
class PDAI_PROJECT_API AHnS_Ability : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHnS_Ability();

	UFUNCTION(BlueprintCallable)
	virtual bool Execute();

	void SetReady(bool value);
	void SetUser(ACharacter* pUser);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float cooldown = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float damage = 0;

	UPROPERTY()
	USceneComponent* spawnLocation;

	bool ready = true;
	ACharacter* user;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

