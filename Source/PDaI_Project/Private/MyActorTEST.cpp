// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTEST.h"

// Sets default values
AMyActorTEST::AMyActorTEST()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyActorTEST::Execute()
{
}

void AMyActorTEST::SetReady(bool value)
{
}

// Called when the game starts or when spawned
void AMyActorTEST::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorTEST::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

