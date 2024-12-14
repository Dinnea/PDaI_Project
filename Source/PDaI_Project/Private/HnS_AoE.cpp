// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_AoE.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <PDaI_Project/HnS_Character.h>
#include <PDaI_Project/Hns_CharacterPlayer.h>
#include <PDaI_Project/HnS_BaseEnemy.h>

// Sets default values
AHnS_AoE::AHnS_AoE()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	vfx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));
	SetRootComponent(vfx);

	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(vfx);

	

}

// Called when the game starts or when spawned
void AHnS_AoE::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(GetActorLocation() + FVector(0, 0, 10000));
	vfx->SetNiagaraVariableFloat(FString("angle"), angle);
	vfx->SetNiagaraVariableFloat(FString("length"), range);
	vfx->SetNiagaraVariableFloat(FString("lifetime"), lifeTime-.5f);
	CollisionSphere->SetSphereRadius(range);

	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_AoE::OnTimeout);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, lifeTime, false);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_AoE::BeginOverlap);

	FTimerDelegate collisionDelegate = FTimerDelegate::CreateUObject(this, &AHnS_AoE::StartCollisionChecking);
	GetWorld()->GetTimerManager().SetTimerForNextTick(collisionDelegate);
	
}

//find objects in collider-> find n

void AHnS_AoE::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* caster = GetInstigator();
	if (auto* targetPtr = Cast<AHnS_Character>(OtherActor))
	{
		if (OtherActor != caster && !targetPtr->invulnerable)
		{
			FVector casterLocation = caster->GetActorLocation();
			FVector targetLocation = targetPtr->GetActorLocation();

			FVector directionVector = targetLocation - casterLocation;


			directionVector.Normalize();
			FVector forward = caster->GetActorForwardVector();

			float dot = forward.Dot(directionVector);

			float angleDegrees = acos(dot) * (180.0 / 3.141592653589793238463f);

			if (auto* tempCaster = Cast<AHns_CharacterPlayer>(caster))
			{
				if (auto* tempTarget = Cast<AHnS_BaseEnemy>(targetPtr))
				{
					if (angleDegrees <= angle / 2.f)
					{
						UGameplayStatics::ApplyDamage(OtherActor, damage, GetInstigatorController(), this, DamageType);
						//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(angleDegrees));
					}
				}
			}
			else
			{
				if (auto* tempTarget = Cast<AHns_CharacterPlayer>(OtherActor))
				{
					if (angleDegrees <= angle / 2.f)
					{
						UGameplayStatics::ApplyDamage(OtherActor, damage, GetInstigatorController(), this, DamageType);
						
					}
				}
			}
		}
	}
	
}

void AHnS_AoE::StartCollisionChecking()
{
	SetActorLocation(GetActorLocation() - FVector(0, 0, 10000));
}

void AHnS_AoE::OnTimeout()
{
	this->Destroy();
}

// Called every frame
void AHnS_AoE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

