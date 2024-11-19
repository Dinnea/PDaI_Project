// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Bullet.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AHnS_Bullet::AHnS_Bullet()
{
	BulletFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	SetRootComponent(BulletFX);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(BulletFX);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovement->ProjectileGravityScale = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ProjectileMovement);

	PrimaryActorTick.bCanEverTick = true;

	//UPROPERTY(EditDefaultsOnly)

}

// Called when the game starts or when spawned
void AHnS_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHnS_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

