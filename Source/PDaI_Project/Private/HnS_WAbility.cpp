// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_WAbility.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AHnS_WAbility::AHnS_WAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	W_FX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	SetRootComponent(W_FX);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(W_FX);
	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	//ProjectileMovement->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void AHnS_WAbility::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("W casted"));
	//CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_WAbility::BeginOverlap);
	Super::BeginPlay();
	//CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_WAbility::BeginOverlap);
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Particle, GetActorLocation());
}

void AHnS_WAbility::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
// Called every frame
void AHnS_WAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

