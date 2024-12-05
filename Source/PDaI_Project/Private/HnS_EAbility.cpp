// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_EAbility.h"
#include <PDaI_Project/HnS_Character.h>

// Sets default values
AHnS_EAbility::AHnS_EAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHnS_EAbility::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("E ability casted"));
	Super::BeginPlay();

	ePlayerCharacter = Cast<AHnS_Character>(GetInstigator());
	ePlayerCharacter->setCrouch(true);

	FTimerDelegate cDelegate = FTimerDelegate::CreateUObject(this, &AHnS_EAbility::disableCrouch);
	FTimerHandle cTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(cTimerHandle, cDelegate, 0.8, false);
	
}

void AHnS_EAbility::disableCrouch()
{
	ePlayerCharacter->setCrouch(false);
}

// Called every frame
void AHnS_EAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, ePlayerCharacter->trap_crouch ? TEXT("Crouch: true") : TEXT("Crouch: false"));

}

