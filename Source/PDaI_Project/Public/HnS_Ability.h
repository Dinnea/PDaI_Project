// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/WidgetComponent.h>
#include "HnS_Ability.generated.h"


UCLASS()
class PDAI_PROJECT_API AHnS_Ability : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHnS_Ability();

	UFUNCTION(BlueprintCallable)
	virtual bool Execute(bool flag);
	virtual bool ExecuteRSubclass();

	void SetReady(bool value);
	void SetUser(class AHnS_Character* pUser);

	UFUNCTION(BlueprintCallable)
	float GetTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float cooldown;

	UTexture2D* GetIcon();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float timerElapsed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float damage = 0;

	UPROPERTY()
	USceneComponent* spawnLocation;

	bool ready = true;
	class AHnS_Character* user;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmetic")
	UTexture2D* icon;

private:
	FTimerHandle cooldownHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

