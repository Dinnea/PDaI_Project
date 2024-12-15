// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <PDaI_Project/HnS_Bullet.h>
#include "HnS_RBullet.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API AHnS_RBullet : public AHnS_Bullet
{
	GENERATED_BODY()

	AHnS_RBullet();

	virtual void BeginPlay() override;

	void BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* ultimate_arrowSound;

	virtual void Tick(float DeltaTime) override;
	
};
