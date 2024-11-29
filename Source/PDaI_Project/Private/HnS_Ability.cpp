// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Ability.h"

// Sets default values
AHnS_Ability::AHnS_Ability()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHnS_Ability::SetReady(bool value)
{
	ready = value;
}

void AHnS_Ability::SetOwner(ACharacter* pOwner)
{
	owner = pOwner;
}


bool AHnS_Ability::Execute()
{
	if (!ready) 
	{ 
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No execute."));
		return false; 
	}

	SetReady(false);
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_Ability::SetReady, true);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, cooldown, false);
	return true;
}

// Called when the game starts or when spawned
void AHnS_Ability::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHnS_Ability::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

