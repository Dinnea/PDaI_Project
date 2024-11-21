#include "HnS_Bullet.h"
#include "HnS_Bullet.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Bullet.h"
#include "HnS_Character.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

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
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_Bullet::BeginOverlap);
}

void AHnS_Bullet::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, OtherActor->GetFName().ToString());
	//OtherActor->GetFName().ToString() != "BP_HnS_PlayerChar_C_0"
	//GetOwner()->GetFName().ToString();
	if (GetOwner() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Owner nullptr"));
	}
	if (GetInstigator() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Instigator nullptr"));
	}
	AController* PlayerC = GetInstigator()->GetController(); //Instigator - Object which created the actor/event (player created bullet)
	if (OtherActor != PlayerC->GetPawn())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetFName().ToString());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, impactParticles, GetActorLocation());
		//BulletHit();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, PlayerC->GetPawn()->GetFName().ToString());
		UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, PlayerC, this, DamageType);
		Destroy();
	}
	if (Cast<AHnS_Character>(OtherActor)->HP <= 0)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, deathImpactParticles, GetActorLocation());
	}
}

void AHnS_Bullet::BulletHit()
{
}

// Called every frame
void AHnS_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *(this->GetActorLocation().ToString()));
}

