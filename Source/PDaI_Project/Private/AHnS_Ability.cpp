// Fill out your copyright notice in the Description page of Project Settings.


#include "AHnS_Ability.h"

// Sets default values
AAHnS_Ability::AAHnS_Ability()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAHnS_Ability::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAHnS_Ability::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

